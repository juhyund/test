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

<!-- Mainly scripts -->
<script src="<%=COMMON_PATH_JS%>/jquery-3.1.1.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/popper.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/bootstrap.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.metisMenu.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.slimscroll.min.js"></script>

<!-- Custom and plugin javascript -->
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>

<!-- Data picker -->
<script src="<%=COMMON_PATH_JS%>/bootstrap-datepicker.js"></script>

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>

<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
</head>
<body>
<!--  wrapper -->
<div id="content">
<div id="wrapper">
<div id="page-wrapper" style="width:100%" class="gray-bg" >
<!-- navigator -->
<div class="row wrapper page-heading" style="padding:5px">
<div class="col-lg-10" >
	<h3 style="margin-top:6px">검침현황 모니터링</h3>
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
	
	<table class="table table-borderless" style="margin-bottom:7px;" border="1">
		<tbody> 
		<tr class="table-border">
			<td height="80" >
			<div class="form-group row">				
				<label class="col-lg-1 col-form-label" style="width:80px;">모뎀명</label>
				<div class="col-lg-3"><input type="text" class="form-control"></div>
				<label class="col-lg-1 col-form-label" style="width:80px;">모뎀시리얼</label>
				<div class="col-lg-3"><input type="text" class="form-control"></div>	
				<label class="col-lg-1 col-form-label" style="width:80px;">모뎀구분</label>
				<div class="col-lg-3"><input type="text" class="form-control"></div>		    			
  			</div>
  			
  			<div class="form-group form-group-end row"><label class="col-sm-1 col-form-label">등록일자</label>
			<div class="col-sm-3" id="datePicker">   
    		<div class="input-group date" style="width:48%;float:left;">
			<input type="text" class="form-control" value="03/04/2014" >
			<span class="input-group-addon" style="list-style: none;" ><i class="fa fa-calendar"></i></span>    
			</div>
			<label class="col-form-label" style="width:4%;float:left;text-align:center">~</label>
			<div class="input-group date" style="width:48%;">
			<input type="text" class="form-control" value="03/04/2014" >
			<span class="input-group-addon" style="list-style: none;" ><i class="fa fa-calendar"></i></span>
    		</div>
  			</div>
        	<label class="col-sm-1 col-form-label">미터아이디</label>
        		<div class="col-sm-3"><input type="text" class="form-control"></div>
        	<label class="col-sm-1 col-form-label">미터아이디</label>
        		<div class="col-sm-3"><input type="text" class="form-control"></div>
    		</div>
    		
  			
			</td>		
			<td width="250" height="80" style="text-align:right">
				<button class="btn btn-primary" style="height:100%;width:50px" type="button"><i class="fa fa-search"></i></button>
				<button class="btn btn-warning" style="height:100%;width:50px" type="button"><i class="fa fa-undo"></i></button>
			</td>			
		</tr>
		</tbody>
	</table>
  	       
	<div>
	<div style="height:30px;">Result Count : 15</div>
	
	<div id="myGrid" style="height:500px;" class="ag-theme-balham"></div>
	
	<div class="col-sm-12" style="text-align:center">                                      
	<div style="padding-top:10px" class="dataTables_paginate paging_simple_numbers" id="DataTables_Table_0_paginate"><ul class="pagination"><li class="paginate_button page-item previous disabled" id="DataTables_Table_0_previous"><a href="#" aria-controls="DataTables_Table_0" data-dt-idx="0" tabindex="0" class="page-link">Previous</a></li><li class="paginate_button page-item active"><a href="#" aria-controls="DataTables_Table_0" data-dt-idx="1" tabindex="0" class="page-link">1</a></li><li class="paginate_button page-item "><a href="#" aria-controls="DataTables_Table_0" data-dt-idx="2" tabindex="0" class="page-link">2</a></li><li class="paginate_button page-item "><a href="#" aria-controls="DataTables_Table_0" data-dt-idx="3" tabindex="0" class="page-link">3</a></li><li class="paginate_button page-item next" id="DataTables_Table_0_next"><a href="#" aria-controls="DataTables_Table_0" data-dt-idx="4" tabindex="0" class="page-link">Next</a></li></ul></div>	                                              
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
	
$(document).ready(function() {
	var cellStyleCenter = {				
			textAlign: 'center'
	};
	var cellStyleRight = {				
			textAlign: 'right'
	};

	// specify the columns
	var columnDefs = [
	{headerName: "번호", field: "no", width:50},
	{headerName: "미터아이디", field: "meterid", cellStyle: cellStyleCenter, headerClass:"ag-center-header"},
	{headerName: "검침일시", field: "metering_dt", cellStyle: cellStyleCenter, headerClass:"ag-center-header"},
	{headerName: "지역", field: "location", cellStyle: cellStyleCenter, headerClass:"ag-center-header"},
	{headerName: "순방향 유효전력량", field: "ch1", type: 'numericColumn'},
	{headerName: "순방향 지상 무효전력량", field: "ch2", type: 'numericColumn'},
	{headerName: "순방향 진상 무효전력량", field: "ch3", type: 'numericColumn'},
	{headerName: "순방향 피상 전력량", field: "ch4", type: 'numericColumn'}
	];

	// specify the data
	var rowData = [
	];

	// let the grid know which columns and what data to use
	var gridOptions = {
	columnDefs: columnDefs,
	rowData: rowData
	};

	// lookup the container we want the Grid to use
	var eGridDiv = document.querySelector('#myGrid');

	// create the grid passing in the div to use together with the columns & data we want to use
	new agGrid.Grid(eGridDiv, gridOptions);

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