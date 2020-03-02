Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer',
	'Ext.selection.CheckboxModel',
	'Ext.selection.CellModel',
	'Ext.form.field.ComboBox'
]);  

var isolation_flag ;
var toDate = Ext.Date.format(new Date(),'Ymd');
var selected_prd_cd = new Array();
var selected_plan_gd = new Array();
var atonce_prd_cd ;
var atonce2_flag ;

Ext.onReady(function() { 
	
	// leftPanel에 들어가는 고객정보 패널 Start , add by yoon 2015.02.24
	var insuHolderPanel = Ext.create('Ext.panel.Panel', {		
		id: 'insuHolderPanel',
		border: 0,
		defaults: {anchor: '100%'},
        layout: 'anchor',
	    items: [{
			    xtype: 'fieldset',
			    title: '고객정보 관련',
			    padding: '7 7 7 7',
			    defaultType: 'textfield',
			    fieldDefaults: {		            
			    	 	labelAlign: 'center',
			            labelStyle: formLabelStyle,
			            //labelWidth: 100,
			            labelSeparator: ""
		        },
			    items: [
					    {
			            	xtype: 'fieldcontainer',            
				            layout: 'hbox',            
				            defaultType: 'textfield',           
				            items: [{
				    			xtype:'textfield', // add yoon
						        name: 'cust_no',
						        fieldLabel: '고객번호',
					            labelWidth: 70,
								emptyText: '고객번호',
						        width: 150,
						        editable: false,
								readOnly: true
							},{
						    	xtype: 'button',    	    	
						    	align:'right',
						    	text: '고객가져오기',
						    	style:'text-align:right',
						    	flex: 1,
						    	margin: '0 0 0 5',
				    	    	handler: function() {
				    	    		request_KB();
				    	    	}
						    }]
						},
						{
			            	xtype: 'fieldcontainer',            
				            layout: 'hbox',            
				            defaultType: 'textfield',           
				            items: [{
				    			xtype:'textfield', // add yoon
						        name: 'cust_nm',
						        fieldLabel: '고객명',
					            labelWidth: 70,
								emptyText: '고객명',
						        width: 150,
						        editable: false,
								readOnly: true
							},{
						    	xtype: 'button',    	    	
						    	align:'right',
						    	text: '정보초기화',
						    	style:'text-align:right',
						    	flex: 1,
						    	margin: '0 0 0 5',
				    	    	handler: function() {
				    	    		formRefresh();
				    	    	}
						    }]
						},
						{	
							name: 'insu_policy_no',
							xtype:'hiddenfield'
						}
			    ]
			}
        ]
	});	
	
	
	// 운전종류(운전자타입)
	var driveTypeStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
	            {"code":"1", "name":"자가"},
	            {"code":"2", "name":"영업"},
	            {"code":"3", "name":"비운전"}
        ]
    });  	
	
	// leftPanel에 들어가는 첫번째패널 Start
	var insuInsuredPanel = Ext.create('Ext.panel.Panel', {		
		id: 'insuInsuredPanel',
		border: 0,
		defaults: {anchor: '100%'},
        layout: 'anchor',
	    items: [{
			    xtype: 'fieldset',
			    title: '피보험자 관련',
			    padding: '7 7 7 7',
			    defaultType: 'textfield',
			    fieldDefaults: {		            
			    	 	labelAlign: 'center',
			            labelStyle: formLabelStyle,
			            //labelWidth: 100,
			            labelSeparator: ""
		        },
			    items: [
					    {
//			            	xtype: 'datefield', 
//			            	format: 'Ymd',						            	
			                name: 'contract_date',
			                fieldLabel: '계약일자',
			                labelWidth: 70,
			        		width: 150,
			    	        value: toDate
					    },
					    {
				            xtype: 'fieldcontainer',            
				            layout: 'hbox',            
				            defaultType: 'textfield',           
				            items: [{
						                name: 'insu_ssn_no',
				                		fieldLabel: '생년월일',
						                labelWidth: 70,
						        		width: 150,
						        		maxLength:7,
						                maskRe:/^[0-9]+$/,
						                listeners: {
						                	blur: function (t) {
					                    		var form1 = Ext.getCmp('Content').getForm();
						                		var this_val = t.lastValue;
						                		var contract_date = form1.findField("contract_date").getValue();
						                		
					                    		if(this_val!=undefined && this_val!=""){
							                		form1.findField("insu_birth_date").setValue(getBirth(this_val));
							                		form1.findField("insu_age").setValue(insu_age2(getBirth(this_val),contract_date));
													form1.findField("insu_sex").setValue(this_val.substring(6));
							                		form1.findField("txt_insu_sex").setValue(getSexKor(this_val.substring(6)));

						                    		reCal_Check();
					                    		}	
					                        }
					                    }
						            }, {
						                name: 'insu_ssn_no1',
										xtype:'hiddenfield'
						            }, {
						            	// 보험료계산시 사용할~~ 나이
						                id: 'insu_age',
						                name: 'insu_age',
						                emptyText:'나이',
						        		width: 35,
							        	margin: '0 0 0 5',
						                fieldCls: 'fieldBackgroundColor',
								        editable: false,
										readOnly: true
						            }, {
						                name: 'txt_insu_sex',
						                emptyText:'성별',
						        		width: 35,
							        	margin: '0 0 0 5',
						                fieldCls: 'fieldBackgroundColor',
								        editable: false,
										readOnly: true
						            }, {
						                name: 'insu_birth_date',
										xtype:'hiddenfield'
						            }, {
						            	// 보험료계산시 사용할~~ 성별(숫자)
						                name: 'insu_sex',
										xtype:'hiddenfield'
						    		}
				            ]
					    },
						{
			    			xtype:'textfield',
					        name: 'insu_occup_nm',
					        fieldLabel: '직업',
				            labelWidth: 70,
							emptyText: '직업명',
					        width: 249,
					        editable: false,
							readOnly: true
						},
						{
				            xtype: 'fieldcontainer',            
				            layout: 'hbox',            
				            defaultType: 'textfield',
				            margin: '0 0 0 75',
						    items: [{
								        name: 'insu_occup_cd',
										emptyText: '코드',
								        width: 48,		                
								        minLength: 5,		                
								        maxLength: 5,
						                maskRe:/^[A-Z0-9]+$/,
						                enableKeyEvents:true,
						                listeners: {
						                	keydown: function (t,e) {
						                		var form1 = Ext.getCmp('Content').getForm();
					                    		if(e.keyCode==13) {
					                    			if(t.value.length!=5) {
					                    				focusMsgAlert('Error', '[피보험자 정보] 직업코드는 5자리 입니다.', form1.findField("insu_occup_cd"));
					                    				return false;
					                    			}
					                    			else {
					                    				searchJobNM(t.value);
					                    			}
					                    		}
					                        }
//						    				,
//						                	blur: function (t,n,o) {
//						                		var form1 = Ext.getCmp('Content').getForm();
//				                    			if(t.value.length!=5) {
//				                    				focusMsgAlert('Error', '[피보험자 정보] 직업코드는 5자리 입니다.', form1.findField("insu_occup_cd"));
//				                    				return false;
//				                    			} else {
//				                    				searchJobNM(t.value);
//				                    			}
//						                	}
					                    }
								    }, {
								    	xtype: 'hiddenfield',
								        name: 'insured_type',
								        value:'00',
								        id: 'insured_type'
								    }, {
								        name: 'insu_occup_gd',
										emptyText: '급수',
								        width: 37,
								        margins: '0 0 0 -1',			                
								        editable: false,
										readOnly: true,
						                listeners: {
						                	change: function (t) {
						                		var this_val = t.lastValue;
						                		
					                    		if(this_val!=undefined && this_val!=""){
						                    		reCal_Check();
					                    		}	
					                        }
					                    }
								    }, {
						            	xtype: 'hiddenfield',
								        name: 'insu_drive_gd',
						                listeners: {
						                	change: function (t) {
						                		var this_val = t.lastValue;
						                		
					                    		if(this_val!=undefined && this_val!=""){
						                    		reCal_Check();
					                    		}	
					                        }
					                    }
								    }, {
								    	xtype: 'button',    	    	
								    	align:'right',
								    	text: '직업조회',
								    	style:'text-align:right',
								    	iconCls: 'icon-search',	
								    	margin: '0 0 5 5',
						    	    	handler: function() {
						    	    		winOccupCodePop('setCodeOccup');
						    	    	}
								    }
							]
						}
					, {
			            xtype: 'fieldcontainer',            
			            layout: 'hbox',            
			            defaultType: 'textfield',           
			            items: [{
					            	xtype: 'combo',
					                name: 'insu_drive_type',
					                fieldLabel: '운전종류',
					                labelWidth: 70,	
					                width: 140,
					                store: driveTypeStore,		                
					                queryMode: 'local',
							        displayField: 'name',
							        valueField: 'code',
							        editable: false,
					                listeners: {
					                	change: function (t) {
					                		var this_val = t.lastValue;
					                		
				                    		if(this_val!=undefined && this_val!=""){
					                    		reCal_Check();
				                    		}	
				                        }			                    
					                }
					            },	
					            {	// 빌딩급수
					            	xtype: 'hiddenfield',
					                name: 'insu_building_gd'
					            }
			            ]
				    }
			    ]
			}
        ]
	});	
	// leftPanel에 들어가는 첫번째패널 End
	
	// leftPanel에 들어가는 두번째패널에 들어가는 콤보박스 Start
	// 상품
	var planStore = Ext.create('Ext.data.Store', {	
		id: 'planStore',
	    remoteSort: true,
		proxy: {
	        type: 'ajax',
	        url: COMMON_URL + '/ajaxPlanCombo',
	        reader: {root: 'result'},
	        simpleSortMode: true,
	        extraParams: {use_yn:'Y'}
	    },
	    fields: ['plan_no', 'plan_desc', 'plan_period', 'interest_rate'],
	    autoLoad: true
	});
	var comboPlan = Ext.create('Ext.form.ComboBox', {
	    store: planStore.load(),
		fieldLabel: '상품',
		labelWidth: 70,
		width: 250,
	    name: 'plan_no',
	    queryMode: 'local',
	    displayField: 'plan_desc',
	    valueField: 'plan_no',
	    emptyText: '상품 선택',
	    submitValue: true,
	    editable: false,
        listeners: {
        	scope: this,
        	select: function(combo, record, index) {
        		var form1 = Ext.getCmp('Content').getForm();
        		var plan_period = record[0].data.plan_period;
	    		var interest_rate = record[0].data.interest_rate;
        		
        		form1.findField("plan_period").setValue(plan_period);
	    		form1.findField("interest_rate").setValue(interest_rate);
        		
        		productSearch();
            }
        }
	});	
	
	// 가입유형
	var relStore = Ext.create('Ext.data.Store', {	
		id: 'relStore',
	    remoteSort: true,
		proxy: {
	        type: 'ajax',
	        url: COMMON_URL + '/ajaxCodeCombo',
	        reader: {root: 'result'},
	        simpleSortMode: true,
	        extraParams: {use_yn:'Y',display_yn:'Y','class_cd': 'RE'}
	    },
	    fields: ['remark', 'code_nm']
	});
	var comboRel = Ext.create('Ext.form.ComboBox', {
	    store: relStore.load(),
		fieldLabel: '가입유형',
		labelWidth: 70,
		width: 250,
	    name: 'insu_rel',
	    queryMode: 'local',
	    displayField: 'code_nm',
	    valueField: 'remark',
	    value: 'I', 
	    submitValue: true,
	    editable: false
	});	
	// leftPanel에 들어가는 두번째패널에 들어가는 콤보박스 End	
	
	// leftPanel에 들어가는 두번째패널 Start
	var planPanel = Ext.create('Ext.panel.Panel', {
		border: 0,
		defaults: {anchor: '100%'},
        layout: 'anchor',
	    items: [{
			    xtype: 'fieldset',
			    title: '상품정보 관련',
			    padding: '7 7 7 7',
			    defaultType: 'textfield',
			    fieldDefaults: {		            
			    	 	labelAlign: 'center',
			            labelStyle: formLabelStyle,
			            //labelWidth: 100,
			            labelSeparator: ""
		        },
			    items: [ comboPlan,
			             comboRel,
		                {
			    			xtype: 'textfield',
					        name: 'plan_period',
				            fieldLabel: '납입기간',
				    		labelWidth: 70,
				    		width: 250,
					        margins: '0 0 0 5',			                
					        editable: false,
							readOnly: true
						},
			            {
					    	//선택상품의 적용이율
					        name: 'interest_rate',
					        xtype: 'hiddenfield'
					    },
					    {
					    	id: 'btnReCal',
					    	xtype: 'button',
					    	text: '재계산',
							width: 250,
					    	style:'text-align:right',
					    	iconCls: 'icon-Accounting',
			                fieldCls: 'fieldBackgroundColor',
				            disabled: true,
					    	handler: function(){
					    		reCalSearch();
					    	}			
						}
			    ]
			}
        ]
	});	
	// leftPanel에 들어가는 두번째패널 End
	
	// leftPanel에 들어가는 세번째패널 Start
	var searchPanel = Ext.create('Ext.panel.Panel', {		
		border: 0,
		defaults: {anchor: '100%'},
        layout: 'anchor',
	    items: [{
			    xtype: 'fieldset',
			    title: '선택담보 관련',
			    padding: '7 7 7 7',
			    defaultType: 'textfield',
			    fieldDefaults: {		            
			    	 	labelAlign: 'center',
			            labelStyle: formLabelStyle,
			            //labelWidth: 100,
			            labelSeparator: ""
		        },
			    items: [
						{
							id: 'btnSwitching',
			            	xtype: 'button',
							align:'right',
							text: '승환계약조회',			    	
							style:'text-align:right',
							iconCls: 'icon-search',	
							width: 250,
							margin: '0 0 5 0',	
				            disabled: true,		    	
							handler: function() {
								var grid = Ext.getCmp('productPanel').getSelectionModel();
							
								if (grid.store.data.length > 0) {
									switchingPop();
								} else {
									alert('특약 선택 후  클릭하시기 바랍니다.');
									return false;
								}
							}
						},
						{
					        xtype: 'fieldcontainer',            
					        layout: 'hbox',            
					        defaultType: 'textfield',
					        flex: 1,
						    items: [
								{
								    xtype: 'hiddenfield',
								    name: 'poa_cnt'
								}, 
					            {
							        name: 'mr_cnt',
						            fieldLabel: '의료비담보',	             
						            labelWidth: 70,
						            width: 160,
							        editable: false,
									readOnly: true
					            },
					            {
							    	id: 'btnPresearchMR',
					            	xtype: 'button',
							    	text: '담보조회',
							    	iconCls: 'icon-search',
					    	    	handler: function() {
					    	    		var form1 = Ext.getCmp('Content').getForm();
					    	    		if(form1.findField("cust_no").getValue() != "") {
					    	    			mrPop() ;
					    	    		} else {
					    	    			alert("고객가져오기 후 담보조회가 가능합니다.");
					    	    		}
					    	    	},
						            margins: '0 0 0 5',
						            disabled: true
					    	    }
							]
			            }, {
					        xtype: 'fieldcontainer',            
					        layout: 'hbox',            
					        defaultType: 'textfield',
						    items: [
					            {
							        name: 'lumpsum_cnt',
						            fieldLabel: '정액담보',             
						            labelWidth: 70,
						            width: 160,               
							        editable: false,
									readOnly: true
					            },
					            {
							    	id: 'btnPresearchLumpsum',
					            	xtype: 'button',
							    	text: '담보조회',
							    	iconCls: 'icon-search',
					    	    	handler: function() {
					    	    		var form1 = Ext.getCmp('Content').getForm();
					    	    		if(form1.findField("cust_no").getValue() != "") {
					    	    			mePop() ;
					    	    		} else {
					    	    			alert("고객가져오기 후 담보조회가 가능합니다.");
					    	    		}
					    	    	},
						            margins: '0 0 0 5',
						            disabled: true
					    	    }
							]
						}
			    ]
			}
        ]
	});	
	// leftPanel에 들어가는 세번째패널 End	
	
	// rightPanel에 들어가는 첫번째패널 Start
	var buttonPanel = Ext.create('Ext.panel.Panel', {		
		id: 'buttonPanel',
		border: 0,
		defaults: {anchor: '100%'},
	    layout: {
			        type: 'hbox',
			        align: 'stretch'
	    },
	    items: [
//	            {
//			    	xtype: 'button',
//			    	text: '스크립트',
//			    	align:'right',
//			    	style:'text-align:right',
//			    	iconCls: 'icon-page_white_edit',
//			    	margin: '10 0 7 0',
//			    	handler: function(){
//			    		var grid = Ext.getCmp('productPanel').getSelectionModel();
//
//			    		if (grid.store.data.length > 0) {
//			    			sendScopePop();
//			    		} else {
//			                Ext.Msg.alert('Notice', '담보를 선택한 후  클릭하시기 바랍니다.');
//			    			return false;
//			    		}
//			    	}
//	    		},
	    		{
	    			xtype: 'button', 
			    	id : 'btnRecordScript1',
			    	text: '계피동일',
			    	align:'right',			    	
			    	style:'text-align:right',
			    	iconCls: 'icon-script',	
			    	margin: '10 0 7 5',
			    	handler: function(){
			    		var grid = Ext.getCmp('productPanel').getSelectionModel();

			    		if (grid.store.data.length > 0) {
			    			checkRecordScript(1);
			    		} else {
			                Ext.Msg.alert('Notice', '담보를 선택한 후  클릭하시기 바랍니다.');
			    			return false;
			    		}
			    	}
	    		}, {
	    			xtype: 'button',   
			    	id : 'btnRecordScript2',
			    	text: '계피상이',
			    	align:'right',			    	
			    	style:'text-align:right',
			    	iconCls: 'icon-script',	
			    	margin: '10 0 7 15',
			    	handler: function(){
			    		var grid = Ext.getCmp('productPanel').getSelectionModel();

			    		if (grid.store.data.length > 0) {
			    			checkRecordScript(2);
			    		} else {
			                Ext.Msg.alert('Notice', '담보를 선택한 후  클릭하시기 바랍니다.');
			    			return false;
			    		}
			    	}
	    		}, {
	    			xtype: 'button', 
			    	id : 'btnAddScript',
			    	text: 'POA동의',
			    	align:'right',			    	
			    	style:'text-align:right',
			    	iconCls: 'icon-information',	
			    	margin: '10 0 7 5',
			    	handler: function(){
			    		sendPOAagreePop();
			    	}
	    		}, {    			
					xtype: 'tbfill'	    			
			    }, {
			    	xtype: 'button',
			    	text: '청약서적용',
			    	align:'right',
			    	style:'text-align:right',
			    	iconCls: 'icon-page_2_copy',
			    	margin: '10 0 7 0',
			    	handler: function(){
			    		var grid = Ext.getCmp('productPanel').getSelectionModel();

			    		if (grid.store.data.length > 0) {
			    			inputCalculator('contractPop');
			    		} else {
			                Ext.Msg.alert('Notice', '담보를 선택한 후  클릭하시기 바랍니다.');
			    			return false;
			    		}
			    	}
			    }, {
			    	xtype: 'button',
			    	text: '가입설계서적용',
			    	align:'right',
			    	style:'text-align:right',
			    	iconCls: 'icon-page_2_copy',
			    	margin: '10 0 7 10',
			    	handler: function(){
			    		var grid = Ext.getCmp('productPanel').getSelectionModel();

			    		if (grid.store.data.length > 0) {
			    			inputCalculator('insuPlanPop');
			    		} else {
			                Ext.Msg.alert('Notice', '담보를 선택한 후  클릭하시기 바랍니다.');
			    			return false;
			    		}
			    	}
			    }
		]
	});	
	// rightPanel에 들어가는 첫번째패널 End
	
	// rightPanel에 들어가는 두번째패널 Start
	Ext.define('productModel', {
	    extend:'Ext.data.Model',
	    fields:[
	        'plan_no'   ,		//상품번호
	        'prd_cd'    ,		//특약번호
	        'prd_nm_kor',		//특약명
	        'op_cd'     ,		//필수담보 및 선택담보
	        'premium'   ,		//보험료
	        'premium_renewal',	//갱신보험료
	        'premium_renewal_65',	//65세 시점 갱신보험료
	        'band'		,		//밴드
	        'age_min'	,		//가입가능 최소연령
	        'age_max'	,		//가입가능 최대연령
	        'cat'       ,		//캣
	        'dis'       ,		//할인율
	        'rel'       ,		//가입유형
	        'rel_type'  ,		//관계
	        'sex_yn'    ,		//성별에 따른 보험료구별 구분
	        'sex'       ,		//성별
	        'layer'     ,		//레이어
	        'layer_head',
	        'layer_tail',
	        'div'       ,		//급수구분
	        'cls'       ,		//급수
	        'pl'        ,		//상품종류(상품유형)
	        'occup_gd'  ,
	        'plan_gd'   ,
	        'mr'        , 
	        'sick_mr'   , 
	        'lumpsum'   , 
	        'poa'       ,
	        'benefit'   ,
	        'insured_age',
	        'insured_sex', 
	        'insured_job_gd',
	        'insured_drive_gd',
	        'insured_drive_type',
	        'insured_building_gd'
	    ]
	});

	
	var plangdStore = Ext.create('Ext.data.Store', {
	    fields: ['code', 'code_nm']
	});	
	
	var plangdStoreN = Ext.create('Ext.data.Store', {
	    fields: ['code', 'code_nm'],
	    data : [
	            {"code":"N", "code_nm":"N형"}
	    ]
	});	
	
	var plangdStore1 = Ext.create('Ext.data.Store', {
	    fields: ['code', 'code_nm'],
	    data : [
		        {"code":"1", "code_nm":"1형"}
	    ]
	});	
	
	var plangdStore2 = Ext.create('Ext.data.Store', {
	    fields: ['code', 'code_nm'],
	    data : [
		        {"code":"1", "code_nm":"1형"},
		        {"code":"2", "code_nm":"2형"}
	    ]
	});	
	
	var plangdStore3 = Ext.create('Ext.data.Store', {
	    fields: ['code', 'code_nm'],
	    data : [
		        {"code":"1", "code_nm":"1형"},
		        {"code":"2", "code_nm":"2형"},
		        {"code":"3", "code_nm":"3형"}
	    ]
	});	
	
	var plangdStore4 = Ext.create('Ext.data.Store', {
	    fields: ['code', 'code_nm'],
	    data : [
		        {"code":"1", "code_nm":"1형"},
		        {"code":"2", "code_nm":"2형"},
		        {"code":"3", "code_nm":"3형"},
		        {"code":"4", "code_nm":"4형"}
	    ]
	});	
	
	var plangdStore5 = Ext.create('Ext.data.Store', {
	    fields: ['code', 'code_nm'],
	    data : [
		        {"code":"1", "code_nm":"1형"},
		        {"code":"2", "code_nm":"2형"},
		        {"code":"3", "code_nm":"3형"},
		        {"code":"4", "code_nm":"4형"},
		        {"code":"5", "code_nm":"5형"}
	    ]
	});	

	
	var productColumns = [
		            //{xtype: 'rownumberer', header : '번호', align: 'center', width: 30},
		            {
						text : "선택",
						dataIndex : 'op_cd',
						width : 50,
						align : 'center',
		                //menuDisabled: true,
						sortable : false,
						renderer: function(storeItem) {
							var text = '';
							
							if(storeItem == '0'){
								var text = '필수';
							} else {
								var text = '선택'+ storeItem;
							}
							return text;
						}
					}, {
						text : "담보코드",
						dataIndex : 'prd_cd',
						width: 70,				
						align : 'left',
						hidden: true,
		                menuDisabled: true,
						sortable : false
					}, {
						text : "특약명",
						dataIndex : 'prd_nm_kor',
						//flex : 1,
						width: 200,				
						align : 'left',
		                menuDisabled: true,
						sortable : false
		            }, {
		                header: '상품종류',
		                dataIndex: 'plan_gd',
                        width: 65,
		                align: 'center',
		                menuDisabled: true,
		                sortable: false,
		                xtype: 'componentcolumn',
		                renderer: function(storeItem, record) {	
		                	var grid_rowIndex = record.rowIndex;

		                	if(storeItem == "N") {
		                		plangdStore = plangdStoreN;
		                	} else if(storeItem == "1") {
		                		plangdStore = plangdStore1;
		                	} else if(storeItem == "2") {
		                		plangdStore = plangdStore2;
		                	} else if(storeItem == "3") {
		                		plangdStore = plangdStore3;
		                	} else if(storeItem == "4") {
		                		plangdStore = plangdStore4;
		                	} else if(storeItem == "5") {
		                		plangdStore = plangdStore5;
		                	}
		                	
		                    return {
		                        editable: false,
		                        store: plangdStore,
		                        value: storeItem,
		                        xtype: 'combobox',
								name: 'plan_gd_box[]',
		                        width: 60,
		                	    displayField: 'code_nm',
		                	    valueField: 'code',
		                	    listeners: {
		                	        select: function(combo, record, index) {
		                	        	changePlanGd(grid_rowIndex, combo.getValue());
		                	        }		                	    	
		                	    }
		                    };
		                }
		    		}, {
						text : "보장금액",
						width: 80,
						name: 'benefit',
						align : 'center',
		                menuDisabled: true,
						sortable : false,
		                xtype: 'componentcolumn',
		                renderer: function() { 
		                    return { 
		                        xtype: 'textfield',
								name: 'benefit_box[]',
								readOnly: true
		                    }; 
		                }
					}, {
						text : "보험료",
						width: 60,
						align : 'center',
		                menuDisabled: true,
						sortable : false,
		                xtype: 'componentcolumn',
		                renderer: function() { 
		                    return { 
		                        xtype: 'textfield',
								name: 'premium_box[]',
								readOnly: true,
				                fieldCls: 'premiumFieldBackgroundColor'
		                    }; 
		                }
					}, {
						text : "갱신",
						width: 60,
						name: 'premium_renewal',
						align : 'center',
		                menuDisabled: true,
						sortable : false,
		                xtype: 'componentcolumn',
		                renderer: function() { 
		                    return { 
		                        xtype: 'textfield',
								name: 'premium_renewal_box[]',
								readOnly: true
		                    }; 
		                }
					}, {
						text : "65세시점갱신",
						width: 70,
						name: 'premium_renewal_65',
						align : 'center',
		                menuDisabled: true,
						sortable : false,
		                xtype: 'componentcolumn',
		                renderer: function() { 
		                    return { 
		                        xtype: 'textfield',
								name: 'premium_renewal_65_box[]',
								readOnly: true
		                    }; 
		                }		    		
		    		}
		    ];
	
	var productStore = Ext.create('Ext.data.Store', {
		model:'productModel',
	    remoteSort: true,
		proxy: {
	        type: 'ajax',
	        url: COMMON_URL + '/ajaxCalculatorList',
	        reader: {root: 'result'},
	        simpleSortMode: true
	    },
        sorters: [{
            property: 'op_cd',
            direction: 'ASC'
        }],
		listeners: {
	        load: function(dataStore, rows, bool) {
	    		var form1 = Ext.getCmp('Content').getForm();        	
	    		var grid = Ext.getCmp('productPanel').getSelectionModel();

	    		if (form1.findField("plan_no").getValue!="" && dataStore.data.length=="0" ) {
	    			alert('가입조건에 해당되지않습니다.');
	    			form1.findField("plan_no").setValue("");
	    			form1.findField("plan_period").setValue("");
	    		} else {
	    			Ext.each(dataStore.data.items, function(rec) {
	                	if(rec.data.op_cd == '0') {
	                		grid.select(rec.index, true);           		
	                	}
	    			});
	    		}
	        },
	        scope: this
	    }
	});
	
	var sm = new Ext.selection.CheckboxModel({
		id:'chkbox',
		name:'chkbox',	    	
	    checkOnly: true,
        menuDisabled: true,
		sortable : false,
		//showHeaderCheckbox: false,
	    listeners: {
	    	select: function( me, record, index, eOpts ){
	    		
	    		var grid = Ext.getCmp('productPanel').getSelectionModel();
	    		
	    		var form1 = Ext.getCmp('Content').getForm();
	    		form1.findField("insured_age").setValue(record.data.insured_age);	// 보험료계산시 사용한 나이
	    		form1.findField("insured_sex").setValue(record.data.insured_sex);	// 보험료계산시 사용한 성별
	    		form1.findField("insured_job_gd").setValue(record.data.insured_job_gd);// 보험료계산시 사용한 직업급수
	    		form1.findField("insured_drive_gd").setValue(record.data.insured_drive_gd);// 보험료계산시 사용한 운전급수  
	    		form1.findField("insured_drive_type").setValue(record.data.insured_drive_type);// 보험료계산시 사용한 운전자타입  
	    		form1.findField("insured_building_gd").setValue(record.data.insured_building_gd);// 보험료계산시 사용한 빌딩급수  

				// 지금 선택한 코드가 강제동시가입 코드list에 포하되어있다면..
				if ( form1.findField("plan_no").getValue()=="L4I01" ) {
					
					if ( atonce_prd.match(record.data.prd_cd) ) {
						atonce_prd_cd = getAtoncePrdCd(record.data.prd_cd);	// 지금 막 선택한 코드가 강제동시가입 코드이면 받아오기.
						
						Ext.each(productStore.data.items, function(rec) {
					
							if(rec.data.prd_cd == atonce_prd_cd){
								grid.select(rec.index, true);
							}
						});	
					}
				}
				
				// 지금 선택한 코드가 동시가입불가코드list에 포함되어있는 코드라면..
				if ( isolation_prd.match(record.data.prd_cd) ) {
					var now_select_index  = record.index;
					var now_select_prd_cd = record.data.prd_cd;
					
					Ext.each(productStore.data.items, function(rec) {
						if (me.isSelected(rec.index)) {
							isolation_flag = getIsolationPrdCd(now_select_prd_cd, rec.data.prd_cd);	// 지금 막 선택한 코드, 기존에 선택되어있던 코드(foreach로 계속 됨)
							
							if (isolation_flag==true) {
								grid.deselect(now_select_index, true);

								alert("["+ rec.data.prd_nm_kor +"] 과 동시가입 불가한 담보입니다.");
								isolation_flag = false;

								return false;
							}
							
						} else {
							isolation_flag = false;
							
							if(rec.data.op_cd == record.data.op_cd){
		            			grid.select(rec.index, true);
							}
						}
					});
				} else {
					Ext.each(productStore.data.items, function(rec) {
						if(rec.data.op_cd == record.data.op_cd){
	            			grid.select(rec.index, true);
						}
					});
				}

	    	},
	    	beforedeselect: function( me, record, index, eOpts ){
	    		
	    		if(record.data.op_cd == '0'){
                    Ext.Msg.alert('Notice', '기본담보 는 반드시 선택 되어야 합니다.');
                    return false;
	    		}	
	    		
	    	},
	    	deselect: function( me, record, index, eOpts ){
	    		
	    		var grid = Ext.getCmp('productPanel').getSelectionModel();
	    		
				Ext.each(productStore.data.items, function(rec) {
	            	if(rec.data.op_cd == record.data.op_cd){
            			grid.deselect(rec.index, true);
	            	}

					if ( atonce_prd2.match(record.data.prd_cd) ) {

						atonce2_flag = getAtoncePrdCd_Deselect(record.data.prd_cd, rec.data.prd_cd);	// 지금 막 해제한 코드, 기존에 선택되어있던 코드(foreach로 계속 됨)
						
						if (atonce2_flag==true) {
							grid.deselect(rec.index, true);
							atonce2_flag = false;
						}
					}
				});
				
	    	},
	    	selectionchange: function(me, selected, eOpts ){   
    		
	    		var form1 = Ext.getCmp('Content').getForm();
	    		var grid = Ext.getCmp('productPanel').getSelectionModel();

	    		var arr_benefit_box = document.getElementsByName("benefit_box[]");
	    		var arr_premium_box = document.getElementsByName("premium_box[]");
	    		var arr_premium_renewal_box = document.getElementsByName("premium_renewal_box[]");
	    		var arr_premium_renewal_65_box = document.getElementsByName("premium_renewal_65_box[]");

	    		var benefit_amt = 0;
	    		var premium_amt		  = 0;	//월납
	    		var premium_renewal_total = 0;
	    		var premium_renewal_65_total = 0;
	    		var premium_5per_total	  = 0;
	    		var premium_10per_total   = 0;
	    		
	    		var mr_premium_amt		     = 0;	//MR인 담보만 계산한 월납
	    		var mr_premium_renewal_total = 0;
	    		var mr_premium_renewal_65_total = 0;
	    		var mr_premium_5per_total	 = 0;
	    		var mr_premium_10per_total   = 0;   
	    		
	    		var mr_cnt = 0;
	    		var lumpsum_cnt = 0;
	    		var poa_cnt = 0;
	    		
				Ext.each(productStore.data.items, function(rec) {

					if (me.isSelected(rec.index)) {

	            			arr_benefit_box[rec.index].value         = Ext.util.Format.number(rec.data.benefit, '0,000');
		            		arr_premium_box[rec.index].value         = Ext.util.Format.number(rec.data.premium, '0,000');
		            		arr_premium_renewal_box[rec.index].value = Ext.util.Format.number(rec.data.premium_renewal, '0,000');
		            		
		            		// 의료비담보일 경우에만 65세시점 갱신보험료 보여주기
		            		if ( rec.data.mr!="N" || rec.data.sick_mr=="Y") {
		            			arr_premium_renewal_65_box[rec.index].value = Ext.util.Format.number(rec.data.premium_renewal_65, '0,000');
			            		premium_renewal_65_total = premium_renewal_65_total + parseInt(rec.data.premium_renewal_65);
		            		} else {
		                		arr_premium_renewal_65_box[rec.index].value = Ext.util.Format.number(rec.data.premium, '0,000');
			            		premium_renewal_65_total = premium_renewal_65_total + parseInt(rec.data.premium);
		            		}
		            		
		            		benefit_amt           = benefit_amt           + parseInt(rec.data.benefit);
		            		premium_amt           = premium_amt           + parseInt(rec.data.premium);
		            		premium_renewal_total = premium_renewal_total + parseInt(rec.data.premium_renewal);
		            		

		            		if ( rec.data.mr!="N" || rec.data.sick_mr=="Y") {
		            			mr_cnt++;
		            			
			            		mr_premium_amt         	 = mr_premium_amt         + parseInt(rec.data.premium);
			            		mr_premium_renewal_total = mr_premium_renewal_total + parseInt(rec.data.premium_renewal);
			            		mr_premium_renewal_65_total = mr_premium_renewal_65_total + parseInt(rec.data.premium_renewal_65);
		            		}
		            		
		            		if ( rec.data.lumpsum=="Y" )
		            			lumpsum_cnt++;

		            		if ( rec.data.poa=="Y" )
		            			poa_cnt++;		            		
					} else {

						if(arr_premium_box[rec.index] != undefined && arr_premium_box.length > 0 ) {
		            		arr_benefit_box[rec.index].value         = "";
							arr_premium_box[rec.index].value         = "";
		            		arr_premium_renewal_box[rec.index].value = "";
		            		arr_premium_renewal_65_box[rec.index].value = "";
						}
					}
				});

	        	form1.findField("benefit_amt").setValue(benefit_amt);
            	
				premium_5per_total =  premium_amt + Math.round(premium_amt*0.05);
				premium_10per_total = premium_amt + Math.round(premium_amt*0.1);
				
	        	form1.findField("premium_amt").setValue(Ext.util.Format.number(premium_amt, '0,000'));					//보험료 합계
	        	form1.findField("premium_renewal_total").setValue(Ext.util.Format.number(premium_renewal_total, '0,000'));	//갱신보험료 합계
	        	form1.findField("premium_renewal_65_total").setValue(Ext.util.Format.number(premium_renewal_65_total, '0,000'));
	        	form1.findField("premium_5per_total").setValue(Ext.util.Format.number(premium_5per_total, '0,000'));		//5%할증 합계
	        	form1.findField("premium_10per_total").setValue(Ext.util.Format.number(premium_10per_total, '0,000'));		//10%할증 합계 
            	
            	if ( mr_cnt > 0 ) {
            		form1.findField("mr_cnt").setValue(mr_cnt);
        			
        			mr_premium_5per_total =  mr_premium_amt + Math.round(mr_premium_amt*0.05);
        			mr_premium_10per_total = mr_premium_amt + Math.round(mr_premium_amt*0.1);
            		
                	form1.findField("mr_premium_amt").setValue(Ext.util.Format.number(mr_premium_amt, '0,000'));					//MR보험료 합계 (MR특약건의 보험료만 따로 계산)
                	form1.findField("mr_premium_renewal_total").setValue(Ext.util.Format.number(mr_premium_renewal_total, '0,000'));	//MR갱신보험료 합계
                	form1.findField("mr_premium_renewal_65_total").setValue(Ext.util.Format.number(mr_premium_renewal_65_total, '0,000'));
                	form1.findField("mr_premium_5per_total").setValue(Ext.util.Format.number(mr_premium_5per_total, '0,000'));		//5%할증 합계
                	form1.findField("mr_premium_10per_total").setValue(Ext.util.Format.number(mr_premium_10per_total, '0,000'));		//10%할증 합계
                	
    				Ext.getCmp("btnPresearchMR").setDisabled(false);
            	} else {
            		form1.findField("mr_cnt").setValue("");
            		
            		form1.findField("mr_premium_amt").setValue("");
            		form1.findField("mr_premium_renewal_total").setValue("");
            		form1.findField("mr_premium_renewal_65_total").setValue("");
            		form1.findField("mr_premium_5per_total").setValue("");
            		form1.findField("mr_premium_10per_total").setValue("");
            		
    				Ext.getCmp("btnPresearchMR").setDisabled(true);
            	}
            	
            	if ( lumpsum_cnt > 0 ) {
            		form1.findField("lumpsum_cnt").setValue(lumpsum_cnt);
    				Ext.getCmp("btnPresearchLumpsum").setDisabled(false);
            	} else {
            		form1.findField("lumpsum_cnt").setValue("");
    				Ext.getCmp("btnPresearchLumpsum").setDisabled(true);
            	}
            	
            	if ( poa_cnt > 0 ) {           		
            		form1.findField("poa_cnt").setValue(poa_cnt);
            	} else {
            		form1.findField("poa_cnt").setValue("");
            	}
            	
	    	}
	    }
	});	
	
	var productPanel = {
		xtype: 'grid',
		store: productStore,
		id: 'productPanel',
		width: 605,
		height: 490,
	    //scroll: 'vertical',
		scroll: 'both',
		selModel : sm,
		columns: productColumns,
	    plugins: {
	        ptype: 'cellediting',
	        clicksToEdit: 1
	    }
	};
	// rightPanel에 들어가는 두번째패널 End
	

	
	var leftPanel = Ext.create('Ext.panel.Panel', {	
		id:'leftPanel',
		border: 0,	
		defaults: {anchor: '100%'},
		layout: {
	        type: 'vbox',
	        align: 'stretch',	        
	        padding: '5 5 0 5'
	    },
	    items: [insuHolderPanel, insuInsuredPanel, planPanel, searchPanel]
	});		
	
	var rightPanel = Ext.create('Ext.panel.Panel', {
		border: 0,	
		defaults: {anchor: '100%'},
		layout: {
	        type: 'vbox',
	        align: 'stretch',	        
	        padding: 5
	    },
	    items: [buttonPanel, productPanel]
	});


	var amtPanel = Ext.create('Ext.panel.Panel', {
		id: 'amtPanel',
		border:1,	    
	    width: '100%',
	    margin: '5 0 0 0',
	    layout: {
	        type: 'hbox',
	        align: 'stretch',	        
	        padding: 5
	    },   
	    defaultType: 'textfield',   
	    items: [{
			    	xtype: 'tbfill'
			    }, {
			    	xtype: 'component',
				    html: ['<table width=30 bgcolor=silver border=0><tr><td align=center>Tot</td></tr></table>']		
				}, {
					fieldLabel: '월납', 
					name: 'premium_amt', 
					id: 'premium_amt', 
					labelWidth: 30,
					width:100,
					margin: '0 0 0 10',
			        editable: false,
					readOnly: true
				}, {
					fieldLabel: '갱신', 
					name: 'premium_renewal_total', 
					id: 'premium_renewal_total', 
					labelWidth: 30,
					width:100,
					margin: '0 0 0 10',			                
			        editable: false,
					readOnly: true
				}, {
					fieldLabel: '65세', 
					name: 'premium_renewal_65_total', 
					id: 'premium_renewal_65_total', 
					labelWidth: 35,
					width:105,
					margin: '0 0 0 10',		                
			        editable: false,
					readOnly: true
			    }, { 	
					fieldLabel: '5%', 
					name: 'premium_5per_total',
					id: 'premium_5per_total',
					labelWidth: 30,
					width:100,
					margin: '0 0 0 10',	                
			        editable: false,
					readOnly: true
	            }, {
					fieldLabel: '10%', 
					name: 'premium_10per_total', 
					id: 'premium_10per_total',
					labelWidth: 30,
					width:100,
					margin: '0 0 0 10',			                
			        editable: false,
					readOnly: true
	    		}, {
					xtype:'hiddenfield', 
					name: 'benefit_amt', 
					id: 'benefit_amt'
				}, {
					// 현재보이는 보험료계산시에 사용한 나이
					name: 'insured_age',
					xtype:'hiddenfield'
				}, {
					// 현재보이는 보험료계산시에 사용한 성별
					name: 'insured_sex',
					xtype:'hiddenfield' 	        
				}, {
					// 현재보이는 보험료계산시에 사용한 직업급수
					name: 'insured_job_gd',
					xtype:'hiddenfield'
				}, {
					// 현재보이는 보험료계산시에 사용한 운전급수
					name: 'insured_drive_gd',
					xtype:'hiddenfield' 
				}, {
					// 현재보이는 보험료계산시에 사용한 운전자타입
					name: 'insured_drive_type',
					xtype:'hiddenfield' 
				}, {
					// 현재보이는 보험료계산시에 사용한 빌딩급수
					name: 'insured_building_gd',
					xtype:'hiddenfield' 						
	    		}
		]
	});	

	var mr_amtPanel = Ext.create('Ext.panel.Panel', {
		id:'mr_amtPanel',
		border:1,	    
	    width: '100%',
	    margin: '5 0 0 0',
	    layout: {
	        type: 'hbox',
	        align: 'stretch',	        
	        padding: 5
	    },   
	    defaultType: 'textfield',   
	    items: [{
			    	xtype: 'tbfill'
			    }, {
			    	xtype: 'component',
				    html: ['<table width=30 bgcolor=silver border=0><tr><td align=center style=letter-spacing:1px>MR</td></tr></table>']
				}, {
					fieldLabel: '월납', 
					name: 'mr_premium_amt', 
					labelWidth: 30,
					width:100,
					margin: '0 0 0 10',
			        editable: false,
					readOnly: true
				}, {
					fieldLabel: '갱신', 
					name: 'mr_premium_renewal_total', 
					labelWidth: 30,
					width:100,
					margin: '0 0 0 10',	                
			        editable: false,
					readOnly: true
				}, {
					fieldLabel: '65세', 
					name: 'mr_premium_renewal_65_total', 
					labelWidth: 35,
					width:105,
					margin: '0 0 0 10',			                
			        editable: false,
					readOnly: true	  
			    }, { 	
					fieldLabel: '5%', 
					name: 'mr_premium_5per_total',
					labelWidth: 30,
					width:100,
					margin: '0 0 0 10',		                
			        editable: false,
					readOnly: true
	            }, {
					fieldLabel: '10%', 
					name: 'mr_premium_10per_total', 
					labelWidth: 30,
					width:100,
					margin: '0 0 0 10',			                
			        editable: false,
					readOnly: true
	    		}
		]
	});	
	
	
	Ext.create('Ext.form.Panel', {
		id:'Content',
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'vbox',
	        align: 'stretch',
	        padding: 5
	    },
	    items: [{
					border: 1,
					layout: {
				        type: 'hbox',
				        align: 'stretch'
				    },
				    items: [leftPanel, rightPanel]
				},
				amtPanel, mr_amtPanel
	    ]
	});	


//$('.imgzoom').removeAttr('width');	
//console.log( $('#planPanel table').size() );
//$('#planPanel table:eq(1) div:eq(2)').text();
//console.log( $('div:eq(12)').text() );
// combo.setValue(items[0].get(combo.valueField));	

	/*
	* 상품조회 클릭 실행
	*/
	function productSearch() {

		var form1 = Ext.getCmp('Content').getForm();

		/*
		form1.findField("insu_ssn_no").setValue("5512121");
		form1.findField("insu_birth_date").setValue("5512121");
		form1.findField("insu_age").setValue("60");
		form1.findField("insu_sex").setValue("1");
		form1.findField("txt_insu_sex").setValue(getSexKor("1"));
		form1.findField("insu_occup_cd").setValue("B3303");
		form1.findField("insu_occup_gd").setValue("1");
		form1.findField("insu_drive_gd").setValue("1");
		*/
		var insu_age = form1.findField("insu_age").getValue();					// 연령
		var insu_sex = form1.findField("insu_sex").getValue();					// 성별
		var insu_occup_cd = trim(form1.findField("insu_occup_cd").getValue());	// 직업코드
		var insu_occup_gd = trim(form1.findField("insu_occup_gd").getValue());	// 직업급수
		var insu_drive_gd = trim(form1.findField("insu_drive_gd").getValue());	// 운전급수
		var insu_drive_type= form1.findField("insu_drive_type").getSubmitValue();// 운전종류(운전자타입)
		var insu_building_gd= form1.findField("insu_building_gd").getValue();	// 빌딩급수
		
		var plan_no  = form1.findField("plan_no").getSubmitValue();				// 상품코드
		var plan_period = form1.findField("plan_period").getValue();			// 가입기간
		var insu_rel = form1.findField("insu_rel").getSubmitValue();			// 가입유형	

		if(insu_age == ''){
			focusMsgAlert('Error', '[피보험자 정보] 생년월일 은 필수 입니다.', form1.findField("insu_ssn_no"));
			form1.findField("plan_no").setValue("");
			form1.findField("plan_period").setValue("");
			return false;
		}
		
		if(insu_sex == ''){
			focusMsgAlert('Error', '[피보험자 정보] 성별 은 필수 입니다.', form1.findField("insu_ssn_no"));
			form1.findField("plan_no").setValue("");
			form1.findField("plan_period").setValue("");
			return false;
		}
		insu_sex = getSexEng(insu_sex);	//숫자로 된 성별을 M/F로 변경해줌
		
		if(insu_occup_cd == '' || insu_occup_cd == null){
			focusMsgAlert('Error', '[피보험자 정보] 직업 은 필수 입니다.', form1.findField("insu_occup_nm"));
			form1.findField("plan_no").setValue("");
			form1.findField("plan_period").setValue("");
			return false;
		}
		
		if(insu_occup_gd == '' || insu_occup_gd == null){
			focusMsgAlert('Error', '[피보험자 정보] 직업 은 필수 입니다.', form1.findField("insu_occup_nm"));
			form1.findField("plan_no").setValue("");
			form1.findField("plan_period").setValue("");
			return false;
		}
		
		if(plan_no == ''){
			focusMsgAlert('Error', '[상품정보] 상품 은 필수 입니다.', form1.findField("plan_no"));
			form1.findField("plan_no").setValue("");
			form1.findField("plan_period").setValue("");
			return false;
		}

		if (plan_no == 'L4P01' && (insu_drive_type==' ' || insu_drive_type=='' || insu_drive_type==null)) {
			focusMsgAlert('Error', '[피보험자 정보] 운전종류는 필수입니다.', form1.findField("insu_drive_type"));
			form1.findField("plan_no").setValue("");
			form1.findField("plan_period").setValue("");
			return false;
		}
		if (plan_no == 'L4P01' && insu_drive_type=='2') {
			focusMsgAlert('Error', '[피보험자 정보] 운전종류가 영업일때는 판매불가한 플랜입니다.', form1.findField("insu_drive_type"));
			form1.findField("plan_no").setValue("");
			form1.findField("plan_period").setValue("");
			return false;
		}	

		if (plan_period*1 > 1) {
			Ext.getCmp("btnSwitching").setDisabled(false);
		} else {
			Ext.getCmp("btnSwitching").setDisabled(true);
		}	
		
		if(insu_rel == ''){
			focusMsgAlert('Error', '[상품정보] 가입유형 선택은 필수 입니다.', form1.findField("insu_rel"));
			form1.findField("plan_no").setValue("");
			form1.findField("plan_period").setValue("");
			return false;
		}
		
		// 특약+보장금액+보험료 불러오기
		productStore.load({
			params: { 'insu_age': insu_age
					, 'insu_sex': insu_sex
					, 'insu_occup_cd': insu_occup_cd
					, 'insu_occup_gd': insu_occup_gd
					, 'insu_drive_gd': insu_drive_gd
					, 'insu_drive_type': insu_drive_type
					, 'insu_building_gd': insu_building_gd
					, 'plan_no': plan_no
					, 'insu_rel': insu_rel
			}		
		});

		Ext.getCmp("btnReCal").setDisabled(true);
	}
	

	/*
	* 상품종류(plan_gd) 변경 실행
	*/	
	function changePlanGd(grid_rowIndex, combo_value) {
		$("#loading").show();
		
		var form1 = Ext.getCmp('Content').getForm();
		var grid = Ext.getCmp('productPanel').getSelectionModel();
		
		var plan_no = grid.store.data.items[grid_rowIndex].data.plan_no;
		var prd_cd 	= grid.store.data.items[grid_rowIndex].data.prd_cd;
		var layer_head = grid.store.data.items[grid_rowIndex].data.layer_head;
		var layer_tail = grid.store.data.items[grid_rowIndex].data.layer_tail;
		var cat 	= grid.store.data.items[grid_rowIndex].data.cat;                             
		var band 	= grid.store.data.items[grid_rowIndex].data.band;                           
		var sex 	= grid.store.data.items[grid_rowIndex].data.sex;                            
		var insu_age= grid.store.data.items[grid_rowIndex].data.insured_age;                 
		var age_max = grid.store.data.items[grid_rowIndex].data.age_max;

		var layer	= layer_head + combo_value + layer_tail;

		
		Ext.Ajax.request({
	        url: COMMON_URL + 'ajaxChangePlanGd',
	        params: { 'plan_no'	: plan_no
	        		, 'prd_cd'  : prd_cd
	        		, 'layer'	: layer
	        		, 'cat'		: cat
	        		, 'band'	: band
	        		, 'sex'  	: sex
	        		, 'insu_age': insu_age
	        		, 'age_max'	: age_max
	        },
	        success: function(response){
	    		$("#loading").hide();
	    		
	        	var obj = toJson(response.responseText);

	        	grid.store.data.items[grid_rowIndex].data.plan_gd 		  = combo_value;
	        	grid.store.data.items[grid_rowIndex].data.benefit 		  = obj.result[0].benefit;
	        	grid.store.data.items[grid_rowIndex].data.premium 		  = obj.result[0].premium;
	        	grid.store.data.items[grid_rowIndex].data.premium_renewal = obj.result[0].premium_renewal;
	        	grid.store.data.items[grid_rowIndex].data.premium_renewal_65 = obj.result[0].premium_renewal_65;

	        	// 상품종류 변경전에 체크박스 미리 체크되어있었는지 여부 확인
	        	if ( sm.isSelected(grid_rowIndex) == true ) {
	        		grid.deselect(grid_rowIndex, true);
	        	}	 
	        	grid.select(grid_rowIndex, true);       	
	        },
	        failure: function(result, request) {	
	    		$("#loading").hide();
	    		
	        	Ext.Msg.alert('Error', '등록을 실패하였습니다.');
			}
	    });		
	}

	
	/*
	* 재계산 버튼 활성여부 체크
	*/		
	function reCal_Check() {
		var form1 = Ext.getCmp('Content').getForm();
		var reCal_flag = false;

		var insu_age = form1.findField("insu_age").getValue();					// 피보험자관련 박스에 있는 나이
		var insu_sex = form1.findField("insu_sex").getValue();					// 피보험자관련 박스에 있는 성별
		var insu_occup_gd = trim(form1.findField("insu_occup_gd").getValue());	// 피보험자관련 박스에 있는 직업급수
		var insu_drive_gd = trim(form1.findField("insu_drive_gd").getValue());	// 피보험자관련 박스에 있는 운전급수
		var insu_drive_type = form1.findField("insu_drive_type").getSubmitValue();// 피보험자관련 박스에 있는 운전종류(운전자타입)
		var insu_building_gd= form1.findField("insu_building_gd").getValue();	// 피보험자관련 박스에 있는 빌딩급수
		var plan_no = form1.findField("plan_no").getSubmitValue();				// 상품코드		
		
		var insured_age = form1.findField("insured_age").getValue();			// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 나이
		var insured_sex = form1.findField("insured_sex").getValue();			// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 성별		
		var insured_job_gd 	 = form1.findField("insured_job_gd").getValue();	// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 직업급수
		var insured_drive_gd = form1.findField("insured_drive_gd").getValue();  // [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 운전급수
		var insured_drive_type = form1.findField("insured_drive_type").getValue();	// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 운전자타입
		var insured_building_gd= form1.findField("insured_building_gd").getValue();	// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 빌딩급수		

		if (insured_age!="" && insured_sex!="" && insured_job_gd!="" && insured_drive_gd!="") {
			insu_sex = getSexEng(insu_sex);	//숫자로 된 성별을 M/F로 변경해줌
			
			if (insu_age != insured_age) reCal_flag = true;
			if (insu_sex != insured_sex) reCal_flag = true;
			if (insu_occup_gd != insured_job_gd) reCal_flag = true;
			if (insu_drive_gd != insured_drive_gd) reCal_flag = true;
			if (plan_no=='L4P01' && (insu_drive_type != insured_drive_type)) reCal_flag = true;
			
			if (reCal_flag==true) {
				Ext.getCmp("btnReCal").setDisabled(false);
			} else {
				Ext.getCmp("btnReCal").setDisabled(true);
			}
			
//			if (insu_age != insured_age) {
//				Ext.getCmp("insu_age").setFieldStyle('background-color:red');
//			}
		} else {
			Ext.getCmp("btnReCal").setDisabled(true);
		}
	}


	/*
	* 재계산 실행하기
	*/		
	function reCalSearch() {

		var form1 = Ext.getCmp('Content').getForm();
		var grid  = Ext.getCmp('productPanel').getSelectionModel();
		var arr_plan_gd_box = document.getElementsByName("plan_gd_box[]");

		var insu_birth_date = form1.findField("insu_birth_date").getValue();	// 생년월일
		var insu_age = form1.findField("insu_age").getValue();					// 연령
		var insu_sex = form1.findField("insu_sex").getValue();					// 성별
		var insu_occup_cd = trim(form1.findField("insu_occup_cd").getValue());	// 직업코드
		var insu_occup_gd = trim(form1.findField("insu_occup_gd").getValue());	// 직업급수
		var insu_drive_gd = trim(form1.findField("insu_drive_gd").getValue());	// 운전급수
		var insu_drive_type= form1.findField("insu_drive_type").getSubmitValue();// 운전종류(운전자타입)
		var insu_building_gd= form1.findField("insu_building_gd").getValue();	// 빌딩급수
		
		var plan_no  = form1.findField("plan_no").getSubmitValue();				// 상품코드
		var insu_rel = form1.findField("insu_rel").getSubmitValue();			// 가입유형

		if(insu_age == ''){
			focusMsgAlert('Error', '[피보험자 정보] 생년월일 은 필수 입니다.', form1.findField("insu_ssn_no"));
			return false;
		}
		
		if(insu_sex == ''){
			focusMsgAlert('Error', '[피보험자 정보] 성별 은 필수 입니다.', form1.findField("insu_ssn_no"));
			return false;
		}
		insu_sex = getSexEng(insu_sex);	//숫자로 된 성별을 M/F로 변경해줌
		
		if(insu_occup_cd == '' || insu_occup_cd == null){
			focusMsgAlert('Error', '[피보험자 정보] 직업 은 필수 입니다.', form1.findField("insu_occup_nm"));
			return false;
		}

		if (plan_no == 'L4P01' && (insu_drive_type==' ' || insu_drive_type=='' || insu_drive_type == null)) {
			focusMsgAlert('Error', '[피보험자 정보] 운전종류는 필수입니다.', form1.findField("insu_drive_type"));
			return false;
		}
		if (plan_no == 'L4P01' && insu_drive_type=='2') {
			focusMsgAlert('Error', '[피보험자 정보] 운전종류가 영업일때는 판매불가한 플랜입니다..', form1.findField("insu_drive_type"));
			return false;
		}
		
		var i = 0;
		Ext.each(grid.selected.items, function(rec) {
			selected_prd_cd[i] = rec.data.prd_cd;
			selected_plan_gd[i] = arr_plan_gd_box[rec.index].value.substring(0,1);

			i++;
		});
		
		// 보험료 재계산해서 불러오기
		productStore.load({
			params: { 'insu_age': insu_age
				, 'insu_sex': insu_sex
				, 'insu_occup_cd': insu_occup_cd
				, 'insu_occup_gd': insu_occup_gd
				, 'insu_drive_gd': insu_drive_gd
				, 'insu_drive_type': insu_drive_type
				, 'insu_building_gd': insu_building_gd
				, 'plan_no': plan_no
				, 'insu_rel': insu_rel
			},
			callback: function(records, operation, success) {
				if(success == true) {
		    		reCalPremium();
					Ext.getCmp("btnReCal").setDisabled(true);
		    	} else  {
					Ext.getCmp("btnReCal").setDisabled(false);
		    	}
		    }
		});
	}


	/*
	* 새로 계산한 보험료로 보여주기
	*/	
	var reCalPremium = function() {
    	var grid = Ext.getCmp('productPanel').getSelectionModel();
		var arr_plan_gd_box = document.getElementsByName("plan_gd_box[]");

		Ext.each(productStore.data.items, function(rec) {

			for (var key in selected_prd_cd)
			{
				if (rec.data.prd_cd == selected_prd_cd[key])
				{
					grid.select(rec.index, true);
					arr_plan_gd_box[rec.index].value = selected_plan_gd[key];
					changePlanGd(rec.index , arr_plan_gd_box[rec.index].value);
				}
			}			
		});
	}
	
	
	/*
	* 스크립트창으로 값넘기기
	*/		
	function sendScopePop() {

		openNoScrollWin('/ScopePop', '', '1100', '530')
	}
	
});





/*
* 추가동의 팝업창
*/		
function sendPOAagreePop() {

	var form1	= Ext.getCmp('Content').getForm();	
	var plan_no	= form1.findField("plan_no").getValue();	// 선택한 플랜no
	
	openScrollWin('/POAagreePop?plan_no='+plan_no, 'AddScriptWin', '900', '800')
}


/*
* 녹취스크립트 팝업창 띄우기 체크하기
*/
function checkRecordScript(type) {

	var form1 = Ext.getCmp('Content').getForm();
	
	var insu_policy_no	= form1.findField("insu_policy_no").getValue();	// 설계번호
	var cust_nm			= form1.findField("cust_nm").getValue();		// 계약자 성명	
	var grid			= Ext.getCmp('productPanel').getSelectionModel();// 선택한 담보
	var mr_cnt			= form1.findField("mr_cnt").getValue();		
	var lumpsum_cnt		= form1.findField("lumpsum_cnt").getValue();		
	var poa_cnt			= form1.findField("poa_cnt").getValue();

	if (grid.store.data.length < 1) {
		focusMsgAlert('Error', '[가입 설계] 보험설계는 필수 입니다.', form1.findField("plan_no"));
		return false;
	}

	var plan_no  = form1.findField("plan_no").getSubmitValue();
	
	// 피보험자정보와 가입설계시 사용한 기본정보가 동일한지 체크 
	var insured_age = form1.findField("insured_age").getValue();
	var insured_sex = form1.findField("insured_sex").getValue();
	var insured_job_gd = form1.findField("insured_job_gd").getValue();
	var insured_drive_gd = form1.findField("insured_drive_gd").getValue();
	var insured_drive_type = form1.findField("insured_drive_type").getValue();
	var insured_building_gd = form1.findField("insured_building_gd").getValue();

	// 피보험자정보fild에 있는 피보험자의 나이 VS 보험료계산시 사용한 나이
	if (form1.findField("insu_age").getValue() != insured_age ) {
		focusMsgAlert('Error','재계산 실행 후 클릭해주세요.', form1.findField("insu_ssn_no1"));
		return false;
	}
	// 피보험자정보fild에 있는 피보험자의 성별 VS 보험료계산시 사용한 성별
	if (getSexEng(form1.findField("insu_sex").getValue()) != insured_sex) {
		focusMsgAlert('Error','재계산 실행 후 클릭해주세요.', form1.findField("insu_ssn_no2"));
		return false;
	}
	// 피보험자정보fild에 있는 피보험자의 직업급수 VS 보험료계산시 사용한 직업급수
	if (form1.findField("insu_occup_gd").getValue() != insured_job_gd ) {
		focusMsgAlert('Error','재계산 실행 후 클릭해주세요.', form1.findField("insu_occup_cd"));
		return false;
	}
	// 피보험자정보fild에 있는 피보험자의 운전급수 VS 보험료계산시 사용한 운전급수
	if (form1.findField("insu_drive_gd").getValue() != insured_drive_gd ) {
		focusMsgAlert('Error','재계산 실행 후 클릭해주세요.', form1.findField("insu_occup_cd"));
		return false;
	}
	// 피보험자정보fild에 있는 피보험자의 운전자타입 VS 보험료계산시 사용한 운전자타입
	if (form1.findField("insu_drive_type").getSubmitValue() != insured_drive_type ) {
		focusMsgAlert('Error','재계산 실행 후 클릭해주세요.', form1.findField("insu_drive_type"));
		return false;
	}

	//fncPresearchSWH2(); // MR/정액담보/승환계약 조회여부 확인
	sendRecordScriptPop(type);
}

/*
* 녹취스크립트 팝업창 띄우기
*/	
function sendRecordScriptPop(type) {
	
	var form1	= Ext.getCmp('Content').getForm();
	var poa_cnt			= form1.findField("poa_cnt").getValue();	// 선택된 사망담보 갯수		
	var plan_no			= form1.findField("plan_no").getValue();	// 선택한 플랜no

	destroyPopUps();	// 기존에 열러있는 녹취스크립트창이 있으면 닫기
	
	if (type==1) {
		// 계피 동일
		openScrollWinResizeN('/RecordScriptPop_TypeA?plan_no='+plan_no,   'RecordScriptPop_TypeA',  '900', '800')

	} else {
		if(poa_cnt == 0)
		{
			// 계피 상이
			openScrollWinResizeN('/RecordScriptPop_TypeB_2?plan_no='+plan_no, 'RecordScriptPop_TypeB_2', '900', '800'); //피보험자	
			openScrollWinResizeN('/RecordScriptPop_TypeB_1?plan_no='+plan_no, 'RecordScriptPop_TypeB_1', '900', '800'); //계약자
		}
		else
		{
			var poa_confirm = confirm("사망담보가 포함되어있습니다.\n\n자필서명이 가능하면 [확인], 불가능하면 [취소]를 클릭하세요.");
			if(poa_confirm==true) {
			// 계피 상이
				openScrollWinResizeN('/RecordScriptPop_TypeB_2?plan_no='+plan_no, 'RecordScriptPop_TypeB_2', '900', '800'); //피보험자	
				openScrollWinResizeN('/RecordScriptPop_TypeB_1?plan_no='+plan_no, 'RecordScriptPop_TypeB_1', '900', '800'); //계약자
			} else {
			// 계피 상이_POA
				openScrollWinResizeN('/RecordScriptPop_TypeC_2?plan_no='+plan_no, 'RecordScriptPop_TypeC_2', '900', '800'); //계약자,피보험자	
				openScrollWinResizeN('/RecordScriptPop_TypeC_1?plan_no='+plan_no, 'RecordScriptPop_TypeC_1', '900', '800'); //대리인
			}
		}
	}
}






/*
* [직업/운전] 팝업창에서 급수조회된 값 받아오기
*/	
function setCodeOccup(occup_cd, occup_nm, occup_gd, drive_gd) {
	var form1 = Ext.getCmp('Content').getForm();	
	form1.findField("insu_occup_cd").setValue(occup_cd);
	form1.findField("insu_occup_gd").setValue(occup_gd);
	form1.findField("insu_occup_nm").setValue(occup_nm);
	form1.findField("insu_drive_gd").setValue(drive_gd);
}


/*
* [직업/운전] 입력한 직업코드를 통해 직업명/직업급수/운전급수 받아오기
*/	
function searchJobNM(occup_cd) {
	
	var options = { 
			url         : COMMON_URL + '/ajaxCodeOccup',
			contentType : "application/x-www-form-urlencoded;charset=UTF-8",
			type        : "post",
			dataType    : "json",
			data        : {'class_cd':'3', 'occup_cd':occup_cd},
			success     : function(data, status){

				var form1 = Ext.getCmp('Content').getForm();

				if(data.result.length==1) {
					var obj = data.result[0];
					form1.findField("insu_occup_nm").setValue(obj.occup_nm);
					form1.findField("insu_occup_gd").setValue(obj.occup_gd);
					form1.findField("insu_drive_gd").setValue(obj.drive_gd);
				} else {
    				focusMsgAlert('Error', '[피보험자 정보] 해당 직업코드는 없는 코드 입니다.', form1.findField("insu_occup_cd"));
    				return false;
				}
			}
	};
	
	$.ajax(options);
}


/*
 * 청약서나 가입설계서로 보험료설계정보 밀어넣기 
 */
var target_win	= "";

function inputCalculator(winNM)
{
	//var f = document.Content;
	var form1 = Ext.getCmp('Content').getForm();

	var cust_nm			= form1.findField("cust_nm").getValue();			// 고객이름
	var insu_ssn_no 	= form1.findField("insu_ssn_no").getValue();		// 주민번호앞6자리+성별1자리
	var insu_ssn_no1 	= insu_ssn_no.substring(0,6);						// 주민번호앞6자리
	var insu_ssn_no2 	= insu_ssn_no.substring(6);							// 성별1자리
	var insu_birth_date = form1.findField("insu_birth_date").getValue();	// 생년월일
	var insu_age 		= form1.findField("insu_age").getValue();			// 연령
	var insu_sex 		= form1.findField("insu_sex").getValue();			// 성별
	var txt_insu_sex	= form1.findField("txt_insu_sex").getValue();		// 한글성별
	var insu_occup_nm = trim(form1.findField("insu_occup_nm").getValue());	// 직업명
	var insu_occup_cd = trim(form1.findField("insu_occup_cd").getValue());	// 직업코드
	var insu_occup_gd = trim(form1.findField("insu_occup_gd").getValue());	// 직업급수
	var insu_drive_gd = trim(form1.findField("insu_drive_gd").getValue());	// 운전급수
	var insu_drive_type= form1.findField("insu_drive_type").getSubmitValue();// 운전종류(운전자타입)
	var insu_building_gd= form1.findField("insu_building_gd").getValue();	// 빌딩급수
	
	var plan_no  	  = form1.findField("plan_no").getSubmitValue();		// 상품코드
	var insu_rel 	  = form1.findField("insu_rel").getSubmitValue();		// 가입유형	
	var plan_period   = form1.findField("plan_period").getSubmitValue();	// 기간
	var interest_rate = form1.findField("interest_rate").getSubmitValue();	// 적용이율
	
	if ( winNM == "contractPop" ) {
	// 청약서
		target_win = open('', 'contractPop', 'top=0,left=0,width=10,height=10');
	} else if ( winNM == "insuPlanPop" ) {
	// 가입설계서
		target_win = open('', 'insuPlanPop', 'top=0,left=0,width=10,height=10');
	}

	if( target_win.document.getElementsByName("insu_name").length == 0 ) {
	// 청약서/가입설계서 창이 열려있지않음		
		
		if ( winNM == "contractPop" ) 
		{
			this.focus();
			alert('청약서 팝업을 연 후 다시 클릭해주세요.');
			open('/common/html/self_close.html', 'contractPop', 'top=0,left=0,width=10,height=10');
		} else if ( winNM == "insuPlanPop" ) {
			this.focus();
			alert('가입설계서 팝업을 연 후 다시 클릭해주세요.');
			open('/common/html/self_close.html', 'insuPlanPop', 'top=0,left=0,width=10,height=10');
		}	
		
	} else {
		
		var target_frm	= target_win.Ext.getCmp('Content').getForm();
		
		// 청약서일때
		if ( winNM == "contractPop" ) {
			
			//if (target_frm.findField("insu_ssn_no1").getValue().length!=6 && target_frm.findField("insu_ssn_no2").getValue().length!=7) {
			//	target_frm.findField("insu_ssn_no1").setValue(insu_ssn_no1);	
			//	target_frm.findField("insu_ssn_no2").setValue(insu_ssn_no2);
			//}
			target_frm.findField("insu_rel2").setValue(insu_rel);
			target_frm.findField("interest_rate").setValue(interest_rate);
       		
    		if (plan_no=='L4P01') {
    			if(insu_drive_type == '3'){
        			target_win.Ext.getCmp('insu_drive_yn').setValue("N");
        			target_win.Ext.getCmp('insu_drive_car').setDisabled(true);
        		} else {
        			target_win.Ext.getCmp('insu_drive_yn').setValue("Y");
        			target_win.Ext.getCmp('insu_drive_car').setDisabled(false);
        		}
    		}			
			
		} else if ( winNM == "insuPlanPop" ) {
			target_frm.findField("insu_ssn_no").setValue(insu_ssn_no);
			target_frm.findField("insu_ssn_no1").setValue(insu_ssn_no1);
			target_frm.findField("insu_rel").setValue(insu_rel);
			target_frm.findField("insu_payment_term_cd").setValue(plan_period);
		}
		
		if ( target_frm.findField("insu_name").getValue().length < 2 ) {
			target_frm.findField("insu_name").setValue(cust_nm);
		}
		
		target_frm.findField("insu_birth_date").setValue(insu_birth_date);
		target_frm.findField("insu_age").setValue(insu_age);
		target_frm.findField("insu_sex").setValue(insu_sex);
		target_frm.findField("txt_insu_sex").setValue(txt_insu_sex);
		target_frm.findField("insu_occup_nm").setValue(insu_occup_nm);
		target_frm.findField("insu_occup_cd").setValue(insu_occup_cd);
		target_frm.findField("insu_occup_gd").setValue(insu_occup_gd);
		target_frm.findField("insu_drive_gd").setValue(insu_drive_gd);
		target_frm.findField("insu_drive_type").setValue(insu_drive_type);
		target_frm.findField("insu_building_gd").setValue(insu_building_gd);
		target_frm.findField("plan_no").setValue(plan_no);
		target_frm.findField("plan_period").setValue(plan_period);
		
		target_win.productSearch();

		setTimeout("inputCheck(target_win);", 1000);	
	}
}

function inputCheck(target_win) {	
	var target_grid				= target_win.Ext.getCmp('productPanel').getSelectionModel();
	var target_arr_plan_gd_box	= target_win.document.getElementsByName("plan_gd_box[]");

	var grid  			= Ext.getCmp('productPanel').getSelectionModel();
	var arr_plan_gd_box = document.getElementsByName("plan_gd_box[]");
	
	var selected_items = ",";
	var this_index = "";
	
	Ext.each(grid.selected.items, function(rec) {
		selected_items += rec.index+",";
	});
	
	Ext.each(grid.store.data.items, function(rec) {
		this_index = ","+ rec.index +",";
		
		if( selected_items.indexOf(this_index) > -1 )
		{			
			target_grid.select(rec.index, true);
			target_grid.store.data.items[rec.index].data.plan_gd = arr_plan_gd_box[rec.index].value.substring(0,1);
			target_arr_plan_gd_box[rec.index].value = arr_plan_gd_box[rec.index].value.substring(0,1);
			target_win.changePlanGd(rec.index , arr_plan_gd_box[rec.index].value.substring(0,1));
		}
	});
}






/*
 *	승환조회 팝업창 띄우기 
 */
function switchingPop() {
	
	var form1 = Ext.getCmp('Content').getForm();
	
	var insu_ssn_no = form1.findField("insu_ssn_no").getValue();// 생년월일+성별숫자	
	var insu_ssn_no1 = insu_ssn_no.substring(0,6);
	
	if(insu_ssn_no1.length != 6){
		focusMsgAlert('Error', '[피보험자 정보] 생년월일 은 필수 입니다.', form1.findField("insu_ssn_no"));
		return false;
	}
	form1.findField("insu_ssn_no1").setValue(insu_ssn_no1);		// 주민번호앞6자리
	
	openNoScrollWin('/SwitchingPolicyPop', 'SwitchingPolicyPop', '1200', '590')
}

/*
 *	MR팝업
 */
function mrPop() {
	
	var form1 = Ext.getCmp('Content').getForm();

	var insu_policy_no = form1.findField("insu_policy_no").getValue();
	var plan_no		= form1.findField("plan_no").getValue();
	var insu_ssn_no = form1.findField("insu_ssn_no").getValue();// 생년월일+성별숫자	
	var insu_ssn_no1= insu_ssn_no.substring(0,6);
	var insu_ssn_no2= "";
	var insu_name 	= "";
	var insu_age	 = form1.findField("insu_age").getValue();
	var insu_occup_gd= trim(form1.findField("insu_occup_gd").getValue());

	if(insu_ssn_no1.length != 6){
		focusMsgAlert('Error', '[피보험자 정보] 생년월일 은 필수 입니다.', form1.findField("insu_ssn_no"));
		return false;
	}
	form1.findField("insu_ssn_no1").setValue(insu_ssn_no1);		// 주민번호앞6자리
	
	var MR_URL = COMMON_URL + "/jsp/Insu/Popup/InsuMRForm.jsp?insu_ssn_no1="+insu_ssn_no1+"&insu_name="+insu_name+"&insu_ssn_no2="+insu_ssn_no2+"&insu_policy_no="+insu_policy_no+"&plan_no="+plan_no+"&member_id="+member_id+"&member_nm="+member_nm;
	
	window.open(MR_URL,"mrPop","menubar=no,scrollbars=no,resizable=no,width=1200,height=778");
}

/*
 *	MR팝업
 */
function mePop() {
	
	var form1 = Ext.getCmp('Content').getForm();

	var insu_policy_no = form1.findField("insu_policy_no").getValue();
	var plan_no		= form1.findField("plan_no").getValue();
	var insu_ssn_no = form1.findField("insu_ssn_no").getValue();// 생년월일+성별숫자	
	var insu_ssn_no1= insu_ssn_no.substring(0,6);
	var insu_ssn_no2= "";
	var insu_name 	= "";
	var insu_age	 = form1.findField("insu_age").getValue();
	var insu_occup_gd= trim(form1.findField("insu_occup_gd").getValue());

	if(insu_ssn_no1.length != 6){
		alert("생년월일은 필수 입니다.");		
		return false;
	}
	
	var ME_URL = COMMON_URL + "/jsp/Insu/Popup/InsuLumpsumForm.jsp?insu_name="+insu_name+"&insu_ssn_no1="+insu_ssn_no1+"&insu_ssn_no2="+insu_ssn_no2+"&plan_no="+plan_no+"&insu_policy_no="+insu_policy_no+"&insu_age="+insu_age+"&insu_occup_gd="+insu_occup_gd+"&member_id="+member_id+"&member_nm="+member_nm;
	
	window.open(ME_URL,"mePop","menubar=no,scrollbars=no,resizable=no,width=1200,height=790");	

}

//add by yoon 2015.02.24
function request_KB(){

	//opener.top.headerFrame.toServerMsg("DATASEND;11111;0111;00000");

	
	//prd 서버 적용 시 
//	opener.top.headerFrame.toServerMsg("DATASEND;"+member_id+";0111;00000");
	toServerMsg("DATASEND;"+member_id+";0111;00000");	
//	getInsuPlanForm("K00000545");

}

function response_KB(result_code){

	var arrCode = result_code.split(";");
	
	var r_code = arrCode[0];
	var insu_policy_no = arrCode[1];

	//KB가입설계동의 고객 정보 응답	
	if(r_code == '0000'){
		getInsuPlanForm(insu_policy_no);

	}else if(r_code == '0001'){
		Ext.Msg.alert('Error','[0001] 대상 고객 이 없습니다.');
		return false;
	}else if(r_code == '9000'){
		Ext.Msg.alert('Error','[9000] 내부시스템 오류 입니다.');
		return false;
	}else if(r_code == '9001'){
		Ext.Msg.alert('Error','[9001] 전문 형식 오류 입니다.');
		return false;
	}else if(r_code == '9002'){
		Ext.Msg.alert('Error','[9002] 전문 길이가 불일치 합니다.');
		return false;
	}else{
		Ext.Msg.alert('Error','잘못된 응답 코드 입니다. 관리자에게 문의하세요.');		
		return false;
	}
}

//KB 고객정보 로드 하기 
var getInsuPlanForm = function(insu_policy_no) {

	var store = Ext.create('Ext.data.Store', {
		proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxInsuPolicyForm',
            reader: {
            	type: 'json',
            	root: 'result'
            }
        },
        fields: [
             'insu_policy_no'
             ,'cust_nm'
             ,'cust_no'
             ,'form_trans_status'
             ,'form_trans_date'
             ,'sex'
             ,'birth_date'
             ,'contact_no'
             ,'ssn_no1'
	        ]
    });

	store.load({
	    params: {
	    	insu_policy_no: insu_policy_no
	    	,insu_form_type : 'FT001'
	    },
	    callback: function(records, operation, success) {

	    	if(success == true) {
	    		
	    		var form1 = Ext.getCmp('Content').getForm();
	    		var contract_date = form1.findField("contract_date").getValue();
	    		form1.findField("insu_policy_no").setValue(store.getAt(0).data.insu_policy_no);
	    		form1.findField("cust_no").setValue(store.getAt(0).data.cust_no);
	    		form1.findField("cust_nm").setValue(store.getAt(0).data.cust_nm);
	    		
	    		if(form1.findField("insu_ssn_no").getValue() == "") {
	    			form1.findField("insu_ssn_no").setValue(store.getAt(0).data.ssn_no1+''+store.getAt(0).data.sex);
	    			form1.findField("insu_ssn_no1").setValue(store.getAt(0).data.ssn_no1);
	    			form1.findField("insu_birth_date").setValue(getBirth(store.getAt(0).data.ssn_no1));
	        		form1.findField("insu_age").setValue(insu_age2(getBirth(store.getAt(0).data.ssn_no1),contract_date));
					form1.findField("insu_sex").setValue(store.getAt(0).data.sex);
	        		form1.findField("txt_insu_sex").setValue(getSexKor(store.getAt(0).data.sex));
	    		}
	    	}		    	
	    },
	    scope: this
	});	
}

function formRefresh() {
	
	var form1 = Ext.getCmp('Content').getForm();
	var contract_date = form1.findField("contract_date").getValue();
	form1.findField("insu_policy_no").setValue("");
	form1.findField("cust_no").setValue("");
	form1.findField("cust_nm").setValue("");
	
	form1.findField("insured_age").setValue("");
	form1.findField("insured_sex").setValue("");
	form1.findField("insured_job_gd").setValue("");
	form1.findField("insured_drive_gd").setValue("");
	form1.findField("insu_ssn_no").setValue("");
	form1.findField("insu_ssn_no1").setValue("");
	form1.findField("insu_age").setValue("");
	form1.findField("txt_insu_sex").setValue("");
	form1.findField("insu_birth_date").setValue("");
	form1.findField("insu_sex").setValue("");
	form1.findField("insu_occup_nm").setValue("");
	form1.findField("insu_occup_cd").setValue("");
	form1.findField("insured_type").setValue("");
	form1.findField("insu_occup_gd").setValue("");
	form1.findField("insu_drive_gd").setValue("");
	form1.findField("plan_no").clearValue();
	form1.findField("plan_period").setValue("");
	form1.findField("interest_rate").setValue("");
	form1.findField("mr_cnt").setValue("");
	form1.findField("lumpsum_cnt").setValue("");
	
	var grid = Ext.getCmp('productPanel');
	grid.getStore().removeAll();
	
}
