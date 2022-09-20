package com.northward.router.dao;

import com.northward.router.bean.RouterTable;
import com.northward.router.util.MysqlConnectUtils;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class RouterTableDao {
    public List<RouterTable> lookupRouterTableGetRouterTables() {
        /**
         * 获取所有的转发表信息
         * 用于测试
         */
        List<RouterTable> routerTables = new ArrayList();
        String sql = "select * from db_router_table";
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                RouterTable routerTable = new RouterTable();
                routerTable.setTableId(rs.getInt(1));
                routerTable.setTableName(rs.getString(2));
                routerTable.setRouterId(rs.getInt(3));
                routerTable.setReachableAddressName(rs.getString(4));
                routerTable.setReachableDistance(rs.getInt(5));
                routerTable.setNextAddressName(rs.getString(6));
                routerTables.add(routerTable);
            }
            MysqlConnectUtils.mysqlClose();
            return routerTables;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public List<RouterTable> lookupRouterTableById(int routerId) {
        /**
         * 获取所有的转发表信息
         * 用于测试
         */
        List<RouterTable> routerTables = new ArrayList();
        String sql = "select * from db_router_table where routerId="+routerId;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                RouterTable routerTable = new RouterTable();
                routerTable.setTableId(rs.getInt(1));
                routerTable.setTableName(rs.getString(2));
                routerTable.setRouterId(rs.getInt(3));
                routerTable.setReachableAddressName(rs.getString(4));
                routerTable.setReachableDistance(rs.getInt(5));
                routerTable.setNextAddressName(rs.getString(6));
                routerTables.add(routerTable);
            }
            MysqlConnectUtils.mysqlClose();
            return routerTables;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public RouterTable lookupRouterTableByIdAndName(int routerId,String reachableAddressName) {
        /**
         * 通过路由器和目标地址查找某一条数据
         * 用于路由表更新时对比更新数据
         */
        RouterTable routerTable = new RouterTable();
        String sql = "select * from db_router_table where routerId=" + routerId +
                " and reachableAddressName='" + reachableAddressName + "'";
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(sql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                routerTable.setTableId(rs.getInt(1));
                routerTable.setTableName(rs.getString(2));
                routerTable.setRouterId(rs.getInt(3));
                routerTable.setReachableAddressName(rs.getString(4));
                routerTable.setReachableDistance(rs.getInt(5));
                routerTable.setNextAddressName(rs.getString(6));
            }
            MysqlConnectUtils.mysqlClose();
            return routerTable;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public void lookRouterTable(RouterTable routerTable) {
        /**
         * 插入一条新的路由表信息
         * 用于在没有目标地址时,更新路由表
         */
        String prepareSql = "select count(*) as count from db_router_table";
        int number = -1;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlSelect(prepareSql);
            ResultSet rs = MysqlConnectUtils.getRs();
            for(;rs.next();) {
                number = rs.getInt("count");
            }
        number++;
        String sql = "insert into db_router_table values(" + number +
                ",'" + routerTable.getTableName() +"'," + routerTable.getRouterId() +
                ",'" + routerTable.getReachableAddressName() + "'," +
                routerTable.getReachableDistance() + ",'" + routerTable.getNextAddressName() + "')";

            MysqlConnectUtils.mysqlUpdate(sql);
            MysqlConnectUtils.mysqlClose();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void lookRouterTableByDistance(int distance,int tableId) {
        /**
         * 通过距离和主键更新本条路由表内容
         * 用于在得到相同的下一跳时,直接替换距离
         */
        String sql = "update db_router_table set reachableDistance=" + distance +
                " where tableId=" + tableId;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlUpdate(sql);
            MysqlConnectUtils.mysqlClose();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void lookRouterTableByDistanceAndNext(int distance,String nextAddressName,int tableId) {
        /**
         * 通过距离与下一跳和主键更新本条路由表内容
         * 用于在得到不同的下一跳时,替换距离和下一跳
         */
        String sql = "update db_router_table set reachableDistance=" + distance +
                ",nextAddressName='" + nextAddressName + "' where tableId=" + tableId;
        try {
            MysqlConnectUtils.mysqlInit();
            MysqlConnectUtils.mysqlUpdate(sql);
            MysqlConnectUtils.mysqlClose();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
