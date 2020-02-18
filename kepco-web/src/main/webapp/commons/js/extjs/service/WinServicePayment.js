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

// 결제유형
var paymentTypeStore = Ext.create('Ext.data.Store', {	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},
        extraParams: {class_cd: 'PC', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

// 결제상태
var paymentStatusStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},
        extraParams: {class_cd: 'PM', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});
    
// 결제상태
var comboPaymentStatus = Ext.create('Ext.form.ComboBox', {
    store: paymentStatusStore,
    name: 'payment_status', 
    fieldLabel: '결제상태',
    flex: 1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    margin: '0 0 0 15',
    value: 'PM001',
    afterLabelTextTpl: [MARK_ASTERISK]
});  

// 결제유형
var comboPaymentType = Ext.create('Ext.form.ComboBox', {
    store: paymentTypeStore,
    name: 'payment_type',
    fieldLabel: '결제유형',
    flex: 1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    value: '',
    afterLabelTextTpl: [MARK_ASTERISK]
});

var winServicePayment = null;
//팝업 window
var winServicePaymentPop = function(service_no, payment_no, cust_no, cust_nm) {
	
	servicePaymentform.getForm().reset();
	
	if(!winServicePayment) {
		
    	winServicePayment = Ext.create('Ext.window.Window', {
            title: '결제정보',
            height: 520,
            width: 650,
            closeAction: 'close',
            modal: false,
            resizable: false,
            draggable: true,
            items: [
                   servicePaymentform
            ]
        });
	}
	
	if(winServicePayment.isVisible()) {
		winServicePayment.hide();
	} else {
		loadDataServicePayment(service_no, payment_no, cust_no, cust_nm);
		winServicePayment.show();			
	}
}

var html = '<div style="line-height:19px;">'; 
	html += '<ol start="1">';
	html += '<li> 가상계좌 신규 등록시 결제 완료 상태로 등록하면 신규 가상계좌가 발행되지 않습니다.</li>';
	html += '<li> 가상계좌 신규 등록시 이전에 결제완료되지 않은 계좌가 있으면 자동으로 계좌가 취소되고 다시 발행.</li>';
	html += '<li> 결제정보 신규 등록시 결제 유형에 따라서 고객에게 자동으로 계좌 정보가 발송됩니다.<br>- 가상계좌: 자동생성 발송<br>- 고객센터-무통장: 기업은행 137-055741-01-058 </li>';	
	html += '<li> 계좌 발급일은 가상계좌 발생시 자동으로 갱신되어 등록됩니다. </li>';
	html += '<li> 결제완료일의 경우 사용자 등록값이 저장되나 가상계좌 연동시에 결제 완료되면 다시 갱신 됩니다. </li>';
	html += '</ol></div>';	
/**
 * 서비스 처리정보
 * @param service_no
 */
function loadDataServicePayment(service_no, payment_no, cust_no, cust_nm) {

	var form = servicePaymentform.getForm();
	
	form.findField("service_no").setValue(service_no);
	form.findField("payment_no").setValue(payment_no);
	form.findField("cust_no").setValue(cust_no);
	form.findField("cust_nm").setValue(cust_nm);
	form.findField("insert_dt").setValue(toDateTime);
	
	if(payment_no == undefined) payment_no = "";
		
	Ext.Ajax.request({
	
        url: COMMON_URL + '/ajaxServicePaymentDetail',
        params: { 'service_no' : service_no, 'payment_no' : payment_no},
        success: function(response) {
        	
        	var obj = Ext.decode(response.responseText);	        	
        	var result = obj.result; // 배송정보
        	var paymentAmtMap = obj.paymentAmtMap; // 배송정보        	
        	
        	if(result != null) {
        		form.setValues(result);
        	} else {
        		form.findField("order_amt").setValue(paymentAmtMap.order_amt); // 주문금액
            	form.findField("as_amt").setValue(paymentAmtMap.as_amt); // 서비스금액
            	form.findField("payment_amt").setValue(Number(paymentAmtMap.order_amt) + Number(paymentAmtMap.as_amt)); // 결제금액
        	}
        },
        failure: function(result, request) {
        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
    		return;
		}
	});		
	 	
}

// 팝업 form
var servicePaymentform = Ext.create('Ext.form.Panel', {
	id: 'servicePaymentform',
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
        	name: 'payment_no'				
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
		        flex: 1
			}, {
				name: 'insert_dt',
				fieldLabel: '접수일시',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1,
		        margin: '0 0 0 15'
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
		        flex: 1
			}, {
				name: 'cust_no',
				fieldLabel: '고객번호',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'as_amt',
				fieldLabel: '서비스 비용',
		        flex: 1,
		        value: '0',
                fieldStyle: 'text-align: right;'
			}, {
				name: 'order_amt',
				fieldLabel: '주문금액',
		        flex: 1,
		        margin: '0 0 0 15',
		        value: '0',
                fieldStyle: 'text-align: right;'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [comboPaymentType, comboPaymentStatus]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'payment_amt',
				fieldLabel: '결제비용',
		        flex: 1,
		        value: '0',
                fieldStyle: 'text-align: right;',
		        afterLabelTextTpl: [MARK_ASTERISK]
			}, {
				name: 'payment_dt',
				fieldLabel: '결제완료일',
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'account_no',
				fieldLabel: '가상계좌번호',
		        flex: 1
			}, {
				name: 'account_issue_dt',
				fieldLabel: '계좌발급일자',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'payment_auth_no',
				fieldLabel: '카드승인번호',
		        flex: 1
			}, {
				name: 'card_chain_no',
				fieldLabel: '가맹번호',
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {   
		    xtype: 'textareafield',
			name: 'remark',
		    fieldLabel: '비고',
		    height: 50
		}, {
	        xtype:'fieldset',
	        bodyPadding: 5,
	        title: '결제정보 등록 주의사항',
	        defaults: {anchor: '100%'},
	        layout: 'anchor',
	        items :[{'html' : html, border: 0}]
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
            var payment_no = form.findField("payment_no");
            var payment_type = form.findField("payment_type");
            var payment_status = form.findField("payment_status");
            var payment_amt = form.findField("payment_amt");
            var payment_dt = form.findField("payment_dt");
            
            var remark = form.findField("remark");
			
			if(service_no.getValue() == "" ) {					
				focusMsgAlert('Warning', '서비스번호가 없습니다.', service_no);
				return;
			}
			
			if(payment_type.getSubmitValue() == "" ) {					
				focusMsgAlert('Warning', '결제유형을 선택해 주시기 바랍니다.', payment_type);
				return;
			}
			
			if(payment_status.getSubmitValue() == "" ) {					
				focusMsgAlert('Warning', '결제상태를 선택해 주시기 바랍니다.', payment_status);
				return;
			}
			
			/*if(payment_status.getSubmitValue() == "PM002") { // 결제완료
				if(payment_dt.getSubmitValue() == "" ) { // 결제처리일시					
					focusMsgAlert('Warning', '결제처리일시를 입력해 주세요', payment_dt);
					return;
				}
			}*/
			
			if (isNaN(payment_amt.getValue())) {
				focusMsgAlert('Warning', '결제금액을 숫자로 입력해 주시기 바랍니다.', payment_amt);
				return;
            }
			
			if (Number(payment_amt.getValue()) < 0) {
				focusMsgAlert('Warning', '결제금액은 0원 이상 입력해 주세요', payment_amt);
				return;
            }
			
			if(payment_no.getValue() == "") { // 신규
				url = COMMON_URL + '/ajaxServicePaymentInsert';
			} else { // 수정
				url = COMMON_URL + '/ajaxServicePaymentUpdate';
			}
											
            if (form.isValid()) {
                form.submit({
                	url: url,
                	submitEmptyText: false,
                    success: function(form, action) {	                    	
                       Ext.Msg.alert('Success', action.result.msg);
                       reload(service_no.getValue());
                       winServicePayment.hide();
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
        	winServicePayment.hide();
    	}
    }]
});
