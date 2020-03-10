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
		var meter_serial = $("#_meter_serial").val();
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
	    	
//	    	$scope.resources = data.data.result;
	    	
	    	var result = data.data.result;
	    	
	    	if(object_id == 31012) {
	    		for(i in result) {	    			
		    		if(result[i].resource_id == 101) { // targetMeter		    			
		    			result[i].newValue = meter_serial;
		    		} else if (result[i].resource_id == 102) { // MeterSchedule
		    			result[i].newValue = "* * * * *";
		    		} else if (result[i].resource_id == 103) { // UploadSchedule
		    			result[i].newValue = "* * * * *";
		    		} else if (result[i].resource_id == 104) { // DlmsMethod
		    			result[i].newValue = 192;
		    		}
		    	}
	    	} else if (object_id == 31011) {
	    		
	    		for(i in result) { 			
		    		if(result[i].resource_id == 104) { // targetMeter		    			
		    			result[i].newValue = meter_serial;
		    		} else if (result[i].resource_id == 105) { // MeterSchedule
		    			result[i].newValue = "* * * * *";
		    		} else if (result[i].resource_id == 106) { // UploadSchedule
		    			result[i].newValue = "* * * * *";
		    		} else if (result[i].resource_id == 107) { // StartTime
		    			result[i].newValue = "* * * * *";
		    		} else if (result[i].resource_id == 108) { // EndTime
		    			result[i].newValue = "* * * * *";
		    		} else if (result[i].resource_id == 109) { // PG_Offset
		    			result[i].newValue = -1;
		    		} else if (result[i].resource_id == 110) { // PG_Count
		    			result[i].newValue = -1;
		    		} else if (result[i].resource_id == 111) { // PG_Access Selector
		    			result[i].newValue = 1;
		    		}
		    	}
	    	}
	    	$scope.resources = result;
	    	
		}, function errorCallback(response) {
	        alert("error");
	    });
	};
	
	// meter serial for selectbox
	$scope.meterSerialList = [
		{id:$("#_meter_serial").val(), name:$("#_meter_serial").val()},
		{id:"00000000000", name:"00000000000"}
	];	
	
	$scope.write = function (resources) {
		
		var object_instance_id = 0;
		var object_id = resources[0].object_id;
		var targetMeter = "";
		
		if(object_id == 31011) {
			object_instance_id = $("#object_instance_id").val(); 
		}
		
		// 전송
		var path = "/" + object_id + "/" + object_instance_id;	
		
		if($scope.isValid(resources)) {
			
			var payload = {};
			
	        payload["id"] = object_instance_id;
	        payload["resources"] = [];
	           
			for(i in resources) {
				
				var resource = resources[i];
				
				// targetMeter for meterAccess
				if(object_id == 31012 && resource.resource_id == 101) {
					targetMeter = resource.newValue;
				}
				
				// targetMeter for meteringSchedule
				if(object_id == 31011 && resource.resource_id == 104) {
					targetMeter = resource.newValue;
				}
				
				if(object_id == 31011 && resource.resource_id == 113) {// multiple				
					
					if(resource.newValue != undefined) {
						
						var resourceSplit = resource.newValue.split(',');
		        		var values = {};
		        		 
		        		for ( var i in resourceSplit ) {
		        			values[i] = resourceSplit[i];                        			                        			
		        		}
		        		
		        		// 113
		        		payload.resources.push({
		                    "id":resource.resource_id,
		                    "values":values
		                });
					}
					
				} else {
					
					
					if(object_id == 31012 && resource.resource_id == 106) {
						
						var obis = resources[4].newValue;
						var cmd = resources[3].newValue;						
						var apdu = $scope.makeAPDU(obis, resource.newValue, cmd);
						
						
						if(apdu != undefined) {
							payload.resources.push({
				                "id":resource.resource_id,
				                "value":apdu
				            });
						}
					} else {
						
						if(object_id == 31011 && (
								   resource.resource_id == 109 
								|| resource.resource_id == 110 
								|| resource.resource_id == 111
								|| resource.resource_id == 112
								|| resource.resource_id == 114)) {
							
							if(resource.newValue != undefined) { // int
								payload.resources.push({
					                "id":resource.resource_id,
					                "value":parseInt(resource.newValue)
					            });
							}
							
						} else if(resource.newValue != undefined) {
							payload.resources.push({
				                "id":resource.resource_id,
				                "value":resource.newValue
				            });
						}
					}
				}
			}
			
			$scope.executeWrite(path, payload, targetMeter);
		}
    };
    
    
    $scope.isValid = function (resources) {
    	
    	var object_id = resources[0].object_id;
    	
    	if(object_id == 31012) { // 동적미터 설정
    		
    		for(i in resources) {
    			
    			var resource = resources[i];    			
    			if(resource.newValue == undefined || resource.newValue == "") {
    				
    				if(resource.resource_id == 106) {
    					if(resources[3].newValue == 193 || resources[3].newValue == 6) {
    						resource.msg = "설정 값을 입력해 주세요!";
    						return false;
    					}    					
    				} else {
    					resource.msg = resource.resource_nm + "을(를) 입력해 주세요!!!!";
    					return false;
    				}
    					
    			} else {
    				resource.msg = "";
    			}
    			
    		} // end for
    		
    	} else if(object_id == 31011) { // 동적스케줄 설정
    		
    		for(i in resources) {
    			
    			var resource = resources[i];    			
    			if(resource.newValue == undefined || resource.newValue == "") {    				
    				if(resource.resource_id != 114) {
    					resource.msg = resource.resource_nm + "을(를) 입력해 주세요!!!!";
    					return false;
    				}    					
    			} else {
    				resource.msg = "";
    			}    			
    		} // end for
    	}
    	
    	return true;
    };
    
    
    $scope.executeWrite = function (path, payload, targetMeter) {
    	
    	var operation_method = "Write";
    	
		$http({
	    
			method: 'POST',
	        url: COMMON_URL + "/ajaxWriteMultiResource",
	        params : {
	        	"url" : "clients/",
	        	"method" : operation_method,
	        	"device_id" : $("#device_id").val(),
	        	"service_id" : $("#service_id").val(),
	        	"device_serial" : $("#device_serial").text(),
	        	"target_meter" : targetMeter,
	        	"resource" : path
	        },
	        data : payload		
	    }).then(function SuccessCallback(data, status, headers, config) {
	    	
	    	if(data.data.statusCode == "200") {
	    		alert("전송성공 [" + data.data.tid + "]");
	    	} else {
	    		alert("제어실패 [" + data.data.statusMsg + "]");
	    	}
	    	
    	}, function errorCallback(response) {
	        alert("제어실패");	    	
	    });
    };
    
    
    $scope.settingBillingDt = function (resources) {
    	//정기검침일 설정. 
    	resources[3].newValue = 193;
    	resources[4].newValue = "001600000F0000FF04";
    	resources[4].obis_nm = "정기검침일";
    	resources[5].strUnit = "일";
    };
    
    $scope.settingLpPeriod = function (resources) {
    	resources[3].newValue = 193;    	
   	 	resources[4].newValue = "00030101000804FF02";
   	 	resources[4].obis_nm = "LP 주기";
   	 	resources[4].msg = "";
   	 	resources[5].strUnit = "분";
   	 	
    };
    
    $scope.settingObisCode = function(obis, obis_nm) {    	
    	var resources = $scope.resources;    	
    	resources[4].newValue = obis;
    	resources[4].obis_nm = obis_nm;
    	resources[4].msg = "";
    };
    
    $scope.settingDynamicObisCode = function(obis, obis_cnt, resource_nm) {	
    	var resources = $scope.resources;    	
    	resources[8].newValue = obis_cnt;
    	resources[9].newValue = obis;
    	resources[9].obis_nm = resource_nm;
    	resources[8].msg = "";
    	resources[9].msg = "";
    };
    
    $scope.makeAPDU = function(obiscode, value, cmd) {
    	
    	var apdu = "00";
    	
    	if(cmd == 193) { // SET_REQUEST
    		if(obiscode == "00030101000804FF02") { // lp주기
    			var hex = $scope.makeHex(value);
    			apdu += "11" + hex; 
    		} else if(obiscode == "001600000F0000FF04") {
    			var hex = $scope.makeHex(value);
    			apdu += "010102020904000000000905FFFFFF" + hex + "FF"
    		} 
    	}
    	
    	return apdu;
    }
    
    $scope.makeHex = function(n) {
    	n = parseInt(n);
    	var h = (n).toString(16).toUpperCase();    	
    	return $scope.LPAD(h, '0', 2);
    } 

    $scope.LPAD = function(s, c, n) {   
        if (! s || ! c || s.length >= n) {
            return s;
        }
     
        var max = (n - s.length)/c.length;
        for (var i = 0; i < max; i++) {
            s = c + s;
        }
     
        return s;
    }
});

