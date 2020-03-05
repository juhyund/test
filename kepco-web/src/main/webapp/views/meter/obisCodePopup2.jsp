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


<!-- angular -->
<script src="<%=COMMON_PATH_JS%>/angular.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/angular-route.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/controller/meterApp.js"></script>



<!-- Data picker -->
<script src="<%=COMMON_PATH_JS%>/bootstrap-datepicker.js"></script>

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js?ver=0"></script>
<style>
  div .ibox-title {
		/* background-color: #dee2e6; */
		background-color: #5fa4ef47;
	}
  table th.text-navy {
  	color: #676a6c !important;
  }	
</style>
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
<body ng-app="meterApp">
<!--  wrapper -->
<div id="content"  ng-controller="meterCtrl"> 
<div id="wrapper">
<div id="page-wrapper" style="width:100%" class="gray-bg" >
<!-- navigator -->
<div class="row wrapper page-heading" style="padding:5px">
<div class="col-lg-10" >
	<h3 style="margin-top:6px">OBIS CODE 선택2</h3>
</div>						
</div>
<!-- navigator -->
<!-- body -->
<div >

	<div class="col-lg-12">	
		<div class="ibox">
			<div class="ibox-content">
				<form name="search_form" id="search_form" method="post">
					<table class="table table-borderless" style="height: 100%; "
						style="margin-bottom: 7px;" border="1">
						<tbody >
							<tr class="table-border">
								<td>
									<div class="form-group row">
										<label class="col-lg-2 col-form-label">OBIS 코드</label>
										<div class="col-lg-3">
											<input type="text" id="obis_code" name="obis_code" value="" class="form-control">
										</div>
										<label class="col-lg-2 col-form-label"
											style="padding-left: 10px;">OBIS 코드명</label>
										<div class="col-lg-3">
											<input type="text" id="descr" name="descr" value="" class="form-control">
										</div>
									</div>
								</td>
								<td width="180" style="text-align: right">
									<button class="btn btn-primary" style="height: 100%; width: 50px" type="button" onclick="ajaxSearchForm();">
										<i class="fa fa-search"></i>
									</button>
									<button class="btn btn-warning" style="height: 100%; width: 50px" type="button" onclick="resetForm();">
										<i class="fa fa-undo"></i>
									</button>
								</td>
							</tr>
					</table>
			
				</form>
			
					
				<!-- <div class="row m-b-md ">
				</div> -->
				
				 <div id="grid" style="height:300px;" class="ag-theme-balham m-b-md"></div>								
				<div>
					<button class="btn btn-primary m-t-sm" style="height: 100%" type="button" onclick="selectObis()">
						<i class="fa">OBIS 선택</i>
					</button>
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
var selectedObisCode = '';
//specify the columns
var columnDefs = [
	{headerName: "번호", 			field: "no", 	   width:50,suppressSizeToFit: true},
	{headerName: "CLASS",		field: "class_id"},
	{headerName: "OBIS 코드",		field: "obis_code",width:300},
 	{headerName: "OBIS 코드명",	field: "descr"},
	{headerName: "속성",			field: "attribute_no"},
	{headerName: "권한",			field: "access_right"}
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
           url         : COMMON_URL + "/ajaxSelectObisList2",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : {meter_type		:'${meter_type}',
        	  			  obis_code			: $("#obis_code").val(),
        	  			  metering_type_nm 	: $("#descr").val()}
     };             	
    
     $.ajax(options);
}

onRowClicked = function(event){
	//선택된 row의 obis_code를 저장한다
	
	var selectedRows = dataGrid.getSelectedRow();
    var selectedRowsString = '';
    selectedRows.forEach( function(selectedRow, index) {
    	selectedObisCode = selectedRow.class_id+selectedRow.obis_code+selectedRow.attribute_no
    	
    });
}

selectObis = function(event){
	opener.document.getElementById("obis_code105").value = selectedObisCode;
	 window.close();
}

function resetForm(){
	$("#search_form")[0].reset();
	
};

function showRequest() {
	// $("#loading").show();
}

function successResultHandler(data, status) {
	
	dataGrid.setData(data.result);
	
}

function init() {
	// init
	initGrid();
	
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