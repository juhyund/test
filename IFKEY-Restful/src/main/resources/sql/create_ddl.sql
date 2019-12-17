CREATE TABLE `tauthorize` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `access_right` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `attribute_name` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `attribute_No` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `class_Id` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `class_Name` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `dataType` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `descr` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `devicemodel_id` int(11) DEFAULT NULL,
  `OBIS_CODE` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_OBISCODE_01` (`OBIS_CODE`,`class_Id`,`attribute_No`,`devicemodel_id`),
  KEY `FK_OBISCODE_devicemodel_id` (`devicemodel_id`),
  CONSTRAINT `FK_OBISCODE_devicemodel_id` FOREIGN KEY (`devicemodel_id`) REFERENCES `devicemodel` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
