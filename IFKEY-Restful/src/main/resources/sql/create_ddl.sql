CREATE TABLE `EMI_AUTH` (
  `CALLING_ID` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `SYS_TITLE` varchar(64) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `NAS_IP` varchar(128) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `NAS_PORT` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `FEP_KEY` varchar(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  `NMS_KEY` varchar(128) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `CREATE_DT` varchar(14) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `MODIFY_DT` varchar(14) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`CALLING_ID`),
  UNIQUE KEY `UK_EMI_AUTH_01` (`CALLING_ID`,`SYS_TITLE`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
