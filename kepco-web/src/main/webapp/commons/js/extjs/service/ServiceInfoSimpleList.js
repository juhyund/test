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
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 20,
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
        {xtype: 'rownumberer', header : 'No', align: 'center', width: 40},
        {
			dataIndex : 'service_no',
			text : '서비스',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'service_type_nm',
			text : '서비스구분',
			width : 90,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'service_status_nm',
			text : '서비스상태',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'cust_nm',
			text : '고객명',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'cust_no',
			text : '고객번호',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'service_member_nm',
			text : '담당자',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_nm',
			text : '접수자',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_dt',
			text : '접수일시',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'service_dt',
			text : '처리일시',
			width : 100,
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
    
    var comboSite = Ext.create('Ext.form.ComboBox', {
        store: siteStore,
        id: 'site',
        name: 'site',       
        flex: 1,
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code', 
        emptyText: '사이트구분',
        value: '1'
    });
    
    
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"contact_no", "name":"휴대/전화번호"},
            {"code":"cust_nm", "name":"고객명"},
            {"code":"cust_no", "name":"고객번호"},
            {"code":"service_no", "name":"서비스번호"},
            {"code":"invoice_no", "name":"송장번호"},
            {"code":"account_no", "name":"계좌번호"},
            {"code":"prd_no", "name":"제품코드"}
        ]
    });	
    
    var comboSearch = Ext.create('Ext.form.ComboBox', {
        store: searchType,
        width: 110,
        id: 'searchfield',
        name: 'searchfield',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',
        editable: false,
        emptyText: '검색조건',
        value: 'contact_no'
    });    
    
    var searchDateType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"insert_dt", "name":"접수일자"},
            {"code":"payment_dt", "name":"결제일자"},
            {"code":"repair_dt", "name":"수리일자"},
            {"code":"service_dt", "name":"처리일자"}
        ]
    });	
    
    var comboSearchDate = Ext.create('Ext.form.ComboBox', {
        store: searchDateType,
        width: 110,
        id: 'date_div',
        name: 'date_div',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',
        editable: false,
        value: 'insert_dt'
    });
    
    var comboServiceType = Ext.create('Ext.form.ComboBox', {
        store: serviceTypeStore,
        name: 'service_type',
        flex: 1, 
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '서비스구분',
        editable: false,
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
        flex: 1,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '서비스상태',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var comboPaymentType = Ext.create('Ext.form.ComboBox', {
        store: paymentTypeStore,
        name: 'payment_type',        
        flex: 1,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '결제유형',
        editable: false
    });
    
    var comboPaymentStatus = Ext.create('Ext.form.ComboBox', {
        store: paymentStatusStore,
        name: 'payment_status',
        flex: 1,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '결제상태',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var comboDeliveryStatus = Ext.create('Ext.form.ComboBox', {
        store: deliveryStatusStore,
        name: 'delivery_status',
        flex: 1,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '배송상태',
        editable: false
    });
    
    var comboPickupStatus = Ext.create('Ext.form.ComboBox', {
        store: pickupStatusStore,
        name: 'pickup_status',
        flex: 1,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '수거상태',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var comboGubun = Ext.create('Ext.form.ComboBox', {
        store: gubunStore, 
        id: 'gubun',
        name: 'gubun',
        width: 110,
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
        margin: '0 0 0 5',
        value: '1'
    });
    
        
    var searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: '5 10 0 10',
    	layout: {
            type: 'vbox',
            align: 'stretch'
        },        
	    items: [
	        {xtype:'hiddenfield', name:'gubun'}, 
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
			        comboSite,
			        {
			            xtype: 'fieldcontainer',			                        
			            defaultType: 'textfield',
			            layout: 'hbox',
			            margin: '0 0 0 10',
			           flex: 1,		            
			            items: [
							{
							    xtype: 'hiddenfield',
							    name: 'service_member_id'
							},
							{
								flex: 1,
							    name: 'service_member_nm',
							    value: '',
							    emptyText: '담당자',
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
							}]}
			        ]    
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
			        comboServiceType,
			        comboServiceStatus
			        ]    
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
			        comboPaymentType,
			        comboPaymentStatus
			        ]    
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
			        comboDeliveryStatus,
			        comboPickupStatus
			        ]    
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',			    
			    items: [comboSearchDate,
			            {
		        	xtype: 'datefield',
		        	name: 'sdate',
		        	flex: 1,
		        	margin: '0 0 0 5',
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
		        	flex: 1,
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
		        }
				        ]    
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',			    
			    items: [comboSearch,
				        {
		            flex: 1,
			        xtype: 'textfield',
			        name: 'searchquery',
			        emptyText: '검색어 입력',
			        margin: '0 0 0 5',
			        style: 'IME-MODE:ACTIVE',
			        listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        }]    
			}
		]
	});
    
    var serviceInfoSimpleList = Ext.create('Ext.panel.Panel', {
		title: '서비스조회',
	    flex: 1,
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
		    items: [comboGubun,
		            {
		    	xtype: 'tbfill'
		    }, {
			    xtype: 'button',
			    text: '검색',
			    margin: '0 0 0 3',
			    iconCls: 'icon-search',
				handler: function() {
					reload();
				}
			}, {
			    xtype: 'button',
			    text: '초기화',
			    margin: '0 0 0 3',
			    iconCls: 'icon-reset',
				handler: function() {
					reset();
				}
			}]
		},
		{
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
	        	'cellclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
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
		
		var searchfield = form.findField("searchfield");
		var searchquery = form.findField("searchquery");
		
		if(searchfield.getSubmitValue() == "contact_no") {
			searchquery.setValue(remainNumber(searchquery.getValue()));
		}
					
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '접수일자 검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		var gubunVal = Ext.getCmp("gubun").getValue();
		
		form.findField("gubun").setValue(gubunVal);
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	function reset() {
		var form = Ext.getCmp('searchForm').getForm();
		form.reset();
	}
	
	// form date
	function setFormDate(flag) {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var toDate = Ext.Date.format(new Date(),'Ymd');
		
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
	}
	
	
	prdCate1Store.getProxy().extraParams = {"site": Ext.getCmp('site').getSubmitValue()};
	prdCate1Store.load();
	

/**
 * 담당자 검색 팝업
 */
function searchMemberWin(func_name)
{
	var win = window.open(COMMON_URL + "/jsp/CRM/MemberInfoSearchPop.jsp?func_name="+func_name, "searchMember", "menubar=no, scrollbars=no, resizable=no, width=800, height=600");
}

function setServiceMemberInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	searchForm.getForm().findField("service_member_id").setValue(member_id);
	searchForm.getForm().findField("service_member_nm").setValue(member_nm);
}

/**
 * 서비스조회
 */
function serviceFormWin(service_no)
{	
	//top.insertPop();
	top.iframe.contentFrame.location.href = COMMON_URL + '/Service/ServiceInfoForm?service_no=' + service_no;
}

Ext.onReady(function() {
	
	// layout
	Ext.create('Ext.form.Panel', {
		id:'Content',
	    border: 0,
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: 'Content',
	    layout: {
	        type: 'hbox',	        
	        align: 'stretch'
	    },
	    items: [serviceInfoSimpleList]
	});
	
	if(WORK_CD == "WT003") { // 찾서		
		comboGubun.setValue("2"); // 로드샵
	} else if(WORK_CD == "WT004") { // 홈케어		
		comboGubun.setValue("2"); // 로드샵
		comboSite.setValue("4"); //홈케어
	}
});