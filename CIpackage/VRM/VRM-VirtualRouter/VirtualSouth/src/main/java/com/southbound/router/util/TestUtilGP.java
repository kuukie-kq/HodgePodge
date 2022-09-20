package com.southbound.router.util;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.URL;
import java.net.URLConnection;
import java.util.List;
import java.util.Map;

public class TestUtilGP {
    public static String send(String host,String port,String request) throws Exception {
        String result = null;
        URL url = new URL("https://" + host + "/");
        URLConnection connection = url.openConnection();

        connection.setRequestProperty("accept", "*/*");
        connection.setRequestProperty("connection", "Keep-Alive");
        connection.setRequestProperty("user-agent", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)");

        connection.setDoOutput(true);
        connection.setDoInput(true);
        connection.connect();

        int length = request.split(RouterUtils.SEQUENCE+RouterUtils.SEQUENCE).length;
        String data = null;
        if(length == 2) {
            data = request.split(RouterUtils.SEQUENCE+RouterUtils.SEQUENCE)[1];
        }

        PrintWriter out = new PrintWriter(connection.getOutputStream());
        out.print(data);
        out.flush();

        Map<String,List<String>> map = connection.getHeaderFields();
        result = map.get(null) + RouterUtils.SEQUENCE;
        for(String key:map.keySet()) {
            if(key == null) {
                continue;
            } else {
                result = result + map.get(key) + RouterUtils.SEQUENCE;
            }
        }
        result = result + "VirtualRouter:" + host + "->" + port + RouterUtils.SEQUENCE;
        result = result + RouterUtils.SEQUENCE;
        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        for(String line;(line=in.readLine())!=null;) {
            result = result + line + RouterUtils.SEQUENCE;
        }
        return result;
    }
}
