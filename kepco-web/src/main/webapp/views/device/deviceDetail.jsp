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
var target;
$(document).ready(function() {
    $('a[data-toggle="tab"]').on('shown.bs.tab', function(e){
    	target = $(e.target).attr("href");
    	if(target == '#info'){
    		$('#info_btn').show();
    	} else {
    		$('#info_btn').hide();
    	}
    });
});

function resetForm() {
	$("#searchfield").val($("#target option:first").val());
	$("#searchquery").val("");
	$("#instances").val("");
}

function speedModal() {
	$('#speedModal').modal('show');
}

function coapModal() {
	$('#coapModal').modal('show');
}

function rebootModal() {
	$('#rebootModal').modal('show');
}

function updateForm() {
	$('#update_data').show();
	$('#update_form').hide();
	
	$('#di_mobile_no').attr("readonly", false);
	$('#di_ip').attr("readonly", false);
	$('#di_port').attr("readonly", false);	
	$('#di_hw_version').attr("readonly", false);	
	$('#di_fw_version').attr("readonly", false);	
	$('#di_sw_version1').attr("readonly", false);	
	$('#di_sw_version2').attr("readonly", false);	
	$('#di_remark').attr("readonly", false);
	
	$('#di_mobile_no').css({'border' : ''});
	$('#di_ip').css({'border' : ''});
	$('#di_port').css({'border' : ''});
	$('#di_hw_version').css({'border' : ''});
	$('#di_fw_version').css({'border' : ''});
	$('#di_sw_version1').css({'border' : ''});
	$('#di_sw_version2').css({'border' : ''});
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
	        	"mobile_no" : $("#di_mobile_no").val(),
	        	"device_id" : $("#device_id").val(),
	        	"ip" : $("#di_ip").val(),
	        	"port" : $("#di_port").val(),
	        	"hw_version" : $("#di_hw_version").val(),
	        	"fw_version" : $("#di_fw_version").val(),
	        	"sw_version1" : $("#di_sw_version1").val(),
	        	"sw_version2" : $("#di_sw_version2").val(),
	        	"remark" : $("#di_remark").val()
	       }
     };             
    
     $.ajax(options);

	$('#di_mobile_no').attr("readonly", true);	
	$('#di_ip').attr("readonly", true);	
	$('#di_port').attr("readonly", true);	
	$('#di_hw_version').attr("readonly", true);	
	$('#di_fw_version').attr("readonly", true);	
	$('#di_sw_version1').attr("readonly", true);	
	$('#di_sw_version2').attr("readonly", true);	
	$('#di_remark').attr("readonly", true);
	
	$('#di_mobile_no').css({'border' : 'none'});
	$('#di_ip').css({'border' : 'none'});
	$('#di_port').css({'border' : 'none'});
	$('#di_hw_version').css({'border' : 'none'});
	$('#di_fw_version').css({'border' : 'none'});
	$('#di_sw_version1').css({'border' : 'none'});
	$('#di_sw_version2').css({'border' : 'none'});
	$('#di_remark').css({'border' : 'none'});
}

function firmwarelist() {
	var scope = angular.element($('#content')).scope();
	scope.firmware();
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
						<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> ?????? ????????????</h2>
					</div>
				</div>
				<!-- navigator -->
				<div class="row">
					<ul class="nav nav-tabs" style="width: 100%;">
						<li class="nav-item"><a class="nav-link active"
							data-toggle="tab" href="#info" ng-click="deviceInfo()">????????????</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#firmware" ng-click="firmware()">SW ???????????????</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#object" ng-click="objectModel()">???????????? ??????</a></li>
						<!-- 
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#observe">Observe ??????</a></li>
						<li class="nav-item"><a class="nav-link" data-toggle="tab"
							href="#history">????????????</a></li>
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
							<table class="table table-bordered white-bg" style="width: 100%">
								<thead>
									<tr>
										<th class="device-detail-head">????????????</th>
										<td class="device-detail-body"><span id="device_serial_span" style="display: none;">{{device_info.device_serial}}</span></td>
										<th class="device-detail-head">????????????</th>
										<td class="device-detail-body"><span id="code_local_nm_span" style="display: none;">{{device_info.code_local_nm}}</span></td>
									</tr>
									<tr>
										<th class="device-detail-head">????????????</th>
										<td class="device-detail-body"><span id="branch_span" style="display: none;">{{device_info.parent_branch_nm}} {{device_info.branch_nm}}</span></td>
										<th class="device-detail-head">??????IP/PORT</th>
										<td class="device-detail-body"><input type="text" id="di_ip" style="width:100px; display:none; border: none" value="{{device_info.ip}}" readonly="readonly" > /
											<input type="text" id="di_port" style="width:80px; display:none; border: none" value="{{device_info.port}}" readonly="readonly" ></td>
										
									</tr>
									<tr>
										<th class="device-detail-head">?????????</th>
										<td class="device-detail-body"><span id="vendor_nm_span" style="display: none;">{{device_info.vendor_nm}}</span></td>
										<th class="device-detail-head">????????????</th>
										<td class="device-detail-body">
											<input type="text" id="di_mobile_no" style="width:100%; display:none; border: none" value="{{device_info.mobile_no}}" readonly="readonly" ></td>
										</td>
									</tr>
									<tr>
										<th class="device-detail-head">???????????? ??????</th>
										<td class="device-detail-body"><input type="text" id="di_hw_version" style="width:100px; display:none; border: none" value="{{device_info.hw_version}}" readonly="readonly"></td>
										<th class="device-detail-head">SW ??????</th>
										<td class="device-detail-body"><input type="text" id="di_fw_version" style="width:100px; display:none; border: none" value="{{device_info.fw_version}}" readonly="readonly"></td>
									</tr>
									<tr>
										<th class="device-detail-head">DLMS AGENT SW ??????</th>
										<td class="device-detail-body"><input type="text" id="di_sw_version1" style="width:100px; display:none; border: none" value="{{device_info.sw_version1}}" readonly="readonly"></td>
										<th class="device-detail-head">LWM2M CLIENT SW ??????</th>
										<td class="device-detail-body"><input type="text" id="di_sw_version2" style="width:100px; display:none; border: none" value="{{device_info.sw_version2}}" readonly="readonly"></td>
									</tr>
									<!-- 
									<tr>
										<th class="device-detail-head">????????????</th>
										<td class="device-detail-body"><span id="security_mode_span" style="display: none;">{{device_info.security_mode}}</span></td>
										<th class="device-detail-head">????????????</th>
										<td class="device-detail-body"><span id="code_local_nm_span" style="display: none;">{{device_info.code_local_nm}}</span></td>
									</tr>
									-->
									<tr>
										<th class="device-detail-head">??????????????????</th>
										<td class="device-detail-body"><span id="last_comm_dt_span" style="display: none;">{{device_info.last_comm_dt}}</span></td>
										<th class="device-detail-head">????????????</th>
										<td class="device-detail-body"><span id="reg_dt_span" style="display: none;">{{device_info.reg_dt}}</span></td>
									</tr>
									<tr>
										
										<th class="device-detail-head">??????</th>
										<td class="device-detail-body" colspan="3"><input type="text" id="di_remark" style="border: none; display:none; width: 100%" value="{{device_info.remark}}" readonly="readonly"></td>
									</tr>
								</thead>
							</table>
						</div>
						
						<div class="tab-pane fade" id="firmware">
							<div class="row">
								<input type="hidden" id="limit" name="limit" value ="10" class="form-control">
								<input type="hidden" id="page" name="page" value ="1" class="form-control" onchange="firmwarelist()">
								<div class="col-lg-12">
									<div class="ibox-content">
										<table class="table table-borderless" style="height: 100%; style="margin-bottom: 7px;" border="1">
											<tbody>
												<tr class="table-border">
													<td width="90%">
														<div class="form-group row" style="margin-left: 0px">
															<label class="col-sm-2 col-form-label">SW ???</label>
															<div class="col-lg-4">
																<input type="text" class="form-control" name="fw_file_nm_b" id="fw_file_nm_b" style="height: 38px; display: inline;">
															</div>
															<label class="col-sm-2 col-form-label">SW ??????</label>
															<div class="col-lg-4">
																<input type="text" class="form-control" name="fw_version_b" id="fw_version_b" style="height: 38px; display: inline;">
															</div>
														</div>
													</td>
													<td width="15%" style="text-align: right">
														<button class="btn btn-primary" style="height: 35px; width: 40px" type="button" onclick="firmwarelist()">
															<i class="fa fa-search"></i>
														</button>
														<button class="btn btn-warning" style="height: 35px; width: 40px" type="button" onclick="fwUploadModal();">
															<i class="fa fa-upload"></i>
														</button>
													</td>
												</tr>
											</tbody>
										</table>
										
										<div>
											<!-- page option -->
											<div class="row m-t-n-n" style="margin:-1px"  >
												<div style="width :100%;vertical-align:center" class="m-t-n-sm">
													<label id="cur_page_num" class="col-form-label"></label>
													<div style ="float:right; margin-bottom:5px">
														<select id="data_per_page" class="form-control" name="data_per_page" onchange="javascript:changeLimit(this);">
															<option value=10 selected>10??????</option>
															<option value=100>100?????? </option>
															<option value=250>250?????? </option>
														</select>
													</div>
												</div>
											</div>
											<!-- grid -->
											<div id="grid_b" style="height:400px;" class="ag-theme-balham"></div>
											
											<!-- grid pagination -->
											<center>
											<div id="grid-page" style ="display:none;" class="m-t-sm">
												<ul id="pagination" class="pagination"></ul>
											</div>
											</center>
								        </div>
									</div>
								</div>
							</div>
						</div>
						
						<div class="tab-pane fade" id="object">
							<div class="row">
								<div class="col-lg-12">
									<div class="ibox-title" style="border: 0px #f3f3f4; background-color: #f3f3f4">
										<!-- <h5 style="margin-top: 6px; margin-right: 50px">?????? ID : {{device_info.device_id}}</h> -->
										<h5 style="margin-top: 6px; margin-right: 50px">OID : {{device_info.device_oid}}</h>
										<h5 style="margin-top: 6px; margin-right: 50px">????????? : {{device_info.vendor_nm}}</h>
										<h5 style="margin-top: 6px">?????? : {{device_info.model_nm}}</h>
									</div>
								</div>
								<div class="col-lg-12">
									<div class="ibox-content" style="background-color: #e7eaec">
										<table style="height: 100%; width: 100%; border: 0px #e7eaec">
											<tbody>
												<tr width="100%" >
													<td width="90%">
														<div class="form-group row">
															<label class="col-lg-1 col-form-label" style="padding-left: 10px; font-weight: bold;">??????</label>
															<div class="col-lg-5">
																<select class="form-control" name="searchfield" id="searchfield" style="width: 30%; display: inline-block;">
																	<option value=''>??????</option>
																	<option value='object_id'>???????????? ID</option>
																	<option value='object_nm'>???????????? ???</option>
																</select>
																<input type="text" class="form-control" name="searchquery" id="searchquery" style="width: 69%; height: 33px; vertical-align: top; display: inline;">
															</div>
															<label class="col-lg-1 col-form-label" style="padding-left: 10px; font-weight: bold;">????????????</label>
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
											<div class="ibox-title collapse-link" style="cursor: pointer" data-toggle="collapse" href="\#{{object.object_id}}_obj">
												<h5 style="margin-top: 6px; width: 300px">???????????? ???  : {{object.object_nm}}</h>
												<h5 style="margin-top: 6px; width: 180px">???????????? ID : {{object.object_id}}</h>
												<h5 style="margin-top: 6px; width: 180px">???????????? ???????????? : {{object.instances}}</h>
												<h5 style="margin-top: 6px; width: 160px" ng-if="object.instances == 1">???????????? : Single</h>
												<h5 style="margin-top: 6px; width: 160px" ng-if="object.instances == 0">???????????? : Multiple</h>
												<h5 style="margin-top: 6px;">?????? : {{object.descr}}</h>
											</div>
											<!-- ibox-content -->
											<div class="ibox-content collapse" id="{{object.object_id}}_obj">
												<div class="table-responsive" ng-repeat="(key, data) in object.instance">
													<table class="table table-striped">
														<thead>
															<tr align="center">
																<td colspan=10 style="text-indent: 1em; background-color: #18a689; border-color: #18a689; color: #FFF">
																	<h4><i class="fas fa-list"></i>&nbsp;????????????: {{key}}</h>
																</td>
															</tr>
															<tr align="center">
																<th width="100">????????? ID</th>
																<th style="text-align: left">????????????</th>
																<th width="150">????????????</th>
																<th width="150">??????</th>
																<th width="150">Operation</th>
																<!-- th width="80">????????????</th>
																<th width="250">Observe ??????/??????</th -->
																<th width="250">??? ??????</th>
																<th width="80">??????</th>
																<th width="250">????????????</th>
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
																		style="background-color: #FA5858;border-color: #FA5858"
																		ng-click="execute(resource);">Execute</button>
																</td>
																<!-- td>
																	<button
																		ng-show="resource.operation.indexOf('R') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		ng-click="attribute(resource);">??????</button>
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
																		style="background-color: #2E64FE;border-color: #2E64FE"
																		ng-click="write(resource, newValue);">Write</button>
																	</div>
																	<div ng-show="object.object_id == 5 && resource.resource_id == 1">
																		<input ng-show="resource.operation.indexOf('W') != -1"
																		type="text" ng-model="newValue" name="newValue"
																		style="width: 100px;">
																		<button ng-show="resource.operation.indexOf('W') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		style="background-color: #2E64FE;border-color: #2E64FE"
																		ng-click="write(resource, newValue);">Write</button>
																	</div>
																	<div ng-show="object.object_id == 5 && resource.resource_id == 0">
																		<button ng-show="resource.operation.indexOf('W') != -1"
																		class="btn btn-primary btn-xs" type="button"
																		style="background-color: #2E64FE;border-color: #2E64FE"
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
							<i class="fa fa-undo"> ???????????? ????????????</i>
						</button>
						<div id='info_btn' style="float: right">
							<button class="btn btn-outline btn-primary m-t-sm" style="margin-right: 5px; height: 35px" type="button" onclick="speedModal()">
								<i class="fas fa-rss"> ?????? ?????????</i>
							</button>
							<button class="btn btn-outline btn-primary m-t-sm" style="margin-right: 5px; height: 35px" type="button" onclick="coapModal()">
								<i class="fas fa-wifi"> CoAP Ping</i>
							</button>
							<button class="btn btn-outline btn-primary m-t-sm" style="margin-right: 5px; height: 35px" type="button" onclick="rebootModal()">
								<i class="fas fa-retweet"> Reset</i>
							</button>
							<button id="update_form" class="btn btn-outline btn-primary m-t-sm" style="margin-right: 7px; height: 35px" type="button" onclick="updateForm()">
								<i class="fas fa-edit"> ??????</i>
							</button>
							<button id="update_data" class="btn btn-outline btn-primary m-t-sm" style="margin-right: 7px; height: 35px; display: none" type="button" onclick="updateData()">
								<i class="fas fa-edit"> ??????</i>
							</button>
						</div>
					</div>
				</div>
				</form>
				
				<!-- body -->
			</div>
		</div>
		
		
		<!-- modal -->
		<div class="modal bs-example-modal-sm" id="speedModal" tabindex="-1" role="dialog"
		aria-labelledby="speedModal" aria-hidden="true">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header" style="background-color: #1ab394; color: #FFF">				
					<span class="modal-title" style="font-size: 20px; font-weight: bold">Payload ??????/?????? ?????? ?????????</span>
					<button type="button" class="close" data-dismiss="modal"
						aria-hidden="true">&times;</button>
				</div>
				<form class="form-horizontal" role="form" method="post" id="form">	
				<div class="form-group row">
					<table class="table table-borderless" style="height: 100%; margin: 7px 0px;" border="1">
						<tbody>
							<tr>
								<td style="text-align: right">
									<button class="btn btn-primary" style="height: 100%;" type="button" ng-click="speedtest();">?????? ????????? ??????</button>
								</td>
							</tr>
							<tr>
								<td colspan="2">
									<div class="form-group form-group-end row">
										<H3>[??????/?????? ??????????????? ??????]</H3>
										<textarea style="border: 0px; min-height: 90px; width: 100%">{{speedtest.statusMsg}}</textarea>
									</div>
								</td>
							</tr>
						</tbody>
					</table>
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-default" data-dismiss="modal">??????</button>
				</div>
			</form>
			</div>
		</div>
		</div>
		<!-- modal -->
		
		<!-- modal -->
		<div class="modal bs-example-modal-sm" id="coapModal" tabindex="-1" role="dialog"
		aria-labelledby="coapModal" aria-hidden="true">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header" style="background-color: #1ab394; color: #FFF">				
					<h3 class="modal-title">CoAP PING</h3>
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
										<span class="modal-title" style="font-size: 20px; font-weight: bold">CoAP Ping</span>
										<input type="text" class="form-control" name="sec" id="sec" style="width: 15%; height: 33px; vertical-align: top; display: inline;" value="5">
										<label class="col-lg-1 col-form-label" style="padding-left: 10px;">???</label>
									</div>
								</td>
								<td style="text-align: right">
									<button class="btn btn-primary" style="height: 100%; width: 60px" type="button" ng-click="coapping();">??????</button>
								</td>
							</tr>
							<tr>
								<td colspan="2">
									<div class="form-group form-group-end row">
										<label class="col-lg-3 col-form-label" style="padding-left: 10px;">????????????</label>
										<textarea style="border: 0px; width: 100%">{{coapping.statusMsg}}</textarea>
									</div>
								</td>
							</tr>
						</tbody>
					</table>
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-default" data-dismiss="modal">??????</button>
				</div>
			</form>
			</div>
		</div>
		</div>
		<!-- modal -->
	
		<!-- modal -->
		<div class="modal bs-example-modal-sm" id="rebootModal" tabindex="-1" role="dialog"
		aria-labelledby="rebootModal" aria-hidden="true">
		<div class="modal-dialog">
			<div class="modal-content">
				<div class="modal-header" style="background-color: #1ab394; color: #FFF">
					<span class="modal-title" style="font-size: 20px; font-weight: bold">Reset</span>
					<button type="button" class="close" data-dismiss="modal"
						aria-hidden="true">&times;</button>
				</div>
				<div class="modal-content" style="text-align: center; padding: 15px">
					<h3><string>????????? ???????????????????</string></h3>
				</div>
				<div class="modal-footer" style="justify-content: center">
					<button type="button" class="btn btn-primary" data-dismiss="modal" ng-click="reset();">??????</button>
					<button type="button" class="btn btn-default" data-dismiss="modal">??????</button>
				</div>
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
					<span class="modal-title" style="font-size: 20px; font-weight: bold" id="writeModalLabel"></span>	
					<button type="button" class="close" data-dismiss="modal"
						aria-hidden="true">&times;</button>
				</div>
				<div class="modal-body">		
				<form class="form-horizontal" role="form" method="post" id="form">	
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">????????????</label>
						<div class="col-lg-9"><input type="text" name="pmin" id="pmin" placeholder="pmin" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">????????????</label>
						<div class="col-lg-9"><input type="text" name="pmax" id="pmax" placeholder="pmax" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">?????????</label>
						<div class="col-lg-9"><input type="text" name="lt" id="lt" placeholder="lt" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">?????????</label>
						<div class="col-lg-9"><input type="text" name="gt" id="gt" placeholder="gt" class="form-control"></div>
					</div>
					<div class="form-group row">
						<label class="col-lg-3 col-form-label">??????</label>
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
					<button type="button" class="btn btn-default" data-dismiss="modal">??????</button>
					<button type="button" class="btn btn-primary" data-dismiss="modal" id="writeSubmit">??????</button>
				</div>
			</form>
			</div>
		</div>
		</div>
		<!-- modal -->
		
		<!-- fw modal -->
		<%@ include file="/views/device/fwModal.jsp"%>
	</div>
	<div id="loading">
		<div id="loading-image" class="spinner-border" role="status">
			<img id="loading-image" src="<%=COMMON_PATH_IMG%>/loading.gif" alt="Loading..." /></div>
		</div>
	</div>
</body>
</html>