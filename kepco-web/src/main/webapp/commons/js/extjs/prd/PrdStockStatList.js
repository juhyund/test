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

	var iYear = Ext.Date.format(new Date(),'Y');
	var iMonth = Ext.Date.format(new Date(),'m');
	
	var yearStore = new Ext.data.ArrayStore({        
        fields : ['code','val']
    });
	
	var monthStore = new Ext.data.ArrayStore({        
        fields : ['code','val']
    });
	
	for(i = 0; i < 5; i++) {
		year = (iYear - i)+"";		
		yearStore.add({'code' : year, 'val' : year + '년'});
	}
	
	for(i = 0; i < 12; i++) {
		mon = i+1;
		monthStore.add({'code' : lpad(mon,2,'0'), 'val' : lpad(mon,2,'0') + '월'});
	}	
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'stock_month'
            , 'prd_no'
            , 'prd_serial_no'
			, 'prd_nm'
			, 'prd_spec'
			, 'stock_id'
			, 'stock_nm'
			, 'stock_inp_qty'
			, 'stock_inp_cancel_qty'
			, 'stock_inp_tot_qty'
			, 'stock_out_qty'
			, 'stock_out_cancel_qty'
			, 'stock_out_tot_qty'
			, 'stock_qty'
			, 'pre_stock_qty'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdStockStatList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'insert_dt',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'stock_month',
			text : '조회년월',
			width : 100,
			align : 'center',
			sortable : false
		}, 
        {
			dataIndex : 'prd_serial_no',
			text : '자재번호',
			width : 120,
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
			text : '자재SPEC',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'stock_nm',
			text : '입출고지',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'pre_stock_qty',
			text : '이전재고',
			width : 120,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
            text: "입고",
            columns: [{
            	dataIndex : 'stock_inp_qty',
                text : 'AS자재입고',    
                width : 120,
    			align : 'right',
    			sortable : false,
    			renderer: Ext.util.Format.numberRenderer('0,000')
            }, {
            	dataIndex : 'stock_inp_cancel_qty',
                text : 'AS자재회수',
                width : 120,
    			align : 'right',
    			sortable : false,
    			renderer: Ext.util.Format.numberRenderer('0,000')                
            }, {
            	dataIndex : 'stock_inp_tot_qty',
                text : '합계',
                width : 120,
    			align : 'right',
    			sortable : false,
    			renderer: Ext.util.Format.numberRenderer('0,000')
            }]
        }, {
            text: "출고",
            columns: [{
            	dataIndex : 'stock_out_qty',
                text : 'AS사용자재',
                width : 120,
    			align : 'right',
    			sortable : false,
    			renderer: Ext.util.Format.numberRenderer('0,000')
            }, {
            	dataIndex : 'stock_out_cancel_qty',
                text : '출고오류',
                width : 120,
    			align : 'right',
    			sortable : false,
    			renderer: Ext.util.Format.numberRenderer('0,000')
            }, {
            	dataIndex : 'stock_out_tot_qty',
                text : '합계',
                width : 120,
    			align : 'right',
    			sortable : false,
    			renderer: Ext.util.Format.numberRenderer('0,000')
            }]
        },  {
			dataIndex : 'stock_qty',
			text : '현재고량',
			width : 120,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
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
    
    
    // 년도
    var comboYear = Ext.create('Ext.form.ComboBox', {
    	store: yearStore,
        width: 120,        
        name: 'stock_year',
        queryMode: 'local',
        displayField: 'val',
        valueField: 'code',
        editable: false,
	    padding: '0 0 0 5',
	    value: iYear
    });
    
    // 월
    var comboMonth = Ext.create('Ext.form.ComboBox', {
        store: monthStore,
        width: 120,        
        name: 'stock_month',
        queryMode: 'local',
        displayField: 'val',
        valueField: 'code', 
        editable: false,
	    padding: '0 0 0 5',
        value: iMonth
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
        emptyText: '입출고지'
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
						fieldLabel: '조회년월', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
					comboYear,
					comboMonth
					]
	        }, // 1 row
			{
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
			} // 2 row
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
		    items: [, {
		    	xtype: 'tbfill'
		    }, {
		    	xtype: 'button',
		    	text: '엑셀다운로드',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-excel',
		    	handler: function() {
		    		download();
		    	}
		    }]
		}, {
	        xtype: 'splitter'
	    }, {               
	        xtype: 'grid',
	        columns: columns,
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
			})
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var stock_year = form.findField("stock_year");
		var stock_month = form.findField("stock_month");
		var searchquery = form.findField("searchquery");
		
		var site = form.findField("site");
//		
//		if(sdate.getSubmitValue() == "" 
//			&& edate.getSubmitValue() == "" 
//			&& searchquery.getValue() == ""
//			&& site.getValue() == ""
//		) {
//			Ext.Msg.alert('Notice', '검색조건을 하나 이상 입력해 주세요');
//			return;			
//		}
		
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	function download() {
		
		Ext.getBody().mask('파일 다운로드 중...');
		
		Ext.Ajax.request({
			url: COMMON_URL + '/ajaxExcelPrdStockStat',
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
	
	if(WORK_CD == "WT003") { //찾서
		comboIList.setDisabled(true);
		comboIList.setValue(DEPT_CD);
	}
});