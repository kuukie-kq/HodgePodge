package com.southbound.router.util;

import redis.clients.jedis.Jedis;

public class RedisUtils {
    private static Jedis jedis = new Jedis("127.0.0.1",3306);

    public static String routerAddress(int key) {
        return jedis.get(String.valueOf(key));
    }
}
