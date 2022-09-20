package com.boot.web.dao.impl;

import com.boot.web.bean.Host;
import com.boot.web.bean.Router;
import com.boot.web.dao.RouterDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@Repository
public class RouterDaoImpl implements RouterDao {
    @Autowired
    JdbcTemplate jdbcTemplate;

    @Override
    public List<Router> lookupRouterGetRouters() {
        List<Router> routers = new ArrayList<>();
        String sql = "select * from db_router";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql);
        for (Map<String,Object> map : maps) {
            Router router = new Router();
            router.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            router.setRouterName(map.get("routerName").toString());
            router.setRouterAddress(map.get("routerAddress").toString());
            routers.add(router);
        }
        return routers;
    }

    @Override
    public List<Router> lookupRouterGetRoutersByLimit(int page) {
        List<Router> routers = new ArrayList<>();
        String sql = "select * from db_router limit ?,?";
        int start = page * 5;
        int end = (page + 1) * 5;

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql,start,end);
        for (Map<String,Object> map : maps) {
            Router router = new Router();
            router.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            router.setRouterName(map.get("routerName").toString());
            router.setRouterAddress(map.get("routerAddress").toString());
            routers.add(router);
        }
        return routers;
    }

    @Override
    public Router lookupRouterById(int id) {
        Router router = new Router();
        String sql = "select * from db_router where routerId=?";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql,id);
        for (Map<String,Object> map : maps) {
            router.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            router.setRouterName(map.get("routerName").toString());
            router.setRouterAddress(map.get("routerAddress").toString());
        }
        return router;
    }

    @Override
    public Router lookupRouterByName(String name) {
        Router router = new Router();
        String sql = "select * from db_router where routerName=?";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql,name);
        for (Map<String,Object> map : maps) {
            router.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            router.setRouterName(map.get("routerName").toString());
            router.setRouterAddress(map.get("routerAddress").toString());
        }
        return router;
    }

    @Override
    public int lookupRouterGetRoutersNumber() {
        String sql = "select count(*) from db_router";
        return jdbcTemplate.queryForObject(sql,Integer.class);
    }

    @Override
    public boolean lookRouter(Router router) {
        String sql = "insert into db_router values(?,?,?)";
        jdbcTemplate.update(sql,router.getRouterId(),router.getRouterName(),router.getRouterAddress());
        return true;
    }
}
