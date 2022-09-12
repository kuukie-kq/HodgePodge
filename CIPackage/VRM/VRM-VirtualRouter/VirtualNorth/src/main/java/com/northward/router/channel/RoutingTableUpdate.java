package com.northward.router.channel;

import com.northward.router.bean.Router;
import com.northward.router.bean.RouterTable;
import com.northward.router.util.RouterUtils;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.util.Attribute;
import io.netty.util.AttributeKey;
import redis.clients.jedis.Jedis;

public class RoutingTableUpdate extends ChannelInboundHandlerAdapter {
    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        System.out.println("<RoutingTableUpdate><channelRead()>====");
        String request = (String) msg;
        //System.out.println(request);

        if(request.split(RouterUtils.SEPLUS).length == 2) {
            String virtual = request.split(RouterUtils.SEPLUS)[0].trim();
            if(virtual.split(RouterUtils.UPDATE).length == 2) {
                String virtualBody = virtual.split(RouterUtils.UPDATE)[0].trim();

                AttributeKey<Object> attributeKey = AttributeKey.valueOf("routerId");
                Attribute<Object> attribute = ctx.channel().attr(attributeKey);
                Object attr = attribute.get();
                //System.out.println(Integer.parseInt(attr.toString()));
                Jedis jedis = new Jedis("127.0.0.1",6379);
                jedis.rpush(RouterUtils.routerDao.lookupRouterById(Integer.parseInt(attr.toString())).getRouterName(),virtualBody);
                jedis.close();

                for(String routingTable:virtualBody.split("<>")) {
                    if(routingTable.split("-").length == 3) {
                        String[] routingColumns = routingTable.split("-");
                        RouterTable routerDatabase = RouterUtils.routerTableDao.lookupRouterTableByIdAndName(Integer.parseInt(attr.toString()),routingColumns[0]);
                        if(routerDatabase.getNextAddressName() == null) {
                            // insert table
                            RouterTable insertData = new RouterTable();
                            insertData.setTableId(-1);
                            Router router = RouterUtils.routerDao.lookupRouterById(Integer.parseInt(attr.toString()));
                            insertData.setTableName(router.getRouterName() + "To" + routingColumns[0]);
                            insertData.setRouterId(Integer.parseInt(attr.toString()));
                            insertData.setReachableAddressName(routingColumns[0]);
                            insertData.setReachableDistance(Integer.parseInt(routingColumns[1]));
                            insertData.setNextAddressName(routingColumns[2]);
                            RouterUtils.routerTableDao.lookRouterTable(insertData);
                        } else {
                            if(routerDatabase.getNextAddressName().equals(routingColumns[2])) {
                                //update distance
                                RouterUtils.routerTableDao.lookRouterTableByDistance(Integer.parseInt(routingColumns[1]),routerDatabase.getTableId());
                            } else {
                                if(routerDatabase.getReachableDistance() > Integer.parseInt(routingColumns[1])) {
                                    //update nextAddressName
                                    RouterUtils.routerTableDao.lookRouterTableByDistanceAndNext(Integer.parseInt(routingColumns[1]),routingColumns[2],routerDatabase.getTableId());
                                } else {
                                    System.out.println("Keep unchanged.");
                                }
                            }
                        }
                    } else {
                        System.out.println("This columns has not compliance with specifications." +
                                "It's " + routingTable + ".");
                    }
                }

                //ACK
                String message = RouterUtils.RT + ":";
                Router router = RouterUtils.routerDao.lookupRouterById(Integer.parseInt(attr.toString()));
                for(RouterTable stringTable:RouterUtils.routerTableDao.lookupRouterTableById(Integer.parseInt(attr.toString()))) {
                    message = message + stringTable.getReachableAddressName() + "-" +
                            (stringTable.getReachableDistance() + 1) + "-" + router.getRouterName() + "<>";
                }
                message = message + RouterUtils.SEQUENCE + RouterUtils.SEQUENCE;
                ctx.write(ctx.alloc().buffer().writeBytes(message.getBytes(RouterUtils.charset)));
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
        System.out.println("<RoutingTableUpdate><channelReadComplete()>====");
        ctx.flush();
    }
}
