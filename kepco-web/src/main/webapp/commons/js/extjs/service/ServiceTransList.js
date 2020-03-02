/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : ServiceInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.12.23
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);

var insertform;
var searchForm;
 
Ext.onReady(function() {
	
	var url;
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'service_no'
			, 'service_type'
			, 'service_type_nm'
			, 'service_status'
			, 'service_status_nm'
			, 'prd_cate1_nm'
			, 'prd_nm'
			, 'cust_no'
			, 'cust_nm'
			, 'service_member_id'
			, 'service_member_nm'
			, 'insert_id'
			, 'insert_nm'
			, 'insert_dt'
			, 'service_dt'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxServiceTransInfoList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'service_no',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'service_no',
			text : '서비스번호',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'service_type_nm',
			text : '서비스구분',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'service_status_nm',
			text : '서비스상태',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_cate1_nm',
			text : '모델군',
			width : 200,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_nm',
			text : '제품명',
			flex : 1,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'cust_nm',
			text : '고객명',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'cust_no',
			text : '고객번호',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'service_member_nm',
			text : '담당자',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_nm',
			text : '접수자',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_dt',
			text : '접수일시',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'service_dt',
			text : '처리일시',
			width : 120,
			align : 'center',
			sortable : false
		}
	];    
    
    // 서비스구분코드
    var serviceTypeStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxServiceCodeCombo',
            reader: {root: 'result'}           
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true  
    });

    // 서비스상태코드
    var serviceStatusStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxServiceStatusCombo',
            reader: {root: 'result'}           
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }]
    });	
        
    var comboSite = Ext.create('Ext.form.ComboBox', {
        store: siteStore,
        id: 'site',
        name: 'site',
        fieldLabel: '사이트',
        width: 250,
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
        margin: '0 0 0 10',
        emptyText: '사이트구분',
        value: '1',
        listeners: {
        	change: function(combo, record, index) {
            }
        }
    });   
    
    var comboServiceType = Ext.create('Ext.form.ComboBox', {
        store: serviceTypeStore,
        name: 'service_type',
        fieldLabel: '서비스구분',
        width: 250, 
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10',
        listeners: {
        	change: function(combo, record, index) {
        		
        		comboServiceStatus.clearValue();
        		serviceStatusStore.getProxy().extraParams = {"service_cd1": combo.lastValue};
        		serviceStatusStore.load();
            }
        }
    });
    
    var comboServiceStatus = Ext.create('Ext.form.ComboBox', {
        store: serviceStatusStore,
        name: 'service_status',
        fieldLabel: '처리상태',
        width: 250, 
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var sm = new Ext.selection.CheckboxModel({		
		name:'chkbox',	    	
	    checkOnly: true,
	    menuDisabled: true,
		sortable : false,
	    listeners: {
	    	selectionchange: function(me, selected, eOpts) {
	    		
	    		var form = Ext.getCmp('searchForm').getForm();
	    		var arr_service_no = "";
	    		var cnt_service_no = 0;
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			arr_service_no += rec.data.service_no + "|";	  
	    			cnt_service_no++;
	            });
	    		
	    		form.findField("str_service_no").setValue(arr_service_no);
	    		form.findField("cnt_service_no").setValue(cnt_service_no);
	    	}
	    }
	});
        
    searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: 10,
    	layout: {
            type: 'vbox'
        },
        fieldDefaults: {		            
    		labelAlign: 'right',
    		labelWidth: 90,
    		labelSeparator: "",
    	    enableKeyEvents: true
    	},
	    items: [
	        {
	        	xtype: 'hiddenfield',
	        	name: 'str_service_no'
	        },
	        {
	        	xtype: 'hiddenfield',
	        	name: 'cnt_service_no'
	        },
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [comboSite,			    
		        {
		            xtype: 'fieldcontainer',
		            fieldLabel: '담당자',	            
		            defaultType: 'textfield',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:250,
		            items: [
		                {
						    xtype: 'hiddenfield',
						    name: 'service_member_id'
						},    
						{
							flex: 1,
						    name: 'service_member_nm',
						    value: '',
						    readOnly: true,
						    editable: false,
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
							handler: function() {
								searchMemberWin('setServiceMemberInfo');
							}
						}/*,
						{
						    xtype: 'button',
						    iconCls: 'icon-cross',
						    margin: '0 0 0 3',
							handler: function() {
								
							}
						}*/
		            ]
		        }, {
		            xtype: 'fieldcontainer',
		            fieldLabel: '접수자',	            
		            defaultType: 'textfield',
		            layout: 'hbox',
		            margin: '0 0 0 10',
		            width:250,
		            items: [
						{
						    xtype: 'hiddenfield',
						    name: 'insert_id'
						},
						{
							flex: 1,
						    name: 'insert_nm',
						    value: '',
						    readOnly: true,
						    editable: false,
						    value: '',
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
							handler: function() {
								searchMemberWin('setInsertInfo');
							}
						}/*,
						{
						    xtype: 'button',
						    iconCls: 'icon-cross',
						    margin: '0 0 0 3',
							handler: function() {
								
							}
						}*/
		            ]
		        }]
			},			
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [
			        comboServiceType,
			        comboServiceStatus,
			        {
			        	xtype: 'textfield',
			        	name: 'service_no',        	
			        	fieldLabel: '서비스번호',			        	
			        	width:250,
			            readOnly: true,
			            editable: false,            
			            margin: '0 0 0 10',
			            listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        }, {
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '접수일자',
				    width:300,
				    margin: '0 0 0 10',
				    items: [{
			        	xtype: 'datefield',
			        	name: 'sdate',
			        	width: 100,
			        	format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: getWeekDay(),
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }				        	
			        }, {
			        	xtype: 'datefield',
			        	name: 'edate',
			        	width: 100,
			            margin: '0 0 0 5',
			            format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: toDate,
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        }]
				}]
			},			
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [{
		        	xtype: 'textfield',
		        	name: 'cust_no',        	
		        	fieldLabel: '고객번호',
		        	width:250,         
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },{
		        	xtype: 'textfield',
		        	name: 'cust_nm',        	
		        	fieldLabel: '고객명',
		        	width:250,           
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },{
		        	xtype: 'textfield',
		        	name: 'contact_no',        	
		        	fieldLabel: '전화/휴대번호',
		        	width:250,            
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },{
				    xtype: 'fieldcontainer',            
				    layout: 'hbox',
				    fieldLabel: '처리일자',
				    width:300,
				    margin: '0 0 0 10',
				    items: [{
			        	xtype: 'datefield',
			        	name: 'service_sdate',
			        	width: 100,
			        	format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        }, {
			        	xtype: 'datefield',
			        	name: 'service_edate',
			        	width: 100,
			            margin: '0 0 0 5',
			            format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: '',
				        listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        }]
				}]
			}
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
		    	xtype: 'button',
		    	text: '선택한 서비스 담당자 이관',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-yes',
		    	handler: function() {
		    		
		    		if(searchForm.getForm().findField("cnt_service_no").getValue() > 0) {
		    			insertPop(searchForm.getForm().findField("str_service_no").getValue());
		    		} else {
		    			Ext.Msg.alert('Notice', '이관 할 서비스 번호를 선택해 주세요!');
		    			return;
		    		}
		    	}
		    }, {
			    xtype: 'button',
			    text: '검색',
			    margin: '0 0 0 3',
				handler: function() {
					reload();
				}
			}, {
			    xtype: 'button',
			    text: '초기화',
			    margin: '0 0 0 3',
				handler: function() {
					reset();
				}
			}, {
		    	xtype: 'tbfill'
		    }/*, {
		    	xtype: 'button',
		    	text: '엑셀다운로드',
		    	align:'right',
		    	style:'text-align:right',		    	
		    	iconCls: 'icon-excel',
		    	margin: '0 0 0 5px',
		    	handler: function(){
		    	}
		    }*/]
		},{
	        xtype: 'splitter'   // A splitter between the two child items
	    },		
	    {               
	        xtype: 'grid',
	        selModel : sm,
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
	        		var service_no = rec.data.service_no + "|"; 
	        		insertPop(service_no);
	        	}
	        }
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
		var service_sdate = form.findField("service_sdate");
		var service_edate = form.findField("service_edate");
		
		var contact_no = form.findField("contact_no");
			
		contact_no.setValue(remainNumber(contact_no.getValue()));
			
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '접수일자 검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		if((service_sdate.getSubmitValue() == "" && service_edate.getSubmitValue() != "") || 
				(service_sdate.getSubmitValue() != "" && service_edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '처리일자 검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	function reset() {
		var form = Ext.getCmp('searchForm').getForm();
		form.reset();
		
		Ext.each(store.data.items, function(rec) {			
			var grid = Ext.getCmp('grid').getSelectionModel();
			grid.deselect(rec.index, true);
		});
	}
	
	
	var win = null;
    //팝업 window
    var insertPop = function(str_service_no) {
    	
    	insertform.getForm().reset();
    	var service_no = str_service_no;
    	
    	if(!win) {
    		
	    	win = Ext.create('Ext.window.Window', {
	            title: '서비스이관',
	            height: 280,
	            width: 450,
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
			
			insertform.getForm().findField("arr_service_no").setValue(service_no);			
	    	url = COMMON_URL + '/ajaxServiceTransInsert';
		}
    }
    
    // 이관사유
	var serviceTransTypeStore = Ext.create('Ext.data.Store', {    	  
		proxy: {
	        type: 'ajax',
	        url: COMMON_URL + '/ajaxCodeCombo',
	        reader: {root: 'result'},           
	        extraParams: {class_cd: 'TR', use_yn:'Y', display_yn:'Y'}
	    },
	    fields: [{ name: 'code' },{ name: 'code_nm' }],
	    autoLoad:true  
	});
	
	
	var comboServiceTransType = Ext.create('Ext.form.ComboBox', {
		fieldLabel: '이관사유',
		afterLabelTextTpl: [MARK_ASTERISK],
	    store: serviceTransTypeStore,
	    name: 'service_trans_type',	    
	    displayField: 'code_nm',
	    valueField: 'code',
	    emptyText: '이관사유',
	    editable: false,
	    value: ''
	});
	
	
    //팝업 form
    insertform = Ext.create('Ext.form.Panel', {
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
			    name: 'service_dept_cd'
			},
			{
			    xtype: 'hiddenfield',
			    name: 'service_member_id'
			},
			{   
			    name: 'arr_service_no',
			    fieldLabel: '서비스번호',
			    afterLabelTextTpl: [MARK_ASTERISK],
			    readOnly: true,
			    editable: false
			},			
			comboServiceTransType,
			{
		        xtype: 'fieldcontainer',            
		        layout: 'hbox',         
		        defaultType: 'textfield',
		        items: [
		            {
			        	name: 'service_member_nm',
			        	fieldLabel: '담당자',
			        	afterLabelTextTpl: [MARK_ASTERISK],
			            flex:1,			            
			            readOnly: true,
			            editable: false
		        	}, {
					    xtype: 'button',
					    iconCls: 'icon-search',
					    margin: '0 0 0 3',
						handler: function() {
							searchMemberWin('setMemberInfo');
						}
					} 
		        ]
		    },
			{   
			    xtype: 'textareafield',
				name: 'service_trans_remark',
			    fieldLabel: '비고',
			    height: 80
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
	        	
				var arr_service_no = form.findField("arr_service_no");
				var service_member_nm = form.findField("service_member_nm");
				var service_trans_type = form.findField("service_trans_type");
				
				if(arr_service_no.getValue() == "") {					
					focusMsgAlert('Warning', '이관 할 서비스 번호를 선택해 주세요', arr_service_no);
					return;
				}
				
				if(service_trans_type.getSubmitValue() == "") {					
					focusMsgAlert('Warning', '이관 사유를 선택해 주세요', service_trans_type);
					return;
				}
				
				if(service_member_nm.getValue() == "") {					
					focusMsgAlert('Warning', '이관 받을 담당자를 선택해 주세요', service_member_nm);
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

function setServiceMemberInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	searchForm.getForm().findField("service_member_id").setValue(member_id);
	searchForm.getForm().findField("service_member_nm").setValue(member_nm);
}

function setInsertInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	searchForm.getForm().findField("insert_id").setValue(member_id);
	searchForm.getForm().findField("insert_nm").setValue(member_nm);
}

function setMemberInfo(dept_cd, member_id, member_nm, tel_mobile) {
	
	insertform.getForm().findField("service_member_id").setValue(member_id);
	insertform.getForm().findField("service_member_nm").setValue(member_nm);
	insertform.getForm().findField("service_dept_cd").setValue(dept_cd);
}

/**
 * 담당자 검색 팝업
 */
function searchMemberWin(func_name)
{
	var win = window.open(COMMON_URL + "/jsp/CRM/MemberInfoSearchPop.jsp?func_name="+func_name, "searchMember", "menubar=no, scrollbars=no, resizable=no, width=800, height=600");
}
/**
 * 서비스조회
 */
function serviceFormWin(service_no)
{
	var win = window.open(COMMON_URL + "/jsp/Service/ServiceInfoFormWin.jsp?service_no="+service_no, "serviceForm", "menubar=no, scrollbars=yes, resizable=yes, width=1200, height=1000");
}