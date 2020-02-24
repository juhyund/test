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
<script src="https://cdn.jsdelivr.net/npm/sweetalert2@9"></script>

<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js?ver=00" charset="UTF-8"></script>
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
	<h3 style="margin-top:6px">검침데이터 조회</h3>
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
										<label class="col-sm-2 col-form-label text-align">검침 기간</label>
										<div class="col-sm-2 btn-group">
											<button type="button" class="btn btn-outline btn-primary" onclick="setSearchPeriod('today')">오늘</button>
											<button type="button" class="btn btn-outline btn-primary" onclick="setSearchPeriod('weekly')">주간</button>
											<button type="button" class="btn btn-outline btn-primary" onclick="setSearchPeriod('montly')">월간</button>
			                            </div>
										
										<label class="col-lg-1 col-form-label">미터 ID</label>
										<div class="col-lg-3">
											<input type="text" id="meter_id" name="meter_id" value="" class="form-control">
										</div>
									</div>
									<div class="form-group row">
										<!-- <label class="col-sm-1 col-form-label"></label> -->
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
										
										<label class="col-lg-1 col-form-label"
											style="padding-left: 10px;">단말 ID</label>
										<div class="col-lg-3">
											<input type="text" id="device_id" name="device_id" value="" class="form-control">
										</div>
										<label class="col-lg-1 col-form-label" style="padding-left: 10px;">미터타입</label>
										<div class="col-lg-3">
											<select class="form-control" name="meter_type"	id="meter_type"></select>
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
					</table>
			
				</form>
				<form name="detail_form" id="detail_form" method="get" action="showMeterValueDetail">
					<input type="hidden" id="detail_meter_id" name="detail_meter_id" class="form-control">
				</form>
			  	     
					<div>
						<!-- page option -->
						<div class="row m-t-n-n" style="margin:-1px"  >
							<div style="width :100%;vertical-align:center" class="m-t-n-sm">
								<label id="cur_page_num" class="col-form-label"></label>
								<div style ="float:right; margin-bottom:5px">
									<select id="data_per_page" class="form-control" name="data_per_page" onchange="javascript:changeLimit(this);">
										<option valuesearch_num=10 selected>10개씩</option>
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
								<ul id="pagination" class="pagination">?</ul>
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
	{headerName: "미터 시리얼", field: "meter_id"},
	{headerName: "READ_DT", field: "read_dt"},
   	{headerName: "구간검침값 (kWh)", 
			   	field: "sect_meter_value", 
			   	valueFormatter: numberFormatter,
			   	cellStyle: { 'text-align': "right" }},
   	{headerName: "누적검침값 (kWh)",
			   	field: "meter_value", 
			   	valueFormatter: numberFormatter,
			   	cellStyle: { 'text-align': "right" }}, 
	{headerName: "등록시간", field: "reg_dt"}
];


var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500, true);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};

var totalCnt = 0;

function ajaxSearchForm() {
	setSearchParam2($("#sdateView").val(), $("#edateView").val());
	
    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxMeterValue",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
     $.ajax(options);
}

function excelDownload() {
	setSearchParam2($("#sdateView").val(), $("#edateView").val());
	
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

onRowClicked = function(event){
	//선택된 row의 meter_id를 파라미터로 MeteringDetail.jsp를 팝업으로 연다.
	
	var selectedRows = dataGrid.getSelectedRow();
    var selectedRowsString = '';
    selectedRows.forEach( function(selectedRow, index) {
    	selectedRowsString = selectedRow.meter_id;
    });
    
    showDetailMeterValue(selectedRowsString);
    
}


var winObj;
function showDetailMeterValue(meter_id){ 
	var opts="width=900, height=800,left=200, top=200, resizable=no, toolbar=yes"; 

	if(winObj)
        winObj.close();
	
	var param = "?detail_meter_id="+meter_id;
	param += "&sdate="+$("#sdateView").val();
	param += "&edate="+$("#edateView").val();
	
    winObj = window.open(COMMON_URL+"/meteringDetail"+param, "", opts);
}

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
	var currentPage = $("#page").val();
	
	dataGrid.setData(data.resultGrid);
	gridPage(data.totalCount, dataPerPage, 10, currentPage);
	
	totalCnt = data.totalCount;
}

//device type
function comboDeviceType() { 
     selectComboBox('meter_type', 'MT');
}

function init() {
	
	// init
	initGrid();
	
	setSearchPeriod('today');
	comboDeviceType();
	
	// form search
	ajaxSearchForm();
	
	//$("#limit").val($("#search_num option:selected").val());
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
