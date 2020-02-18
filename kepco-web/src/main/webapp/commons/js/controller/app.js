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
	        	// resources
	        	item.resources = data.data.result;	        	
	        	$scope.objects[index] = item;
	    	}, function errorCallback(response) {
	        	console.log("error");
	        });        	
        });     
        
	}
	
	$scope.read = function (data) {
		
		console.log($scope.objects);
		
		var resource = "";		
		
		resource = data.object_id + "/" + data.object_instance_id + "/" + data.resource_id;		
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execReadResource",
	        params : {"device_id" : $("#device_id").val(), "resource" : resource}
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	if(data.data.statusCode != "200") {
	    		alert(data.data.statusMsg);
	    	} else {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	    });
		
    };
    
    $scope.write = function (data) {
    	
    	var resource = "";
    	var newValue = "";
		
		resource = data.object_id + "/" + data.object_instance_id + "/" + data.resource_id;		
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execControlValue",
	        params : {"device_id" : $("#device_id").val(), "resource" : resource, "newValue" : newValue}
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	if(data.data.statusCode != "200") {
	    		alert(data.data.statusMsg);
	    	} else {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	    });
    };
    
    $scope.execute = function (data) {
    	
    	var resource = "";
    	var newValue = "";
		
		resource = data.object_id + "/" + data.object_instance_id + "/" + data.resource_id;		
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execControlExecute",
	        params : {"device_id" : $("#device_id").val(), "resource" : resource}
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	if(data.data.statusCode != "200") {
	    		alert(data.data.statusMsg);
	    	} else {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	    });
    };
    

    $scope.attribute = function (data) {
    	
    	var resource = "";
    	var newValue = "";
		
		resource = data.object_id + "/" + data.object_instance_id + "/" + data.resource_id;		
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execControlExecute",
	        params : {"device_id" : $("#device_id").val(), "resource" : resource}
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	if(data.data.statusCode != "200") {
	    		alert(data.data.statusMsg);
	    	} else {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	    });
    };
    
    $scope.observe = function (data, observeType) {
    	
    	var resource = "";
    	var newValue = "";
		
		resource = data.object_id + "/" + data.object_instance_id + "/" + data.resource_id;		
		
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/nuri/kicpcall/execControlObserve",
	        params : {"device_id" : $("#device_id").val(), "resource" : resource, "observeType" : observeType}
		
	    }).then(function SuccessCallback(data, status, headers, config) {
	 	    	
	    	if(data.data.statusCode != "200") {
	    		alert(data.data.statusMsg);
	    	} else {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("전송실패");
	    });
    };
  
});