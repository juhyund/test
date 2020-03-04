var deviceApp = angular.module('deviceApp', []);

deviceApp.controller('deviceCtrl', function DeviceController($scope, $http) {
	
	$scope.deviceInfo = function () {
		$http({
	        method: 'POST',

	        url: COMMON_URL + "/ajaxDeviceInfo",
	        params : {"device_id" : $("#device_id").val()}
	    }).then(function getInfo(data, status, headers, config) {
	    	$scope.device_info = data.data.result;
		}, function errorCallback(response) {
	        alert("error");
	    });
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
		resource.operation_method = "Read";
		var path = "/" + resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/ajaxExecResource",
	        params : {
	        	"url" : "clients/",
	        	"method" : resource.operation_method,
	        	"device_serial" : $("#device_serial").val(), 
	        	"resource" : path
	        }
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	resource.statusCode = data.data.statusCode
    		resource.statusMsg = data.data.statusMsg;
	    	resource.tid = data.data.tid;
	    	
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + resource.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	        resource.statusMsg = "제어실패";	    	
	    });
		
    };
    
    $scope.write = function (resource, newValue) {
    	
    	resource.operation_method = "Write";    	
		var path = "/" + resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;	
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/ajaxExecResource",
	        params : {
	        	"url" : "clients/",
	        	"method" : resource.operation_method,
	        	"device_serial" : $("#device_serial").val(), 
	        	"resource" : path, 
	        	"newValue" : newValue
	        }
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	resource.statusCode = data.data.statusCode
    		resource.statusMsg = data.data.statusMsg;
	    	resource.tid = data.data.tid;
	    	
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + resource.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	        resource.statusMsg = "제어실패";	    	
	    });
    };
    
    $scope.execute = function (resource) {
    	
    	resource.operation_method = "Execute";
    
    	var path = "/" + resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/ajaxExecResource",
	        params : {
	        	"url" : "clients/execute/",
	        	"method" : resource.operation_method,
	        	"device_serial" : $("#device_serial").val(), 
	        	"resource" : path
	        }
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	    		
	    	resource.statusCode = data.data.statusCode
    		resource.statusMsg = data.data.statusMsg;
	    	resource.tid = data.data.tid;
	    	
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + data.data.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	        resource.statusMsg = "전송실패";	    	
	    });
		
    };
    

    $scope.attribute = function (resource) {
    	
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
    	        	"url" : "clients/"
    	        	, "method" : "WriteAttribute" 
    	        	, "device_serial" : $("#device_serial").val()
    	        	, "resource" : path
    	        	, "attributes" : attributes
	        	}
    		
    	    }).then(function SuccessCallback(data, status, headers, config) {
    	    
    	    	resource.statusCode = data.data.statusCode
        		resource.statusMsg = data.data.statusMsg;
    	    	resource.tid = data.data.tid;
    	    	
    	    	if(data.data.statusCode == "200") {
    	    		alert("전송성공 [" + data.data.tid + "]");
    	    	} else {
    	    		alert("제어실패 [" + resource.statusMsg + "]");
    	    	}
    	    	
        	}, function errorCallback(response) {
    	        alert("전송실패");
    	        resource.statusMsg = "전송실패";	    	
    	    });
            
        });
    	
        $('#writeModal').modal('show');
    	
    };
    
    $scope.coapping = function () {
		
		$http({
			method: 'POST',
	        url: COMMON_URL + "/ajaxExecResource",
	        params : {
	        	"url" : "coapping/clients/",
	        	"method" : "coapping",
	        	"device_serial" : $("#device_serial").val(), 
	        	"resource" : ""
	        }
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    
	    	console.log(data);
	    	/*
	    	resource.statusCode = data.data.statusCode
    		resource.statusMsg = data.data.statusMsg;
	    	resource.tid = data.data.tid;
	    	*/
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + resource.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	        resource.statusMsg = "제어실패";	    	
	    });
    };
    
});