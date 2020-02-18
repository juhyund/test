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
	
	var siteStore = Ext.create('Ext.data.Store', {
	    fields: ['code', 'name'],
	    data : [
	        {"code":"", "name":"전체"},    
	        {"code":"1", "name":"한경희생활과학"},
	        {"code":"2", "name":"리빙(뷰티)"},
	        {"code":"3", "name":"카페이탈리아"},
	        {"code":"4", "name":"홈케어"},
	        {"code":"5", "name":"브랜드대여"},
	        {"code":"6", "name":"사은품"}
	    ]
	});
	    
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
            
    searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: 10,
    	layout: {
            type: 'vbox'
        },
        fieldDefaults: {		            
    		labelAlign: 'right',    		
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
				    layout: 'hbox',
				    fieldLabel: '완료일자',
				    labelWidth: 110,
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
			        }
			        ]
				},
				{
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '제조년월',
				    labelWidth: 110,
				    width:460,
				    margin: '0 0 0 0',
				    items: [{
			        	xtype: 'datefield',
			        	name: 'm_sdate',
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
			        	name: 'm_edate',
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
			        }
			        ]
				}
				]
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
		    		xlsDownload();
		    	}
		    }]
		},{
	        xtype: 'splitter'   // A splitter between the two child items
	    },		
	    {               // Results grid specified as a config object with an xtype of 'grid'
	    	html: '<iframe name="iframe" src="/statisticsBadCd" width="100%" height='+(FRAME_CONTENT_HEIGHT-200)+'>'	    	
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var site = form.findField("site");
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
		
		var prd_cate1 = form.findField("prd_cate1");
		var prd_cate2 = form.findField("prd_cate2");
		var prd_no = form.findField("prd_no");
		var prd_nm = form.findField("prd_nm");
		
		var m_sdate = form.findField("m_sdate");
		var m_edate = form.findField("m_edate");
		
		document.form.site.value = site.getValue();
		document.form.sdate.value = sdate.getSubmitValue();
		document.form.edate.value = edate.getSubmitValue();
		document.form.m_sdate.value = m_sdate.getSubmitValue();
		document.form.m_edate.value = m_edate.getSubmitValue();
		document.form.prd_cate1.value = prd_cate1.getValue();
		document.form.prd_cate2.value = prd_cate2.getValue();
		document.form.prd_no.value = prd_no.getValue();
		document.form.prd_nm.value = prd_nm.getValue();
		
		document.form.prd_cate1_nm.value = prd_cate1.rawValue;
		document.form.prd_cate2_nm.value = prd_cate2.rawValue;
		document.form.sel_prd_nm.value = prd_no.rawValue;
			
		document.form.target = "iframe";
		document.form.action = "/statisticsBadCd";
		document.form.submit();
	}
	
	// form download
	function xlsDownload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var site = form.findField("site");
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
		
		var m_sdate = form.findField("m_sdate");
		var m_edate = form.findField("m_edate");
		
		var prd_cate1 = form.findField("prd_cate1");
		var prd_cate2 = form.findField("prd_cate2");
		var prd_no = form.findField("prd_no");
		var prd_nm = form.findField("prd_nm");
		
		document.form.site.value = site.getValue();
		document.form.sdate.value = sdate.getSubmitValue();
		document.form.edate.value = edate.getSubmitValue();
		document.form.m_sdate.value = m_sdate.getSubmitValue();
		document.form.m_edate.value = m_edate.getSubmitValue();
		document.form.prd_cate1.value = prd_cate1.getValue();
		document.form.prd_cate2.value = prd_cate2.getValue();
		document.form.prd_no.value = prd_no.getValue();
		document.form.prd_nm.value = prd_nm.getValue();
		
		document.form.prd_cate1_nm.value = prd_cate1.rawValue;
		document.form.prd_cate2_nm.value = prd_cate2.rawValue;
		document.form.sel_prd_nm.value = prd_no.rawValue;
			
		document.form.action = "/excelStatisticsBadCd";
		document.form.submit();
	}
	
	
	function reset() {
		var form = Ext.getCmp('searchForm').getForm();
		form.reset();
	}
	
	prdCate1Store.getProxy().extraParams = {"site": Ext.getCmp('site').getSubmitValue()};
	prdCate1Store.load();
	
});

