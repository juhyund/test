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

// 수거상태
var pickupStatusStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},
        extraParams: {class_cd: 'PK', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});
    
// 배송업체
var pickupAgencyStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},
        extraParams: {class_cd: 'DP', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

var comboPickupStatus = Ext.create('Ext.form.ComboBox', {
    store: pickupStatusStore,
    name: 'delivery_status', 
    fieldLabel: '수거상태',
    flex: 1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    value: 'PK001',
    afterLabelTextTpl: [MARK_ASTERISK]
});  

var comboPickupAgency = Ext.create('Ext.form.ComboBox', {
    store: pickupAgencyStore,
    name: 'delivery_agency',
    fieldLabel: '수거업체',
    flex: 1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    margin: '0 0 0 15',
    value: 'DP001',
    afterLabelTextTpl: [MARK_ASTERISK]
});

var winServicePickup = null;
//팝업 window
var winServicePickupPop = function(service_no, delivery_no, cust_no, cust_nm, tel_mobile, zipcode, address1, address2, insert_dt) {
	
	servicePickupform.getForm().reset();
	
	if(!winServicePickup) {
		
    	winServicePickup = Ext.create('Ext.window.Window', {
            title: '수거처리정보',
            height: 450,
            width: 600,
            closeAction: 'close',
            modal: false,
            resizable: false,
            draggable: true,
            items:[
                   servicePickupform
            ]
        });
	}
	
	if(winServicePickup.isVisible()) {
		winServicePickup.hide();
	} else {
		loadDataServicePickup(service_no, delivery_no, cust_no, cust_nm, tel_mobile, zipcode, address1, address2, insert_dt);
		winServicePickup.show();			
	}
}


/**
 * 서비스 처리정보
 * @param service_no
 */
function loadDataServicePickup(service_no, delivery_no, cust_no, cust_nm, tel_mobile, zipcode, address1, address2, insert_dt) {

	var form = servicePickupform.getForm();
	
	form.findField("service_no").setValue(service_no);
	form.findField("delivery_no").setValue(delivery_no);
	form.findField("cust_no").setValue(cust_no);
	form.findField("cust_nm").setValue(cust_nm);
	form.findField("delivery_owner_nm").setValue(cust_nm);
	form.findField("tel_mobile").setValue(tel_mobile);
	form.findField("zipcode").setValue(zipcode);
	form.findField("address1").setValue(address1);
	form.findField("address2").setValue(address2);
	
	if(insert_dt == "") {
		form.findField("insert_dt").setValue(toDateTime);
	} else {
		form.findField("insert_dt").setValue(insert_dt);
	}
		
	if(delivery_no != undefined && delivery_no != "") {
		
		Ext.Ajax.request({
		
	        url: COMMON_URL + '/ajaxServiceDeliveryDetail',
	        params: { 'service_no' : service_no, 'delivery_no' : delivery_no},
	        success: function(response) {	        	
	        	var obj = Ext.decode(response.responseText);	        	
	        	var result = obj.result; // 배송정보	
	        	form.setValues(result);
	        },
	        failure: function(result, request) {
	        	// console.log(result);
	        	// console.log(request);
	        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
	    		return;
			}
		});	
	} else {
		
		Ext.Ajax.request({
			
	        url: COMMON_URL + '/ajaxServiceInfoDetailCRM',
	        params: { 'service_no' : service_no},
	        success: function(response) {
	        	
	        	var obj = Ext.decode(response.responseText);        	
	        	
	        	var result = obj.serviceInfoData;
	        	
	        	form.findField("delivery_owner_nm").setValue(result.pickup_owner_nm);
	        	form.findField("tel_mobile").setValue(result.pickup_tel_mobile);
	        	form.findField("zipcode").setValue(result.pickup_zipcode);
	        	form.findField("address1").setValue(result.pickup_address1);
	        	form.findField("address2").setValue(result.pickup_address2);
	        	form.findField("remark").setValue(result.pickup_remark);
	        	
	        },
	        failure: function(result, request) {
	        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
	    		return;
			}
		});	
			
		//form.findField("delivery_remark").setValue(remark);
		
	}
}

// 팝업 form
var servicePickupform = Ext.create('Ext.form.Panel', {
	id: 'servicePickupform',
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
        	name: 'delivery_no'				
		},
		{
			xtype: 'hiddenfield',
        	name: 'delivery_flag',
        	value: '1'
		},
		{
			xtype: 'hiddenfield',
        	name: 'delivery_type',
        	value: '2'
		},
		{
			xtype: 'hiddenfield',
        	name: 'delivery_owner_type',
        	value: '1'
		},
		{
			xtype: 'hiddenfield',
        	name: 'service_type'				
		},
		{
			xtype: 'hiddenfield',
        	name: 'service_status'				
		},		
		{
			xtype: 'hiddenfield',
        	name: 'site'				
		},
		{
			xtype: 'hiddenfield',
        	name: 'invoice_nm'				
		},
		{
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'service_no',
				fieldLabel: '서비스번호',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1,
		        afterLabelTextTpl: [MARK_ASTERISK]
			}, {
				name: 'insert_dt',
				fieldLabel: '접수일시',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1,
		        margin: '0 0 0 15',
		        afterLabelTextTpl: [MARK_ASTERISK]
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'cust_nm',
				fieldLabel: '고객명',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1,
		        afterLabelTextTpl: [MARK_ASTERISK]
			}, {
				name: 'cust_no',
				fieldLabel: '고객번호',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1,
		        margin: '0 0 0 15',
		        afterLabelTextTpl: [MARK_ASTERISK]
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'delivery_owner_nm',
				fieldLabel: '수령자',	
		        flex: 1,
		        afterLabelTextTpl: [MARK_ASTERISK]
			}, {
				name: 'invoice_no',
				fieldLabel: '송장번호',	
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'tel_mobile',
				fieldLabel: '휴대번호',
		        flex: 1,
		        afterLabelTextTpl: [MARK_ASTERISK]
			}, {
				name: 'tel_home',
				fieldLabel: '전화번호',
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [comboPickupStatus, comboPickupAgency]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox', 
	        defaultType: 'textfield',
	        fieldLabel: '수거지 주소',
	        afterLabelTextTpl: [MARK_ASTERISK],
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
		    		zipcode('setOrderAddr2');
		    	}
		    }, {
	            name: 'address1',
	            flex: 1,
	            padding: '0 0 0 5'
	        }]
	    }, {
	        fieldLabel: '상세주소',
	        afterLabelTextTpl: [MARK_ASTERISK],
	        name: 'address2'
	    }, {   
		    xtype: 'textareafield',
			name: 'delivery_remark',
		    fieldLabel: '배송정보',
		    height: 80
		}, {   
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
        	
            var service_no = form.findField("service_no");
            var delivery_no = form.findField("delivery_no");
            var delivery_owner_nm = form.findField("delivery_owner_nm");
            var tel_mobile = form.findField("tel_mobile");
            
            var delivery_status = form.findField("delivery_status");
            var delivery_agency = form.findField("delivery_agency");
            var invoice_no = form.findField("invoice_no");
            var invoice_nm = form.findField("invoice_nm");
            
            var remark = form.findField("remark");
			
			if(service_no.getValue() == "" ) {					
				focusMsgAlert('Warning', '서비스번호가 없습니다.', service_no);
				return;
			}
			
			if(delivery_owner_nm.getValue() == "" ) {					
				focusMsgAlert('Warning', '수거자를 입력해 주시기 바랍니다.', delivery_owner_nm);
				return;
			}
			
			if(tel_mobile.getValue() == "" ) {					
				focusMsgAlert('Warning', '휴대번호를 입력해 주시기 바랍니다.', tel_mobile);
				return;
			}
			
			if(delivery_status.getSubmitValue() == "" ) {					
				focusMsgAlert('Warning', '수거상태를 선택해 주시기 바랍니다.', delivery_status);
				return;
			}
			
			if(delivery_agency.getSubmitValue() == "" ) {					
				focusMsgAlert('Warning', '수거업체를 선택해 주시기 바랍니다.', delivery_agency);
				return;
			}
			
			if(delivery_status.getSubmitValue() == "PK003" ) {	// 수거완료				
				if(invoice_no.getValue() == "" ) {					
					focusMsgAlert('Warning', '송장번호를 입력해 주시기 바랍니다.', invoice_no);
					return;
				}
				
				if(delivery_agency.getSubmitValue() == "" ) {					
					focusMsgAlert('Warning', '배송업체를 선택해 주시기 바랍니다.', delivery_agency);
					return;
				}
			}
			
			invoice_nm.setValue(delivery_agency.getRawValue()); // 택배사명
			
			if(delivery_no.getValue() == "") { // 신규
				url = COMMON_URL + '/ajaxServiceDeliveryInsert';
			} else { // 수정
				url = COMMON_URL + '/ajaxServiceDeliveryUpdate';
			}
											
            if (form.isValid()) {
                form.submit({
                	url: url,
                	submitEmptyText: false,
                    success: function(form, action) {	                    	
                       Ext.Msg.alert('Success', action.result.msg);
                       reload(service_no.getValue());
                       winServicePickup.hide();
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
        	winServicePickup.hide();
    	}
    }]
});

function setOrderAddr2(zipcode, address1) {

	var form = servicePickupform.getForm();
	
	form.findField("zipcode").setValue(zipcode);
	form.findField("address1").setValue(address1);
}