/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : DeptInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.10.16
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer',
	'Ext.window.*',
]);

var badCodeGridStore = null;

Ext.onReady(function(){
	
	var url;
	var arr_bad_cd = "";
	var sel_prd_no = "";
	var sel_site = "";
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
			'site'
			, 'prd_no'
			, 'prd_serial_no'
			, 'prd_nm'
			, 'prd_cate1'
			, 'prd_cate1_nm'
			, 'prd_cate2'
			, 'prd_cate2_nm'
			, 'prd_spec'
			, 'prd_desc'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
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
            property: 'prd_serial_no',
            direction: 'ASC'
        }]
    });
    
    badCodeGridStore = Ext.create('Ext.data.Store', {
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdBadCodeList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        fields: [{ name: 'bad_cd' },{ name: 'prd_no' },{ name: 'prd_serial_no' },{ name: 'prd_nm' },{ name: 'bad_m_nm' },{ name: 'bad_nm' },{ name: 'site' }]
    });
    
    // 제품군
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
    
    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'site',
			text : '구분',
			width : 100,
			align : 'center',
			sortable : true,
			renderer: getSiteNm
		}, {
			dataIndex : 'prd_serial_no',
			text : '제품일련번호',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_nm',
			text : '제품명',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_cate1_nm',
			text : '제품군',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_cate2_nm',
			text : '모델군',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_spec',
			text : '제품SPEC',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_desc',
			text : '비고',
			width : 150,
			align : 'center',
			sortable : true
		}
	];
      
    var comboSite = Ext.create('Ext.form.ComboBox', {
        store: siteStore,        
        width: 120,  
        id: 'site',
        name: 'site',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '사이트구분',
        value: '1',
        listeners: {
        	change: function(combo, record, index) {                     		
        		
        		comboPrdCate1.clearValue();
        		comboPrdCate2.clearValue();
        		comboPrdNo.clearValue();
        		
        		prdCate1Store.getProxy().extraParams = {"site": combo.lastValue};
        		prdCate1Store.load();
        		
        		reload();
            }
        }
    });
    
    var comboPrdCate1 = Ext.create('Ext.form.ComboBox', {
        store: prdCate1Store,
        width: 150, 
        id: 'prd_cate1',
        name: 'prd_cate1',
        queryMode: 'local',
        displayField: 'cate_nm',
        valueField: 'cate',        
	    padding: '0 0 0 5',
        emptyText: '제품군',
        listeners: {
        	change: function(combo, record, index) {                     		
        		
        		comboPrdCate2.clearValue();
        		comboPrdNo.clearValue();
        		
        		prdCate2Store.getProxy().extraParams = {"site": Ext.getCmp("site").getValue(), "prd_cate1": combo.lastValue};
        		prdCate2Store.load();
        		
        		reload();
            }
        }
    });
    
    var comboPrdCate2 = Ext.create('Ext.form.ComboBox', {
        store: prdCate2Store,
        width: 150,    
        id: 'prd_cate2',
        name: 'prd_cate2',
        queryMode: 'local',
        displayField: 'cate_nm',
        valueField: 'cate',        
	    padding: '0 0 0 5',
        emptyText: '모델군',
        listeners: {
        	change: function(combo, record, index) {                     		
        	
        		comboPrdNo.clearValue();
        		
        		prdNoStore.getProxy().extraParams = {"site": Ext.getCmp("site").getValue(), "prd_cate1": Ext.getCmp("prd_cate1").getValue(), "prd_cate2": combo.lastValue};
        		prdNoStore.load();
        		
        		reload();
            }
        }
    });
    
    var comboPrdNo = Ext.create('Ext.form.ComboBox', {
        store: prdNoStore,
        width: 150,        
        name: 'prd_no',
        queryMode: 'local',
        displayField: 'prd_nm',
        valueField: 'prd_no',        
	    padding: '0 0 0 5',
        emptyText: '제품',
        listeners: {
        	change: function(combo, record, index) {
        		reload();
            }
        }
    });
    
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"a.prd_nm", "name":"제품명"},
            {"code":"a.prd_serial_no", "name":"제품번호"},
            {"code":"a.prd_spec", "name":"제품SPEC"},
            {"code":"a.prd_desc", "name":"비고"}
        ]
    });	
    
    var comboSearch = Ext.create('Ext.form.ComboBox', {
        store: searchType,
        width: 120,
        id: 'searchfield',
        name: 'searchfield',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',
        editable: false,
	    padding: '0 0 0 5',
        emptyText: '검색조건',
        value: 'a.prd_nm'
    });
       
    var searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: 5,
    	layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch'    // Each takes up full width
	    },
	    items: [        
		{
			border: 0,
			layout: {
				type: 'hbox',  
				align: 'stretch',
				padding: '0 5 0 5'
			},      
			items: [
			{
			    width: 16,
			    height: 16,
			    xtype: 'image',
			    margin: '0 5 0 5',
			    imgCls: 'icon-mn004'				        
			},			
			{
				xtype: 'displayfield',					    
				fieldLabel: '제품분류', 
				margin: '0 5 0 5',
				labelWidth: 55
			},		
			comboSite,
			comboPrdCate1,
			comboPrdCate2,
			comboPrdNo
			]
		}, {
			border: 0,
			layout: {
				type: 'hbox',  
				align: 'stretch',
				padding: '5 5 0 5'
			},      
			items: [
			{
			    width: 16,
			    height: 16,
			    xtype: 'image',
			    margin: '0 5 0 5',
			    imgCls: 'icon-mn004'				        
			},			
			{
				xtype: 'displayfield',					    
				fieldLabel: '조건검색', 
				margin: '0 5 0 5',
				labelWidth: 55
			},
			comboSearch,
	        {
	            width: 150,
		        xtype: 'textfield',
		        name: 'searchquery',
		        emptyText: '검색어 입력',
		        margin: '0 5 0 5',
		        style: 'IME-MODE:ACTIVE',
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
	        	handler: reload
	        }]
		}]
	});
    
    var leftForm = {
		xtype: 'panel',		
		flex: 1.5,
		minWidth: 500,
		layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [
        searchForm,
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
	        scroll: 'horizontal',
			bbar: Ext.create('Ext.PagingToolbar', {
				pageSize: 30,
				store: store,
				displayInfo: true,
				displayMsg: '{0} - {1} of {2} 건',
				emptyMsg: "데이터가 없습니다."
			}),
			listeners: {
	        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
	        		
	        		loadData(iRowIdx);
	        		
	        	}
	        }
	    }]
    } 
    
    var loadData = function(iRowIdx) {    	
		
    	insertform.getForm().reset();
    	
    	sel_prd_no = "";  
    	sel_site = "";
    	    	
    	if(iRowIdx != undefined) {
    		
			var rec = store.getAt(iRowIdx);
			
			sel_prd_no = rec.get('prd_no');  
        	sel_site = rec.get('site');
			
			insertform.getForm().loadRecord(rec);
			insertform.getForm().findField("site_nm").setValue(getSiteNm(rec.get('site')));
			
			// 코드리스트
			badCodeReload();
		}
    }
    
    //팝업 form
    var insertform = Ext.create('Ext.form.Panel', {
    	id: 'insertform',
    	title: '제품정보',
        bodyPadding: 10,	   
	    border: 1,
	    margins: '0 0 5 0',
	    defaultType: 'textfield',
	    height: 125,
	    layout: 'anchor',
	    fieldDefaults: {
	        labelWidth: 80
	    }, 
	    items: [
			{   
				xtype: 'hiddenfield',
				name: 'site'
			},
			{   
				xtype: 'hiddenfield',
				name: 'prd_no'
			},
			{   
				name: 'site_nm',
			    fieldLabel: '구분',
			    anchor: '100%'
			}, {     
				name: 'prd_serial_no',
			    fieldLabel: '제품일련번호',
			    anchor: '100%'
			}, {   
				name: 'prd_nm',
			    fieldLabel: '제품명',
			    anchor: '100%'
			}
	    ]
	});
    
    var sm = new Ext.selection.CheckboxModel({		
		name:'chkbox',	    	
	    checkOnly: true,
	    menuDisabled: true,
		sortable : false,
	    listeners: {
	    	selectionchange: function(me, selected, eOpts) {
	    		
	    		arr_bad_cd = "";
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			arr_bad_cd += rec.data.bad_cd + "|";	            	
	            });
	    	}
	    }
	});	
    
    var prdBadCodeGrid =  {
    	xtype: 'grid',
    	store: badCodeGridStore, 
    	id: 'prdBadCodeGrid',
    	layout: {
	        align: 'stretch'
	    },
	    flex: 1,
    	loadMask: true,
    	border: 1,
	   	title: '제품별 불량코드',
	   	selModel : sm,
	   	columns:  [
	   	    {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
	   	    {
				dataIndex : 'bad_cd',
				text : '불량코드',
				width : 100,
				align : 'center',
				sortable : true
			}, {
				dataIndex : 'bad_m_nm',
				text : '불량코드 대분류',
				flex : 1,
				align : 'center',
				sortable : true
			}, {
				dataIndex : 'bad_nm',
				text : '불량코드 소분류',
				flex : 1,
				align : 'center',
				sortable : true
			}
	   	],
    	tbar : [
    		{
    		    iconCls: 'icon-add',
    		    text: '불량코드추가',
    		    scope: this,
    		    handler: onInsertBadCode
    		}, {
    		    iconCls: 'icon-remove',
    		    text: '선택된 코드 삭제',
    		    itemId: 'delete',
    		    scope: this,
    		    handler: onDeleteBadCode
    		}
        ]
    }
    
    /**
     * 불량코드 등록
     */
    function onInsertBadCode() {
		
		if(sel_prd_no == "") {
			Ext.Msg.alert('Warnning', "제품을 선택해 주세요!");
		} else {						
			var theURL = COMMON_URL + '/jsp/Prd/PrdBadCodeListPop.jsp?prd_no='+sel_prd_no+"&site="+sel_site;			
			window.open(theURL, 'pop', "menubar=no, scrollbars=yes, resizable=yes, width=" + 800 + ", height=" + 600);			
		}		
	}
    
    
    /**
	 * 불량코드 선택삭제
	 */
	function onDeleteBadCode() {
		
    	var result = arr_bad_cd.split("|");
    	
    	if(sel_prd_no == "") {
    		Ext.Msg.alert("Warning", "제품구분을 선택하세요");
    		return;
    	}
    	
    	if(result.length == 1) {
    		Ext.Msg.alert("Warning", "삭제할 불량코드를 선택하세요");
    		return;
    	}
    	
    	Ext.Msg.show({
		    title:'Delete',
		    msg: '해당 제품의 선택된 불량코드를 삭제하시겠습니까?',
		    buttons: Ext.Msg.YESNO,
		    icon: Ext.Msg.QUESTION,
		    fn: function(btn) {
		        if (btn === 'yes') {
		        	
		        	Ext.Ajax.request({
		    	        url: COMMON_URL + '/ajaxPrdBadCodeDelete',
		    	        params: { 'prd_no'	: sel_prd_no
		    	        		, 'strBadCd'  : arr_bad_cd
		    	        },
		    	        success: function(response) {		    	    				    	    		
		    	        	var obj = toJson(response.responseText);		    	        	
		    	        	Ext.Msg.alert('Success', obj.msg);
		    	        	badCodeReload();
		    	        },
		    	        failure: function(result, request) {
		    	        	Ext.Msg.alert('Failed', "삭제 중 오류가 발생하였습니다.");
		    			}
		    	    });		
		        	
		        } else if (btn === 'no') {
		            return;
		        } else {
		            return;
		        } 
		    }
		});
	}	
	    
    var rightForm = {
		xtype: 'panel',
		border: 0,
		flex: 700,
		minWidth: 700,
		maxWidth: 700,
		layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch'
	    },
	    items: [insertform, prdBadCodeGrid]
    }
    
	Ext.create('Ext.panel.Panel', {
		id:'Content',
	    title: name,
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'hbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [leftForm, { xtype: 'splitter' }, rightForm]
	});
     
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
	
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);		
	}	

	function loadPrdCate1() {
		var form = Ext.getCmp('searchForm').getForm();
		prdCate1Store.getProxy().extraParams = {"site": form.findField("site").getValue()};
		prdCate1Store.load();
	}
	
	reload();	
	
	loadPrdCate1();
});


//form reload
function badCodeReload() {
	
	var form = Ext.getCmp('insertform').getForm();

	badCodeGridStore.getProxy().extraParams = form.getValues();
	badCodeGridStore.load();		
}
