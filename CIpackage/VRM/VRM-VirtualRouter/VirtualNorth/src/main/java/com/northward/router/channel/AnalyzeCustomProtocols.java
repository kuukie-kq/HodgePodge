package com.northward.router.channel;

import com.northward.router.util.RouterUtils;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;


public class AnalyzeCustomProtocols extends ChannelInboundHandlerAdapter {
    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
        System.out.println("<AnalyzeCustomProtocols><channelRead()>====");
        String request = ((ByteBuf) msg).toString(RouterUtils.charset);
        //System.out.println(request);

        String head = request.split(RouterUtils.SEQUENCE+RouterUtils.SEQUENCE)[0];
        String stringForward = null;
        boolean flagForward = false;
        String stringUpdate = null;
        boolean flagUpdate = false;
        for(String lineHead:head.split(RouterUtils.SEQUENCE)) {
            if(lineHead.startsWith(RouterUtils.VR)) {
                flagForward = true;
                stringForward = lineHead.split(":")[1].trim();
            } else if(lineHead.startsWith(RouterUtils.RT)) {
                flagUpdate = true;
                stringUpdate = lineHead.split(":")[1].trim();
            } else {
                continue;
            }
        }
        if(flagForward) {
            stringForward = stringForward + RouterUtils.FORWARD + "jiaoyan" +
                    RouterUtils.SEPLUS + request;
            ctx.write(ctx.alloc().buffer().writeBytes(stringForward.getBytes(RouterUtils.charset)));
            ctx.fireChannelRead(stringForward);
        } else if(flagUpdate) {
            stringUpdate = stringUpdate + RouterUtils.UPDATE + "jiaoyan" +
                    RouterUtils.SEPLUS + request;
            ctx.write(ctx.alloc().buffer().writeBytes(stringUpdate.getBytes(RouterUtils.charset)));
            ctx.fireChannelRead(stringUpdate);
        } else {
            ctx.write(ctx.alloc().buffer().writeBytes(request.getBytes(RouterUtils.charset)));
            ctx.fireChannelRead(request);
        }
    }

    @Override
    public void channelReadComplete(ChannelHandlerContext ctx) throws Exception {
        System.out.println("<AnalyzeCustomProtocols><channelReadComplete()>====");
        ctx.flush();
    }
}
