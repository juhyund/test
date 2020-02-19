var SERVICE_CODE_AS = '10'; // 서비스구분 AS
var SERVICE_CODE_ORDER = '11'; // 서비스구분 주문 
var SERVICE_CODE_GO1 = '12'; // 서비스구분 찾서 
var SERVICE_CODE_HAPPY = '13'; // 홈케어
var SERVICE_CODE_SALES = '14'; // 서비스구분 보상판매
var SERVICE_CODE_GENERAL = '15'; // 고객상담
var SERVICE_CODE_CLAIME1 = '16'; // 클레임(일반)
var SERVICE_CODE_CLAIME2 = '17'; // 클레임(일반)
var SERVICE_CODE_ETC = '18'; // 내방

var siteStore = Ext.create('Ext.data.Store', {
    fields: ['code', 'name'],
    data : [
        {"code":"", "name":"전체"},    
        {"code":"1", "name":"한경희생활과학"},
        {"code":"2", "name":"리빙(뷰티)"},
        {"code":"3", "name":"카페이탈리아"},
        {"code":"4", "name":"홈케어"},
        {"code":"5", "name":"브랜드대여"},
        {"code":"6", "name":"사은품"}
    ]
});


var gubunStore = Ext.create('Ext.data.Store', {
    fields: ['code', 'name'],
    data : [         
        {"code":"1", "name":"상담직"},
        {"code":"2", "name":"로드샵"},
        {"code":"", "name":"전체"}
    ]
});