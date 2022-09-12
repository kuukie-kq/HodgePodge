package com.boot.web.service.impl;

import com.boot.web.bean.Router;
import com.boot.web.bean.RouterRelationship;
import com.boot.web.bean.data.Message;
import com.boot.web.bean.data.Relationship;
import com.boot.web.bean.data.RouterShip;
import com.boot.web.dao.RouterDao;
import com.boot.web.dao.RouterRelationshipDao;
import com.boot.web.dao.RouterTableDao;
import com.boot.web.service.RelationshipService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.BoundListOperations;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class RelationshipServiceImpl implements RelationshipService {
    @Autowired
    RouterDao routerDao;
    @Autowired
    RouterRelationshipDao routerRelationshipDao;
    @Autowired
    RouterTableDao routerTableDao;
    @Autowired
    RedisTemplate redisTemplate;

    @Override
    public RouterShip getRouterShip() {
        List<Router> routers = routerDao.lookupRouterGetRouters();
        List<Relationship> ships = new ArrayList<>();
        for (RouterRelationship relationship:routerRelationshipDao.lookupRouterShipGetRouterShips()) {
            Relationship ship = new Relationship();
            ship.setFromNode(routerDao.lookupRouterById(relationship.getRouterIdFrom()).getRouterName());
            ship.setToNode(routerDao.lookupRouterById(relationship.getRouterIdTo()).getRouterName());
            ships.add(ship);
        }
        return new RouterShip(routers,ships);
    }

    @Override
    public RouterShip autoFoundRouterShip() {
        return null;
    }

    @Override
    public List<Message> getRouterMessages(String key) {
        List<Message> messages = new ArrayList<>();
        BoundListOperations<String,String> boundListOperations = redisTemplate.boundListOps(key);
        List<String> range = boundListOperations.range(0, -1);
        int i=1;
        for (String o : range) {
            messages.add(new Message(i++,o));
        }
        return messages;
    }
}
