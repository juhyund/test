/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : PrdInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.11.06
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);

Ext.onReady(function() {
	
	var url;
	
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
    
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"prd_serial_no", "name":"자재번호"},
            {"code":"prd_nm", "name":"자재명"},
            {"code":"prd_spec", "name":"자재SPEC"}
        ]
    });
    
    var freeCostStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"N", "name":"AS유상"},
            {"code":"Y", "name":"AS무상"}
        ]
    });
    
    var comboPrdCate1 = Ext.create('Ext.form.ComboBox', {
        store: prdCate1Store,
        width: 130,
        id: 'prd_cate1',
        name: 'prd_cate1',
        queryMode: 'local',
        displayField: 'cate_nm',
        valueField: 'cate',        
        padding: '0 0 0 5',
        emptyText: '제품군',
        editable: false,
        listeners: {
        	change: function(combo, record, index) {                     		
        		
        		comboPrdCate2.clearValue();
        		comboPrdNo.clearValue();
        		
        		prdCate2Store.getProxy().extraParams = {"site": get_site, "prd_cate1": combo.lastValue};
        		prdCate2Store.load();
            },
            select: function() {
            	reload();
            }
        }
    });

    var comboPrdCate2 = Ext.create('Ext.form.ComboBox', {
        store: prdCate2Store,
        width: 130,   
        id: 'prd_cate2',
        name: 'prd_cate2',
        queryMode: 'local',
        displayField: 'cate_nm',
        valueField: 'cate',        
        padding: '0 0 0 5',
        emptyText: '모델군',
        editable: false,
        listeners: {
        	change: function(combo, record, index) {                     		
        	
        		comboPrdNo.clearValue();
        		
        		prdNoStore.getProxy().extraParams = {"site": get_site, "prd_cate1": Ext.getCmp("prd_cate1").getValue(), "prd_cate2": combo.lastValue};
        		prdNoStore.load();
            },
            select: function() {
            	reload();
            }
        }
    });

    var comboPrdNo = Ext.create('Ext.form.ComboBox', {
        store: prdNoStore,
        width: 150,
        id: 'prd_no',
        name: 'prd_no',
        queryMode: 'local',
        displayField: 'prd_nm',
        valueField: 'prd_no',        
        padding: '0 0 0 5',
        emptyText: '제품',
        editable: false,
        listeners: {    	
        	change: function(combo, record, index) {
        	
            },
            select: function() {
            	reload();
            }
        }
    });
    
    var comboSearch = Ext.create('Ext.form.ComboBox', {
        store: searchType,
        width: 130,
        id: 'searchfield',
        name: 'searchfield',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',
        editable: false,
        emptyText: '검색조건',
        value: 'prd_serial_no'
    });  
    
    var useYNStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"Y", "name":"사용"},
            {"code":"N", "name":"미사용"}
        ]
    });
    
    var searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: 5,
    	layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch'    // Each takes up full width
	    },
	    items: [{
			border: 0,
			layout: {
				type: 'hbox',  
				align: 'stretch',
				padding: '0 5 0 5'
			},      
			items: [	
			{
				xtype: 'hidden',
			    name: 'active'
			},
			{
				xtype: 'hidden',
			    name: 'site',
			    value: get_site
			},
			{
				xtype: 'hidden',
			    name: 'strPrdNo'
			},
			{
			    width: 16,
			    height: 16,
			    xtype: 'image',
			    margin: '0 5 0 5',
			    imgCls: 'icon-mn004'				        
			},
			{
				xtype: 'displayfield',					    
				fieldLabel: '제품검색', 
				margin: '0 5 0 5',
				labelWidth: 55
			},			
			{
				xtype: 'textfield',	
				name: 'site_nm',
				width: '130',
				labelWidth: 55,
				value: get_site_nm,
				readOnly: true
			},
			comboPrdCate1,
			comboPrdCate2,
			comboPrdNo,
			{
				xtype: 'textfield',	
				name: 'prd_nm',
				width: '130',
				labelWidth: 55,
				value: '',
				margin: '0 5 0 5',
				emptyText: '제품/자재명'
			},
			{
	            xtype: 'button',
	            iconCls: 'icon-search',
	            margin: '0 5 0 5',
	        	handler: reload
	        }
			]
		}]
	});
    
	
    // 제품 정보 검색
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
			'site'
			, 'prd_type'
			, 'prd_no'
			, 'prd_serial_no'
			, 'prd_nm'
			, 'prd_cate1'
			, 'prd_cate1_nm'
			, 'prd_cate2'
			, 'prd_cate2_nm'
			, 'prd_spec'
			, 'prd_desc'
			, 'as_price'
			, 'mat_cost'
			, 'labor_cost'
			, 'qty'
			, 'free_cost_yn'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 25,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdInfoPrdList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'a.prd_no',
            direction: 'ASC'
        }]
    });
    
    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
   			dataIndex : 'prd_type',
   			text : '구분',
   			width : 60,
   			align : 'center',
   			sortable : true,
   			renderer: getPrdTypeNm
   		}, 
   		{
			dataIndex : 'free_cost_yn', 
			text : '유무상구분',
			width : 70,
			align : 'center',
			sortable : false,
			editor: {
                xtype: 'combobox',		                
                store: freeCostStore,	                
                displayField: 'name',
                valueField: 'code',
                mode: 'local',
                editable: false,
                value: 'N'
            },
            renderer: function(val) {
                
            	index = freeCostStore.findExact('code',val);
            	
                if (index != -1){
                    rs = freeCostStore.getAt(index).data; 
                    return rs.name; 
                }
            }
		}, {
   			dataIndex : 'as_price',
   			text : '단가',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000'),
   			editor: {
				xtype: 'numberfield',
				hideTrigger: true
			}
   		}, {
   			dataIndex : 'qty',
   			text : '수량',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000'),
   			editor: {
				xtype: 'numberfield',
				hideTrigger: true
			}
   		}, {
   			dataIndex : 'prd_cate1_nm',
   			text : '제품군',
   			width : 130,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'prd_serial_no',
   			text : '제품번호',
   			width : 130,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'prd_nm',
   			text : '제품명',
   			width : 150,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'mat_cost', 
   			text : '자재비',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'labor_cost',
   			text : '공임비',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'prd_spec',
   			text : '자재SPEC',
   			width : 130,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'site',
   			text : '사이트',
   			width : 100,
   			align : 'center',
   			sortable : false,
   			renderer : getSiteNm
   		}
   	];
    
    var sm = new Ext.selection.CheckboxModel({		
		name:'chkbox',	    	
	    checkOnly: true,
	    menuDisabled: true,
		sortable : false,
	    listeners: {
	    	selectionchange: function(me, selected, eOpts) {
	    		
	    		var form = Ext.getCmp('searchForm').getForm();
	    		var arr_prd_no = "";
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			arr_prd_no += rec.data.prd_no + "|";	            	
	            });
	    		
	    		form.findField("strPrdNo").setValue(arr_prd_no);
	    	}
	    }
	});
   
    // 제품 PANEL
	var productPanel = new Ext.panel.Panel({		
		border: 0,	
		height: FRAME_CONTENT_HEIGHT - 130,
		layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
		defaults: {anchor: '100%'},
		items: [   	       
   	    { // Details Panel specified as a config object (no xtype defaults to 'panel').
		    border: 0,		    
		    layout: {
		        type: 'hbox',
		        align: 'stretch'
		    },
		    items: [{
		    	xtype: 'button',
		    	text: '선택한 제품정보 추가',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-yes',
		    	handler: function() {
		    		onInsertPRD();
		    	}
		    }, {
		    	xtype: 'tbfill'
		    }, {
		    	xtype: 'button',
		    	text: '닫기',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-cross',
		    	handler: function(){
		    		self.close();
		    	}
		    }]
		}, {
	        xtype: 'splitter'   // A splitter between the two child items
	    }, {               
	        xtype: 'grid',
	        columns: columns,
	        store: store, 
		    selModel : sm,
	        flex: 1,
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
			clicksToEdit: 1
	    }]
	});
	
	// 자재 정보 검색
    Ext.define('MatDataThread', {
        extend: 'Ext.data.Model',
        fields: [
			'site'
			, 'prd_type'
			, 'prd_mat_no'
			, 'prd_no'
			, 'prd_serial_no'
			, 'prd_nm'
			, 'prd_cate1'
			, 'prd_cate1_nm'
			, 'prd_cate2'
			, 'prd_cate2_nm'
			, 'mat_no'
			, 'mat_serial_no'
			, 'mat_nm'			
			, 'as_price'
			, 'as_cost'
			, 'mat_cost'
			, 'labor_cost'
			, 'mk_cost'
			, 'as_travel_cost'
			, 'prd_member_id'
			, 'road_prd_cost'
			, 'road_labor_cost'
			, 'road_cost'		
			, 'mat_spec'	
			, 'mat_merit'
			, 'mat_desc'
			, 'qty'
			, 'free_cost_yn'
        ]
    });
	
    matStore = Ext.create('Ext.data.Store', {
        pageSize: 25,
        model: 'MatDataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdMaterialsList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'm.prd_no',
            direction: 'ASC'
        }]
    });
    
    var matColumns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
   			dataIndex : 'prd_type',
   			text : '구분',
   			width : 60,
   			align : 'center',
   			sortable : true,
   			renderer: getPrdTypeNm
   		}, {
			dataIndex : 'free_cost_yn', 
			text : '유무상구분',
			width : 70,
			align : 'center',
			sortable : false,
			editor: {
                xtype: 'combobox',		                
                store: freeCostStore,	                
                displayField: 'name',
                valueField: 'code',
                mode: 'local',
                editable: false,
                value: 'N'
            },
            renderer: function(val) {
                
            	index = freeCostStore.findExact('code',val);
            	
                if (index != -1){
                    rs = freeCostStore.getAt(index).data; 
                    return rs.name; 
                }
            }
		}, {
   			dataIndex : 'as_price',
   			text : '단가',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000'),
   			editor: {
				xtype: 'numberfield',
				hideTrigger: true
			}
   		}, {
   			dataIndex : 'qty',
   			text : '수량',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000'),
   			editor: {
				xtype: 'numberfield',
				hideTrigger: true
			}
   		}, {
   			dataIndex : 'prd_cate1_nm',
   			text : '제품군',
   			width : 100,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'prd_nm',
   			text : '제품명',
   			width : 130,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'mat_serial_no',
   			text : '자재번호',
   			width : 130,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'mat_nm',
   			text : '자재명',
   			width : 150,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'mat_cost', 
   			text : '자재비',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'labor_cost',
   			text : '공임비',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'mat_spec',
   			text : '자재SPEC',
   			width : 130,
   			align : 'center',
   			sortable : true
   		}, {
   			dataIndex : 'site',
   			text : '사이트',
   			width : 100,
   			align : 'center',
   			sortable : false,
   			renderer : getSiteNm
   		}
   	];
    
    var matSm = new Ext.selection.CheckboxModel({		
		name:'chkbox',	    	
	    checkOnly: true,
	    menuDisabled: true,
		sortable : false,
	    listeners: {
	    	selectionchange: function(me, selected, eOpts) {
	    		
	    		var form = Ext.getCmp('searchForm').getForm();
	    		var arr_prd_no = "";
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			arr_prd_no += rec.data.prd_no + "|";	            	
	            });
	    		
	    		form.findField("strPrdNo").setValue(arr_prd_no);
	    	}
	    }
	});
    
	// 자재 PANEL
	var matPanel = new Ext.panel.Panel({		
		border: 0,	
		height: FRAME_CONTENT_HEIGHT - 130,
		layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
		defaults: {anchor: '100%'},
		items: [   	       
   	    { // Details Panel specified as a config object (no xtype defaults to 'panel').
		    border: 0,		    
		    layout: {
		        type: 'hbox',
		        align: 'stretch'
		    },
		    items: [{
		    	xtype: 'button',
		    	text: '선택한 자재정보 추가',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-yes',
		    	handler: function(){
		    		onInsertMat();
		    	}
		    }, {
		    	xtype: 'tbfill'
		    }, {
		    	xtype: 'button',
		    	text: '닫기',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-cross',
		    	handler: function(){
		    		self.close();
		    	}
		    }]
		}, {
	        xtype: 'splitter'   // A splitter between the two child items
	    }, {               
	        xtype: 'grid',
	        columns: matColumns,
	        store: matStore, 
		    selModel : matSm,
	        flex: 1,
	        id: 'matGrid',
	        name: 'matGrid',
	        scroll: 'both',
			bbar: Ext.create('Ext.PagingToolbar', {
				pageSize: 30,
				store: matStore,
				displayInfo: true,
				displayMsg: '{0} - {1} of {2} 건',
				emptyMsg: "데이터가 없습니다."
			}),
			selType: 'cellmodel',
			plugins: {
				ptype: 'cellediting',
		        clicksToEdit: 1
		    }
	    }]
	});
	
	// PANEL
	var productTabPanel = new Ext.tab.Panel({	 	
		border: 1,
		height: 150,	
		margin: '5 0 0 0',		
		height: FRAME_CONTENT_HEIGHT - 100,
		activeTab: 1,
		layout: {
	        type: 'vbox',
	        align: 'stretch'
	    },
	    items: [{
		    title: '제품정보',
		    items: [productPanel],
		    listeners: {
                activate: function(tab) {
                	var form = Ext.getCmp('searchForm').getForm();
                	form.findField("active").setValue("1");
                }
            }
		},
		{
		    title: '자재정보',
		    items: [matPanel],
		    listeners: {
                activate: function(tab) {
                	var form = Ext.getCmp('searchForm').getForm();
                	form.findField("active").setValue("2");
                }
            }
		}]
	});
	
	// layout
	Ext.create('Ext.form.Panel', {
		id:'Content',
		title: '제품/자재검색',
	    border: 0,
	    flex: 1,	    
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'vbox',	        
	        align: 'stretch',
	        padding: 5
	    },
	    items: [searchForm, productTabPanel]
	});
	
	
	// form reload
	function reload() {		
		var form = Ext.getCmp('searchForm').getForm();		
		var tab = form.findField("active").getValue();
		
		if(tab == 1) { // 제품
			store.getProxy().extraParams = form.getValues();
			store.loadPage(1);
		} else { // 자재
			matStore.getProxy().extraParams = form.getValues();
			matStore.loadPage(1);
		}	
	}
	
	function setPrdCate() {		
		
		var form = Ext.getCmp('searchForm').getForm();		
		
		// 제품군
		prdCate1Store.getProxy().extraParams = {"site": form.findField("site").getValue()};
		prdCate1Store.load({
			callback: function(records, operation, success) {				
				form.findField("prd_cate1").setValue(get_prd_cate1);
				
				// 모델군
				prdCate2Store.getProxy().extraParams = {"site": form.findField("site").getValue(), "prd_cate1": get_prd_cate1};
				prdCate2Store.load({
					callback: function(records, operation, success) {						
						form.findField("prd_cate2").setValue(get_prd_cate2);
						
						// 제품
						prdNoStore.getProxy().extraParams = {"site": form.findField("site").getValue(), "prd_cate1": get_prd_cate1, "prd_cate2": get_prd_cate2};
						prdNoStore.load({
							callback: function(records, operation, success) {							
								get_prd_no = Number(get_prd_no);
								form.findField("prd_no").setValue(get_prd_no);
								reload();
							}
						});
					}
				});
				
			}
		});
	}
	
	setPrdCate();	
	
	/**
	 * 제품정보 추가
	 */
	function onInsertPRD() {
		
		var orderStore = new Ext.data.ArrayStore({        
		    fields : ['prd_type'
		        , 'free_cost_yn'
		        , 'order_no'
	           	, 'prd_no'
	         	, 'prd_nm'
	         	, 'prd_cate1'
	         	, 'prd_cate1_nm'
	         	, 'prd_cate2'
	         	, 'prd_cate2_nm'
	         	, 'service_no'
	         	, 'price'
	         	, 'qty'
	         	, 'cost_amt']
		});
		
		orderStore.removeAll();
		
		var grid = Ext.getCmp("grid").getSelectionModel();
		var selections = grid.getSelection();
		
		var records = new Array();
		
		for(var i = 0; i < selections.length; i++) {
			
			var currentRecord = selections[i].data;
			var cost_amt = Number(currentRecord.as_price) * Number(currentRecord.qty);
			
			if(currentRecord.free_cost_yn == "Y") cost_amt = 0; // 무상AS
			
			var record = {'prd_type' : currentRecord.prd_type
				, 'free_cost_yn' : currentRecord.free_cost_yn	
				, 'order_no': ''
				, 'prd_no': currentRecord.prd_no
				, 'prd_nm': currentRecord.prd_nm.replace("'","")
				, 'prd_cate1': currentRecord.prd_cate1
				, 'prd_cate1_nm': currentRecord.prd_cate1_nm.replace("'","")
				, 'prd_cate2': currentRecord.prd_cate2
				, 'prd_cate2_nm': currentRecord.prd_cate2_nm.replace("'","")
				, 'service_no': ''
				, 'price': currentRecord.as_price
				, 'qty': currentRecord.qty
				, 'cost_amt': cost_amt
			};
			
			records.push(record);			
		}
		
		recordObj = Ext.JSON.encode(records);
		
		try {
			var _func_name = "window.opener." + func_name;
			
			var fncExec = _func_name+"('"+recordObj+"')";
	         
	        eval(fncExec);
			
			self.close();
		} catch(e) {
			
		}
	}
	
	/**
	 * 자재정보 추가
	 */
	function onInsertMat() {
		
		var orderStore = new Ext.data.ArrayStore({        
		    fields : ['prd_type'
		        , 'free_cost_yn'
		        , 'order_no'
	           	, 'prd_no'
	         	, 'prd_nm'
	         	, 'prd_cate1'
	         	, 'prd_cate1_nm'
	         	, 'prd_cate2'
	         	, 'prd_cate2_nm'
	         	, 'service_no'
	         	, 'price'
	         	, 'qty'
	         	, 'cost_amt']
		});
		
		orderStore.removeAll();
		
		var grid = Ext.getCmp("matGrid").getSelectionModel();
		var selections = grid.getSelection();
		
		var records = new Array();
		
		for(var i = 0; i < selections.length; i++) {
			
			var currentRecord = selections[i].data;
			var cost_amt = Number(currentRecord.as_price) * Number(currentRecord.qty);
			
			if(currentRecord.free_cost_yn == "Y") cost_amt = 0; // 무상AS
						
			var record = {'prd_type' : currentRecord.prd_type
				, 'free_cost_yn' : currentRecord.free_cost_yn	
				, 'order_no': ''
				, 'prd_no': currentRecord.mat_no
				, 'prd_nm': currentRecord.mat_nm.replace("'","")
				, 'prd_cate1': currentRecord.prd_cate1
				, 'prd_cate1_nm': currentRecord.prd_cate1_nm.replace("'","")
				, 'prd_cate2': currentRecord.prd_cate2
				, 'prd_cate2_nm': currentRecord.prd_cate2_nm.replace("'","")
				, 'service_no': ''
				, 'price': currentRecord.as_price
				, 'qty': currentRecord.qty
				, 'cost_amt': cost_amt
			};
			
			records.push(record);			
		}
		
		recordObj = Ext.JSON.encode(records);
		
		try {
			
			var _func_name = "window.opener." + func_name;
			
			var fncExec = _func_name+"('"+recordObj+"')";
	         
	        eval(fncExec);
			
			self.close();
			
		} catch(e) {
			alert(e);
		}
	}
	
});