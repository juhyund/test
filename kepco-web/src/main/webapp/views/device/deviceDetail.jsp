<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<%
	String device_id = request.getParameter("device_id");
%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<title><%=PAGE_TITLE%></title>
<link href="<%=COMMON_PATH_JS%>/bootstrap.min.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/datepicker3.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/font-awesome.css" rel="stylesheet">

<!-- Mainly scripts -->
<script src="<%=COMMON_PATH_JS%>/jquery-3.1.1.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/popper.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/bootstrap.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.metisMenu.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.slimscroll.min.js"></script>

<!-- angular -->
<script src="<%=COMMON_PATH_JS%>/angular.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/angular-route.min.js"></script>

<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js"
	charset="UTF-8"></script>

<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
</head>
<body ng-app="deviceApp">
	<!--  wrapper -->
	<div id="content" ng-controller="deviceCtrl">
		<div id="wrapper">
			<div id="page-wrapper" style="width: 100%" class="gray-bg">
				<!-- navigator -->
				<div class="row wrapper page-heading" style="padding: 5px">
					<div class="col-lg-10">
						<h3 style="margin-top: 6px">단말 관리</h3>
					</div>
					<div class="col-lg-2">
						<ol class="breadcrumb" style="float: right; margin-top: 10px;">
							<li class="breadcrumb-item"><a href="#">Home</a></li>
							<li class="breadcrumb-item active"><strong>단말정보 상세</strong>
							</li>
						</ol>
					</div>
				</div>
				<!-- navigator -->
				<div class="row">
					<ul class="nav nav-tabs">
						<li class="nav-item"><a class="nav-link active"
							data-toggle="tab" href="#info">기본정보</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#object">오브젝트 정보</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#zxc">연결미터</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#zxc">Observe 상태</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#zxc">제어이력</a></li>
					</ul>
				</div>
				<!-- navigator -->

				<!-- body -->
				<form name="search_form" id="search_form" method="post">
					<input type=hidden name="device_id" id="device_id"
						value="<%=device_id%>">
				</form>
				<div class="row">
					<div class="tab-content">
						<div class="col-lg-10">
							<h4 style="margin-top: 6px">단말상세정보</h4>
						</div>
						<div class="tab-pane fade show active" id="info">
							<table class="table table-bordered white-bg">
								<tbody>
									<tr>
										<td>단말ID</td>
										<td></td>
										<td>지역본부</td>
										<td></td>
									</tr>
								</tbody>
							</table>

						</div>
						<div class="tab-pane fade" id="object">bbb</div>
					</div>
				</div>
				<!-- body -->
			</div>
		</div>
	</div>

</body>
</html>

