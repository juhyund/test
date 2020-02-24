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

<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>

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
	<h3 style="margin-top:6px">계기 상세 정보</h3>
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
<div >

	<div class="col-lg-12">	
		<div class="ibox">
			<div class="ibox-content">
					<!-- start :summary_area -->
					
				<div class="row m-b-md ">
					<div class="col-lg-6">
                    <div class="tabs-container">
                        <ul class="nav nav-tabs" role="tablist">
                            <li><a class="nav-link active" data-toggle="tab" href="#tab-1">기본정보</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-2">미터 설정 읽기/설정</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-3">OBIS 제어</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-4">TOU설정 조회</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-5">제어이력</a></li>
                        </ul>
                        <div class="tab-content">
                            <div role="tabpanel" id="tab-1" class="tab-pane active">
                                <div class="panel-body">
									<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
                                </div>
                            </div>
                            <div role="tabpanel" id="tab-2" class="tab-pane">
                                <div class="panel-body">
                                	<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
                                </div>
                            </div>
                            <div role="tabpanel" id="tab-3" class="tab-pane">
                                <div class="panel-body">
									<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
                                </div>
                            </div>
                            <div role="tabpanel" id="tab-4" class="tab-pane">
                                <div class="panel-body">
									<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
                                </div>
                            </div>
                            <div role="tabpanel" id="tab-5" class="tab-pane">
                                <div class="panel-body">
									<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
                                </div>
                            </div>
                        </div>
                   		 </div>
                	</div>
				<form name="control_detail_form" id="control_detail_form" method="post">
					<input type="hidden" id="control_seq" name="control_seq" value="${control_seq}" class="form-control">
				</form>
				</div>
				<!--  end : summary_area  -->

			   <button class="btn btn-outline btn-primary m-t-sm" style="height: 100%" type="button" onclick="javascript:history.back(-1)">
					<i class="fa fa-undo"> 목록으로 돌아가기</i>
				</button>
			              
			</div>
		</div>
	</div>
</div>
<!-- body -->
</div>
</div>	
</div>

<script type="text/javascript" charset="utf-8">	

//specify the columns  
var columnDefs = [
	{headerName: "번호", field: "no", width:80},
	{headerName: "리소스 ID", field: "resource_id"},
	{headerName: "리소스 명", field: "resource_name"},
	{headerName: "인스턴스구분", field: "instance"},
	{headerName: "필수", field: "mandatory"},
	{headerName: "데이터 타입", field: "type"},
	{headerName: "비고", field: "descr", width:250}
];

/* var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};
*/ 
function ajaxSearchForm() {

    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxDeviceControlListDetail",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#control_detail_form").serialize()
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
	//로딩
	
	var service_cd = data.result[0].service_cd;
	var app_id = data.result[0].app_id;
	var resource_path = data.result[0].resource_path;
	var control_type = data.result[0].control_type;
	var request_msg = data.result[0].request_msg;
	var reg_id = data.result[0].reg_id;
	var reg_dt = data.result[0].reg_dt;
	var success_yn = data.result[0].success_yn;
	var status_cd = data.result[0].status_cd;
	var status_msg = data.result[0].status_msg;
	var result_dt = data.result[0].result_dt;
	var result_msg = data.result[0].result_msg;

	success_yn = (success_yn==1) ? "성공" : "실패";
	
	$('#service_cd').text(service_cd);
	$('#app_id').text(app_id);
	$('#resource_path').text(resource_path);
	$('#control_type').text(control_type);
	$('#request_msg').text(request_msg);
	$('#reg_id').text(reg_id);
	$('#reg_dt').text(reg_dt);
	$('#success_yn').text(success_yn);
	$('#status_cd').text(status_cd);
	$('#status_msg').text(status_msg);
	$('#result_dt').text(result_dt);
	$('#result_msg').text(result_msg);
	
}
var meter_serial = event.data.meter_serial;

function init() {
	
	// initGrid
	var initGrid = function() {
	    dataGrid = new DataGrid('grid', columnDefs, true, 500);    
	    dataGrid.makeGrid();
	    dataGrid.showNoRows();
	};
	
	// form search
	ajaxSearchForm();
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