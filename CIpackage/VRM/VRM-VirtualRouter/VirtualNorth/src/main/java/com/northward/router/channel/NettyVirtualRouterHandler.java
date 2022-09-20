package com.northward.router.channel;

import io.netty.channel.ChannelInitializer;
import io.netty.channel.socket.SocketChannel;

public class NettyVirtualRouterHandler extends ChannelInitializer<SocketChannel> {
    @Override
    protected void initChannel(SocketChannel socketChannel) throws Exception {
        socketChannel.pipeline().addLast(new AnalyzeCustomProtocols());
        socketChannel.pipeline().addLast(new LookingForNext());
        socketChannel.pipeline().addLast(new LookingForRouterLazyLoading());
        socketChannel.pipeline().addLast(new RoutingTableUpdate());
        socketChannel.pipeline().addLast(new EndOfCycleAndForwarding());
    }
}
