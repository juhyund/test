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
	var siteStore;
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'zip_no'
            , 'sido'
            , 'sigungu'
			, 'dong'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 200,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxSelectHappyArea',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'zip_no',
            direction: 'ASC'
        }]
    });
    
    
    var sidoStore = Ext.create('Ext.data.Store', {
    	id : 'sidoStore',  
        proxy : {
            type: 'ajax',
            url: COMMON_URL + '/ajaxSelectAreaSidoCD',
            reader: {root: 'result'}       
        },   
        fields: [{ name: 'sido' }],
        autoLoad: true
    });
    
    var sigunguStore = Ext.create('Ext.data.Store', {
    	id : 'sigunguStore',  
        proxy : {
            type: 'ajax',
            url: COMMON_URL + '/ajaxSelectAreaSigunguCD',
            reader: {root: 'result'}       
        },   
        fields: [{ name: 'sigungu' }]
    });
    

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'zip_no',
			text : '우편번호',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'sido',
			text : '시도',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'sigungu',
			text : '시군구',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'dong',
			text : '행정동',
			width : 150,
			align : 'center',
			sortable : false
		}
	];
    
    var comboSido = Ext.create('Ext.form.ComboBox', {
        store: sidoStore,
        width: 120,
        id: 'sido',
        name: 'sido',
        queryMode: 'local',
        displayField: 'sido',
        valueField: 'sido',
        editable: false,
        emptyText: '시도',
        listeners: {
        	change: function(combo, record, index) {        		
        		comboSigungu.clearValue();
        		sigunguStore.getProxy().extraParams = {"sido": combo.lastValue};
        		sigunguStore.load();
            }
        }
    });
    
    var comboSigungu = Ext.create('Ext.form.ComboBox', {
        store: sigunguStore,
        width: 120,
        id: 'sigungu',
        name: 'sigungu',
        queryMode: 'local',
        displayField: 'sigungu',
        valueField: 'sigungu',
        editable: false,
        emptyText: '시군구',
	    padding: '0 0 0 5'
    });
        
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"dong", "name":"행정동"}
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
        value: 'dong'
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
				align: 'stretch'
			},      
			items: [
		    comboSido,
		    comboSigungu,
		    comboSearch,
	        {
	            width: 150,
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
	        },		            
	        {
	            xtype: 'button',
	            iconCls: 'icon-search',
	            margin: '0 0 0 5',
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
	    		str_zip_no = "";
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			str_zip_no += rec.data.zip_no + "^";	            	
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
				xtype: 'displayfield',					    
				fieldLabel: '대리점', 
				labelWidth: 45
			},{
		    	xtype: 'textfield',
		    	name: 'agency_cd',
		    	id: 'agency_cd',		    	
		    	align:'right',		    	
		    	style:'text-align:right',
		    	width: 50,
		    	readOnly: true,
		    	editable: false,
		    	value: agency_cd
		    }, {
		    	xtype: 'textfield',
		    	name: 'agency_nm',
		    	id: 'agency_nm',
		    	align:'right',
		    	style:'text-align:right',
		    	margin: '0 0 0 5',
		    	width: 80,
		    	readOnly: true,
		    	editable: false,
		    	value: agency_nm
		    }, {
		    	xtype: 'button',
		    	text: '선택한 지역 설정',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-yes',
		    	handler: onSave,
		    	margin: '0 0 0 5'
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
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	/**
	 * 지역정보 선택저장
	 */
	function onSave() {
		
		var grid = Ext.getCmp("grid").getSelectionModel();
		var selections = grid.getSelection();
		var str_zip_no = "";
		var isValid = true;
		var agency_cd = Ext.getCmp("agency_cd").getValue();
		
		for(i = 0; i < selections.length; i++) {
			
			var currentRecord = grid.store.getAt(selections[i].index);
			
			var zip_no = currentRecord.get("zip_no");
			
			str_zip_no = str_zip_no + zip_no + "^";
		}
	
		if(isValid) { // save
			Ext.Ajax.request({
    	        url: COMMON_URL + '/ajaxHappyAreaCdUpdate',
    	        params: {'str_zip_no'  : str_zip_no, 'agency_cd':agency_cd},
    	        success: function(response) {		    	    				    	    		
    	        	var obj = Ext.decode(response.responseText);		    	        	
    	        	Ext.Msg.alert('Success', "홈케어지역지역 추가되었습니다.");
    	        	reload();
    	        },
    	        failure: function(result, request) {
    	        	Ext.Msg.alert('Failed', "등록 중 오류가 발생하였습니다.");
    			}
    	    });
		}
		
	}

});