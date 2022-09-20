package com.southbound.router.dao;

import com.southbound.router.bean.Host;
import com.southbound.router.util.MysqlConnectUtils;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class HostDao {
    public List<Host> lookupHostGetHosts() {
        List<Host> hosts = new ArrayList();
        String sql = "select * from db_host";
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                Host host = new Host();
                host.setHostId(rs.getInt(1));
                host.setHostName(rs.getString(2));
                host.setHostAddress(rs.getString(3));
                hosts.add(host);
            }
            MysqlConnectUtils.mysqlClose();
            return hosts;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public List<Host> lookupHostGetHostsByLimit(int page) {
        List<Host> hosts = new ArrayList();
        String sql = "select * from db_host limit " + page*5 + "," + (page+1)*5;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                Host host = new Host();
                host.setHostId(rs.getInt(1));
                host.setHostName(rs.getString(2));
                host.setHostAddress(rs.getString(3));
                hosts.add(host);
            }
            MysqlConnectUtils.mysqlClose();
            return hosts;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public Host lookupHostByName(String name) {
        Host host = new Host();
        String sql = "select * from db_host where hostName='" + name + "'";
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                host.setHostId(rs.getInt(1));
                host.setHostName(rs.getString(2));
                host.setHostAddress(rs.getString(3));
            }
            MysqlConnectUtils.mysqlClose();
            return host;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public int lookupHostGetHostsNumber() {
        List<Host> hosts = new ArrayList();
        String sql = "select * from db_host";
        int i = 0;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();i++) {
                Host host = new Host();
                host.setHostId(rs.getInt(1));
                host.setHostName(rs.getString(2));
                host.setHostAddress(rs.getString(3));
                hosts.add(host);
            }
            MysqlConnectUtils.mysqlClose();
            return i;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    public boolean lookHost(Host host) {
        String sql = "insert into db_host values(" + host.getHostId() + ",'" + host.getHostName() + "','" + host.getHostAddress() + "')";
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlUpdate(sql);
            MysqlConnectUtils.mysqlClose();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}
