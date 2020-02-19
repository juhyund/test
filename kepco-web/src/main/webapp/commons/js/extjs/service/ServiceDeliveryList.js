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

var searchForm;
var insertform2;

Ext.onReady(function() {
	
	var url;
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'service_no'
			, 'delivery_no'
			, 'delivery_type'
			, 'service_type'
			, 'service_type_nm'
			, 'service_status'
			, 'service_status_nm'
			, 'payment_status'
			, 'payment_status_nm'
			, 'free_cost_yn'
			, 'cust_no'
			, 'cust_nm'
			, 'delivery_status'
			, 'delivery_status_nm'
			, 'delivery_agency'
			, 'delivery_agency_nm'
			, 'invoice_no'
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
            url: COMMON_URL + '/ajaxServiceDeliveryList',
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
        { 	xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'service_no',
			text : '서비스번호',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'delivery_no',
			text : '배송번호',
			width : 100,
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
			dataIndex : 'delivery_status_nm',
			text : '배송상태',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'payment_status_nm',
			text : '결제상태',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'delivery_agency_nm',
			text : '택배사',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'invoice_no',
			text : '송장번호',
			width : 120,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'free_cost_yn', 
			text : '유/무상',
			width : 120,
			align : 'center',
			sortable : false,
			renderer: function(dat) {
				if(dat == "Y") {
					return "무상";
				} else {
					return "유상";
				}
			}
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
    
    // 결제상태
    var paymentStatusStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            extraParams: {class_cd: 'PM', use_yn:'Y', display_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true  
    });
    
    // 배송상태
    var deliveryStatusStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            extraParams: {class_cd: 'DL', use_yn:'Y', display_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true  
    });
    
    
    // 배송업체
    var deliveryAgencyStore = Ext.create('Ext.data.Store', {    	  
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCodeCombo',
            reader: {root: 'result'},
            extraParams: {class_cd: 'DP', use_yn:'Y', display_yn:'Y'}
        },
        fields: [{ name: 'code' },{ name: 'code_nm' }],
        autoLoad:true  
    });
    
    // 주문구분
	var deliveryFlagStore = Ext.create('Ext.data.ArrayStore', {
	    fields: [{ name: 'code' },{ name: 'code_nm' }],
	    data: [['1','일반'],['2', '교환']]
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
    
    var comboPaymentStatus = Ext.create('Ext.form.ComboBox', {
        store: paymentStatusStore,
        name: 'payment_status', 
        fieldLabel: '결제상태',
        width: 250,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var comboDeliveryAgency = Ext.create('Ext.form.ComboBox', {
        store: deliveryAgencyStore,
        name: 'delivery_agency',
        width: 100,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 5'
    });
    
    var comboDeliveryStatus = Ext.create('Ext.form.ComboBox', {
        store: deliveryStatusStore,
        name: 'delivery_status', 
        fieldLabel: '배송상태',
        width: 250,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
    });
    
    var freeCostYNStore = Ext.create('Ext.data.Store', {
	    fields: ['code', 'name'],
	    data : [
	        {"code":"", "name":"전체"},
	        {"code":"Y", "name":"무상"},
	        {"code":"N", "name":"유상"}
	    ]
	});
    
    var comboFreeCostYN = Ext.create('Ext.form.ComboBox', {
        store: freeCostYNStore,
        name: 'free_cost_yn', 
        fieldLabel: '유무상/택배',
        width: 195,
        displayField: 'name',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10'
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
						    name: 'delivery_type',
						    value : '1'
						},
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
			},
			{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    items: [{
		        	xtype: 'textfield',
		        	name: 'invoice_no',        	
		        	fieldLabel: '송장번호',
		        	width:250,         
		            margin: '0 0 0 10',
		            listeners:  {
		                specialkey: function (f,e) {    
		                     if (e.getKey() == e.ENTER) {
		                    	 reload();
		                    }
		                }
		            }
		        },
		        	comboDeliveryStatus,
		        	comboPaymentStatus,
		        	comboFreeCostYN,
		        	comboDeliveryAgency
				]
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
		    }, {
			    xtype: 'button',
			    text: '송장번호 일괄등록',
			    iconCls: 'icon-yes',
			    margin: '0 0 0 3',
				handler: function() {
					insertPop();
				}
			}, {
		    	xtype: 'button',
		    	text: '엑셀다운로드',
		    	align:'right',
		    	style:'text-align:right',		    	
		    	iconCls: 'icon-excel',
		    	margin: '0 0 0 5px',
		    	handler: function(){
		    		download();
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
				
	        		var service_no = rec.data.service_no;
	        		var delivery_no = rec.data.delivery_no;
	        		var cust_nm = rec.data.cust_nm;
	        		var insert_dt = rec.data.insert_dt;
				
	        		winServiceDeliveryPop(service_no, delivery_no, cust_nm, insert_dt);
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
	}
	
	
	var win = null;
    //팝업 window
    var insertPop = function(iRowIdx) {
    	
    	insertform.getForm().reset();
    	
    	if(!win) {
    		
	    	win = Ext.create('Ext.window.Window', {
	            title: '송장번호 일괄등록',
	            height: 350,
	            width: 500,
	            closeAction: 'close',
	            modal: false,
	            resizable: false,
	            draggable: true,
	            items:[insertform]
	        });
    	}
    	
    	if(win.isVisible()) {
			win.hide();
		} else {
			win.show();
		}
    }
    
    var fileListeners = {
    	"change" : function(me, value, eOpts) {	            		
    		var ext = value.slice(value.indexOf(".") + 1).toLowerCase().trim();    		
    		var extFormat = /(xls)/;
    		if(!extFormat.test(ext))
            {
    			Ext.Msg.alert('Warning', '허용된 확장자가 아닙니다.\n파일을 다시 선택하여 주십시오');
    			me.reset();
    			return;
    		}	
    	}
	};
    
    var html = '<div style="line-height:19px;">'; 
	html += '<ol start="1"><li> 엑셀업로드 양식을 다운로드 하여 형식에 맞게 기재합니다.</li>';
	html += '<li> 파일찾기 버튼을 클릭하여 <u><font color="#FF0000">업로드 할 파일(.xls, 확장자 유의)</font></u>을 선택하고</li>';
	html += '<li> [업로드]버튼을 클릭하여 <u>데이터 업로드</u>를 시작합니다.</li>';
	html += '<li> 데이터 업로드가 완료되면 업로드 결과를 확인합니다.</li>';
	html += '<li><font color="#FF0000">업로드 중 오류가 있는 경우 오류파일을 다운로드 하여 수정 후 다시 업로드 합니다.</font></li>';
	html += '</ol></div>';
	
    //팝업 form
    var insertform = Ext.create('Ext.form.Panel', {
    	id: 'insertform',    	
	    bodyPadding: 10,
	    flex: 1,
	    border: 0,
	    layout: 'anchor',
	    fieldDefaults: {		            
	    	labelAlign: 'center',            
            labelWidth: 80,
            labelSeparator: "",
            enableKeyEvents: true,
            anchor: '100%'
        },
	    height: 300,
	    items: [{
	        xtype:'fieldset',
	        bodyPadding: 5,
	        title: '업로드 주의사항',
	        defaults: {anchor: '100%'},
	        layout: 'anchor',
	        items :[{'html' : html, border: 0}]
	    }, {
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            flex: 1,
            padding: '20 0 0 0',
            items: [{		                
                fieldLabel: '택배사선택',	
                xtype: 'radiogroup',    
                width: 250,
                defaults: {
                    name: 'delivery_agency'
                },
                items: [{
                    inputValue: 'DP001',
                    boxLabel: 'CJ택배',
                    checked: true
                }, {
                    inputValue: 'DP003',
                    boxLabel: '한진택배'
                }]
            }]		   
	    }, {
			xtype: 'fileuploadfield',			
            name: 'filename',		 
            fieldLabel: '파일업로드',
            flex: 1,        	
        	buttonText: '송장번호 파일찾기',
        	buttonConfig: {
                iconCls: 'icon-upload'
            },
            listeners: fileListeners
	    }],
	    buttons: [
		{
		    text: '송장번호 입력양식 다운로드',
		    iconCls: 'icon-excel',
		    handler: function() {
		    	location.href = COMMON_URL + "/common/templates/송장번호_등록양식.xls"
			}
		},
        '->',	        
        {
	        text: '업로드',
	        formBind: true, 
	        iconCls: 'icon-yes',
	        handler: function() {
	        	
	        	var form = this.up('form').getForm();
	        	
	        	if (form.isValid()) {
	        		
	                form.submit({
                        url: COMMON_URL + '/ajaxFileUpload?savePath=INVOICE',
                        submitEmptyText: false,
	                    success: function(form, action) {
	                    	
	                    	Ext.getBody().mask('송장번호 등록 중 입니다.');
	                    	
	                    	Ext.Ajax.request({
	                    		url: COMMON_URL + '/ajaxInvoiceExcelUpload',
	                    		success: function(result, request) {
	                    			Ext.getBody().unmask();        							 
	                    			var obj = Ext.decode(result.responseText);        							 
	                    			var msg = '송장번호 업로드가 완료 되었습니다.<br><br> - 전체 : ' + obj.total + '건<br> - 성공 : ' + obj.success + '건<br> - 오류 : ' + obj.error + '건<br>';
 
	                    			Ext.Msg.alert('Success', msg, function(btn, text) {
	                    				if (btn == 'ok') {
	                    					if(obj.error > 0) {
	                    						location.href = COMMON_URL + "/common/FileDown.jsp?fileName="+obj.errFileName+"&fileDir="+obj.errFilePath
	                    					}
	                    					
	                    					reload();
	                    				}
	                    			});
	                    		},
	                    		failure: function(result, request) {
	                    			Ext.getBody().unmask();        							 
	                    			Ext.Msg.alert('Error', '송장정보 업로드 중 오류가 발생하였습니다.');	        							 
	                    		},
	                    		params: {
	                    			'filename':action.result.fileName,
	                    			'filepath':action.result.filePath,
	                    			'delivery_agency':insertform.getForm().findField("delivery_agency").getGroupValue()
	                    		},
	                    		timeout: TIMEOUT_SEC
	                    	});
	                    },
	                    failure: function(form, action) {	
	                    	Ext.getBody().unmask();
	                        Ext.Msg.alert('Failed', action.result.msg);
	                        return;
	                    },
	                    timeout: TIMEOUT_SEC
	                });
	            } // form check
	        } // handle
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

function setZipcode1(zipcode, address1) {
	
	var form = insertform2.getForm();
	
	form.findField("zipcode").setValue(zipcode);
	form.findField("address1").setValue(address1);
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


function download() {
	
	Ext.getBody().mask('파일 다운로드 중...');
	
	Ext.Ajax.request({
		url: COMMON_URL + '/ajaxSelectDeliveryExcel',
		success: function(result, request) {
			Ext.getBody().unmask();
			var obj = Ext.decode(result.responseText);
			location.href = COMMON_URL + "/common/FileDown.jsp?fileName="+obj.filename+"&fileDir="+obj.filepath;
		},
		failure: function(result, request) {
			Ext.getBody().unmask();        							 
			Ext.Msg.alert('Error', '다운로드 중 오류가 발생하였습니다.');	        							 
		},
		params : Ext.getCmp('searchForm').getForm().getValues(),  
		timeout: TIMEOUT_SEC
	});
}