/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMServiceTabPanel.js
* @Author : kyunghee.yoon
* @Date : 2015.10.30
**************************************/	

var comboServiceType = Ext.create('Ext.form.ComboBox', {
    store: serviceTypeStore,
    name: 'service_type',
    fieldLabel: '서비스구분',
    flex:1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    listeners: {
    	change: function(combo, record, index) {
    		
    		var cust_no = custInfoFormPanel.getForm().findField("cust_no").getValue();
    		
    		if(cust_no != "") {
    			
    			comboServiceStatus.clearValue();
        		serviceStatusStore.getProxy().extraParams = {"service_cd1": combo.lastValue};
        		serviceStatusStore.load();
        		
        		setServiceTypeAtion(combo.lastValue);
        		
    		} else {
    			
    			Ext.Msg.alert("Notice", "고객정보를 먼저 조회해 주세요!");
    			comboServiceType.clearValue();	
    		}
        }
    }
});

var comboServiceStatus = Ext.create('Ext.form.ComboBox', {
    store: serviceStatusStore,
    name: 'service_status',
    fieldLabel: '처리상태',
    flex:1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false
});

var comboAgency = Ext.create('Ext.form.ComboBox', {
    store: agencyStore,
    name: 'agency',
    fieldLabel: '대행업체',
    flex:1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    margin: '0 0 0 10'
});

var comboPaymentType = Ext.create('Ext.form.ComboBox', {
    store: paymentTypeStore,
    name: 'payment_type',    
    flex:1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    margin: '0 0 0 5'
});

var comboPrdBadCode1 = Ext.create('Ext.form.ComboBox', {
    store: badCode1Store,
    name: 'bad_cd1',    
    flex:1,
    displayField: 'bad_nm',
    valueField: 'bad_cd',
    emptyText: '선택',
    editable: false,
    listeners: {
    	'change' : function(combo, record, index) {
    		
    		var prd_no = productFormPanel.getForm().findField("prd_no").getValue();
    		
    		// 불량코드2선택
    		badCode2Store.getProxy().extraParams = {"prd_no": prd_no, "bad_m_cd": combo.lastValue};
    		badCode2Store.load();
    	}
    }
});

var comboPrdBadCode2 = Ext.create('Ext.form.ComboBox', {
    store: badCode2Store,
    name: 'bad_cd2',    
    flex:1,
    displayField: 'bad_nm',
    valueField: 'bad_cd',
    emptyText: '선택',
    editable: false,
    margin: '0 0 0 5'
});

var comboServiceTransType = Ext.create('Ext.form.ComboBox', {
    store: serviceTransTypeStore,
    name: 'service_trans_type',    
    width: 105,
    margin: '0 0 0 3',
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '이관사유',
    editable: false,
    margin: '0 0 0 3'
});
	
// 서비스상담정보
var serviceFormPanel = new Ext.form.Panel({
	id: 'serviceFormPanel',
	border: 1,
	padding: '10 0 0 0',
	bodyPadding: '7 7 0 7',
	defaultType: 'textfield',
	defaults: {anchor: '100%'},
	fieldDefaults: {		            
		labelAlign: 'center',
		labelWidth: 60,
		labelSeparator: "",
	    enableKeyEvents: true
	},
	items: [
	{
		xtype: 'hiddenfield',
		name: 'service_no'
	},
	{
		xtype: 'hiddenfield',
		name: 'cust_prd_seq_no'
	},
	{
		xtype: 'hiddenfield',
		name: 'order_records'
	}, 
	{
		xtype: 'hiddenfield',
		name: 'as_records'
	},
    {
        xtype: 'fieldcontainer',            
        layout: 'hbox',
        items: [  
			comboServiceType,	
			{
	            xtype: 'fieldcontainer',
	            fieldLabel: '수거발송',	            
	            defaultType: 'checkboxfield',
	            layout: 'hbox',
	            margin: '0 0 0 10',
	            flex: 1,
	            id: 'chk_as_group',
	            disabled: true,
	            items: [
                {
                    boxLabel: '수거',
                    name: 'chk_pickup',
                    inputValue: 'Y',
                    id: 'chk_pickup'
                }, {
                    boxLabel: '발송',
                    name: 'chk_delivery',
                    inputValue: 'Y',
                    id: 'chk_delivery',
                    margin: '0 0 0 7'
                }, {
                    boxLabel: '직택',
                    name: 'chk_direct',
                    inputValue: 'Y',
                    id: 'chk_direct',
                    margin: '0 0 0 7' 
                }, {
                    boxLabel: '한달내맞교환',
                    name: 'chk_exchange',
                    inputValue: 'Y',
                    id: 'chk_exchange',
                    margin: '0 0 0 7',
                    listeners: {
            			change: function(t, newValue, oldValue, eOpts) {
            				if(t.getValue() == true) {
            					Ext.getCmp("chk_pickup").setValue(true); 
            					Ext.getCmp("chk_delivery").setValue(true);
            				}
            			}
            		}
                }
	            ]
	        }
        ]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',         
        defaultType: 'textfield',
        items: [comboServiceStatus                
                , {
        	name: 'prd_nm',
        	fieldLabel: '제품',
            flex:1,
            margin: '0 0 0 10',
            readOnly: true,
            editable: false
        }
        ]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',         
        defaultType: 'textfield',
        items: [{
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            fieldLabel: '불량코드',
            flex:1,
            items: [comboPrdBadCode1, comboPrdBadCode2]
        }, {
            xtype: 'fieldcontainer',            
            layout: 'hbox',            
            fieldLabel: '결제유형',
            flex:1,
            margin: '0 0 0 10',
            items: [{           
            	xtype: 'combo',
            	name: 'free_cost_yn',
            	store: FreeCostYNStore,
            	width: 80,
            	displayField: 'code_nm',
                valueField: 'code',
            	emptyText:'유무상구분',
            	value: 'Y',
            	listeners: {
            		'change': function(combo, record, index) {
            			if(combo.lastValue == "Y") { // 무상
            				comboPaymentType.clearValue();
            			}
            			calcOrderAmt(); // 계산
            		}
            	}
            }, 
            comboPaymentType]
        }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox', 
        items: [{
            xtype: 'fieldcontainer',            
            layout: 'hbox',           
            fieldLabel: '주문금액',
            flex:1,
            items: [{  
            	xtype: 'numberfield',
            	name: 'payment_amt',
                flex:1,
                value: '0',
                fieldStyle: 'text-align: right;',
                hideTrigger: true
            }, {
            	xtype: 'hiddenfield',
            	name: 'order_amt',
            	flex:1,
                margin: '0 0 0 5'
            }, {
            	xtype: 'hiddenfield',
            	name: 'as_amt',
            	flex:1,
                margin: '0 0 0 5'
            }]
        },  {
        	xtype: 'textfield',
        	name: 'account_no',        	
        	fieldLabel: '가상계좌',
            flex:1,
            readOnly: true,
            editable: false,            
            margin: '0 0 0 10'
        }]
    }, {   
	    xtype: 'textareafield',
		name: 'memo',
	    fieldLabel: '상담내용',
	    height: 70
	}, {
        xtype: 'fieldcontainer',            
        layout: 'hbox', 
        items: [{
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            fieldLabel: '접수',
            flex:1,
            defaultType: 'textfield',
            items: [{ 
            	name: 'insert_nm',        	
                width: 100,
                value: haan_member_nm,
                readOnly: true,
                editable: false
            }, {
            	name: 'insert_dt',	
            	width: 110,
                margin: '0 0 0 5',
                value: toDateTime,
                readOnly: true,
                editable: false
            }]
        }, 
        comboAgency]
    }], 
    tbar : ['<b>서비스 상담정보</b>', '->',
	    {
		    xtype: 'button',
		    text: '새로작성',
		    iconCls: 'icon-yes',
		    tooltip: 'search',
		    handler: function() {	    	 
		    	CRMFormReset();
			}
	    }, {
		    xtype: 'button',
		    text: '서비스저장',
		    iconCls: 'icon-yes',
		    tooltip: 'search',
		    handler: function() {	    	 
		    	CRMFormCheck();
			}
        }
    ]
});

// 이관담당
var transferFormPanel = new Ext.form.Panel({	
	border: 1,
	bodyPadding: '5 7 0 7',
	margin: '5 0 0 0',	
	defaults: {anchor: '100%'},
	fieldDefaults: {		            
		labelAlign: 'center',		
		labelSeparator: "",
	    enableKeyEvents: true
	},
	items: [
    {
        xtype: 'fieldcontainer',            
        layout: 'hbox',
        defaultType: 'textfield',
        fieldLabel: '이관담당',
    	labelWidth: 60,
        flex:1,
        items: [{
        	xtype: 'hiddenfield',
        	name: 'service_dept_cd'
        }, {
        	xtype: 'hiddenfield',
        	name: 'service_member_id'
        }, { 
        	name: 'service_member_nm',
            width: 78,
            readOnly: true,
            editable: false
        }, {
	    	xtype: 'button',
	    	iconCls: 'icon-search',
	    	margin: '0 0 0 3',
	    	handler: function() {
	    		searchMemberWin();
	    	}
	    }, {
        	name: 'service_trans_dt',
        	width: 110,
            margin: '0 0 0 3',
            value: toDateTime,
            readOnly: true,
            editable: false
        },   
	    	comboServiceTransType,
    	{
        	xtype: 'hiddenfield',
        	name: 'service_engineer_id'
        }, 	
	    { 
        	name: 'service_engineer_nm',
        	fieldLabel: '기사',
        	labelWidth: 30,
            width: 110,
            margin: '0 0 0 10',
            emptyText: '기사이름',
            readOnly: true,
            editable: false
        }, {
	    	xtype: 'button',
	    	iconCls: 'icon-search',
	    	margin: '0 0 0 3',
	    	handler: function() {
	    	}
	    }, 
        { 	
	    	name: 'service_engineer_tel_mobile',
	    	width: 110,
            margin: '0 0 0 3',
            emptyText: '기사연락처',
            readOnly: true,
            editable: false
        }]
    }]
});