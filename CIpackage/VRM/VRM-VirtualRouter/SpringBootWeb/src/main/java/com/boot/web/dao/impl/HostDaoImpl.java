package com.boot.web.dao.impl;

import com.boot.web.bean.Host;
import com.boot.web.dao.HostDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@Repository
public class HostDaoImpl implements HostDao {
    @Autowired
    JdbcTemplate jdbcTemplate;

    @Override
    public List<Host> lookupHostGetHosts() {
        List<Host> hosts = new ArrayList();
        String sql = "select * from db_host";

        List<Map<String,Object>> maps = jdbcTemplate.queryForList(sql);
        for (Map<String,Object> map : maps) {
            Host host = new Host();
            host.setHostId(Integer.parseInt(map.get("hostId").toString()));
            host.setHostName(map.get("hostName").toString());
            host.setHostAddress(map.get("hostAddress").toString());
            hosts.add(host);
        }
        return hosts;
    }

    @Override
    public List<Host> lookupHostGetHostsByLimit(int page) {
        List<Host> hosts = new ArrayList();
        String sql = "select * from db_host limit ?,?";
        int start = page * 5;
        int end = (page + 1) * 5;

        List<Map<String,Object>> maps = jdbcTemplate.queryForList(sql,start,end);
        for (Map<String,Object> map : maps) {
            Host host = new Host();
            host.setHostId(Integer.parseInt(map.get("hostId").toString()));
            host.setHostName(map.get("hostName").toString());
            host.setHostAddress(map.get("hostAddress").toString());
            hosts.add(host);
        }
        return hosts;
    }

    @Override
    public Host lookupHostByName(String name) {
        Host host = new Host();
        String sql = "select * from db_host where hostName=?";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql, name);
        for (Map<String,Object> map : maps) {
            host.setHostId(Integer.parseInt(map.get("hostId").toString()));
            host.setHostName(map.get("hostName").toString());
            host.setHostAddress(map.get("hostAddress").toString());
        }
        return host;
    }

    @Override
    public int lookupHostGetHostsNumber() {
        String sql = "select count(*) from db_host";
        return jdbcTemplate.queryForObject(sql,Integer.class);
    }

    @Override
    public boolean lookHost(Host host) {
        String sql = "insert into db_host values(?,?,?)";
        jdbcTemplate.update(sql,host.getHostId(),host.getHostName(),host.getHostAddress());
        return true;
    }
}
