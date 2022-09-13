package com.northward.router.channel;

import com.northward.router.bean.Host;
import com.northward.router.bean.Router;
import com.northward.router.bean.RouterTable;
import com.northward.router.util.RouterUtils;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.util.Attribute;
import io.netty.util.AttributeKey;
import redis.clients.jedis.Jedis;

public class LookingForNext extends ChannelInboundHandlerAdapter {
    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        System.out.println("<LookingForNext><channelRead()>====");
        String request = (String) msg;
        //System.out.println(request);

        if(request.split(RouterUtils.SEPLUS).length == 2) {
            String virtual = request.split(RouterUtils.SEPLUS)[0].trim();
            if(virtual.split(RouterUtils.FORWARD).length == 2) {
                String requestBody = request.split(RouterUtils.SEPLUS)[1];
                String virtualBody = virtual.split(RouterUtils.FORWARD)[0].trim();
                if(virtualBody.split("->").length == 2) {
                    String[] virtualFT = virtualBody.split("->");

                    AttributeKey<Object> attributeKey = AttributeKey.valueOf("routerId");
                    Attribute<Object> attribute = ctx.channel().attr(attributeKey);
                    Object attr = attribute.get();
                    //System.out.println(Integer.parseInt(attr.toString()));
                    Jedis jedis = new Jedis("127.0.0.1",6379);
                    jedis.rpush(RouterUtils.routerDao.lookupRouterById(Integer.parseInt(attr.toString())).getRouterName(),virtualBody);
                    jedis.close();

                    RouterTable routerTable = RouterUtils.routerTableDao.lookupRouterTableByIdAndName(Integer.parseInt(attr.toString()),virtualFT[1]);
                    if(routerTable.getNextAddressName() == null) {
                        System.out.println("There are not have gold.");
                        String stringLaze = virtualFT[1];
                        stringLaze = stringLaze + RouterUtils.LAZE + "jiaoyan" +
                                RouterUtils.SEPLUS + requestBody;
                        ctx.write(ctx.alloc().buffer().writeBytes(stringLaze.getBytes(RouterUtils.charset)));
                        ctx.fireChannelRead(stringLaze);
                    } else {
                        Router router = RouterUtils.routerDao.lookupRouterByName(routerTable.getNextAddressName());
                        if(router.getRouterAddress() == null) {
                            Host host = RouterUtils.hostDao.lookupHostByName(routerTable.getNextAddressName());
                            if(host.getHostAddress() == null) {
                                System.err.println("Router and Host table are not have address");
                            } else {
                                System.out.println("send my host");
                                String address = host.getHostAddress();
                                address = address + RouterUtils.CONNECT + "jiaoyan" +
                                        RouterUtils.SEPLUS + requestBody;
                                ctx.write(ctx.alloc().buffer().writeBytes(address.getBytes(RouterUtils.charset)));
                                ctx.fireChannelRead(address);
                            }
                        } else {
                            System.out.println("send the next");
                            String address = router.getRouterAddress();
                            address = address + RouterUtils.CONNECT + "jiaoyan" +
                                    RouterUtils.SEPLUS + requestBody;
                            ctx.write(ctx.alloc().buffer().writeBytes(address.getBytes(RouterUtils.charset)));
                            ctx.fireChannelRead(address);
                        }
                    }
                } else {
                    System.err.println("The VirtualRouter forwarding parameter is not (xx)->(xx)");
                    ctx.write(ctx.alloc().buffer().writeBytes(requestBody.getBytes(RouterUtils.charset)));
                    ctx.fireChannelRead(requestBody);
                }
            } else {
                ctx.write(ctx.alloc().buffer().writeBytes(request.getBytes(RouterUtils.charset)));
                ctx.fireChannelRead(request);
            }
        } else {
            ctx.write(ctx.alloc().buffer().writeBytes(request.getBytes(RouterUtils.charset)));
            ctx.fireChannelRead(request);
        }
    }

    @Override
    public void channelReadComplete(ChannelHandlerContext ctx) throws Exception {
        System.out.println("<LookingForNext><channelReadComplete()>====");
        ctx.flush();
    }
}
