// 주문조회
Ext.define('OrderDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'prd_type'
        , 'prd_type_nm'  
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
     	, 'insert_id'
     	, 'insert_nm'
    ]
});

var orderStore = Ext.create('Ext.data.Store', {    
    model: 'OrderDataThread'
});

// AS조회
Ext.define('AsDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'prd_type'
        , 'prd_type_nm'  
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
     	, 'insert_id'
     	, 'insert_nm'
    ]
});


var asStore = Ext.create('Ext.data.Store', {    
    model: 'AsDataThread'
});

//배송조회
Ext.define('DeliveryDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'service_no'
        , 'delivery_no'  
        , 'delivery_type'  
        , 'delivery_agency'
      	, 'delivery_owner_type'
      	, 'delivery_owner_nm'
      	, 'delivery_status'
      	, 'invoice_no'
      	, 'tel_mobile'
      	, 'tel_home'
      	, 'zipcode'
      	, 'address1'
      	, 'address2'
      	, 'remark'
      	, 'insert_id'
      	, 'insert_dt'
    ]
});

var deliveryStore = Ext.create('Ext.data.Store', {    
    model: 'DeliveryDataThread'
});

// 수거조회
Ext.define('PickupDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'service_no'
        , 'delivery_no'  
        , 'delivery_type'  
        , 'delivery_agency'
     	, 'delivery_owner_type'
     	, 'delivery_owner_nm'
     	, 'delivery_status'
     	, 'invoice_no'
     	, 'tel_mobile'
     	, 'tel_home'
     	, 'zipcode'
     	, 'address1'
     	, 'address2'
     	, 'remark'
     	, 'insert_id'
     	, 'insert_dt'
    ]
});

var pickupStore = Ext.create('Ext.data.Store', {    
    model: 'PickupDataThread'
});

// 결제내역정보
Ext.define('PaymentDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'payment_no'
        , 'service_no'  
        , 'payment_type'  
        , 'payment_type_nm'
     	, 'payment_status'
     	, 'payment_status_nm'
     	, 'payment_amt'
     	, 'payment_dt'
     	, 'account_no'
     	, 'credit_card_no'
     	, 'valid_date'
     	, 'payment_auth_no'
     	, 'remark'
     	, 'insert_id'
     	, 'insert_dt'
     	, 'update_id'
     	, 'update_dt'
    ]
});

var paymentStore = Ext.create('Ext.data.Store', {    
    model: 'PaymentDataThread'
});


// 서비스이관이력
Ext.define('TransDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'service_no'
        , 'trans_seq_no'  
        , 'service_status'  
        , 'service_dept_cd'
     	, 'service_dept_nm'
     	, 'service_member_id'
     	, 'service_member_nm'
     	, 'service_trans_type'
     	, 'service_trans_type_nm'
     	, 'service_trans_remark'
     	, 'insert_id'
     	, 'insert_dt'
    ]
});

var transStore = Ext.create('Ext.data.Store', {    
    model: 'TransDataThread'
});

// 서비스처리
Ext.define('RemarkDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'service_no'
        , 'seq_no'  
        , 'remark'  
        , 'insert_id'
     	, 'insert_nm'
     	, 'insert_dt'
     	, 'update_id'
     	, 'update_dt'
    ]
});

var remarkStore = Ext.create('Ext.data.Store', {    
    model: 'RemarkDataThread'
});

// 상태변경이력
Ext.define('LogDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'service_no'
        , 'seq_no'  
        , 'service_type'  
        , 'service_type_nm'
     	, 'service_status'
     	, 'service_status_nm'
     	, 'service_pre_status'
     	, 'service_pre_status_nm'
     	, 'insert_id'
     	, 'insert_nm'
     	, 'insert_dt'     	
    ]
});

var logStore = Ext.create('Ext.data.Store', {    
    model: 'LogDataThread'
});

// SMS발송이력
Ext.define('SMSDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'msg_id'
        , 'phone_no'  
        , 'callback_no'  
        , 'sms_msg'
     	, 'send_time'
     	, 'save_time'
     	, 'tran_time'
     	, 'msg_type'
     	, 'content_id'
     	, 'user_id'
     	, 'result'
     	, 'telecom'
     	, 'delivery_time'
     	, 'result_time'
     	, 'cust_nm'
     	, 'etc2'
     	, 'cust_no'
    ]
});

var smsStore = Ext.create('Ext.data.Store', {    
    model: 'SMSDataThread'
});

// 첨부파일
Ext.define('FileDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'cust_no'
        , 'prd_no'  
        , 'file_seq_no'  
        , 'file_name'
     	, 'file_path'
     	, 'file_size'
     	, 'file_save_name'
     	, 'insert_id'
     	, 'insert_nm'
     	, 'prd_serial_no'
     	, 'prd_nm'
     	, 'insert_dt'     	
    ]
});

var fileStore = Ext.create('Ext.data.Store', {    
    model: 'FileDataThread'
});

// 고객정보 PANEL
var custInfoFormPanel = new Ext.form.Panel({
	id: 'custInfoForm',
	border: 1,  
	padding: '0 0 0 0',	
    defaultType: 'textfield',
    bodyPadding: 7,
    fieldDefaults: {		            
    	labelAlign: 'center',
        labelWidth: 100,
        labelSeparator: "",
        enableKeyEvents: true
    },
    defaults: {anchor: '100%'},
    items: [{
    	xtype: 'hiddenfield',
    	name: 'group_no',
    	value: '100'
	}, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',  
        defaultType: 'textfield',
        items: [{
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            defaultType: 'textfield',
            flex: 1,            
            fieldLabel: '고객명',
            items: [{
                name: 'cust_nm',
                flex: 1
            }, {
    	    	xtype: 'button',
    	    	iconCls: 'mobile_phone',
    	    	margin: '0 0 0 5',
    	    	handler: function() {
    	    	}
    	    }]
        }, {
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            defaultType: 'textfield',
            flex: 1,
            margin: '0 0 0 20',
            fieldLabel: '휴대번호',
            items: [{
                name: 'tel_mobile',
                flex: 1
            }]
        }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox',         
        defaultType: 'textfield',
        items: [{
        	name: 'cust_no',
        	fieldLabel: '고객번호',        	
            flex:1,
            readOnly: true,
            editable: false
        }, {
            xtype: 'fieldcontainer',            
            layout: 'hbox',
            defaultType: 'textfield',
            flex: 1,
            margin: '0 0 0 20',    	            
            fieldLabel: '전화번호',
            items: [{
            	name: 'tel_home',
                flex: 1
            }]
        }]
    }, {
        xtype: 'fieldcontainer',            
        layout: 'hbox', 
        defaultType: 'textfield',
        fieldLabel: '주소',
        items: [{
            name: 'zipcode',
            width: 60,
            readOnly: true,
            editable: false
        }, {
            name: 'address1',
            flex: 1,
            readOnly: true,
            editable: false,
            padding: '0 0 0 5'
        }]
    }, {
        fieldLabel: '비고',
        name: 'cust_remark'
    }],
    tbar : ['<b>고객정보</b>', '->'
    ]
});


// 서비스상담정보
var serviceInfoFormPanel = new Ext.form.Panel({
	id: 'serviceInfoFormPanel',
	title: '서비스 접수정보',
	border: 1,
	padding: '15 0 0 0',
	bodyPadding: '7 7 0 7',
	defaultType: 'textfield',
	defaults: {anchor: '100%'},
	fieldDefaults: {		            
		labelAlign: 'center',
		labelWidth: 100,
		labelSeparator: "",
	    enableKeyEvents: true
	},
	items: [
		{
		    xtype: 'fieldcontainer',            
		    layout: 'hbox',
		    defaultType: 'textfield',
		    items: [{
		    	fieldLabel: '서비스번호',
		        name: 'service_no',
		        flex: 1
		    }, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1,     
			    margin: '0 0 0 20', 
			    fieldLabel: '',
			    items: []
			}]
		}, {
		    xtype: 'fieldcontainer',            
		    layout: 'hbox',
		    defaultType: 'textfield',
		    items: [{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1,
			    fieldLabel: '서비스구분',
			    items: [{
			        name: 'service_type_nm',
			        flex: 1
			    }, {
			        name: 'service_status_nm',
			        flex: 1,
			        margin: '0 0 0 5'
			    }]
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1,     
			    margin: '0 0 0 20', 
			    fieldLabel: '접수자',
			    items: [{
			        name: 'insert_nm',
			        flex: 1
			    }, {
			        name: 'insert_dt',
			        flex: 1,
			        margin: '0 0 0 5'
			    }]
			}]
		}, {
		    xtype: 'fieldcontainer',            
		    layout: 'hbox',
		    defaultType: 'textfield',
		    items: [{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1,
			    fieldLabel: '불량제품',
			    items: [{
			        name: 'prd_serial_no',
			        flex: 1
			    }, {
			        name: 'prd_nm',
			        flex: 1,
			        margin: '0 0 0 5'
			    }]
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1,     
			    margin: '0 0 0 20', 
			    fieldLabel: '담당자',
			    items: [{
			        name: 'service_member_id',
			        flex: 1
			    }, {
			        name: 'service_dt',
			        flex: 1,
			        margin: '0 0 0 5'
			    }]
			}]
		}, {
		    xtype: 'fieldcontainer',            
		    layout: 'hbox',
		    defaultType: 'textfield',
		    items: [{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1,      
			    fieldLabel: '불량유형',
			    items: [{
			        name: 'bad_cd1_nm',
			        flex: 1
			    }, {
			        name: 'bad_cd2_nm',
			        flex: 1,
			        margin: '0 0 0 5'
			    }]
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1,     
			    margin: '0 0 0 20', 
			    fieldLabel: 'AS수리자',
			    items: [{
			        name: 'service_no',
			        flex: 1
			    }, {
			        name: 'service_no',
			        flex: 1,
			        margin: '0 0 0 5'
			    }]
			}]
		}, {
			xtype: 'textareafield',
			fieldLabel: '상담내용',	
	        name: 'memo',
	        flex: 1,
	        height: 80
	    }, {
	    	xtype: 'textareafield',
	    	fieldLabel: '처리내용',
	        name: '',
	        flex: 1,
	        height:80
	    }
    ]
});


// 제품정보
var serviceFormPrdPanel = new Ext.form.Panel({
	id: 'serviceFormPrdPanel',	
	border: 1,
	padding: '5 0 0 0',
	bodyPadding: '7 7 0 7',
	defaultType: 'textfield',
	defaults: {anchor: '100%'},
	fieldDefaults: {		            
		labelAlign: 'center',
		labelWidth: 100,
		labelSeparator: "",
	    enableKeyEvents: true
	},
	items: [
		{
		    xtype: 'fieldcontainer',            
		    layout: 'hbox',
		    defaultType: 'textfield',
		    items: [{
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1, 
			    fieldLabel: '제품제조년월',
			    items: [{
			        name: 'manufacture_year',
			        flex: 1
			    }, {
			        name: 'manufacture_month',
			        flex: 1,
			        margin: '0 0 0 5'
			    }]
			}, {
			    xtype: 'fieldcontainer',            
			    layout: 'hbox',
			    defaultType: 'textfield',
			    flex: 1,     
			    margin: '0 0 0 20', 
			    fieldLabel: '제품제조번호',
			    items: [{
			        name: 'manufacture_type_nm',
			        flex: 1
			    }, {
			        name: 'manufacture_no',
			        flex: 1,
			        margin: '0 0 0 5'
			    }]
			}]
		}
    ]
});

//주문제품정보
var orderFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '주문제품정보',
    padding: '15 0 0 0',
    height: 150,
    store: orderStore,
    columns: [
        { xtype: 'rownumberer', header : 'No', align: 'center', width: 40},
        { text: '주문번호', dataIndex: 'order_no', align:'center', width: 100},
        { text: '제품구분', dataIndex: 'prd_type', align:'center', width: 100, renderer:getPrdTypeNm},
        { text: '주문품목', dataIndex: 'prd_cate1_nm', align:'center', flex:1},
        { text: '주문제품', dataIndex: 'prd_nm', align:'center', flex:1},
        { text: '제품가격', dataIndex: 'price', align:'right', width: 120, renderer: Ext.util.Format.numberRenderer('0,000')},
        { text: '주문수량', dataIndex: 'qty', align:'right', width: 120, renderer: Ext.util.Format.numberRenderer('0,000')},        
        { text: '주문비용', dataIndex: 'cost_amt', align:'right', width: 120, renderer: Ext.util.Format.numberRenderer('0,000')},
        { text: '등록자', dataIndex: 'insert_nm', align:'center', width: 120},
        { text: '등록일시', dataIndex: 'insert_dt', align:'center', width: 120}
    ]
});

//자재사용내역
var asFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '자재사용내역',
    padding: '15 0 0 0',
    height: 150,
    store: asStore,
    columns: [
        { xtype: 'rownumberer', header : 'No', align: 'center', width: 40},
        { text: '주문번호', dataIndex: 'order_no', align:'center', width: 100},
        { text: '제품구분', dataIndex: 'prd_type', align:'center', width: 100, renderer:getPrdTypeNm},
        { text: '주문품목', dataIndex: 'prd_cate1_nm', align:'center', flex:1},
        { text: '주문제품', dataIndex: 'prd_nm', align:'center', flex:1},
        { text: '제품가격', dataIndex: 'price', align:'right', width: 120, renderer: Ext.util.Format.numberRenderer('0,000')},
        { text: '주문수량', dataIndex: 'qty', align:'right', width: 120, renderer: Ext.util.Format.numberRenderer('0,000')},        
        { text: '주문비용', dataIndex: 'cost_amt', align:'right', width: 120, renderer: Ext.util.Format.numberRenderer('0,000')},
        { text: '등록자', dataIndex: 'insert_nm', align:'center', width: 120},
        { text: '등록일시', dataIndex: 'insert_dt', align:'center', width: 120}
    ]
});

//결제내역정보
var paymentFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '결제내역정보',
    padding: '15 0 0 0',
    store: paymentStore,
    columns: [
        { xtype: 'rownumberer', header : 'No', align: 'center', width: 40},
        { text: '결제번호',  dataIndex: 'payment_no', align:'center', width: 120},        
        { text: '결제유형', dataIndex: 'service_type_nm', align:'center', width: 120},
        { text: '결제상태', dataIndex: 'service_status_nm', align:'center', width: 120},
        { text: '결제비용', dataIndex: 'payment_amt', align:'center', renderer: Ext.util.Format.numberRenderer('0,000')},
        { text: '비고', dataIndex: 'remark', align:'center', flex: 1},
        { text: '담당자', dataIndex: 'insert_nm', align:'center', width: 120},        
        { text: '등록일', dataIndex: 'insert_dt', align:'center', width: 120},
        { text: '결제완료일', dataIndex: 'payment_dt', align:'center', width: 120}
    ]
});

//수거처리정보
var pickupFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '수거처리정보',
    padding: '15 0 0 0',
    height: 150,
    store: pickupStore,
    columns: [
        { xtype: 'rownumberer', header : 'No', align: 'center', width: 40},
        { text: '수거번호',  dataIndex: 'delivery_no', align:'center', width: 120},
        { text: '배송업체', dataIndex: 'delivery_agency', align:'center', width: 120},
        { text: '수거상태', dataIndex: 'delivery_status_nm', align:'center', width: 120},
        { text: '송장번호', dataIndex: 'invoice_no', align:'center', width: 120},
        { text: '고객명', dataIndex: 'delivery_owner_nm', align:'center', width: 120},
        { text: '연락처', dataIndex: 'tel_mobile', align:'center', width: 120, renderer: renderTel},
        { text: '수거지주소', dataIndex: 'address1', align:'center', flex: 1, renderer: renderAddr},        
        { text: '비고', dataIndex: 'remark', align:'center', width: 150}
    ]
});

//배송처리정보
var deliveryFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '배송처리정보',
    padding: '15 0 0 0',
    height: 150,
    store: deliveryStore,
    columns: [
        { xtype: 'rownumberer', header : 'No', align: 'center', width: 40},
        { text: '수거번호',  dataIndex: 'delivery_no', align:'center', width: 120},
        { text: '배송업체', dataIndex: 'delivery_agency', align:'center', width: 120},
        { text: '배송상태', dataIndex: 'delivery_status_nm', align:'center', width: 120},
        { text: '송장번호', dataIndex: 'invoice_no', align:'center', width: 120},
        { text: '고객명', dataIndex: 'delivery_owner_nm', align:'center', width: 120},
        { text: '연락처', dataIndex: 'tel_mobile', align:'center', width: 120, renderer: renderTel},
        { text: '배송지주소', dataIndex: 'address1', align:'center', flex: 1, renderer: renderAddr},        
        { text: '비고', dataIndex: 'remark', align:'center', width: 150},
        { text: '인쇄', dataIndex: 'insert_dt', align:'center', width: 60}
    ]
});

//서비스이관
var transFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '서비스이관이력',
    padding: '15 0 0 0',
    height: 150,
    store: transStore,
    columns: [
        { xtype: 'rownumberer', header : 'No', align: 'center', width: 40},
        { text: '이관번호', dataIndex: 'trans_seq_no', align:'center', width: 120},   
        { text: '담당부서', dataIndex: 'service_dept_nm', align:'center', width: 120},
        { text: '담당자', dataIndex: 'service_member_nm', align:'center', width: 120},
        { text: '이관사유', dataIndex: 'service_trans_type_nm', align:'center', width: 120},
        { text: '이관내용', dataIndex: 'service_trans_remark', align:'center', flex: 1},        
        { text: '이관일시', dataIndex: 'insert_dt', align:'center', width: 120}
    ]
});

//서비스처리
var remarkFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '서비스처리이력',
    padding: '15 0 0 0',
    height: 150,
    store: remarkStore,
    columns: [
        { xtype: 'rownumberer', header : 'No', align: 'center', width: 40},      
        { text: '처리내용',  dataIndex: 'insert_dt', align:'center', flex: 1},
        { text: '담당자', dataIndex: 'service_no', align:'center', width: 120},
        { text: '등록일시', dataIndex: 'service_type_nm', align:'center', width: 120}
    ]
});

//SMS발송이력
var smsFormPanel = new Ext.create('Ext.grid.Panel', {
    title: 'SMS발송이력',
    padding: '15 0 0 0',
    height: 150,
    store: smsStore,
    columns: [
        { xtype: 'rownumberer', header : 'No', align: 'center', width: 40},
        { text: '수신번호', dataIndex: 'phone_no', align:'center', width: 120},
        { text: '수신자', dataIndex: 'cust_nm', align:'center', width: 120},
        { text: '발신번호', dataIndex: 'callback_no', align:'center', width: 120},
        { text: '발신자', dataIndex: 'user_id', align:'center', width: 120},
        { text: '발송내용', dataIndex: 'sms_msg', align:'center', flex: 1},
        { text: '발송일자', dataIndex: 'send_time', align:'center', width: 120},
        { text: '발송결과', dataIndex: 'result', align:'center', width: 120}
    ]
});

//상태변경이력
var logFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '상태변경이력',
    padding: '15 0 0 0',
    height: 150,
    store: logStore,
    columns: [
        {xtype: 'rownumberer', header : 'No', align: 'center', width: 40},        
        { text: '상태구분', dataIndex: 'service_type_nm', align:'center', flex: 1},
        { text: '이전상태값', dataIndex: 'service_pre_status_nm', align:'center', flex: 1},
        { text: '이후상태값', dataIndex: 'service_status_nm', align:'center', flex: 1},
        { text: '변경일시', dataIndex: 'insert_dt', align:'center', flex: 1},
        { text: '등록자', dataIndex: 'insert_nm', align:'center', flex: 1}
    ]
});

//파일
var fileFormPanel = new Ext.create('Ext.grid.Panel', {
    title: '파일',
    padding: '15 0 0 0',
    height: 150,
    store: fileStore,
    columns: [
        { text: '다운',  dataIndex: 'insert_dt', align:'center'},
        { text: '제품번호', dataIndex: 'service_no', align:'center'},
        { text: '제품명', dataIndex: 'service_type_nm', align:'center'},
        { text: '파일명', dataIndex: 'service_status_nm', align:'center'},
        { text: '등록자', dataIndex: 'prd_nm', align:'center'},
        { text: '등록일시', dataIndex: 'manufacture_year', align:'center'}
    ]
});


function renderAddr(dat, meta, rec, rowIndex, colIndex) {
	if(dat != "") {
		return rec.get('zipcode') + " " + rec.get('address1') + " " + rec.get('address2');
	} else {
		return "";
	}
}

function renderTel(dat, meta, rec, rowIndex, colIndex) {
	
	var str = "";	
	
	if(rec.get('tel_home') != "") str += maskPhoneNo(rec.get('tel_home')) + "<br>";
	if(rec.get('tel_mobile') != "") str += maskPhoneNo(rec.get('tel_mobile'));
	
	return str;
}

/**
 * load service data
 * @param service_no
 */
function loadServiceData(service_no) {
	loadCRMServiceForm(service_no);
}


/**
 * 서비스 이력 클릭 후 정보 로드
 * @param service_no
 */
function loadCRMServiceForm(service_no) {
	
	Ext.getBody().mask('조회 중 입니다.');
	
	Ext.Ajax.request({
		
        url: COMMON_URL + '/ajaxSelectServiceInfo',
        params: { 'service_no' : service_no},
        success: function(response) {
        	
        	Ext.getBody().unmask();
        	
        	var obj = Ext.decode(response.responseText);
        	
        	var serviceInfoData = obj.serviceInfoData; // 서비스정보	
        	var custInfoData = obj.custInfoData; // 고객정보
        	var custPrdResult = obj.custPrdResult; // 제품정보
        	var serviceOrderList = obj.serviceOrderListResult; // 주문정보
        	var serviceAsList = obj.serviceAsListResult; // as자재정보
        	var serviceDeliveryList = obj.serviceDeliveryListResult; // 배송정보
        	var servicePickupList = obj.servicePickupListResult; // 수거정보
        	
        	var servicePaymentList = obj.servicePaymentListResult; // 결제정보
        	var serviceSMSList = obj.serviceSMSListResult; // SMS
        	var serviceLogList = obj.serviceLogListResult; // 상태변경이력
        	var serviceRemarkList = obj.serviceRemarkListResult; // 서비스처리이력
        	var serviceTransList = obj.serviceTransListResult; // 이관이력
        	var custPrdFiles = obj.custPrdFilesResult; // 첨부파일
        	
        	// 1. 고객정보
        	custInfoFormPanel.getForm().setValues(custInfoData);
        	
        	// 2. 서비스 상담정보
        	serviceInfoFormPanel.getForm().setValues(serviceInfoData);
        	
        	// 3. 제품정보
        	serviceFormPrdPanel.getForm().setValues(custPrdResult);
        	
        	// 4. 주문정보
        	orderStore.loadRawData(serviceOrderList);
        	
        	// 5. AS정보
        	asStore.loadRawData(serviceAsList);
        	
        	// 6. 결제정보
        	paymentStore.loadRawData(servicePaymentList);
        	
        	// 7. 수거
        	pickupStore.loadRawData(servicePickupList);
        	
        	// 8. 배송
        	deliveryStore.loadRawData(serviceDeliveryList);
        	
        	// 9. 이관
        	transStore.loadRawData(serviceTransList);
        	
        	// 10. 처리내용
        	remarkStore.loadRawData(serviceRemarkList);
        	
        	// 11. SMS 문자발송
        	smsStore.loadRawData(serviceSMSList);
        	
        	// 12. 상태변경이력
        	logStore.loadRawData(serviceLogList);
        	
        	// 13. 첨부파일
        	fileStore.loadRawData(custPrdFiles);
        	
        },
        failure: function(result, request) {
        	Ext.getBody().unmask();
        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
    		return;
		}
    });		
}