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

// 이관사유
var serviceTransTypeStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},           
        extraParams: {class_cd: 'TR', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

// 이관사유
var comboServiceTransType = Ext.create('Ext.form.ComboBox', {
    store: serviceTransTypeStore,
    name: 'service_trans_type', 
    fieldLabel: '이관사유',
    flex: 1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    value: '',
    afterLabelTextTpl: [MARK_ASTERISK]
});  


var winServiceTrans = null;
//팝업 window
var winServiceTransPop = function(service_no, trans_seq_no, cust_no, cust_nm) {
	
	serviceTransform.getForm().reset();
	
	if(!winServiceTrans) {
		
    	winServiceTrans = Ext.create('Ext.window.Window', {
            title: '이관이력',
            height: 270,
            width: 550,
            closeAction: 'close',
            modal: false,
            resizable: false,
            draggable: true,
            items: [
                   serviceTransform
            ]
        });
	}
	
	if(winServiceTrans.isVisible()) {
		winServiceTrans.hide();
	} else {
		loadDataServiceTrans(service_no, trans_seq_no, cust_no, cust_nm);
		winServiceTrans.show();			
	}
}


/**
 * 서비스 처리정보
 * @param service_no
 */
function loadDataServiceTrans(service_no, trans_seq_no, cust_no, cust_nm) {

	var form = serviceTransform.getForm();
	
	form.findField("arr_service_no").setValue(service_no);
	form.findField("cust_no").setValue(cust_no);
	form.findField("cust_nm").setValue(cust_nm);
	form.findField("insert_dt").setValue(toDateTime);
	
	if(trans_seq_no != undefined && trans_seq_no != "") {
		
		Ext.Ajax.request({
		
	        url: COMMON_URL + '/ajaxServiceTransDetail',
	        params: { 'service_no' : service_no, 'trans_seq_no' : trans_seq_no},
	        success: function(response) {
	        	
	        	var obj = Ext.decode(response.responseText);	        	
	        	var result = obj.result; // 	
	        	form.setValues(result);
	        	
	        	Ext.getCmp("btnSaveTrans").hide();
	        },
	        failure: function(result, request) {
	        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
	    		return;
			}
		});	
	} else {
		Ext.getCmp("btnSaveTrans").show();
	}		
}

// 팝업 form
var serviceTransform = Ext.create('Ext.form.Panel', {
	id: 'serviceTransform',
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
		    name: 'service_dept_cd'
		},
		{
		    xtype: 'hiddenfield',
		    name: 'service_member_id'
		},
		{
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'arr_service_no',
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
		},
		{
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [
	            comboServiceTransType, 
	        {
		        xtype: 'fieldcontainer',            
		        layout: 'hbox',         
		        defaultType: 'textfield',
		        flex: 1,
		        margin: '0 0 0 15',
		        items: [
		            {
			        	name: 'service_member_nm',
			        	fieldLabel: '담당자',
			        	afterLabelTextTpl: [MARK_ASTERISK],
			            flex:1,			            
			            readOnly: true,
			            editable: false
		        	}, {
					    xtype: 'button',
					    iconCls: 'icon-search',
					    margin: '0 0 0 3',
						handler: function() {
							searchMemberWin('setMemberInfo');
						}
					} 
		        ]
		    }]
		},
		{   
		    xtype: 'textareafield',
			name: 'service_trans_remark',
		    fieldLabel: '비고',
		    height: 90
		}
    ],
    buttons: [
  	  	'<font color="red">*</font>  항목은 필수 항목입니다.',
        '->',
        {
        text: '저장',
        id: 'btnSaveTrans',
        formBind: true, 
        iconCls: 'icon-yes',
        handler: function() {
            
        	var form = this.up('form').getForm();
        	
            var arr_service_no = form.findField("arr_service_no");
			var service_member_nm = form.findField("service_member_nm");
			var service_trans_type = form.findField("service_trans_type");
			
			if(arr_service_no.getValue() == "") {					
				focusMsgAlert('Warning', '이관 할 서비스 번호를 선택해 주세요', arr_service_no);
				return;
			}
			
			if(service_trans_type.getSubmitValue() == "") {					
				focusMsgAlert('Warning', '이관 사유를 선택해 주세요', service_trans_type);
				return;
			}
			
			if(service_member_nm.getValue() == "") {					
				focusMsgAlert('Warning', '이관 받을 담당자를 선택해 주세요', service_member_nm);
				return;
			}
											
            if (form.isValid()) {
                form.submit({
                	url: COMMON_URL + '/ajaxServiceTransInsert',
                	submitEmptyText: false,
                    success: function(form, action) {
                       Ext.Msg.alert('Success', action.result.msg);
	                       reload(arr_service_no.getValue());
	                       winServiceTrans.hide();
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
        	winServiceTrans.hide();
    	}
    }]
});

function setMemberInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	serviceTransform.getForm().findField("service_member_id").setValue(member_id);
	serviceTransform.getForm().findField("service_member_nm").setValue(member_nm);
	serviceTransform.getForm().findField("service_dept_cd").setValue(dept_cd);
}

/**
 * 담당자 검색 팝업
 */
function searchMemberWin(func_name)
{
	var win = window.open(COMMON_URL + "/jsp/CRM/MemberInfoSearchPop.jsp?func_name="+func_name, "searchMember", "menubar=no, scrollbars=no, resizable=no, width=800, height=600");
}
