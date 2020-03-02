/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMCustBookingPop.js
* @Author : kyunghee.yoon
* @Date : 2015.12.12
**************************************/
Ext.onReady(function() {
	
	var currentTime = new Date();
	var hour = currentTime.getHours() + "";
	
	var min = lpad((Math.ceil(currentTime.getMinutes() / 5) * 5) + 10, 2, '0');
	
	var bookingTime1Store = new Ext.data.ArrayStore({        
	    fields : ['code','val']
	});
	
	var bookingTime2Store = new Ext.data.ArrayStore({        
	    fields : ['code','val']
	});
	
	for(i = 9; i < 19; i++) {			
		bookingTime1Store.add({'code' : lpad(i, 2, '0'), 'val' : lpad(i, 2, '0') + ' 시'});
	}
	
	for(i = 0; i < 12; i++) {	
		bookingTime2Store.add({'code' : lpad(i*5, 2, '0'), 'val' : lpad(i*5, 2, '0') + ' 분'});
	}
	
	// 시
	var comboBookingTime1 = Ext.create('Ext.form.ComboBox', {	
		store: bookingTime1Store,
	    width: 80,        
	    name: 'booking_time1',
	    queryMode: 'local',
	    displayField: 'val',
	    valueField: 'code',
	    editable: false,
	    padding: '0 0 0 0',
	    value: hour 
	});
	
	// 분
	var comboBookingTime2 = Ext.create('Ext.form.ComboBox', {
	    store: bookingTime2Store,
	    width: 80,        
	    name: 'booking_time2',
	    queryMode: 'local',
	    displayField: 'val',
	    valueField: 'code', 
	    editable: false,
	    padding: '0 0 0 5',
	    value: min
	});
		
	// 예약상태
	var bookingStatusStore = Ext.create('Ext.data.Store', {    	  
		proxy: {
	        type: 'ajax',
	        url: COMMON_URL + '/ajaxCodeCombo',
	        reader: {root: 'result'},
	        extraParams: {class_cd: 'BS', use_yn:'Y', display_yn:'Y'}
	    },
	    fields: [{ name: 'code' },{ name: 'code_nm' }],
	    autoLoad:true  
	});
	
	// 예약상태
	var comboBookingStatus = Ext.create('Ext.form.ComboBox', {
		fieldLabel: '예약상태',
		afterLabelTextTpl: [MARK_ASTERISK],
		store: bookingStatusStore,
	    width: 80,        
	    name: 'booking_status',
	    queryMode: 'local',
	    displayField: 'code_nm',
	    valueField: 'code', 
	    editable: false,
	    value: 'BS001'
	});
		
	// 예약정보
	var custBookingFormPanel = new Ext.form.Panel({
		id: 'custBookingForm',
		title: '예약고객저장',
		flex: 1,
		border: 1,  
		padding: '0 0 10 0',	
	    defaultType: 'textfield',
	    bodyPadding: 7,
	    fieldDefaults: {		            
	    	labelAlign: 'center',
	        labelWidth: 60,
	        labelSeparator: "",
	        enableKeyEvents: true
	    },
	    defaultType: 'textfield',
	    defaults: {anchor: '100%'},
	    items: [{
	    		xtype: 'hiddenfield',
		        name: 'booking_no'
	    	}, {
	    		xtype: 'hiddenfield',
		        name: 'cust_no',
		        value: cust_no
		    }, {    	
		        name: 'cust_nm',
		        fieldLabel: '고객명',
		        afterLabelTextTpl: [MARK_ASTERISK],
		        flex: 1,
		        value: cust_nm
		    }, {    	
		        name: 'tel_mobile',
		        fieldLabel: '휴대번호',
		        afterLabelTextTpl: [MARK_ASTERISK],
		        flex: 1,
		        value: tel_mobile
		    }, {    	
		        name: 'tel_home',
		        fieldLabel: '전화번호',
		        flex: 1,
		        value: tel_home
		    }, {    	
		    	xtype: 'datefield',
		        name: 'booking_date',
		        fieldLabel: '예약일자',
		        afterLabelTextTpl: [MARK_ASTERISK],
		        format: 'Ymd',
			    submitFormat: 'Ymd',
			    submitValue: true,
			    value: toDate,
			    width: 150
		    }, {
		        xtype: 'fieldcontainer',            
		        layout: 'hbox',         
		        fieldLabel: '예약시간',
		        afterLabelTextTpl: [MARK_ASTERISK],
		        items: [
		                comboBookingTime1,
		                comboBookingTime2
		        ]
		    },
		    	comboBookingStatus
		    , {  
		    	xtype: 'textarea',
		        name: 'remark',
		        fieldLabel: '비고',
		        flex: 1,
		        height: 80
		    }
	    ], 
	    buttons: [
	  	  	'<font color="red">*</font>  항목은 필수 항목입니다.',
	        '->',
	        {
	  	  		
	        text: '저장',
	        formBind: true, 
	        iconCls: 'icon-yes',
	        handler: function() {
	            
	        	saveForm();
	        }
	    },
	    {
	        text: '닫기',
	        iconCls: 'icon-cancel',
	        handler: function() {
	        	self.close();
	    	}
	    }]
	});
	
	function saveForm() {
		
		var url = "/ajaxCustBookingInsert";
		
	    var form = Ext.getCmp("custBookingForm").getForm(); 
	    
	    var booking_no = form.findField("booking_no");
		var cust_no = form.findField("cust_no");
	    var cust_nm = form.findField("cust_nm");
		var tel_mobile = form.findField("tel_mobile");
		var tel_home = form.findField("tel_home");
		
		var booking_date = form.findField("booking_date");		
		var booking_time1 = form.findField("booking_time1");
		var booking_time2 = form.findField("booking_time2");
		var booking_status = form.findField("booking_status");
		
		tel_mobile.setValue(maskPhoneNo(tel_mobile.getValue()));
		tel_home.setValue(maskPhoneNo(tel_home.getValue()));
		
		if(booking_no.getValue() != "") {
			url = "/ajaxCustBookingUpdate";
		}
	
		if(cust_nm.getValue() == "" ) {					
			focusMsgAlert('Warning', '고객명을 입력해 주세요', cust_nm);
			return;
		}
		
		if(tel_mobile.getValue() == "" && tel_home.getValue() == "") {
			focusMsgAlert('Warning', '휴대전화 또는 전화번호를 입력해 주세요');					
			return;
		}
		
		if(tel_mobile.getValue() != "") {
			if ( !regPhone.test(tel_mobile.getValue()) ) {
				focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_mobile);
				return;
			}
			
			if ( regPhone2.test(tel_mobile.getValue()) ) {	     				
				focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_mobile);
				return;
			}
		}
		
		if(tel_home.getValue() != "") {
			if ( !regPhone.test(tel_home.getValue()) ) {
				focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_home);
				return;
			}
			
			if ( regPhone2.test(tel_home.getValue()) ) {	     				
				focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_home);
				return;
			}
		}
		
		if(booking_date.getSubmitValue() == "") {
			focusMsgAlert('Warning', '예약일자를 입력해 주세요', booking_date);					
			return;
		}
		
		if(booking_time1.getSubmitValue() == "") {
			focusMsgAlert('Warning', '예약시간(시)을 입력해 주세요', booking_time1);					
			return;
		}
		
		if(booking_time2.getSubmitValue() == "") {
			focusMsgAlert('Warning', '예약시간(분)을 입력해 주세요', booking_time2);					
			return;
		}
									
	    if (form.isValid()) {
	        form.submit({
	        	url: url,
	        	submitEmptyText: false,
	            success: function(form, action) {
	               Ext.Msg.alert('Success', action.result.msg);
	               window.opener.custBookingStore.reload();
	               self.close();
	            },
	            failure: function(form, action) {
	                Ext.Msg.alert('Failed', action.result.msg);
	                return;
	            }
	        });
	    }
	}
	
	function loadBookingData(booking_no) {
		
		if(booking_no != "") { 
			Ext.Ajax.request({
				
		        url: COMMON_URL + '/ajaxCustBookingSelect',
		        params: { 'booking_no' : booking_no},
		        success: function(response) {
		        	
		        	var obj = Ext.decode(response.responseText);
		        	
		        	var resultObj = obj.result;
		        	
		        	custBookingFormPanel.getForm().setValues(resultObj);
		        	custBookingFormPanel.getForm().findField("tel_mobile").setValue(maskPhoneNo(resultObj.tel_mobile));
		        	custBookingFormPanel.getForm().findField("tel_home").setValue(maskPhoneNo(resultObj.tel_home));
		        			        	
		        	var booking_times = resultObj.booking_time.split(":");
		        	
		        	if(booking_times.length > 1) {
		        		custBookingFormPanel.getForm().findField("booking_time1").setValue(booking_times[0]);
		        		custBookingFormPanel.getForm().findField("booking_time2").setValue(booking_times[1]);
		        	}		        	
		        },
		        failure: function(result, request) {
		        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
		    		return;
				}
		    });
		}
	}
	
	loadBookingData(booking_no);
	
	// layout
	Ext.create('Ext.form.Panel', {
		id:'Content',
	    border: 0,
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'hbox',	        
	        align: 'stretch',
	        padding: 5
	    },
	    items: [custBookingFormPanel]
	});
});


