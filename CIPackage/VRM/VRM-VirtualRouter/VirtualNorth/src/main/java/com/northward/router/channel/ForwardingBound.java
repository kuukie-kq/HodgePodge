package com.northward.router.channel;

import com.northward.router.util.RouterUtils;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.util.Attribute;
import io.netty.util.AttributeKey;

public class ForwardingBound extends ChannelInboundHandlerAdapter {
    @Override
    public void channelActive(ChannelHandlerContext ctx) throws Exception {
        System.out.println("<Forward:>Active");

        AttributeKey<Object> attributeKey = AttributeKey.valueOf("requestBody");
        Attribute<Object> attribute = ctx.channel().attr(attributeKey);
        String requestBody = attribute.get().toString();
        //System.out.println(requestBody);

        ctx.channel().writeAndFlush(ctx.alloc().buffer().writeBytes(requestBody.getBytes(RouterUtils.charset)));
        //System.out.println(requestBody);
    }
    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        ByteBuf byteBuf = (ByteBuf) msg;
        System.out.println("<Forward:>Read");
        System.out.println(byteBuf.toString(RouterUtils.charset));
    }
}
