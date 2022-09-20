package com.boot.web.service.impl;

import com.boot.web.bean.Router;
import com.boot.web.bean.data.RouterMessage;
import com.boot.web.dao.RouterDao;
import com.boot.web.service.RouterService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class RouterServiceImpl implements RouterService {
    @Autowired
    RouterDao routerDao;

    @Override
    public RouterMessage getMessage() {
        List<Router> routers = routerDao.lookupRouterGetRoutersByLimit(0);
        int hostCount = routerDao.lookupRouterGetRoutersNumber();
        int pageCount = hostCount / 5;
        return new RouterMessage(pageCount,5,1,hostCount,routers);
    }

    @Override
    public RouterMessage getMessageByLimit(int page) {
        List<Router> routers = routerDao.lookupRouterGetRoutersByLimit(page);
        return new RouterMessage(0,5,page+1,0,routers);
    }

    @Override
    public boolean setNewRouter(int routerId, String routerName, String routerAddress) {
        Router router = new Router(routerId,routerName,routerAddress);
        return routerDao.lookRouter(router);
    }
}
