/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : MemberInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.10.16
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
         	'member_id'
         	, 'ref_dept_cd'
         	, 'dept_cd'
         	, 'dept_nm'
         	, 'member_nm'
         	, 'tel_mobile'
         	, 'tel_home'
         	, 'tel_office'
         	, 'station'
         	, 'email1'
         	, 'email2'
         	, 'position_cd'
         	, 'position_nm'
         	, 'work_cd'
         	, 'work_nm'
         	, 'auth_cd'
         	, 'auth_nm'
         	, 'status_cd'
         	, 'status_nm'
         	, 'office_sdate'
         	, 'office_edate'
         	, 'service_area'
         	, 'service_area_nm'
         	, 'passwd_chg_yn'
         	, 'passwd_chg_dt'
         	, 'passwd_miss_times'
         	, 'insert_id'
         	, 'insert_nm'
         	, 'insert_dt'
         	, 'update_id'
         	, 'update_dt'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxMemberInfoList',
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
			dataIndex : 'member_id',
			text : '사원아이디',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'member_nm',
			text : '사원명',
			flex : 1,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'dept_nm',
			text : '부서명',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'position_nm',
			text : '직급',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'work_nm',
			text : '업무',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'status_nm',
			text : '재직상태',
			width : 120,
			align : 'center',
			sortable : true
		}
	];
    
    // 부서 store
    var deptCdStore = Ext.create('Ext.data.Store', {
    	id: 'deptCdStore',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxDeptCdCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {depth: '0', dept_status:'DS001'}
        },
        fields: [{ name: 'dept_cd' },{ name: 'dept_nm' }],
        autoLoad:true
    });
    
    
    var comboDeptCd = Ext.create('Ext.form.ComboBox', {
        store: deptCdStore,
        width: 120,
        name: 'ref_dept_cd',
        queryMode: 'local',
        displayField: 'dept_nm',
        valueField: 'dept_cd',        
	    padding: '0 0 0 5',
        emptyText: '본부선택',
        listeners: {
            select: {
            	fn : function(combo) {   
            		comboDeptCd2.clearValue();            		
            		deptCdStore2.getProxy().extraParams = {depth: '1', dept_status:'DS001', ref_dept_cd:combo.lastValue};
            		deptCdStore2.load();
            	}
            },
            specialkey: function (f,e) {    
                if (e.getKey() == e.ENTER) {
               	 reload();
               }
            }
        }
    });
    
    // 부서 store
    var deptCdStore2 = Ext.create('Ext.data.Store', {
    	id: 'deptCdStore2',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxDeptCdCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {depth: '1', dept_status:'DS001'}
        },
        fields: [{ name: 'dept_cd' },{ name: 'dept_nm' }],
        autoLoad:false
    });
    
    // 부서 store
    var deptCdStore3 = Ext.create('Ext.data.Store', {
    	id: 'deptCdStore3',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxDeptCdCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {depth: '1', dept_status:'DS001'}
        },
        fields: [{ name: 'dept_cd' },{ name: 'dept_nm' }],
        autoLoad:false
    });
    
    
    var comboDeptCd2 = Ext.create('Ext.form.ComboBox', {
        store: deptCdStore2,
        width: 120,
        name: 'dept_cd',
        queryMode: 'local',
        displayField: 'dept_nm',
        valueField: 'dept_cd',        
	    padding: '0 0 0 5',
        emptyText: '부서선택',
        listeners:  {
            specialkey: function (f,e) {    
                 if (e.getKey() == e.ENTER) {
                	 reload();
                }
            }
        }
    });
    
    
    // 직급코드
    var positionCdStore = Ext.create('Ext.data.Store', {
    	id: 'positionCdStore',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {class_cd: 'PT', use_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true
    });
    
    var comboPositionCd = Ext.create('Ext.form.ComboBox', {
        store: positionCdStore,
        width: 120,
        name: 'position_cd',
        queryMode: 'local',
        displayField: 'code_nm',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '직급선택'
    });
    
    // 업무코드
    var workCdStore = Ext.create('Ext.data.Store', {
    	id: 'workCdStore',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {class_cd: 'WT', use_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true
    });
    
    var comboWorkCd = Ext.create('Ext.form.ComboBox', {
        store: workCdStore,
        width: 120,
        name: 'work_cd',
        queryMode: 'local',
        displayField: 'code_nm',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '업무선택'
    });
    
    
    // 재직코드
    var statusCdStore = Ext.create('Ext.data.Store', {
    	id: 'statusCdStore',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {class_cd: 'ST', use_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true
    });
    
    var comboStatusCd = Ext.create('Ext.form.ComboBox', {
        store: statusCdStore,
        width: 120,
        name: 'status_cd',
        queryMode: 'local',
        displayField: 'code_nm',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '재직상태',
        value: 'ST001'
    });
    
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"member_nm", "name":"사원명"},
            {"code":"member_id", "name":"사원아이디"},
            {"code":"tel_mobile", "name":"휴대번호"},
            {"code":"tel_home", "name":"전화번호"},
            {"code":"tel_office", "name":"직장번호"},
            {"code":"email1", "name":"이메일"}
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
        value: 'member_nm'
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
						fieldLabel: '부서검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
					comboDeptCd,
					comboDeptCd2,
					comboPositionCd,
					comboWorkCd,					
					comboStatusCd
					]
	        }, // 2 row
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
			        comboSearch,
			        {
			            width: 212,
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
			} // 3 row
	    ]
	});
   
	Ext.create('Ext.panel.Panel', {
		id:'Content',
	    title: '담당자 검색',
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
	    {
	        xtype: 'splitter'
	    },		
	    {               
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
			}),
			listeners: {
	        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
	        		
	        		var rec = store.getAt(iRowIdx);
	        		
	        		var dept_cd = rec.get("dept_cd");
	        		var member_id = rec.get("member_id");
	        		var member_nm = rec.get("member_nm");
	        		var tel_mobile = rec.get("tel_mobile");
	        
	        		var fncExec = "window.opener." + func_name+"('"+dept_cd+"','"+member_id+"','"+member_nm+"','"+tel_mobile+"')";
            
	        		eval(fncExec);
            		
	        		self.close();
	        	}
	        }
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var searchfield = form.findField("searchfield");
		var searchquery = form.findField("searchquery");
		
		if(searchfield.getValue() == "tel_mobile" || searchfield.getValue() == "tel_home" || searchfield.getValue() == "tel_office" ) {
			searchquery.setValue(remainNumber(searchquery.getValue()));
		}
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
});