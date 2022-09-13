package com.boot.web.dao;

import com.boot.web.bean.Host;

import java.util.List;

public interface HostDao {
    List<Host> lookupHostGetHosts();
    List<Host> lookupHostGetHostsByLimit(int page);
    Host lookupHostByName(String name);
    int lookupHostGetHostsNumber();
    boolean lookHost(Host host);
}
