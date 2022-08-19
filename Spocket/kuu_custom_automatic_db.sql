##Navicat Premium Data Transfer
##
## Source Server         : wsl_mysql_tmp
## Source Server Type    : MySQL
## Source Server Version : 80030
## Source Host           : 172.16.192.2:3306
## Source Schema         : kuu_custom_automatic_db
##
## Target Server Type    : MySQL
## Target Server Version : 80030
## File Encoding         : 65001
##
## Date: 2022-08-12 10:42:06

##The start
##This is added manually.
## It is used to ensure the consistency of the library name.
DROP DATABASE IF EXISTS `kuu_custom_automatic_db`;
CREATE DATABASE `kuu_custom_automatic_db`;
USE `kuu_custom_automatic_db`;
##You are also use the next way
# CREATE DATABASE IF NOT EXISTS `kuu_custom_automatic_db`;
# USE `kuu_custom_automatic_db`;
##The end

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

## ----------------------------
## Table structure for db_base_user
## ----------------------------
DROP TABLE IF EXISTS `db_base_user`;
CREATE TABLE `db_base_user`  (
  `dbu_id` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `dbu_name` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `dbu_password` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `dbu_pid` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`dbu_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

## ----------------------------
## Table structure for db_base_menu
## ----------------------------
DROP TABLE IF EXISTS `db_base_menu`;
CREATE TABLE `db_base_menu`  (
  `dbm_reminder` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `dbm_link` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `dbm_pid` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`dbm_reminder`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

## ----------------------------
## Table structure for db_base_view
## ----------------------------
DROP TABLE IF EXISTS `db_base_view`;
CREATE TABLE `db_base_view`  (
  `dbv_reminder` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `dbv_message` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `dbv_mode` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`dbv_reminder`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
