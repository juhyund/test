<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<title><%=PAGE_TITLE%></title>
<link href="<%=COMMON_PATH_JS%>/bootstrap.min.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/font-awesome.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/datepicker3.css" rel="stylesheet">
<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">

<!-- Mainly scripts -->
<script src="<%=COMMON_PATH_JS%>/jquery-3.1.1.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/popper.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/bootstrap.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.metisMenu.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.slimscroll.min.js"></script>

<!-- Custom and plugin javascript -->
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>

<!-- Data picker -->
<script src="<%=COMMON_PATH_JS%>/bootstrap-datepicker.js"></script>
<script src="https://unpkg.com/ag-grid-community/dist/ag-grid-community.min.noStyle.js"></script>
<link rel="stylesheet" href="https://unpkg.com/ag-grid-community/dist/styles/ag-grid.css">
<link rel="stylesheet" href="https://unpkg.com/ag-grid-community/dist/styles/ag-theme-balham.css">

<!-- highcharts -->
<script src="https://code.highcharts.com/highcharts.js"></script>
<script src="https://code.highcharts.com/modules/series-label.js"></script>
<script src="https://code.highcharts.com/modules/exporting.js"></script>
<script src="https://code.highcharts.com/modules/export-data.js"></script>


<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
</head>
<body>
<!--  wrapper -->
<div id="content">
<div id="wrapper">
<div id="page-wrapper" style="width:100%" class="gray-bg" >
<!-- navigator -->
<div class="row wrapper page-heading" style="padding:5px">
<div class="col-lg-10" >
	<h3 style="margin-top:6px">Dashboard</h3>
</div>
<div class="col-lg-2" >
	<ol class="breadcrumb" style="float:right;margin-top:10px;">
		<li class="breadcrumb-item">
			<a href="http://webapplayers.com/inspinia_admin-v2.9.2/index.html">Home</a>
		</li>
		<li class="breadcrumb-item active">
			<strong>Main</strong>
		</li>
		</ol>
	</div>						
</div>
<!-- navigator -->
<!-- body -->
            <div class="wrapper wrapper-content ">
            <div class="row">
                <div class="col-lg-4">
                    <div class="widget style1 navy-bg">
                    <div class="row">
                        <div class="col-4">
                           <i class="fa fa-chart-pie fa-5x"></i>
                        </div>
                        <div class="col-8 text-right">                            
                            <h2 class="font-bold">통신현황 - 98%</h2>
                            <h3> 24시간 이내 통신 성공 (196/200) </h3>
                        </div>
                    </div>
                		</div>
                </div>
                <div class="col-lg-4">
                    <div class="widget style1 yellow-bg">
                    <div class="row">
                        <div class="col-4">
                           <i class="fa fa-chart-bar fa-5x"></i>
                        </div>
                        <div class="col-8 text-right">                            
                            <h2 class="font-bold">검침현황 - 98%</h2>
                            <h3> 2019.07.09 10:15 현재 검침율 </h3>
                        </div>
                    </div>
                		</div>
                </div>
                <div class="col-lg-4">
                    <div class="widget style1 red-bg">
                    <div class="row">
                        <div class="col-4">
                           <i class="fa fa-chart-line fa-5x"></i>
                        </div>
                        <div class="col-8 text-right">                            
                            <h2 class="font-bold">적시현황 - 98%</h2>
                            <h3> 2019.07.09 10:15 기준 적시율 </h3>
                        </div>
                    </div>
                		</div>
                </div>
            </div>
            <div class="row">
                <div class="col-lg-4">
                    <div class="ibox ">                      
										<div class="ibox-content text-center h-300" style="height: 300px; overflow: hidden;">                    	 	
                    	<div id="pie-chart" style="min-width: 310px; height: 300px; max-width: 650px; margin: 0 auto"></div>
                    </div>
										</div>
                </div>
                <div class="col-lg-4">
                    <div class="ibox ">                      
                        <div class="ibox-content text-center h-300" style="height: 300px; overflow: hidden;">
                        	<center>
<div id="highcharts-leu8wyg-38" dir="ltr" class="highcharts-container " style="position: relative; overflow: hidden; width: 373px; height: 270px; text-align: left; line-height: normal; z-index: 0; -webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><svg version="1.1" class="highcharts-root " style="font-family:&quot;Lucida Grande&quot;, &quot;Lucida Sans Unicode&quot;, Arial, Helvetica, sans-serif;font-size:12px;" xmlns="http://www.w3.org/2000/svg" width="373" height="270" viewBox="0 0 373 270"><desc>Created with Highcharts 7.2.0</desc><defs><clipPath id="highcharts-leu8wyg-39-"><rect x="0" y="0" width="296" height="181" fill="none"></rect></clipPath></defs><rect fill="#ffffff" class="highcharts-background" x="0" y="0" width="373" height="270" rx="0" ry="0"></rect><rect fill="none" class="highcharts-plot-background" x="67" y="10" width="296" height="181"></rect><g class="highcharts-grid highcharts-xaxis-grid" data-z-index="1"><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 125.5 10 L 125.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 184.5 10 L 184.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 244.5 10 L 244.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 303.5 10 L 303.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 362.5 10 L 362.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 66.5 10 L 66.5 191" opacity="1"></path></g><g class="highcharts-grid highcharts-yaxis-grid" data-z-index="1"><path fill="none" stroke="#e6e6e6" stroke-width="1" data-z-index="1" class="highcharts-grid-line" d="M 67 191.5 L 363 191.5" opacity="1"></path><path fill="none" stroke="#e6e6e6" stroke-width="1" data-z-index="1" class="highcharts-grid-line" d="M 67 131.5 L 363 131.5" opacity="1"></path><path fill="none" stroke="#e6e6e6" stroke-width="1" data-z-index="1" class="highcharts-grid-line" d="M 67 70.5 L 363 70.5" opacity="1"></path><path fill="none" stroke="#e6e6e6" stroke-width="1" data-z-index="1" class="highcharts-grid-line" d="M 67 9.5 L 363 9.5" opacity="1"></path></g><rect fill="none" class="highcharts-plot-border" data-z-index="1" x="67" y="10" width="296" height="181"></rect><g class="highcharts-axis highcharts-xaxis" data-z-index="2"><path fill="none" class="highcharts-axis-line" stroke="#ccd6eb" stroke-width="1" data-z-index="7" d="M 67 191.5 L 363 191.5"></path></g><g class="highcharts-axis highcharts-yaxis" data-z-index="2"><text x="26.03125" data-z-index="7" text-anchor="middle" transform="translate(0,0) rotate(270 26.03125 100.5)" class="highcharts-axis-title" style="color:#666666;fill:#666666;" y="100.5"><tspan>Number of fruits</tspan></text><path fill="none" class="highcharts-axis-line" data-z-index="7" d="M 67 10 L 67 191"></path></g><g class="highcharts-series-group" data-z-index="3"><g data-z-index="0.1" class="highcharts-series highcharts-series-0 highcharts-column-series highcharts-color-0  highcharts-tracker" transform="translate(67,10) scale(1 1)" clip-path="url(#highcharts-leu8wyg-39-)" opacity="1"><rect x="13.5" y="84.5" width="15" height="61" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect><rect x="72.5" y="97.5" width="15" height="36" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect><rect x="131.5" y="84.5" width="15" height="49" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect><rect x="190.5" y="72.5" width="15" height="85" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect><rect x="249.5" y="97.5" width="15" height="24" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect></g><g data-z-index="0.1" class="highcharts-markers highcharts-series-0 highcharts-column-series highcharts-color-0 " transform="translate(67,10) scale(1 1)" clip-path="none" opacity="1"></g><g data-z-index="0.1" class="highcharts-series highcharts-series-1 highcharts-column-series highcharts-color-1  highcharts-tracker" transform="translate(67,10) scale(1 1)" clip-path="url(#highcharts-leu8wyg-39-)" opacity="1"><rect x="13.5" y="145.5" width="15" height="36" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect><rect x="72.5" y="133.5" width="15" height="48" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect><rect x="131.5" y="133.5" width="15" height="48" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect><rect x="190.5" y="157.5" width="15" height="24" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect><rect x="249.5" y="121.5" width="15" height="60" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect></g><g data-z-index="0.1" class="highcharts-markers highcharts-series-1 highcharts-column-series highcharts-color-1 " transform="translate(67,10) scale(1 1)" clip-path="none" opacity="1"></g><g data-z-index="0.1" class="highcharts-series highcharts-series-2 highcharts-column-series highcharts-color-2  highcharts-tracker" transform="translate(67,10) scale(1 1)" clip-path="url(#highcharts-leu8wyg-39-)"><rect x="30.5" y="121.5" width="15" height="24" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect><rect x="90.5" y="121.5" width="15" height="60" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect><rect x="149.5" y="60.5" width="15" height="73" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect><rect x="208.5" y="109.5" width="15" height="24" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect><rect x="267.5" y="133.5" width="15" height="12" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect></g><g data-z-index="0.1" class="highcharts-markers highcharts-series-2 highcharts-column-series highcharts-color-2 " transform="translate(67,10) scale(1 1)" clip-path="none"></g><g data-z-index="0.1" class="highcharts-series highcharts-series-3 highcharts-column-series highcharts-color-3  highcharts-tracker" transform="translate(67,10) scale(1 1)" clip-path="url(#highcharts-leu8wyg-39-)" opacity="1"><rect x="30.5" y="145.5" width="15" height="36" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect><rect x="90.5" y="181.5" width="15" height="0" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect><rect x="149.5" y="133.5" width="15" height="48" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect><rect x="208.5" y="133.5" width="15" height="48" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect><rect x="267.5" y="145.5" width="15" height="36" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect></g><g data-z-index="0.1" class="highcharts-markers highcharts-series-3 highcharts-column-series highcharts-color-3 " transform="translate(67,10) scale(1 1)" clip-path="none" opacity="1"></g></g><text x="187" text-anchor="middle" class="highcharts-title" data-z-index="4" style="color:#333333;font-size:18px;fill:#333333;" y="24"></text><text x="187" text-anchor="middle" class="highcharts-subtitle" data-z-index="4" style="color:#666666;fill:#666666;" y="24"></text><text x="10" text-anchor="start" class="highcharts-caption" data-z-index="4" style="color:#666666;fill:#666666;" y="267"></text><g class="highcharts-legend" data-z-index="7" transform="translate(53,225)"><rect fill="none" class="highcharts-legend-box" rx="0" ry="0" x="0" y="0" width="267" height="30" visibility="visible"></rect><g data-z-index="1"><g><g class="highcharts-legend-item highcharts-column-series highcharts-color-0 highcharts-series-0" data-z-index="1" transform="translate(8,3)"><text x="21" style="color:#333333;cursor:pointer;font-size:12px;font-weight:bold;fill:#333333;" text-anchor="start" data-z-index="2" y="15"><tspan>John</tspan></text><rect x="2" y="4" width="12" height="12" fill="#7cb5ec" rx="6" ry="6" class="highcharts-point" data-z-index="3"></rect></g><g class="highcharts-legend-item highcharts-column-series highcharts-color-1 highcharts-series-1" data-z-index="1" transform="translate(77.46875,3)"><text x="21" y="15" style="color:#333333;cursor:pointer;font-size:12px;font-weight:bold;fill:#333333;" text-anchor="start" data-z-index="2"><tspan>Joe</tspan></text><rect x="2" y="4" width="12" height="12" fill="#434348" rx="6" ry="6" class="highcharts-point" data-z-index="3"></rect></g><g class="highcharts-legend-item highcharts-column-series highcharts-color-2 highcharts-series-2" data-z-index="1" transform="translate(138.484375,3)"><text x="21" y="15" style="color:#333333;cursor:pointer;font-size:12px;font-weight:bold;fill:#333333;" text-anchor="start" data-z-index="2"><tspan>Jane</tspan></text><rect x="2" y="4" width="12" height="12" fill="#90ed7d" rx="6" ry="6" class="highcharts-point" data-z-index="3"></rect></g><g class="highcharts-legend-item highcharts-column-series highcharts-color-3 highcharts-series-3" data-z-index="1" transform="translate(206.4375,3)"><text x="21" y="15" style="color:#333333;cursor:pointer;font-size:12px;font-weight:bold;fill:#333333;" text-anchor="start" data-z-index="2"><tspan>Janet</tspan></text><rect x="2" y="4" width="12" height="12" fill="#f7a35c" rx="6" ry="6" class="highcharts-point" data-z-index="3"></rect></g></g></g></g><g class="highcharts-axis-labels highcharts-xaxis-labels" data-z-index="7"><text x="96.6" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Apples</text><text x="155.8" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Oranges</text><text x="215" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Pears</text><text x="274.2" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Grapes</text><text x="333.4" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Bananas</text></g><g class="highcharts-axis-labels highcharts-yaxis-labels" data-z-index="7"><text x="52" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="end" transform="translate(0,0)" y="195" opacity="1">0</text><text x="52" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="end" transform="translate(0,0)" y="135" opacity="1">5</text><text x="52" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="end" transform="translate(0,0)" y="74" opacity="1">10</text><text x="52" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="end" transform="translate(0,0)" y="14" opacity="1">15</text></g></svg></div></div>
                       </center>                        
                    </div>
                </div>
                <div class="col-lg-4">
                    <div class="ibox ">                      
                        <div class="ibox-content text-center h-300" style="height: 300px; overflow: hidden;">
                        	<center>
<div id="highcharts-leu8wyg-38" dir="ltr" class="highcharts-container " style="position: relative; overflow: hidden; width: 373px; height: 270px; text-align: left; line-height: normal; z-index: 0; -webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><svg version="1.1" class="highcharts-root " style="font-family:&quot;Lucida Grande&quot;, &quot;Lucida Sans Unicode&quot;, Arial, Helvetica, sans-serif;font-size:12px;" xmlns="http://www.w3.org/2000/svg" width="373" height="270" viewBox="0 0 373 270"><desc>Created with Highcharts 7.2.0</desc><defs><clipPath id="highcharts-leu8wyg-39-"><rect x="0" y="0" width="296" height="181" fill="none"></rect></clipPath></defs><rect fill="#ffffff" class="highcharts-background" x="0" y="0" width="373" height="270" rx="0" ry="0"></rect><rect fill="none" class="highcharts-plot-background" x="67" y="10" width="296" height="181"></rect><g class="highcharts-grid highcharts-xaxis-grid" data-z-index="1"><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 125.5 10 L 125.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 184.5 10 L 184.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 244.5 10 L 244.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 303.5 10 L 303.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 362.5 10 L 362.5 191" opacity="1"></path><path fill="none" data-z-index="1" class="highcharts-grid-line" d="M 66.5 10 L 66.5 191" opacity="1"></path></g><g class="highcharts-grid highcharts-yaxis-grid" data-z-index="1"><path fill="none" stroke="#e6e6e6" stroke-width="1" data-z-index="1" class="highcharts-grid-line" d="M 67 191.5 L 363 191.5" opacity="1"></path><path fill="none" stroke="#e6e6e6" stroke-width="1" data-z-index="1" class="highcharts-grid-line" d="M 67 131.5 L 363 131.5" opacity="1"></path><path fill="none" stroke="#e6e6e6" stroke-width="1" data-z-index="1" class="highcharts-grid-line" d="M 67 70.5 L 363 70.5" opacity="1"></path><path fill="none" stroke="#e6e6e6" stroke-width="1" data-z-index="1" class="highcharts-grid-line" d="M 67 9.5 L 363 9.5" opacity="1"></path></g><rect fill="none" class="highcharts-plot-border" data-z-index="1" x="67" y="10" width="296" height="181"></rect><g class="highcharts-axis highcharts-xaxis" data-z-index="2"><path fill="none" class="highcharts-axis-line" stroke="#ccd6eb" stroke-width="1" data-z-index="7" d="M 67 191.5 L 363 191.5"></path></g><g class="highcharts-axis highcharts-yaxis" data-z-index="2"><text x="26.03125" data-z-index="7" text-anchor="middle" transform="translate(0,0) rotate(270 26.03125 100.5)" class="highcharts-axis-title" style="color:#666666;fill:#666666;" y="100.5"><tspan>Number of fruits</tspan></text><path fill="none" class="highcharts-axis-line" data-z-index="7" d="M 67 10 L 67 191"></path></g><g class="highcharts-series-group" data-z-index="3"><g data-z-index="0.1" class="highcharts-series highcharts-series-0 highcharts-column-series highcharts-color-0  highcharts-tracker" transform="translate(67,10) scale(1 1)" clip-path="url(#highcharts-leu8wyg-39-)" opacity="1"><rect x="13.5" y="84.5" width="15" height="61" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect><rect x="72.5" y="97.5" width="15" height="36" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect><rect x="131.5" y="84.5" width="15" height="49" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect><rect x="190.5" y="72.5" width="15" height="85" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect><rect x="249.5" y="97.5" width="15" height="24" fill="#7cb5ec" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-0"></rect></g><g data-z-index="0.1" class="highcharts-markers highcharts-series-0 highcharts-column-series highcharts-color-0 " transform="translate(67,10) scale(1 1)" clip-path="none" opacity="1"></g><g data-z-index="0.1" class="highcharts-series highcharts-series-1 highcharts-column-series highcharts-color-1  highcharts-tracker" transform="translate(67,10) scale(1 1)" clip-path="url(#highcharts-leu8wyg-39-)" opacity="1"><rect x="13.5" y="145.5" width="15" height="36" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect><rect x="72.5" y="133.5" width="15" height="48" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect><rect x="131.5" y="133.5" width="15" height="48" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect><rect x="190.5" y="157.5" width="15" height="24" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect><rect x="249.5" y="121.5" width="15" height="60" fill="#434348" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-1"></rect></g><g data-z-index="0.1" class="highcharts-markers highcharts-series-1 highcharts-column-series highcharts-color-1 " transform="translate(67,10) scale(1 1)" clip-path="none" opacity="1"></g><g data-z-index="0.1" class="highcharts-series highcharts-series-2 highcharts-column-series highcharts-color-2  highcharts-tracker" transform="translate(67,10) scale(1 1)" clip-path="url(#highcharts-leu8wyg-39-)"><rect x="30.5" y="121.5" width="15" height="24" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect><rect x="90.5" y="121.5" width="15" height="60" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect><rect x="149.5" y="60.5" width="15" height="73" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect><rect x="208.5" y="109.5" width="15" height="24" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect><rect x="267.5" y="133.5" width="15" height="12" fill="#90ed7d" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-2"></rect></g><g data-z-index="0.1" class="highcharts-markers highcharts-series-2 highcharts-column-series highcharts-color-2 " transform="translate(67,10) scale(1 1)" clip-path="none"></g><g data-z-index="0.1" class="highcharts-series highcharts-series-3 highcharts-column-series highcharts-color-3  highcharts-tracker" transform="translate(67,10) scale(1 1)" clip-path="url(#highcharts-leu8wyg-39-)" opacity="1"><rect x="30.5" y="145.5" width="15" height="36" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect><rect x="90.5" y="181.5" width="15" height="0" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect><rect x="149.5" y="133.5" width="15" height="48" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect><rect x="208.5" y="133.5" width="15" height="48" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect><rect x="267.5" y="145.5" width="15" height="36" fill="#f7a35c" stroke="#ffffff" stroke-width="1" opacity="1" class="highcharts-point highcharts-color-3"></rect></g><g data-z-index="0.1" class="highcharts-markers highcharts-series-3 highcharts-column-series highcharts-color-3 " transform="translate(67,10) scale(1 1)" clip-path="none" opacity="1"></g></g><text x="187" text-anchor="middle" class="highcharts-title" data-z-index="4" style="color:#333333;font-size:18px;fill:#333333;" y="24"></text><text x="187" text-anchor="middle" class="highcharts-subtitle" data-z-index="4" style="color:#666666;fill:#666666;" y="24"></text><text x="10" text-anchor="start" class="highcharts-caption" data-z-index="4" style="color:#666666;fill:#666666;" y="267"></text><g class="highcharts-legend" data-z-index="7" transform="translate(53,225)"><rect fill="none" class="highcharts-legend-box" rx="0" ry="0" x="0" y="0" width="267" height="30" visibility="visible"></rect><g data-z-index="1"><g><g class="highcharts-legend-item highcharts-column-series highcharts-color-0 highcharts-series-0" data-z-index="1" transform="translate(8,3)"><text x="21" style="color:#333333;cursor:pointer;font-size:12px;font-weight:bold;fill:#333333;" text-anchor="start" data-z-index="2" y="15"><tspan>John</tspan></text><rect x="2" y="4" width="12" height="12" fill="#7cb5ec" rx="6" ry="6" class="highcharts-point" data-z-index="3"></rect></g><g class="highcharts-legend-item highcharts-column-series highcharts-color-1 highcharts-series-1" data-z-index="1" transform="translate(77.46875,3)"><text x="21" y="15" style="color:#333333;cursor:pointer;font-size:12px;font-weight:bold;fill:#333333;" text-anchor="start" data-z-index="2"><tspan>Joe</tspan></text><rect x="2" y="4" width="12" height="12" fill="#434348" rx="6" ry="6" class="highcharts-point" data-z-index="3"></rect></g><g class="highcharts-legend-item highcharts-column-series highcharts-color-2 highcharts-series-2" data-z-index="1" transform="translate(138.484375,3)"><text x="21" y="15" style="color:#333333;cursor:pointer;font-size:12px;font-weight:bold;fill:#333333;" text-anchor="start" data-z-index="2"><tspan>Jane</tspan></text><rect x="2" y="4" width="12" height="12" fill="#90ed7d" rx="6" ry="6" class="highcharts-point" data-z-index="3"></rect></g><g class="highcharts-legend-item highcharts-column-series highcharts-color-3 highcharts-series-3" data-z-index="1" transform="translate(206.4375,3)"><text x="21" y="15" style="color:#333333;cursor:pointer;font-size:12px;font-weight:bold;fill:#333333;" text-anchor="start" data-z-index="2"><tspan>Janet</tspan></text><rect x="2" y="4" width="12" height="12" fill="#f7a35c" rx="6" ry="6" class="highcharts-point" data-z-index="3"></rect></g></g></g></g><g class="highcharts-axis-labels highcharts-xaxis-labels" data-z-index="7"><text x="96.6" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Apples</text><text x="155.8" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Oranges</text><text x="215" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Pears</text><text x="274.2" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Grapes</text><text x="333.4" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="middle" transform="translate(0,0)" y="210" opacity="1">Bananas</text></g><g class="highcharts-axis-labels highcharts-yaxis-labels" data-z-index="7"><text x="52" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="end" transform="translate(0,0)" y="195" opacity="1">0</text><text x="52" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="end" transform="translate(0,0)" y="135" opacity="1">5</text><text x="52" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="end" transform="translate(0,0)" y="74" opacity="1">10</text><text x="52" style="color:#666666;cursor:default;font-size:11px;fill:#666666;" text-anchor="end" transform="translate(0,0)" y="14" opacity="1">15</text></g></svg></div></div>
                       </center>                        
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="col-lg-4">
                                          		
              		<table class="table table-bordered white-bg">
                      <thead>
                      <tr>
                          <th class="text-center">통신 상태</th>
                          <th width="150" class="text-right">건수</th>
                          <th width="150" class="text-right">통신율(%)</th>
                      </tr>
                      </thead>
                      <tbody>
                      <tr>                         
                          <td class="text-center">24시간 이내</td>
                          <td class="text-right">196</td>
                          <td class="text-right">98%</td>
                      </tr>
                      <tr>
                          <td class="text-center">24시간 - 48시간</td>
                          <td class="text-right">196</td>
                          <td class="text-right">98%</td>
                      </tr>
                      <tr>                         
                          <td class="text-center">48시간 초과</td>
                          <td class="text-right">196</td>
                          <td class="text-right">98%</td>
                      </tr>
                      <tr>                         
                          <td class="text-center">통신기록 없음</td>
                          <td class="text-right">196</td>
                          <td class="text-right">98%</td>
                      </tr>
                      <tr class="table-active">                          
                          <th class="text-center">TOTAL</td>
                          <th class="text-right">196</th>
                          <th class="text-right">98%</th>
                      </tr>
                      </tbody>
                  </table>	
                      
                </div>
                <div class="col-lg-4">
                                      		
                		<table class="table table-bordered white-bg">
                      <thead>
                      <tr>
                          <th class="text-center">미터타입</th>
                          <th width="150" class="text-right">성공(%)</th>
                          <th width="150" class="text-right">실패(%)</th>
                      </tr>
                      </thead>
                      <tbody>
                      <tr>                         
                          <td class="text-center">E Type</td>
                          <td class="text-right">90%</td>
                          <td class="text-right">10%</td>
                      </tr>
                      <tr>
                          <td class="text-center">EA Type</td>
                          <td class="text-right">90%</td>
                          <td class="text-right">10%</td>
                      </tr>
                      <tr>                         
                          <td class="text-center">G Type</td>
                          <td class="text-right">90%</td>
                          <td class="text-right">10%</td>
                      </tr>
                      <tr>                         
                          <td class="text-center">표준</td>
                          <td class="text-right">90%</td>
                          <td class="text-right">10%</td>
                      </tr>
                      <tr class="table-active">                          
                          <th class="text-center">TOTAL</th>
                          <th class="text-right">90%</th>
                          <th class="text-right">10%</th>
                      </tr>
                      </tbody>
                  </table>
                      
                </div>
                <div class="col-lg-4">
                                    		
	            		<table class="table table-bordered white-bg">
                      <thead>
                      <tr>
                          <th class="text-center">미터타입</th>
                          <th width="150" class="text-right">성공(%)</th>
                          <th width="150" class="text-right">실패(%)</th>
                      </tr>
                      </thead>
                      <tbody>
                      <tr>                         
                          <td class="text-center">E Type</td>
                          <td class="text-right">90%</td>
                          <td class="text-right">10%</td>
                      </tr>
                      <tr>
                          <td class="text-center">EA Type</td>
                          <td class="text-right">90%</td>
                          <td class="text-right">10%</td>
                      </tr>
                      <tr>                         
                          <td class="text-center">G Type</td>
                          <td class="text-right">90%</td>
                          <td class="text-right">10%</td>
                      </tr>
                      <tr>                         
                          <td class="text-center">표준</td>
                          <td class="text-right">90%</td>
                          <td class="text-right">10%</td>
                      </tr>
                      <tr class="table-active">                           
                          <th class="text-center">TOTAL</th>
                          <th class="text-right">90%</th>
                          <th class="text-right">10%</th>
                      </tr>
                      </tbody>
                  </table> 	
                  
                  
                       
                </div>
            </div>
        		</div>
            
            <!-- body -->
</div>
</div>	
</div>

 <script type="text/javascript" charset="utf-8">
	
		// Build the chart
Highcharts.chart('pie-chart', {
    chart: {
        plotBackgroundColor: null,
        plotBorderWidth: null,
        plotShadow: false,
        type: 'pie'
    },
    title: {
        text: '통신현황'
    },
    tooltip: {
        pointFormat: '{series.name}: <b>{point.percentage:.1f}%</b>'
    },
    plotOptions: {
        pie: {
            allowPointSelect: true,
            cursor: 'pointer',
            dataLabels: {
                enabled: false
            },
            showInLegend: true
        }
    },
    series: [{
        name: 'Brands',
        colorByPoint: true,
        data: [{
            name: 'Chrome',
            y: 61.41,
            sliced: true,
            selected: true
        }, {
            name: 'Internet Explorer',
            y: 11.84
        }, {
            name: 'Firefox',
            y: 10.85
        }, {
            name: 'Edge',
            y: 4.67
        }]
    }]
});
		

</script>
<!--  wrapper -->
</body>
</html>