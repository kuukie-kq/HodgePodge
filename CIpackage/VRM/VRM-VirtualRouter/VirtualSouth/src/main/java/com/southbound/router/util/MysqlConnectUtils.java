package com.southbound.router.util;

import java.sql.*;

public class MysqlConnectUtils {
    public static final String DRIVER = "com.mysql.cj.jdbc.Driver";
    public static final String DB = "jdbc:mysql://localhost/virtual_router_db";
    public static final String USER = "root";
    public static final String PASSWORD = "root";
    public static Connection conn = null;
    public static Statement stmt = null;
    public static ResultSet rs = null;

    //建立MySQL连接
    public static void mysqlInit() throws Exception {
        Class.forName(DRIVER);
        //System.out.println("Connecting to a selected database...");
        conn= DriverManager.getConnection(DB,USER,PASSWORD);
        stmt=conn.createStatement();
    }

    //关闭MySQL连接
    public static void mysqlClose() throws SQLException {
        if(rs!=null)
            rs.close();
        if(stmt!=null)
            stmt.close();
        if(conn!=null)
            conn.close();
        //System.out.println("Closing the selected database...");
    }

    //添加
    public static void mysqlUpdate(String sql) {
        try {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    //查询
    public static void mysqlSelect(String sql) {
        try {
            rs=stmt.executeQuery(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    //返回结果
    public static ResultSet getRs() {
        return rs;
    }
}
