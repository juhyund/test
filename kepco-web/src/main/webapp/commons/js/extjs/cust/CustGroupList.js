/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CustGroupList.js
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
              'group_no'
         	, 'group_nm'
         	, 'remark'
         	, 'use_yn'
         	, 'dept_cd'
         	, 'dept_nm'
         	, 'insert_id'
         	, 'insert_nm'
         	, 'insert_dt'
         	, 'update_dept_cd'
         	, 'update_dept_nm'
         	, 'update_id'
         	, 'update_nm'
         	, 'update_dt'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCustGroupList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'group_no',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'group_no',
			text : '그룹번호',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'group_nm',
			text : '그룹명',
			width : 110,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'remark',
			text : '비고',
			width : 200,
			align : 'center',
			sortable : true
		},{
			dataIndex : 'use_yn',
			text : '사용여부',
			width : 80,
			align : 'center',
			sortable : false
		},  {
			dataIndex : 'insert_nm',
			text : '등록자명',
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
			dataIndex : 'update_nm',
			text : '수정자명',
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
            {"code":"group_nm", "name":"그룹명"},
            {"code":"group_cd", "name":"그룹코드"}
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
        value: 'group_nm'
    });
    
    // 사용여부
    var useYNType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"Y", "name":"사용"},
            {"code":"N", "name":"미사용"}
        ]
    });	
    
    var comboUseYN = Ext.create('Ext.form.ComboBox', {
        store: useYNType,
        width: 120,
        name: 'use_yn',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '사용여부'
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
				        value: toDate,
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
				        value: toDate,
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
					comboUseYN,			        
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
		    	text: '그룹정보등록',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-People',
		    	handler: function(){
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
		    	}
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
		var searchquery = form.findField("searchquery");
		var use_yn = form.findField("use_yn");
		
		if(sdate.getSubmitValue() == "" 
			&& edate.getSubmitValue() == "" 
			&& searchquery.getValue() == "" 
			&& (use_yn.getValue() == undefined || use_yn.getValue() == "")) {
			Ext.Msg.alert('Notice', '검색조건을 하나 이상 입력해 주세요');
			return;
		}
		
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '기간검색은 시작일자와 종료일자 모두 입력해 주세요!');
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
	            title: '그룹정보',
	            height: 200,
	            width: 400,
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
			var group_no = "";
			if(iRowIdx != undefined) {
				var rec = store.getAt(iRowIdx);			
				insertform.getForm().loadRecord(rec);
				// 그룹번호
				group_no = rec.data.group_no;				
			}
	    	
	    	if(group_no == "") {
	    		url = COMMON_URL + '/ajaxCustGroupInsert';
			} else {				
				url = COMMON_URL + '/ajaxCustGroupUpdate';
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
			    name: 'group_no'
			},
			{   
			    name: 'group_nm',
			    fieldLabel: '그룹명',
			    afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
				xtype: 'combobox',
				name: 'use_yn',
			    fieldLabel: '사용여부',
			    store: useYNType,
		        queryMode: 'local',
		        displayField: 'name',
		        valueField: 'code',
		        editable: false,
		        value: 'Y'
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

				var group_no = form.findField("group_no");
				var group_nm = form.findField("group_nm");
				
				if(group_nm.getValue() == "") {					
					focusMsgAlert('Warning', '그룹명을 입력해 주세요', group_nm);
					return;
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