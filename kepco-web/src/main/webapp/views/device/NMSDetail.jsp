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
	.chart-container-left{
		width: 49.2%;
		float: left;
		margin: 2px 3px;
		margin-right: 10px;
	}
	
	.chart-container-right{
		width: 49.2%;
		float: left;
		margin: 2px 0px;
	}
	
	.long-chart-container-left{
		width: 99%;
		float: left;
    	margin: 10px 0px 2px 3px;
	}
	
	#search_form {
		margin-left: 5px;
	}
	
	#contentsFrame {
		min-height: 1500px !important;
	}
	
	.iframe100 {   display: block;   border: none;   height: 100vh;   width: 100vw; }

	
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
	<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> NMS ????????????</h2>
</div>
<div class="col-lg-2" >
	<ol class="breadcrumb" style="float:right;margin-top:10px;">
		</ol>
	</div>						
</div>
<!-- navigator -->
<!-- body -->
<div style="width:100%">

	<div class="col-lg-12">	
		<div>
				<!-- start :summary_area -->
				<div class="row m-b-md " style="background: white; margin-bottom: 10px;">
					<div>
	                    <div class="widget-left-color-box p-sm m-l-n-sm navy-bg">
	                        <div >
	                           <i class="fa fa-cubes fa-5x"></i>
	                        </div>
	                	</div>
	                </div>
	                <div class="col-lg-6 "> 
		                <table class="table-borderless text-center m-t" style="width:100%" >
							<thead>
								<tr class="text-navy">
									<th>????????????</th>
									<!-- <th>??????ID</th> -->
									<th>????????????<th>
								</tr>
							</thead>
							<tbody>
								<tr>
									<td><h2>${deviceSerial}</h2></td>
									<%-- <td><h3>${deviceId}</h3></td> --%>
									<td><h2>${deviceStatusNm}</h2></td>
								</tr>
							</tbody>
						</table>
					</div>
				</div>
				<!--  end : summary_area  -->
				<form name="search_form" id="search_form" method="post" style="margin-left: 0px">
				<input type="hidden" id="limit" name="limit" value ="10" class="form-control">
				<input type="hidden" id="page" name="page" value ="1" class="form-control" onchange="ajaxSearchForm()">
					<table class="table table-borderless ibox-content"  style="width: 99.3%; margin-bottom: 7px;" border="1" >
						<tbody>
							<tr class="table-border">
								<td>
									<div class="form-group row">
										<label class="col-sm-2 col-form-label" style="text-align: center">????????????</label>
			                            <div class="col-sm-6" id="datePicker">
											<div class="input-group date" style="width: 48%; float: left;">
												<input type="hidden" id="sdate" name="sdate" value=""> 
												<input type="text" class="form-control" id="sdateView" name="sdateView" value="">
												<span class="input-group-addon" style="list-style: none;">
													<i class="fa fa-calendar"></i>
												</span>
											</div>
											<label class="col-form-label" style="width: 4%; float: left; text-align: center">~</label>
											<div class="input-group date" style="width: 48%;">
												<input type="hidden"  id="edate" name="edate" value=""> 
												<input type="text" class="form-control"  id="edateView" name="edateView" value=""> 
												<span class="input-group-addon" style="list-style: none;">
													<i class="fa fa-calendar"></i>
												</span>
											</div>
										</div>
										<div class="col-sm-4 btn-group">
											<button type="button" class="btn btn-outline btn-primary" clicked onclick="setSearchPeriod('today')">??????</button>
											<button type="button" class="btn btn-outline btn-primary" onclick="setSearchPeriod('weekly')">??????</button>
											<button type="button" class="btn btn-outline btn-primary" onclick="setSearchPeriod('montly')">??????</button>
			                            </div>
									</div>
								</td>
								<td width="180" style="text-align: right">
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
					<input type="hidden" id="deviceSerial" name="deviceSerial" value="${deviceSerial}" class="form-control">
					<input type="hidden" id="usageTime" name="usageTime" value="${usageTime}" class="form-control">
				</form>
				
				<div id="loading">
					<div id="loading-image" class="spinner-border" role="status">
						<img id="loading-image" src="<%=COMMON_PATH_IMG%>/loading.gif" alt="Loading..." /></div>
					</div>
				</div>
				<div>								
				   <!-- chart -->
				   <div style="overflow: hidden;">
		    		   <div class="chart-container-left" id="cpuContainer"></div>
		    		   <div class="chart-container-right" id="ramContainer"></div>
		    	    </div>
		    	    <div style="overflow: hidden;">
		    		   <div class="long-chart-container-left" id="rsrpContainer"></div>
		    		   <div class="long-chart-container-left" id="rsrqContainer"></div>
		    		   <div class="long-chart-container-left" id="snrContainer"></div>
		    		</div>   
			    </div>        
				<button class="btn btn-outline btn-primary m-t-sm" style="height: 100%; float: right;" type="button" onclick="javascript:history.back(-1)">
					<i class="fa fa-undo"> ???????????? ????????????</i>
				</button>
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
	setSearchParam2($("#sdateView").val(), $("#edateView").val());
	
    var options = { 
           beforeSend  : showLoading,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxNMSDetail",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function resetForm(){
	setSearchPeriod('today');	
};

function successResultHandler(data, status) {
	//chart rendering
	renderChart(data, status)
}
	
function renderChart(data, status){
	var format = '{value: %H:%M}';
	var change1 = {
	    '-60': '??????',
	    '-70': '??????',
	    '-80': '??????',
	    '-90': '??????'
	};
	var rsrpChartOptions = {
		  chart: {
			borderColor: '#BDC3C7',
			borderWidth: 1,
		    scrollablePlotArea: {
		      minWidth: 500
		    },
		    zoomType: "x",
		  },
		  credits: {
		    enabled: false
		  },
		  title: {
		    text: 'RSRP(dBm)'
		  },
		  xAxis: {
				type: 'datetime',
				labels: {
					format: format,
				},
				//minTickInterval: interval,
				ordinal: false //this sets the fixed time formats 
			
			}, 

		  yAxis: [{ // left y axis
		    title: {
		      text: 'Reference Signal Received Power'
		    },
		    labels: {
		      align: 'left',
		      x: 3,
		      y: 16,
		      format: '{value:.,0f}'
		    },
		    showFirstLabel: false,
		    max: -60, min: -100,
		    lineWidth: 2,
		  }, 
		    {
		      labels: {
			      formatter: function() {
			          var value = change1[this.value];
			          return value !== 'undefined' ? value : this.value;
			      },
				  align: 'right',
		      	  x: -3,
		          y: 16,
		      	  format: '{value:.,0f}'
			  },
		      title: {
		        text: ''			      
		      },
		      showFirstLabel: false,
		      max: -60, min: -100,
		      opposite:true
	        }],
		  lang: {
		        noData: "No data to Display"
		  },
		  legend: {
		    align: 'center',
		    verticalAlign: 'bottom',
		    borderWidth: 0
		  },
	 
		  tooltip: {
		    shared: true
		  },

		  plotOptions: {
		    series: {
		    	marker: {
		            enabled: true,
		            symbol: 'circle',
		            radius: 2
		        },
		      cursor: 'pointer',
		      lineWidth: 3,
		   	  color: '#0b6623'
		    }
		  },
		  series: rsrpCreateSeries(data)
		};
	var change2 = {
	    '0': '??????',
	    '-5': '??????',
	    '-10': '??????',
	    '-15': '??????'
	};
	var rsrqChartOptions = {
			  chart: {
			    borderColor: '#BDC3C7',
				borderWidth: 1,
			    scrollablePlotArea: {
			      minWidth: 500
			    },
			    zoomType: "x"
			  },
			  credits: {
			    enabled: false
			  },
			  title: {
			    text: 'RSRQ(dB)'
			  },
			  xAxis: {
					type: 'datetime',
					labels: {
						format: format,
					},
					//minTickInterval: interval,
					ordinal: false //this sets the fixed time formats 
				
				}, 

			  yAxis: [{ // left y axis
			    title: {
			      text: 'Reference Signal Received Quality'
			    },
			    labels: {
			      align: 'left',
			      x: 3,
			      y: 16,
			      format: '{value:.,0f}'
			    },
			    showFirstLabel: false,
			    max: 0, min: -20,
			    lineWidth: 2,
			  }, 
			    {
			      labels: {
				      formatter: function() {
				          var value = change2[this.value];
				          return value !== 'undefined' ? value : this.value;
				      },
					  align: 'right',
			      	  x: -3,
			          y: 16,
			      	  format: '{value:.,0f}'
				  },
			      title: {
			        text: ''			      
			      },
			      showFirstLabel: false,
			      max: 0, min: -20,
			      opposite:true
		        }],
			  lang: {
			        noData: "No data to Display"
			  },
			  legend: {
			    align: 'center',
			    verticalAlign: 'bottom',
			    borderWidth: 0
			  },
		 
			  tooltip: {
			    shared: true
			  },

			  plotOptions: {
			    series: {
			    	marker: {
			            enabled: true,
			            symbol: 'circle',
			            radius: 2
			        },
			      cursor: 'pointer',
			      lineWidth: 3,
			   	  color: '#0b6623'
			    }
			  },
			  series: rsrqCreateSeries(data)
			};
	var change3 = {
	    '40': '??????',
	    '30': '??????',
	    '20': '??????',
	    '10': '??????'
	};
	var snrChartOptions = {
			  chart: {
			    borderColor: '#BDC3C7',
				borderWidth: 1,
			    scrollablePlotArea: {
			      minWidth: 500
			    },
			    zoomType: "x"
			  },
			  credits: {
			    enabled: false
			  },
			  title: {
			    text: 'SNR(dB)'
			  },
			  xAxis: {
					type: 'datetime',
					labels: {
						format: format,
					},
					//minTickInterval: interval,
					ordinal: false //this sets the fixed time formats 
				
				}, 

			  yAxis: [{ // left y axis
			    title: {
			      text: 'Signal to Interference Noise Ratio'
			    },
			    labels: {
			      align: 'left',
			      x: 3,
			      y: 16,
			      format: '{value:.,0f}'
			    },
			    showFirstLabel: false,
			    max: 40, min: 0,
			    lineWidth: 2,
			  }, 
			    {
			      labels: {
				      formatter: function() {
				          var value = change3[this.value];
				          return value !== 'undefined' ? value : this.value;
				      },
					  align: 'right',
			      	  x: -3,
			          y: 16,
			      	  format: '{value:.,0f}'
				  },
			      title: {
			        text: ''			      
			      },
			      showFirstLabel: false,
			      max: 40, min: 0,
			      opposite:true
		        }],
			  lang: {
			        noData: "No data to Display"
			  },
			  legend: {
			    align: 'center',
			    verticalAlign: 'bottom',
			    borderWidth: 0
			  },
		 
			  tooltip: {
			    shared: true
			  },

			  plotOptions: {
			    series: {
			    	marker: {
			            enabled: true,
			            symbol: 'circle',
			            radius: 2
			        },
			      cursor: 'pointer',
			      lineWidth: 3,
			   	  color: '#0b6623'
			    }
			  },
			  series: snrCreateSeries(data)
			};
	var change = {
	    25: '??????',
	    50: '??????',
	    75: '??????',
	    100: '??????'
	};
	var cpuChartOptions = {
			  chart: {
				borderColor: '#BDC3C7',
				borderWidth: 1,
			    scrollablePlotArea: {
			      minWidth: 500
			    },
			    zoomType: "x"
			  },
			  credits: {
			    enabled: false
			  },
			  title: {
			    text: 'CPU(%)'
			  },
			  xAxis: {
					type: 'datetime',
					labels: {
						format: format,
						overflow: 'justify'
						
					},
					//minTickInterval: interval,
					ordinal: false //this sets the fixed time formats 
				
				}, 

			  yAxis: [{ // left y axis
			    title: {
			      text: 'CPU Usage Monitor'			      
			    },
			    labels: {
			      align: 'left',
			      x: 3,
			      y: 16,
			      format: '{value:.,0f}'
			    },
			      showFirstLabel: false,
			      lineWidth: 2,
			      max: 100, min: 0
				}, 
			    {
			      labels: {
				      formatter: function() {
				          var value = change[this.value];
				          return value !== 'undefined' ? value : this.value;
				      },
					  align: 'right',
			      	  x: -3,
			          y: 16,
			      	  format: '{value:.,0f}'
				  },
			      title: {
			        text: ''			      
			      },
			      showFirstLabel: false,
			      max: 100, min: 0,
			      opposite:true
		        }],
			  lang: {
			        noData: "No data to Display"
			  },
			  legend: {
			    align: 'center',
			    verticalAlign: 'bottom',
			    borderWidth: 0
			  },
		 
			  tooltip: {
			    shared: true
			  },

			  plotOptions: {
			    series: {
			    	marker: {
			            enabled: true,
			            symbol: 'circle',
			            radius: 2
			        },
			      cursor: 'pointer',
			      lineWidth: 3,
			   	  color: '#0b6623'
			    }
			  },
			  series: cpuCreateSeries(data)
			}
	
	var ramChartOptions = {
			  chart: {
			  	borderColor: '#BDC3C7',
				borderWidth: 1,
			    scrollablePlotArea: {
			      minWidth: 500
			    },
			    zoomType: "x"
			  },
			  credits: {
			    enabled: false
			  },
			  title: {
			    text: 'MEMORY(%)'
			  },
			  xAxis: {
					type: 'datetime',
					labels: {
						format: format,
						overflow: 'justify'
						
					},
					//minTickInterval: interval,
					ordinal: false //this sets the fixed time formats 
				
				}, 

			  yAxis: [{ // left y axis
			    title: {
			    	text: 'RAM Usage Monitor'
			    },
			    labels: {
			      align: 'left',
			      x: 3,
			      y: 16,
			      format: '{value:.,0f}'
			    },
			    showFirstLabel: false,
			    lineWidth: 2,
			    max: 100, min: 0
			  }, 
			    {
			      labels: {
				      formatter: function() {
				          var value = change[this.value];
				          return value !== 'undefined' ? value : this.value;
				      },
					  align: 'right',
			      	  x: -3,
			          y: 16,
			      	  format: '{value:.,0f}'
				  },
			      title: {
			        text: ''			      
			      },
			      showFirstLabel: false,
			      max: 100, min: 0,
			      opposite:true
		        }],
			  lang: {
			        noData: "No data to Display"
			  },
			  legend: {
			    align: 'center',
			    verticalAlign: 'bottom',
			    borderWidth: 0
			  },
		 
			  tooltip: {
			    shared: true
			  },

			  plotOptions: {
			    series: {
			    	marker: {
			            enabled: true,
			            symbol: 'circle',
			            radius: 2
			        },
			      cursor: 'pointer',
			      lineWidth: 3,
			   	  color: '#0b6623'
			    }
			  },
			  series: ramCreateSeries(data)
			};
		
	
	function rsrpCreateSeries(data) {
		 var series = [];
		 var rsrpChannelData = [];
		 var rsrqChannelData = [];
		 var ssnrChannelData = [];
		 
			 //????????? ?????? (??? ????????? ????????? ????????? ??????)
			 $.each( data, function(index, item) {
				if(index == 'connectivityList'){
					for(var i=0; i<item.length; i++){
						if(item[i].rsrp.getOwnPropertyNames = "rsrp"){
							var point = [];
							var pointData = item[i].rsrp;
							
							point.push(getTimeMilisec(item[i].usageTime.substr(0, 14)));
							point.push(item[i].rsrp);
							
							rsrpChannelData.push(point);			
						} 
					}
				}
			});
			 
			 
			 //????????? ?????? (????????? ????????? ????????? ???????????? ??????)
			 series.push({
				 name : 'RSRP',
				 lineWidth: 2,
				 data : rsrpChannelData,
				 zoneAxis: 'y',
		         zones: [{value: -90, color: 'red'}, {value: 80, color: '#ff7f00'}, {value: 70, color: '#ffd740'}, {value: 60}]
			 });
			
		  return series;
	}
	
	function rsrqCreateSeries(data) {
		 var series = [];
		 var rsrpChannelData = [];
		 var rsrqChannelData = [];
		 var ssnrChannelData = [];
		 
			 //????????? ?????? (??? ????????? ????????? ????????? ??????)
			 $.each( data, function(index, item) {
				if(index == 'connectivityList'){
					for(var i=0; i<item.length; i++){
						if(item[i].rsrq.getOwnPropertyNames = "rsrq"){
							var point = [];
							var pointData = item[i].rsrq;
							
							point.push(getTimeMilisec(item[i].usageTime.substr(0, 14)));
							point.push(item[i].rsrq);
							
							rsrqChannelData.push(point);
						}
					}
				}
			});
			 
			 
			 //????????? ?????? (????????? ????????? ????????? ???????????? ??????)
			 series.push({
				 name : 'RSRQ',
				 lineWidth: 2,
				 data : rsrqChannelData,
				 zoneAxis: 'y',
		         zones: [{value: -15, color: 'red'}, {value: -10, color: '#ff7f00'}, {value: -5, color: '#ffd740'}, {value: 0}]
			 });
			
		  return series;
	}
	
	function snrCreateSeries(data) {
		 var series = [];
		 var rsrpChannelData = [];
		 var rsrqChannelData = [];
		 var ssnrChannelData = [];
		 
			 //????????? ?????? (??? ????????? ????????? ????????? ??????)
			 $.each( data, function(index, item) {
				if(index == 'connectivityList'){
					for(var i=0; i<item.length; i++){
						if(item[i].ssnr.getOwnPropertyNames = "ssnr"){
							var point = [];
							var pointData = item[i].ssnr;
							
							point.push(getTimeMilisec(item[i].usageTime.substr(0, 14)));
							point.push(item[i].ssnr);
							
							ssnrChannelData.push(point);
						}
					}
				}
			});
			 
			 //????????? ?????? (????????? ????????? ????????? ???????????? ??????)
			 series.push({
				 name : 'SNR',
				 lineWidth: 2,
				 data : ssnrChannelData,
				 zoneAxis: 'y',
		         zones: [{value: 10, color: 'red'}, {value: 20, color: '#ff7f00'}, {value: 30, color: '#ffd740'}, {value: 40}]
			 });
			
		  return series;
	}
	
	function cpuCreateSeries(data) {
		 var series = [];
		 var cpuChannelData = [];
		 
			 //????????? ?????? (??? ????????? ????????? ????????? ??????)
			 $.each( data, function(index, item) {
				if(index == 'cpuUsageList'){
					for(var i=0; i<item.length; i++){
							var point = [];
							var pointData = item[i].cpuUsage;
							
							point.push(getTimeMilisec(item[i].usageTime.substr(0, 14)));
							point.push(item[i].cpuUsage);
							
							cpuChannelData.push(point);			
					} 
				}
				
			});
			 
			 //????????? ?????? (????????? ????????? ????????? ???????????? ??????)
			 series.push({
				 name : 'CPU',
				 data : cpuChannelData,
				 zoneAxis: 'y',
				 zones: [{value: 50}, {value: 70, color: '#ffd740'}, {value: 90, color: '#ff7f00'}, {value: 100, color: 'red'}]
			 });
			
		  return series;
	}
	
	function ramCreateSeries(data) {
		 var series = [];
		 var ramChannelData = [];
		 
			 //????????? ?????? (??? ????????? ????????? ????????? ??????)
			 $.each( data, function(index, item) {
				if(index == 'ramUsageList'){
					for(var i=0; i<item.length; i++){
							var point = [];
							var pointData = item[i].ramUsage;
							
							point.push(getTimeMilisec(item[i].saveTime.substr(0, 14)));
							point.push(item[i].ramUsage);
							
							ramChannelData.push(point);			
					} 
				}
			});
			 
			 
			 //????????? ?????? (????????? ????????? ????????? ???????????? ??????)
			 series.push({
				 name : 'RAM',
				 data : ramChannelData,
				 zoneAxis: 'y',
		         zones: [{value: 50}, {value: 70, color: '#ffd740'}, {value: 90, color: '#ff7f00'}, {value: 100, color: 'red'}]
			 });
			
		  return series;
	}
	var color = [ '#0b6623', '#ffd740', '#ff7f00', 'red' ];
	var color1 = [ 'red', '#ff7f00', '#ffd740', '#0b6623' ];
	//highcharts ??????
	Highcharts.chart('rsrpContainer', rsrpChartOptions, function(chart){
		lineColor('rsrpContainer', color1)
	});
	Highcharts.chart('rsrqContainer', rsrqChartOptions, function(chart){
		lineColor('rsrqContainer', color1)
	});
	Highcharts.chart('snrContainer', snrChartOptions, function(chart){
		lineColor('snrContainer', color1)
	});
	Highcharts.chart('cpuContainer', cpuChartOptions, function(chart){
		lineColor('cpuContainer', color)
	});
	Highcharts.chart('ramContainer', ramChartOptions, function(chart){
		lineColor('ramContainer', color)
	});
	var div = [ '#rsrpContainer', '#rsrqContainer', '#snrContainer' ];
	for(var len = 0 ; len < div.length ; len++){
		$(div[len]).highcharts().reflow();
	}
	hideLoading();
}	

function lineColor(id, color) {
	
	var cnt = 0;
	for(var j = 0 ; j < 2 ; j++) {
		for(var i = 1 ; i <= color.length ; i++){
			$('#' + id +' .highcharts-yaxis-grid .highcharts-grid-line')[(i + cnt)].setAttribute('stroke', color[(i-1)]);
		}
		cnt = 5;
	}
}

function initDate() {

	var initSdate = $("#sdateView").val();
	var initEdate = $("#edateView").val();

	setSearchParam2(initSdate, initEdate);
}	
	
function init() {
	
	// init
	setSearchPeriod('today');
	
	// form search
	ajaxSearchForm();
	
}
	
$(document).ready(function() {	
	init();
});
</script>

<script>	
$('#datePicker .input-group.date').datepicker({
	todayBtn: "linked",	
	forceParse: false,
	autoclose: true,
	todayHighlight: true,
	format: "yyyy/mm/dd",
	language: "kr"
});
</script>
</body>
</html>