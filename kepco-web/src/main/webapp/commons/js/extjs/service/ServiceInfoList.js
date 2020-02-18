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

var searchForm;

Ext.onReady(function() {
	
	var url;
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'service_no'
			, 'service_type'
			, 'service_type_nm'
			, 'service_status'
			, 'service_status_nm'
			, 'payment_status'
			, 'payment_status_nm'
			, 'pickup_status'
			, 'pickup_status_nm'
			, 'delivery_status'
			, 'delivery_status_nm'
			, 'cust_no'
			, 'cust_nm'
			, 'service_member_id'
			, 'service_member_nm'
			, 'insert_id'
			, 'insert_nm'
			, 'insert_dt'
			, 'service_dt'
			, 'as_cnt'
			, 'order_cnt'
			, 'site_nm'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxServiceInfoList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'service_no',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'service_no',
			text : '서비스번호',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'service_type_nm',
			text : '서비스구분',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'service_status_nm',
			text : '서비스상태',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'payment_status_nm',
			text : '결제상태',
			width : 120,
			align : 'center',
			sortable : true
		},{
			dataIndex : 'pickup_status_nm',
			text : '수거상태',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'delivery_status_nm', 
			text : '배송상태',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'as_cnt',
			text : '자재',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'order_cnt',
			text : '주문',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'cust_nm',
			text : '고객명',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'cust_no',
			text : '고객번호',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'service_member_nm',
			text : '담당자',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_nm',
			text : '접수자',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_dt',
			text : '접수일시',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'service_dt',
			text : '처리일시',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'site_nm',
			text : '사이트',
			width : 80,
			align : 'center',
			sortable : false
		}
	];    
    
    // 서비스구분코드
    var serviceTypeStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxServiceCodeCombo',
            reader: {root: 'result'}           
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true  
    });

    // 서비스상태코드
    var serviceStatusStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxServiceStatusCombo',
            reader: {root: 'result'}           
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }]
    });	
    
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
    
    // 배송상태
    var deliveryStatusStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            extraParams: {class_cd: 'DL', use_yn:'Y', display_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true  
    });
    
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
    
  //제품군
    var prdCate1Store = Ext.create('Ext.data.Store', {
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdCate1',
            reader: {root: 'result'},
            simpleSortMode: true
        },
        fields: [{ name: 'cate' },{ name: 'cate_nm' }]
    });

    // 모델군
    var prdCate2Store = Ext.create('Ext.data.Store', {
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdCate2',
            reader: {root: 'result'},
            simpleSortMode: true
        },
        fields: [{ name: 'cate' },{ name: 'cate_nm' }]
    });

    // 제품
    var prdNoStore = Ext.create('Ext.data.Store', {
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdNoCombo',
            reader: {root: 'result'},
            simpleSortMode: true
        },
        fields: [{ name: 'prd_no' },{ name: 'prd_serial_no' },{ name: 'prd_nm' },{ name: 'site' }]
    });
    
    var comboSite = Ext.create('Ext.form.ComboBox', {
        store: siteStore,
        id: 'site',
        name: 'site',
        fieldLabel: '사이트',
        width: 250,
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
        margin: '0 0 0 10',
        emptyText: '사이트구분',
        value: '1',
        listeners: {
        	change: function(combo, record, index) { 
        		
        		comboPrdCate1.clearValue();
        		comboPrdCate2.clearValue();
        		comboPrdNo.clearValue();
        		
        		prdCate1Store.getProxy().extraParams = {"site": combo.lastValue};
        		prdCate1Store.load();
            }
        }
    });
    
    var comboGubun = Ext.create('Ext.form.ComboBox', {
        store: gubunStore,        
        name: 'gubun',
        fieldLabel: '담당구분',
        width: 250,
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
        margin: '0 0 0 10',
        value: '1'
    });
    
    
    var comboPrdCate1 = Ext.create('Ext.form.ComboBox', {
        store: prdCate1Store,        
        id: 'prd_cate1',
        name: 'prd_cate1',
        fieldLabel: '제품군',
        width: 250,
        queryMode: 'local',
        displayField: 'cate_nm',
        valueField: 'cate',        
        padding: '0 0 0 10',
        value: '',
        emptyText: '선택',
        editable: false,
        listeners: {
        	change: function(combo, record, index) {                     		
        		
        		comboPrdCate2.clearValue();
        		comboPrdNo.clearValue();
        		
        		prdCate2Store.getProxy().extraParams = {"site": Ext.getCmp("site").getValue(), "prd_cate1": combo.lastValue};
        		prdCate2Store.load();
            }
        }
    });
    
    var comboPrdCate2 = Ext.create('Ext.form.ComboBox', {
        store: prdCate2Store,
        width: 250,   
        id: 'prd_cate2',
        name: 'prd_cate2',
        fieldLabel: '모델군',
        queryMode: 'local',
        displayField: 'cate_nm',
        valueField: 'cate', 
        value: '',
        padding: '0 0 0 10',
        emptyText: '선택',
        editable: false,
        listeners: {
        	change: function(combo, record, index) {                     		
        	
        		comboPrdNo.clearValue();
        		
        		prdNoStore.getProxy().extraParams = {"site": Ext.getCmp("site").getValue(), "prd_cate1": Ext.getCmp("prd_cate1").getValue(), "prd_cate2": combo.lastValue};
        		prdNoStore.load();
            }
        }
    });


    var comboPrdNo = Ext.create('Ext.form.ComboBox', {
        store: prdNoStore,
        width: 250,       
        name: 'prd_no',
        fieldLabel: '제품',
        queryMode: 'local',
        displayField: 'prd_nm',
        valueField: 'prd_no',        
        padding: '0 0 0 10',
        value: '',
        emptyText: '선택',
        editable: false,
        listeners: {    	
        	change: function(combo, record, index) {
        		
            }
        }
    });
    
    var comboServiceType = Ext.create('Ext.form.ComboBox', {
        store: serviceTypeStore,
        name: 'service_type',
        fieldLabel: '서비스구분',
        width: 250, 
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10',
        listeners: {
        	change: function(combo, record, index) {
        		
        		comboServiceStatus.clearValue();
        		serviceStatusStore.getProxy().extraParams = {"service_cd1": combo.lastValue};
        		serviceStatusStore.load();
        		
        		if(combo.lastValue == '10') { // AS
        			Ext.getCmp('chk_as_group').setDisabled(false);
        		} else {
        			Ext.getCmp('chk_as_group').setDisabled(true);
        		}
            }
        }
    });
    
    var comboServiceStatus = Ext.create('Ext.form.ComboBox', {
        store: serviceStatusStore,
        name: 'service_status',
        fieldLabel: '처리상태',
        width: 200, 
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var comboPaymentType = Ext.create('Ext.form.ComboBox', {
        store: paymentTypeStore,
        name: 'payment_type', 
        fieldLabel: '결제유형',
        width: 250,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var comboPaymentStatus = Ext.create('Ext.form.ComboBox', {
        store: paymentStatusStore,
        name: 'payment_status', 
        fieldLabel: '결제상태',
        width: 250,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var comboDeliveryStatus = Ext.create('Ext.form.ComboBox', {
        store: deliveryStatusStore,
        name: 'delivery_status', 
        fieldLabel: '배송상태',
        width: 250,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var comboPickupStatus = Ext.create('Ext.form.ComboBox', {
        store: pickupStatusStore,
        name: 'pickup_status', 
        fieldLabel: '수거상태',
        width: 250,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
    });
        
    searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: 10,
    	layout: {
            type: 'vbox'
        },
        fieldDefaults: {		            
    		labelAlign: 'right',
    		labelWidth: 90,
    		labelSeparator: "",
    	    enableKeyEvents: true
    	},
	    items: [
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [comboSite,			    
		        {
		            xtype: 'fieldcontainer',
		            fieldLabel: '담당자',	            
		            defaultType: 'textfield',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:250,
		            items: [
						{
						    xtype: 'hiddenfield',
						    name: 'service_member_id'
						},
						{
							flex: 1,
						    name: 'service_member_nm',
						    value: '',
						    readOnly: true,
						    editable: false,
							listeners:  {
						        specialkey: function (f,e) {    
						             if (e.getKey() == e.ENTER) {
						            	 reload();
						            }
						        }
						    }
						},
						{
						    xtype: 'button',
						    iconCls: 'icon-search',
						    margin: '0 0 0 5',
							handler: function() {
								searchMemberWin('setServiceMemberInfo');
							}
						}/*,
						{
						    xtype: 'button',
						    iconCls: 'icon-cross',
						    margin: '0 0 0 3',
							handler: function() {
								
							}
						}*/
		            ]
		        }, {
		            xtype: 'fieldcontainer',
		            fieldLabel: '접수자',	            
		            defaultType: 'textfield',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:250,
		            items: [
						{
						    xtype: 'hiddenfield',
						    name: 'insert_id'
						},
						{
							flex: 1,
						    name: 'insert_nm',
						    value: '',
						    readOnly: true,
						    editable: false,
						    value: '',
							listeners:  {
						        specialkey: function (f,e) {    
						             if (e.getKey() == e.ENTER) {
						            	 reload();
						            }
						        }
						    }
						},
						{
						    xtype: 'button',
						    iconCls: 'icon-search',
						    margin: '0 0 0 5',
							handler: function() {
								searchMemberWin('setInsertInfo');
							}
						}/*,
						{
						    xtype: 'button',
						    iconCls: 'icon-cross',
						    margin: '0 0 0 3',
							handler: function() {
								
							}
						}*/
		            ]
		        },
		        comboGubun]
			},
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
			        comboPrdCate1,
			        comboPrdCate2,
			        comboPrdNo,
			        {
			        	xtype: 'textfield',
			        	name: 'prd_nm',        	
			        	fieldLabel: '제품명',
			        	width:250,			                    
			            margin: '0 0 0 10',
			            listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },
			    ]
			},
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
		            {
			        	xtype: 'textfield',
			        	name: 'service_no',        	
			        	fieldLabel: '서비스번호',			        	
			        	width:250,            
			            margin: '0 0 0 10',
			            listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },     
			        comboServiceType,
			        comboServiceStatus,
			        {
			            xtype: 'fieldcontainer',			                    
			            defaultType: 'checkboxfield',
			            layout: 'hbox',
			            margin: '0 0 0 5',
			            width:55,
			            id: 'chk_as_group',
			            disabled: true,
			            items: [
		                {
		                    boxLabel: '맞교환',
		                    name: 'chk_exchange',
		                    inputValue: 'Y',
		                    id: 'chk_exchange'
		                }
			            ]
			        }, {
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '접수일자',
				    width:460,
				    margin: '0 0 0 0',
				    items: [{
			        	xtype: 'datefield',
			        	name: 'sdate',
			        	width: 100,
			        	format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: getWeekDay(),
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }				        	
			        }, {
			        	xtype: 'datefield',
			        	name: 'edate',
			        	width: 100,
			            margin: '0 0 0 5',
			            format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: toDate,
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },
			        {
			            xtype: 'button',
			            text: '오늘',			            
			            margin: '0 0 0 5',
			        	handler: function() {
			        		setFormDate('today', '1');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '주간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('week', '1');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '월간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('month', '1');
			        	}
			        }
			        ]
				}]
			},
			{
			    xtype: 'fieldcontainer',       	     
			    layout: 'hbox',
			    items: [{
		        	xtype: 'textfield',
		        	name: 'account_no',        	
		        	fieldLabel: '가상계좌',
		        	width:250,		            
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },
		        	comboPaymentType,
		        	comboPaymentStatus,
		        {
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '결제일자',
				    width:460,
				    margin: '0 0 0 10',
				    items: [{
			        	xtype: 'datefield',
			        	name: 'payment_sdate',
			        	width: 100,
			        	format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        }, {
			        	xtype: 'datefield',
			        	name: 'payment_edate',
			        	width: 100,
			            margin: '0 0 0 5',
			            format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },{
			            xtype: 'button',
			            text: '오늘',			            
			            margin: '0 0 0 5',
			        	handler: function() {
			        		setFormDate('today', '2');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '주간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('week', '2');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '월간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('month', '2');
			        	}
			        }]
				}]
			},
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [{
		        	xtype: 'textfield',
		        	name: 'invoice_no',        	
		        	fieldLabel: '송장번호',
		        	width:250,           
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },
		        	comboDeliveryStatus,
		        	comboPickupStatus,
		        {
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '수리일자',
				    width:460,
				    margin: '0 0 0 10',
				    items: [{
			        	xtype: 'datefield',
			        	name: 'repair_sdate',
			        	width: 100,
			        	format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        }, {
			        	xtype: 'datefield',
			        	name: 'repair_edate',
			        	width: 100,
			            margin: '0 0 0 5',
			            format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },{
			            xtype: 'button',
			            text: '오늘',			            
			            margin: '0 0 0 5',
			        	handler: function() {
			        		setFormDate('today', '3');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '주간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('week', '3');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '월간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('month', '3');
			        	}
			        }]
				}]
			},
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [{
		        	xtype: 'textfield',
		        	name: 'cust_no',        	
		        	fieldLabel: '고객번호',
		        	width:250,         
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },{
		        	xtype: 'textfield',
		        	name: 'cust_nm',        	
		        	fieldLabel: '고객명',
		        	width:250,           
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },{
		        	xtype: 'textfield',
		        	name: 'contact_no',        	
		        	fieldLabel: '전화/휴대번호',
		        	width:250,            
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },{
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '처리일자',
				    width:460,
				    margin: '0 0 0 10',
				    items: [{
			        	xtype: 'datefield',
			        	name: 'service_sdate',
			        	width: 100,
			        	format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        }, {
			        	xtype: 'datefield',
			        	name: 'service_edate',
			        	width: 100,
			            margin: '0 0 0 5',
			            format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },{
			            xtype: 'button',
			            text: '오늘',			            
			            margin: '0 0 0 5',
			        	handler: function() {
			        		setFormDate('today', '4');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '주간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('week', '4');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '월간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('month', '4');
			        	}
			        }]
				}]
			}
	    ]
	});
    
	Ext.create('Ext.panel.Panel', {
		id:'Content',
	    title: name,
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [
	        searchForm,
	        { // Details Panel specified as a config object (no xtype defaults to 'panel').
		    bodyPadding: 5,
		    padding: '5 0 0 0',
		    layout: {
		        type: 'hbox',
		        align: 'stretch'
		    },
		    items: [{
			    xtype: 'button',
			    text: '검색',
			    margin: '0 0 0 3',
				handler: function() {
					reload();
				}
			}, {
			    xtype: 'button',
			    text: '초기화',
			    margin: '0 0 0 3',
				handler: function() {
					reset();
				}
			}, {
		    	xtype: 'tbfill'
		    }, {
		    	xtype: 'button',
		    	text: '엑셀다운로드',
		    	align:'right',
		    	style:'text-align:right',		    	
		    	iconCls: 'icon-excel',
		    	margin: '0 0 0 5px',
		    	handler: function() {
		    		download();
		    	}
		    }]
		},{
	        xtype: 'splitter'   // A splitter between the two child items
	    },		
	    {               // Results grid specified as a config object with an xtype of 'grid'
	        xtype: 'grid',
	        columns: columns,// One header just for show. There's no data,
	        store: store, // A dummy empty data store
	        flex: 1,                                       // Use 1/3 of Container's height (hint to Box layout)
	        id: 'grid',
	        name: 'grid',
	        scroll: 'both',
			bbar: Ext.create('Ext.PagingToolbar', {
				pageSize: 30,
				store: store,
				displayInfo: true,
				displayMsg: '{0} - {1} of {2} 건',
				emptyMsg: "데이터가 없습니다."
			}),
			listeners: {
	        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
	        		var rec = store.getAt(iRowIdx)
	        		serviceFormWin(rec.data.service_no);
	        	}
	        }
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");		
		var payment_sdate = form.findField("payment_sdate");
		var payment_edate = form.findField("payment_edate");				
		var repair_sdate = form.findField("repair_sdate");
		var repair_edate = form.findField("repair_edate");
		var service_sdate = form.findField("service_sdate");
		var service_edate = form.findField("service_edate");
		
		var contact_no = form.findField("contact_no");
			
		contact_no.setValue(remainNumber(contact_no.getValue()));
			
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '접수일자 검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		if((payment_sdate.getSubmitValue() == "" && payment_edate.getSubmitValue() != "") || 
				(payment_sdate.getSubmitValue() != "" && payment_edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '결제일자 검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		if((repair_sdate.getSubmitValue() == "" && repair_edate.getSubmitValue() != "") || 
				(repair_sdate.getSubmitValue() != "" && repair_edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '수리일자 검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		if((service_sdate.getSubmitValue() == "" && service_edate.getSubmitValue() != "") || 
				(service_sdate.getSubmitValue() != "" && service_edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '처리일자 검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	function reset() {
		var form = Ext.getCmp('searchForm').getForm();
		form.reset();
	}
	
	// form date
	function setFormDate(flag, gubun) {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var toDate = Ext.Date.format(new Date(),'Ymd');
		
		if (gubun == "1") {
			if(flag == "today") { // 오늘			
				form.findField("sdate").setValue(toDate);
				form.findField("edate").setValue(toDate);			
			} else if (flag == "week") { // 주간
				form.findField("sdate").setValue(getWeekDay());			
				form.findField("edate").setValue(toDate);
			} else if (flag == "month") { // 월간
				form.findField("sdate").setValue(getMonthDay());
				form.findField("edate").setValue(toDate);
			} else { //공백
				form.findField("sdate").setValue("");
				form.findField("edate").setValue("");
			}	
		} else if (gubun == "2") {
			if(flag == "today") { // 오늘			
				form.findField("payment_sdate").setValue(toDate);
				form.findField("payment_edate").setValue(toDate);			
			} else if (flag == "week") { // 주간
				form.findField("payment_sdate").setValue(getWeekDay());			
				form.findField("payment_edate").setValue(toDate);
			} else if (flag == "month") { // 월간
				form.findField("payment_sdate").setValue(getMonthDay());
				form.findField("payment_edate").setValue(toDate);
			} else { //공백
				form.findField("payment_sdate").setValue("");
				form.findField("payment_edate").setValue("");
			}	
		} else if (gubun == "3") {
			if(flag == "today") { // 오늘			
				form.findField("repair_sdate").setValue(toDate);
				form.findField("repair_edate").setValue(toDate);			
			} else if (flag == "week") { // 주간
				form.findField("repair_sdate").setValue(getWeekDay());			
				form.findField("repair_edate").setValue(toDate);
			} else if (flag == "month") { // 월간
				form.findField("repair_sdate").setValue(getMonthDay());
				form.findField("repair_edate").setValue(toDate);
			} else { //공백
				form.findField("repair_sdate").setValue("");
				form.findField("repair_edate").setValue("");
			}	
		} else if (gubun == "4") {
			if(flag == "today") { // 오늘			
				form.findField("service_sdate").setValue(toDate);
				form.findField("service_edate").setValue(toDate);			
			} else if (flag == "week") { // 주간
				form.findField("service_sdate").setValue(getWeekDay());			
				form.findField("service_edate").setValue(toDate);
			} else if (flag == "month") { // 월간
				form.findField("service_sdate").setValue(getMonthDay());
				form.findField("service_edate").setValue(toDate);
			} else { //공백
				form.findField("service_sdate").setValue("");
				form.findField("service_edate").setValue("");
			}	
		}	
	}
	
	
	prdCate1Store.getProxy().extraParams = {"site": Ext.getCmp('site').getSubmitValue()};
	prdCate1Store.load();
	
	if(WORK_CD == "WT003") { // 찾서		
		comboGubun.setValue("2"); // 로드샵
	} else if(WORK_CD == "WT004") { // 홈케어		
		comboGubun.setValue("2"); // 로드샵
		comboSite.setValue("4"); //홈케어
	}
	
});

function setServiceMemberInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	searchForm.getForm().findField("service_member_id").setValue(member_id);
	searchForm.getForm().findField("service_member_nm").setValue(member_nm);
}

function setInsertInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	searchForm.getForm().findField("insert_id").setValue(member_id);
	searchForm.getForm().findField("insert_nm").setValue(member_nm);
}

/**
 * 담당자 검색 팝업
 */
function searchMemberWin(func_name)
{
	var win = window.open(COMMON_URL + "/jsp/CRM/MemberInfoSearchPop.jsp?func_name="+func_name, "searchMember", "menubar=no, scrollbars=no, resizable=no, width=800, height=600");
}

/**
 * 서비스조회
 */
function serviceFormWin(service_no)
{
	var win = window.open(COMMON_URL + "/jsp/Service/ServiceInfoFormWin.jsp?service_no="+service_no, "serviceForm", "menubar=no, scrollbars=yes, resizable=yes, width=1280, height=1000");
}

function download() {
	
	Ext.getBody().mask('파일 다운로드 중...');
	
	Ext.Ajax.request({
		url: COMMON_URL + '/ajaxSelectListExcel',
		success: function(result, request) {
			Ext.getBody().unmask();
			var obj = Ext.decode(result.responseText);
			location.href = COMMON_URL + "/common/FileDown.jsp?fileName="+obj.filename+"&fileDir="+obj.filepath;
		},
		failure: function(result, request) {
			Ext.getBody().unmask();        							 
			Ext.Msg.alert('Error', '다운로드 중 오류가 발생하였습니다.');	        							 
		},
		params : Ext.getCmp('searchForm').getForm().getValues(),  
		timeout: TIMEOUT_SEC
	});
}


