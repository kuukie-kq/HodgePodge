package com.southbound.router.channel;

import com.southbound.router.util.RouterUtils;
import com.southbound.router.util.TestUtilGP;
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

                System.err.println(virtualBody);
                String[] port = virtualBody.split("->");
                ctx.close();

                if(port.length == 2) {
                    String response = TestUtilGP.send(port[1],port[0],requestBody);

                    AttributeKey<Object> attributeKey = AttributeKey.valueOf("response");

                    Bootstrap bootstrap = new Bootstrap();
                    bootstrap.group(ctx.channel().eventLoop());
                    bootstrap.attr(attributeKey,response);
                    bootstrap.channel(NioSocketChannel.class);
                    bootstrap.handler(new ForwardingHandler());

                    bootstrap.connect("127.0.0.1",55031).addListener(future -> {
                        if(future.isSuccess()) {
                            System.out.println("Connect success :)");
                        } else {
                            System.err.println("Connect error please try again");
                        }
                    });
                } else {
                    AttributeKey<Object> attributeKey = AttributeKey.valueOf("response");

                    Bootstrap bootstrap = new Bootstrap();
                    bootstrap.group(ctx.channel().eventLoop());
                    bootstrap.attr(attributeKey,"response 404");
                    bootstrap.channel(NioSocketChannel.class);
                    bootstrap.handler(new ForwardingHandler());

                    bootstrap.connect("127.0.0.1",55031).addListener(future -> {
                        if(future.isSuccess()) {
                            System.out.println("Connect success :)");
                        } else {
                            System.err.println("Connect error please try again");
                        }
                    });
                }
            } else {
                ctx.write(ctx.alloc().buffer().writeBytes(("error 500 for" + request).getBytes(RouterUtils.charset)));
                //ctx.fireChannelRead(request);
            }
        } else {
            System.err.println(request);
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
