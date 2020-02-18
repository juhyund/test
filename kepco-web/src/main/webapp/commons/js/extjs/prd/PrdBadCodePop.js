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
			'bad_m_cd'
			, 'bad_m_nm'
			, 'bad_cd'
			, 'bad_nm'
			, 'prd_no'
			, 'prd_serial_no'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdBadCodePop',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'bad_cd',
            direction: 'ASC'
        }]
    });
    
    
    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'bad_cd',
			text : '불량코드',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'bad_m_nm',
			text : '불량코드 대분류',
			width : 200,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'bad_nm',
			text : '불량코드 소분류',
			width : 200,
			align : 'center',
			sortable : true
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
	    		var arr_bad_cd = "";
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			arr_bad_cd += rec.data.bad_cd + "|";	            	
	            });
	    		
	    		form.findField("strBadCd").setValue(arr_bad_cd);
	    	}
	    }
	});	

    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"a.bad_nm", "name":"불량코드명"},
            {"code":"a.bad_cd", "name":"불량코드"}
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
        value: 'a.bad_nm'
    });
    
    // 불량코드 대분류
    var mBadCodeStore = Ext.create('Ext.data.Store', {
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxBadCode?site='+get_site,
            reader: {root: 'result'},
            simpleSortMode: true
        },
        fields: [{ name: 'bad_m_cd' },{ name: 'bad_m_nm' }],        
        autoLoad:true
    });
    
    var comboBadCode = Ext.create('Ext.form.ComboBox', {
        store: mBadCodeStore,
        width: 120,
        id: 'bad_m_cd',
        name: 'bad_m_cd',
        queryMode: 'local',
        displayField: 'bad_m_nm',
        valueField: 'bad_m_cd',
	    padding: '0 0 0 5',
        emptyText: '불량코드분류',
        listeners: {
        	change: function(combo, record, index) {
        		reload();
            }
        }
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
				    name: 'strBadCd'
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
				comboBadCode,
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
	    title: '제품별 불량코드 검색',
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
		    	text: '선택한 불량코드 추가',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-yes',
		    	handler: function(){
		    		onInsertBadCode();
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
			})
	    }]
	});
	
	/**
	 * 선택한 불량정보 추가
	 */
	function onInsertBadCode() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var prd_no = form.findField("prd_no").getValue();
		var strBadCd = form.findField("strBadCd").getValue();
		var result = strBadCd.split("|");
		
    	if(prd_no == "") {
    		Ext.Msg.alert("Warning", "제품번호를 선택해 주세요!");
    		return;
    	}
    	
    	if(result.length == 1) {
    		Ext.Msg.alert("Warning", "추가할 제품별 불량코드를 선택하세요!");
    		return;
    	}
    	
    	Ext.Msg.show({
		    title:'불량코드추가',
		    msg: '해당 제품의 선택된 불량코드를 추가하시겠습니까?',
		    buttons: Ext.Msg.YESNO,
		    icon: Ext.Msg.QUESTION,
		    fn: function(btn) {
		        if (btn === 'yes') {
		        	
		        	Ext.Ajax.request({
		    	        url: COMMON_URL + '/ajaxPrdBadCodeInsert',
		    	        params: { 'prd_no'	: prd_no
		    	        		, 'strBadCd'  : strBadCd
		    	        },
		    	        success: function(response) {		    	    				    	    		
		    	        	var obj = toJson(response.responseText);		    	        	
		    	        	Ext.Msg.alert('Success', obj.msg);
		    	        	reload();
		    	        	window.opener.badCodeReload();		    	        	
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
	
	reload();
});