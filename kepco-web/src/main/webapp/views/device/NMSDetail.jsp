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
<link href="<%=COMMON_PATH_CSS%>/style.css?ver=a" rel="stylesheet">

<!-- Mainly scripts -->
<script src="<%=COMMON_PATH_JS%>/jquery-3.1.1.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/popper.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/bootstrap.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.metisMenu.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.slimscroll.min.js"></script>
<!-- Data picker -->
<script src="<%=COMMON_PATH_JS%>/bootstrap-datepicker.js"></script>

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>

<!-- Highcharts -->
<script src="https://code.highcharts.com/highcharts.js"></script>
<script src="https://code.highcharts.com/highcharts-more.js"></script>
<script src="https://code.highcharts.com/modules/data.js"></script>
<script src="https://code.highcharts.com/modules/series-label.js"></script>
<script src="https://code.highcharts.com/modules/exporting.js"></script>
<script src="https://code.highcharts.com/modules/export-data.js"></script>
<script src="https://code.highcharts.com/modules/no-data-to-display.js"></script>
<script src="https://code.highcharts.com/modules/solid-gauge.js"></script>
<script src="https://code.highcharts.com/modules/accessibility.js"></script>

<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
<style>
  .highcharts-figure .chart-container {
		width: 300px;
		height: 200px;
		float: left;
	}
	
	.highcharts-figure, .highcharts-data-table table {
		width: 600px;
		height: 200px;
		margin: 0 auto;
	}
	
	.highcharts-line, .highcharts-data-table table {
	    min-width: 360px; 
	    max-width: 600px;
	    height: 400px;
	    margin: 1em auto;
	}
	
	.highcharts-data-table table {
	    font-family: Verdana, sans-serif;
	    border-collapse: collapse;
	    border: 1px solid #EBEBEB;
	    margin: 10px auto;
	    text-align: center;
	    width: 100%;
	    max-width: 500px;
	}
	.highcharts-data-table caption {
	    padding: 1em 0;
	    font-size: 1.2em;
	    color: #555;
	}
	.highcharts-data-table th {
		font-weight: 600;
	    padding: 0.5em;
	}
	.highcharts-data-table td, .highcharts-data-table th, .highcharts-data-table caption {
	    padding: 0.5em;
	}
	.highcharts-data-table thead tr, .highcharts-data-table tr:nth-child(even) {
	    background: #f8f8f8;
	}
	.highcharts-data-table tr:hover {
	    background: #f1f7ff;
	}
	
	@media (max-width: 600px) {
		.highcharts-figure, .highcharts-data-table table {
			width: 100%;
		}
		.highcharts-figure .chart-container {
			width: 300px;
			float: none;
			margin: 0 auto;
		}
	
	}
	
</style>
<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
<!-- <link href="css/plugins/awesome-bootstrap-checkbox/awesome-bootstrap-checkbox.css" rel="stylesheet"> -->
</head>
<body>
<!--  wrapper -->
<div id="content">
<div id="wrapper">
<div id="page-wrapper" style="width:100%" class="gray-bg" >
<!-- navigator -->
<div class="row wrapper page-heading" style="padding:5px">
<div class="col-lg-10" >
	<h3 style="margin-top:6px">NMS 상세정보 </h3>
</div>
<div class="col-lg-2" >
	<ol class="breadcrumb" style="float:right;margin-top:10px;">
		<li class="breadcrumb-item">
			<a href="http://webapplayers.com/inspinia_admin-v2.9.2/index.html">Home</a>
		</li>
		<li class="breadcrumb-item active">
			<strong>Layouts</strong>
		</li>
		</ol>
	</div>						
</div>
<!-- navigator -->
<!-- body -->
<div style="width:100%">

	<div class="col-lg-12">	
		<div class="ibox">
			<div class="ibox-content">
					<!-- start :summary_area -->
					
				<%-- <div class="row m-b-md ">
					<div>
	                    <div class="widget-left-color-box p-sm m-l-n-sm navy-bg">
	                        <div >
	                           <i class="fa fa-cubes fa-5x"></i>
	                        </div>
	                	</div>
	                </div>
	                <div class=" gray-bg  col-lg-6 "> 
		                <table class="table-borderless text-center m-t" style="width:100%" >
							<thead>
								<tr class="text-navy">
									<th>제어관리번호</th>
									<th>띠용<th>
									<th>인스턴스 구분</th>
									<th>필수여부</th>
								</tr>
							</thead>
							<tbody>
								<tr>
									<td><h1>${control_seq}</h1></td>
									<td><h1>${object_name}</h1></td>
									<td><h1>${instance}</h1></td>
									<td><h1>${mandatory}</h1></td>
								</tr>
							</tbody>
						</table>
					</div>
					
				</div> --%>
				<!--  end : summary_area  -->
				
				<form name="search_form" id="search_form" method="post">
				<input type="hidden" id="limit" name="limit" value ="10" class="form-control">
				<input type="hidden" id="page" name="page" value ="1" class="form-control" onchange="ajaxSearchForm()">
				<table class="table table-borderless" style="height: 100%;" style="margin-bottom: 7px;" border="1">
					<tbody>
						<tr class="table-border">
							<td height="80">
								<div class="form-group row">
									<label class="col-lg-1 col-form-label" style="padding-left: 10px;">지역본부</label>
									<div class="col-lg-3">
										<select class="form-control" style="width: 49%; display: inline;" name="branch_parent_id" id="branch_parent_id" onchange="changeParent()"></select>
										<select class="form-control" style="width: 49%; vertical-align: top; display: inline;" name="branch_id" id="branch_id">
											<option value=''>선택</option>
										</select>
									</div>
									<label class="col-lg-1 col-form-label" style="padding-left: 10px;">단말모델</label>
									<div class="col-lg-3">
										<select class="form-control" name="model_seq" id="model_seq"></select>
									</div>
								</div>

								<div class="form-group form-group-end row">
									<label class="col-sm-1 col-form-label" style="padding-left: 10px;">검색</label>
									<div class="col-lg-3">
										<select class="form-control" name="searchfield" id="searchfield" style="width: 29%; display: inline;">
											<option value=''>선택</option>
											<option value='deviceId'>단말ID</option>
											<option value='deviceSerial'>단말 번호</option>
										</select>
										<input type="text" class="form-control" name="deviceSerial" id="deviceSerial" style="width: 69%; height: 33px; vertical-align: top; display: inline;">
									</div>
													
									<label class="col-sm-1 col-form-label">검색 일자</label>
									<div class="col-sm-3" id="datePicker">
										<div class="input-group date" style="width: 48%; float: left;">
											<input type="text" class="form-control" id="lsdate" name="lsdate"value=""> 
											<span class="input-group-addon" style="list-style: none;">
												<i class="fa fa-calendar"></i>
											</span>
										</div>
										<label class="col-form-label" style="width: 4%; float: left; text-align: center">~</label>
										<div class="input-group date" style="width: 48%;">
											<input type="text" class="form-control"  id="ledate" name="ledate" value=""> 
											<span class="input-group-addon" style="list-style: none;">
												<i class="fa fa-calendar"></i>
											</span>
										</div>
									</div>
								</div>
							</td>
							<td width="180" height="80" style="text-align: right">
								<button class="btn btn-primary" style="height: 100%; width: 50px" type="button" onclick="ajaxSearchForm();">
									<i class="fa fa-search"></i>
								</button>
								<button class="btn btn-warning" style="height: 100%; width: 50px" type="button" onclick="resetForm();">
									<i class="fa fa-undo"></i>
								</button>
							</td>
						</tr>
					</tbody>
				</table>	
				</form>
				<div>								
				   <!-- chart -->
				   <figure class="highcharts-figure">
					   <div id="container-CPU" class="chart-container"></div>
		    		   <div id="container-RAM" class="chart-container"></div>
		    	   </figure>
				   <figure class="highcharts-line">
		    		   <div id="container" style="overflow: inherit !important;"></div>
		    	    </figure>
				   <button class="btn btn-outline btn-primary m-t-sm" style="height: 100%" type="button" onclick="javascript:history.back(-1)">
						<i class="fa fa-undo"> 목록으로 돌아가기</i>
					</button>
			    </div>        
			</div>
		</div>
	</div>
</div>
<!-- body -->
</div>
</div>	
</div>

<script type="text/javascript" charset="utf-8">	

var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};

function ajaxSearchForm() {

    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxNMSList",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function resetForm(){
	$("#search_form")[0].reset();
	
};

function showRequest() {
	// $("#loading").show();
}

function successResultHandler(data, status) {
	
	/* $.each( data, function(index, item) {
		if(index == 'ramUsageList'){
			for(var i=0; i<item.length; i++){
				setInterval(item[i].ramUsage);			
			}
		}
		
	}); */	
}

//gauge chart
var gaugeOptions = {
	    chart: {
	        type: 'solidgauge'
	    },

	    title: null,

	    pane: {
	        center: ['50%', '85%'],
	        size: '120%',
	        startAngle: -90,
	        endAngle: 90,
	        background: {
	            backgroundColor:
	                Highcharts.defaultOptions.legend.backgroundColor || '#EEE',
	            innerRadius: '60%',
	            outerRadius: '100%',
	            shape: 'arc'
	        }
	    },

	    exporting: {
	        enabled: false
	    },

	    tooltip: {
	        enabled: false
	    },

	    // the value axis
	    yAxis: {
	        stops: [
	            [0.1, '#55BF3B'], // green
	            [0.5, '#DDDF0D'], // yellow
	            [0.9, '#DF5353'] // red
	        ],
	        lineWidth: 0,
	        tickWidth: 0,
	        minorTickInterval: null,
	        tickAmount: 2,
	        title: {
	            y: -70
	        },
	        labels: {
	            y: 16
	        }
	    },

	    plotOptions: {
	        solidgauge: {
	            dataLabels: {
	                y: 5,
	                borderWidth: 0,
	                useHTML: true
	            }
	        }
	    }
	};

	// The speed gauge
	var chartSpeed = Highcharts.chart('container-CPU', Highcharts.merge(gaugeOptions, {
	    yAxis: {
	        min: 0,
	        max: 100,
	        title: {
	            text: 'CPU'
	        }
	    },

	    credits: {
	        enabled: false
	    },

	    series: [{
	        name: 'CPU',
	        data: [80],
	        dataLabels: {
	            format:
	                '<div style="text-align:center">' +
	                '<span style="font-size:25px">{y}</span><br/>' +
	                '<span style="font-size:12px;opacity:0.4">CPU Usage</span>' +
	                '</div>'
	        },
	        tooltip: {
	            valueSuffix: ' CPU Usage'
	        }
	    }]

	}));

	// The RPM gauge
	var chartRpm = Highcharts.chart('container-RAM', Highcharts.merge(gaugeOptions, {
	    yAxis: {
	        min: 0,
	        max: 100,
	        title: {
	            text: 'Memory'
	        }
	    },

	    series: [{
	        name: 'Memory',
	        data: [1],
	        dataLabels: {
	            format:
	                '<div style="text-align:center">' +
	                '<span style="font-size:25px">{y}</span><br/>' +
	                '<span style="font-size:12px;opacity:0.4">' +
	                'Ram Usage' +
	                '</span>' +
	                '</div>'
	        },
	        tooltip: {
	            valueSuffix: ' Ram Usage'
	        }
	    }]

	}));

	// Bring life to the dials
	setInterval(function () {
	    // Speed
	    var point,
	        newVal,
	        inc;

	    if (chartSpeed) {
	        point = chartSpeed.series[0].points[0];
	        inc = data;
	        /* inc = Math.round((Math.random() - 0.5) * 100); */
	        newVal = point.y + inc;

	        if (newVal < 0 || newVal > 100) {
	            newVal = point.y - inc;
	        }

	        point.update(newVal);
	    }

	    // RPM
	    if (chartRpm) {
	        point = chartRpm.series[0].points[0];
	        inc = Math.round((Math.random() - 0.5) * 100);
	        newVal = point.y + inc;

	        if (newVal < 0 || newVal > 100) {
	            newVal = point.y - inc;
	        }

	        point.update(newVal);
	    }
	}, 2000);
	
	//line chart
	function getData(n) {
	    var arr = [],
	        i,
	        x,
	        a,
	        b,
	        c,
	        spike;
	    for (
	        i = 0, x = Date.UTC(new Date().getUTCFullYear(), 0, 1) - n * 36e5;
	        i < n;
	        i = i + 1, x = x + 36e5
	    ) {
	        if (i % 100 === 0) {
	            a = 2 * Math.random();
	        }
	        if (i % 1000 === 0) {
	            b = 2 * Math.random();
	        }
	        if (i % 10000 === 0) {
	            c = 2 * Math.random();
	        }
	        if (i % 50000 === 0) {
	            spike = 10;
	        } else {
	            spike = 0;
	        }
	        arr.push([
	            x,
	            2 * Math.sin(i / 100) + a + b + c + spike + Math.random()
	        ]);
	    }
	    return arr;
	}
	var n = 5000,
	    data = getData(n);


	console.time('line');
	Highcharts.chart('container', {

	    chart: {
	        zoomType: 'x'
	    },

	    title: {
	        text: 'COMPARISON OF RSRP, RSRQ, SNR'
	    },

	   /*  subtitle: {
	        text: 'Using the Boost module'
	    }, */

	    tooltip: {
	        valueDecimals: 2
	    },

	    xAxis: {
	        type: 'datetime'
	    },

	    series: [{
	        data: data,
	        lineWidth: 0.5,
	        name: 'Hourly data points'
	    }]

	});
	console.timeEnd('line');	

function init() {
	
	// init
	//initGrid();
	
	// form search
	//ajaxSearchForm();
}
	
$(document).ready(function() {	
	init();
});
</script>
<!-- 

<script>	
$('#datePicker .input-group.date').datepicker({
	todayBtn: "linked",	
	forceParse: false,
	autoclose: true
});


</script> -->
<!--  wrapper -->
</body>
</html>