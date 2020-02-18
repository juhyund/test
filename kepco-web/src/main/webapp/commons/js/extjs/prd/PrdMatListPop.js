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
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
			'prd_no'
			, 'prd_type'
			, 'prd_serial_no'
			, 'prd_nm'
			, 'as_price'
			, 'as_cost'
			, 'mat_cost'
			, 'labor_cost'
			, 'mk_cost'
			, 'as_travel_cost'
			, 'prd_member_id'
			, 'color'
			, 'sale_sdate'
			, 'sale_edate'
			, 'road_prd_cost'
			, 'road_labor_cost'
			, 'road_cost'
			, 'prd_spec'
			, 'prd_merit'
			, 'prd_desc'
			, 'site'
			, 'use_yn'
			, 'sort'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdInfoMatList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'b.prd_no',
            direction: 'ASC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'sort',
			text : '정렬',
			width : 70,
			align : 'center',
			sortable : true,
			editor: {
				xtype: 'numberfield',
				hideTrigger: true
			}
		}, 
        {
			dataIndex : 'prd_serial_no',
			text : '자재번호',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_nm',
			text : '자재명',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_spec',
			text : '자재SPEC',
			width : 150,
			align : 'center',
			sortable : true
		},{
			dataIndex : 'as_price',
			text : '단가',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
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
			dataIndex : 'as_cost',
			text : 'AS비용',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'as_travel_cost',
			text : 'AS출장비',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'road_cost',
			text : '로드단가',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'road_prd_cost',
			text : '로드자재비',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'road_labor_cost',
			text : '로드공임비',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'use_yn',
			text : '사용여부',
			width : 80,
			align : 'center',
			sortable : false
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
	    		var arr_sort = "";
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			arr_prd_no += rec.data.prd_no + "|";
	    			arr_sort += rec.data.sort + "|";
	            });	    
	    			    		
	    		form.findField("strPrdNo").setValue(arr_prd_no);
	    		form.findField("strSort").setValue(arr_sort);
	    	}
	    }
	});	

    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"prd_serial_no", "name":"자재번호"},
            {"code":"prd_nm", "name":"자재명"},
            {"code":"prd_spec", "name":"자재SPEC"}
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
				    name: 'prd_no',
				    value: get_prd_no
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
					xtype: 'hidden',
				    name: 'strSort'
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
					fieldLabel: '조건검색', 
					margin: '0 5 0 5',
					labelWidth: 55
				},			
				{
					xtype: 'textfield',	
					name: 'site_nm',
					margin: '0 0 0 0',
					labelWidth: 55,
					value: get_site_nm,
					readOnly: true
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
			} // 2 row
	    ]
	});
    
	Ext.create('Ext.panel.Panel', {
		id:'Content',
	    title: '제품별 자재검색',
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
		},{
	        xtype: 'splitter'   // A splitter between the two child items
	    },		
	    {               
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
			plugins: {
				ptype: 'cellediting',
		        clicksToEdit: 1
		    }
	    }]
	});
	
	/**
	 * 선택한 자재정보 추가
	 */
	function onInsertMat() {
		
		selectedGrid();
		
		var form = Ext.getCmp('searchForm').getForm();
		var prd_no = form.findField("prd_no").getValue();
		var strPrdNo = form.findField("strPrdNo").getValue();
		var strSort = form.findField("strSort").getValue();
		var result = strPrdNo.split("|");
		
    	if(prd_no == "") {
    		Ext.Msg.alert("Warning", "제품번호를 선택해 주세요!");
    		return;
    	}
    	
    	if(result.length == 1) {
    		Ext.Msg.alert("Warning", "추가할 자재정보를 선택하세요!");
    		return;
    	}
    	
    	Ext.Msg.show({
		    title:'제품추가',
		    msg: '해당 제품의 선택된 자재정보를 추가하시겠습니까?',
		    buttons: Ext.Msg.YESNO,
		    icon: Ext.Msg.QUESTION,
		    fn: function(btn) {
		        if (btn === 'yes') {
		        	
		        	Ext.Ajax.request({
		    	        url: COMMON_URL + '/ajaxPrdMaterialsInsert',
		    	        params: { 'prd_no'	: prd_no
		    	        		, 'strPrdNo'  : strPrdNo
		    	        		, 'strSort'  : strSort
		    	        },
		    	        success: function(response) {		    	    				    	    		
		    	        	var obj = toJson(response.responseText);		    	        	
		    	        	Ext.Msg.alert('Success', obj.msg);
		    	        	reload();
		    	        	window.opener.matReload();		    	        	
		    	        },
		    	        failure: function(result, request) {
		    	        	Ext.Msg.alert('Failed', "등록 중 오류가 발생하였습니다.");
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
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
		
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
	
	function selectedGrid() {
		
		var grid = Ext.getCmp('grid').getSelectionModel();
		var form = Ext.getCmp('searchForm').getForm();
		
		var arr_prd_no = "";
	    var arr_sort = "";
		
		Ext.each(grid.selected.items, function(rec) {
				
	    	arr_prd_no += rec.data.prd_no + "|";
	    	arr_sort += rec.data.sort + "|";	    		
		});	
		
		form.findField("strPrdNo").setValue(arr_prd_no);
	    form.findField("strSort").setValue(arr_sort);

	}
	
	reload();
});