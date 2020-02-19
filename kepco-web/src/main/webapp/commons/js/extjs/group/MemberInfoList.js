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
        pageSize: 25,
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
			dataIndex : 'dept_cd',
			text : '부서코드',
			width : 80,
			align : 'center',
			sortable : true
		},{
			dataIndex : 'dept_nm',
			text : '부서명',
			width : 100,
			align : 'center',
			sortable : false
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
			dataIndex : 'tel_office',
			text : '직장번호',
			width : 110,
			align : 'center',
			sortable : false,
    		renderer: maskPhoneNo
		}, {
			dataIndex : 'station',
			text : '내선번호',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'email1',
			text : '이메일',
			width : 150,
			align : 'center',
			sortable : true,
			renderer : function(value, p, record) {
				if(value != "") {					
					return record.data.email1 + "@" + record.data.email2;
				}
			}
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
		}, {
			dataIndex : 'auth_nm',
			text : '권한',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'status_nm',
			text : '재직상태',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'passwd_chg_yn',
			text : '비밀번호 변경여부',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'passwd_chg_dt',
			text : '비밀번호 변경일자',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'passwd_miss_times',
			text : '비밀번호 오류횟수',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'insert_id',
			text : '등록자',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'insert_dt',
			text : '등록일시',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'update_id',
			text : '수정자',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'update_dt',
			text : '수정일시',
			width : 120,
			align : 'center',
			sortable : true
		}, 
		{
            xtype: 'actioncolumn',
            header: '비번초기화',
            width: 80,
            align:'center',
            items: [{
            		iconCls: 'icon-Sync',
            		tooltip: '비밀번호초기화',                   
            		handler: function(grid, rowIndex, colIndex) {            			
            			
            			var rec = store.getAt(rowIndex);
            			var member_id = rec.get("member_id");
            			
            			Ext.Msg.confirm('Confirm', '해당 사용자의 비밀번호를 초기화 하시겠습니까?', function(e) {
                			if(e == 'yes') {
                				
                				Ext.Ajax.request({
            		                url: COMMON_URL + '/ajaxMemberInfoPasswdInit',
            		                params: {
            		                    member_id: member_id
            		                },
            		                success: function(response){
            		                	var obj = toJson(response.responseText);
            		                	
            		                	if(obj.result > 0) {
            		                		Ext.Msg.alert('Success', '비밀번호는 아이디로 초기화 되었습니다.');
            		                		store.reload();
            		                		return;
            		                	} 	                	
            		                },
            		                failure: function(result, request) {	        							 
            							 Ext.Msg.alert('Error', '비밀번호 초기화에 실패하였습니다.');
            						}
            		            });
                				
                			} else {
                				return;
                			}
                		});    	        		
            		}
            }]
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
    
    // 권한코드
    var authCdStore = Ext.create('Ext.data.Store', {
    	id: 'authCdStore',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {class_cd: 'AT', use_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true
    });
    
    var comboAuthCd = Ext.create('Ext.form.ComboBox', {
        store: authCdStore,
        width: 120,
        name: 'auth_cd',
        queryMode: 'local',
        displayField: 'code_nm',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '권한선택'
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
        emptyText: '재직상태'
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
        width: 100,
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
    
    // 이메일
	var emailStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
	            {"code":"", "name":"직접입력"},
	            {"code":"hotmail.com", "name":"hotmail.com"},
	            {"code":"yahoo.co.kr", "name":"yahoo.co.kr"},
	            {"code":"hanmir.com", "name":"hanmir.com"},
	            {"code":"naver.com", "name":"naver.com"},
	            {"code":"empal.com", "name":"empal.com"},
	            {"code":"hitel.net", "name":"hitel.net"},
	            {"code":"kebi.com", "name":"kebi.com"},
	            {"code":"netian.com", "name":"netian.com"},
	            {"code":"nate.com", "name":"nate.com"},
	            {"code":"dreamwiz.com", "name":"dreamwiz.com"},
	            {"code":"orgio.net", "name":"orgio.net"},
	            {"code":"korea.com", "name":"korea.com"},
	            {"code":"hanmail.net", "name":"hanmail.net"},
	            {"code":"wail.co.kr", "name":"wail.co.kr"},
	            {"code":"lycos.co.kr", "name":"lycos.co.kr"},
	            {"code":"chol.com", "name":"chol.com"},
	            {"code":"intizen.com", "name":"intizen.com"},
	            {"code":"freechal.com", "name":"freechal.com"}
        ]
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
						fieldLabel: '기간검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
					{
			        	width: 120,
				        xtype: 'datefield',
				        name: 'sdate',		
				        format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        margin: '0 0 0 5',
			    		emptyText: '등록일(시작)',
			    		listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },
			        {
			        	width: 120,
				        xtype: 'datefield',
				        name: 'edate',		
				        format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        margin: '0 0 0 5',
			    		emptyText: '등록일(종료)',
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
			            text: '오늘',
			            margin: '0 0 0 5',
			        	handler: function() {
			        		setFormDate('today');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '주간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('week');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '월간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('month');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '공백',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('blank');
			        	}
			        }]
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
						fieldLabel: '부서검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
					comboDeptCd,
					comboDeptCd2
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
					comboPositionCd,
					comboWorkCd,
					comboAuthCd,
					comboStatusCd,
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
			} // 3 row
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
		    	xtype: 'tbfill'
		    },{
		    	xtype: 'button',
		    	text: '사원정보등록',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-People',
		    	handler: function(){
		    		insertPop();
		    	},
		    	disabled: authYN
		    },{
		    	xtype: 'button',
		    	text: '엑셀다운로드',
		    	align:'right',
		    	style:'text-align:right',		    	
		    	iconCls: 'icon-excel',
		    	margin: '0 0 0 5px',
		    	handler: function(){
		    		insertPop();
		    	},
		    	disabled: downYN
		    }]
		},{
	        xtype: 'splitter'
	    },		
	    {               
	        xtype: 'grid',
	        columns: columns,
	        store: store,
	        flex: 1,
	        id: 'grid',
	        name: 'grid',
	        scroll: 'horizontal',
			bbar: Ext.create('Ext.PagingToolbar', {
				pageSize: 25,
				store: store,
				displayInfo: true,
				displayMsg: '{0} - {1} of {2} 건',
				emptyMsg: "데이터가 없습니다."
			}),
			listeners: {
	        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
	        		insertPop(iRowIdx);
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
	
	
	var win = null;
    //팝업 window
    var insertPop = function(iRowIdx) {
    	
    	insertform.getForm().reset();
    	var member_id = "";
    	
    	if(!win) {
    		
	    	win = Ext.create('Ext.window.Window', {
	            title: '사원정보',
	            height: 550,
	            width: 430,
	            closeAction: 'close',
	            modal: false,
	            resizable: false,
	            draggable: true,
	            items:[
	                   insertform
	            ]
	        });
    	}
    	
    	if(win.isVisible()) {
			win.hide();
		} else {
			win.show();
			
			if(iRowIdx != undefined) {
				
				var rec = store.getAt(iRowIdx);
				
				if(rec.data.ref_dept_cd != "") {
					deptCdStore3.getProxy().extraParams = {depth: '1', dept_status:'DS001', ref_dept_cd:rec.data.ref_dept_cd};
					deptCdStore3.load();
				}
				
				insertform.getForm().loadRecord(rec);				
				// 휴대번호
				insertform.getForm().findField("tel_mobile").setValue(maskPhoneNo(rec.data.tel_mobile));
				// 전화번호
				insertform.getForm().findField("tel_home").setValue(maskPhoneNo(rec.data.tel_home));
				// 직장번호
				insertform.getForm().findField("tel_office").setValue(maskPhoneNo(rec.data.tel_office));
				
				//고객번호
				member_id = rec.data.member_id;
			}
			
			
	    	
	    	if(member_id == "") {
	    		url = COMMON_URL + '/ajaxMemberInfoInsert';
			} else {				
				insertform.getForm().findField("emode").setValue("update");
				insertform.getForm().findField("member_id").setReadOnly(true);
				Ext.getCmp("btnChkMemberId").setDisabled(true);
        		
				url = COMMON_URL + '/ajaxMemberInfoUpdate';
			}
		}
    }
    
    //팝업 form
    var insertform = Ext.create('Ext.form.Panel', {
    	id: 'insertform',
	    bodyPadding: 7,
	    flex: 1,
	    border: 0,
	    layout: 'anchor',
	    defaults: {
	        anchor: '100%'
	    },
	    defaultType: 'textfield',
	    items: [
			{
				xtype: 'hidden',
				name: 'member_id_chk',
				value:'N'
			},
			{
				xtype: 'hidden',
				name: 'emode',
				value:'insert'
			},
			{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '사원아이디',
	            defaultType: 'textfield',
	            afterLabelTextTpl: [MARK_ASTERISK],
	            items: [{
	                name: 'member_id',
	                flex: 1
	            }, {
	    	    	xtype: 'button',
	    	    	id: 'btnChkMemberId',
	    	    	text: '중복검색',
	    	    	align:'right',
	    	    	style:'text-align:right',
	    	    	iconCls: 'icon-search',
	    	    	margin: '0 0 0 5',
	    	    	handler: function() {
	    	    		
	    	    		var form = this.up('form').getForm();					
			            var member_id = form.findField("member_id");
			            
			            if (member_id.getValue() == "") {	     				
		     				focusMsgAlert('Warning', "사용자 ID를 입력해 주세요.", member_id);
		     				return;
		     			}
			            
			            Ext.Ajax.request({
			                url: COMMON_URL + '/ajaxSelectCountMemberId',
			                params: {
			                    member_id: member_id.getValue()
			                },
			                success: function(response){
			                	var obj = toJson(response.responseText);
			                	
			                	if(obj.result > 0) {
			        				focusMsgAlert('Warning', "사용중인 아이디가 있습니다.", member_id);
			        				form.findField("member_id_chk").setValue("N");
			                		return;
			                	} else {
			                		focusMsgAlert('Success', "사용 할 수 있는 아이디 입니다.");
			                		form.findField("member_id_chk").setValue("Y");
			                		return;
			                	}
			                },
			                failure: function(result, request) {
								 focusMsgAlert('Error', "ID중복체크에  실패하였습니다.", member_id);
							}
			            });
	    	    	}
	    	    }]
	        },
			{   
			    name: 'member_nm',
			    fieldLabel: '사원명',
			    afterLabelTextTpl: [MARK_ASTERISK]
			},			
			{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '부서코드',
	            defaultType: 'textfield',
	            afterLabelTextTpl: [MARK_ASTERISK],
	            items: [{
					xtype: 'combobox',
					name: 'ref_dept_cd',
					flex: 1,
				    store: deptCdStore,
			        queryMode: 'local',
			        displayField: 'dept_nm',
			        valueField: 'dept_cd',
			        editable: false,
			        listeners: {
			            select: {
			            	fn : function(combo) {
			            		
			            		var form = this.up('form').getForm();
			            		form.findField("dept_cd").clearValue();
			            		
			            		deptCdStore3.getProxy().extraParams = {depth: '1', dept_status:'DS001', ref_dept_cd:combo.lastValue};
			            		deptCdStore3.load();
			            	}
			            }
			        }
				}, {   
					xtype: 'combobox',
					name: 'dept_cd',
					flex: 1,
					margin: '0 0 0 5px',
				    store: deptCdStore3,
			        queryMode: 'local',
			        displayField: 'dept_nm',
			        valueField: 'dept_cd',
			        editable: false
				}]
	        },		
	        {   
			    name: 'tel_mobile',
			    fieldLabel: '휴대번호',
			    listeners: {
                	blur: function (t,n,o) {
                		if(t.getValue() != "") {
                		
	                		if ( !regPhone.test(t.getValue()) ) {
	                			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", t);
		          			}
		          			
		          			if ( regPhone2.test(t.getValue()) ) {
		          				focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", t);
		          			}
                		}
                	}
			    }
			},
			{   
			    name: 'tel_home',
			    fieldLabel: '전화번호',
			    listeners: {
                	blur: function (t,n,o) {
                		if(t.getValue() != "") {
	                		if ( !regPhone.test(t.getValue()) ) {
	                			focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", t);
		          			}
		          			
		          			if ( regPhone2.test(t.getValue()) ) {
		          				focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", t);
		          			}
                		}
                	}
			    }
			},
			{   
			    name: 'tel_office',
			    fieldLabel: '직장번호',
			    listeners: {
                	blur: function (t,n,o) {
                		if(t.getValue() != "") {
                		
	                		if ( !regPhone.test(t.getValue()) ) {
	                			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", t);
		          			}
		          			
		          			if ( regPhone2.test(t.getValue()) ) {
		          				focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", t);
		          			}
                		}
                	}
			    }
			},
			{   
			    name: 'station',
			    fieldLabel: '내선번호'
			},
			{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '이메일',
	            defaultType: 'textfield',
	            items: [{					
					name: 'email1',
					flex: 1				    
				}, {	
                	xtype: 'displayfield',
                	margins: '0 0 0 5',
                	value: '@'
                }, {   
					xtype: 'combobox',
					name: 'email2',
					store: emailStore,
					flex: 1,
					margin: '0 0 0 5px',
			        queryMode: 'local',
			        displayField: 'name',
			        valueField: 'code'
				}]
	        },
			{   
				xtype: 'combobox',
				name: 'position_cd',
			    fieldLabel: '직급',
			    store: positionCdStore,
		        queryMode: 'local',
		        displayField: 'code_nm',
		        valueField: 'code',
		        editable: false,
		        afterLabelTextTpl: [MARK_ASTERISK]
			},			
			{   
				xtype: 'combobox',
				name: 'work_cd',
			    fieldLabel: '업무',
			    store: workCdStore,
		        queryMode: 'local',
		        displayField: 'code_nm',
		        valueField: 'code',
		        editable: false,
		        afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
				xtype: 'combobox',
				name: 'auth_cd',
			    fieldLabel: '권한',
			    store: authCdStore,
		        queryMode: 'local',
		        displayField: 'code_nm',
		        valueField: 'code',
		        editable: false,
		        afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
				xtype: 'combobox',
				name: 'status_cd',
			    fieldLabel: '재직',
			    store: statusCdStore,
		        queryMode: 'local',
		        displayField: 'code_nm',
		        valueField: 'code',
		        editable: false,
		        afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
				xtype: 'datefield',
				name: 'office_sdate',
				format: 'Ymd',
			    fieldLabel: '입사일자',
			    afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
				xtype: 'datefield',
				name: 'office_edate',
				format: 'Ymd',
			    fieldLabel: '퇴사일자'
			},
			{   
			    xtype: 'textareafield',
				name: 'remark',
			    fieldLabel: '비고',
			    height: 50
			}
	    ],
	    buttons: [
	  	  	'<font color="red">*</font>  항목은 필수 항목입니다.',
	        '->',
	        {
	        text: '저장',
	        formBind: true, 
	        iconCls: 'icon-yes',
	        handler: function() {
	            var form = this.up('form').getForm();
	            
	            var emode = form.findField("emode").getValue();
	            
				var member_id = form.findField("member_id");
				var member_nm = form.findField("member_nm");
				var dept_cd = form.findField("dept_cd");
				var member_id_chk = form.findField("member_id_chk");
				
				var tel_mobile = form.findField("tel_mobile");
				var tel_home = form.findField("tel_home");
				var tel_office = form.findField("tel_office");
				
				var position_cd = form.findField("position_cd");
				var work_cd = form.findField("work_cd");
				var auth_cd = form.findField("auth_cd");
				var status_cd = form.findField("status_cd");
				
				var office_sdate = form.findField("office_sdate");
				var office_edate = form.findField("office_edate");
				
				if(emode == "insert") {
				
					if(trim(member_id.getValue()) == "") {					
						focusMsgAlert('Warning', '사원아이디를 입력해 주세요', member_id);
						return;
					}
					
					if(member_id_chk.getValue() == "N") {
						Ext.Msg.alert('Warning','사용자 ID 중복검색해 주세요');
						return;
					}
				
				}
				
				if(trim(member_nm.getValue()) == "") {					
					focusMsgAlert('Warning', '사원명을 입력해 주세요', member_nm);
					return;
				}
				
				if(dept_cd.getValue() == "" || dept_cd.getValue() == null) {					
					focusMsgAlert('Warning', '부서코드를 선택해 주세요', dept_cd);
					return;
				}
				
//				if(trim(tel_mobile.getValue()) == "") {					
//					focusMsgAlert('Warning', '휴대번호를 입력해 주세요', tel_mobile);
//					return;
//				}
				
				if(tel_mobile.getValue() != "") {
            		if ( !regPhone.test(tel_mobile.getValue()) ) {
            			focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_mobile);
          			}
          			
          			if ( regPhone2.test(tel_mobile.getValue()) ) {
          				focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_mobile);
          			}
        		}
				
				if(tel_home.getValue() != "") {
            		if ( !regPhone.test(tel_home.getValue()) ) {
            			focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_home);
          			}
          			
          			if ( regPhone2.test(tel_home.getValue()) ) {
          				focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_home);
          			}
        		}
				
				if(tel_office.getValue() != "") {
            		if ( !regPhone.test(tel_office.getValue()) ) {
            			focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_office);
          			}
          			
          			if ( regPhone2.test(tel_office.getValue()) ) {
          				focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_office);
          			}
        		}
				
				if(position_cd.getValue() == "" || position_cd.getValue() == null) {					
					focusMsgAlert('Warning', '직급을 선택해 주세요', position_cd);
					return;
				}
				
				if(work_cd.getValue() == "" || work_cd.getValue() == null) {					
					focusMsgAlert('Warning', '업무를 선택해 주세요', work_cd);
					return;
				}
				
				if(auth_cd.getValue() == "" || auth_cd.getValue() == null) {					
					focusMsgAlert('Warning', '권한을 선택해 주세요', auth_cd);
					return;
				}
				
				if(status_cd.getValue() == "" || status_cd.getValue() == null) {					
					focusMsgAlert('Warning', '재직상태를 선택해 주세요', status_cd);
					return;
				}
				
				if(office_sdate.getValue() == "") {					
					focusMsgAlert('Warning', '입사일자를 입력해 주세요', office_sdate);
					return;
				}
				
				if(office_edate.getValue() == "" && status_cd.getValue() == "ST002") {			
					focusMsgAlert('Warning', '퇴사일자를 입력해 주세요', office_edate);
					return;
				}
				
				tel_mobile.setValue(remainNumber(tel_mobile.getValue()));
				tel_home.setValue(remainNumber(tel_home.getValue()));
				tel_office.setValue(remainNumber(tel_office.getValue()));
				
				if(emode == "insert") {
		    		url = COMMON_URL + '/ajaxMemberInfoInsert';
				} else {
					url = COMMON_URL + '/ajaxMemberInfoUpdate';
				}	
				
	            if (form.isValid()) {
	                form.submit({
	                	url: url,
	                	submitEmptyText: false,
	                    success: function(form, action) {
	                       Ext.Msg.alert('Success', action.result.msg);
	                       reload();
	                       win.hide();
	                    },
	                    failure: function(form, action) {
	                        Ext.Msg.alert('Failed', action.result.msg);
	                        return;
	                    }
	                });
	            }
	        }
	    },
	    {
	        text: '닫기',
	        iconCls: 'icon-cancel',
	        handler: function() {
	        	win.hide();
        	}
        }]
	});
	
});