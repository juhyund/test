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
<script src="<%=COMMON_PATH_JS%>/bootstrap-datepicker.js?ver=1"></script>

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js?ver=22"></script>
<script src="https://cdn.jsdelivr.net/npm/sweetalert2@9"></script>
<script src="components/angular-sweetalert/SweetAlert.js"></script>


<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js?ver=00" charset="UTF-8"></script>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
<!-- <link href="css/plugins/awesome-bootstrap-checkbox/awesome-bootstrap-checkbox.css" rel="stylesheet"> -->



<script src="https://code.highcharts.com/highcharts.js"></script>
<script src="https://code.highcharts.com/modules/data.js"></script>
<script src="https://code.highcharts.com/modules/exporting.js"></script>
<script src="https://code.highcharts.com/modules/export-data.js"></script>
<script src="https://code.highcharts.com/modules/no-data-to-display.js"></script>

<!-- Additional files for the Highslide popup effect -->
<script src="https://www.highcharts.com/media/com_demo/js/highslide-full.min.js"></script>
<script src="https://www.highcharts.com/media/com_demo/js/highslide.config.js" charset="utf-8"></script>
<link rel="stylesheet" type="text/css" href="https://www.highcharts.com/media/com_demo/css/highslide.css" />



</head>
<body>
<!--  wrapper -->
<div id="content">
<div id="wrapper">
<div id="page-wrapper" style="width:100%" class="gray-bg" >
<!-- navigator -->
<div class="row wrapper page-heading" style="padding:5px">
<div class="col-lg-10" >
	<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> LP?????? - ?????? ????????? ??????</h2>
</div>
					
</div>
<!-- navigator -->
<!-- body -->
<div class="row">

	<div class="col-lg-12">	
		<div class="ibox">
			<div class="ibox-content">
					<!-- start :summary_area -->
					
				<div class="row m-b-md">
					<div>
	                    <div class="widget-left-color-box p-sm m-l-n-sm navy-bg">
	                        <div >
	                           <i class="fa fa-sitemap fa-5x"></i>
	                        </div>
	                	</div>
	                </div>
	                <div class=" gray-bg m-r-n-sm"   style="width:90%"> 
	                
		                <table class="table-borderless text-center m-t" style="width:100%" >
							<thead>
								<tr class="text-navy">
									<th>????????????</th>
									<th>????????????</th>
									<th>????????????</th>
									<th>??????????????????</th>
								</tr>
							</thead>
							<tbody>
								<tr>
									<td><h2 id = "meter_serial"></h2></td>
									<td><h2 id = "device_serial"></h2></td>
									<td><h2 id = "meter_type"></h2></td>
									<td><h2 id = "last_comm_dt"></h2></td>
								</tr>
							</tbody>
						</table>
					</div>
				</div>
				<!--  end : summary_area  -->
				
				<form name="search_form" id="search_form" method="post">
					<table class="table table-borderless"  style="width: 100%; margin-bottom: 7px;" border="1" >
						<tbody>
							<tr class="table-border">
								<td>
									<div class="form-group row">
										<label class="col-sm-2 col-form-label ">????????????</label>
			                            <div class="col-sm-6" id="datePicker">
											<div class="input-group date" style="width: 48%; float: left;">
												<input type="hidden" id="sdate" name="sdate" value=""> 
												<input type="text" class="form-control" id="sdateView" name="sdateView" value="${sdate}">
												<span class="input-group-addon" style="list-style: none;">
													<i class="fa fa-calendar"></i>
												</span>
											</div>
											<label class="col-form-label" style="width: 4%; float: left; text-align: center">~</label>
											<div class="input-group date" style="width: 48%;">
												<input type="hidden"  id="edate" name="edate" value=""> 
												<input type="text" class="form-control"  id="edateView" name="edateView" value="${edate}"> 
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
									<button class="btn btn-outline btn-primary" style="height: 100%; width: 50px" type="button" onclick="excelDownload();">
										<i class="fa fa-download"></i>
									</button>
								</td>
							</tr>
						</tbody>
					</table>
					<input type="hidden" id="meter_id" name="meter_id" value="${meter_id}" class="form-control">
				</form>
			  	<!-- <div class="text-center" style="padding-bottom:15px">
					<button class="btn btn-primary " type="button"><i class="fa fa-search"></i>&nbsp;&nbsp;<span class="bold">??????</span></button>
					<button class="btn btn-primary " type="button"><i class="fa fa-undo"></i>&nbsp;&nbsp;<span class="bold">????????????</span></button>
				</div>  -->       
				<div>
					<div class="ibox "  style="width:100%";>                      
	                    <div class="ibox-content text-center" style="min-height: 300px; overflow: hidden;">
	                    <center>
	                    <div id="chartContainer" style="min-width: 310px; height: 300px; margin: 0 auto"></div>	
	                    </center>                        
	                    
                    </div>
					<div id="grid" style="height:500px;" class="ag-theme-balham"></div>
					<div class="col-sm-12" style="text-align:center"> 
			        </div>
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
//var meter_id = $('#detail_meter_id').val();// ${meterId};
var channelName = new Array();
var channel_cnt = 0;
var colwidth = 70;

$(document).ready(function() {	
	init();
	
});

function init() {
	
	ajaxMeterInfoSummary();
	ajaxChannelList();

	initDate();
	
}
function initDate(){
	
	var initSdate = $("#sdateView").val();
	var initEdate = $("#edateView").val();
	
	setSearchParam2(initSdate,initEdate);
}

var columnDefs = [
//specify the columns  
	{headerName: "??????",		field: "no",		width:50,	suppressSizeToFit: true, pinned:"left"},
	{headerName: "????????????", 	field: "read_dt",	width:100,	suppressSizeToFit: true, pinned:"left"},
	{headerName: "???????????? ", 	field: "itime",		width:100,	suppressSizeToFit: true, pinned:"left"}	]
	
function useChannelList(data, status) {
	//????????? ???????????? ????????? ?????? ??????????????? ????????? ??????
	channel_cnt = data.resultGrid.length;
	var useSuppressSizeToFit = true;
	if(channel_cnt<=4){
		useSuppressSizeToFit = false;
	}
	
	for(i=0;i<channel_cnt;i++){
		//channelName[i]??? channel_idx??? i+1??? ?????? ?????????. 
		channelName[i] = data.resultGrid[i].channel_name;
		columnDefs.push({headerName: channelName[i], 
						field: "c"+(i+1)+"_metervalue",
						valueFormatter: numberFormatter,
						suppressSizeToFit: useSuppressSizeToFit,
						width:150,
						cellStyle: { 'text-align': "right" }});
	}
	
	//grid??????
	initGrid();
	ajaxSearchForm();
}

var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
    dataGrid.autoSizeAll();
};

function ajaxMeterInfoSummary() {
    var options = { 
           beforeSend  : showRequest,
           success     : loadMeterInfo,
           url         : COMMON_URL + "/ajaxMeterInfoSummary",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };            
    
     $.ajax(options);
}

function ajaxChannelList() {
    var options = { 
           beforeSend  : showRequest,
           success     : useChannelList, /*????????? ???????????? ????????? ?????? ??????????????? ????????? ??????*/
           url         : COMMON_URL + "/ajaxChannelList",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };
    
     $.ajax(options);
}

function ajaxSearchForm() {
	setSearchParam2($("#sdateView").val(), $("#edateView").val());

    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxMeterValueDetail",
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

function excelDownload() {
	setSearchParam2($("#sdateView").val(), $("#edateView").val());
	
	 $('#search_form').attr('action', COMMON_URL + "/downloadMeterValueDetail");
	 $('#search_form').attr('method',"GET");
	 $('#search_form').submit();
	Swal.fire({
		position: 'center',
		icon: 'info',
		text: 'excel ?????????',
		showConfirmButton: false,
			timer: 1500
	});

}

function showRequest() {
	// $("#loading").show();
}

function successResultHandler(data, status) {	
	//grid??? ????????? ?????? 
	dataGrid.setData(data.resultGrid);
	dataGrid.autoSizeAll();
	//chart??? ????????? ??????
	loadChart(data, status);
}

function loadMeterInfo(data, status) {	
	//????????? ???????????? ??????Info??? ??????
	var device_serial; 
	var meter_serial;
	var meter_type;
	var last_comm_dt; 
	
	device_serial = data.resultGrid[0].device_serial;
	meter_serial = data.resultGrid[0].meter_serial;
	meter_type = data.resultGrid[0].meter_type;
	last_comm_dt = data.resultGrid[0].last_comm_dt;
	
	$('#device_serial').text(device_serial);
	$('#meter_serial').text(meter_serial);
	$('#meter_type').text(meter_type);
	$('#last_comm_dt').text(last_comm_dt);
}

function loadChart(data, status){
	var format = '{value: %m/%d <br> %H:%M}';

	var chartOptions = {
		  chart: {
		    scrollablePlotArea: {
		      minWidth: 700
		    },
		    zoomType: "x"
		  },

		  title: {
		    text: ''
		  },
		  xAxis: {
			  	useHTML : true,
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
		      text: null
		    },
		    labels: {
		      align: 'left',
		      x: 3,
		      y: 16,
		      format: '{value:.,0f}'
		    },
		    showFirstLabel: false
		  }/* , { // right y axis
		    linkedTo: 0,
		    gridLineWidth: 0,
		    opposite: true,
		    title: {
		      text: null
		    },
		    labels: {
		      align: 'right',
		      x: -3,
		      y: 16,
		      format: '{value:.,0f}'
		    },
		    showFirstLabel: false
		  } */],
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
		      cursor: 'pointer',
		      //lineWidth: 1,
		      point: {
		        events: {
		          click: function (e) {
		            hs.htmlExpand(null, {
		              pageOrigin: {
		                x: e.pageX || e.clientX,
		                y: e.pageY || e.clientY
		              },
		              headingText: this.series.name,
		              maincontentText: Highcharts.dateFormat('%Y/%m/%d %H:%M', this.x) + '<br/> ' +
		                this.y ,
		              width: 200
		            });
		          }
		        }
		      },
		      marker: {
		        symbol   :"circle",
		        radius: 1.5
		        
		      }
		    }
		  },
		  series: createSeries(data)
		};
	
	
	function createSeries(data) {
		 var series = [];
		 var channelData = [[],[],[],[],[],[],[],[],[]];
		 
			 //????????? ?????? (??? ????????? ????????? ????????? ??????)
			 data.resultGrid.forEach(function(row){
				for(var i=0; i<channel_cnt; i++){
					var point = [];
					var pointData = "row.c"+(i+1)+"_metervalue";
					
					point.push(getTimeMilisec(row.read_dt_int.toString()));
					point.push(eval(pointData));
					
					channelData[i].push(point);
				}
			 })
			 //????????? ?????? (????????? ????????? ????????? ???????????? ??????)
			  for(var i=0; i<channel_cnt; i++){
				 series.push({
					 name : channelName[i],
					 data : channelData[i]
				 });
			  }	
			
		  return series;
	}
	//highcharts ??????
	Highcharts.chart('chartContainer', chartOptions);
	
}




</script>


<script>	
$('#datePicker .input-group.date').datepicker({
	todayBtn: "linked",	
	forceParse: false,
	autoclose: true
});


</script>
<!--  wrapper -->
</body>
</html>
