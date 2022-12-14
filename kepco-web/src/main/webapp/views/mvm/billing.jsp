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

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css?ver=0">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js?ver=6"></script>
<script src="https://cdn.jsdelivr.net/npm/sweetalert2@9"></script>

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
	<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> ???????????? ????????? ??????</h2>
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
					<table class="table table-borderless" style="height: 100%; "
						style="margin-bottom: 7px;" border="1">
						<tbody >
							<tr class="table-border">
								<td height="80">
									<div class="form-group row">
										<label class="col-lg-1 col-form-label" style="padding-left: 10px;">????????????</label>
										<div class="col-lg-3">
											<select class="form-control" style="width: 49%; display: inline;" name="branch_parent_id" id="branch_parent_id" onchange="changeParent()"></select>
											<select class="form-control" style="float:right; width: 49%; vertical-align: top; display: inline;" name="branch_id" id="branch_id">
												<option value=''>??????</option>
											</select>
										</div>
										<label class="col-sm-1 col-form-label">????????????</label>
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
										<label class="col-lg-1 col-form-label"style="padding-left: 10px;"></label>
										<div class="col-lg-3 btn-group">
											<button type="button" class="btn btn-outline btn-primary" onclick="setSearchPeriod('thisMonth')">??????</button>
											<button type="button" class="btn btn-outline btn-primary" onclick="setSearchPeriod('lastMonth')">??????</button>
											<button type="button" class="btn btn-outline btn-primary" onclick="setSearchPeriod('twoMonthsAgo')">?????????</button>
			                            </div>
									</div>
									<div class="form-group row">
										<label class="col-lg-1 col-form-label" style="padding-left: 10px;">????????????</label>
										<div class="col-lg-3">
											<select class="form-control" name="meter_type"	id="meter_type"></select>
										</div> 
										<label class="col-lg-1 col-form-label"
											style="padding-left: 10px;">????????????</label>
										<div class="col-lg-3">
											<input type="text" id="meter_serial" name="meter_serial" value="" class="form-control">
										</div>
										<label class="col-lg-1 col-form-label"
											style="padding-left: 10px;">????????????</label>
										<div class="col-lg-3">
											<input type="text" id="device_serial" name="device_serial" value="" class="form-control">
										</div>
									</div>
									<!--
									<div class="form-group row">
										
										 <label class="col-lg-1 col-form-label">?????? ?????????</label>
										<div class="col-lg-3">
											<select class="form-control" name="billing_dt"	id="billing_dt" type="number">
												<option value=1 selected>1</option>
												<option value=5 >5</option>
												<option value=10 >10</option>
												<option value=15 >15</option>
											</select>	
										</div> 
									</div>-->
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
										<option value=15 selected>15??????</option>
										<option value=100>100?????? </option>
										<option value=250>250?????? </option>
									</select>
								</div>
							</div>
						</div>
						<!-- grid -->
						<div id="grid" style="height:500px;" class="ag-theme-balham"></div>
						
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
	{headerName: "??????", 		field: "no", 			width:50,	suppressSizeToFit: true, pinned:"left"},
	{headerName: "?????????", 	field: "billing_dt",	width:100,	suppressSizeToFit: true, pinned:"left"},
	{headerName: "????????????", field: "meter_serial",	width:100,	suppressSizeToFit: true, pinned:"left"},
	{headerName: "??????", 	  	 field: "parent_branch_nm", width:100,suppressSizeToFit: true},
	{headerName: "??????", 		field: "branch_nm",		width:100,	suppressSizeToFit: true},
	{headerName: "????????????", 	field: "meter_type", 	width:100,	suppressSizeToFit: true},
	{headerName: "????????????", 	field: "device_serial", width:100,	suppressSizeToFit: true},
	{headerName: '????????? ???????????????(kWh)',
       children: [{headerName: "??????",  width:100, 
    	   				suppressSizeToFit: true,
					   	field: "active_imp_tot", 
					   	valueFormatter: numberFormatter,
					   	cellStyle: { 'text-align': "right" }},
				   	{headerName: "?????????", width:100, 
	    	   			suppressSizeToFit: true,
					   	field: "active_imp_rate1", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }}, 
					{headerName: "????????????", width:100,
					   	field: "active_imp_rate2", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }}, 
				   	{headerName: "?????????", width:100,
					   	field: "active_imp_rate3", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }}
					   	/*,   
					{headerName: "T4", width:100,
					   	field: "active_imp_rate4", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }}*/]
	},
	{headerName: '????????? ???????????????(kWh)',
       children: [{headerName: "??????", width:100,
					   	field: "active_exp_tot", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }},
				   	{headerName: "?????????", width:100,
					   	field: "active_exp_rate1", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }}, 
					{headerName: "????????????", width:100,
					   	field: "active_exp_rate2", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }},
				   	{headerName: "?????????", width:100,
					   	field: "active_exp_rate3", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }}/*,   
				   	{headerName: "T4", width:100,
					   	field: "active_exp_rate4", 
					   	valueFormatter: numberFormatter, 
	    	   			suppressSizeToFit: true,
					   	cellStyle: { 'text-align': "right" }}*/]
		},
	{headerName: "????????????", field: "reg_dt", width:200, suppressSizeToFit: true}
];


var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500, true);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
    dataGrid.autoSizeAll();
};

var totalCnt = 0;

function ajaxSearchForm() {
	setSearchParam2($("#sdateView").val(), $("#edateView").val());
	
    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxMeterBilling",
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
			title: 'excel ???????????? ??????',
			text: '?????? ????????? ????????????!',
			showConfirmButton: false,
				timer: 1500
			});
	}else{
		 $('#search_form').attr('action', COMMON_URL + "/downloadMeterBilling");
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

}

onRowClicked = function(event){
	var meter_id = event.data.meter_id;
	var billing_dt = event.data.billing_dt_int;
	
	var param = "?meter_id="+meter_id;
	param += "&billing_dt="+billing_dt;
	param += "&sdate="+$("#sdateView").val();
	param += "&edate="+$("#edateView").val();
	
	location.href = CONTEXT_PATH + "/billingDetail"+param;
}

function resetForm(){
	$("#search_form")[0].reset();
	setSearchPeriod("thisMonth");
};


function showRequest() {
	// $("#loading").show();
}

function successResultHandler(data, status) {
	var dataPerPage = $("#limit").val();
	var currentPage = $("#page").val();
	
	dataGrid.setData(data.resultGrid);
	gridPage(data.totalCount, dataPerPage, 10, currentPage);
	dataGrid.autoSizeAll();
	totalCnt = data.totalCount;
}

//device type
function comboDeviceType() { 
     selectComboBox('meter_type', 'MT');
     
     var combo = [ 'ajaxParentBranchCombo'];
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
function successResultCombo(data, status) {
	$.each(data, function(nm, combo) {
		$('#'+nm).append(new Option("??????", ""));
		$.each(data[nm], function(key, value){
			$('#'+nm).append(new Option(value, key));
		});
	});
}

function init() {
	
	// init
	initGrid();
	setSearchPeriod('thisMonth');
	comboDeviceType();
	
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
	autoclose: true
});


</script>
<!--  wrapper -->
</body>
</html>