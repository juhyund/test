<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<html>
<head>
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>

<script>
//specify the columns
var columnDefs = [
	{headerName: "번호", field: "no", width:80, menuTabs:[]},
	{headerName: "생성일자", field: "reg_dt", menuTabs:[]},
	{headerName: "파일명", field: "fw_nm", menuTabs:[]},
	{headerName: "패키지 명", field: "fw_file_nm", menuTabs:[]},
	{headerName: "패키지 버전", field: "fw_version", menuTabs:[]}
];

var initGrid = function() {
  dataGrid = new DataGrid('grid', columnDefs, true, 500);    
  dataGrid.makeGrid();
  dataGrid.showNoRows();
};

onRowClicked = function(event){
	var device_id = event.data.device_id;
	
}

function ajaxSearchForm() {
	initGrid();
  var options = { 
         success     : successResultHandler,
         url         : COMMON_URL + "/ajaxDeviceFWList",
         contentType : "application/x-www-form-urlencoded;charset=UTF-8",
         type        : "post", /* get, post */
         dataType    : "json", /* xml, html, script, json */
         data        : $("#fwModal").serialize()
   };             
  
   $.ajax(options);
}

function successResultHandler(data, status) {	
	dataGrid.setData(data.resultGrid);
}

function fwListModal() {
	ajaxSearchForm();
    $('#fwListModal').modal('show');
	
};

function fwUpgradeModal() {
    $('#fwUpgradeModal').modal('show');
	
};

function fwUploadModal() {
	
	$("#fw_name").val("");
	$("#fw_ver").val("");
	$("#fw_file_name").val("");
	$("#fw_file").val("");
	$('#uploadFw').attr('disabled', true);

    $('#fwUploadModal').modal('show');
};

function ajaxDeviceFwUpdate() {
showLoading();
  var formData = new FormData(); 
  formData.append("fw_nm", $("#fw_name").val());
  formData.append("fw_version", $("#fw_ver").val());
  formData.append("fw_file_nm", $("#fw_file_name").val());
  formData.append("fw_file", $("#fw_file")[0].files[0]);
  
  var options = { 
         url         : COMMON_URL + "/ajaxDeviceFWUpload",
         processData : false,
		 contentType : false,
		 data		 : formData,
         type        : "post",
         success     : function(data, status){
        	 if(data.result == "success"){
        		 ajaxSearchForm();
        		 firmwarelist();
        	 } else {
        		 alert(data.result);
        	 }
        	 hideLoading();
         }
   };             
   $.ajax(options);
}

$(function() {
	$("#fw_file").change(function(e){
		var ori_name = $('#fw_file')[0].files[0].name;
		var idx = ori_name.lastIndexOf('_');
		if(idx > -1){
			$("#fw_name").val(ori_name.substring(0, idx));
			$("#fw_ver").val(ori_name.substring((idx + 1), ori_name.length));
			$("#fw_file_name").val(ori_name);
			$('#uploadFw').attr('disabled', false);
		} else {
			alert("유효하지 않은 파일 형식 입니다.");
			$("#fw_file").val("");
		}
	});
});

function ajaxDeviceFwUpgrade() {
showLoading();
  var options = { 
         url         : COMMON_URL + "/ajaxExecResource",
		 contentType : "application/x-www-form-urlencoded;charset=UTF-8",
		 dataType    : "json",
         type        : "post",
         data		 : { 
			url : "clients/",
        	method :"Write",
        	device_id : $("#device_id").val(),
        	service_id : $("#service_id").val(),
        	device_serial : $("#device_serial").val(), 
        	resource : "/5/0/1", 
        	newValue : $("#package_uri").val()
	     },
         success     : function(data, status){
        	 if(data.statusCode == "200") {
 	    		alert("전송성공 [" + data.tid + "]");
 	    	} else {
 	    		alert("제어실패 [" + data.statusMsg + "]");
 	    	}
        	 hideLoading();
         }
   };             
   $.ajax(options);

}
</script>
</head>
<body>
	<!-- modal -->
	<div class="modal bs-example-modal-sm" id="fwListModal" tabindex="-1" role="dialog"
	aria-labelledby="fwListModalLabel" aria-hidden="true">
	<div class="modal-dialog" style="max-width: 700px">
		<div class="modal-content">
			<div class="modal-header">
				<span class="modal-title" style="font-size: 20px; font-weight: bold">SW 파일 목록</span>		
				<button type="button" class="close" data-dismiss="modal"
					aria-hidden="true">&times;</button>
			</div>
			<div class="modal-body">		
			<form class="form-horizontal" role="form" method="post" id="fwModal">
				<div>
					<div class="ibox-content" style="background-color: #e7eaec">
						<table style="height: 100%; width: 100%; border: 0px #e7eaec">
							<tbody>
								<tr width="100%" >
									<td width="85%">
										<div class="form-group row" style="margin-left: 0px">
											<div class="col-lg-6">
												<input type="text" placeholder="패키지 명" class="form-control" name="fw_file_nm" id="fw_file_nm" style="height: 38px; display: inline;">
											</div>
											<div class="col-lg-6">
												<input type="text" placeholder="패키지 버전" class="form-control" name="fw_version" id="fw_version" style="height: 38px; display: inline;">
											</div>
										</div>
									</td>
									<td width="15%" style="text-align: right">
										<button class="btn btn-primary" style="height: 35px; width: 40px" type="button" onclick="ajaxSearchForm()">
											<i class="fa fa-search"></i>
										</button>
										<button class="btn btn-warning" style="height: 35px; width: 40px" type="button" onclick="fwUploadModal();">
											<i class="fa fa-upload"></i>
										</button>
									</td>
								</tr>
							</tbody>
						</table>
					</div>
				</div>
			
				<!-- grid -->
				<div id="grid" style="height:350px;" class="ag-theme-balham"></div>
				
				<!-- grid pagination 
				<div id="grid-page" style ="display:none;" class="m-t-sm">
					<ul id="pagination" class="pagination"></ul>
				</div>
				-->
			</div>
			<div class="modal-footer">
				<button type="button" class="btn btn-primary" data-dismiss="modal" onclick="ajaxDeviceFwUpgrade()">모뎀전송</button>
				<button type="button" class="btn btn-default" data-dismiss="modal">닫기</button>
			</div>
		</form>
		</div>
	</div>
	</div>
	<!-- modal -->
	
	<!-- modal -->
	<div class="modal bs-example-modal-sm" id="fwUploadModal" tabindex="-1" role="dialog"
	aria-labelledby="fwUploadModalLabel" aria-hidden="true">
	<div class="modal-dialog" style="max-width: 420px">
		<div class="modal-content">
			<div class="modal-header" style="background-color: #1ab394; color: #FFF">
				<span class="modal-title" style="font-size: 20px; font-weight: bold">파일 업로드</span>	
				<button type="button" class="close" data-dismiss="modal"
					aria-hidden="true">&times;</button>
			</div>
			<div class="modal-body">		
			<form class="form-horizontal" role="form" method="post" id="fwFileModal" enctype="multipart/form-data">
				<div class="form-group row">
					<label class="col-lg-3 col-form-label">패키지 명</label>
					<div class="col-lg-9"><input type="text" name="fw_name" id="fw_name" class="form-control"></div>
				</div>
				<div class="form-group row">
					<label class="col-lg-3 col-form-label">패키지 버전</label>
					<div class="col-lg-9"><input type="text" name="fw_ver" id="fw_ver" class="form-control"></div>
				</div>
				<div class="form-group row">
					<label class="col-lg-3 col-form-label">파일 상태</label>
					<div class="col-lg-9"><input type="text" name="fw_file_name" id="fw_file_name" class="form-control"></div>
					<input type="file" id="fw_file" name="fw_file" value="click"/>
				</div>
			</div>
			<div class="modal-footer">
				<button type="button" class="btn btn-primary" id="uploadFw" data-dismiss="modal" onclick="ajaxDeviceFwUpdate()">확인</button>
				<button type="button" class="btn btn-default" data-dismiss="modal">취소</button>
			</div>
		</form>
		</div>
	</div>
	</div>
	<!-- modal -->
	
	<!-- modal -->
	<div class="modal bs-example-modal-sm" id="fwUpgradeModal" tabindex="-1" role="dialog"
	aria-labelledby="fwUpgradeModalLabel" aria-hidden="true">
	<div class="modal-dialog" style="max-width: 850px">
		<div class="modal-content">
			<div class="modal-header" style="background-color: #1ab394; color: #FFF">				
				<span class="modal-title" style="font-size: 20px; font-weight: bold">SW 업그레이드</span>
				<button type="button" class="close" data-dismiss="modal"
					aria-hidden="true">&times;</button>
			</div>
			<div class="modal-body">		
			<form class="form-horizontal" role="form" method="post" id="fwUpgradeform">
				<div class="form-group row">
					<label class="col-lg-2 col-form-label">모뎀번호</label>
					<div class="col-lg-9"><input type="text" name="deviceserial" id="deviceserial" class="form-control" style="border: none" readonly="readonly"></div>
				</div>
				<div class="form-group row">
					<label class="col-lg-2 col-form-label">패키지 URI</label>
					<div class="col-lg-9"><input type="text" name="package_uri" id="package_uri" class="form-control" style="border: none"></div>
				</div>
			</div>
			<div class="modal-footer">
				<button type="button" class="btn btn-primary" id="uploadFw" data-dismiss="modal" onclick="ajaxDeviceFwUpgrade()">모뎀전송</button>
				<button type="button" class="btn btn-default" data-dismiss="modal">취소</button>
			</div>
		</form>
		</div>
	</div>
	</div>
	<!-- modal -->
	
</body>
</html>
