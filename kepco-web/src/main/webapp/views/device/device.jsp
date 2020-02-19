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
						<h3 style="margin-top: 6px">단말 목록 조회</h3>
					</div>
					<div class="col-lg-2">
						<ol class="breadcrumb" style="float: right; margin-top: 10px;">
							<li class="breadcrumb-item"><a
								href="http://webapplayers.com/inspinia_admin-v2.9.2/index.html">Home</a>
							</li>
							<li class="breadcrumb-item active"><strong>Layouts</strong>
							</li>
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
								<input type="hidden" id="limit" name="limit" value ="10" class="form-control">
								<input type="hidden" id="page" name="page" value ="1" class="form-control" onchange="ajaxSearchForm()">
									<table class="table table-borderless" style="height: 100%;" style="margin-bottom: 7px;" border="1">
										<tbody>
											<tr class="table-border">
												<td height="80">
													<div class="form-group row">
														<label class="col-lg-1 col-form-label">단말명</label>
														<div class="col-lg-3">
															<input type="text" class="form-control">
														</div>
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">단말시리얼</label>
														<div class="col-lg-3">
															<input type="text" class="form-control">
														</div>
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">단말구분</label>
														<div class="col-lg-3">
															<select class="form-control" name="device_type"
																id="device_type"></select>
														</div>
													</div>

													<div class="form-group form-group-end row">
														<label class="col-sm-1 col-form-label">등록일자</label>
														<div class="col-sm-3" id="datePicker">
															<div class="input-group date"
																style="width: 48%; float: left;">
																<input type="text" class="form-control" id="sdate" name="sdate"
																	value=""> <span
																	class="input-group-addon" style="list-style: none;"><i
																	class="fa fa-calendar"></i></span>
															</div>
															<label class="col-form-label"
																style="width: 4%; float: left; text-align: center">~</label>
															<div class="input-group date" style="width: 48%;">
																<input type="text" class="form-control"  id="edate" name="edate"
																	value=""> <span
																	class="input-group-addon" style="list-style: none;"><i
																	class="fa fa-calendar"></i></span>
															</div>
														</div>
														<label class="col-sm-1 col-form-label"
															style="padding-left: 10px;">미터아이디</label>
														<div class="col-sm-3">
															<input type="text" class="form-control">
														</div>
														<label class="col-sm-1 col-form-label"
															style="padding-left: 10px;">미터아이디</label>
														<div class="col-sm-3">
															<input type="text" class="form-control">
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
									<!-- page option -->
									<div class="row m-t-n-n" style="margin:-1px"  >
										<div style="width :100%;vertical-align:center" class="m-t-n-sm">
											<label id="cur_page_num" class="col-form-label"></label>
											<div style ="float:right; margin-bottom:5px">
												<select id="data_per_page" class="form-control" name="data_per_page" onchange="javascript:changeLimit(this);">
													<option value=10 selected>10개씩</option>
													<option value=100>100개씩 </option>
													<option value=250>250개씩 </option>
												</select>
											</div>
										</div>
									</div>
									<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
									
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
	{headerName: "번호", field: "no", width:80},
	{headerName: "아이디", field: "device_id"},
	{headerName: "단말번호", field: "device_serial"},
	{headerName: "단말OID", field: "device_oid", width:250},
	{headerName: "단말상태", field: "device_stat_nm"},
	{headerName: "최종통신일자", field: "last_comm_dt"},
	{headerName: "아이피", field: "device_ip"},
	{headerName: "PORT", field: "device_port"}
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
     selectComboBox('device_type', 'MT');
}

function init() {
	
	// init
	initGrid();
	
	// form search
	ajaxSearchForm();
	
	// combo
	comboDeviceType();	
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
