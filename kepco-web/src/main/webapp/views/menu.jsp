<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<div class="sidebar-collapse">
	<ul class="nav metismenu" id="side-menu" style="">
		<li class="nav-header" style="height:59px">
	        <div class="profile-element logo-text">
	        	LWM2M LTE 5차
	        </div>
	        <div class="logo-element">
	            LWM2M
	        </div>
	    </li>
	    <li>
	        <a href="<%=COMMON_URL%>/main" target="contentsFrame"><i class="fa fa-chart-pie"></i> <span class="nav-label">Dashboard</span></a>
	    <li>
	        <a href="#"><i class="fa fa-cubes"></i> <span class="nav-label">모뎀 관리</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/device" target="contentsFrame">모뎀 목록 조회</a></li>
	            <li><a href="<%=COMMON_URL%>/NMS" target="contentsFrame">NMS</a></li>
	            <li><a href="<%=COMMON_URL%>/firmware" target="contentsFrame">펌웨어 관리 이력</a></li>
	        </ul>
	    </li>
	    <li>
	        <a href="#"><i class="fa  fa-database"></i> <span class="nav-label">미터관리</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/meter" target="contentsFrame">미터정보</a></li>                           
	        </ul>
	    </li>
   	    <li>
	        <a href="#"><i class="fa fa-chart-area"></i> <span class="nav-label">검침정보</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/metering" target="contentsFrame">LP</a></li>
	            <li><a href="<%=COMMON_URL%>/billing" target="contentsFrame">정기검침</a></li>                           
	        </ul>
	    </li>
	    <li>
	        <a href="#"><i class="fas fa-history"></i> <span class="nav-label">이력정보</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
				<li><a href="<%=COMMON_URL%>/operationLog" target="contentsFrame">제어 이력</a></li>
	        </ul>
	    </li>
	    
	    
	    <%-- <li>
	        <a href="#" ><i class="fa fa-pen-square"></i> <span class="nav-label">게시판</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/board" target="contentsFrame">공지사항</a></li>                            
	
	        </ul>
	    </li> --%>
	</ul>
</div>