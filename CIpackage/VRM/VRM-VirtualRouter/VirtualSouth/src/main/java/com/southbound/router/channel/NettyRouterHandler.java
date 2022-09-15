package com.southbound.router.channel;

import io.netty.channel.ChannelInitializer;
import io.netty.channel.socket.SocketChannel;

public class NettyRouterHandler extends ChannelInitializer<SocketChannel> {
    @Override
    protected void initChannel(SocketChannel socketChannel) throws Exception {
        socketChannel.pipeline().addLast(new AnalyzeCustomProtocols());
        socketChannel.pipeline().addLast(new LookingForEdgeGateway());
        socketChannel.pipeline().addLast(new EndOfCycleAndForwarding());
    }
}
