var deviceApp = angular.module('deviceApp', []);

deviceApp.controller('deviceCtrl', function DeviceController($scope, $http) {
	
	$scope.deviceInfo = function () {
		showLoading();
		$http({
	        method: 'POST',

	        url: COMMON_URL + "/ajaxDeviceInfo",
	        params : {"device_id" : $("#device_id").val()}
	    }).then(function getInfo(data, status, headers, config) {
	    	$scope.device_info = data.data.result;
	    	$("#device_id_span").show();
	    	$("#branch_span").show();
	    	$("#device_serial_span").show();
	    	$("#vendor_nm_span").show();
	    	$("#di_mobile_no").show();
	    	$("#di_ip").show();
	    	$("#di_port").show();
	    	$("#model_nm_span").show();
	    	$("#di_fw_version").show();
	    	$("#di_hw_version").show();
	    	$("#di_sw_version1").show();
	    	$("#di_sw_version2").show();
	    	$("#security_mode_span").show();
	    	$("#code_local_nm_span").show();
	    	$("#last_comm_dt_span").show();
	    	$("#reg_dt_span").show();
	    	$("#di_remark").show();
		}, function errorCallback(response) {
	        alert("error");
	    });
		hideLoading();
	};
	
	$scope.objectModel = function () {
		$scope.objects = {};
		$http({
	        method: 'POST',
	        url: COMMON_URL + "/ajaxObjectModelList",
	        params : { 
	        	"searchfield" : $("#searchfield").val(),
            	"searchquery" : $("#searchquery").val(),
            	"instances" : $("#instances").val()	
	        }
	    }).then(successCallback, function errorCallback(response) {
	        alert("error");
	    });
	};
	
	$scope.firmware = function () {
		var columnDefs = [
			{headerName: "번호", field: "no", width:80},
			{headerName: "생성일자", field: "reg_dt"},
			{headerName: "파일명", field: "fw_nm"},
			{headerName: "패키지 명", field: "fw_file_nm"},
			{headerName: "패키지 버전", field: "fw_version"}
		];
		
		var initGrid = function() {
		  dataGrid = new DataGrid('grid_b', columnDefs, true, 500);    
		  dataGrid.makeGrid();
		  dataGrid.showNoRows();
		};
		
		onRowClicked = function(event){
			$("#deviceserial").val($("#device_serial").val());
			$("#package_uri").val(event.data.fw_pkg_uri);
			
			if(target == "#firmware"){
				fwUpgradeModal();	
			}
		}
		
		initGrid();
		
		$http({
	        method: 'POST',
	        url: COMMON_URL + "/ajaxDeviceFWList",
	        params : { 
	        	"fw_file_nm" : $("#fw_file_nm_b").val(),
            	"fw_version" : $("#fw_version_b").val(),
	        }
	    }).then(function result(data, status, headers, config) {
	    	
	    	var dataPerPage = $("#limit").val();
	    	var currentPage = $("#page").val();
	    	
	    	dataGrid.setData(data.data.resultGrid);
	    	gridPage(data.data.totalCount, dataPerPage, 10, currentPage);
	    	
		}, function errorCallback(response) {
	        alert("error");
	    });
	};
	
	
	function successCallback(data, status, headers, config) {
        $.each(data.data.result, function (index, item) {
	    	$http({
	            method: 'POST',
	            url: COMMON_URL + "/ajaxDeviceResourceModelList",
	            params : { "device_id" : $("#device_id").val(), "object_id" : item.object_id }
	    	
	        }).then(function resourceSuccessCallback(data, status, headers, config) {
	        	// instance
	        	item.instance = data.data.result;
	        	$scope.objects[index] = item;
	    	}, function errorCallback(response) {
	        	console.log("error");
	        });      	
        });     
	}
	$scope.read = function (resource) {
		showLoading();
		resource.operation_method = "Read";
		var path = "/" + resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/ajaxExecResource",
	        params : {
	        	"url" : "clients/",
	        	"method" : resource.operation_method,
	        	"device_id" : $("#device_id").val(),
	        	"service_id" : $("#service_id").val(),
	        	"device_serial" : $("#device_serial").val(), 
	        	"resource_instance_id" : resource.resource_instance_id, 
	        	"resource" : path
	        }
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	resource.statusCode = data.data.statusCode
    		resource.statusMsg = data.data.statusMsg;
	    	resource.tid = data.data.tid;
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공\nTID:  [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + resource.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	        resource.statusMsg = "제어실패";	    	
	    });
		hideLoading();
    };
    
    $scope.write = function (resource, newValue) {
    	showLoading();
    	resource.operation_method = "Write";    	
		var path = "/" + resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;	
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/ajaxExecResource",
	        params : {
	        	"url" : "clients/",
	        	"method" : resource.operation_method,
	        	"device_id" : $("#device_id").val(),
	        	"service_id" : $("#service_id").val(),
	        	"device_serial" : $("#device_serial").val(), 
	        	"resource_instance_id" : resource.resource_instance_id,
	        	"resource" : path, 
	        	"newValue" : newValue
	        }
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	resource.statusCode = data.data.statusCode
    		resource.statusMsg = data.data.statusMsg;
	    	resource.tid = data.data.tid;
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공\nTID:  [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + resource.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	        resource.statusMsg = "제어실패";	    	
	    });
		hideLoading();
    };
    
    $scope.execute = function (resource) {
    	showLoading();
    	resource.operation_method = "Execute";
    
    	var path = "/" + resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/ajaxExecResource",
	        params : {
	        	"url" : "clients/execute/",
	        	"method" : resource.operation_method,
	        	"device_id" : $("#device_id").val(),
	        	"service_id" : $("#service_id").val(),
	        	"device_serial" : $("#device_serial").val(), 
	        	"resource_instance_id" : resource.resource_instance_id,
	        	"resource" : path
	        }
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	    		
	    	resource.statusCode = data.data.statusCode
    		resource.statusMsg = data.data.statusMsg;
	    	resource.tid = data.data.tid;
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공\nTID:  [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + data.data.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	        resource.statusMsg = "전송실패";	    	
	    });
		hideLoading();
    };
    

    $scope.attribute = function (resource) {
    	showLoading();
    	resource.operation_method = "속성설정";
    	
    	var path = "/" + resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;	
    	
    	$('#writeModalLabel').text(resource.resource_name + " (" + path + ") 속성 설정");
    	$('#writeSubmit').unbind();
    	
    	$('#form').each(function() {
    		this.reset();
    	});
    	
    	$('#writeSubmit').click(function(e) {
            e.preventDefault();            
            var attributes = $('#form').serialize();
            
            $('#writeModal').modal('hide');
            
            $http({
    			
    			method: 'POST',
    	        url: COMMON_URL + "/ajaxExecResource",
    	        params : {
    	        	"url" : "clients/",
    	        	"method" : "WriteAttribute", 
	        		"device_id" : $("#device_id").val(),
	        		"service_id" : $("#service_id").val(),
    	        	"device_serial" : $("#device_serial").val(),
    	        	"resource_instance_id" : resource.resource_instance_id,
    	        	"resource" : path, 
    	        	"attributes" : attributes
	        	}
    		
    	    }).then(function SuccessCallback(data, status, headers, config) {
    	    
    	    	resource.statusCode = data.data.statusCode
        		resource.statusMsg = data.data.statusMsg;
    	    	resource.tid = data.data.tid;
    	    	if(data.data.statusCode == "200") {
    	    		alert("전송성공\nTID:  [" + data.data.tid + "]");
    	    	} else {
    	    		alert("제어실패 [" + resource.statusMsg + "]");
    	    	}
    	    	
        	}, function errorCallback(response) {
    	        alert("전송실패");
    	        resource.statusMsg = "전송실패";	    	
    	    });
            
        });
    	hideLoading();
        $('#writeModal').modal('show');
    	
    };
    
    $scope.coapping = function () {
    	showLoading();
    	$scope.coapping = {};
		$http({
			method: 'POST',
	        url: COMMON_URL + "/ajaxCoAPpIng",
	        params : {
	        	"url" : "coapping/clients/",
	        	"method" : "coapping",
	        	"device_id" : $("#device_id").val(),
	        	"service_id" : $("#service_id").val(),
	        	"device_serial" : $("#device_serial").val(), 
	        	"sec" : $("#sec").val() 
	        }
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	    	$scope.coapping.statusMsg = data.data.statusMsg;
	    	if(data.data.statusCode == "200") {
	    		//alert("전송성공\nTID:  [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + coapping.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	        coapping.statusMsg = "제어실패";	    	
	    });
		hideLoading();
    };
    
    $scope.reset = function () {
    	showLoading();
		$http({
			method: 'POST',
	        url: COMMON_URL + "/ajaxExecResource",
	        params : {
	        	"url" : "clients/execute/",
	        	"method" : "Execute", 
        		"device_id" : $("#device_id").val(),
        		"service_id" : $("#service_id").val(),
	        	"device_serial" : $("#device_serial").val(),
	        	"resource" : "/3/0/4" 
        	}
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공 \nTID: [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + data.data.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	    });
		hideLoading();
    };
});