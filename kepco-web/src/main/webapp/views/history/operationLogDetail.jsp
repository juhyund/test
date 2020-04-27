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
						<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> 제어이력 상세 &lt;모뎀번호: <span id="device_serial"></span>&gt;</h2>
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
								<table class="table table-bordered white-bg" style="width: 100%">
									<thead>
										<tr>
											<th class="device-detail-head">제어요청일시</th>
											<td class="device-detail-body" id="request_dt"></td>
											<th class="device-detail-head">요청자</th>
											<td class="device-detail-body" id="reg_id"></td>
										</tr>
										<tr>
											<th class="device-detail-head">응답일시</th>
											<td class="device-detail-body" id="result_dt"></td>
											<th class="device-detail-head">응답결과</th>
											<td class="device-detail-body" id="result"></td>
										</tr>
										<tr>
											<th class="device-detail-head">리소스</th>
											<td class="device-detail-body" id="resource_sum"></td>
											<th class="device-detail-head">제어구분</th>
											<td class="device-detail-body" id="method"></td>
										</tr>
										<tr>
											<th class="device-detail-head">오브젝트명</th>
											<td class="device-detail-body" id="object_nm"></td>
											<th class="device-detail-head">리소스명</th>
											<td class="device-detail-body" id="resource_nm"></td>
										</tr>
										<tr>
											<th class="device-detail-head">트랜잭션ID</th>
											<td class="device-detail-body" id="tid"></td>
											<th class="device-detail-head">동적스케줄 리소스명</th>
											<td class="device-detail-body"  id="metering_type_nm"></td>
										</tr>
										
										<tr>
											<th class="device-detail-head">결과내용</th>
											<td class="device-detail-body" colspan="3" id="payload"></td>
										</tr>
									</thead>
								</table>
								<form name="control_detail_form" id="control_detail_form" method="post">
									<input type="hidden" id="_device_id" name="_device_id" value="${device_id}" class="form-control">
									<input type="hidden" id="_request_dt" name="_request_dt" value="${request_dt}" class="form-control">
								</form>
								<div>
									<button class="btn btn-outline btn-primary m-t-sm" style="height: 100%; float: right" type="button" onclick="javascript:history.back(-1)">
										<i class="fa fa-undo"> 목록으로 돌아가기</i>
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

function ajaxSearchForm() {

    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxOperationLogDetail",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#control_detail_form").serialize()
     };             
    
     $.ajax(options);
}

function showRequest() {
	// $("#loading").show();
}

function successResultHandler(data, status) {
	
	//result, resource_sum 변환
	$.each( data, function(index, item) {
		if(index == 'result'){
			if(item.result == 1){
				data.result.result = '성공'
			}else if(item.result == 0){
				data.result.result = '실패'
			}else{
				data.result.result = '대기중'
			}
		
			if(item.object_id != "" && item.object_id != null){
				item.resource_sum = item.object_id
				
				if(item.object_instance_id != "" && item.object_instance_id != null){
					item.resource_sum += "/"+item.object_instance_id
				}	
			}
			
			if(item.resource_id != "" && item.resource_id != null){
				item.resource_sum += "/"+item.resource_id
				
				if(item.resource_instance_id != "" && item.resource_instance_id != null){
					item.resource_sum += "/"+item.resource_instance_id
				}
			}
		}
	});
	
	$('#device_serial').text(data.result.device_serial);
	$('#device_id').text(data.result.device_id);
	$('#request_dt').text(data.result.request_dt);
 	$('#method').text(data.result.method);
	$('#token').text(data.result.token);
	$('#tid').text(data.result.tid);	
	$('#result').text(data.result.result);	
	$('#result_dt').text(data.result.result_dt);	
	$('#reg_id').text(data.result.reg_id);
	$('#object_nm').text(data.result.object_nm);
	$('#resource_nm').text(data.result.resource_nm);
	$('#payload').text(data.result.payload);
	$('#resource_sum').text(data.result.resource_sum);
	
	// 동적스케줄 리소스명 추가
	$('#metering_type_nm').text(data.result.metering_type_nm);
	
}

function init() {
	
	// init
	// form search
	ajaxSearchForm();
	
}
	
$(document).ready(function() {	
	init();
});

</script>
</body>
</html>