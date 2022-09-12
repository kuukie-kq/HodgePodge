-- MySQL dump 10.13  Distrib 8.0.26, for Linux (x86_64)
--
-- Host: localhost    Database: virtual_router_db
-- ------------------------------------------------------
-- Server version	8.0.26-0ubuntu0.20.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `db_host`
--

/*The start*/
/*This is added manually.*/
/*It is used to ensure the consistency of the library name.*/
DROP DATABASE IF EXISTS `virtual_router_db`;
CREATE DATABASE `virtual_router_db`;
USE `virtual_router_db`;
/*The end*/

DROP TABLE IF EXISTS `db_host`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `db_host` (
  `hostId` int NOT NULL,
  `hostName` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `hostAddress` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`hostId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_host`
--

LOCK TABLES `db_host` WRITE;
/*!40000 ALTER TABLE `db_host` DISABLE KEYS */;
INSERT INTO `db_host` VALUES (1,'HostOne','127.0.0.1:55131'),(2,'HostTwo','127.0.0.1:55132'),(3,'HostThree','127.0.0.1:55133'),(4,'HostFour','127.0.0.1:55134');
/*!40000 ALTER TABLE `db_host` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `db_host_relationship`
--

DROP TABLE IF EXISTS `db_host_relationship`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `db_host_relationship` (
  `hostShipId` int NOT NULL,
  `hostId` int NOT NULL,
  `routerId` int NOT NULL,
  PRIMARY KEY (`hostShipId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_host_relationship`
--

LOCK TABLES `db_host_relationship` WRITE;
/*!40000 ALTER TABLE `db_host_relationship` DISABLE KEYS */;
INSERT INTO `db_host_relationship` VALUES (1,1,1),(2,2,2),(3,3,3),(4,4,4);
/*!40000 ALTER TABLE `db_host_relationship` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `db_router`
--

DROP TABLE IF EXISTS `db_router`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `db_router` (
  `routerId` int NOT NULL,
  `routerName` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `routerAddress` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`routerId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_router`
--

LOCK TABLES `db_router` WRITE;
/*!40000 ALTER TABLE `db_router` DISABLE KEYS */;
INSERT INTO `db_router` VALUES (1,'RouterOne','127.0.0.1:55031'),(2,'RouterTwo','127.0.0.1:55032'),(3,'RouterThree','127.0.0.1:55033'),(4,'RouterFour','127.0.0.1:55034');
/*!40000 ALTER TABLE `db_router` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `db_router_relationship`
--

DROP TABLE IF EXISTS `db_router_relationship`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `db_router_relationship` (
  `routerShipId` int NOT NULL,
  `routerIdFrom` int NOT NULL,
  `routerIdTo` int NOT NULL,
  PRIMARY KEY (`routerShipId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_router_relationship`
--

LOCK TABLES `db_router_relationship` WRITE;
/*!40000 ALTER TABLE `db_router_relationship` DISABLE KEYS */;
INSERT INTO `db_router_relationship` VALUES (1,1,2),(2,2,3),(3,2,4);
/*!40000 ALTER TABLE `db_router_relationship` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `db_router_table`
--

DROP TABLE IF EXISTS `db_router_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `db_router_table` (
  `tableId` int NOT NULL,
  `tableName` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `routerId` int NOT NULL,
  `reachableAddressName` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `reachableDistance` int NOT NULL,
  `nextAddressName` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`tableId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `db_router_table`
--

LOCK TABLES `db_router_table` WRITE;
/*!40000 ALTER TABLE `db_router_table` DISABLE KEYS */;
INSERT INTO `db_router_table` VALUES (1,'RouterOneToHostOne',1,'HostOne',0,'HostOne'),(2,'RouterOneToHostTwo',1,'HostTwo',1,'RouterTwo'),(3,'RouterOneToHostThree',1,'HostThree',2,'RouterTwo'),(4,'RouterOneToHostFour',1,'HostFour',2,'RouterTwo'),(5,'RouterTwoToHostOne',2,'HostOne',1,'RouterOne'),(6,'RouterTwoToHostTwo',2,'HostTwo',0,'HostTwo'),(7,'RouterTwoToHostThree',2,'HostThree',1,'RouterThree'),(8,'RouterTwoToHostFour',2,'HostFour',1,'RouterFour'),(9,'RouterThreeToHostOne',3,'HostOne',2,'RouterTwo'),(10,'RouterThreeToHostTwo',3,'HostTwo',1,'RouterTwo'),(11,'RouterThreeToHostThree',3,'HostThree',0,'HostThree'),(12,'RouterThreeToHostFour',3,'HostFour',2,'RouterTwo'),(13,'RouterFourToHostOne',4,'HostOne',2,'RouterTwo'),(14,'RouterFourToHostTwo',4,'HostTwo',1,'RouterTwo'),(15,'RouterFourToHostThree',4,'HostThree',2,'RouterTwo'),(16,'RouterFourToHostFour',4,'HostFour',0,'HostFour');
/*!40000 ALTER TABLE `db_router_table` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-08-17 22:34:12
