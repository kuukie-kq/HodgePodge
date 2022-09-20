package com.northward.router.dao;

import com.northward.router.bean.Router;
import com.northward.router.util.MysqlConnectUtils;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class RouterDao{
    public List<Router> lookupRouterGetRouters() {
        List<Router> routers = new ArrayList();
        String sql = "select * from db_router";
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                Router router = new Router();
                router.setRouterId(rs.getInt(1));
                router.setRouterName(rs.getString(2));
                router.setRouterAddress(rs.getString(3));
                routers.add(router);
            }
            MysqlConnectUtils.mysqlClose();
            return routers;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public List<Router> lookupRouterGetRoutersByLimit(int page) {
        List<Router> routers = new ArrayList();
        String sql = "select * from db_router limit " + page*5 + "," + (page+1)*5;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                Router router = new Router();
                router.setRouterId(rs.getInt(1));
                router.setRouterName(rs.getString(2));
                router.setRouterAddress(rs.getString(3));
                routers.add(router);
            }
            MysqlConnectUtils.mysqlClose();
            return routers;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public Router lookupRouterById(int id) {
        Router router = new Router();
        String sql = "select * from db_router where routerId=" + id;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                router.setRouterId(rs.getInt(1));
                router.setRouterName(rs.getString(2));
                router.setRouterAddress(rs.getString(3));
            }
            MysqlConnectUtils.mysqlClose();
            return router;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public Router lookupRouterByName(String name) {
        Router router = new Router();
        String sql = "select * from db_router where routerName='" + name + "'";
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                router.setRouterId(rs.getInt(1));
                router.setRouterName(rs.getString(2));
                router.setRouterAddress(rs.getString(3));
            }
            MysqlConnectUtils.mysqlClose();
            return router;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public int lookupRouterGetRoutersNumber() {
        List<Router> routers = new ArrayList();
        String sql = "select * from db_router";
        int i = 0;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();i++) {
                Router router = new Router();
                router.setRouterId(rs.getInt(1));
                router.setRouterName(rs.getString(2));
                router.setRouterAddress(rs.getString(3));
                routers.add(router);
            }
            MysqlConnectUtils.mysqlClose();
            return i;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    public boolean lookRouter(Router router) {
        String sql = "insert into db_router values(" + router.getRouterId() + ",'" + router.getRouterName() + "','" + router.getRouterAddress() + "')";
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
