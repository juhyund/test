<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<%@ page import="com.nuri.kepco.config.CodeConstants" %>
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

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>
<style>
  select.form-control {
		width: fit-content;
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
						<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> SW 관리 이력</h2>
					</div>
					<div class="col-lg-2">
						<ol class="breadcrumb" style="float: right; margin-top: 10px;">
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
												<td height="80">
													<div class="form-group row">
														<label class="col-sm-1 col-form-label" style="padding-left: 10px;">모뎀 번호</label>
														<div class="col-lg-3">
															<input type="text" class="form-control" name="device_serial" id="device_serial" style="height: 33px; vertical-align: top; display: inline;">
														</div>
														<label class="col-sm-1 col-form-label" style="padding-left: 10px;">실행 상태</label>
														<div class="col-lg-3">
															<select class="form-control" name="fw_issue_status" id="fw_issue_status" style="width: 100%; margin-right: 45px;">
																<option value=''>선택</option>
																<% for(CodeConstants.FW_STATUS ds : CodeConstants.FW_STATUS.values()){ %> 
																<option value='<%= ds.name() %>'><%= ds.getDescr()%></option>
																<% }%>
															</select>
														</div>
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">실행 일시</label>
														<div class="col-lg-3" id="datePicker">
														<div class="input-group date"
															style="width: 48%; float: left;">
															<input type="hidden" class="form-control" id="sdate" name="sdate" value="">
															<input type="text" class="form-control" id="sdateView" name="sdateView" value="">
															<span class="input-group-addon" style="list-style: none;">
																<i class="fa fa-calendar"></i>
															</span>
														</div>
														<label class="col-form-label" style="width: 4%; float: left; text-align: center">~</label>
														<div class="input-group date" style="width: 48%;">
															<input type="hidden" class="form-control"  id="edate" name="edate" value=""> 
															<input type="text" class="form-control" id="edateView" name="edateView" value="">
															<span class="input-group-addon" style="list-style: none;">
																<i class="fa fa-calendar"></i>
															</span>
														</div>
													</div>
													</div>

													<div class="form-group form-group-end row">
														<label class="col-lg-1 col-form-label" style="padding-left: 10px;">SW 파일</label>
														<div class="col-lg-3">
															<input type="text" class="form-control" name="fw_file_nm" id="fw_file_nm" style="height: 33px; vertical-align: top; display: inline;">
														</div>
														<label class="col-lg-1 col-form-label" style="padding-left: 10px;">SW 버전</label>
														<div class="col-lg-3">
															<input type="text" class="form-control" name="fw_version" id="fw_version" style="height: 33px; vertical-align: top; display: inline;">
														</div>
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">성공 일시</label>
														<div class="col-sm-3" id="datePicker">
															<div class="input-group date" style="width: 48%; float: left;">
																<input type="text" class="form-control" id="usdate" name="usdate" value="">
																<span class="input-group-addon" style="list-style: none;">
																	<i class="fa fa-calendar"></i>
																</span>
															</div>
															<label class="col-form-label" style="width: 4%; float: left; text-align: center">~</label>
															<div class="input-group date" style="width: 48%;">
																<input type="text" class="form-control" id="uedate" name="uedate" value="">
																<span class="input-group-addon" style="list-style: none;">
																	<i class="fa fa-calendar"></i>
																</span>
															</div>
														</div>
													</div>
												</td>
												<td width="130" height="80" style="text-align: right">
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
									<!-- page option -->
									<div class="row m-t-n-n" style="margin:-1px"  >
										<div style="width :100%;vertical-align:center" class="m-t-n-sm">
											<label id="cur_page_num" class="col-form-label"></label>
											<div style ="float:right; margin-bottom:5px">
												<select id="data_per_page" class="form-control" name="data_per_page" onchange="javascript:changeLimit(this);">
													<option value=15 selected>15개씩</option>
													<option value=100>100개씩 </option>
													<option value=250>250개씩 </option>
												</select>
											</div>
										</div>
									</div>
									<!-- grid -->
									<div id="grid" style="height:490px;" class="ag-theme-balham"></div>
									
									<!-- grid pagination -->
									<div id="grid-page" style ="display:none;" class="m-t-sm">
										<ul id="pagination" class="pagination"></ul>
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

//specify the columns
var columnDefs = [
	{headerName: "번호", field: "no", width:100, cellStyle:{'text-align': "center"}},	
	{headerName: "모뎀 번호", field: "device_serial", cellStyle:{'text-align': "center"}},
	{headerName: "SW 파일", field: "fw_file_nm", cellStyle:{'text-align': "center"}},
	{headerName: "SW 버전", field: "fw_version", cellStyle:{'text-align': "center"}},
	{headerName: "트랜잭션ID", field: "tid", cellStyle:{'text-align': "center"}},
	{headerName: "실행 일시", field: "fw_write_dt", cellStyle:{'text-align': "center"}},
	{headerName: "SW 실행 상태", field: "fw_issue_status_nm", cellStyle:{'text-align': "center"}},
	{headerName: "요청자", field: "reg_id", cellStyle:{'text-align': "center"}}		
];

// init selectComboBox

var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};

// grid row click
 onRowClicked = function(event){
	var device_id = event.data.device_id;
}

function ajaxSearchForm() {
	setSearchParam2($("#sdateView").val(), $("#edateView").val());
    var options = { 
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxFirmwareHistoryList",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function successResultHandler(data, status) {	
	var dataPerPage = $("#limit").val();
	var currentPage = $("#page").val();
	
	dataGrid.setData(data.resultGrid);
	gridPage(data.totalCount, dataPerPage, 10, currentPage);
}

function resetForm() {
	$('#device_serial').val("");
	$("#fw_issue_status").val($("#target option:first").val());
	$("#fw_file_nm").val("");
	$("#fw_version").val("");
	setSearchPeriod('thisMonth');
	setSearchParam2($("#sdateView").val(), $("#edateView").val());
	$("#usdate").val("");
	$("#uedate").val("");
}


function init() {
	// Grid
	initGrid();
	
	setSearchPeriod('thisMonth');
	
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