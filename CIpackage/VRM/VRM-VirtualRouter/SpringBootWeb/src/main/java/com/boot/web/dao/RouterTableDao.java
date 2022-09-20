package com.boot.web.dao;

import com.boot.web.bean.RouterTable;

import java.util.List;

public interface RouterTableDao {
    List<RouterTable> lookupRouterTableGetRouterTables();
    List<RouterTable> lookupRouterTableById(int routerId);
    RouterTable lookupRouterTableByIdAndName(int routerId,String reachableAddressName);
    void lookRouterTable(RouterTable routerTable);
    void lookRouterTableByDistance(int distance,int tableId);
    void lookRouterTableByDistanceAndNext(int distance,String nextAddressName,int tableId);
}
