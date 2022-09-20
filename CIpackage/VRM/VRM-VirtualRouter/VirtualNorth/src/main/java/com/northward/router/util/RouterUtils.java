package com.northward.router.util;

import com.northward.router.dao.HostDao;
import com.northward.router.dao.RouterDao;
import com.northward.router.dao.RouterTableDao;

import java.nio.charset.Charset;

public class RouterUtils {
    public static final String VR = "VirtualRouter";
    public static final String RT = "RouterTable";
    public static Charset charset = Charset.forName("utf-8");
    public static final String SEQUENCE = "\r\n";
    public static final String SEPLUS = "\r\n>\r\n<\r\n";
    public static final String FORWARD = "<Forward>";
    public static final String UPDATE = "<Update>";
    public static final String CONNECT = "<Connect>";
    public static final String LAZE = "<Laze>";
    public static final String DNS = "<DnsSouth>";
    public static final String EDGE = "<EdgeGateway>";

    public static HostDao hostDao = new HostDao();
    public static RouterDao routerDao = new RouterDao();
    public static RouterTableDao routerTableDao = new RouterTableDao();
}
