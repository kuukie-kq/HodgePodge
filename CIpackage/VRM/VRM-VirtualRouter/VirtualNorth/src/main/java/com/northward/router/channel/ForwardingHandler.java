package com.northward.router.channel;

import io.netty.channel.ChannelInitializer;
import io.netty.channel.socket.SocketChannel;

public class ForwardingHandler extends ChannelInitializer<SocketChannel> {
    @Override
    protected void initChannel(SocketChannel socketChannel) throws Exception {
        socketChannel.pipeline().addLast(new ForwardingBound());
    }
}
