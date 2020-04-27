<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8" isELIgnored="false"%>
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
<script
	src="https://unpkg.com/ag-grid-community/dist/ag-grid-community.min.noStyle.js"></script>
<link rel="stylesheet"
	href="https://unpkg.com/ag-grid-community/dist/styles/ag-grid.css">
<link rel="stylesheet"
	href="https://unpkg.com/ag-grid-community/dist/styles/ag-theme-balham.css">

<!-- highcharts -->
<script src="https://code.highcharts.com/highcharts.js"></script>
<script src="https://code.highcharts.com/modules/series-label.js"></script>
<script src="https://code.highcharts.com/modules/exporting.js"></script>
<script src="https://code.highcharts.com/modules/export-data.js"></script>
<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
</head>
<body>
	<!--  wrapper -->
	<div id="content">
		<div id="wrapper">
			<div id="page-wrapper" style="width: 100%" class="gray-bg">
				<!-- navigator -->
				<div class="row wrapper page-heading" style="padding: 5px">
					<div class="col-lg-10">
						<h3 style="margin-top: 6px">Dashboard</h3>
					</div>
					<div class="col-lg-2">
						<ol class="breadcrumb" style="float: right; margin-top: 10px;">
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
										<h2 class="font-bold">
											통신현황 -
											<div style="display: inline;" id="com_rate"></div>
										</h2>
										<h3><div style="display: inline;" id="com_date"></div> 현재 통신 성공율</h3>
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
										<h2 class="font-bold">
											검침현황 - 
											<div style="display: inline;" id="lp_rate"></div>
										</h2>
										<h3><div style="display: inline;" id="lp_date"></div> 현재 검침 성공율</h3>
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
										<h2 class="font-bold">제어현황 - <div style="display: inline;" id="exec_rate"></div></h2>
										<h3><div style="display: inline;" id="exec_date"></div> 현재 제어 성공율</h3>
									</div>
								</div>
							</div>
						</div>
					</div>
					<div class="row">
						<div class="col-lg-4">
							<div class="ibox ">
								<div class="ibox-content text-center h-300"
									style="height: 300px; overflow: hidden;">
									<div id="comm_chart"
										style="min-width: 310px; height: 300px; max-width: 650px; margin: 0 auto"></div>
								</div>
							</div>
						</div>
						<div class="col-lg-4">
							<div class="ibox ">
								<div class="ibox-content text-center h-300"
									style="height: 300px; overflow: hidden;">
									<div id="lp_chart"
										style="min-width: 310px; height: 300px; max-width: 650px; margin: 0 auto"></div>
								</div>
							</div>
						</div>
						<div class="col-lg-4">
							<div class="ibox ">
								<div class="ibox-content text-center h-300"
									style="height: 300px; overflow: hidden;">
									<div id="exec_chart"
										style="min-width: 310px; height: 300px; max-width: 650px; margin: 0 auto"></div>
								</div>
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
										<td class="text-center">24H 이내</td>
										<td class="text-right" id="d1_cnt"></td>
										<td class="text-right" id="d1_rate"></td>
									</tr>
									<tr>
										<td class="text-center">24H - 48H</td>
										<td class="text-right" id="d2_cnt"></td>
										<td class="text-right" id="d2_rate"></td>
									</tr>
									<tr>
										<td class="text-center">48H 초과</td>
										<td class="text-right" id="d3_cnt"></td>
										<td class="text-right" id="d3_rate"></td>
									</tr>
									<tr>
										<td class="text-center">통신기록 없음</td>
										<td class="text-right" id="d4_cnt"></td>
										<td class="text-right" id="d4_rate"></td>
									</tr>
									<tr class="table-active">
										<th class="text-center">TOTAL
										</td>
										<th class="text-right" id="t_cnt"></th>
										<th class="text-right" id="t_rate"></th>
									</tr>
								</tbody>
							</table>

						</div>
						<div class="col-lg-4">

							<table class="table table-bordered white-bg">
								<thead>
									<tr>
										<th class="text-center">계기타입</th>
										<th width="150" class="text-right">미터개수/성공(%)</th>
										<th width="150" class="text-right">미터개수/실패(%)</th>
									</tr>
								</thead>
								<tbody id="lp_body">
								</tbody>
							</table>

						</div>
						<div class="col-lg-4">

							<table class="table table-bordered white-bg">
								<thead>
									<tr>
										<th width="100" class="text-center">제어명령</th>
										<th width="150" class="text-right">성공</th>
										<th width="150" class="text-right">실패</th>
										<th width="150" class="text-right">대기</th>
									</tr>
								</thead>
								<tbody id="exec_body">
									
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
$(document).ready(function() {	
	communication();
	lpRate();
	excuteRate();
});	
	

function communication(){
	var options = { 
           success     : successCommunication,
           url         : COMMON_URL + "/ajaxCommunication",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function successCommunication(data, status) {
	var toDay = new Date();
	var d1_rate = 0;
	var d2_rate = 0;
	var d3_rate = 0;
	var d4_rate = 0;
	var t = 0;
	if(data.d1 != 0){
		d1_rate = data.d1 / data.total * 100;
		t++;
	}
	if(data.d2 != 0) {
		d2_rate = data.d2 / data.total * 100;
		t++;
	}
	if(data.d3 != 0) {
		d3_rate = data.d3 / data.total * 100;
		t++;
	}
	if(data.d4 != 0) {
		d4_rate = data.d4 / data.total * 100;
		t++;
	}
	var t_cnt = data.d1 + data.d2 + data.d3 + data.d4;
	var t_rate = 0;
	if(t_cnt != 0) {
		t_rate = (d1_rate + d2_rate + d3_rate + d4_rate) / t;
	}
	
	$("#com_rate").html(removeZero(t_rate.toFixed(1))+"%");
	$("#com_date").html(toDay.yyyymmdd());

	$("#d1_cnt").html(data.d1);
	$("#d1_rate").html(removeZero(d1_rate.toFixed(1)) + "%");
	$("#d2_cnt").html(data.d2);
	$("#d2_rate").html(removeZero(d2_rate.toFixed(1)) + "%");
	$("#d3_cnt").html(data.d3);
	$("#d3_rate").html(removeZero(d3_rate.toFixed(1)) + "%");
	$("#d4_cnt").html(data.d4);
	$("#d4_rate").html(removeZero(d4_rate.toFixed(1)) + "%");
	$("#t_cnt").html(t_cnt);
	$("#t_rate").html(removeZero(t_rate.toFixed(1)) + "%");
	
	Highcharts.chart('comm_chart', {
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
	        name: '통신 률',
	        colorByPoint: true,
	        data: [{
	            name: '24H 이내',
	            y: data.d1,
	            sliced: true,
	            selected: true,
	            color: '#0009FF'
	        }, {
	            name: '24H ~ 48H 이내',
	            y: data.d2,
	            color: '#FFE510'
	        }, {
	            name: '48H 초과',
	            y: data.d3,
	            color: '#FF0900',
	        }, {
	            name: '통신기록 없음',
	            y: data.d4,
	            color: '#7A753F'
	        }]
	    }]
	});
}

function lpRate(){
	var options = { 
           success     : successLpRate,
           url         : COMMON_URL + "/ajaxLpRate",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function successLpRate(data, status) {
	var toDay = new Date();
	var total_succ_cnt = 0;
   	var total_fail_cnt = 0;
	var total_succ = 0;
   	var total_fail = 0;
	
    var types = new Array();
    var succ = new Array();
    var fail = new Array();
    
    if(data.result.length > 0){

        for(var i=0 ; i < data.result.length ; i++){
        	var value = data.result[i];
        	
        	var total_cnt = value.total_cnt;
        	var succ_cnt = value.succ_cnt;
        	var fail_cnt = total_cnt - succ_cnt;
        	
        	var succ_rate = succ_cnt / total_cnt * 100;
        	var fail_rate = fail_cnt / total_cnt * 100;
        	
        	var tr = '<tr>'
        	tr += '<td class="text-center">' + value.m_type + '</td>';
        	tr += '<td class="text-right">' + succ_cnt + " ("+ removeZero(succ_rate.toFixed(1)) + '%)</td>';
        	tr += '<td class="text-right">' + fail_cnt + " ("+ removeZero(fail_rate.toFixed(1)) + '%)</td>';
        	tr += '</tr>';

        	$("#lp_body").append(tr);

        	total_succ += succ_rate;
        	total_fail += fail_rate;
        	
        	total_succ_cnt += succ_cnt;
        	total_fail_cnt += fail_cnt;
        	
            types[i] = value.m_type;
            succ[i] = Math.round(succ_rate);
            fail[i] = Math.round(fail_rate);
        }

       	var total_succ_rate = total_succ / types.length;
       	var total_fail_rate = total_fail / types.length;
        
        var last_tr = '<tr class="table-active">'
       	last_tr += '<th class="text-center">TOTAL</th>';
       	last_tr += '<th class="text-right">' + total_succ_cnt + " / " + removeZero(total_succ_rate.toFixed(1)) + '%</th>';
       	last_tr += '<th class="text-right">' + total_fail_cnt + " / " + removeZero(total_fail_rate.toFixed(1)) + '%</th>';
       	last_tr += '</tr>';

       	$("#lp_rate").html(removeZero(total_succ_rate.toFixed(1))+"%");
       	$("#lp_body").append(last_tr);
       	
    } else {
        var last_tr = '<tr>'
       	last_tr += '<th class="text-center" colspan="3">No Data.</th>';
       	last_tr += '</tr>';

       	$("#lp_rate").html("0%");
       	$("#lp_body").append(last_tr);    	
    }
    
    $("#lp_date").html(toDay.yyyymmdd());
   	
   	Highcharts.chart('lp_chart', {
   	    chart: {
   	        type: 'column'
   	    },
   	    title: {
   	        text: '검침현황'
   	    },
   	    xAxis: {
   	        categories: types,
   	        crosshair: true
   	    },
   	    yAxis: {
   	        min: 0,
   	        max: 100,
   	        title: {
   	            text: '%'
   	        }
   	    },
   	    tooltip: {
   	        headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
   	        pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
   	            '<td style="padding:5"><b>{point.y}%</b></td></tr>',
   	        footerFormat: '</table>',
   	        shared: true,
   	        useHTML: true
   	    },
   	    series: [{
   	        name: '성공',
   	     	color: '#0009FF',
   	        data: succ
   	    }, {
   	        name: '실패',
   	        color: '#FF0900',
   	        data: fail
   	    }]
   	});
}

function excuteRate(){
	var options = { 
           success     : successExcuteRate,
           url         : COMMON_URL + "/ajaxExcuteRate",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function successExcuteRate(data, status) {
	var toDay = new Date();
    var succ_cnt = 0;
    var fail_cnt = 0;
    var wait_cnt = 0;
    
    var types = new Array();
    var succ = new Array();
    var fail = new Array();
    var wait = new Array();
    
    if(data.result.length > 0){
    	for(var i=0 ; i < data.result.length ; i++){
        	var value = data.result[i];
        	var tr = '<tr>'
        	tr += '<td class="text-center">' + value.m_type + '</td>';
        	tr += '<td class="text-right">' + value.succ_cnt + '</td>';
        	tr += '<td class="text-right">' + value.fail_cnt + '</td>';
        	tr += '<td class="text-right">' + value.wait_cnt + '</td>';
        	tr += '</tr>';
        	
        	$("#exec_body").append(tr);
        	
            succ_cnt += value.succ_cnt;
            fail_cnt += value.fail_cnt;
            wait_cnt += value.wait_cnt;
            
            types[i] = value.m_type;
            succ[i] = value.succ_cnt;
            fail[i] = value.fail_cnt;
            wait[i] = value.wait_cnt;
        }
        
        var last_tr = '<tr class="table-active">'
       	last_tr += '<th class="text-center">TOTAL</th>';
       	last_tr += '<th class="text-right">' + succ_cnt + '</th>';
       	last_tr += '<th class="text-right">' + fail_cnt + '</th>';
       	last_tr += '<th class="text-right">' + wait_cnt + '</th>';
       	last_tr += '</tr>';
       	
       	var total_cnt = succ_cnt + fail_cnt + wait_cnt;
       	var exec_rate = succ_cnt / total_cnt * 100;
       	
       	$("#exec_body").append(last_tr);
       	$("#exec_rate").html(Math.round(exec_rate)+"%");
    } else {
    	var last_tr = '<tr>'
           	last_tr += '<td class="text-center" colspan="4">No Data.</td>';
           	last_tr += '</tr>';
           	
           	$("#exec_body").append(last_tr);
           	$("#exec_rate").html("0%");
    }
   	
   	$("#exec_date").html(toDay.yyyymmdd());
   	
   	Highcharts.chart('exec_chart', {
   	    chart: {
   	        type: 'column'
   	    },
   	    title: {
   	        text: '제어현황'
   	    },
   	    xAxis: {
   	        categories: types,
   	        crosshair: true
   	    },
   	    yAxis: {
   	    	allowDecimals: false,
   	        min: 0,
   	        title: {
   	            text: 'Count'
   	        }
   	    },
   	    tooltip: {
   	        headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
   	        pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
   	            '<td style="padding:5"><b>{point.y}</b></td></tr>',
   	        footerFormat: '</table>',
   	        shared: true,
   	        useHTML: true
   	    },
   	    series: [{
   	        name: '성공',
   	     	color: '#0009FF',
   	        data: succ
   	    }, {
   	        name: '실패',
   	        color: '#FF0900',
   	        data: fail
   	    }, {
   	        name: '대기',
   	     	color: '#FFE510',
   	        data: wait

   	    }]
   	});
   	
}

function removeZero(val){
	return val.replace(".0", "");
}
</script>
	<!--  wrapper -->
</body>
</html>