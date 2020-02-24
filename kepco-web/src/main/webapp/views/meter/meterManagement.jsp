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
						<h3 style="margin-top: 6px">미터 정보 조회</h3>
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
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">지역본부</label>
														<div class="col-lg-3">
															<select class="form-control" name=""
																id="central_nm"></select>
														</div>
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">지사</label>
														<div class="col-lg-3">
															<select class="form-control" name="branch_nm"
																id="branch_nm"></select>
														</div>
													</div>

													<div class="form-group form-group-end row">
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">계기타입</label>
														<div class="col-lg-3">
															<select class="form-control" name="meter_type"
																id="meter_type"></select>
														</div>
														
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">계기번호</label>
														<div class="col-lg-3">
															<input class="form-control" name="meter_serial"
																id="meter_serial"></input>
														</div>
														
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">모뎀번호</label>
														<div class="col-lg-3">
															<input class="form-control" name="device_serial"
																id="device_serial"></input>
														</div>
													</div>
													
													<div class="form-group form-group-end row">
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">통신상태</label>
														<div class="col-lg-3">
															<select class="form-control" name="device_status"
																id="device_status"></select>
														</div>
														
														<label class="col-lg-1 col-form-label"
															style="padding-left: 10px;">최종통신 일자</label>
														<div class="col-sm-4" id="datePicker">
															<div class="input-group date" style="width: 48%; float: left;">
																<input type="hidden" id="sdate" name="sdate" value=""> 
																<input type="text" class="form-control" id="sdateView" name="sdateView" value="">
																<span class="input-group-addon" style="list-style: none;">
																	<i class="fa fa-calendar"></i>
																</span>
															</div>
															<label class="col-form-label" style="width: 4%; float: left; text-align: center">~</label>
															<div class="input-group date" style="width: 48%;">
																<input type="hidden" id="edate" name="edate" value=""> 
																<input type="text" class="form-control" id="edateView" name="edateView" value="">
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
													<button class="btn btn-outline btn-primary" style="height: 100%; width: 50px" type="button" onclick="excelDownload();">
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
	{headerName: "본부", field: "", width:100, cellStyle:{'text-align': "center"}},
	{headerName: "지사", field: "branch_nm", width:100, cellStyle:{'text-align': "center"}},
	{headerName: "계기타입", field: "meter_type", width:150, cellStyle:{'text-align': "center"}},
	{headerName: "계기번호", field: "meter_serial", cellStyle:{'text-align': "center"}},
	{headerName: "검침주기", field: "lp_period", cellStyle:{'text-align': "center"}},
	{headerName: "통신상태", field: "device_status", cellStyle:{'text-align': "center"}},
	{headerName: "마지막 검침 일시", field: "last_comm_dt"},
	{headerName: "모뎀번호", field: "device_serial", width:120},
	{headerName: "모뎀 최종통신일자", field: "last_comm_dt"},
	{headerName: "모뎀 운영상태", field: "allow_yn", cellStyle:{'text-align': "center"}}
	/* {headerName: "계약상태", field: ""},
	{headerName: "고객번호", field: ""} */
];

// init selectComboBox
//device type
function comboDeviceType() { 
     selectComboBox('meter_type', 'MT');
}

//device type
function comboDeviceStatus() { 
     selectComboBox('device_status', 'CT');
}

var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};

onRowClicked = function(event){
	var meter_serial = event.data.meter_serial;
	location.href = CONTEXT_PATH + "/meterDetail?meter_serial="+meter_serial;
}

function ajaxSearchForm() {
	
    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxMeterInfoList",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function excelDownload() {
	
	if( totalCnt == 0){
		Swal.fire({
			position: 'center',
			icon: 'error',
			title: 'excel 다운로드 불가',
			text: '조회 결과가 없습니다!',
			showConfirmButton: false,
				timer: 1500
			});
	}else{

		 $('#search_form').attr('action', "/ewsn-app/downloadMeterValue");
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

function resetForm() {
	$('#sdate').val("");
	$('#edate').val("");
	$('#lsdate').val("");
	$('#ledate').val("");
}


function init() {
	
	// init
	// combo
	comboDeviceType();
	comboDeviceStatus()
	
	// Grid
	initGrid();
	
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