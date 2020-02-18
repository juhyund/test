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
	'Ext.grid.column.RowNumberer'
]);

Ext.onReady(function(){
	
	var url;
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
              'dept_cd'
         	, 'dept_nm'
         	, 'remark'
         	, 'dept_status'
         	, 'dept_status_nm'
         	, 'ref_dept_cd'
         	, 'ref_dept_nm'
         	, 'depth'
         	, 'sort_seq'
         	, 'insert_id'
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
            url: COMMON_URL + '/ajaxDeptInfoList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'dept_cd',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'depth',
			text : '구분',
			width : 100,
			align : 'center',
			sortable : true,
			renderer : function(data) {
				return (data == "0")?"본부":"팀";
			}
		},
        {
			dataIndex : 'dept_cd',
			text : '부서코드',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'dept_nm',
			text : '부서명',
			width : 130,
			align : 'center',
			sortable : true
		}, 
		{
			dataIndex : 'ref_dept_nm',
			text : '소속부서',
			width : 130,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'remark',
			text : '비고',
			width : 200,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'dept_status_nm',
			text : '부서상태',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'sort_seq',
			text : '정렬',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_id',
			text : '등록자',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'insert_dt',
			text : '등록일시',
			width : 150,
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
			width : 150,
			align : 'center',
			sortable : true
		}
	];

    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"dept_nm", "name":"부서명"},
            {"code":"dept_cd", "name":"부서코드"}
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
        value: 'dept_nm'
    });
    
    // 본부 store
    var refDeptCdStore = Ext.create('Ext.data.Store', {
    	id: 'deptStatusStore',        
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
    
    // 본부 combo
    var comboRefDeptCd = Ext.create('Ext.form.ComboBox', {
        store: refDeptCdStore,
        width: 130,
        name: 'ref_dept_cd',
        queryMode: 'local',
        displayField: 'dept_nm',
        valueField: 'dept_cd',        
	    padding: '0 0 0 5',
        emptyText: '본부선택'
    });
    
    // depth store
    var depthType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"0", "name":"본부"},
            {"code":"1", "name":"팀"}
        ]
    });	
    
    // depth combo
    var comboDepth = Ext.create('Ext.form.ComboBox', {
        store: depthType,
        width: 130,
        name: 'depth',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',
        editable: false,
	    padding: '0 0 0 5',
        emptyText: '구분'
    });
    

    // 상태코드
    var deptStatusStore = Ext.create('Ext.data.Store', {
    	id: 'deptStatusStore',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {class_cd: 'DS', use_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true
    });
    
    var comboDeptStatus = Ext.create('Ext.form.ComboBox', {
        store: deptStatusStore,
        width: 120,
        name: 'dept_status',
        queryMode: 'local',
        displayField: 'code_nm',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '부서상태'
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
			        	width: 130,
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
			        	width: 130,
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
						fieldLabel: '조건검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
					comboRefDeptCd,
					comboDepth,
					comboDeptStatus,			        
			        comboSearch,
			        {
			            width: 200,
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
		    items: [{
		    	xtype: 'tbfill'
		    },{
		    	xtype: 'button',
		    	text: '조직정보등록',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-People',
		    	handler: function() {
		    		insertPop();
		    	}
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
	        		insertPop(iRowIdx);
	        	}
	        }
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
		
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '조회기간을 시작일자와 종료일자 모두 입력해 주세요!');
			return;
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
    	var cust_no = "";
    	
    	if(!win) {
    		
	    	win = Ext.create('Ext.window.Window', {
	            title: '조직정보',
	            height: 300,
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
			var dept_cd = "";
			if(iRowIdx != undefined) {
				var rec = store.getAt(iRowIdx);			
				insertform.getForm().loadRecord(rec);				
				dept_cd = rec.data.dept_cd;		
				insertform.getForm().findField("depth2").setValue(rec.data.depth);
			}	    	
	    	if(dept_cd == "") {
	    		url = COMMON_URL + '/ajaxDeptInfoInsert';
	    		Ext.getCmp("radio_depth").setDisabled(false);
			} else {
				url = COMMON_URL + '/ajaxDeptInfoUpdate';
				Ext.getCmp("radio_depth").setDisabled(true);
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
			    xtype: 'hiddenfield',
			    name: 'dept_cd'
			},
			{
			    xtype: 'hiddenfield',
			    name: 'depth2'
			},
			{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',
	            margins: '0 0 0 5',
	            flex: 1,
	            id: 'radio_depth',
	            items: [{		                
	                fieldLabel: '구분',	
	                xtype: 'radiogroup',
	                labelWidth:90, 
	                width:300,
	                defaults: {
	                    name: 'depth'
	                },
	                items: [{
	                    inputValue: '0',
	                    boxLabel: '본부',
	                    width:45,
	                    checked: true
	                }, {
	                    inputValue: '1',
	                    boxLabel: '팀'
	                }],
	                listeners : {
	                	change: function(radioGroup, radio) {
	                		var form = Ext.getCmp('insertform').getForm();
	                		
	                		if(radio.depth == "1") {	                			
	                			form.findField("ref_dept_cd").setDisabled(false);
	                		} else {
	                			form.findField("ref_dept_cd").setDisabled(true);
	                		}
	                	}
	                }
	            }]
		    },
		    {   
				xtype: 'combobox',
				name: 'ref_dept_cd',
			    fieldLabel: '소속본부',
			    store: refDeptCdStore,
		        queryMode: 'local',
		        displayField: 'dept_nm',
		        valueField: 'dept_cd',
		        editable: false,
		        disabled: true
			},
			{   
			    name: 'dept_nm',
			    fieldLabel: '부서명',
			    afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
				xtype: 'combobox',
				name: 'dept_status',
			    fieldLabel: '부서상태코드',
			    store: deptStatusStore,
		        queryMode: 'local',
		        displayField: 'code_nm',
		        valueField: 'code',
		        editable: false,
		        value: 'DS001',
		        afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
			    name: 'sort_seq',
			    fieldLabel: '정렬순서',
			    afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
			    xtype: 'textareafield',
				name: 'remark',
			    fieldLabel: '비고',
			    height: 50
			},
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
	            var dept_cd = form.findField("dept_cd");
				var depth = form.findField("depth");
				var dept_nm = form.findField("dept_nm");
				var ref_dept_cd = form.findField("ref_dept_cd");
				var sort_seq = form.findField("sort_seq");
				
				if(AUTH_CD == "AT002" && depth.getGroupValue() == "0") { // 팀장
					
					focusMsgAlert('Warning', '팀장권한인 경우 팀만 등록 가능합니다.<br>구분을 \'팀\'으로 선택해 주세요', depth);
					return;
				}
				
				if(dept_nm.getValue() == "") {					
					focusMsgAlert('Warning', '조직명을 입력해 주세요', dept_nm);
					return;
				}
				
				if(depth.getGroupValue() == "1" && (ref_dept_cd.getValue() == "" || ref_dept_cd.getValue() == null)) {					
					focusMsgAlert('Warning', '소속본부를 선택해 주세요', ref_dept_cd);
					return;
				}
				
				if(sort_seq.getValue() == "" || isNaN(sort_seq.getValue())) {
					focusMsgAlert('Error','정렬순서를 숫자형식으로 입력해 주세요', sort_seq);
					return;
				}
								
				if(depth.getGroupValue() == "0") { //본부선택
					ref_dept_cd.setValue("00");
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