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
<script src="<%=COMMON_PATH_JS%>/controller/meterApp.js?version=1"></script>

<!-- Data picker -->
<script src="<%=COMMON_PATH_JS%>/bootstrap-datepicker.js"></script>

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>

<script src="https://cdn.jsdelivr.net/npm/sweetalert2@9"></script>

<style>
  div .ibox-title {
		/* background-color: #dee2e6; */
		background-color: #F3F3F4;
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
	<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> ?????? ????????????</h2>
</div>
<div class="col-lg-2" >
	<ol class="breadcrumb" style="float:right;margin-top:10px;">
		</ol>
	</div>						
</div>
<!-- navigator -->
<!-- body -->
<div>
	<div class="col-lg-12">	
		<div class="ibox">
			<div class="ibox-content" style="background-color: #F3F3F4;">
				<div class="row m-b-md ">
					<div class="col-lg-6">
                    <div class="tabs-container" style=width:200%;>
                        <ul class="nav nav-tabs" role="tablist">
                            <li><a class="nav-link active" data-toggle="tab" href="#tab-1">????????????</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-2" ng-click="meterResourceList(2);">?????? ?????? ??????</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-3" ng-click="meterResourceList(3);">?????? ????????? ??????</a></li>
                          <!--   <li><a class="nav-link" data-toggle="tab" href="#tab-4">OBIS ??????</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-5">TOU?????? ??????</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-6">????????????</a></li> -->
                        </ul>
                        <div class="tab-content">
                            <div role="tabpanel" id="tab-1" class="tab-pane active">
                                <div class="panel-body">
                                	<div class="ibox">
	                                	<div class="ibox-title" style=width:100%;>
	                                		<h3>?????? ?????? &lt;????????????: <span id="device_serial"></span>&gt;</h3>
	                                	</div>
		                                	<table class="table text-center">
		                                		<colgroup>
										            <col width="12%" />
										            <col width="12%" />
										            <col width="12%" />
										            <col width="12%" />
										            <col width="12%" />
										            <col width="12%" />
										            <col width="12%" />
										            <col width="18%" />
												</colgroup>
												<tbody>
													<tr>
														<th class="text-navy" scope="row">?????? ??????:</th>
														<td id = "op_status"></td>
														<th class="text-navy" scope="row">?????????:</th>
														<td id = "">SKT</td>
														<th class="text-navy" scope="row">?????? ??????:</th>
														<td id = "comm_type"></td>
														<th class="text-navy" scope="row">?????? ?????? ??????:</th>
														<td id = "last_comm_dt"></td>
													</tr>
												</tbody>
											</table>
									</div>
									<div class="ibox">
										<div class="ibox-title">
	                                		<h3>?????? ?????? &lt;?????? ??????: <span id="meter_serial"></span>&gt;</h3>
	                                	</div>
										<table class="table text-center">
											 <colgroup>
									            <col width="10%" />
									            <col width="10%" />
									            <col width="12%" />
									            <col width="5%" />
									            <col width="12%" />
									            <col width="7%" />
									            <col width="14%" />
									            <col width="20%" />
											</colgroup>
											<tbody>
												<tr>
													<th class="text-navy" scope="row">????????????:</th>
													<td id = "meter_type"></td>
													<th class="text-navy" scope="row">?????? ??????(???):</th>
													<td id = "lp_period"></td>
													<th class="text-navy" scope="row">??????????????? ????????????:</th>
													<td id = "acon"></td>
													<th class="text-navy" scope="row"> COSEM ?????? ?????????:</th>
													<td id = "cosem_device_name"></td>
												</tr>
												<tr>
													<th class="text-navy" scope="row">?????????:</th>
													<td id = "vendor_nm"></td>
													<th class="text-navy" scope="row">??????????????????:</th>
													<td id = "billing_dt"></td>
													<th class="text-navy" scope="row">??????????????? ????????????:</th>
													<td id = "rcon"></td>
													<th class="text-navy" scope="row">????????????:</th>
													<td id = "meter_phase"></td>
												</tr>
												<tr>
													<th class="text-navy" scope="row">?????????????????????:</th>
													<td id = "net_metering"></td>
													<th class="text-navy" scope="row">????????????????????????(???):</th>
													<td id = "avg_power_period"></td>
													<th class="text-navy" scope="row">??????????????? ????????????:</th>
													<td id = "pcon"></td>
													<th class="text-navy" scope="row">????????? ?????? ??????:</th>
													<td id = "last_lp_dt"></td>
												</tr>
											</tbody>
										</table>
									</div>
                                </div>
                            </div>
                            <div role="tabpanel" id="tab-2" class="tab-pane">
									<div style="background-color: #FFF">
										<div class="row" style="padding-top: 10px">
											<div class="col-lg-12">
												<div class="ibox">
													<div class="row m-b-md">
														<div>
										                    <div class="widget-left-color-box p-sm m-l-n-sm navy-bg">
										                        <div >
										                           <i class="fa fa-sitemap fa-5x"></i>
										                        </div>
										                	</div>
										                </div>
										                <div class=" gray-bg m-r-n-sm"   style="width:90%"> 
										                
											                <table class="table-borderless text-center m-t" style="width:100%" >
																<thead>
																	<tr class="text-navy">
																		<th>????????????</th>
																		<th>????????????</th>
																		<th>????????????</th>
																		<th>????????????(???)</th>
																		<th>?????????????????????</th>
																	</tr>
																</thead>
																<tbody>
																	<tr>
																		<td><h2 id = "device_serial_tab2"></h2></td>
																		<td><h2 id = "meter_type_tab2"></h2></td>
																		<td><h2 id = "meter_serial_tab2"></h2></td>
																		<td><h2 id = "lp_period_tab2"></h2></td>
																		<td><h2 id = "net_metering_tab2"></h2></td>
																	</tr>
																</tbody>
															</table>
														</div>
													</div>
													
													<div class="ibox-content">
														<div> 
															<input type="hidden" id=device_id name="device_id" value=""> </input>
															
														</div>
														<div id="resource">
															<table class="table">
																<thead class ="gray-bg">
																	<tr align="center" >
																		<th>????????? ID</th>
																		<th style="text-align: left">????????????</th>
																		<th>????????????</th>
																		<th>?????? <i class="fas fa-info-circle" style="font-size: 14px; vertical-align: middle; cursor: pointer;" onclick="viewInfo()"></i></th>
																		<th colspan="2">??? ??????</th>																		
																	</tr>
																</thead>
																<tbody>
																	<tr align="center"  ng-repeat="resource in resources">
																		<td>{{resource.resource_id}}</td>
																		<td align="left">{{resource.resource_nm}}</td>
																		<td>{{resource.resource_val}}</td>
																		<td style="max-width: 200px;">{{resource.unit}}
																			<button ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id == '105'"
																					class="btn btn-primary btn-outline" style="margin-right:10px; max-width: 300px;"  type="button" onclick="popupObisCode2();">
																					<i class="fa fa-search"> OBIS ?????? ??????</i>
																			</button>
																		</td>
																		<td style="width: 200px;">
																			<div ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id == '101'">
																				<select ng-model="resource.newValue" name="newValue" name="meterSerial" style="min-width: 300px;height:26px;">
																				    <option ng-repeat="row in meterSerialList" value="{{row.id}}">{{row.name}}</option>
																				</select>
																			</div>
																			<div ng-if="resource.operation.indexOf('W') != -1 && (resource.resource_id == '102' 
																				|| resource.resource_id == '103' 
																				|| resource.resource_id == '106')">
																				<input type="text" ng-model="resource.newValue" name="resource_val" id="{{resource.resource_nm}}" ng-required="true" style="min-width: 300px;">
																				</input>	
																																							
																			</div>																			
																			<div ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id == '104'">
																				<select ng-model="resource.newValue" name="newValue" id="{{resource.resource_nm}}" ng-required="true" style="min-width: 300px;height:26px;" id="command-select" >
																					<option value="192" selected>GET </option>
																					<option value="193" >SET</option>																					
																					<option value="5">READ </option>
																					<option value="6">WRITE </option>
																				</select>
																			</div>
																			<div ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id == '105'">
																				<input type="text" ng-model="resource.newValue" name="obis_code" id="obis_code{{resource.resource_id}}" ng-required="true" style="min-width: 300px;" readonly>																																																												
																			</div>
																		</td>
																		<td style="width:250px;">{{resource.obis_nm}} {{resource.strUnit}}<font color="red"> {{resource.msg}}</font></td>
																	</tr>
																</tbody>
															</table>
															<div name="schedule-buttons" class="row" style="margin:0; height:35px">
																
																<button class="btn btn-primary" style="margin-right:10px; width: 140px" type="button" ng-click="settingBillingDt(resources);">
																	<i class="fa"> ??????????????? ?????? </i>
																</button>
																<button class="btn btn-primary" style="margin-right:10px; width: 140px" type="button" ng-click="settingLpPeriod(resources);">
																	<i class="fa"> LP ?????? ?????? </i>
																</button>
																<button class="btn btn-danger" style="margin-right:10px; width: 140px" type="button" ng-click="write(resources)">
																	<i class="fa fa-play"> Access ??????</i>
																</button>
															</div>
														</div>
													</div>
													<!-- ibox-content -->
												</div>
												
											</div>
											
										</div>
									</div>
									
                            </div>
                                                        
                            <div role="tabpanel" id="tab-3" class="tab-pane">
									<div style="background-color: #FFF">
										<div class="row" style="padding-top: 10px">
											<div class="col-lg-12">
												<div class="ibox">
													<div class="row m-b-md">
														<div>
										                    <div class="widget-left-color-box p-sm m-l-n-sm navy-bg">
										                        <div >
										                           <i class="fa fa-sitemap fa-5x"></i>
										                        </div>
										                	</div>
										                </div>
										                <div class=" gray-bg m-r-n-sm"   style="width:90%"> 
											                <table class="table-borderless text-center m-t" style="width:100%" >
																<thead>
																	<tr class="text-navy">
																		<th>????????????</th>
																		<th>????????????</th>
																		<th>????????????</th>
																		<th>????????????(???)</th>
																		<th>?????????????????????</th>
																	</tr>
																</thead>
																<tbody>
																	<tr>
																		<td><h2 id = "device_serial_tab3"></h2></td>
																		<td><h2 id = "meter_type_tab3"></h2></td>
																		<td><h2 id = "meter_serial_tab3"></h2></td>
																		<td><h2 id = "lp_period_tab3"></h2></td>
																		<td><h2 id = "net_metering_tab3"></h2></td>
																	</tr>
																</tbody>
															</table>
														</div>
													</div>
													
													<div class="ibox-content">
														<input type="hidden" name="object_instance_id" id="object_instance_id" value="">															
														<div id="resource">
															<table class="table">
																<thead class ="gray-bg">
																	<tr align="center" >
																		<th>????????? ID</th>
																		<th style="text-align: left">????????????</th>
																		<th>????????????</th>
																		<th>?????? <i class="fas fa-info-circle" style="font-size: 14px; vertical-align: middle; cursor: pointer;" onclick="viewInfo()"></i></th>
																		<th colspan="2">??? ??????</th>
																	</tr>
																</thead>
																<tbody>
																	<tr align="center"  ng-repeat="resource in resources">
																		<td>{{resource.resource_id}}</td>
																		<td align="left">{{resource.resource_nm}}</td>
																		<td>{{resource.resource_val}}</td>
																		<td style="max-width: 200px;">{{resource.unit}}
																			<button  ng-show="resource.operation.indexOf('W') != -1 && resource.resource_id == '113'" ng-model="newValue" name="newValue"
																					class="btn btn-primary btn-outline" style="margin-right:10px; max-width: 200px;" type="button" onclick="popupObisCode();">
																					<i class="fa fa-search"> OBIS ?????? ??????</i>
																			</button>
																		</td>
																		<td style="width:250px;">
																			<div ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id == '104'">
																				<select ng-model="resource.newValue" style="min-width: 300px;height:26px;">
																				    <option ng-repeat="row in meterSerialList" ng-required="true" value="{{row.id}}">{{row.name}}</option>
																				</select>
																			</div>
																			<div ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id != '104' && resource.resource_id != '113'">
																				<input type="text" ng-model="resource.newValue" ng-required="true" name="newValue" id="{{resource.resource_nm}}" style="min-width: 300px;">
																			</div>	
																			<div ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id == '113'">
																				<input type="text" ng-model="resource.newValue" ng-required="true" name="obis_code3" id="obis_code_tab3_{{resource.resource_id}}" style="min-width: 300px;" readonly>
																			</div>
																		</td>
																		<td style="width:200px;">{{resource.obis_nm}} <font color="red">{{resource.msg}}</font></td>
																	</tr>
																</tbody>
															</table>															
															<div name="schedule-buttons" class="row" style="margin:0; height:35px">
																<button class="btn btn-danger" style="margin-right:10px; width: 200px" type="button" ng-click="write(resources)">
																	<i class="fa fa-play"> ?????? ????????? ??????</i>
																</button>
															</div>
															
															
															
														</div>
													</div>
													<!-- ibox-content -->
												</div>
												
											</div>
											
										</div>
									</div>
									
                            </div>
                        </div>
                   		 </div>
                	</div>
				<form name="control_detail_form" id="control_detail_form" method="post">
					<input type="hidden" id="_meter_serial" name="_meter_serial" value="${meter_serial}" class="form-control">
				</form>
					
				</div>
				<!--  end : summary_area  -->
				
				<div class="modal bs-example-modal-sm" id="infoModal" tabindex="-1" role="dialog"
				aria-labelledby="infoModal" aria-hidden="true">
				<div class="modal-dialog" style="max-width: 650px">
					<div class="modal-content">
						<div class="modal-header" style="background-color: #1ab394; color: #FFF">				
							<h4 class="modal-title">?????? ??????</h4>
							<button type="button" class="close" data-dismiss="modal"
								aria-hidden="true">&times;</button>
						</div>
						<div class="modal-content" style="text-align: center; padding: 15px">
							<table class="table">
								<thead class ="gray-bg">
									<tr>
										<th align="center">??????</th>
										<th align="center">??????</th>
										<th align="center">??????</th>
									</tr>
								</thead>
								<tbody>
									<tr align="center">
										<td> MeterID</td>
										<td> ?????? ????????????</td>
										<td></td>
									</tr>
									<tr align="center">
										<td>* * * * *</td>
										<td>???????????? ???(0-59) ??????(0-23) ???(1-31) ???(1-12) ??????(0-7)</td>
										<td>
											- ????????? 0,7??? ?????????<br>
											- *??? ??? ?????? ????????? ??????
										</td>
									</tr>
								</tbody>
							</table>
						</div>
						<div class="modal-footer" style="justify-content: center">
							<button type="button" class="btn btn-default" data-dismiss="modal">??????</button>
						</div>
					</div>
				</div>
				</div>							

			   <button class="btn btn-outline btn-primary m-t-sm" style="height: 100%; float: right" type="button" onclick="javascript:history.back(-1)">
					<i class="fa fa-undo"> ???????????? ????????????</i>
				</button>
			              
			</div>
		</div>
	</div>
</div>
<!-- body -->
</div>
</div>	
</div>

<script type="text/javascript" charset="utf-8">	
var meterTypeCode;
var obis_code;

var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};
 
function ajaxSearchForm() {

    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxMeterDetailInfo",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#control_detail_form").serialize()
     };             
    
     $.ajax(options);
}

function resetForm(){
	$("#search_form")[0].reset();	
};

function showRequest() {
	// $("#loading").show();
}


function successResultHandler(data, status) {
	
	$('#device_serial').text(data.result.device_serial);
	$('#device_serial_tab2').text(data.result.device_serial);
	$('#device_serial_tab3').text(data.result.device_serial);
	$('#meter_serial').text(data.result.meter_serial);

	$('#meter_serial_tab2').text(data.result.meter_serial);
	$('#meter_serial_tab3').text(data.result.meter_serial);
	$('#reg_dt').text(data.result.reg_dt);
 	$('#last_comm_dt').text(data.result.last_comm_dt);
 	$('#last_lp_dt').text(data.result.last_comm_dt);
	$('#lp_period').text(data.result.lp_period);
	$('#lp_period_tab2').text(data.result.lp_period);
	$('#lp_period_tab3').text(data.result.lp_period);
	$('#meter_type').text(data.result.meter_type);	
	$('#meter_type_tab2').text(data.result.meter_type);	
	$('#meter_type_tab3').text(data.result.meter_type);	
	$('#op_status').text(data.result.code_local_nm);	
	meterTypeCode = data.result.meter_type_code;	
	$('#device_id').val(data.result.device_id);	
	
	$('#meter_phase').text(data.result.meter_phase);
	$('#ip').text(data.result.ip);
	$('#vendor_nm').text(data.result.vendor_nm);
	$('#comm_type').text(data.result.comm_type);
	
	$('#cosem_device_name').text(data.result.cosem_device_name);
	
	$('#acon').text(formatNumber(data.result.acon,0));	
	$('#rcon').text(formatNumber(data.result.rcon,0));	
	$('#pcon').text(formatNumber(data.result.pcon,0));
	
	$('#billing_dt').text(data.result.billing_dt);
	$('#itime').text(data.result.itime);
	$('#mtime').text(data.result.mtime);
	
	if(data.result.net_metering == "0") {
		$('#net_metering').text("????????? ??????");
		$('#net_metering_tab2').text("????????? ??????");
		$('#net_metering_tab3').text("????????? ??????");
	} else {
		$('#net_metering').text("????????? ??????");
		$('#net_metering_tab2').text("????????? ??????");
		$('#net_metering_tab3').text("????????? ??????");
	}
	
	$('#avg_power_period').text(data.result.avg_power_period);
	
	
		 //$("#testselect").prepend("<option value="+data.result.meter_serial+">"+data.result.meter_serial+"</option>");
	$("#target_meter104").prepend("<option value="+data.result.meter_serial+">"+data.result.meter_serial+"</option>");
}

var winObj;
function popupObisCode(){ //???????????????

	var opts="width=1200, height=750,left=200, top=200, resizable=no, toolbar=yes";
	if(winObj)
        winObj.close();
	var param = "?meter_type="+meterTypeCode;
    winObj = window.open(COMMON_URL+"/obisCodePopup"+param, "", opts);
}


function popupObisCode2(){ //????????????
	
	var opts="width=1200, height=750,left=200, top=200, resizable=no, toolbar=yes";
	if(winObj)
        winObj.close();
	var param = "?meter_type="+meterTypeCode;
	    winObj = window.open(COMMON_URL+"/obisCodePopup2"+param, "", opts);
}

function init() {
	// init
	// form search
	ajaxSearchForm();
}

$(document).ready(function() {	
	init();
});


function Scope() {
    var scope = angular.element(document.getElementById("content")).scope(); 
    return scope;
}

function settingObisCode(obis, obis_nm) {	
	Scope().$apply(function () {
        Scope().settingObisCode(obis, obis_nm);
    });
}

function settingDynamicObisCode(obis, obis_cnt, resource_nm) {	
	Scope().$apply(function () {
        Scope().settingDynamicObisCode(obis, obis_cnt, resource_nm);
    });
}

function viewInfo() {
	$('#infoModal').modal('show');
}

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
<div id="loading">
	<div id="loading-image" class="spinner-border" role="status">
	<img id="loading-image" src="<%=COMMON_PATH_IMG%>/loading.gif" alt="Loading..." /></div>
	</div>
</div>
</body>
</html>
<script>
	$("#loading").hide();
</script>
