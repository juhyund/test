<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<%@ page import="com.nuri.kepco.config.CodeConstants" %>
<%@ include file="/commons/common_define.jsp"%>
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
<!-- Data picker -->
<script src="<%=COMMON_PATH_JS%>/bootstrap-datepicker.js"></script>

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">
<script src="https://cdn.jsdelivr.net/npm/sweetalert2@9"></script>

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>
<style>
	.rag-red-outer {
	    color: red;
	    font-weight: bold;
	}
	
	.rag-green-outer {
	    color: blue;
	    font-weight: bold;
	}
	
	.rag-grey-outer {
	    color: e3f704;
	    font-weight: bold;
	}
	.warning-red{
		background-color: red;
		border: solid 1px;
		font-size: 16px;
		font-weight: bold;
	}
	
	.warning-green{
		background-color: lightgreen;
		border: solid 1px;
		font-size: 16px;
		font-weight: bold;
	}
	
	.warning-yellow{
		background-color: yellow;
		border: solid 1px;
		font-size: 16px;
		font-weight: bold;
	}
	
	.warning-orange{
		background-color: orange;
		border: solid 1px;
		font-size: 16px;
		font-weight: bold;
	}
	
	.warning-grey{
		background-color: #b3b5b7;
		border: solid 1px;
		font-size: 16px;
		font-weight: bold;
	}
	
	.col-custom{
		position: relative;
	    width: max-content;
	    min-height: 1px;
	    padding-right: 7px;
	    padding-left: 7px;
	}	
	
	table#nmsCodeGuide {
	    border-collapse: collapse;   
	}
	
	#nmsCodeGuide tr {
	    background-color: #fff;
	}

	#nmsCodeGuide th {
	    background-color: #343a40;
	    font-weight: bold;
	    border: solid 1px;
	    color: white;
	}
	
	.td-custom {
		font-weight: bold;
		color: black;
	}
	
	.border-bottom-color {
		border-bottom: 0.5px solid white !important;
	}
	
	#nmsCodeGuide th, #nmsCodeGuide td {
	    padding: 3px 5px;
	    border: solid 1px;
	    text-align: center;
	}
	#nmsCodeGuide td {
	    color: #000;
	}
	
	.status {
		width: 80px;
	}
	.data {
		width: 160px;
	}	
	
</style>
<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>
<%-- <script src="<%=COMMON_PATH_JS%>/icheckbox.css"></script> --%>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
<link href="<%=COMMON_PATH_CSS%>/style.css?ver=1" rel="stylesheet">
</head>
<body>
<!--  wrapper -->
<div id="content">
<div id="wrapper">
<div id="page-wrapper" style="width:100%" class="gray-bg" >
<!-- navigator -->
<div class="row wrapper page-heading" style="padding:5px">
<div class="col-lg-10" >
	<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> NMS</h2>
</div>
<div class="col-lg-2" >
	<ol class="breadcrumb" style="float:right;margin-top:10px;">
		</ol>
	</div>						
</div>
<!-- navigator -->
<!-- body -->
<div class="row">

	<div class="col-lg-12">	
		<div class="ibox">
			<div class="ibox-content">
				<form name="search_form" id="search_form" method="post">
				<input type="hidden" id="limit" name="limit" value ="15" class="form-control">
				<input type="hidden" id="page" name="page" value ="1" class="form-control" onchange="ajaxSearchForm()">
				<table class="table table-borderless" style="height: 100%;" style="margin-bottom: 7px;" border="1">
					<tbody>
						<tr class="table-border">
							<td>
								<div class="form-group row">
									<label class="col-lg-1 col-form-label" style="padding-left: 10px;">지역본부</label>
									<div class="col-lg-3">
										<select class="form-control" style="width: 49%; display: inline;" name="branch_parent_id" id="branch_parent_id" onchange="changeParent()"></select>
										<select class="form-control" style="width: 49%; vertical-align: top; display: inline;" name="branch_id" id="branch_id">
											<option value=''>선택</option>
										</select>
									</div>
									<label class="col-lg-1 col-form-label" style="padding-left: 10px;">모뎀상태</label>
									<div class="col-custom">
										<select class="form-control" name="device_status" id="device_status" style="width: max-content;">
											<option value=''>선택</option>
												<% for(CodeConstants.DEVICE_STAT ds : CodeConstants.DEVICE_STAT.values()){ %> 
											<option value='<%= ds.getDcodeId() %>'><%= ds.getDescr()%></option>
												<% }%>
										</select>
									</div>
									<label class="col-sm-1 col-form-label" style="padding-left: 10px; text-align: center;">검색</label>
									<div class="col-custom">
										<select class="form-control" name="searchfield" id="searchfield" style="width: 29%; display: inline;">
											<option value=''>선택</option>
											<!-- <option value='deviceId'>모뎀ID</option> -->
											<option value='deviceSerial'>모뎀 번호</option>
										</select>
										<input type="text" class="form-control" name="searchquery" id="searchquery" style="width: 69%; height: 33px; vertical-align: top; display: inline;">
									</div>
									<!-- <label class="col-lg-1 col-form-label" style="padding-left: 10px;">모뎀모델</label>
									<div class="col-lg-3">
										<select class="form-control" name="model_seq" id="model_seq"></select>
									</div> -->
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
				</form>
				<form name="detail_form" id="detail_form" method="get" action="deviceControlDetail">
					<input type="hidden" id="detail_control_seq" name="detail_control_seq" class="form-control">
				</form>
				<div>
					<!-- NMS 상태값 -->
					<div>
						<table id="nmsCodeGuide" style="display: none;">
						<tr>
						    <th class="status" style="border-left: solid 1px #000; border-top: solid 1px #000">상태</th>
						    <th class="data" style="border-right: solid 1px #000; border-top: solid 1px #000">CPU/Memory</th>
						    <th style="width: 70px; background-color: white; border-right: solid 1px #000;"></th>
						    <th class="status" style="border-left: solid 1px #000; border-top: solid 1px #000">상태</th>
						    <th class="data" style="border-top: solid 1px #000">RSRP(dBm)</th>
						    <th class="data" style="border-top: solid 1px #000">RSRQ(dB)</th>
						    <th class="data" style="border-right: solid 1px #000; border-top: solid 1px #000">SNR(dB)</th>
						</tr>
						<tr>
						    <td class="warning-green td-custom">정상</td>
						    <td><= 50%</td>
						    <td class="border-bottom-color"></td>
						    <td class="warning-green td-custom">정상</td>
						    <td>>= (-80)</td>
						    <td>>= (-10)</td>
						    <td>>= (20)</td>
						</tr>
						<tr>
						    <td class="warning-yellow td-custom">양호</td>
						    <td>50% to 70%</td>
						    <td class="border-bottom-color"></td>
						    <td class="warning-yellow td-custom">양호</td>
						    <td>(-80) to (-90)</td>
						    <td>(-10) to (-15)</td>
						    <td>(13) to (20)</td>
						</tr>
						<tr>
						    <td class="warning-orange td-custom">경고</td>
						    <td>70% to 90%</td>
						    <td class="border-bottom-color"></td>
						    <td class="warning-orange td-custom">약함</td>
						    <td>(-90) to (-100)</td>
						    <td>(-15) to (-20)</td>
						    <td>(0) to (13)</td>
						</tr>
						<tr>
						    <td class="warning-red td-custom">위험</td>
						    <td>90% to 100%</td>
						    <td class="border-bottom-color"></td>
						    <td class="warning-red td-custom">불량</td>
						    <td><=(-100)</td>
						    <td><(-20)</td>
						    <td><=(0)</td>
						</tr>
						<tr>
						    <td class="warning-grey td-custom"></td>
						    <td>null or ""</td>
						    <td class="border-bottom-color"></td>
						    <td class="warning-grey td-custom"></td>
						    <td>null or ""</td>
						    <td>null or ""</td>
						    <td>null or ""</td>
						</tr>
						</table>
					</div>
					
					<!-- page option -->
					<div class="row m-t-n-n" style="margin:-1px"  >
						<div style="width :100%;vertical-align:center">
							<label id="cur_page_num" class="col-form-label"></label>
							<div style ="float:right;margin-bottom:5px;width: 330px;">
								<button class="btn btn-outline btn-primary" style ="float:left;" onclick="onBtShowCodeGuide()">(도움말) 코드 상태값 가이드</button>
								<select id="data_per_page" class="form-control" name="data_per_page" style ="float:right;width: fit-content;" onchange="javascript:changeLimit(this);">
									<option value=15 selected>15개씩</option>
									<option value=100>100개씩 </option>
									<option value=250>250개씩 </option>
								</select>
							</div>
						</div>
					</div>
					
					<!-- grid -->
					<div id="grid" style="height:510px;" class="ag-theme-balham"></div>
					
					<!-- grid pagination -->
					<div id="grid-page" style ="display:none;" class="m-t-sm">
							<ul id="pagination" class="pagination"></ul>
					</div>
		        </div>
		        
			   </div>
			              
			</div>
		</div>
	</div>
</div>
<!-- body -->
</div>
</div>	

<script type="text/javascript" charset="utf-8">	

//specify the columns
var columnDefs = [
	{headerName: "번호", field: "no", width:50,	suppressSizeToFit: true, pinned:"left"},
	{headerName: "모뎀번호", field: "deviceSerial",suppressSizeToFit: true, pinned:"left"},
	{headerName: "모뎀상태", field: "deviceStatusNm",suppressSizeToFit: true, width:140, pinned:"left",
		 cellClassRules: {
	            'rag-green-outer': function(params) { return params.value == '정상'},
	            'rag-grey-outer': function(params) { return params.value == '대기중'},
	            'rag-red-outer': function(params) { return params.value == '등록해제'}
	        }},
	{headerName: "_모뎀번호", field: "deviceId", hide:"true"},
	{headerName: "본부", field: "parentBranchNm", width:200,	suppressSizeToFit: true},
	{headerName: "지사", field: "branchNm", width:100,	suppressSizeToFit: true},
	{headerName: "CPU(%)", field: "cpuUsage", width:150,
		cellStyle:{'text-align': "right"},
		cellClassRules: {
			'warning-green': function(params) { return params.value <= 50 && params.value != null},
            'warning-yellow': function(params) { return params.value > 50 && params.value <= 70},
            'warning-orange': function(params) { return params.value > 70 && params.value <= 90},
            'warning-red': function(params) { return params.value > 90 && params.value != null},
            'warning-grey': function(params) { return params.value == null || params.value == ""}
        }
    },
	{headerName: "Memory(%)", field: "ramUsage", width:170,
    	cellStyle:{'text-align': "right"},
		cellClassRules: {
            'warning-green': function(params) { return params.value <= 50 && params.value != null},
            'warning-yellow': function(params) { return params.value > 50 && params.value <= 70},
            'warning-orange': function(params) { return params.value > 70 && params.value <= 90},
            'warning-red': function(params) { return params.value > 90 && params.value != null},
            'warning-grey': function(params) { return params.value == null || params.value == ""}
        }
    },
	{headerName: "RSRP(dBm)", field: "rsrp", width:150,
    	cellStyle:{'text-align': "right"},
   		cellClassRules: {
               'warning-green': function(params) { return params.value >= -80 && params.value != null},
               'warning-yellow': function(params) { return params.value < -80 && params.value >= -90},
               'warning-orange': function(params) { return params.value < -90 && params.value > -100},
               'warning-red': function(params) { return params.value <= -100 && params.value != null},
               'warning-grey': function(params) { return params.value == null || params.value == ""}
           }
    },
	{headerName: "RSRQ(dB)", field: "rsrq", width:150,
    	cellStyle:{'text-align': "right"},
   		cellClassRules: {
               'warning-green': function(params) { return params.value >= -10 && params.value != null},
               'warning-yellow': function(params) { return params.value < -10 && params.value >= -15},
               'warning-orange': function(params) { return params.value < -15 && params.value >= -20},
               'warning-red': function(params) { return params.value < -20 && params.value != null},
               'warning-grey': function(params) { return params.value == null || params.value == ""}
           }
    },
	{headerName: "SNR(dB)", field: "ssnr", width:150,
    	cellStyle:{'text-align': "right"},
   		cellClassRules: {
               'warning-green': function(params) { return params.value >= 20 && params.value != null},
               'warning-yellow': function(params) { return params.value >= 13 && params.value < 20},
               'warning-orange': function(params) { return params.value > 0 && params.value < 13},
               'warning-red': function(params) { return params.value <= 0 && params.value != null},
               'warning-grey': function(params) { return params.value == null || params.value == ""}
           }
    },
	{headerName: "최종 통신일자", field: "usageTime", width:150,suppressSizeToFit: true},
	{headerName: "등록일자", field: "saveTime", width:150,suppressSizeToFit: true}
];

//device type
function comboDeviceType() {
	var combo = [ 'ajaxParentBranchCombo', 'ajaxDeviceModelCombo' ];
	for (var i = 0; i < combo.length; i++) {
		var options = { 
	           beforeSend  : showRequest,
	           success     : successResultCombo,
	           url         : COMMON_URL + "/" + combo[i],
	           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
	           type        : "post", /* get, post */
	           dataType    : "json", /* xml, html, script, json */
	           data        : $("#search_form").serialize()
	     };             
	     $.ajax(options);
	}
	
}

function successResultCombo(data, status) {
	$.each(data, function(nm, combo) {
		$('#'+nm).append(new Option("선택", ""));
		$.each(data[nm], function(key, value){
			$('#'+nm).append(new Option(value, key));
		});
	});
}

function changeParent() {
	var sel_obj = document.getElementById('branch_id');
    for(var i=0; i<sel_obj.options.length; i++) sel_obj.options[i] = null;
    sel_obj.options.length = 0;

	var options = { 
	           beforeSend  : showRequest,
	           success     : successResultCombo,
	           url         : COMMON_URL + "/ajaxBranchCombo",
	           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
	           type        : "post", /* get, post */
	           dataType    : "json", /* xml, html, script, json */
	           data        : $("#search_form").serialize()
	     };             
	    
	     $.ajax(options);
}

var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500, true);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};

function ajaxSearchForm() {
	//setSearchParam($("#sdateView").val(), $("#edateView").val());
	
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

function excelDownload() {

	$('#search_form').attr('action', COMMON_URL + "/downloadNMSList");
	$('#search_form').attr('method',"GET");
	$('#search_form').submit();
	Swal.fire({
		position: 'center',
		icon: 'info',
		text: 'excel 생성중',
		showConfirmButton: false,
			timer: 1500
	});
}

//grid row click
onRowClicked = function(event){
	var deviceSerial = event.data.deviceSerial;
	var deviceId = event.data.deviceId;
	var usageTime = event.data.usageTime;
	var deviceStatusNm = event.data.deviceStatusNm;
	location.href = CONTEXT_PATH + "/NMSDetail?deviceSerial="+deviceSerial+"&deviceId="
			+deviceId+"&usageTime="+usageTime+"&deviceStatusNm="+deviceStatusNm;
}

function onBtShowCodeGuide() {
	$("#nmsCodeGuide").toggle();	
}

/* 
var winObj;
function showDetailWindow(device_id){ 
	var opts="width=900, height=800,left=200, top=200, resizable=no, toolbar=yes"; 

	if(winObj)
        winObj.close();
    winObj = window.open(COMMON_URL+"/deviceControlDetail?detail_control_seq="+detail_control_seq, "", opts);
} */


function resetForm(){
	$("#search_form")[0].reset();
	setSearchPeriod('today');
};


function showRequest() {
	// $("#loading").show();
}

function successResultHandler(data, status) {
	var dataPerPage = $("#limit").val();
	var currentPage = $("#page").val();
	
	dataGrid.setData(data.resultGrid);
	gridPage(data.totalCount, dataPerPage, 10, currentPage);
    dataGrid.autoSizeAll();
}

function init() {
	
	// init
	initGrid();
	
	// combo
	comboDeviceType();
	
	// form search
	ajaxSearchForm();
	
	//$("#limit").val($("#search_num option:selected").val());
}
function setLimit(obj){
	$("#limit").val(obj.value);
}
	
$(document).ready(function() {	
	init();
	
	
});
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