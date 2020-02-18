<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<%
	String device_id = request.getParameter("device_id");
%>
<!DOCTYPE html>
<html >
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
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>

<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
</head>
<body ng-app="deviceApp">
	<!--  wrapper -->
	<div id="content" ng-controller="deviceCtrl" >
		<div id="wrapper">
			<div id="page-wrapper" style="width: 100%" class="gray-bg">
				<!-- navigator -->
				<div class="row wrapper page-heading" style="padding: 5px">
					<div class="col-lg-10">
						<h3 style="margin-top: 6px">단말 관리</h3>
					</div>
					<div class="col-lg-2">
						<ol class="breadcrumb" style="float: right; margin-top: 10px;">
							<li class="breadcrumb-item"><a
								href="#">Home</a>
							</li>
							<li class="breadcrumb-item active"><strong>Layouts</strong>
							</li>
						</ol>
					</div>
				</div>
				<!-- navigator -->
				<!-- body -->
				<form name="search_form" id="search_form" method="post">
				<input type=hidden name="device_id" id="device_id" value="<%=device_id%>">
				</form>
							
				<div ng-repeat="object in objects" > 								
				<div class="row" >
					<div class="col-lg-12">
						<div class="ibox">
                        <div class="ibox-title">
                            <h5>{{object.object_name}} - {{object.object_id}} / {{object.object_instance_id}}</h5>
                            <div class="ibox-tools">
                                <a class="collapse-link">
                                    <i class="fa fa-chevron-up"></i>
                                </a>
                            </div>
                        </div>
                        <!-- ibox-content -->
                        <div class="ibox-content">                            
                            <div class="table-responsive">
                                <table class="table table-striped">
                                    <thead>
                                    <tr align="center">
                                        <th width="100">리소스아이디</th>
                                        <th style="text-align:left">리소스명</th>
                                        <th width="150">리소스값</th>
                                        <th width="150">단위</th>
                                        <th width="150">Operation</th>
                                        <th width="250">Observe 설정/해제</th>
                                        <th width="250">값 변경</th>
                                        <th width="80">속성설정</th>
                                        <th width="80">실행</th>
                                        <th width="250">제어상태</th>
                                    </tr>
                                    </thead>
                                    <tbody>
                                    <tr align="center" ng-repeat="resource in object.resources">
                                    	<td>{{resource.resource_id}}</td>
                                    	<td align="left">{{resource.resource_name}} {{resource.temp}}</td>
                                    	<td></td>
                                    	<td>{{resource.unit}}</td>
                                    	<td>                                    	
                                    	<button ng-show="resource.operation.indexOf('R') != -1" class="btn btn-primary btn-xs" type="button"
											ng-click="read(resource);">
											Read
										</button>                                    									
                                    	<button ng-show="resource.operation.indexOf('E') != -1" class="btn btn-primary btn-xs" type="button"
											ng-click="execute(resource);">
											Execute
										</button>										
										</td>
                                    	<td>
                                    	<button ng-show="resource.operation.indexOf('R') != -1" class="btn btn-primary btn-xs" type="button"
											ng-click="observe(resource, 'Y');">
											Observe
										</button>
										<button ng-show="resource.operation.indexOf('R') != -1" class="btn btn-primary btn-xs" type="button"
											ng-click="observe(resource, 'N');">
											Cancel
										</button>
                                    	</td>
                                    	<td>
                                    		<input ng-show="resource.operation.indexOf('W') != -1" type="text" ng-model="newValue" name="newValue" style="width:100px;">
                                    		<button ng-show="resource.operation.indexOf('W') != -1" class="btn btn-primary btn-xs" type="button"
											ng-click="write(resource, newValue);">
											Write
											</button>		
                                    	</td>
                                    	<td><button ng-show="resource.operation.indexOf('R') != -1" class="btn btn-primary btn-xs" type="button"
											ng-click="attribute(resource);">
											속성
										</button></td>  
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
				
				<!-- body -->
			</div>
		</div>
	</div>
	
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

</body>
</html>

