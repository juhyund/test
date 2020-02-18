/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : ServiceInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.12.23
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);
	
// 그룹
var custGroupStore = Ext.create('Ext.data.Store', {
	id: 'custGroupStore',        
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCustGroupCombo',
        reader: {root: 'result'},
        simpleSortMode: true,
        extraParams: {use_yn:'Y'}
    },
    fields: [{ name: 'group_no' },{ name: 'group_nm' }],
    autoLoad:true
});

var comboGroup = {
	xtype: 'combobox',
	id: 'group_no',
    store: custGroupStore,
    width: 120,        
    name: 'group_no',
    queryMode: 'local',
    displayField: 'group_nm',
    valueField: 'group_no',
    padding: '0 0 0 5',
    emptyText: '그룹선택'
}

var winCustInfo = null;
//팝업 window
var winCustInfoPop = function(cust_no) {
	
	custInfoform.getForm().reset();
	
	if(!winCustInfo) {
		
    	winCustInfo = Ext.create('Ext.window.Window', {
            title: '고객정보',
            height: 370,
            width: 600,
            closeAction: 'close',
            modal: false,
            resizable: false,
            draggable: true,
            items:[
                   custInfoform
            ]
        });
	}
	
	if(winCustInfo.isVisible()) {
		winCustInfo.hide();
	} else {
		loadDataCustInfo(cust_no);
		winCustInfo.show();			
	}
}

/**
 * 서비스 처리정보
 * @param service_no
 */
function loadDataCustInfo(cust_no) {
	
	var form = custInfoform.getForm();
	
	if(cust_no != undefined && cust_no != "") {
		
		Ext.Ajax.request({
		
	        url: COMMON_URL + '/ajaxCustInfoDetail',
	        params: { 'cust_no' : cust_no},
	        success: function(response) {		        	
	        	var obj = Ext.decode(response.responseText);	        	
	        	var result = obj.result; // 배송정보	
	        	form.setValues(result);
	        },
	        failure: function(result, request) {
	        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
	    		return;
			}
		});	
	}	
}

// 팝업 form
var custInfoform = Ext.create('Ext.form.Panel', {
	id: 'custInfoform',
    bodyPadding: 7,
    flex: 1,
    border: 0,
    layout: 'anchor',
    defaults: {
        anchor: '100%'
    },
    defaultType: 'textfield',
    items: [
		{
		    xtype: 'hiddenfield',
		    name: 'cust_no'
		},
		{   
		    name: 'cust_nm',
		    fieldLabel: '고객명',
		    afterLabelTextTpl: [MARK_ASTERISK]
		},
		{   
			xtype: 'combobox',
			name: 'group_no',
			fieldLabel: '그룹',
	        store: custGroupStore,
	        queryMode: 'local',
	        displayField: 'group_nm',
	        valueField: 'group_no',
	        emptyText: '그룹선택',
	        editable: false,
	        value: '100'
		},			
		{   
		    name: 'tel_mobile',
		    fieldLabel: '휴대번호',
		    afterLabelTextTpl: [MARK_ASTERISK]
		},
		{   
		    name: 'tel_home',
		    fieldLabel: '전화번호',
		    afterLabelTextTpl: [MARK_ASTERISK]
		},			
		{
            xtype: 'fieldcontainer',            
            layout: 'hbox',     
            fieldLabel: '우편번호',
            defaultType: 'textfield',
            items: [{
                name: 'zipcode',
                flex: 1,
                readOnly: true,
                editable: false
            }, {
    	    	xtype: 'button',
    	    	id: 'btnLoadCust',
    	    	text: '우편번호검색',
    	    	align:'right',
    	    	style:'text-align:right',
    	    	iconCls: 'icon-search',
    	    	margin: '0 0 0 5',
    	    	handler: function() {
    	    		zipcode('setZipcodeCustInfo');
    	    	}
    	    }]
        },
		{   
		    name: 'address1',
		    fieldLabel: '주소1',
		    readOnly: true,
            editable: false
		},
		{   
		    name: 'address2',
		    fieldLabel: '주소2'
		},
		{   
		    xtype: 'textareafield',
			name: 'remark',
		    fieldLabel: '비고',
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
            var form = this.up('form').getForm();

			var cust_no	= form.findField("cust_no");
			var cust_nm = form.findField("cust_nm");
			var group_no = form.findField("group_no");				
			var tel_mobile = form.findField("tel_mobile");
			var tel_home = form.findField("tel_home");
			
			tel_mobile.setValue(maskPhoneNo(tel_mobile.getValue()));
			tel_home.setValue(maskPhoneNo(tel_home.getValue()));
			
			if(cust_nm.getValue() == "") {					
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
			
			tel_mobile.setValue(remainNumber(tel_mobile.getValue()));
			tel_home.setValue(remainNumber(tel_home.getValue()));
											
            if (form.isValid()) {
                form.submit({
                	url: COMMON_URL + '/ajaxCustInfoUpdate',
                	submitEmptyText: false,
                    success: function(form, action) {
                    	Ext.Msg.alert('Success', action.result.msg);
                       	reload();
                       	winCustInfo.hide();
                    },
                    failure: function(form, action) {
                        Ext.Msg.alert('Failed', action.result.msg);
                        return;
                    }
                });
            }
        }
    },
    {
        text: '닫기',
        iconCls: 'icon-cancel',
        handler: function() {
        	winCustInfo.hide();
    	}
    }]
});


function setZipcodeCustInfo(zipcode, address1) {
	
	var form = Ext.getCmp('custInfoform').getForm();
	
	form.findField("zipcode").setValue(zipcode);
	form.findField("address1").setValue(address1);
}