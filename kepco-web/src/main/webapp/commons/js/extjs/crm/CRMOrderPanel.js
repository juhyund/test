/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMOrderPanel.js
* @Author : kyunghee.yoon
* @Date : 2015.10.30
**************************************/
Ext.define('OrderDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'prd_type'
        , 'free_cost_yn'  
        , 'order_no'
     	, 'prd_no'
     	, 'prd_nm'
     	, 'prd_cate1'
     	, 'prd_cate1_nm'
     	, 'service_no'
     	, 'price'
     	, 'qty'
     	, 'cost_amt'
    ]
});


// 주문조회
var orderStore = Ext.create('Ext.data.Store', {    
    model: 'OrderDataThread'
});

var orderSm = new Ext.selection.CheckboxModel({		
	name:'chkbox',	    	
    checkOnly: true,
    menuDisabled: true,
	sortable : false,
    listeners: {
    	selectionchange: function(me, selected, eOpts) {
    	}
    }
});

// 주문정보
var orderListPanel = {
	xtype: 'grid',
	id: 'orderGrid',
	name: 'orderGrid',
	border: 0,
	height: 246,
	flex: 1,
    store: orderStore, 
    selModel: orderSm,
    columns: [
        { text: '구분', dataIndex: 'prd_type', width:40, renderer: getPrdTypeNm},        
		{ text: '제품자재품목', dataIndex: 'prd_cate1_nm', align:'center'},
		{ text: '제품자재명', dataIndex: 'prd_nm', align:'center', flex: 1},
		{ text: '단가', dataIndex: 'price', align:'right', width:90, renderer: Ext.util.Format.numberRenderer('0,000')},
		{ text: '수량', dataIndex: 'qty', align:'right', width:50, renderer: Ext.util.Format.numberRenderer('0,000')},
		{ text: '가격', dataIndex: 'cost_amt', align:'right', width:90, renderer: Ext.util.Format.numberRenderer('0,000')}
    ],
    bbar : [{
		xtype: 'button',
		id: 'btnOrderAdd',
		text: '추가',
		iconCls: 'icon-add',
		tooltip: 'add',
		disabled: true,
		handler: function() {	    	 
			
			var form = productFormPanel.getForm();
			var cform = custInfoFormPanel.getForm();
			
			var site = form.findField("site").getSubmitValue();
			var prd_cate1 = form.findField("prd_cate1").getSubmitValue();
			var prd_cate2 = form.findField("prd_cate2").getSubmitValue();
			var prd_no = form.findField("prd_no").getSubmitValue();
			var cust_no = cform.findField("cust_no").getValue();
			
			if(cust_no == "") {
				Ext.Msg.alert('Notice', "고객정보를 먼저 선택해 주세요!");
				return;
			}
			
			if(prd_no == "") {
				Ext.Msg.alert('Notice', "보유제품을 먼저 선택해 주세요!");
				return;
			}
			
			searchPrdWin(site, prd_cate1, prd_cate2, prd_no, 'addOrderInfo');			
		}
	}, {
	    xtype: 'button',
	    id: 'btnOrderRemove',
	    text: '삭제',
	    iconCls: 'icon-remove',
	    tooltip: 'delete',
	    disabled: true,
	    handler: function() {
	    	removeOrderInfo();
	    }
	}, '->', 
	'택배비추가 : ',
	{
	    xtype: 'checkbox',
	    id: 'parcel_service_yn',
	    name: 'parcel_service_yn',
	    inputValue: 'Y',
	    listeners: {
        	change : function(t, newValue, oldValue, eOpts) {   		          		
        		calcOrderAmt();
        	}
        }
	},
	'     ',
	'총 주문금액 : ', 
	{
	     xtype: 'numberfield',
	     id: 'totalOrderAmt',
	     name: 'totalOrderAmt',
	     fieldStyle: 'text-align: right;',	     
	     value:0,
	     hideTrigger: true,
	     readOnly: true,
	     editable: false
	}, '원']
};


Ext.define('ASDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'prd_type'
        , 'free_cost_yn'
        , 'order_no'
     	, 'prd_no'
     	, 'prd_nm'
     	, 'prd_cate1'
     	, 'prd_cate1_nm'
     	, 'service_no'
     	, 'price'
     	, 'qty'
     	, 'cost_amt'
    ]
});

// AS STORE
var asStore = Ext.create('Ext.data.Store', {    
    model: 'ASDataThread'
});

var asSm = new Ext.selection.CheckboxModel({		
	name:'chkbox',	    	
    checkOnly: true,
    menuDisabled: true,
	sortable : false,
    listeners: {
    	selectionchange: function(me, selected, eOpts) {
    	}
    }
});

// AS자재정보
var asListPanel = {
	xtype: 'grid',
	id: 'asGrid',
	name: 'asGrid',
	border: 0,
	height: 246,
	flex: 1,
    store: asStore, 
    selModel: asSm,
    columns: [
        { text: '구분', dataIndex: 'prd_type', width:40, renderer: getPrdTypeNm},        
		{ text: '자재품목', dataIndex: 'prd_cate1_nm', align:'center'},
		{ text: '자재이름', dataIndex: 'prd_nm', align:'center', flex: 1},
		{ text: '단가', dataIndex: 'price', align:'right', width:90, renderer: Ext.util.Format.numberRenderer('0,000')},
		{ text: '수량', dataIndex: 'qty', align:'right', width:50, renderer: Ext.util.Format.numberRenderer('0,000')},
		{ text: '가격', dataIndex: 'cost_amt', align:'right', width:90, renderer: Ext.util.Format.numberRenderer('0,000')}
    ],
    bbar : [{
		xtype: 'button',
		id: 'btnAsAdd',
		text: '추가',
		iconCls: 'icon-add',
		tooltip: 'add',
		disabled: true,
		handler: function() {	    	 
			
			var form = productFormPanel.getForm();
			var cform = custInfoFormPanel.getForm();
	 
			var site = form.findField("site").getSubmitValue();
			var prd_cate1 = form.findField("prd_cate1").getSubmitValue();
			var prd_cate2 = form.findField("prd_cate2").getSubmitValue();
			var prd_no = form.findField("prd_no").getSubmitValue();
	 		var cust_no = cform.findField("cust_no").getValue();
			
			if(cust_no == "") {
				Ext.Msg.alert('Notice', "고객정보를 먼저 선택해 주세요!");
				return;
			}
			
			if(prd_no == "") {
				Ext.Msg.alert('Notice', "보유제품을 먼저 선택해 주세요!");
				return;
			}
			
			searchPrdWin(site, prd_cate1, prd_cate2, prd_no, 'addAsInfo');
		}
	}, {
	    xtype: 'button',
	    id: 'btnAsRemove',
	    text: '삭제',
	    iconCls: 'icon-remove',
	    tooltip: 'delete',
	    disabled: true,
	    handler: function() {
	    	removeAsInfo();
	    }
	}, '->',
	'총 자재사용금액 : ', 
	{
	     xtype: 'numberfield',
	     id: 'totalASAmt',
	     name: 'totalASAmt',
	     fieldStyle: 'text-align: right;',	     
	     value:0,
	     hideTrigger: true,
	     readOnly: true,
	     editable: false
	}, '원']
};

var orderAddrForm1Panel = new Ext.form.Panel({
	border: 0, 	
    defaultType: 'textfield',
    bodyPadding: 7,
    fieldDefaults: {		            
    	labelAlign: 'center',
        labelWidth: 80,
        labelSeparator: "",
        enableKeyEvents: true
    },
    defaults: {anchor: '100%'},
    items: [{
        	xtype: 'hiddenfield',
    		name: 'delivery1_type',
    		value: '1'
        }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',  
        defaultType: 'textfield',
        items: [{
        	name: 'delivery1_owner_nm',
        	fieldLabel: '수령자',
            flex:1
        }, {
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            margins: '0 0 0 7',
            flex: 1,
            items: [{
                xtype: 'radiogroup',
                defaults: {
                    name: 'delivery1_owner_type'
                },
                flex: 1,
                items: [{
                    inputValue: '1',
                    boxLabel: '고객',
                    checked: true
                }, {
                    inputValue: '2',
                    boxLabel: '대행업체'
                }, {
                    inputValue: '3',
                    boxLabel: '로드샵'
                }]
            }]
	    }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',         
        defaultType: 'textfield',
        items: [{
        	name: 'delivery1_tel_mobile',
        	fieldLabel: '휴대번호',
            flex:1
        }, {
        	name: 'delivery1_tel_home',
        	fieldLabel: '전화번호',
            flex:1,
            margin: '0 0 0 7'
        }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox', 
        defaultType: 'textfield',
        fieldLabel: '수령지 주소',
        items: [{
            name: 'delivery1_zipcode',
            width: 60,
            readOnly: true,
            editable: false
        }, {
	    	xtype: 'button',
	    	iconCls: 'icon-search',
	    	margin: '0 0 0 5',
	    	handler: function() {
	    		zipcode('setOrderAddr1');
	    	}
	    }, {
            name: 'delivery1_address1',
            flex: 1,
            readOnly: true,
            editable: false,
            padding: '0 0 0 5'
        }]
    }, {
        fieldLabel: '상세주소',
        name: 'delivery1_address2'
    }, {
        fieldLabel: '비고',
        name: 'delivery1_remark'
    }]
});

var orderAddrForm2Panel = new Ext.form.Panel({
	border: 0, 	
    defaultType: 'textfield',
    bodyPadding: 7,
    fieldDefaults: {		            
    	labelAlign: 'center',
        labelWidth: 80,
        labelSeparator: "",
        enableKeyEvents: true
    },
    defaults: {anchor: '100%'},
    items: [{
    	xtype: 'hiddenfield',
		name: 'delivery2_type',
		value: '2'
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',  
        defaultType: 'textfield',
        items: [{
        	name: 'delivery2_owner_nm',
        	fieldLabel: '수거자',
            flex:1
        }, {
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            margins: '0 0 0 7',
            flex: 1,
            items: [{
                xtype: 'radiogroup',
                defaults: {
                    name: 'delivery2_owner_type'
                },
                flex: 1,
                items: [{
                    inputValue: '1',
                    boxLabel: '고객',
                    checked: true
                }, {
                    inputValue: '2',
                    boxLabel: '대행업체'
                }, {
                    inputValue: '3',
                    boxLabel: '로드샵'
                }]
            }]
	    }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',         
        defaultType: 'textfield',
        items: [{
        	name: 'delivery2_tel_mobile',
        	fieldLabel: '휴대번호',
            flex:1
        }, {
        	name: 'delivery2_tel_home',
        	fieldLabel: '전화번호',
            flex:1,
            margin: '0 0 0 7'
        }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox', 
        defaultType: 'textfield',
        fieldLabel: '수거지 주소',
        items: [{
            name: 'delivery2_zipcode',
            width: 60,
            readOnly: true,
            editable: false
        }, {
	    	xtype: 'button',
	    	iconCls: 'icon-search',
	    	margin: '0 0 0 5',
	    	handler: function() {
	    		zipcode('setOrderAddr2');
	    	}
	    }, {
            name: 'delivery2_address1',
            flex: 1,
            readOnly: true,
            editable: false,
            padding: '0 0 0 5'
        }]
    }, {
        fieldLabel: '상세주소',
        name: 'delivery2_address2'
    }, {
        fieldLabel: '비고',
        name: 'delivery2_remark'
    }]
});


//주문정보검색 TAB PANEL
var orderAddrTabPanel = new Ext.tab.Panel({
	flex: 1,
	padding: '10 0 0 0',
	layout: {
        type: 'vbox',
        align: 'stretch'
    },
    items: [{
	    title: '수령지',
	    flex: 1,
	    items: [orderAddrForm1Panel]
	}, {
	    title: '수거지',
	    flex: 1,
	    items: [orderAddrForm2Panel]
	}]
});

// 주문정보검색 TAB PANEL
var orderTabPanel = new Ext.tab.Panel({	 	
	border: 1,
	padding: '10 0 0 0',
	height: 284,		
	layout: {
        type: 'vbox',
        align: 'stretch'
    },
    items: [{
	    title: '주문정보',	    
	    items: [orderListPanel]
	}, {
	    title: 'AS자재사용정보',
	    items: [asListPanel]
	}]
});

function setOrderAddr1(zipcode, address1) {
	
	var form = orderAddrForm1Panel.getForm();
	
	form.findField("delivery1_zipcode").setValue(zipcode);
	form.findField("delivery1_address1").setValue(address1);
}

function setOrderAddr2(zipcode, address1) {
	
	var form = orderAddrForm2Panel.getForm();
	
	form.findField("delivery2_zipcode").setValue(zipcode);
	form.findField("delivery2_address1").setValue(address1);
}

// 주문추가
function addOrderInfo(records) {
	
	var _record = Ext.JSON.decode(records);
	
	for(var i = 0; i < _record.length; i++) {
		orderStore.add(_record[i]);
	}
	
	calcOrderAmt();
}

// AS추가
function addAsInfo(records) {
	
	var _record = Ext.JSON.decode(records);
	
	for(var i = 0; i < _record.length; i++) {
		asStore.add(_record[i]);
	}
	
	calcOrderAmt();
}

// 주문삭제
function removeOrderInfo() {
	
	var grid = Ext.getCmp("orderGrid").getSelectionModel();
	var selections = grid.getSelection();
	
	for(var i = 0; i < selections.length; i++) {
		var selectedIndex = grid.store.indexOf(selections[i]);
		grid.store.removeAt(selectedIndex);
	}
	
	calcOrderAmt();
}

//AS삭제
function removeAsInfo() {
	
	var grid = Ext.getCmp("asGrid").getSelectionModel();
	var selections = grid.getSelection();
	
	for(var i = 0; i < selections.length; i++) {
		var selectedIndex = grid.store.indexOf(selections[i]);
		grid.store.removeAt(selectedIndex);
	}
	
	calcOrderAmt();
}

//주문금액 계산
function calcOrderAmt() {
	
	var form = serviceFormPanel.getForm();
	var service_type = form.findField("service_type").getValue();
	var free_cost_yn = form.findField("free_cost_yn").getSubmitValue();
	
	var totalOrderAmt = 0;
	var totalASAmt = 0;
	var len = orderStore.getCount();
	var len2 = asStore.getCount();
	
	if(service_type == SERVICE_CODE_AS || service_type == SERVICE_CODE_ORDER || service_type == SERVICE_CODE_SALES) { // AS, 주문, 보상판매
		
		if(free_cost_yn == "Y") { // 무상
			
			form.findField("payment_amt").setValue(0);
			form.findField("order_amt").setValue(0);
			form.findField("as_amt").setValue(0);
			
			Ext.getCmp("totalOrderAmt").setValue(0);
			Ext.getCmp("totalASAmt").setValue(0);	
			
		} else { // 유상
	
			for(var i = 0; i < len; i++) {
				var record = orderStore.getAt(i);
				totalOrderAmt = totalOrderAmt + Number(record.get("cost_amt"));		
			}
			
			for(var i = 0; i < len2; i++) {
				var record = asStore.getAt(i);
				totalASAmt = totalASAmt + Number(record.get("cost_amt"));		
			}
			
			var form = Ext.getCmp("serviceFormPanel").getForm();
			
			// 택배비 추가
			if(Ext.getCmp("parcel_service_yn").getValue() == true) {
				totalOrderAmt = totalOrderAmt + parcelServiceAmt;
			} 
			
			form.findField("payment_amt").setValue(totalOrderAmt + totalASAmt);
			form.findField("order_amt").setValue(totalOrderAmt);
			form.findField("as_amt").setValue(totalASAmt);
			
			Ext.getCmp("totalOrderAmt").setValue(totalOrderAmt);
			Ext.getCmp("totalASAmt").setValue(totalASAmt);
		}
		
	} else {
		
		form.findField("payment_amt").setValue(0);
		form.findField("order_amt").setValue(0);
		form.findField("as_amt").setValue(0);
		
		Ext.getCmp("totalOrderAmt").setValue(0);
		Ext.getCmp("totalASAmt").setValue(0);	
	}
}