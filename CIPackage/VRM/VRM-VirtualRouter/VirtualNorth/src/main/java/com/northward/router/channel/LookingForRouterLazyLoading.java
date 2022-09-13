package com.northward.router.channel;

import com.northward.router.bean.Router;
import com.northward.router.util.RouterUtils;
import io.netty.bootstrap.Bootstrap;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.channel.socket.nio.NioSocketChannel;
import io.netty.util.Attribute;
import io.netty.util.AttributeKey;

public class LookingForRouterLazyLoading extends ChannelInboundHandlerAdapter {
    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        System.out.println("<LookingForRouterLazyLoading><channelRead()>====");
        String request = (String) msg;
        //System.out.println(request);

        if(request.split(RouterUtils.SEPLUS).length == 2) {
            String virtual = request.split(RouterUtils.SEPLUS)[0].trim();
            if(virtual.split(RouterUtils.LAZE).length == 2) {
                String requestBody = request.split(RouterUtils.SEPLUS)[1];
                String virtualBody = virtual.split(RouterUtils.LAZE)[0].trim();
                System.err.println(virtualBody);

                AttributeKey<Object> attributeKey = AttributeKey.valueOf("routerId");
                Attribute<Object> attribute = ctx.channel().attr(attributeKey);
                Object attr = attribute.get();
                //System.out.println(Integer.parseInt(attr.toString()));

                for(Router router:RouterUtils.routerDao.lookupRouterGetRouters()) {
                    if (router.getRouterId() == Integer.parseInt(attr.toString())) {
                        continue;
                    }
                    AttributeKey<Object> routerIdKey = AttributeKey.valueOf("routerId");
                    AttributeKey<Object> routerVirtualKey = AttributeKey.valueOf("virtualBody");
                    AttributeKey<Object> routerRequestKey = AttributeKey.valueOf("requestBody");

                    Bootstrap bootstrap = new Bootstrap();
                    bootstrap.group(ctx.channel().eventLoop());
                    bootstrap.attr(routerIdKey,attr);
                    bootstrap.attr(routerVirtualKey,virtualBody);
                    bootstrap.attr(routerRequestKey,requestBody);
                    bootstrap.channel(NioSocketChannel.class);
                    bootstrap.handler(new LazyLoadingHandler());

                    String[] address = router.getRouterAddress().split(":");
                    bootstrap.connect(address[0], Integer.parseInt(address[1])).addListener(future -> {
                        if(future.isSuccess()) {
                            System.out.println("Connect success :)");
                        } else {
                            System.err.println("Connect error please try again");
                        }
                    });
                }

                ctx.write(ctx.alloc().buffer().writeBytes(RouterUtils.LAZE.getBytes(RouterUtils.charset)));
                //ctx.fireChannelRead(RouterUtils.LAZE);
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
        System.out.println("<LookingForRouterLazyLoading><channelReadComplete()>====");
        ctx.flush();
    }
}
