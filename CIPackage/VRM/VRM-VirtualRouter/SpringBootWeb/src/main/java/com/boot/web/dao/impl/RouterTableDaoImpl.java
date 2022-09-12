package com.boot.web.dao.impl;

import com.boot.web.bean.RouterTable;
import com.boot.web.dao.RouterTableDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@Repository
public class RouterTableDaoImpl implements RouterTableDao {
    @Autowired
    JdbcTemplate jdbcTemplate;

    @Override
    public List<RouterTable> lookupRouterTableGetRouterTables() {
        List<RouterTable> routerTables = new ArrayList<>();
        String sql = "select * from db_router_table";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql);
        for (Map<String,Object> map : maps) {
            RouterTable routerTable = new RouterTable();
            routerTable.setTableId(Integer.parseInt(map.get("tableId").toString()));
            routerTable.setTableName(map.get("tableName").toString());
            routerTable.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            routerTable.setReachableAddressName(map.get("reachableAddressName").toString());
            routerTable.setReachableDistance(Integer.parseInt(map.get("reachableDistance").toString()));
            routerTable.setNextAddressName(map.get("nextAddressName").toString());
            routerTables.add(routerTable);
        }
        return routerTables;
    }

    @Override
    public List<RouterTable> lookupRouterTableById(int routerId) {
        List<RouterTable> routerTables = new ArrayList<>();
        String sql = "select * from db_router_table where routerId=?";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql,routerId);
        for (Map<String,Object> map : maps) {
            RouterTable routerTable = new RouterTable();
            routerTable.setTableId(Integer.parseInt(map.get("tableId").toString()));
            routerTable.setTableName(map.get("tableName").toString());
            routerTable.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            routerTable.setReachableAddressName(map.get("reachableAddressName").toString());
            routerTable.setReachableDistance(Integer.parseInt(map.get("reachableDistance").toString()));
            routerTable.setNextAddressName(map.get("nextAddressName").toString());
            routerTables.add(routerTable);
        }
        return routerTables;
    }

    @Override
    public RouterTable lookupRouterTableByIdAndName(int routerId, String reachableAddressName) {
        RouterTable routerTable = new RouterTable();
        String sql = "select * from db_router_table where routerId=? and reachableAddressName=?";

        List<Map<String, Object>> maps = jdbcTemplate.queryForList(sql,routerId,reachableAddressName);
        for (Map<String,Object> map : maps) {
            routerTable.setTableId(Integer.parseInt(map.get("tableId").toString()));
            routerTable.setTableName(map.get("tableName").toString());
            routerTable.setRouterId(Integer.parseInt(map.get("routerId").toString()));
            routerTable.setReachableAddressName(map.get("reachableAddressName").toString());
            routerTable.setReachableDistance(Integer.parseInt(map.get("reachableDistance").toString()));
            routerTable.setNextAddressName(map.get("nextAddressName").toString());
        }
        return routerTable;
    }

    @Override
    public void lookRouterTable(RouterTable routerTable) {
        int id = jdbcTemplate.queryForObject("select count(*) from db_router_table", Integer.class);
        String sql = "insert into db_router_table values(?,?,?,?,?,?)";
        jdbcTemplate.update(sql,
                id+1,
                routerTable.getTableName(),
                routerTable.getRouterId(),
                routerTable.getReachableAddressName(),
                routerTable.getReachableDistance(),
                routerTable.getNextAddressName());
    }

    @Override
    public void lookRouterTableByDistance(int distance, int tableId) {
        String sql = "update db_router_table set reachableDistance=? where tableId=?";
        jdbcTemplate.update(sql,distance,tableId);
    }

    @Override
    public void lookRouterTableByDistanceAndNext(int distance, String nextAddressName, int tableId) {
        String sql = "update db_router_table set reachableDistance=?,nextAddressName=? where tableId=?";
        jdbcTemplate.update(sql,distance,nextAddressName,tableId);
    }
}
