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

Ext.onReady(function(){
	
	var url;
	var arr_prd_stock_idx = "";
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'prd_no'
            , 'prd_serial_no'
            , 'prd_nm'
			, 'prd_spec'
			, 'stock_id'
			, 'stock_nm'
			, 'stock_qty'
			, 'stock_chg_qty'
			, 'chg_type'
			, 'chg_type_nm'			
			, 'chg_remark'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdStockChgList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'prd_no',
            direction: 'ASC'
        }]
    });
    
    
    var prgChgTypeStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},           
            extraParams: {class_cd: 'CT', use_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true  
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'prd_serial_no',
			text : '자재번호',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'prd_nm',
			text : '자재명',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'prd_spec',
			text : '규격',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'stock_nm',
			text : '입고지',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'stock_qty',
			text : '현재고',
			width : 150,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'chg_type', 
			text : '보정유형',
			width : 150,
			align : 'center',
			sortable : false,
			editor: {
                xtype: 'combobox',		                
                store: prgChgTypeStore,	                
                displayField: 'code_nm',
                valueField: 'code',
                mode: 'local',
                editable: false
            },
            renderer: function(val) {
                
            	index = prgChgTypeStore.findExact('code',val);
                
                if (index != -1) {
                    rs = prgChgTypeStore.getAt(index).data; 
                    return rs.code_nm; 
                }
            }
		}, {
			dataIndex : 'stock_chg_qty',
			text : '입고수량',
			width : 150,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000'),
			editor: {
				xtype: 'numberfield',
				hideTrigger: true
			}
		}, {
			dataIndex : 'chg_remark', 
			text : '보정사유',
			width : 150,
			align : 'center',
			sortable : false,
			editor: {
				xtype: 'textfield'
			}
		}
	];
       
    var deptCodeStore = Ext.create('Ext.data.Store', {
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxDeptCdStoreCombo',
            reader: {root: 'result'},
            simpleSortMode: true
        },
        fields: [{ name: 'dept_cd' },{ name: 'dept_nm' }],
        autoLoad:true
    });
    
    // 입고지
    var comboIList = Ext.create('Ext.form.ComboBox', {
        store: deptCodeStore,
        width: 120,        
        name: 'stock_id',
        queryMode: 'local',
        displayField: 'dept_nm',
        valueField: 'dept_cd',
        editable: false,
	    padding: '0 0 0 5',
        emptyText: '입고지'
    });
    
    // 사이트
    var comboSite = Ext.create('Ext.form.ComboBox', {
        store: siteStore,
        width: 120,        
        name: 'site',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '사이트구분',
        value: '1'
    });
        
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"p.prd_serial_no", "name":"제품자재번호"},
            {"code":"p.prd_nm", "name":"제품자재명"},
            {"code":"p.prd_spec", "name":"자재SPEC"}
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
        value: 'p.prd_serial_no'
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
						fieldLabel: '조건검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
					comboSite,
					comboIList,					
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
			} // 1 row
	    ]
	});
    
    var sm = new Ext.selection.CheckboxModel({		
		name:'chkbox',	    	
	    checkOnly: true,
	    menuDisabled: true,
		sortable : false,
	    listeners: {
	    	selectionchange: function(me, selected, eOpts) {	    		
	    		arr_prd_stock_idx = "";
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			arr_prd_stock_idx += rec.data.prd_stock_idx + "|";	            	
	            });
	    	}
	    }
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
		    	text: '선택한 자재수량보정',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-yes',
		    	handler: onSave
		    }, {
		    	xtype: 'tbfill'
		    }]
		}, {
	        xtype: 'splitter'
	    }, {               
	        xtype: 'grid',
	        id: 'grid',
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
			plugins: {
				ptype: 'cellediting',
		        clicksToEdit: 1
		    }
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		var searchquery = form.findField("searchquery");
		var site = form.findField("site");
		
		if( searchquery.getValue() == ""
			&& site.getValue() == ""		
		) {
			Ext.Msg.alert('Notice', '검색조건을 하나 이상 입력해 주세요');
			return;			
		}
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	/**
	 * 자재정보 선택저장
	 */
	function onSave() {
		
		var grid = Ext.getCmp("grid").getSelectionModel();
		var selections = grid.getSelection();
		var strRecord = "";
		var isValid = true;
		
		for(i = 0; i < selections.length; i++) {
			
			var currentRecord = grid.store.getAt(selections[i].index);
			
			var prd_no = currentRecord.get("prd_no");
			var prd_serial_no = currentRecord.get("prd_serial_no");
			var prd_nm = currentRecord.get("prd_nm");
			var stock_id = currentRecord.get("stock_id");
			var chg_type = currentRecord.get("chg_type");
			var stock_chg_qty = currentRecord.get("stock_chg_qty");
			var chg_remark = currentRecord.get("chg_remark");
			
			if(chg_type == "") {
				Ext.Msg.alert('Notice', '자재 [' + prd_nm + ']의 보정유형을 선택해 주세요');
				isValid = false;
				return;
			}
			
			if(stock_chg_qty == "" || stock_chg_qty == "0") {
				Ext.Msg.alert('Notice', '자재 [' + prd_nm + ']의 입고수량을 숫자로 입력해 주세요');
				isValid = false;
				return;
			}
			
			strRecord = strRecord + prd_no + "^" + prd_serial_no + "^" + stock_id + "^" + chg_type + "^" + chg_remark + "^" + stock_chg_qty + "^" + "|";
		}
		
		if(isValid) { // save
		
			Ext.Ajax.request({
    	        url: COMMON_URL + '/ajaxPrdStockChgInsert',
    	        params: {'prdStockRecord'  : strRecord},
    	        success: function(response) {		    	    				    	    		
    	        	var obj = Ext.decode(response.responseText);		    	        	
    	        	Ext.Msg.alert('Success', obj.msg + "<br><br>전체 : " + obj.total + " / 성공 : " + obj.result);
    	        	reload();
    	        },
    	        failure: function(result, request) {
    	        	Ext.Msg.alert('Failed', "등록 중 오류가 발생하였습니다.");
    			}
    	    });
		}
		
	}

});