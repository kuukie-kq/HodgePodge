package com.southbound.router.channel;

import com.southbound.router.util.RouterUtils;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.util.Attribute;
import io.netty.util.AttributeKey;

public class ForwardingBound extends ChannelInboundHandlerAdapter {
    @Override
    public void channelActive(ChannelHandlerContext ctx) throws Exception {
        System.out.println("<Forward:>Active");

        AttributeKey<Object> attributeKey = AttributeKey.valueOf("response");
        Attribute<Object> attribute = ctx.channel().attr(attributeKey);
        String response = attribute.get().toString();
        System.out.println(response);

        ctx.channel().writeAndFlush(ctx.alloc().buffer().writeBytes(response.getBytes(RouterUtils.charset)));
        //System.out.println(response);
    }
    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        ByteBuf byteBuf = (ByteBuf) msg;
        System.out.println("<Forward:>Read");
        System.out.println(byteBuf.toString(RouterUtils.charset));
    }
}
