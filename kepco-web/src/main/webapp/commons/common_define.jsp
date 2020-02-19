<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<%
	String CONTEXT_PATH = request.getContextPath();
	String COMMON_HOST = "http://127.0.0.1";
	String COMMON_URL = CONTEXT_PATH;
	
	String COMMON_PATH = COMMON_URL + "/commons";
	String COMMON_PATH_JS = COMMON_PATH + "/js";
	String COMMON_PATH_IMG =  COMMON_PATH + "/images";
	String COMMON_PATH_CSS =  COMMON_PATH + "/css";
	
	String BASE_PATH = "";
	String WEBROOT_PATH = BASE_PATH + "/WebRoot";
	String WEBINF_PATH = WEBROOT_PATH + "/WEB-INF";
	String SAVE_PATH = WEBROOT_PATH + "/files";
	
	String PAGE_TITLE = "eWSN SOC 실증 시스템";	
%>