/*************************************
* @Copyright : (주)누리텔레콤
* @ProjectName : HaanCRM
* @FileName : DeviceInfoList.js
* @Author : kyunghee.yoon
* @Date : 2019.11.05
**************************************/
var insertform;
var searchForm;
 
Ext.onReady(function() {
	
	Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'device_id'
			, 'device_oid'
			, 'device_serial'
			, 'reg_dt'
			, 'device_type'
			, 'device_type_nm'
			, 'type_code'
			, 'type_code_nm'
			, 'area_code'
			, 'area_code_nm'
			, 'device_ip'
			, 'device_port'
			, 'class_code'
			, 'class_code_nm'
			, 'energy_type_code'
			, 'energy_type_code_nm'
			, 'meter_unit_code'
			, 'meter_unit_code_nm'
			, 'phase_div'
			, 'phase_div_nm'
			, 'prog_id'
			, 'prog_version'
			, 'latitude'
			, 'hardness'
			, 'altitude'
			, 'vendor_code'
			, 'vendor_code_nm'
			, 'prod_dt'
			, 'model_code'
			, 'model_code_nm'
			, 'device_code'
			, 'device_code_nm'
			, 'device_stat'
			, 'device_stat_nm'
			, 'last_comm_dt'
			
        ]
    });
	
	// 미터타입코드 store
    var meterTypeCodeStore = Ext.create('Ext.data.Store', {
    	id: 'meterTypeCodeStore',        
    	proxy: {
            type: 'ajax',
            url: CONTEXT_PATH + '/ajaxCodeCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {code_id: 'MT'}
        },
        fields: [{ name: 'dcode_id' },{ name: 'dcode_name' }],
        autoLoad:true
    });
    
	// 미터타입
    var comboTypeCode = Ext.create('Ext.form.ComboBox', {
        store: meterTypeCodeStore,
        flex: 1,
        name: 'type_code',
        queryMode: 'local',
        displayField: 'dcode_name',
        valueField: 'dcode_id',
        emptyText: '미터타입선택'
    });
    
    // 제조사 store
    var vendorCodeStore = Ext.create('Ext.data.Store', {
    	id: 'vendorCodeStore',        
    	proxy: {
            type: 'ajax',
            url: CONTEXT_PATH + '/ajaxCodeCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {code_id: 'VD'}
        },
        fields: [{ name: 'dcode_id' },{ name: 'dcode_name' }],
        autoLoad:true
    });
    
	// 제조사 코드
    var comboVendorCode = Ext.create('Ext.form.ComboBox', {
        store: vendorCodeStore,
        flex: 1,
        name: 'vendor_code',
        queryMode: 'local',
        displayField: 'dcode_name',
        valueField: 'dcode_id',
        emptyText: '제조사선택'
    });
	
	var store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: CONTEXT_PATH + '/ajaxDeviceInfoList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'device_id',
            direction: 'DESC'
        }]
    });
	
	var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'device_id',
			text : '아이디',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'device_serial',
			text : '단말번호',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'device_oid',
			text : '단말OID',
			width : 250,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'device_code_nm',
			text : '단말구분',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'device_stat_nm',
			text : '단말상태',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'last_comm_dt',
			text : '최종통신일자',
			width : 200,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'device_ip',
			text : '아이피',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'device_port',
			text : 'PORT',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'vendor_code_nm',
			text : '제조사명',
			width : 120,
			align : 'center',
			sortable : false
		}
	];
	
	var searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: 10,
    	width: '100%',
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
			    items: [			    
		        {
		            xtype: 'fieldcontainer',
		            fieldLabel: '단말아이디',	            
		            defaultType: 'textfield',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:300,
		            items: [		               
						{
							flex: 1,
						    name: 'device_id',
						    value: '',						    
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
		            fieldLabel: '단말시리얼',	            
		            defaultType: 'textfield',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:300,
		            items: [						
						{
							flex: 1,
						    name: 'device_serial',
						    value: '',
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
		            fieldLabel: '단말OID',	            
		            defaultType: 'textfield',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:300,
		            items: [						
						{
							flex: 1,
						    name: 'device_oid',
						    value: '',
							listeners:  {
						        specialkey: function (f,e) {    
						             if (e.getKey() == e.ENTER) {
						            	 reload();
						            }
						        }
						    }
						}
		            ]
		        }]
			},			
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
			    	{
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '최종통신일자',
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
				},
				{
		            xtype: 'fieldcontainer',
		            fieldLabel: '미터타입',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:300,
		            items: [		               
		            	comboTypeCode
		            ]
		        },
				{
		            xtype: 'fieldcontainer',
		            fieldLabel: '제조사',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:300,
		            items: [		               
		            	comboVendorCode
		            ]
		        }
				
				]
			}
	    ]
	});
	
	var renderDiv = Ext.get('Content');
	
	var panel = Ext.create('Ext.panel.Panel', {
		id:'Content',
	    flex: 1,
	    height: 600,
	    layout: 'fit',
        autoWidth:true,
	    renderTo: renderDiv,
	    layout: {
	        type: 'vbox',       // Arrange child items vertically	        
	        padding: 5
	    },
	    items:  [
	    	searchForm,
	    	{ 
			    bodyPadding: 5,
			    padding: '5 0 0 0',
			    width: '100%',
			    layout: {
			        type: 'hbox',
			        align: 'stretch'
			    },
			    items: [ {
				    xtype: 'button',
				    text: '검색',
				    iconCls: 'fa fa-search',
				    margin: '0 0 0 0',
					handler: function() {
						reload();
					}
				}, {
				    xtype: 'button',
				    text: '초기화',
				    iconCls: 'fa fa-undo',
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
			    	iconCls: 'fa fa-download',
			    	margin: '0 0 0 5px',
			    	handler: function() {
			    		download();
			    	}
			    }]
			},
	    	{
		        xtype: 'splitter'   // A splitter between the two child items
		    },
	    	{               
	        xtype: 'grid',	        
	        columns: columns,
	        width: '100%',
	        store: store, 
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
			listeners: {
	        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {	        		
	        	}
	        }
	    }]
	});
	
	
	// form reload
	function reload() {		
		var form = Ext.getCmp('searchForm').getForm();		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	// form reset
	function reset() {
		var form = Ext.getCmp('searchForm').getForm();
		form.reset();
	}
	
	// excel download
	function download() {
		
		Ext.getBody().mask('파일 다운로드 중...');
		
		Ext.Ajax.request({
			url: CONTEXT_PATH + '/ajaxExcelDeviceInfoList',
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
	
	// onResize
	Ext.EventManager.onWindowResize(function () {		
		var height = renderDiv.getHeight();
        var width = renderDiv.getWidth();
        panel.setSize(width, height);
    });
});