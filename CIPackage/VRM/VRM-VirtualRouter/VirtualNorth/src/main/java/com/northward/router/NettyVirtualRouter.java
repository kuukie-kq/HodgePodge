package com.northward.router;

import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.Channel;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import io.netty.util.AttributeKey;
import com.northward.router.channel.NettyVirtualRouterHandler;
import redis.clients.jedis.Jedis;

public class NettyVirtualRouter {
    private int routerId;

    public NettyVirtualRouter(int routerId) {
        this.routerId = routerId;
    }

    public void run() {
        try {
            EventLoopGroup bossGroup = new NioEventLoopGroup();
            EventLoopGroup workGroup = new NioEventLoopGroup();

            AttributeKey<Object> routerAttrKey = AttributeKey.valueOf("routerId");

            ServerBootstrap serverBootstrap = new ServerBootstrap();
            serverBootstrap.group(bossGroup,workGroup);
            serverBootstrap.childAttr(routerAttrKey,routerId);
            serverBootstrap.channel(NioServerSocketChannel.class);
            serverBootstrap.childHandler(new NettyVirtualRouterHandler());

            Jedis jedis = new Jedis("127.0.0.1",6379);
            String router = jedis.get(String.valueOf(routerId));
            jedis.close();
            String port = router.split(":")[1].trim();
            Channel channel = serverBootstrap.bind(Integer.parseInt(port)).sync().channel();
            channel.closeFuture().sync();

            workGroup.shutdownGracefully();
            bossGroup.shutdownGracefully();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if(args.length == 1) {
            NettyVirtualRouter nettyVirtualRouter = new NettyVirtualRouter(Integer.parseInt(args[0]));
            nettyVirtualRouter.run();
        } else {
            System.err.println("Run error, there have one parameter of process.");
        }
    }
}
