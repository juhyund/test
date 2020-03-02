/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : winSearchMemberInfo.js
* @Author : kyunghee.yoon
* @Date : 2015.10.22
**************************************/
var searchMemberInfoWin = null;

//팝업 window
var searchMemberInfoPop = function(func_name) {
	
	Ext.define('MemberDataThread', {
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
        ]
    });
	
	var store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'MemberDataThread',
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
	
	// 부서 store
    var deptCdStore = Ext.create('Ext.data.Store', {    	        
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
        id: 'm_ref_dept_cd',
        name: 'm_ref_dept_cd',
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
                	reloadMemberInfoSearch();
               }
            }
        }
    });
    
    // 부서 store
    var deptCdStore2 = Ext.create('Ext.data.Store', {    	        
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
    	id: 'm_dept_cd',
        name: 'm_dept_cd',
        queryMode: 'local',
        displayField: 'dept_nm',
        valueField: 'dept_cd',
        emptyText: '부서선택',
        listeners:  {
            specialkey: function (f,e) {    
                 if (e.getKey() == e.ENTER) {
                	 reloadMemberInfoSearch();
                }
            }
        }
    });
    
	var memberInfoGrid = {               
        xtype: 'grid',
        title: '사원정보검색',
        columns: [
            {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
            {
      			dataIndex : 'member_id',
      			text : '사원아이디',
      			width : 100,
      			align : 'center',
      			sortable : true
      		}, {
      			dataIndex : 'member_nm',
      			text : '사원명',
      			width : 110,
      			align : 'center',
      			sortable : true
      		}, {
      			dataIndex : 'dept_nm',
      			text : '부서명',
      			width : 100,
      			align : 'center',
      			sortable : false
      		}, {
      			dataIndex : 'status_nm',
      			text : '재직상태',
      			width : 80,
      			align : 'center',
      			sortable : true
      		}, {
      			dataIndex : 'tel_mobile',
      			text : '휴대번호',
      			width : 110,
      			align : 'center',
      			sortable : false,
          		renderer: maskPhoneNo
      		}, {
      			dataIndex : 'tel_home',
      			text : '전화번호',
      			width : 110,
      			align : 'center',
      			sortable : false,
          		renderer: maskPhoneNo
      		}, {
      			dataIndex : 'position_nm',
      			text : '직급',
      			width : 80,
      			align : 'center',
      			sortable : true
      		}, {
      			dataIndex : 'work_nm',
      			text : '업무',
      			width : 80,
      			align : 'center',
      			sortable : true
      		}
      	],
      	store: store,
        flex: 1,
        height: 510,        
        name: 'memberInfoGrid',
        scroll: 'both',
        tbar : [               
				comboDeptCd, 
				comboDeptCd2,
                {
		        xtype: 'combo',
		        id: 'm_searchfield',
		        store: 
		          new Ext.data.SimpleStore({
		            fields: ['id','value'],
		            data: [["member_nm","사원명"],["member_id","사원아이디"]]
		        }), 
		        displayField: 'value',
		        valueField: 'id',
		        selectOnFocus: true,
		        mode: 'local',
		        typeAhead: true,
		        editable: false,
		        triggerAction: 'all',
		        value: 'member_nm',
		        width: 100
		      }, {
			     xtype: 'textfield',
			     id: 'm_searchquery',
			     name: 'm_searchquery',
			     listeners: {
			    	 specialkey: function(f, e) {
			    		 if(e.getKey() == e.ENTER) {
			    			 reloadMemberInfoSearch(); 
			    		 }
			    	 }
			     } 
			 },
			 {
			     xtype: 'button',
			     text: '조회',
			     tooltip: 'search',
			     handler: function() {
			    	 reloadMemberInfoSearch();
			     }
			 }
        ],
		bbar: Ext.create('Ext.PagingToolbar', {
			pageSize: 20,
			store: store,
			displayInfo: true,
			displayMsg: '{0} - {1} of {2} 건',
			emptyMsg: "데이터가 없습니다."
		}),
		listeners: {
        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
        		 var fncExec = func_name+"('"+iStore.data.member_id+"','"+iStore.data.member_nm+"','')";
                 eval(fncExec);
                 searchMemberInfoWin.close();
        	}
        }
    };
	
	var reloadMemberInfoSearch = function() {
		
		var searchfield = Ext.getCmp('m_searchfield').getValue();
		var searchquery = Ext.getCmp('m_searchquery').getValue();
		
		var ref_dept_cd = Ext.getCmp('m_ref_dept_cd').getValue();
		var dept_cd = Ext.getCmp('m_dept_cd').getValue();
		
		store.proxy.extraParams = {"searchfield":searchfield, "searchquery":searchquery, "ref_dept_cd":ref_dept_cd, "dept_cd":dept_cd};		
		store.load();
	}
	
	if(!searchMemberInfoWin) {
		
		searchMemberInfoWin = Ext.create('Ext.window.Window', {
            title: '사원정보',
            height: 550,
            width: 600,
            closeAction: 'close',
            modal: false,
            resizable: false,
            draggable: true,
            layout:{
            	layout: 'fit',
            	align:'stretch'
            },
            items:[
                   memberInfoGrid
            ]
        });
	}
	
	if(searchMemberInfoWin.isVisible()) {
		searchMemberInfoWin.hide();
	} else {
		searchMemberInfoWin.show();
	}
}