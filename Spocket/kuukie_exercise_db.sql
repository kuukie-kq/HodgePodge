/*
 Navicat Premium Data Transfer

 Source Server         : bigdatacase_conn
 Source Server Type    : MySQL
 Source Server Version : 50711
 Source Host           : localhost:3306
 Source Schema         : kuukie_exercise_db

 Target Server Type    : MySQL
 Target Server Version : 50711
 File Encoding         : 65001

 Date: 21/09/2021 16:50:16
*/

#The start
#This is added manually.
#It is used to ensure the consistency of the library name.
DROP DATABASE IF EXISTS `kuukie_exercise_db`;
CREATE DATABASE `kuukie_exercise_db`;
USE `kuukie_exercise_db`;
#The end

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

# Table structure for db_demo
DROP TABLE IF EXISTS `db_demo`;
CREATE TABLE `db_demo`  (
  `idD` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `nameD` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `ageD` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `pidD` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`idD`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
