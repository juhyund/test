var deviceApp = angular.module('deviceApp', []);

deviceApp.controller('deviceCtrl', function DeviceController($scope, $http) {
	
	$scope.objects = {};
	
	$http({
        method: 'POST',
        url: COMMON_URL + "/ajaxDeviceObjectModelList",
        params : {"device_id" : $("#device_id").val()}
    }).then(successCallback, function errorCallback(response) {
        alert("error");
    });
	
	function successCallback(data, status, headers, config) {
        $.each(data.data.result, function (index, item) {
        	
	    	$http({
	            method: 'POST',
	            url: COMMON_URL + "/ajaxDeviceResourceModelList",
	            params : {"device_id" : $("#device_id").val(), "object_id" : item.object_id}
	    	
	        }).then(function resourceSuccessCallback(data, status, headers, config) {
	        	console.log(data);
	        	// resources
	        	item.resources = data.data.result;	        	
	        	$scope.objects[index] = item;
	    	}, function errorCallback(response) {
	        	console.log("error");
	        });        	
        });     
        
	}
	$scope.read = function (resource) {
		
		var path = resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execReadResource",
	        params : {"device_id" : $("#device_id").val(), "resource" : path}
		
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
		resource.operation_method = "Read";
    };
    
    $scope.write = function (resource, newValue) {
    	
    	resource.operation_method = "Write";    	
		var path = resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;	
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execControlValue",
	        params : {"device_id" : $("#device_id").val(), "resource" : path, "newValue" : newValue}
		
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
    
    	var path = resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;	
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execControlExecute",
	        params : {"device_id" : $("#device_id").val(), "resource" : path}
		
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
    	
    	var path = resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;	
    	
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
    	        url: COMMON_URL + "/nuri/kicpcall/execControlAttribute",
    	        params : {
    	        	"device_id" : $("#device_id").val()
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
    
    $scope.observe = function (resource, observeType) {
    	
    	if(observeType == "Y") {
    		resource.operation_method = "Observe";
    	} else {
    		resource.operation_method = "Observe-Cancel";
    	}
    	
		var path = resource.object_id + "/" + resource.object_instance_id + "/" + resource.resource_id;		
				
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execControlObserve",
	        params : {"device_id" : $("#device_id").val(), "resource" : path, "observeType" : observeType}
		
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
    };
});