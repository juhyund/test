Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);

Ext.onReady(function() {

// 부모창에서 선택된 특약과 보험료를 정보추출 Start
	var openFrm		= opener.Ext.getCmp('Content').getForm();
	var openGrid	= opener.Ext.getCmp('productPanel').getSelectionModel();

	var insured_name = "";
	if (openFrm.findField("insu_name")!=null) {
		insured_name = openFrm.findField("insu_name").getValue();	// 피보험자 이름
	}
	var insured_age  = openFrm.findField("insured_age").getValue();	// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 나이
		insured_age	 = insured_age +"세";
	var insured_sex  = openFrm.findField("insured_sex").getValue();	// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 성별	
		insured_sex  = getSexE2K(insured_sex);
	var insured_job  = openFrm.findField("insured_job_gd").getValue();		// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 직업급수
		insured_job	 = insured_job +"급";
	var insured_drive = openFrm.findField("insured_drive_gd").getValue();	// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 운전급수
		insured_drive = insured_drive +"급";

	var arr_plan_gd_box = opener.document.getElementsByName("plan_gd_box[]");
	var arr_benefit_box = opener.document.getElementsByName("benefit_box[]");
	var arr_premium_box = opener.document.getElementsByName("premium_box[]");
	var arr_premium_renewal_box = opener.document.getElementsByName("premium_renewal_box[]");
		
	var plan_no  	= openFrm.findField("plan_no").getSubmitValue();		// [조회]버튼을 눌러서 나온 결과를 보여줄때 사용한 상품코드
	var arr_op_cd 	= new Array();
	var arr_prd_cd  = new Array();
	var arr_prd_nm_kor  = new Array();
	var arr_plan_gd = new Array();
	var arr_premium = new Array();
	var arr_premium_renewal = new Array();
	var arr_benefit = new Array();

	var premium_amt = 0;
	var premium_renewal_total = 0;
	var premium_5per_total = 0;
	var premium_10per_total = 0;
	var mr_premium_amt = 0;
	var mr_premium_renewal_total = 0;
	var mr_premium_5per_total = 0;
	var mr_premium_10per_total = 0;

	var sendData = "";
	
	var selected_items = ",";
	Ext.each(openGrid.selected.items, function(rec) {
		selected_items += rec.index+",";
	});
	
	var i = 0;
	var this_index = "";
	Ext.each(openGrid.store.data.items, function(rec) {
		
		this_index = ","+ rec.index +",";
		
		if( selected_items.indexOf(this_index) != -1 )
		{
			arr_op_cd[i]		  = String(rec.data.op_cd);
			arr_prd_cd[i]		  = rec.data.prd_cd;
			arr_prd_nm_kor[i]	  = rec.data.prd_nm_kor;
			arr_plan_gd[i]		  = arr_plan_gd_box[rec.index].value.substring(0,1);
			arr_benefit[i]		  = arr_benefit_box[rec.index].value.replace(/\,/g,'');
			arr_premium[i]		  = arr_premium_box[rec.index].value.replace(/\,/g,'');
			arr_premium_renewal[i]= arr_premium_renewal_box[rec.index].value.replace(/\,/g,'');
			
			premium_amt 		  += parseInt(arr_premium[i]);
			premium_renewal_total += parseInt(arr_premium_renewal[i]);
			
			if (rec.data.mr!="N" || rec.data.sick_mr=="Y") {
				mr_premium_amt			 += parseInt(arr_premium[i]);
				mr_premium_renewal_total += parseInt(arr_premium_renewal[i]);			
			}
			
			i++;		
		}
	});
	sendData = arr_prd_cd.join(",");
	
	premium_5per_total  = premium_amt + Math.round(premium_amt*0.05);
	premium_10per_total = premium_amt + Math.round(premium_amt*0.1);

	mr_premium_5per_total  = mr_premium_amt + Math.round(mr_premium_amt*0.05);
	mr_premium_10per_total = mr_premium_amt + Math.round(mr_premium_amt*0.1);	
// 부모창에서 선택된 특약와 보험료 정보추출 End	

	
// 피보험자정보 Start
	var insuredPanel = Ext.create('Ext.panel.Panel', {		
		id: 'insuredPanel',
		border: 0,
		width:500,
        layout: 'anchor',
	    items:[{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',            
	            defaultType: 'displayfield',
			    fieldDefaults: {		            
		    	 	labelAlign: 'center',
		            labelStyle: formLabelStyle,
		            labelSeparator: ""
			    },
			    items: [{        
					        fieldLabel: '이름',
			                value: insured_name,
					        labelWidth: 40,
					        width:150
			            }, {
					        fieldLabel: '연령',
			                value: insured_age,
					        labelWidth: 40,
					        width:80,
			                margin: '0 0 0 10'
			            }, {
			                fieldLabel:'성별',
			                value: insured_sex,
					        labelWidth: 40,
					        width:80,
			                margin: '0 0 0 10'
			            }, {
			                fieldLabel:'직업',
			                value: insured_job,
					        labelWidth: 40,
					        width:80,
			                margin: '0 0 0 10'
			            }, {
			                fieldLabel:'운전',
			                value: insured_drive,
					        labelWidth: 40,
					        width:80,
			                margin: '0 0 0 10'
					    }]
	    }]
	});	
// 피보험자정보 End	
	
// 선택된 특약+보험료 Start
    Ext.define('productModel', {
        extend: 'Ext.data.Model',
        fields: [
    	        'op_cd'     ,		//필수담보 및 선택담보
    	        'prd_cd'    ,		//특약번호
    	        'prd_nm_kor',		//특약명
    	        'plan_gd'   ,		//상품종류
    	        'benefit'	,		//보장금액   
    	        'premium'   ,		//보험료
    	        'premium_renewal'	//갱신보험료
        ]
    });	
    
    var productColumns = [
                          {xtype: 'rownumberer', header : 'No', align: 'center', width: 30},
                          {
                        	  dataIndex : 'op_cd',
                        	  text : "선택",
                        	  width : 60,
                        	  align : 'center',
                        	  menuDisabled: true,
                        	  sortable : true,
							  renderer: function(storeItem) {
								var text = '';
							
								if(storeItem == '0'){
									text = '필수';
								} else {
									text = '선택'+ storeItem;
								}
								return text;
							  }
                          }, {
                        	  dataIndex : 'prd_nm_kor',
                        	  text : "특약명",	
                        	  width: 190,		
                        	  align : 'left',
                        	  menuDisabled: true,
                        	  sortable : false
                          }, {
                        	  dataIndex: 'plan_gd',
                        	  header: '판매',
                        	  width: 40,
                        	  align: 'center',
                        	  menuDisabled: true,
                        	  sortable: false,
							  renderer: function(storeItem) {
								  return storeItem +'형';
							  }
                          }, {
                        	  dataIndex: 'benefit',
                        	  text : "보장금액",
                        	  width: 75,
                        	  align : 'right',
                        	  menuDisabled: true,
                        	  sortable : false,
							  renderer: function(storeItem) {
								return Ext.util.Format.number(storeItem, '0,000');
							  }
                          }, {
                        	  dataIndex: 'premium',
                        	  text : "보험료",
                        	  width: 55,
                        	  align : 'right',
                        	  menuDisabled: true,
    						  sortable : false,
							  renderer: function(storeItem) {
									return Ext.util.Format.number(storeItem, '0,000');
							  }
                          }, {
                        	  dataIndex: 'premium_renewal',
                        	  text : "갱신",
                        	  width: 50,
                        	  align : 'right',
                        	  menuDisabled: true,
                        	  sortable : false,
							  renderer: function(storeItem) {
									return Ext.util.Format.number(storeItem, '0,000');
							  }	    		
                          }
    			    ];
    
	var productStore = Ext.create('Ext.data.Store', {
		model:'productModel',
		traditional:true,	    
		proxy: {
	        type: 'ajax',
	        url: COMMON_URL + '/ajaxScope',
	        reader: {root: 'result'},
	        simpleSortMode: true,
	        extraParams: {
			        	  'plan_no'			: plan_no
		        		, 'arr_prd_cd'  	: arr_prd_cd
		        		, 'arr_prd_nm_kor'  : arr_prd_nm_kor
		        		, 'arr_op_cd'		: arr_op_cd
		        		, 'arr_plan_gd'		: arr_plan_gd
		        		, 'arr_premium'		: arr_premium
		        		, 'arr_premium_renewal' : arr_premium_renewal
		        		, 'arr_benefit' 	: arr_benefit
	        }
	    },
        autoLoad: true
	}); 
	
	var productPanel = {
			id: 'productPanel',
			store: productStore,
			xtype: 'grid',
			width: 500,
			height: 400,
			scroll: 'both',
			columns: productColumns,
		    plugins: {
		        ptype: 'cellediting',
		        clicksToEdit: 1
		    }
		};  
// 선택된 특약+보험료 End  

// 보험료합계 Start
	var amtPanel = Ext.create('Ext.panel.Panel', {		
		id: 'amtPanel',
		border: 1,
		width: 500,
	    margin: '5 0 2 0',
	    layout: {
	        type: 'hbox',
	        align: 'stretch',	        
	        padding: 5
	    },
	    defaultType: 'displayfield',          
	    items: [{
					xtype: 'tbfill'			
			    }, { 	
					id: 'premium_5per_total',
					value: premium_5per_total,
					fieldLabel: '5%할증', 
					labelWidth: 55,
					renderer: function(premium_5per_total) {
						return Ext.util.Format.number(premium_5per_total, '0,000');
					}
	            }, {
					id: 'premium_10per_total',
					value: premium_10per_total,
					fieldLabel: '10%할증', 
					labelWidth: 63,
					margin: '0 0 0 10',
					renderer: function(premium_10per_total) {
						return Ext.util.Format.number(premium_10per_total, '0,000');
					}
	    		}, {
					id: 'premium_renewal_total',
					value: premium_renewal_total,
					fieldLabel: '갱신보험료', 
					labelWidth: 70,
					margin: '0 0 0 10',
					renderer: function(premium_renewal_total) {
						return Ext.util.Format.number(premium_renewal_total, '0,000');
					}
	    		}, {
					id: 'premium_amt',
					value: premium_amt,
					fieldLabel: '월납보험료', 
					labelWidth: 70,	
					margin: '0 0 0 10',
					renderer: function(premium_amt) {
						return Ext.util.Format.number(premium_amt, '0,000');
					}
	    }]
	});
// 보험료합계 End

// MR보험료합계 Start
	var mr_amtPanel = Ext.create('Ext.panel.Panel', {		
		id: 'mr_amtPanel',
		border: 1,
		width: 500,
	    margin: '5 0 2 0',
	    layout: {
	        type: 'hbox',
	        align: 'stretch',	        
	        padding: 5
	    },
	    defaultType: 'displayfield',          
	    items: [{
					xtype: 'tbfill'			
			    }, { 	
					id: 'mr_premium_5per_total',
					value: mr_premium_5per_total,
					fieldLabel: 'MR5%', 
					labelWidth: 55,
					renderer: function(mr_premium_5per_total) {
						return Ext.util.Format.number(mr_premium_5per_total, '0,000');
					}
	            }, {
					id: 'mr_premium_10per_total',
					value: mr_premium_10per_total,
					fieldLabel: 'MR10%', 
					labelWidth: 63,
					margin: '0 0 0 10',
					renderer: function(mr_premium_10per_total) {
						return Ext.util.Format.number(mr_premium_10per_total, '0,000');
					}
	    		}, {
					id: 'mr_premium_renewal_total',
					value: mr_premium_renewal_total,
					fieldLabel: 'MR갱신', 
					labelWidth: 70,
					margin: '0 0 0 10',
					renderer: function(mr_premium_renewal_total) {
						return Ext.util.Format.number(mr_premium_renewal_total, '0,000');
					}
	    		}, {
					id: 'mr_premium_amt',
					value: mr_premium_amt,
					fieldLabel: 'MR월납', 
					labelWidth: 70,	
					margin: '0 0 0 10',
					renderer: function(mr_premium_amt) {
						return Ext.util.Format.number(mr_premium_amt, '0,000');
					}
	    }]
	});
// MR보험료합계 End

	
// leftContent Start 
	Ext.create('Ext.form.Panel', {
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: 'leftContent',
	    layout: {
	        type: 'vbox',
	        align: 'stretch',
	        padding: 5
	    },
	    items: [{
					border: 1,
					defaults: {anchor: '100%'},
					layout: {
				        type: 'vbox',
				        align: 'stretch',	        
				        padding: 5
				    },
				    items:[insuredPanel, productPanel, amtPanel, mr_amtPanel]
				}
	    ]
	});	
// leftContent End
	

// rightContent Start
// 담보안내 Start
	Ext.Ajax.request({
        url	  : COMMON_URL + '/ajaxScopeList',
        params: { plan_no	: plan_no
        		, sendData  : sendData
        },
        success: function(response){
        	var obj = toJson(response.responseText);
        	var op_text = "";
        	var title = "";
        	
			Ext.each(obj.result, function(rec) {

				if (rec.op_cd=='0') {
					op_text = '필수';
				} else {
					op_text = '선택'+ rec.op_cd ;
				}
				title = '['+ op_text +'] '+ rec.prd_nm_kor;

			    new Ext.panel.Panel({
			        renderTo: 'rightContent',
			        margin: '5 5 5 5',
			        bodyPadding: 5,
			        title: title,
//			        tpl: ['<p>Location: {prd_nm_kor}</p>'],
//			        tbar: [{
//			            text: rec.prd_nm_kor,
//			            handler: function() {
//			                this.up('panel').update(data);
//			            }
//			        }],
			        html: '<p>'+ rec.prd_scope +'</p>'
			    });

			});
        },
        failure: function(result, request) {	
        	Ext.Msg.alert('Error', '실패하였습니다.');
		}
    });		
// 담보안내 End
// rightContent End

});
