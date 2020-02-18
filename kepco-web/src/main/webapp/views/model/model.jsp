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
<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">

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
<link rel="stylesheet" href="<%=COMMON_PATH_JS%>/icheckbox.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>

<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>
<%-- <script src="<%=COMMON_PATH_JS%>/icheckbox.css"></script> --%>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
</head>
<body>
<!--  wrapper -->
<div id="content">
<div id="wrapper">
<div id="page-wrapper" style="width:100%" class="gray-bg" >
<!-- navigator -->
<div class="row wrapper page-heading" style="padding:5px">
<div class="col-lg-10" >
	<h3 style="margin-top:6px">리소스 모델 관리</h3>
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
					<table class="table table-borderless"
						style="margin-bottom: 7px;" border="1">
						<tbody>
							<tr class="table-border">
								<td height="80">
									<div class="form-group row">
										<label class="col-lg-1 col-form-label">오브젝트ID</label>
										<div class="col-lg-3">
											<input type="text" id="object_id" name="object_id" value="" class="form-control">
										</div>
										<label class="col-lg-1 col-form-label"
											style="padding-left: 10px;">오브젝트명</label>
										<div class="col-lg-3">
											<input type="text" id="object_name" name="object_name" value="" class="form-control">
										</div>
									</div>
									<div class="form-group row">
										<label class="col-lg-1 col-form-label"	style="padding-left: 10px;">인스턴스</label>
										<div class="i-checks col-lg-3">
											<label><input type="radio" class="iradio_square-green" name="instance" value=""  checked> <i></i>전체</label>
											<label><input type="radio" class="iradio_square-green" name="instance" value="single"> <i></i>single</label>
											<label><input type="radio" class="iradio_square-green" name="instance" value="Multiple"> <i></i>Multiple</label>
										</div>
										<label class="col-lg-1 col-form-label"	style="padding-left: 10px;">필수여부</label>
										<div class="col-lg-3">
											<label><input type="radio" class="i-checks iradio_square-green" name="mandatory" value=""  checked> <i></i>전체</label>
											<label><input type="radio" class="i-checks  iradio_square-green" name="mandatory" value="1"> <i></i>필수</label>
											<label><input type="radio" class="i-checks  iradio_square-green" name="mandatory" value="0"> <i></i>선택 </label>
										</div>
										<div style="display:none">
											<input type="text" id="object_flag" name="object_flag" value="O" class="form-control">
										</div>
									</div>
								</td>
								<td width="250" height="80" style="text-align: right">
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
				<form name="detail_form" id="detail_form" method="get" action="showObjectDetail">
					<input type="hidden" id="detail_object_id" name="detail_object_id" class="form-control">
					<input type="hidden" id="detail_object_name" name="detail_object_name" class="form-control">
					<input type="hidden" id="detail_instance" name="detail_instance" class="form-control">
					<input type="hidden" id="detail_mandatory" name="detail_mandatory" class="form-control">
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
<!-- body -->
</div>
</div>	
</div>

<script type="text/javascript" charset="utf-8">	
//specify the columns
var columnDefs = [
	{headerName: "번호", field: "no", width:80},
	{headerName: "오브젝트 ID", field: "object_id"},
	{headerName: "오브젝트 명", field: "object_name"},
	{headerName: "인스턴스구분", field: "instance"},
	{headerName: "필수", field: "mandatory"},
	{headerName: "비고", field: "descr", width:250}
];

var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500, true);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};

function ajaxSearchForm() {

    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxLwm2mResourceList",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function ajaxExcelDownload() {

    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxExcelLwm2mResourceList",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

onRowClicked = function(event){
	//선택된 row의 object데이터를 파라미터로 ModelDetail.jsp를 연다.
	
	var selectedRows = dataGrid.getSelectedRow();
    var selectedRows_id = '';
    var selectedRows_name = '';
    var selectedRows_instance = '';
    var selectedRows_mandatory = '';
    
    selectedRows.forEach( function(selectedRow, index) {
        if (index!==0) {
            selectedRowsString += ', ';
        }
        selectedRows_id += selectedRow.object_id;
        selectedRows_name += selectedRow.object_name;
        selectedRows_instance += selectedRow.instance;
        selectedRows_mandatory += selectedRow.mandatory;
       // alert("selectedRowsString = "+selectedRow.object_id);
    });
    // selectedRow.object_id를 form의 detail_object_id에 보냄.
    $("#detail_object_id").val(selectedRows_id);
    $("#detail_object_name").val(selectedRows_name);
    $("#detail_instance").val(selectedRows_instance);
    $("#detail_mandatory").val(selectedRows_mandatory);
    $("#detail_form").submit();
    
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
}

function init() {
	
	// init
	initGrid();
	
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