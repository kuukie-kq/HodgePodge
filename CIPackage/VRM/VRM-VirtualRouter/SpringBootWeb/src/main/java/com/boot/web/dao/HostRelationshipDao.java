package com.boot.web.dao;

import com.boot.web.bean.HostRelationship;

import java.util.List;

public interface HostRelationshipDao {
    List<HostRelationship> lookupHostShipGetHostShips();
    int lookupHostShipGetHostShipsNumber();
    List<HostRelationship> lookupHostShipGetHostShipsByLimit(int page);
    HostRelationship lookupHostShipGetHostShipById(int id);
    boolean lookHostShipByRouterAndHostId(int hostId, int routerId);
}
