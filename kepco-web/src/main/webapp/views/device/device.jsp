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
  	
</style>
<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>

<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
</head>
<body>
	<!--  wrapper -->
	<div id="content">
		<div id="wrapper">
			<div id="page-wrapper" style="width: 100%" class="gray-bg">
				<!-- navigator -->
				<div class="row wrapper page-heading" style="padding: 5px">
					<div class="col-lg-10">
						<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> ?????? ?????? ??????</h2>
					</div>
					<div class="col-lg-2">
						<ol class="breadcrumb" style="float: right; margin-top: 10px;">
						</ol>
					</div>
				</div>
				<!-- navigator -->
				<!-- body -->
				<div class="row" style="width: 100%">
					<div class="col-lg-12">
						<div class="ibox">
							<div class="ibox-content">
								<form name="search_form" id="search_form" method="post">
								<input type="hidden" id="limit" name="limit" value ="15" class="form-control">
								<input type="hidden" id="page" name="page" value ="1" class="form-control" onchange="ajaxSearchForm()">
								<table class="table table-borderless" style="height: 100%; style="margin-bottom: 7px;" border="1">
									<tbody>
										<tr class="table-border">
											<td height="80" style="padding-right: 0px;">
												<div class="form-group row">
													<label class="col-lg-1 col-form-label">????????????</label>
													<div class="col-lg-3">
														<select class="form-control" style="width: 49%; display: inline;" name="branch_parent_id" id="branch_parent_id" onchange="changeParent()"></select>
														<select class="form-control" style="width: 49%; vertical-align: top; display: inline;" name="branch_id" id="branch_id">
															<option value=''>??????</option>
														</select>
													</div>
													<label class="col-sm-1 col-form-label">SW ??????</label>
													<div class="col-lg-3">
														<input type="text" class="form-control" name="fw_version" id="fw_version" style="height: 33px; vertical-align: top; display: inline;">
													</div>
													<!-- <label class="col-lg-1 col-form-label" style="padding-left: 10px;">????????????</label>
													<div class="col-lg-3">
														<select class="form-control" name="model_seq" id="model_seq"></select>
													</div> -->
													<label class="col-sm-1 col-form-label">????????????</label>
													<div class="col-sm-3" id="datePicker">
														<div class="input-group date" style="width: 48%; float: left;">
															<input type="text" class="form-control" id="sdate" name="sdate"value=""> 
															<span class="input-group-addon" style="list-style: none;">
																<i class="fa fa-calendar"></i>
															</span>
														</div>
														<label class="col-form-label" style="width: 4%; float: left; text-align: center">~</label>
														<div class="input-group date" style="width: 48%;">
															<input type="text" class="form-control"  id="edate" name="edate" value=""> 
															<span class="input-group-addon" style="list-style: none;">
																<i class="fa fa-calendar"></i>
															</span>
														</div>
													</div>
												</div>

												<div class="form-group form-group-end row">
													<label class="col-sm-1 col-form-label">??????</label>
													<div class="col-lg-3">
														<select class="form-control" name="searchfield" id="searchfield" style="width: 29%; display: inline;">
															<option value=''>??????</option>
															<!-- <option value='device_id'>??????ID</option> -->
															<option value='device_serial'>?????? ??????</option>
														</select>
														<input type="text" class="form-control" name="searchquery" id="searchquery" style="width: 69%; height: 33px; vertical-align: top; display: inline;">
													</div>
													
													<label class="col-lg-1 col-form-label">????????????</label>
													<div class="col-lg-3">
														<select class="form-control" name="device_status" id="device_status">
															<option value=''>??????</option>
															<% for(CodeConstants.DEVICE_STAT ds : CodeConstants.DEVICE_STAT.values()){ %> 
															<option value='<%= ds.getDcodeId() %>'><%= ds.getDescr()%></option>
															<% }%>
														</select>
													</div>
													
													<label class="col-sm-1 col-form-label">????????????</label>
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
											<td width="180" height="80" style="text-align: right; padding-left: 0px;">
												<button class="btn btn-primary" style="height: 96%; width: 50px" type="button" onclick="ajaxSearchForm();">
													<i class="fa fa-search"></i>
												</button>
												<button class="btn btn-warning" style="height: 96%; width: 50px" type="button" onclick="resetForm();">
													<i class="fa fa-undo"></i>
												</button>
												<button class="btn btn-outline btn-primary" style="height: 96%; width: 50px" type="button" onclick="excelDownload();">
													<i class="fa fa-download"></i>
												</button>
											</td>
										</tr>
									</tbody>
								</table>

								</form>
								<div>
									<!-- page option -->
									<div class="row m-t-n-n" style="margin:-1px"  >
										<div style="width :100%;vertical-align:center" class="m-t-n-sm">
											<label id="cur_page_num" class="col-form-label"></label>
											<div style ="float:right; margin-bottom:5px">
												<select id="data_per_page" class="form-control" name="data_per_page" onchange="javascript:changeLimit(this);">
													<option value=15 selected>15??????</option>
													<option value=100>100?????? </option>
													<option value=250>250?????? </option>
												</select>
											</div>
										</div>
									</div>
									<!-- grid -->
									<div id="grid" style="height:490px;" class="ag-theme-balham"></div>
									
									<!-- grid pagination -->
									<center>
									<div id="grid-page" style ="display:none;" class="m-t-sm">
										<ul id="pagination" class="pagination"></ul>
									</div>
									</center>
						        </div>
							</div>
						</div>
					</div>
				</div>
				
				<!-- body -->

<script type="text/javascript" charset="utf-8">

//specify the columns
var columnDefs = [
	{headerName: "??????", field: "no", width:80},
	{headerName: "????????????", field: "device_serial"},
	{headerName: "??????", field: "parent_branch_nm"},
	{headerName: "??????", field: "branch_nm"},
	/* {headerName: "????????????", field: "model_nm"}, */
	{headerName: "SW ??????", field: "fw_version"},
	{headerName: "?????????", field: "vendor_nm"},
	{headerName: "????????????", field: "code_local_nm",
        cellClassRules: {
            'rag-green-outer': function(params) { return params.value == '??????'},
            'rag-grey-outer': function(params) { return params.value == '?????????'},
            'rag-red-outer': function(params) { return params.value == '????????????'}
        }},
	{headerName: "??????????????????", field: "last_comm_dt"},
	{headerName: "????????????", field: "reg_dt"}
];

var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};

onRowClicked = function(event){
	var device_id = event.data.device_id;
	location.href = CONTEXT_PATH + "/deviceDetail?device_id="+device_id;
}

function ajaxSearchForm() {
    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxDeviceInfoList",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function excelDownload() {
	$('#search_form').attr('action', COMMON_URL + "/downloadDevicelist");
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
	var dataPerPage = $("#limit").val();
	var currentPage = $("#page").val();
	
	dataGrid.setData(data.resultGrid);
	gridPage(data.totalCount, dataPerPage, 10, currentPage);
}

// device type
function comboDeviceType() {
	//var combo = [ 'ajaxParentBranchCombo', 'ajaxDeviceModelCombo' ];
	var combo = [ 'ajaxParentBranchCombo' ];
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
		$('#'+nm).append(new Option("??????", ""));
		$.each(data[nm], function(key, value){
			$('#'+nm).append(new Option(value, key));
		});
	});
}

function resetForm() {
	
	var today = new Date();
	var settingDate = new Date();
	settingDate.setMonth(today.getMonth());
	settingDate.setDate(1);

	$('#sdate').datepicker('setDate', null);
	$('#edate').datepicker('setDate', null);
	$("#lsdate").datepicker( "setDate", settingDate);
	$("#ledate").datepicker( "setDate", today);
	$("#branch_parent_id").val($("#target option:first").val());
	$("#branch_id").val($("#target option:first").val());
	//$("#model_seq").val($("#target option:first").val());
	$("#fw_version").val("");
	$("#searchfield").val($("#target option:first").val());
	$("#device_status").val($("#target option:first").val());
	$("#searchquery").val("");
}

function init() {
	
	// init
	initGrid();
	
	var today = new Date();
	var settingDate = new Date();
	settingDate.setMonth(today.getMonth());
	settingDate.setDate(1);

	$("#lsdate").datepicker( "setDate", settingDate);
	$("#ledate").datepicker( "setDate", today);
	
	// form search
	ajaxSearchForm();
	
	// combo
	comboDeviceType();	
}
	
$(document).ready(function() {	
	init();
});

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

