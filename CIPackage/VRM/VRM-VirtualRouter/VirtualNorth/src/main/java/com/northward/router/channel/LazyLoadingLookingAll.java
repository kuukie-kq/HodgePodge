package com.northward.router.channel;

import com.northward.router.bean.Router;
import com.northward.router.bean.RouterTable;
import com.northward.router.util.RouterUtils;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.util.Attribute;
import io.netty.util.AttributeKey;

public class LazyLoadingLookingAll extends ChannelInboundHandlerAdapter {
    @Override
    public void channelActive(ChannelHandlerContext ctx) throws Exception {
        System.out.println("<LazyLoadingLookingAll><channelActive()>====");

        AttributeKey<Object> attributeKey = AttributeKey.valueOf("routerId");
        Attribute<Object> attribute = ctx.channel().attr(attributeKey);
        Object attr = attribute.get();
        //System.out.println(Integer.parseInt(attr.toString()));

        String lookingFroRouter = "RouterTable:";
        Router router = RouterUtils.routerDao.lookupRouterById(Integer.parseInt(attr.toString()));
        for (RouterTable stringTable : RouterUtils.routerTableDao.lookupRouterTableById(Integer.parseInt(attr.toString()))) {
            lookingFroRouter = lookingFroRouter + stringTable.getReachableAddressName() + "-" +
                    (stringTable.getReachableDistance() + 1) + "-" + router.getRouterName() + "<>";
        }
        lookingFroRouter = lookingFroRouter + RouterUtils.SEQUENCE + RouterUtils.SEQUENCE;
        ctx.channel().writeAndFlush(ctx.alloc().buffer().writeBytes(lookingFroRouter.getBytes(RouterUtils.charset)));
    }

    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        ByteBuf byteBuf = (ByteBuf) msg;
        System.out.println("<LazyLoadingLookingAll><channelRead()>====");
        //System.out.println(byteBuf.toString(RouterUtils.charset));

        AttributeKey<Object> routerIdKey = AttributeKey.valueOf("routerId");
        Attribute<Object> attribute = ctx.channel().attr(routerIdKey);
        Object attr = attribute.get();
        //System.out.println(Integer.parseInt(attr.toString()));
        AttributeKey<Object> routerVirtualKey = AttributeKey.valueOf("virtualBody");
        Attribute<Object> virtualBodyAttr = ctx.channel().attr(routerVirtualKey);
        String virtualBody = virtualBodyAttr.get().toString();
        //System.out.println(virtualBody);
        AttributeKey<Object> routerRequestKey = AttributeKey.valueOf("requestBody");
        Attribute<Object> requestBodyAttr = ctx.channel().attr(routerRequestKey);
        String requestBody = requestBodyAttr.get().toString();
        //System.out.println(requestBody);

        int length = byteBuf.toString(RouterUtils.charset).split(":").length;
        for (String table : byteBuf.toString(RouterUtils.charset).split(":")[length-1].trim().split("<>")) {
            String[] columns = table.split("-");
            if (columns[0].equals(virtualBody)) {
                Router routerVirtual = RouterUtils.routerDao.lookupRouterByName(columns[2]);
                if (routerVirtual.getRouterAddress() == null) {
                    System.err.println("Forwarding failed...");
                } else {
                    synchronized (RouterTable.class) {
                        RouterTable routerTable = RouterUtils.routerTableDao.lookupRouterTableByIdAndName(Integer.parseInt(attr.toString()),virtualBody);
                        if(routerTable.getNextAddressName() == null) {
                            routerTable.setTableId(-1);
                            Router insertData = RouterUtils.routerDao.lookupRouterById(Integer.parseInt(attr.toString()));
                            routerTable.setTableName(insertData.getRouterName() + "To" + columns[0]);
                            routerTable.setRouterId(Integer.parseInt(attr.toString()));
                            routerTable.setReachableAddressName(columns[0]);
                            routerTable.setReachableDistance(Integer.parseInt(columns[1]));
                            routerTable.setNextAddressName(columns[2]);
                            RouterUtils.routerTableDao.lookRouterTable(routerTable);

                            String lazy = insertData.getRouterAddress();
                            lazy = lazy + RouterUtils.CONNECT + "jiaoyan" +
                                    RouterUtils.SEPLUS + requestBody;
                            ctx.write(ctx.alloc().buffer().writeBytes(lazy.getBytes(RouterUtils.charset)));
                            ctx.fireChannelRead(lazy);
                        }
                    }
                }
                break;
            }
        }

        String dns = "Not Found";
        dns = dns + RouterUtils.DNS + "jiaoyan" +
                RouterUtils.SEPLUS + requestBody;
        ctx.write(ctx.alloc().buffer().writeBytes(dns.getBytes(RouterUtils.charset)));
        ctx.fireChannelRead(dns);
    }
}
