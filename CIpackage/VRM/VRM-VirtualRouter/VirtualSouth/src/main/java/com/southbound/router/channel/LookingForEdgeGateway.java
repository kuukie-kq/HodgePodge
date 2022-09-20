package com.southbound.router.channel;

import com.southbound.router.bean.Host;
import com.southbound.router.util.RouterUtils;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;

import java.net.InetAddress;

public class LookingForEdgeGateway extends ChannelInboundHandlerAdapter {
    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        System.out.println("<LookingForEdgeGateway><channelRead()>====");
        String request = (String) msg;
        //System.out.println(request);

        if(request.split(RouterUtils.SEPLUS).length == 2) {
            String virtual = request.split(RouterUtils.SEPLUS)[0].trim();
            if(virtual.split(RouterUtils.EDGE).length == 2) {
                String requestBody = request.split(RouterUtils.SEPLUS)[1];
                String virtualBody = virtual.split(RouterUtils.EDGE)[0].trim();

                String[] fromToTarget = virtualBody.split("->");
                Host hosts = RouterUtils.hostDao.lookupHostByName(fromToTarget[0]);
                if(hosts.getHostName() == null) {
                    hosts = RouterUtils.hostDao.lookupHostByName(fromToTarget[1]);
                    if(hosts.getHostName() == null) {
                        System.err.println("error");
                    } else {
                        String response = "127.0.0.1:55031";
                        response = request + RouterUtils.CONNECT + "jiaoyan" +
                                RouterUtils.SEPLUS + requestBody;
                        ctx.write(ctx.alloc().buffer().writeBytes(response.getBytes(RouterUtils.charset)));
                        ctx.fireChannelRead(response);
                    }
                } else {
                    InetAddress[] addresses = InetAddress.getAllByName(fromToTarget[1]);
                    if(addresses.length > 0) {
                        String dns = virtualBody;
                        dns = dns + RouterUtils.CONNECT + "jiaoyan" +
                                RouterUtils.SEPLUS + requestBody;
                        ctx.write(ctx.alloc().buffer().writeBytes(dns.getBytes(RouterUtils.charset)));
                        ctx.fireChannelRead(dns);
                    } else {
                        System.err.println("There are not dns");
                    }
                }


            } else {
                ctx.write(ctx.alloc().buffer().writeBytes(("error 500 for" + request).getBytes(RouterUtils.charset)));
                //ctx.fireChannelRead(request);
            }
        } else {
            ctx.write(ctx.alloc().buffer().writeBytes(request.getBytes(RouterUtils.charset)));
            //ctx.fireChannelRead(request);
        }
    }

    @Override
    public void channelReadComplete(ChannelHandlerContext ctx) throws Exception {
        System.out.println("<EndOfCycleAndForwarding><channelReadComplete()>====");
        ctx.flush();
    }
}
