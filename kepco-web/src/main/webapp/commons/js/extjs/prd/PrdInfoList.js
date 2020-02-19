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
            'prd_no'
			, 'prd_type'
			, 'prd_serial_no'
			, 'prd_nm'
			, 'prd_cate1'
			, 'prd_cate1_nm'
			, 'prd_cate2'
			, 'prd_cate2_nm'
			, 'as_price'
			, 'as_cost'
			, 'mat_cost'
			, 'labor_cost'
			, 'mk_cost'
			, 'as_travel_cost'
			, 'prd_member_id'
			, 'color'
			, 'sale_sdate'
			, 'sale_edate'
			, 'road_prd_cost'
			, 'road_labor_cost'
			, 'road_cost'
			, 'prd_spec'
			, 'prd_merit'
			, 'prd_desc'			
			, 'site'
			, 'use_yn'
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
            url: COMMON_URL + '/ajaxPrdInfoList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'prd_no',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'prd_serial_no',
			text : '제품자재번호',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_type',
			text : '제품자재구분',
			width : 80,
			align : 'center',
			sortable : true,
			renderer : getPrdTypeNm
		}, {
			dataIndex : 'prd_nm',
			text : '제품자재명',
			width : 200,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'prd_spec',
			text : '자재SPEC',
			width : 200,
			align : 'center',
			sortable : true
		},{
			dataIndex : 'as_price',
			text : '단가',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'mat_cost', 
			text : '자재비',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'labor_cost',
			text : '공임비',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'as_cost',
			text : 'AS비용',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'as_travel_cost',
			text : 'AS출장비',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'road_cost',
			text : '로드단가',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'road_prd_cost',
			text : '로드자재비',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'road_labor_cost',
			text : '로드공임비',
			width : 100,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'use_yn',
			text : '사용여부',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'site',
			text : '사이트',
			width : 100,
			align : 'center',
			sortable : false,
			renderer : getSiteNm
		}, {
			dataIndex : 'insert_id',
			text : '등록자',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_dt',
			text : '등록일시',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'update_id',
			text : '수정자',
			width : 80,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'update_dt',
			text : '수정일시',
			width : 150,
			align : 'center',
			sortable : false
		}
	];

    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"a.prd_serial_no", "name":"제품자재번호"},
            {"code":"a.prd_nm", "name":"제품자재명"},
            {"code":"a.prd_spec", "name":"자재SPEC"}
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
        value: 'a.prd_serial_no'
    });

    var prdType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"1", "name":"제품"},
            {"code":"2", "name":"자재"}
        ]
    });	
    
    var comboPrdType = Ext.create('Ext.form.ComboBox', {
        store: prdType,
        width: 120,        
        name: 'prd_type',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '제품자재구분'
    });
    
    	
    
    var comboSite = Ext.create('Ext.form.ComboBox', {
        store: siteStore,
        width: 120,        
        name: 'site',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '사이트구분',
        value: '1'
    });
    
    var useYNStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"Y", "name":"사용"},
            {"code":"N", "name":"미사용"}
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
						fieldLabel: '조건검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},			
					comboSite,
					comboPrdType,
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
		    	text: '제품자재정보등록',
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
		
		var site = form.findField("site");
		var prd_type = form.findField("prd_type");
		
		if(sdate.getSubmitValue() == "" 
			&& edate.getSubmitValue() == "" 
			&& searchquery.getValue() == ""
			&& site.getValue() == ""
			&& prd_type.getValue() == ""
		) {
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
    	var prd_no = "";
    	
    	if(!win) {
    		
	    	win = Ext.create('Ext.window.Window', {
	            title: '제품자재정보',
	            height: 600,
	            width: 800,
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
				// 제품번호
				prd_no = rec.data.prd_no;
			}
	    	
	    	if(prd_no == "") {
	    		url = COMMON_URL + '/ajaxPrdInfoInsert';
	    		
	    		insertform.getForm().findField("emode").setValue("insert");
	    		insertform.getForm().findField("prd_serial_no").setReadOnly(false);
	    		
	    		Ext.getCmp("btnDelete").setDisabled(true);
	    		Ext.getCmp("btnChkPrdNo").setDisabled(false);
	    		
			} else {				
				url = COMMON_URL + '/ajaxPrdInfoUpdate';
				insertform.getForm().findField("emode").setValue("update");
				insertform.getForm().findField("prd_serial_no").setReadOnly(true);
				
				Ext.getCmp("btnDelete").setDisabled(false);
				Ext.getCmp("btnChkPrdNo").setDisabled(true);
			}
		}
    }
    
    //팝업 form
    var insertform = Ext.create('Ext.form.Panel', {
    	id: 'insertform',
	    bodyPadding: 10,
	    flex: 1,
	    border: 0,
	    layout: 'anchor',
	    defaults: {
	        anchor: '100%'
	    },
	    defaultType: 'textfield',
	    items: [{
			xtype: 'hidden',
			name: 'emode',
			value:'insert'
		}, {
			xtype: 'hidden',
			name: 'prd_no'
		}, {
			xtype: 'hidden',
			name: 'prd_no_chk',
			value:'N'
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',
	            defaultType: 'textfield',
	            flex: 1,                	            
	            fieldLabel: '제품/자재번호',
	            afterLabelTextTpl: [MARK_ASTERISK],
	            items: [{
	            	name: 'prd_serial_no',
	                flex: 1,	                	                
	                listeners: {
	                	change: function (t, newValue, oldValue, eOpts) {
	                		if(newValue != oldValue) {
	                			var form = this.up('form').getForm();					
	    			            var prd_no_chk = form.findField("prd_no_chk");
	    			            
	    			            prd_no_chk.setValue("N");
	                		}
                        }
	                }
	            }, {
	    	    	xtype: 'button',
	    	    	id: 'btnChkPrdNo',
	    	    	text: '중복검색',
	    	    	margin: '0 0 0 5',
	    	    	handler: function() {
	    	    		var form = this.up('form').getForm();					
			            var prd_serial_no = form.findField("prd_serial_no");
			            
			            if (prd_serial_no.getValue() == "") {	     				
		     				focusMsgAlert('Warning', "제품자재번호를 입력해 주세요.", prd_serial_no);
		     				return;
		     			}
			            
			            Ext.Ajax.request({
			                url: COMMON_URL + '/ajaxPrdInfoCount',
			                params: {
			                	prd_serial_no: prd_serial_no.getValue()
			                },
			                success: function(response){
			                	var obj = toJson(response.responseText);			                	
			                	
			                	if(obj.result > 0) {
			        				focusMsgAlert('Warning', "[사용불가] 사용중인 제품자재번호가 있습니다.", prd_serial_no);
			        				form.findField("prd_no_chk").setValue("N");
			                		return;
			                	} else if(obj.result == 0) {
			                		focusMsgAlert('Success', "사용 할 수 있는 제품자재번호 입니다.");
			                		form.findField("prd_no_chk").setValue("Y");
			                		return;
			                	} else {
			                		focusMsgAlert('Warning', "다시 조회하여 주십시오", prd_serial_no);
			        				form.findField("prd_no_chk").setValue("N");
			                		return;
			                	}
			                },
			                failure: function(result, request) {
								 focusMsgAlert('Error', "중복체크에  실패하였습니다.", prd_serial_no);
							}
			            });	    	    	
	    	    	}
	    	    }]
        	}, {
	        	name: 'prd_nm',
	        	fieldLabel: '제품/자재명',
	            flex:1,
	            margin: '0 0 0 15',
	            afterLabelTextTpl: [MARK_ASTERISK]
	        }]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{   
				xtype: 'combobox',
				name: 'prd_type',
				fieldLabel: '제품자재구분',
		        store: prdType,
		        queryMode: 'local',
		        displayField: 'name',
		        valueField: 'code',		        
		        editable: false,
		        flex: 1,
		        afterLabelTextTpl: [MARK_ASTERISK]
			}, {   
				xtype: 'combobox',
				name: 'site',
				fieldLabel: '사이트',
		        store: siteStore,
		        queryMode: 'local',
		        displayField: 'name',
		        valueField: 'code',		        
		        editable: false,
		        flex:1,
		        value: '1',
	            margin: '0 0 0 15',
	            afterLabelTextTpl: [MARK_ASTERISK]
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
	        	name: 'prd_cate1',
	        	fieldLabel: '제품분류코드',
	            flex:1
	        }, {
	        	name: 'prd_cate2',
	        	fieldLabel: '모델분류코드',
	            flex:1,
	            margin: '0 0 0 15'
	        }]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
	        	name: 'prd_cate1_nm',
	        	fieldLabel: '제품군',
	            flex:1
	        }, {
	        	name: 'prd_cate2_nm',
	        	fieldLabel: '모델군',
	            flex:1,
	            margin: '0 0 0 15'
	        }]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'numberfield',
	        items: [{
	        	name: 'as_price',
	        	fieldLabel: 'AS단가',
	        	hideTrigger: true,
	            flex:1
	        }, {
	        	name: 'as_cost',
	        	fieldLabel: 'AS 비용',
	        	hideTrigger: true,
	            flex:1,
	            margin: '0 0 0 15'
	        }]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'numberfield',
	        items: [{
	        	name: 'mat_cost',
	        	fieldLabel: '자재비',
	        	hideTrigger: true,
	            flex:1
	        }, {
	        	name: 'labor_cost',
	        	fieldLabel: '공임비',
	        	hideTrigger: true,
	            flex:1,
	            margin: '0 0 0 15'
	        }]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'numberfield',
	        items: [{
	        	name: 'mk_cost',
	        	fieldLabel: 'MK 원가',
	        	hideTrigger: true,
	            flex:1
	        }, {
	        	name: 'as_travel_cost',
	        	fieldLabel: 'AS 출장비',
	        	hideTrigger: true,
	            flex:1,
	            margin: '0 0 0 15'
	        }]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'numberfield',
	        items: [{
	        	name: 'road_prd_cost',
	        	fieldLabel: '로드자재비',
	        	hideTrigger: true,
	            flex:1
	        }, {
	        	name: 'road_labor_cost',
	        	fieldLabel: '로드공임비',
	        	hideTrigger: true,
	            flex:1,
	            margin: '0 0 0 15'
	        }]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'numberfield',
	        items: [{
	        	name: 'road_cost',
	        	fieldLabel: '로드단가',
	        	hideTrigger: true,
	            flex:1
	        }, {
	        	xtype: 'textfield',
	        	name: 'color',
	        	fieldLabel: '색상',
	            flex:1,
	            margin: '0 0 0 15'
	        }]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'datefield',
	        items: [{
	        	name: 'sale_sdate',
	        	fieldLabel: '판매시작일',
	        	format: 'Ymd',
	            flex:1
	        }, {
	        	name: 'sale_edate',
	        	fieldLabel: '판매종료일',
	        	format: 'Ymd',
	            flex:1,
	            margin: '0 0 0 15'
	        }]
		}, {
			xtype: 'textareafield',
        	name: 'prd_spec',
        	fieldLabel: '제품SPEC',
            height: 60
        }, {
        	xtype: 'textareafield',	
        	name: 'prd_merit',
        	fieldLabel: '제품특장점',
            height: 60
        }, {
        	xtype: 'textareafield',
        	name: 'prd_desc',
        	fieldLabel: '제품비고',
            height: 60
        }, {   
			xtype: 'combobox',
			name: 'use_yn',
			fieldLabel: '사용여부',
	        store: useYNStore,
	        queryMode: 'local',
	        displayField: 'name',
	        valueField: 'code',		        
	        editable: false,
	        anchor: '30%',
	        value: 'Y',
            afterLabelTextTpl: [MARK_ASTERISK]
		}],
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
	            var prd_no	= form.findField("prd_no");
				var prd_serial_no	= form.findField("prd_serial_no");
				var prd_nm = form.findField("prd_nm");
				var prd_type = form.findField("prd_type");
				var prd_cate1 = form.findField("prd_cate1");
				var prd_cate2 = form.findField("prd_cate2");
				var prd_cate1_nm = form.findField("prd_cate1_nm");
				var prd_cate2_nm = form.findField("prd_cate2_nm");
				var site = form.findField("site");
				var prd_no_chk = form.findField("prd_no_chk");
								
				if(prd_serial_no.getValue() == "" ) {					
					focusMsgAlert('Warning', '제품자재번호를 입력해 주세요1', prd_serial_no);
					return;
				}
				
				if(emode.getValue() == "insert" && prd_no_chk.getValue() == "N" ) {					
					focusMsgAlert('Warning', '제품자재번호 확인을 위해 중복검색 하여 주십시오!', prd_no);
					return;
				}
				
				if(prd_nm.getValue() == "" ) {					
					focusMsgAlert('Warning', '제품자재명을 입력해 주세요', prd_nm);
					return;
				}
				
				if(prd_type.getSubmitValue() == "" ) {					
					focusMsgAlert('Warning', '제품자재구분을 선택해 주세요', prd_type);
					return;
				}
				
				if(prd_type.getSubmitValue() == "1" ) { // 제품
					if(prd_cate1.getValue() == "" ) {					
						focusMsgAlert('Warning', '제품분류코드를 입력해 주세요', prd_cate1);
						return;
					}
					
					if(prd_cate2.getValue() == "" ) {					
						focusMsgAlert('Warning', '모델분류코드를 입력해 주세요', prd_cate2);
						return;
					}
					
					if(prd_cate1_nm.getValue() == "" ) {					
						focusMsgAlert('Warning', '제품군을 입력해 주세요', prd_cate1_nm);
						return;
					}
					
					if(prd_cate2_nm.getValue() == "" ) {					
						focusMsgAlert('Warning', '모델군을 입력해 주세요', prd_cate2_nm);
						return;
					}
				}
				
				if(site.getSubmitValue() == "" ) {					
					focusMsgAlert('Warning', '사이트를 선택해 주세요', site);
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
	        text: '삭제',
	        formBind: true, 
	        iconCls: 'icon-delete',
	        id: 'btnDelete',
	        handler: function() {
	        	
	            var form = this.up('form').getForm();
	            
	            var prd_no	= form.findField("prd_no");
	            
				if(prd_no.getValue() == "" ) {					
					focusMsgAlert('Warning', '제품자재번호가 없어 삭제 할 수 없습니다.', prd_no);
					return;
				}
				
				Ext.Msg.show({
				    title:'Delete',
				    msg: '정말 삭제하시겠습니까?',
				    buttons: Ext.Msg.YESNO,
				    icon: Ext.Msg.QUESTION,
				    fn: function(btn) {
				        if (btn === 'yes') {
				        	if (form.isValid()) {
				                form.submit({
				                	url: COMMON_URL + '/ajaxPrdInfoDelete',
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
				        } else if (btn === 'no') {
				            return;
				        } else {
				            return;
				        } 
				    }
				});
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
    
    function download() {
		
		Ext.getBody().mask('파일 다운로드 중...');
		
		Ext.Ajax.request({
			url: COMMON_URL + '/ajaxExcelPrdInfoList',
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
	
});