/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMCustInfoFormPanel.js
* @Author : kyunghee.yoon
* @Date : 2015.10.26
**************************************/
	
// 고객정보 PANEL
var custInfoFormPanel = new Ext.form.Panel({
	id: 'custInfoForm',
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
    defaults: {anchor: '100%'},
    items: [{
    	xtype: 'hiddenfield',
    	name: 'group_no',
    	value: '100'
	}, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',  
        defaultType: 'textfield',
        items: [{
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            defaultType: 'textfield',
            flex: 1,            
            fieldLabel: '고객명',
            afterLabelTextTpl: [MARK_ASTERISK],
            items: [{
                name: 'cust_nm',
                flex: 1
            }, {
    	    	xtype: 'button',
    	    	iconCls: 'mobile_phone',
    	    	margin: '0 0 0 5',
    	    	handler: function() {
    	    	}
    	    }]
        }, {
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            defaultType: 'textfield',
            flex: 1,
            margin: '0 0 0 10',
            fieldLabel: '휴대번호',
            afterLabelTextTpl: [MARK_ASTERISK],
            items: [{
                name: 'tel_mobile',
                flex: 1
            }, {
    	    	xtype: 'button',
    	    	iconCls: 'icon-Dial',
    	    	margin: '0 0 0 5',
    	    	handler: function() {
    	    	}
    	    }]
        }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',         
        defaultType: 'textfield',
        items: [{
        	name: 'cust_no',
        	fieldLabel: '고객번호',        	
            flex:1,
            readOnly: true,
            editable: false
        }, {
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            defaultType: 'textfield',
            flex: 1,
            margin: '0 0 0 10',    	            
            fieldLabel: '전화번호',
            items: [{
            	name: 'tel_home',
                flex: 1
            }, {
    	    	xtype: 'button',
    	    	iconCls: 'icon-Hungup',
    	    	margin: '0 0 0 5',
    	    	handler: function() {
    	    	}
    	    }]
        }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox', 
        defaultType: 'textfield',
        fieldLabel: '주소',
        items: [{
            name: 'zipcode',
            width: 60,
            readOnly: true,
            editable: false
        }, {
	    	xtype: 'button',
	    	iconCls: 'icon-search',
	    	margin: '0 0 0 5',
	    	handler: function() {
	    		zipcode('setZipcode1');
	    	}
	    }, {
            name: 'address1',
            flex: 1,
            readOnly: true,
            editable: false,
            padding: '0 0 0 5'
        }]
    }, {
        fieldLabel: '상세주소',
        name: 'address2'
    }, {
        fieldLabel: '비고',
        name: 'cust_remark'
    }],
    tbar : ['<b>고객정보</b>', '->',
        {
		    xtype: 'button',
		    text: '고객정보 새로작성',
		    iconCls: 'icon-yes',
		    tooltip: 'search',
		    handler: function() {
		    	CRMFormResetAll();
			}
	    }, 
        {
			xtype: 'button',
			text: '통화예약',
			iconCls: 'icon-yes',
			tooltip: 'search',
			handler: function() {	    	 
				var form = this.up('form').getForm();
				
				var cust_no = form.findField("cust_no").getValue();
				var cust_nm = form.findField("cust_nm").getValue();
				var tel_mobile = form.findField("tel_mobile").getValue();
				var tel_home = form.findField("tel_home").getValue();
								
				custBookingWin(cust_no, cust_nm, tel_mobile, tel_home, '');
			}
        }, {
		    xtype: 'button',
		    text: '고객정보저장',
		    iconCls: 'icon-yes',
		    tooltip: 'search',
		    handler: function() {	    	 
			    var form = this.up('form').getForm();
			    saveCustInfoForm(form);
			}
        }
    ]
});

/**
 * 고객정보저장 FORM CHECK
 * @param form
 */
function saveCustInfoForm(form) {
	
	var url = COMMON_URL + "/ajaxCustInfoInsert";
	
	var cust_no = form.findField("cust_no");	
	var cust_nm = form.findField("cust_nm");
	var tel_mobile = form.findField("tel_mobile");
	var tel_home = form.findField("tel_home");
	
	tel_mobile.setValue(maskPhoneNo(tel_mobile.getValue()));
	tel_home.setValue(maskPhoneNo(tel_home.getValue()));
	
	if(cust_no.getValue() != "") {
		url = COMMON_URL + "/ajaxCustInfoUpdate";
	}
	
	if(cust_nm.getValue() == "") {					
		focusMsgAlert('Warning', '고객명을 입력해 주세요', cust_nm);
		return;
	}
	
	if(tel_mobile.getValue() == "") {					
		focusMsgAlert('Warning', '휴대번호를 입력해 주세요', tel_mobile);
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
									
    if (form.isValid()) {
        form.submit({
        	url: url,
        	submitEmptyText: false,
            success: function(form, action) {
               Ext.Msg.alert('Success', action.result.msg);
               
               if(cust_no.getValue() == "") {
            	   loadCustInfo(action.result.result);
               }
               return;
            },
            failure: function(form, action) {
                Ext.Msg.alert('Failed', action.result.msg);
                return;
            }
        });
    }
}


function setZipcode1(zipcode, address1) {
	
	var form = Ext.getCmp('custInfoForm').getForm();
	
	form.findField("zipcode").setValue(zipcode);
	form.findField("address1").setValue(address1);
}

/**
 * 고객정보 조회
 * @param cust_no
 */
function loadCustInfo(cust_no) {
	
	Ext.Ajax.request({
		
        url: COMMON_URL + 'ajaxCustInfoDetail',
        params: { 'cust_no' : cust_no},
        success: function(response) {
        	
        	var obj = Ext.decode(response.responseText);
        	
        	var custInfoData = obj.result;
        
        	// 고객정보
        	custInfoFormPanel.getForm().setValues(custInfoData);    
        	custInfoFormPanel.getForm().findField("tel_mobile").setValue(maskPhoneNo(custInfoData.tel_mobile));
        	custInfoFormPanel.getForm().findField("tel_home").setValue(maskPhoneNo(custInfoData.tel_home));
        },
        failure: function(result, request) {
        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
    		return;
		}
    });		
}