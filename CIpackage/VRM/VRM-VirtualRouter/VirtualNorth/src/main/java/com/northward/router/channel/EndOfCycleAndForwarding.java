package com.northward.router.channel;

import com.northward.router.util.RouterUtils;
import io.netty.bootstrap.Bootstrap;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.channel.socket.nio.NioSocketChannel;
import io.netty.util.AttributeKey;

public class EndOfCycleAndForwarding extends ChannelInboundHandlerAdapter {
    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        System.out.println("<EndOfCycleAndForwarding><channelRead()>====");
        String request = (String) msg;
        //System.out.println(request);

        if(request.split(RouterUtils.SEPLUS).length == 2) {
            String virtual = request.split(RouterUtils.SEPLUS)[0].trim();
            if(virtual.split(RouterUtils.CONNECT).length == 2) {
                String requestBody = request.split(RouterUtils.SEPLUS)[1];
                String virtualBody = virtual.split(RouterUtils.CONNECT)[0].trim();

                AttributeKey<Object> routerAttrKey = AttributeKey.valueOf("requestBody");

                Bootstrap bootstrap = new Bootstrap();
                bootstrap.group(ctx.channel().eventLoop());
                bootstrap.attr(routerAttrKey,requestBody);
                bootstrap.channel(NioSocketChannel.class);
                bootstrap.handler(new ForwardingHandler());

                String[] port = virtualBody.split(":");
                bootstrap.connect(port[0],Integer.parseInt(port[1])).addListener(future -> {
                    if(future.isSuccess()) {
                        System.out.println("Connect success :)");
                    } else {
                        System.err.println("Connect error please try again");
                    }
                });

            } else if(virtual.split(RouterUtils.DNS).length == 2) {
                String requestBody = request.split(RouterUtils.SEPLUS)[1];
                String virtualBody = virtual.split(RouterUtils.DNS)[0].trim();
                System.err.println(virtualBody);
                System.err.println(requestBody);

                ctx.close();
                AttributeKey<Object> routerAttrKey = AttributeKey.valueOf("requestBody");

                Bootstrap bootstrap = new Bootstrap();
                bootstrap.group(ctx.channel().eventLoop());
                bootstrap.attr(routerAttrKey,requestBody);
                bootstrap.channel(NioSocketChannel.class);
                bootstrap.handler(new ForwardingHandler());

                bootstrap.connect("127.0.0.1",55001).addListener(future -> {
                    if(future.isSuccess()) {
                        System.out.println("Connect success :)");
                    } else {
                        System.err.println("Connect error please try again");
                    }
                });

                //ctx.write(ctx.alloc().buffer().writeBytes(("error 530 for" + virtualBody).getBytes(RouterUtils.charset)));
                //ctx.fireChannelRead(request);
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
