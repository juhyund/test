<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<div class="sidebar-collapse">
	<ul class="nav metismenu" id="side-menu" style="">
		<li class="nav-header" style="height:59px">
	        <div class="profile-element logo-text">
	        	eWSN 실증 시스템
	        </div>
	        <div class="logo-element">
	            eWSN
	        </div>
	    </li>
	    <li>
	        <a href="<%=COMMON_URL%>/main" target="contentsFrame"><i class="fa fa-chart-pie"></i> <span class="nav-label">Dashboard</span></a>
	    </li>
	    <li>
	        <a href="#"><i class="fa fa-chart-area"></i> <span class="nav-label">Metering</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/metering" target="contentsFrame">검침데이터 조회</a></li>
	            <li><a href="<%=COMMON_URL%>/metering" target="contentsFrame">정기검침 (X)</a></li>                           
	        </ul>
	    </li>
	    <li>
	        <a href="#"><i class="fa fa-cubes"></i> <span class="nav-label">단말 관리</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/device" target="contentsFrame">단말 목록 조회</a></li>
	            <li><a href="<%=COMMON_URL%>/deviceControl" target="contentsFrame">제어 결과 조회</a></li>
	        </ul>
	    </li>
	    <li>
	        <a href="#"><i class="fa  fa-database"></i> <span class="nav-label">Resource 관리</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/model" target="contentsFrame">리소스 모델 관리</a></li>                           
	        </ul>
	    </li>
	    <li>
	        <a href="#"><i class="fa fa-desktop"></i> <span class="nav-label">모니터링</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/monitoring" target="contentsFrame">검침 현황 모니터링 (X)</a></li>
	            <li><a href="<%=COMMON_URL%>/monitoring" target="contentsFrame">통신 현황 모니터링 (X)</a></li>
	        </ul>
	    </li>
	    <li>
	        <a href="#"><i class="fa fa-map"></i> <span class="nav-label">NMS</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/NMS" target="contentsFrame">Connectivity Monitoring</a></li>
	            <li><a href="<%=COMMON_URL%>/NMSDetail" target="contentsFrame">NMS 상세</a></li>
	        </ul>
	    </li>
	    <li>
	        <a href="<%=COMMON_URL%>/user" target="contentsFrame">
	        	<i class="fa fa-users"></i> <span class="nav-label">사용자관리</span> 
	        </a>
	    </li>
	    <%-- <li>
	        <a href="#" ><i class="fa fa-pen-square"></i> <span class="nav-label">게시판</span> <span class="fa arrow"></span></a>
	        <ul class="nav nav-second-level collapse" aria-expanded="false">
	            <li><a href="<%=COMMON_URL%>/board" target="contentsFrame">공지사항</a></li>                            
	
	        </ul>
	    </li> --%>
	</ul>
</div>