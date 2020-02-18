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
	<h3 style="margin-top:6px">Connectivity Monitoring</h3>
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
<div class="row">
	<div class="col-lg-12">	
		<div class="ibox">
			<div class="ibox-content">
				<form name="search_form" id="search_form" method="post">
				<input type="hidden" id="limit" name="limit" value ="10" class="form-control">
				<input type="hidden" id="page" name="page" value ="1" class="form-control" onchange="ajaxSearchForm()">
					<table class="table table-borderless" style="height: 100%; "
						style="margin-bottom: 7px;" border="1">
						<tbody >
							<tr class="table-border">
								<td height="80">
									<div class="form-group row">
										<label class="col-lg-1 col-form-label">단말 ID</label>
										<div class="col-lg-3">
											<input type="text" id="device_id" name="device_id" value="" class="form-control">
										</div>
										<label class="col-lg-1 col-form-label">단말타입</label>
										<div class="col-lg-3">
											<select class="form-control" name="device_type"	id="device_type" type="number">
												<option value=0>(데이터 확인 후  변경 예정)</option>
												<option value=1 >GW </option>
												<option value=2 >DEVICE</option>
											</select>	
										</div>
									</div>
									
									<div class="form-group row">
										<label class="col-lg-1 col-form-label">IP 주소</label>
										<div class="col-lg-3">
											<input type="text" id="ip_addr_str" name="ip_addr_str" class="form-control">
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
				<form name="detail_form" id="detail_form" method="get" action="deviceControlDetail">
					<input type="hidden" id="detail_control_seq" name="detail_control_seq" class="form-control">
				</form>
				<div>
					<!-- page option -->
					<div class="row m-t-n-n" style="margin:-1px"  >
						<div style="width :100%;vertical-align:center">
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
</div>
<!-- body -->
</div>
</div>	
</div>

<script type="text/javascript" charset="utf-8">	

//specify the columns
var columnDefs = [
	{headerName: "번호", field: "no", width:80},
	{headerName: "단말 ID", field: "device_id"},
	{headerName: "단말타입", field: "device_type"},
	{headerName: "Network Bearer", field: "network_bearer"},
	{headerName: "무선신호세기", field: "radio_signal_strength"},
	{headerName: "IP 주소", field: "ip_addr"},
	{headerName: "라우터IP 주소", field: "router_ip_addr"},
	{headerName: "Link Quality", field: "link_quality"},
	{headerName: "최종 통신일자", field: "last_comm_date"}
];


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

function ajaxExcelDownload() {
	alert("excel 다운로드 개발중");
	//setSearchParam($("#sdateView").val(), $("#edateView").val());

    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxExcelMeterValue",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

onRowClicked = function(event){
	//선택된 row의 meter_id를 파라미터로 MeteringDetail.jsp를 팝업으로 연다.
	
	var selectedRows = dataGrid.getSelectedRow();
    var selectedRowsString = '';
    selectedRows.forEach( function(selectedRow, index) {
        if (index!==0) {
            selectedRowsString += ', ';
        }
        selectedRowsString += selectedRow.control_seq;
    });
    
    // selectedRow.object_id를 form의 detail_object_id에 보냄.
    $("#detail_control_seq").val(selectedRowsString);
    $("#detail_form").submit();
    
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
	$("#grid-page").hide();
};


function showRequest() {
	// $("#loading").show();
}

function successResultHandler(data, status) {
	var dataPerPage = $("#limit").val();
	
	dataGrid.setData(data.resultGrid);
	gridPage(data.totalCount, dataPerPage, 10, 1);
}


function init() {
	
	// init
	initGrid();
	
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