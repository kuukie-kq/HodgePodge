package com.boot.web.controller;

import com.boot.web.bean.Router;
import com.boot.web.dao.HostDao;
import com.boot.web.dao.HostRelationshipDao;
import com.boot.web.dao.RouterDao;
import com.boot.web.service.RelationshipService;
import io.netty.bootstrap.Bootstrap;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioSocketChannel;
import net.sf.json.JSONArray;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.concurrent.TimeUnit;

@Controller
@RequestMapping(value = "/service")
public class ServiceBoardController {
    @Autowired
    HostDao hostDao;
    @Autowired
    HostRelationshipDao hostRelationshipDao;
    @Autowired
    RelationshipService relationshipService;
    @Autowired
    RouterDao routerDao;
    @Autowired
    RedisTemplate redisTemplate;

    @RequestMapping(value = "/sendRAR", method = RequestMethod.POST)
    @ResponseBody
    public String boardSendEvent(@RequestParam String head,@RequestParam String body) {
        try {
            NioEventLoopGroup workerGroup = new NioEventLoopGroup();
            Bootstrap bootstrap = new Bootstrap();
            bootstrap.group(workerGroup);
            bootstrap.channel(NioSocketChannel.class);
            bootstrap.handler(new ChannelInitializer<SocketChannel>() {
                @Override
                protected void initChannel(SocketChannel socketChannel) throws Exception {
                    socketChannel.pipeline().addLast(new ChannelInboundHandlerAdapter() {
                        @Override
                        public void channelActive(ChannelHandlerContext ctx) throws Exception {
                            System.out.println("<Host:>Active");

                            ByteBuf byteBuf = getByteBuf(ctx);

                            ctx.channel().writeAndFlush(byteBuf);
                        }

                        @Override
                        public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
                            ByteBuf byteBuf = (ByteBuf) msg;
                            System.out.println("<Host:>Read");
                            System.out.println(byteBuf.toString(StandardCharsets.UTF_8));
                        }

                        public ByteBuf getByteBuf(ChannelHandlerContext ctx) {
                            ByteBuf byteBuf = ctx.alloc().buffer();
                            System.out.println("<Host:>Active:>ByteBuf");

                            String SEQUENCE = "\r\n";
                            String packet = "POST / HTTP/1.1" + SEQUENCE + "VirtualRouter:" + head + SEQUENCE + "accept:*/*" + SEQUENCE + "connection:Keep-Alive" + SEQUENCE + "user-agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)" + SEQUENCE + SEQUENCE + body + SEQUENCE;

                            byte[] bytes = packet.getBytes(StandardCharsets.UTF_8);
                            byteBuf.writeBytes(bytes);
                            return byteBuf;
                        }
                    });
                }
            });


            int hostId = hostDao.lookupHostByName(head.split("->")[0]).getHostId();
            int routerId = hostRelationshipDao.lookupHostShipGetHostShipById(hostId).getRouterId();
            String[] addresses = routerDao.lookupRouterById(routerId).getRouterAddress().split(":");
            String host = addresses[0];
            int port = Integer.parseInt(addresses[1]);
            bootstrap.connect(host,port).addListener(future -> {
                if(future.isSuccess()) {
                    System.out.println("Connect success :)");
                } else {
                    System.err.println("Connect error please try again");
                }
            });
        } catch (Exception exception) {
            exception.printStackTrace();
            JSONArray jsonArray = JSONArray.fromObject(null);
            System.err.println(jsonArray.toString());
            return jsonArray.toString();
        }
        JSONArray jsonArray = JSONArray.fromObject(0);
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/startAll", method = RequestMethod.POST)
    @ResponseBody
    public String boardStartEvent() {
        try {
            Runtime.getRuntime().exec("other/virtual-start.sh");
            List<Router> routers = routerDao.lookupRouterGetRouters();
            for (Router router : routers) {
                redisTemplate.opsForValue().set(String.valueOf(router.getRouterId()),router.getRouterAddress());
                redisTemplate.expire(String.valueOf(router.getRouterId()),1L,TimeUnit.MINUTES);
                Runtime.getRuntime().exec("other/virtual-router-start.sh " + router.getRouterId());

                if (redisTemplate.hasKey(router.getRouterName())) {
                    redisTemplate.delete(router.getRouterName());
                }
                redisTemplate.opsForList().rightPush(router.getRouterName(),"start");
            }
        } catch (Exception exception) {
            exception.printStackTrace();
            JSONArray jsonArray = JSONArray.fromObject(null);
            System.err.println(jsonArray.toString());
            return jsonArray.toString();
        }

        JSONArray jsonArray = JSONArray.fromObject(routerDao.lookupRouterGetRouters());
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/closeAll", method = RequestMethod.POST)
    @ResponseBody
    public String boardEndEvent() {
        try {
            Runtime.getRuntime().exec("other/virtual-router-close.sh");
        } catch (Exception exception) {
            exception.printStackTrace();
            JSONArray jsonArray = JSONArray.fromObject(null);
            System.err.println(jsonArray.toString());
            return jsonArray.toString();
        }

        JSONArray jsonArray = JSONArray.fromObject(0);
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }

    @RequestMapping(value = "/router", method = RequestMethod.POST)
    @ResponseBody
    public String boardRouterEvent(@RequestParam String router) {
        JSONArray jsonArray = JSONArray.fromObject(relationshipService.getRouterMessages(router));
        System.err.println(jsonArray.toString());
        return jsonArray.toString();
    }
}
