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
	<h3 style="margin-top:6px">?????? ?????? ????????????</h3>
</div>
<div class="col-lg-2" >
	<ol class="breadcrumb" style="float:right;margin-top:10px;">
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
					<table class="table text-center m-t" style="width:100%; height:200px" >
						<tbody>
							<tr>
								<th class="text-navy" scope="row">??????????????????</th><!-- ?????????????????? -->
								<td id = "control_seq_view"> ${control_seq}</td>
								<th class="text-navy" scope="row">???????????????</th><!--???????????????-->
								<td id = "service_cd"></td>
								<th class="text-navy" scope="row">?????????????????? ID</th><!-- ??????????????????????????? -->
								<td id = "app_id"></td>
							</tr>
							<tr>
								<th class="text-navy" scope="row">?????? ID</th><!-- ??????????????? -->
								<td id = "device_id"></td>
								<th class="text-navy" scope="row">??????????????????</th><!-- ?????????????????? -->
								<td id = "reg_id"></td>
								<th class="text-navy" scope="row">????????? ??????</th><!-- ??????????????? -->
								<td id = "resource_path"></td>
							</tr>
							<tr>
								<th class="text-navy" scope="row">????????????</th><!-- ???????????? -->
								<td id = "control_type"></td>
								<th class="text-navy" scope="row">????????????</th><!-- ???????????? -->
								<td id = "reg_dt"></td>
								<th class="text-navy" scope="row">????????????</th><!-- ???????????? -->
								<td id = "status_cd"></td>
							</tr>
							<tr>
								<th class="text-navy" scope="row">?????? ??????</th><!-- ???????????? -->							
								<td id = "success_yn"></td>
								<th class="text-navy" scope="row">??????????????????</th><!-- ?????????????????? -->
								<td id = "result_dt"></td>
								<th class="text-navy" scope="row">???????????????</th><!-- ??????????????? -->
								<td id = "status_msg"></td>
							</tr>
							<tr>
								<th class="text-navy" scope="row">???????????????</th><!-- ??????????????? -->
								<td id = "request_msg" colspan="5" style="text-align: left;"></td>
							</tr>
							<tr>
								<th class="text-navy" scope="row">????????????<br>???????????????</th><!-- ??????????????????????????? -->
								<td id = "result_msg" colspan="5" style="text-align: left;"></td>
							</tr>
							
						</tbody>
					</table>
				<form name="control_detail_form" id="control_detail_form" method="post">
					<input type="hidden" id="control_seq" name="control_seq" value="${control_seq}" class="form-control">
				</form>
				</div>
				<!--  end : summary_area  -->

			   <button class="btn btn-outline btn-primary m-t-sm" style="height: 100%; float: right" type="button" onclick="javascript:history.back(-1)">
					<i class="fa fa-undo"> ???????????? ????????????</i>
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
	{headerName: "??????", field: "no", width:80},
	{headerName: "????????? ID", field: "resource_id"},
	{headerName: "????????? ???", field: "resource_name"},
	{headerName: "??????????????????", field: "instance"},
	{headerName: "??????", field: "mandatory"},
	{headerName: "????????? ??????", field: "type"},
	{headerName: "??????", field: "descr", width:250}
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
	//??????
	
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

	success_yn = (success_yn==1) ? "??????" : "??????";
	
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
var control_sequence;

function init() {
	
	// init
	control_sequence = $("#control_seq").val();
	
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