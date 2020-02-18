/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMFormCheck.js
* @Author : kyunghee.yoon
* @Date : 2015.12.03
**************************************/
var toDateTime = Ext.Date.format(new Date(),'Y-m-d H:i');

var SERVICE_CODE_AS = '10'; // 서비스구분 AS
var SERVICE_CODE_ORDER = '11'; // 서비스구분 주문 
var SERVICE_CODE_GO1 = '12'; // 서비스구분 찾서 
var SERVICE_CODE_GO2 = '13'; // 서비스구분 찾서(재)
var SERVICE_CODE_SALES = '14'; // 서비스구분 보상판매
var SERVICE_CODE_GENERAL = '15'; // 고객상담
var SERVICE_CODE_CLAIME1 = '16'; // 클레임(일반)
var SERVICE_CODE_CLAIME2 = '17'; // 클레임(일반)
var SERVICE_CODE_ETC = '18'; // 내방


Ext.define('CustSearchDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'cust_no'
     	, 'cust_nm'
     	, 'group_no'
     	, 'tel_mobile'
     	, 'tel_home'
     	, 'zipcode'
     	, 'address1'
     	, 'address2'
     	, 'invoice_no'
     	, 'account_no'
    ]
});

// 고객조회
var custSearchStore = Ext.create('Ext.data.Store', {
    pageSize: 30,
    model: 'CustSearchDataThread',
    remoteSort: true,
    proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCustInfoSimpleList',
        reader: {
        	root: 'resultGrid',
            totalProperty: 'totalCount'
        },
        simpleSortMode: true
    },
    sorters: [{
        property: 'a.insert_dt',
        direction: 'DESC'
    }]
});


Ext.define('CustBookingDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'booking_no'
     	, 'cust_no'
     	, 'cust_nm'
     	, 'tel_mobile'
     	, 'tel_home'
     	, 'booking_date'
     	, 'booking_time'
     	, 'booking_status'
     	, 'booking_status_nm'
     	, 'remark'
     	, 'process_id'
     	, 'process_dt'
     	, 'insert_id'
     	, 'insert_dt'
    ]
});

// 예약고객조회
var custBookingStore = Ext.create('Ext.data.Store', {
    pageSize: 30,
    model: 'CustBookingDataThread',
    remoteSort: true,
    proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCustBookingList',
        reader: {
        	root: 'resultGrid',
            totalProperty: 'totalCount'
        },
        simpleSortMode: true
    },
    sorters: [{
        property: 'a.insert_dt',
        direction: 'DESC'
    }],
    autoLoad: true
});


Ext.define('CustPrdDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'cust_prd_seq_no'
     	, 'prd_no'
     	, 'prd_serial_no'
     	, 'prd_nm'
     	, 'prd_cate1'
     	, 'prd_cate1_nm'
     	, 'prd_cate2'
     	, 'prd_cate2_nm'
     	, 'site'
     	, 'manufacture_year'
     	, 'manufacture_month'
     	, 'manufacture_type'
     	, 'manufacture_no'
     	, 'buy_shop'
     	, 'buy_date'
     	, 'remark'
     	, 'insert_id'
     	, 'insert_dt'
     	, 'update_id'
     	, 'update_dt'
     	, 'file_cnt'
    ]
});

// 보유제품조회
var custPrdListStore = Ext.create('Ext.data.Store', {    
    model: 'CustPrdDataThread',    
    proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCustPrdListCRM',
        reader: {
        	root: 'result'
        },
        simpleSortMode: true
    },
    sorters: [{
        property: 'a.insert_dt',
        direction: 'DESC'
    }]
});

Ext.define('CustServiceDataThread', {
    extend: 'Ext.data.Model',
    fields: [
          'service_no'
     	, 'cust_no'
     	, 'service_type'
     	, 'service_type_nm'
     	, 'service_status'
     	, 'service_status_nm'
     	, 'prd_no'
     	, 'prd_serial_no'
     	, 'prd_nm'
     	, 'manufacture_year'
     	, 'manufacture_month'
     	, 'payment_amt'
     	, 'service_dept_cd'
     	, 'service_dept_nm'
     	, 'service_member_id'
     	, 'service_member_nm'
     	, 'service_dt'
     	, 'insert_dt'
    ]
});

// 서비스 상담이력
var custServiceListStore = Ext.create('Ext.data.Store', {    
    model: 'CustServiceDataThread',    
    proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxServiceInfoListCRM',
        reader: {
        	root: 'result'
        },
        simpleSortMode: true
    },
    sorters: [{
        property: 'service_no',
        direction: 'DESC'
    }]
});

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

// 대행사
var agencyStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},           
        extraParams: {class_cd: 'AG', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

// 결제유형
var paymentTypeStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},
        extraParams: {class_cd: 'PC', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

// 유상무상
var FreeCostYNStore = Ext.create('Ext.data.ArrayStore', {
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    data: [['N','유상'],['Y', '무상']]
});

// 불량유형1
var badCode1Store = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdBadCode1',
        reader: {root: 'result'}
    },
    fields: [{ name: 'bad_cd' },{ name: 'bad_nm' }]
});

// 불량유형 2
var badCode2Store = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdBadCode2',
        reader: {root: 'result'}
    },
    fields: [{ name: 'bad_cd' },{ name: 'bad_nm' }]
});

// 이관사유
var serviceTransTypeStore = Ext.create('Ext.data.ArrayStore', {
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    data: [['TR001','AS담당'], ['TR002', '찾서담당'], ['TR003', '판매담당'], ['TR004', '클레임담당'], ['TR005', '기타']]
});

var iYear = Ext.Date.format(new Date(),'Y');
var iMonth = Ext.Date.format(new Date(),'m');

var yearStore = new Ext.data.ArrayStore({        
    fields : ['code','val']
});

var monthStore = new Ext.data.ArrayStore({        
    fields : ['code','val']
});

for(i = 0; i < 11; i++) {
	year = (iYear - i)+"";		
	yearStore.add({'code' : year, 'val' : year + '년'});
}

for(i = 0; i < 12; i++) {
	mon = i+1;
	monthStore.add({'code' : lpad(mon,2,'0'), 'val' : lpad(mon,2,'0') + '월'});
}

//제품군
var prdCate1Store = Ext.create('Ext.data.Store', {
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdCate1',
        reader: {root: 'result'},
        simpleSortMode: true
    },
    fields: [{ name: 'cate' },{ name: 'cate_nm' }]
});

// 모델군
var prdCate2Store = Ext.create('Ext.data.Store', {
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdCate2',
        reader: {root: 'result'},
        simpleSortMode: true
    },
    fields: [{ name: 'cate' },{ name: 'cate_nm' }]
});

// 제품
var prdNoStore = Ext.create('Ext.data.Store', {
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdNoCombo',
        reader: {root: 'result'},
        simpleSortMode: true
    },
    fields: [{ name: 'prd_no' },{ name: 'prd_serial_no' },{ name: 'prd_nm' },{ name: 'site' }]
});

// 제조번호구분
var manufactureTypeStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},           
        extraParams: {class_cd: 'MT', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

// 제품구매처
var buyShopStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},           
        extraParams: {class_cd: 'PS', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});



function manufactureDate(value, metaData, record) {
	return record.get('manufacture_year') + "-" + record.get('manufacture_month');
}