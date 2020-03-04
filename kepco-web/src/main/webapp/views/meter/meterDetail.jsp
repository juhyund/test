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
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>
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
	<h3 style="margin-top:6px">계기 상세 정보</h3>
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
<div >

	<div class="col-lg-12">	
		<div class="ibox">
			<div class="ibox-content">
					<!-- start :summary_area -->
					
				<div class="row m-b-md ">
					<div class="col-lg-6">
                    <div class="tabs-container" style=width:200%;>
                        <ul class="nav nav-tabs" role="tablist">
                            <li><a class="nav-link active" data-toggle="tab" href="#tab-1">기본정보</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-2" ng-click="meterResourceList(2);">동적 미터 설정</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-3" ng-click="meterResourceList(3);">동적 스케줄 설정</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-4">OBIS 제어</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-5">TOU설정 조회</a></li>
                            <li><a class="nav-link" data-toggle="tab" href="#tab-6">제어이력</a></li>
                        </ul>
                        <div class="tab-content">
                            <div role="tabpanel" id="tab-1" class="tab-pane active">
                                <div class="panel-body">
                                	<div class="ibox">
	                                	<div class="ibox-title">
	                                		<h5>모뎀 정보</h5>
	                                	</div>
		                                	<table class="table text-center">
		                                		<colgroup>
										            <col width="10%" />
										            <col width="14%" />
										            <col width="12%" />
										            <col width="14%" />
										            <col width="12%" />
										            <col width="14%" />
										            <col width="12%" />
										            <col width="12%" />
												</colgroup>
												<tbody>
													<tr>
														<th class="text-navy" scope="row">모뎀 번호:</th>
														<td id = "device_serial"></td>
														<th class="text-navy" scope="row">운전 상태:</th>
														<td id = "device_status"></td>
														<th class="text-navy" scope="row">최종 통신 일시:</th>
														<td id = "last_comm_dt"></td>
														<th class="text-navy" scope="row">통신 방식:</th>
														<td id = "comm_type"></td>
													</tr>
													<tr>
														<th class="text-navy" scope="row">통신사:</th>
														<td id = ""></td>
														<th class="text-navy" scope="row">모뎀 아이피:</th>
														<td id = "ip"></td>
														<th class="text-navy" scope="row">수신감도 레벨:</th>
														<td id = ""></td>
														<th class="text-navy" scope="row"></th>
														<td id = ""></td>
													</tr>
												</tbody>
											</table>
									</div>
									<div class="ibox">
										<div class="ibox-title">
	                                		<h5>계기 정보</h5>
	                                	</div>
										<table class="table text-center">
											 <colgroup>
									            <col width="7%" />
									            <col width="10%" />
									            <col width="12%" />
									            <col width="10%" />
									            <col width="12%" />
									            <col width="8%" />
									            <col width="13%" />
									            <col width="10%" />
									            <col width="10%" />
									            <col width="8%" />
											</colgroup>
											<tbody>
												<tr>
													<th class="text-navy" scope="row">계기번호:</th>
													<td id = "meter_serial"></td>
													<th class="text-navy" scope="row"> COSEM 계기 식별자:</th>
													<td id = "cosem_device_name"></td>
													<th class="text-navy" scope="row">마지막 검침 일시:</th>
													<td id = "last_comm_dt"></td>
													<th class="text-navy" scope="row">검침 주기:</th>
													<td id = "lp_period"></td>
													<th class="text-navy" scope="row">계기 시간:</th>
													<td id = "mtime"></td>
												</tr>
												<tr>
													<th class="text-navy" scope="row">계기 타입:</th>
													<td id = "meter_type"></td>
													<th class="text-navy" scope="row">유효전력량 계기정수:</th>
													<td id = "acon"></td>
													<th class="text-navy" scope="row">무효전력량 계기정수:</th>
													<td id = "rcon"></td>
													<th class="text-navy" scope="row">피상전력량 계기정수:</th>
													<td id = "pcon"></td>
													<th class="text-navy" scope="row">정기검침일자:</th>
													<td id = "billing_dt"></td>
												</tr>
												<tr>
													<th class="text-navy" scope="row">제조사:</th>
													<td id = "vendor_nm"></td>
													<th class="text-navy" scope="row">양방향계량수행:</th>
													<td id = "net_metering"></td>
													<th class="text-navy" scope="row">평균전압전류주기:</th>
													<td id = "avg_power_period"></td>
													<th class="text-navy" scope="row">선식구분:</th>
													<td id = "meter_phase"></td>
													<th class="text-navy" scope="row">계기프로그램버전:</th>
													<td id = "prog_version"></td>
												</tr>
											</tbody>
										</table>
									</div>
                                </div>
                            </div>
                            <div role="tabpanel" id="tab-2" class="tab-pane">
                               <div class="col-lg-10">
										<h4 style="margin-top: 6px"></h4>
									</div>
									<div>
										<div class="row" style="margin-top: 10px">
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
																		<th>단말 번호</th>
																		<th>미터 타입</th>
																		<th>계기 번호</th>
																		<th>검침 주기</th>
																	</tr>
																</thead>
																<tbody>
																	<tr>
																		<td><h3 id = "device_serial_tab2"></h3></td>
																		<td><h3 id = "meter_type_tab2"></h3></td>
																		<td><h3 id = "meter_serial_tab2"></h3></td>
																		<td><h3 id = "lp_period_tab2"></h3></td>
																	</tr>
																</tbody>
															</table>
														</div>
													</div>
													
													<div class="ibox-content">
														<div> 
															<input type="hidden" id=device_id name="device_id" value=""> </input>
															<input type="text" id=obis_code2 name="obis_code" value=""> 오 비 스 </input>
														</div>
														<div class="table-responsive"  id="resource">
															<table class="table">
																<thead class ="gray-bg">
																	<tr align="center" >
																		<th>리소스 ID</th>
																		<th style="text-align: left">리소스명</th>
																		<th>리소스값</th>
																		<th>단위</th>
																		<th>값 변경</th>
																	</tr>
																</thead>
																<tbody>
																	<tr align="center"  ng-repeat="resource in resources">
																		<td>{{resource.resource_id}}</td>
																		<td align="left">{{resource.resource_nm}}</td>
																		<td>{{resource.resource_val}}</td>
																		<td style="max-width: 200px;">{{resource.unit}}
																			<button  ng-show="resource.operation.indexOf('W') != -1 && resource.resource_id == '105'" ng-model="newValue" name="newValue"
																					class="btn btn-primary btn-outline" style="margin-right:10px; max-width: 200px;"  type="button" onclick="popupObisCode2();">
																					<i class="fa fa-search"> OBIS 코드 찾기</i>
																			</button>
																		</td>
																		<td>
																			<select ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id == '104'"
																				ng-model="newValue" name="newValue" 
																				style="min-width: 200px; " id="command-select" >
																				<option value="192" selected>GET </option>
																				<option value="193">SET</option>
																				<option value="5">READ </option>
																				<option value="6">WRITE </option>
																			</select>
																			<input ng-show="resource.operation.indexOf('W') != -1 && resource.resource_id != '104' && resource.resource_nm.indexOf('OBIS') == -1" type="text" ng-model="newValue" name="newValue"
																				style="min-width: 200px; ">
																			
																			<div ng-show="resource.operation.indexOf('W') != -1 && resource.resource_nm.indexOf('OBIS') != -1">
																				<input type="text" ng-model="obis_code" name="obis_code" id="obis_code" style="min-width: 200px;" readonly>
																			</div>
																			
																		</td>
																	</tr>
																</tbody>
															</table>
															<div name="schedule-buttons" class="row" style="margin:0; height:35px">
																
																<button class="btn btn-primary" style="margin-right:10px; width: 140px" type="button" onclick="settingBillingDt();">
																	<i class="fa"> 정기검침일 설정 </i>
																</button>
																<button class="btn btn-primary" style="margin-right:10px; width: 140px" type="button" onclick="settingLpPeriod();">
																	<i class="fa" > LP 주기 설정 </i>
																</button>
																<button class="btn btn-danger" style="margin-right:10px; width: 140px" type="button" ng-click="">
																	<i class="fa fa-play"> 동적 스케줄 실행</i>
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
									<div class="col-lg-10">
										<h4 style="margin-top: 6px"></h4>
									</div>
									<div>
										<div class="row" style="margin-top: 10px">
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
																		<th>단말 번호</th>
																		<th>미터 타입</th>
																		<th>계기 번호</th>
																		<th>검침 주기</th>
																	</tr>
																</thead>
																<tbody>
																	<tr>
																		<td><h3 id = "device_serial_tab3"></h3></td>
																		<td><h3 id = "meter_type_tab3"></h3></td>
																		<td><h3 id = "meter_serial_tab3"></h3></td>
																		<td><h3 id = "lp_period_tab3"></h3></td>
																	</tr>
																</tbody>
															</table>
														</div>
													</div>
													
													<div class="ibox-content">
														<div> 
															<input type="hidden" id=device_id name="device_id" value=""> </input>
														</div>
														<div class="table-responsive"  id="resource">
															<table class="table">
																<thead class ="gray-bg">
																	<tr align="center" >
																		<th>리소스 ID</th>
																		<th style="text-align: left">리소스명</th>
																		<th>리소스값</th>
																		<th>단위</th>
																		<th>값 변경</th>
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
																					<i class="fa fa-search"> OBIS 코드 찾기</i>
																			</button>
																		</td>
																		<td>
																			<select ng-if="resource.operation.indexOf('W') != -1 && resource.resource_id == '104'"
																				ng-model="newValue" name="newValue" id="target_meter_select"
																				style="min-width: 200px; ">
																				<option id="selected_meter_id">해당 미터 </option>
																				<option value="00000000000">같은 타입 모든 미터</option>
																			</select>
																			<input
																				ng-show="resource.operation.indexOf('W') != -1 && resource.resource_id != '104' && resource.resource_nm.indexOf('OBIS') == -1"
																				type="text" ng-model="newValue" name="newValue"
																				style="min-width: 200px; ">
																			<input
																				ng-show="resource.operation.indexOf('W') != -1 && resource.resource_nm.indexOf('OBIS') != -1"
																				type="text" ng-model="newValue" name="newValue" 
																				style="min-width: 200px;" readonly>
																		</td>
																	</tr>
																</tbody>
															</table>
															<div name="schedule-buttons" class="row" style="margin:0; height:35px">
																<button class="btn btn-primary" style="margin-right:10px; width: 140px" type="button" ng-click="">
																	<i class="fa fa-play"> 동적 스케줄 실행</i>
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
                            
                            
                            
                            
                            
                            
                            
                            <div role="tabpanel" id="tab-4" class="tab-pane">
                                <div class="panel-body">
									<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
                                </div>
                            </div>
                            <div role="tabpanel" id="tab-5" class="tab-pane">
                                <div class="panel-body">
									<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
                                </div>
                            </div>
                            <div role="tabpanel" id="tab-6" class="tab-pane">
                                <div class="panel-body">
									<!-- grid -->
									<div id="grid" style="height:400px;" class="ag-theme-balham"></div>
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
				
												

			   <button class="btn btn-outline btn-primary m-t-sm" style="height: 100%" type="button" onclick="javascript:history.back(-1)">
					<i class="fa fa-undo"> 목록으로 돌아가기</i>
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
	
	/* var device_serial = data.result.device_serial;
	var meter_serial = data.result.meter_serial;
	var reg_dt = data.result.reg_dt;
 	var last_comm_dt = data.result.last_comm_dt;
	var lp_period = data.result.lp_period;	
	var meter_type = data.result.meter_type;	
	var prog_id = data.result.prog_id;
	var prog_version = data.result.prog_version;	
	var meter_phase = data.result.meter_phase;
	var ip = data.result.ip;
	var vendor_nm = data.result.vendor_nm;
	var comm_type = data.result.comm_type; */
	
	$('#device_serial').text(data.result.device_serial);
	$('#device_serial_tab2').text(data.result.device_serial);
	$('#device_serial_tab3').text(data.result.device_serial);
	$('#meter_serial').text(data.result.meter_serial);
	$('#meter_serial_tab2').text(data.result.meter_serial);
	$('#meter_serial_tab3').text(data.result.meter_serial);
	$('#reg_dt').text(data.result.reg_dt);
 	$('#last_comm_dt').text(data.result.last_comm_dt);
	$('#lp_period').text(data.result.lp_period);
	$('#lp_period_tab2').text(data.result.lp_period);
	$('#lp_period_tab3').text(data.result.lp_period);
	$('#meter_type').text(data.result.meter_type);	
	$('#meter_type_tab2').text(data.result.meter_type);	
	$('#meter_type_tab3').text(data.result.meter_type);	
	meterTypeCode = data.result.meter_type_code;	
	$('#device_id').val(data.result.device_id);	
	$('#selected_meter_id').val(data.result.device_id);	
	
	$('#prog_id').text(data.result.prog_id);	
	$('#prog_version').text(data.result.prog_version);	
	$('#meter_phase').text(data.result.meter_phase);
	$('#ip').text(data.result.ip);
	$('#vendor_nm').text(data.result.vendor_nm);
	$('#comm_type').text(data.result.comm_type);
	
	$('#cosem_device_name').text(data.result.cosem_device_name);
	$('#acon').text(data.result.acon);
	$('#rcon').text(data.result.rcon);
	$('#pcon').text(data.result.pcon);
	$('#billing_dt').text(data.result.billing_dt);
	$('#itime').text(data.result.itime);
	$('#mtime').text(data.result.mtime);
	$('#net_metering').text(data.result.net_metering);
	$('#avg_power_period').text(data.result.avg_power_period);
	
}

function settingBillingDt(){
	//정기검침일 설정. 
	//DlmsMethod – Set / OBIS - 001600000F0000FF04 세팅

	 $("#command-select").val("193").attr("selected", "true");
	 obis_code = '001600000F0000FF04';
	 
	 alert( " DlmsMethod="+$("#command-select option:selected").text()+"\nobis_code="+ obis_code);
};

function settingLpPeriod(){
	//LP 주기 설정
	//DlmsMethod – Set / OBIS - 00030101000804FF02 세팅
	
	$("#command-select").val("193").attr("selected", "true");
	 obis_code = '00030101000804FF02';
	 
	 alert( " DlmsMethod="+$("#command-select option:selected").text()+"\nobis_code="+ obis_code);
};



var winObj;
function popupObisCode(){ //검침스케줄

	var opts="width=1000, height=550,left=200, top=200, resizable=no, toolbar=yes";
	if(winObj)
        winObj.close();
	var param = "?meter_type="+meterTypeCode;
    winObj = window.open(COMMON_URL+"/obisCodePopup"+param, "", opts);
}


function popupObisCode2(){ //미터설정
	
	var opts="width=1000, height=550,left=200, top=200, resizable=no, toolbar=yes";
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