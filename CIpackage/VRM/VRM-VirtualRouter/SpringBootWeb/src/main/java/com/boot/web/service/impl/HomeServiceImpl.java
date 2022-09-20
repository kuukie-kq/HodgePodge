package com.boot.web.service.impl;

import com.boot.web.bean.data.HeadMessage;
import com.boot.web.bean.HostRelationship;
import com.boot.web.dao.HostDao;
import com.boot.web.dao.HostRelationshipDao;
import com.boot.web.dao.RouterDao;
import com.boot.web.service.HomeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class HomeServiceImpl implements HomeService {
    @Autowired
    HostDao hostDao;
    @Autowired
    RouterDao routerDao;
    @Autowired
    HostRelationshipDao hostRelationshipDao;

    @Override
    public HeadMessage getMessage() {
        int hostsNumber = hostDao.lookupHostGetHostsNumber();
        int routersNumber = routerDao.lookupRouterGetRoutersNumber();
        int countNumber = hostRelationshipDao.lookupHostShipGetHostShipsNumber();
        List<HostRelationship> hostRelationships = hostRelationshipDao.lookupHostShipGetHostShipsByLimit(0);

        return new HeadMessage(hostsNumber,routersNumber,5,countNumber/5,1,countNumber,hostRelationships);
    }

    @Override
    public HeadMessage getMessageByLimit(int page) {
        List<HostRelationship> hostRelationships = hostRelationshipDao.lookupHostShipGetHostShipsByLimit(page);
        return  new HeadMessage(0,0,0,0,page+1,0,hostRelationships);
    }
}
