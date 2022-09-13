package com.boot.web.service.impl;

import com.boot.web.bean.Host;
import com.boot.web.bean.HostRelationship;
import com.boot.web.bean.RouterTable;
import com.boot.web.bean.data.HostMessage;
import com.boot.web.dao.HostDao;
import com.boot.web.dao.HostRelationshipDao;
import com.boot.web.dao.RouterDao;
import com.boot.web.dao.RouterTableDao;
import com.boot.web.service.HostService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class HostServiceImpl implements HostService {
    @Autowired
    HostDao hostDao;
    @Autowired
    HostRelationshipDao hostRelationshipDao;
    @Autowired
    RouterDao routerDao;
    @Autowired
    RouterTableDao routerTableDao;

    @Override
    public HostMessage getMessage() {
        List<Host> hosts = hostDao.lookupHostGetHostsByLimit(0);
        int hostCount = hostDao.lookupHostGetHostsNumber();
        int pageCount = hostCount / 5;
        List<HostRelationship> hostRelationships = hostRelationshipDao.lookupHostShipGetHostShipsByLimit(0);
        return new HostMessage(pageCount,5,1,hostCount,hosts,hostRelationships);
    }

    @Override
    public HostMessage getMessageByLimit(int page) {
        List<Host> hosts = hostDao.lookupHostGetHostsByLimit(page);
        List<HostRelationship> hostRelationships = hostRelationshipDao.lookupHostShipGetHostShipsByLimit(page);
        return new HostMessage(0,0,page+1,0,hosts,hostRelationships);
    }

    @Override
    public boolean setNewHostAndShip(int hostId, String hostName, String hostAddress, int routerId) {
        Host host = new Host(hostId,hostName,hostAddress);
        if (hostDao.lookHost(host)) {
            RouterTable routerTable = new RouterTable();
            routerTable.setTableName(routerDao.lookupRouterById(routerId).getRouterName() + "To" + hostName);
            routerTable.setRouterId(routerId);
            routerTable.setReachableAddressName(hostName);
            routerTable.setReachableDistance(0);
            routerTable.setNextAddressName(hostName);
            routerTableDao.lookRouterTable(routerTable);
            return hostRelationshipDao.lookHostShipByRouterAndHostId(hostId,routerId);
        } else {
            return false;
        }
    }
}
