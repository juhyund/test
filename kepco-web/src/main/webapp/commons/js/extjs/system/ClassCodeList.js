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
         	'class_cd'
         	, 'class_nm'         	
         	, 'class_desc'
         	, 'use_yn'         	
         	, 'insert_id'
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
            url: COMMON_URL + '/ajaxClassCodeList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'class_cd',
            direction: 'ASC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'class_cd',
			text : '분류코드',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'class_nm',
			text : '분류코드명',
			width : 130,
			align : 'center',
			sortable : true
		}, 
		{
			dataIndex : 'class_desc',
			text : '코드설명',
			flex : 1,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'use_yn',
			text : '사용여부',
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
    
    var useYNStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"Y", "name":"Y"},
            {"code":"N", "name":"N"}
        ]
    });	
   
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"class_nm", "name":"분류코드명"},
            {"code":"class_cd", "name":"분류코드"}
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
        value: 'class_nm'
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
						fieldLabel: '조건검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
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
		    	text: '분류코드등록',
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
    	
    	var class_cd = "";
    	
    	if(!win) {
    		
	    	win = Ext.create('Ext.window.Window', {
	            title: '분류코드정보',
	            height: 230,
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
				insertform.getForm().loadRecord(rec);				
				class_cd = rec.data.class_cd;
			}	    	
			
	    	if(class_cd == "") {
	    		url = COMMON_URL + '/ajaxClassCodeInsert';
			} else {
				url = COMMON_URL + '/ajaxClassCodeUpdate';
				
				insertform.getForm().findField("emode").setValue("update");
				insertform.getForm().findField("class_cd").setReadOnly(true);
				
				Ext.getCmp("btnChkClassCd").setDisabled(true);
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
				name: 'emode',
				value:'insert'
			},
			{
				xtype: 'hidden',
				name: 'class_cd_chk',
				value:'N'
			},
			{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '분류코드',
	            defaultType: 'textfield',
	            afterLabelTextTpl: [MARK_ASTERISK],
	            items: [{
	                name: 'class_cd',	                
	                flex: 1,
	                minLength: 2,
	                maxLength: 2,	                
	                style: 'IME-MODE:disabled',
	                listeners: {
	                	blur: function (t) {
	                		 t.setValue(t.getValue().toUpperCase()); 
                    	}
                    }
	            }, {
	    	    	xtype: 'button',
	    	    	id: 'btnChkClassCd',
	    	    	text: '중복검색',
	    	    	align:'right',
	    	    	style:'text-align:right',
	    	    	iconCls: 'icon-search',
	    	    	margin: '0 0 0 5',
	    	    	handler: function() {
	    	    		
	    	    		var form = this.up('form').getForm();					
			            var class_cd = form.findField("class_cd");
			            
			            if (class_cd.getValue() == "") {	     				
		     				focusMsgAlert('Warning', "분류코드를 영문대문자 2자리로 입력해 주세요.", class_cd);
		     				return;
		     			}
			            
			            Ext.Ajax.request({
			                url: COMMON_URL + '/ajaxClassCodeCount',
			                params: {
			                	class_cd: class_cd.getValue()
			                },
			                success: function(response){
			                	var obj = toJson(response.responseText);
			                	
			                	if(obj.result > 0) {
			        				focusMsgAlert('Warning', "사용중인 분류코드가 있습니다.", class_cd);
			        				form.findField("class_cd_chk").setValue("N");
			                		return;
			                	} else {
			                		focusMsgAlert('Success', "사용 할 수 있는 분류코드 입니다.");
			                		form.findField("class_cd_chk").setValue("Y");
			                		return;
			                	}
			                },
			                failure: function(result, request) {
								 focusMsgAlert('Error', "중복체크에  실패하였습니다.", class_cd);
							}
			            });
	    	    	}
	    	    }]
	        },
			{ 
			    name: 'class_nm',
			    fieldLabel: '분류코드명',
			    maxLength: 30,
			    afterLabelTextTpl: [MARK_ASTERISK]
			},			
			{   
				xtype: 'combobox',
				name: 'use_yn',
			    fieldLabel: '사용여부',
			    store: useYNStore,
		        queryMode: 'local',
		        displayField: 'name',
		        valueField: 'code',
		        editable: false,
		        value: 'Y',
		        afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
			    xtype: 'textareafield',
				name: 'class_desc',
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
	            var emode = form.findField("emode");
	            var class_cd = form.findField("class_cd");
	            var class_nm = form.findField("class_nm");
	            var class_cd_chk = form.findField("class_cd_chk");
			
				if(class_cd.getValue() == "" ) {					
					focusMsgAlert('Warning', '분류코드를 입력해 주세요', class_cd);
					return;
				}
				
				if(emode.getValue() == "insert" && class_cd_chk.getValue() == "N" ) {					
					focusMsgAlert('Warning', '사용중인 분류코드가 있습니다.', class_cd);
					return;
				}
				
				if(class_nm.getValue() == "" ) {					
					focusMsgAlert('Warning', '분류코드명을 입력해 주세요', class_nm);
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