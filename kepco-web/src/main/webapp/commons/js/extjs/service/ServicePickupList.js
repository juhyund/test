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
var insertform2;

Ext.onReady(function() {
	
	var url;
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'service_no'
			, 'delivery_no'
			, 'delivery_type'
			, 'service_type'
			, 'service_type_nm'
			, 'service_status'
			, 'service_status_nm'
			, 'payment_status'
			, 'payment_status_nm'
			, 'free_cost_yn'
			, 'cust_no'
			, 'cust_nm'
			, 'delivery_status'
			, 'delivery_status_nm'
			, 'delivery_agency'
			, 'delivery_agency_nm'
			, 'invoice_no'
			, 'service_member_id'
			, 'service_member_nm'
			, 'insert_id'
			, 'insert_nm'			
			, 'insert_dt'
			, 'service_dt'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxServicePickupList',
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
        { 	xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'service_no',
			text : '서비스번호',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'delivery_no',
			text : '배송번호',
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
			dataIndex : 'delivery_agency_nm',
			text : '수거업체',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'invoice_no',
			text : '송장번호',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'delivery_status_nm',
			text : '수거상태',
			width : 120,
			align : 'center',
			sortable : true
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
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_nm',
			text : '접수자',
			width : 120,
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
    var deliveryAgencyStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            extraParams: {class_cd: 'DP', use_yn:'Y', display_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true  
    });
    
    // 주문구분
	var deliveryFlagStore = Ext.create('Ext.data.ArrayStore', {
	    fields: [{ name: 'code' },{ name: 'code_nm' }],
	    data: [['3','반품'],['2', '교환']]
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
            }
        }
    });
    
    var comboServiceStatus = Ext.create('Ext.form.ComboBox', {
        store: serviceStatusStore,
        name: 'service_status',
        fieldLabel: '처리상태',
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
    
    var comboDeliveryAgency = Ext.create('Ext.form.ComboBox', {
        store: deliveryAgencyStore,
        name: 'delivery_agency',
        fieldLabel: '택배업체',
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
    
    var freeCostYNStore = Ext.create('Ext.data.Store', {
	    fields: ['code', 'name'],
	    data : [
	        {"code":"", "name":"전체"},
	        {"code":"Y", "name":"무상"},
	        {"code":"N", "name":"유상"}
	    ]
	});
    
    var comboFreeCostYN = Ext.create('Ext.form.ComboBox', {
        store: freeCostYNStore,
        name: 'free_cost_yn', 
        fieldLabel: '유무상/택배',
        width: 195,
        displayField: 'name',
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
						    name: 'delivery_type',
						    value : '2'
						},
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
		        }]
			},
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
			        comboServiceType,
			        comboServiceStatus,
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
			        }, {
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '접수일자',
				    width:300,
				    margin: '0 0 0 10',
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
				    width:300,
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
		        	comboPickupStatus,	
		        	comboDeliveryAgency
				]
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
		    	handler: function(){
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
	        		
	        		var rec = store.getAt(iRowIdx);			
				
	        		var service_no = rec.data.service_no;
	        		var delivery_no = rec.data.delivery_no;
	        		var cust_nm = rec.data.cust_nm;
	        		var insert_dt = rec.data.insert_dt;
				
	        		winServicePickupPop(service_no, delivery_no, cust_nm, insert_dt);
	        	}
	        }
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");		
		var service_sdate = form.findField("service_sdate");
		var service_edate = form.findField("service_edate");
		var contact_no = form.findField("contact_no");
			
		contact_no.setValue(remainNumber(contact_no.getValue()));
			
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '접수일자 검색은 시작일자와 종료일자 모두 입력해 주세요!');
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
	
});

function setServiceMemberInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	searchForm.getForm().findField("service_member_id").setValue(member_id);
	searchForm.getForm().findField("service_member_nm").setValue(member_nm);
}

function setInsertInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	searchForm.getForm().findField("insert_id").setValue(member_id);
	searchForm.getForm().findField("insert_nm").setValue(member_nm);
}

function setZipcode1(zipcode, address1) {
	
	var form = insertform2.getForm();
	
	form.findField("zipcode").setValue(zipcode);
	form.findField("address1").setValue(address1);
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
	var win = window.open(COMMON_URL + "/jsp/Service/ServiceInfoFormWin.jsp?service_no="+service_no, "serviceForm", "menubar=no, scrollbars=yes, resizable=yes, width=1200, height=1000");
}

function download() {
	
	Ext.getBody().mask('파일 다운로드 중...');
	
	Ext.Ajax.request({
		url: COMMON_URL + '/ajaxSelectDeliveryExcel',
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

