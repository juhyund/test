<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html>

<html class="gr__webapplayers_com">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<title><%=PAGE_TITLE%></title>
<link href="<%=COMMON_PATH_JS%>/bootstrap.min.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/font-awesome.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/style.css" rel="stylesheet">

<!-- Mainly scripts -->
<script src="<%=COMMON_PATH_JS%>/jquery-3.1.1.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/popper.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/bootstrap.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.metisMenu.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.slimscroll.min.js"></script>

<!-- Custom and plugin javascript -->
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>

<body>
<!--  wrapper -->
<sec:authentication var="principal" property="principal" />
<div id="wrapper">
<nav class="navbar-default navbar-static-side" role="navigation" >
<%@ include file="menu.jsp"%>
</nav>
<!--  page-wrapper -->
<div id="page-wrapper" class="gray-bg dashbard-1" >
<div class="row border-bottom white-bg">

<nav class="navbar navbar-static-top" role="navigation" style="margin-bottom: 0">
<div class="navbar-header" style="width:250px">
<a class="navbar-minimalize minimalize-styl-2 btn btn-primary" href="#"><i class="fa fa-angle-double-left"></i> </a>
<div style="padding:20px;width:300px">
	<span class="m-r-sm text-muted welcome-message" style="font-weight: 700"> <strong>Welcome to KEPCO Web</strong></span>
</div>
</div>
<ul class="nav navbar-top-links navbar-right" style="margin-right:5px;">
	<li class="dropdown" >
	<a class="dropdown-toggle" data-toggle="dropdown" href="#" style="padding:10px">
	<img alt="image" class="user_img" src="<%=COMMON_PATH%>/images/myphoto_default.gif">&nbsp;${principal.user_name}(${principal.username}) 반갑습니다.
	</a>
	<ul class="dropdown-menu dropdown-messages" >
		<li>
		    <div class="dropdown-messages-box">
			<a class="dropdown-item float-left" href="http://webapplayers.com/inspinia_admin-v2.9.2/profile.html">
			<img alt="image" class="rounded-circle" src="<%=COMMON_PATH%>/images/myphoto_default.gif">
			</a>
		    <div>
		    	
			    <strong>${principal.user_name}(${principal.username})</strong><br>
			    ${principal.user_email}
			     <br>
			    <button class="btn btn-sm btn-primary m-t-n-xs" style="margin-top:5px;" onClick="location.href='<%=COMMON_URL%>/logout'">로그아웃</button>
			    </div>
			</div>
		</li>
	</ul>
	</li>
</ul>
</nav>
</div>
<!-- body -->
<div id="contents" >
<iframe src="<%=COMMON_URL%>/main" frameborder="0" name="contentsFrame" id="contentsFrame" style="min-width:1022px;width:100%; min-height:800px;" scrolling="yes"></iframe>
</div>
<!-- body -->
<!-- footer -->
<div class="footer">
	<div>
		<strong>Copyright</strong> NuriTelecom.com ©2020
	</div>
</div>
<!-- footer -->
</div>
	
</div>

<!--  page-wrapper -->
<!--  wrapper -->
</body></html>
