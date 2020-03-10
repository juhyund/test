<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html>

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

<meta name="viewport" content="width=device-width, initial-scale=1.0">

<title>LWM2M LTE 5차</title>

<link href="<%=COMMON_PATH_JS%>/bootstrap.min.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/font-awesome.css" rel="stylesheet">
<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">

<!-- Mainly scripts -->
<script src="<%=COMMON_PATH_JS%>/jquery-3.1.1.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/bootstrap.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.slimscroll.min.js"></script>
<script type="text/javascript">
if (top.location!= self.location) {
   top.location = self.location.href;
}
</script>

<style>
.login-bg {
	position: relative;
	height: 1100px;
	background: url(<%=COMMON_PATH_IMG%>/login_bg.jpg);
	background-size: cover;
	background-position: top center;
}

.login-con {
	width: 100%;
	margin-top: 70%;
	margin-left: 25%;
	color: #ffffff;
}

.div {
	font-color:#ffffff;
}
</style>
<body>	
	<div id="wrapper" style="height: 100%; overflow: hidden;">
		<div class="row" style="width:100%">
				<div class="login-bg col-md-9" style="min-height: 1100px;"></div>

				<div class="col-md-3" style="padding:30px">
					<div class="row">
						<div class="col-lg-12">
							<div class="login-con"></div>
							<div class="col-lg-12">
								<img src="<%=COMMON_PATH_IMG%>/login_logo.png" style="width: 260px">
							</div>
							<div class="col-lg-12">
								<form class="m-t" role="form" action="./login" method="post">
									<div class="form-group">
										<input type="text" class="form-control" name="user_id" id="user_id" >
									</div>
									<div class="form-group">
										<input type="password" class="form-control" name="user_pass" id="user_pass">
									</div>
									<div class="form-group">
										<div class="i-checks">
											<label for="saveID"> <input type="checkbox" id="saveID"
												name="saveID" value="Y" checked> <i></i> 아이디저장
											</label>
										</div>
									</div>
									<c:if test="${not empty SPRING_SECURITY_LAST_EXCEPTION}">
										<div class="login-fail-msg" style="text-color:#ffffff"><p>로그인에 실패하였습니다<br>${sessionScope["SPRING_SECURITY_LAST_EXCEPTION"].message}</p> </div>
										<c:remove var="SPRING_SECURITY_LAST_EXCEPTION" scope="session"/>
									</c:if>
									<button type="submit" class="btn btn-primary block full-width m-b">Login</button>
									<p class="m-t" style="font-color:#ffffff">
										<strong>Copyright</strong> NuriTelecom.com ⓒ2020
									</p>
								</form>
							</div>
						</div>
					</div>
				</div>
			</div>
	</div>
</body>
</html>