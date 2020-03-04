<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<%
	String device_id = request.getParameter("device_id");
%>
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

<!-- angular -->
<script src="<%=COMMON_PATH_JS%>/angular.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/angular-route.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/controller/deviceApp.js"></script>
<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
$(document).ready(function() {
    $('a[data-toggle="tab"]').on('shown.bs.tab', function(e){
    	var target = $(e.target).attr("href");
    	if(target == '#info'){
    		$('#info_btn').show();
    	} else {
    		$('#info_btn').hide();
    	}
    });
});


function coapModal() {
	$('#coapModal').modal('show');
}

function updateForm() {
	$('#update_data').show();
	$('#update_form').hide();
	
	$('#di_ip').attr("readonly", false);	
	$('#di_port').attr("readonly", false);	
	$('#di_hw_version').attr("readonly", false);	
	$('#di_fw_version').attr("readonly", false);	
	$('#di_remark').attr("readonly", false);
	
	$('#di_ip').css({'border' : ''});
	$('#di_port').css({'border' : ''});
	$('#di_hw_version').css({'border' : ''});
	$('#di_fw_version').css({'border' : ''});
	$('#di_remark').css({'border' : ''});
}

function updateData() {
	$('#update_data').hide();
	$('#update_form').show();

	var options = { 
           //success     : successResultCombo,
           url         : COMMON_URL + "/ajaxDeviceInfoUpdate",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : {
	        	"device_id" : $("#device_id").val(),
	        	"ip" : $("#di_ip").val(),
	        	"port" : $("#di_port").val(),
	        	"hw_version" : $("#di_hw_version").val(),
	        	"fw_version" : $("#di_fw_version").val(),
	        	"remark" : $("#di_remark").val()
	       }
     };             
    
     $.ajax(options);

	$('#di_ip').attr("readonly", true);	
	$('#di_port').attr("readonly", true);	
	$('#di_hw_version').attr("readonly", true);	
	$('#di_fw_version').attr("readonly", true);	
	$('#di_remark').attr("readonly", true);
	
	$('#di_ip').css({'border' : 'none'});
	$('#di_port').css({'border' : 'none'});
	$('#di_hw_version').css({'border' : 'none'});
	$('#di_fw_version').css({'border' : 'none'});
	$('#di_remark').css({'border' : 'none'});
}

</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js"
	charset="UTF-8"></script>

<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
</head>
<body ng-app="deviceApp">
	<!--  wrapper -->
	<div id="content" ng-controller="deviceCtrl">
		<div id="wrapper">
			<div id="page-wrapper" style="width: 100%" class="gray-bg">
				<!-- navigator -->
				<div class="row wrapper page-heading" style="padding: 5px">
					<div class="col-lg-10">
						<h3 style="margin-top: 6px">단말 관리</h3>
					</div>
					<div class="col-lg-2">
						<ol class="breadcrumb" style="float: right; margin-top: 10px;">
							<li class="breadcrumb-item"><a href="#">Home</a></li>
							<li class="breadcrumb-item active"><strong>단말 관리</strong>
							</li>
						</ol>
					</div>
				</div>
				<!-- navigator -->
				<div class="row">
					<ul class="nav nav-tabs" style="width: 100%;">
						<li class="nav-item"><a class="nav-link active"
							data-toggle="tab" href="#info">기본정보</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#object">오브젝트 정보</a></li>
						<!-- 
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#meters">연결미터</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#observe">Observe 상태</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#history">제어이력</a></li>
						 -->
					</ul>
				</div>
				<!-- navigator -->

				<!-- body -->
				<form name="search_form" id="search_form" method="post">
				<input type=hidden name="device_id" id="device_id" value="<%=device_id%>">
				<input type=hidden name="service_id" id="service_id" value="{{device_info.service_id}}">
				<input type=hidden name="device_serial" id="device_serial" value="{{device_info.device_serial}}">
				<div class="row">
					<div class="tab-content" style="width: 100%">
						<div class="tab-pane fade show active" id="info" ng-init="deviceInfo()">
							<div class="col-lg-10">
								<h4 style="margin-top: 6px">단말상세정보</h4>
							</div>
							<table class="table table-bordered white-bg" style="width: 100%">
								<thead>
									<tr>
										<th class="device-detail-head">단말ID</th>
										<td class="device-detail-body">{{device_info.device_id}}</td>
										<th class="device-detail-head">지역본부</th>
										<td class="device-detail-body">{{device_info.parent_branch_nm}} {{device_info.branch_nm}}</td>
									</tr>
									<tr>
										<th class="device-detail-head">단말번호</th>
										<td class="device-detail-body">{{device_info.device_serial}}</td>
										<th class="device-detail-head">제조사</th>
										<td class="device-detail-body">{{device_info.vendor_nm}}</td>
									</tr>
									<tr>
										<th class="device-detail-head">단말IP/PORT</th>
										<td class="device-detail-body"><input type="text" id="di_ip" style="width:80px; border: none" value="{{device_info.ip}}" readonly="readonly" > /
											<input type="text" id="di_port" style="width:80px; border: none" value="{{device_info.port}}" readonly="readonly" ></td>
										<th class="device-detail-head">모델명</th>
										<td class="device-detail-body">{{device_info.model_nm}}</td>
									</tr>
									<tr>
										<th class="device-detail-head">하드웨어 버전</th>
										<td class="device-detail-body"><input type="text" id="di_hw_version" style="width:80px; border: none" value="{{device_info.hw_version}}" readonly="readonly"></td>
										<th class="device-detail-head">펌웨어 버전</th>
										<td class="device-detail-body"><input type="text" id="di_fw_version" style="width:80px; border: none" value="{{device_info.fw_version}}" readonly="readonly"></td>
									</tr>
									<tr>
										<th class="device-detail-head">인증방식</th>
										<td class="device-detail-body">{{device_info.security_mode}}</td>
										<th class="device-detail-head">단말상태</th>
										<td class="device-detail-body">{{device_info.code_local_nm}}</td>
									</tr>
									<tr>
										<th class="device-detail-head">최종통신일시</th>
										<td class="device-detail-body">{{device_info.last_comm_dt}}</td>
										<th class="device-detail-head">등록일시</th>
										<td class="device-detail-body">{{device_info.reg_dt}}</td>
									</tr>
									<tr>
										<th class="device-detail-head">설명</th>
										<td class="device-detail-body" colspan="3"><input type="text" id="di_remark" style="border: none; width: 100%" value="{{device_info.remark}}" readonly="readonly"></td>
									</tr>
								</thead>
							</table>

						</div>
						<div class="tab-pane fade" id="object" ng-init="objectModel()">
							<div class="col-lg-10">
								<h4 style="margin-top: 6px">오브젝트 정보</h4>
							</div>
							<div class="row">
								<div class="col-lg-12">
									<div class="ibox-title" style="border: 0px #f3f3f4; background-color: #f3f3f4">
										<h5 style="margin-top: 6px; margin-right: 50px">단말 ID : {{device_info.device_id}}</h>
										<h5 style="margin-top: 6px; margin-right: 50px">OID : {{device_info.device_oid}}</h>
										<h5 style="margin-top: 6px; margin-right: 50px">제조사 : {{device_info.vendor_nm}}</h>
										<h5 style="margin-top: 6px">모델 : {{device_info.model_nm}}</h>
									</div>
								</div>
								<div class="col-lg-12">
									<div class="ibox-content" style="background-color: #e7eaec">
										<table style="height: 100%; width: 100%; border: 0px #e7eaec">
											<tbody>
												<tr width="100%" >
													<td width="90%">
														<div class="form-group row">
															<label class="col-lg-1 col-form-label" style="padding-left: 10px; font-weight: bold;">검색</label>
															<div class="col-lg-5">
																<select class="form-control" name="searchfield" id="searchfield" style="width: 30%; display: inline-block;">
																	<option value=''>선택</option>
																	<option value='object_id'>오브젝트 ID</option>
																	<option value='object_nm'>오브젝트 명</option>
																</select>
																<input type="text" class="form-control" name="searchquery" id="searchquery" style="width: 69%; height: 33px; vertical-align: top; display: inline;">
															</div>
															<label class="col-lg-1 col-form-label" style="padding-left: 10px; font-weight: bold;">인스턴스</label>
															<div class="col-lg-5">
																<input type="text" class="form-control" name="instances" id="instances" style="width: 100%; height: 33px; vertical-align: top; display: inline;">
															</div>
														</div>
		
													</td>
													<td width="120" style="text-align: right">
														<button class="btn btn-primary" style="height: 40px; width: 40px" type="button" ng-click="objectModel()">
															<i class="fa fa-search"></i>
														</button>
														<button class="btn btn-warning" style="height: 40px; width: 40px" type="button" onclick="resetForm();">
															<i class="fa fa-undo"></i>
														</button>
													</td>
												</tr>
											</tbody>
										</table>
									</div>
								</div>
							</div>
							<div ng-repeat="object in objects">
								<div class="row">
									<div class="col-lg-12">
										<div class="ibox" style="margin-bottom: 0px">
											<div class="ibox-title collapse-link" style="cursor: pointer" data-toggle="collapse" href="\#{{object.object_id}}">
												<h5 style="margin-top: 6px; width: 300px">오브젝트 명  : {{object.object_nm}}</h>
												<h5 style="margin-top: 6px; width: 180px">오브젝트 ID : {{object.object_id}}</h>
												<h5 style="margin-top: 6px; width: 180px">오브젝트 인스턴스 : {{object.instances}}</h>
												<h5 style="margin-top: 6px; width: 160px" ng-if="object.instances == 1">인스턴스 : Single</h>
												<h5 style="margin-top: 6px; width: 160px" ng-if="object.instances == 0">인스턴스 : Multiple</h>
												<h5 style="margin-top: 6px;">설명 : {{object.descr}}</h>
											</div>
											<!-- ibox-content -->
											<div class="ibox-content collapse" id="{{object.object_id}}">
												<div class="table-responsive" ng-repeat="(key, data) in object.instance">
													<table class="table table-striped">
														<thead>
															<tr align="center">
																<td colspan=10 style="text-indent: 1em; background-color: #18a689; border-color: #18a689; color: #FFF">
																	<h4><i class="fas fa-list"></i>&nbsp;인스턴스: {{key}}</h>
																</td>
															</tr>
															<tr align="center">
																<th width="100">리소스 ID</th>
																<th style="text-align: left">리소스명</th>
																<th width="150">리소스값</th>
																<th width="150">단위</th>
																<th width="150">Operation</th>
																<!-- th width="80">속성설정</th>
																<th width="250">Observe 설정/해제</th -->
																<th width="250">값 변경</th>
																<th width="80">실행</th>
																<th width="250">제어상태</th>
															</tr>
														</thead>
														<tbody>
															<tr align="center" ng-repeat="resource in data">
																<td style="text-align: center">{{resource.resource_id}}</td>
																<td align="left">{{resource.resource_nm}}</td>
																<td>{{resource.resource_val}}</td>
																<td>{{resource.unit}}</td>
																<td>
																	<button ng-show="resource.operation.indexOf('R') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		ng-click="read(resource);">Read</button>
																	<button ng-show="resource.operation.indexOf('E') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		ng-click="execute(resource);">Execute</button>
																</td>
																<!-- td>
																	<button
																		ng-show="resource.operation.indexOf('R') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		ng-click="attribute(resource);">속성</button>
																</td>
																<td>
																	<button ng-show="resource.operation.indexOf('R') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		ng-click="observe(resource, 'Y');">Observe</button>
																	<button ng-show="resource.operation.indexOf('R') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		ng-click="observe(resource, 'N');">Cancel</button>
																</td -->
																<td>
																	<div ng-show="object.object_id != 5 && resource.resource_id != 0">
																		<input ng-show="resource.operation.indexOf('W') != -1"
																		type="text" ng-model="newValue" name="newValue"
																		style="width: 100px;">
																		<button ng-show="resource.operation.indexOf('W') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		ng-click="write(resource, newValue);">Write</button>
																	</div>
																	<div ng-show="object.object_id == 5 && resource.resource_id == 0">
																		<button ng-show="resource.operation.indexOf('W') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		onclick="fwListModal()">List</button>
																	</div>
																</td>
																<td>{{resource.operation_method}}</td>
																<td>{{resource.statusMsg}} {{resource.tid}}</td>
																
															</tr>
														</tbody>
													</table>
												</div>

											</div>
											<!-- ibox-content -->
										</div>
									</div>

								</div>
							</div>
						</div>
						<button class="btn btn-outline btn-primary m-t-sm" style="margin-right: 5px; height: 35px; float: right" type="button" onclick="javascript:history.back(-1)">
							<i class="fa fa-undo"> 목록으로 돌아가기</i>
						</button>
						<div id='info_btn' style="float: right">
							<button class="btn btn-outline btn-primary m-t-sm" style="margin-right: 5px; height: 35px" type="button" onclick="coapModal()">
								<i class="fas fa-wifi"> CoAP Ping</i>
							</button>
							<button class="btn btn-outline btn-primary m-t-sm" style="margin-right: 5px; height: 35px" type="button" onclick="">
								<i class="fas fa-retweet"> Reset</i>
							</button>
							<button id="update_form" class="btn btn-outline btn-primary m-t-sm" style="margin-right: 7px; height: 35px" type="button" onclick="updateForm()">
								<i class="fas fa-edit"> 수정</i>
							</button>
							<button id="update_data" class="btn btn-outline btn-primary m-t-sm" style="margin-right: 7px; height: 35px; display: none" type="button" onclick="updateData()">
								<i class="fas fa-edit"> 반영</i>
							</button>
						</div>
					</div>
				</div>
				</form>
				
				<!-- body -->
			</div>
		</div>
		
		<!-- modal -->
		<div class="modal bs-example-modal-sm" id="coapModal" tabindex="-1" role="dialog"
		aria-labelledby="coapModal" aria-hidden="true">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header" style="background-color: #1ab394; color: #FFF">				
					<h4 class="modal-title">CoAP PING</h4>
					<button type="button" class="close" data-dismiss="modal"
						aria-hidden="true">&times;</button>
				</div>
				<form class="form-horizontal" role="form" method="post" id="form">	
				<div class="form-group row">
					<table class="table table-borderless" style="height: 100%; margin: 7px 0px;" border="1">
						<tbody>
							<tr>
								<td>
									<div class="form-group row">
										<label class="col-lg-4 col-form-label" style="padding-left: 10px;">CoAP Ping</label>
										<input type="text" class="form-control" name="sec" id="sec" style="width: 15%; height: 33px; vertical-align: top; display: inline;" value="5">
										<label class="col-lg-1 col-form-label" style="padding-left: 10px;">초</label>
									</div>
								</td>
								<td style="text-align: right">
									<button class="btn btn-primary" style="height: 100%; width: 50px" type="button" ng-click="coapping();">실행</button>
								</td>
							</tr>
							<tr>
								<td colspan="2">
									<div class="form-group form-group-end row">
										<label class="col-sm-4 col-form-label" style="padding-left: 10px;">실행결과</label>
										<div class="col-lg-3">{{coapping.statusMsg}}</div>
									</div>
								</td>
							</tr>
						</tbody>
					</table>
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-default" data-dismiss="modal">닫기</button>
				</div>
			</form>
			</div>
		</div>
		</div>
		<!-- modal -->
	
		<!-- modal -->
		<div class="modal bs-example-modal-sm" id="writeModal" tabindex="-1" role="dialog"
		aria-labelledby="writeModalLabel" aria-hidden="true">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header">				
					<h4 class="modal-title" id="writeModalLabel"></h4>
					<button type="button" class="close" data-dismiss="modal"
						aria-hidden="true">&times;</button>
				</div>
				<div class="modal-body">		
				<form class="form-horizontal" role="form" method="post" id="form">	
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">최소주기</label>
						<div class="col-lg-9"><input type="text" name="pmin" id="pmin" placeholder="pmin" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">최대주기</label>
						<div class="col-lg-9"><input type="text" name="pmax" id="pmax" placeholder="pmax" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">최소값</label>
						<div class="col-lg-9"><input type="text" name="lt" id="lt" placeholder="lt" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">최대값</label>
						<div class="col-lg-9"><input type="text" name="gt" id="gt" placeholder="gt" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">간격</label>
						<div class="col-lg-9"><input type="text" name="step" id="step" placeholder="step" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">Notification</label>
						<div class="col-lg-9">
						<select class="form-control m-b" name="ntype" id="ntype">
	                        <option value="true">true</option>
	                        <option value="false">false</option>                        
	                    </select>
						</div>
					</div>	
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-default" data-dismiss="modal">취소</button>
					<button type="button" class="btn btn-primary" data-dismiss="modal" id="writeSubmit">적용</button>
				</div>
			</form>
			</div>
		</div>
		</div>
		<!-- modal -->
		
		<!-- fw modal -->
		<%@ include file="/views/device/fwModal.jsp"%>
	</div>

	

</body>
</html>