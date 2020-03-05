var meterApp = angular.module('meterApp', []);

meterApp.controller('meterCtrl', function MeterController($scope, $http) {
	
/*	$scope.objectInfo = function () {
		
		var object_id = $("#object_id").val();
		
		$http({
	        method: 'POST',
	        url: COMMON_URL + "/ajaxMeterObjectModel",
	        params : {"object_id" : object_id}
	    }).then(function getInfo(data, status, headers, config) {
	    	$scope.object = data.data.result;
	    	$("#object_id").val(data.data.result.object_id);
		}, function errorCallback(response) {
	        alert("error");
	    });
	};*/
	
	$scope.meterResourceList = function (selectedTab) {
		
		var device_id = $("#device_id").val();
		var object_id;
		var object_instance_id;
		var meter_type = $('#meter_type').text()
		
		if(selectedTab == 2){//미터 설정
    		object_id = 31012;
    		object_instance_id = 0;
	   	}
		else if(selectedTab == 3){//검침스케줄 읽기
			
			object_id = 31011;
			switch(meter_type){	
				case "S-TYPE":  {
					object_instance_id = 10;
		   	   		break;
		   		}
				case "E-TYPE":  {
					object_instance_id = 30;
		   	   		break;
		   		}
				case "G-TYPE":  {
					object_instance_id = 52;
		   	   		break;
		   		}
				case "AE-TYPE":  {
					object_instance_id = 82;
		   	   		break;
		   		}
			}
		}
		
			
			$http({
		        method: 'POST',
	
		        url: COMMON_URL + "/ajaxMeterResourceList",
		        params : {"device_id" : device_id,
			        	  "object_id" : object_id,
			        	  "object_instance_id" : object_instance_id}
		    }).then(function getInfo(data, status, headers, config) {
		    	
		    	$scope.resources = data.data.result;
			}, function errorCallback(response) {
		        alert("error");
		    });
	};
	
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