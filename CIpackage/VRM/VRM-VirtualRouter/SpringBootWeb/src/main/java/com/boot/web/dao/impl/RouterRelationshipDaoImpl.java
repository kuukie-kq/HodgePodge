package com.boot.web.dao.impl;

import com.boot.web.bean.HostRelationship;
import com.boot.web.bean.RouterRelationship;
import com.boot.web.dao.RouterRelationshipDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@Repository
public class RouterRelationshipDaoImpl implements RouterRelationshipDao {
    @Autowired
    JdbcTemplate jdbcTemplate;

    @Override
    public List<RouterRelationship> lookupRouterShipGetRouterShips() {
        List<RouterRelationship> relationships = new ArrayList<>();
        String sql = "select * from db_router_relationship";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql);
        for (Map<String,Object> map : maps) {
            RouterRelationship relationship = new RouterRelationship();
            relationship.setRouterShipId(Integer.parseInt(map.get("routerShipId").toString()));
            relationship.setRouterIdFrom(Integer.parseInt(map.get("routerIdFrom").toString()));
            relationship.setRouterIdTo(Integer.parseInt(map.get("routerIdTo").toString()));
            relationships.add(relationship);
        }
        return relationships;
    }
}
