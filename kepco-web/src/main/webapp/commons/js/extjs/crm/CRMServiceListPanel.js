/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMServiceListPanel.js
* @Author : kyunghee.yoon
* @Date : 2015.10.30
**************************************/

// 서비스상담이력
var serviceListPanel = new Ext.create('Ext.grid.Panel', {
    title: '서비스 상담이력',
    padding: '10 0 0 0',
    flex: 1,
    store: custServiceListStore, 
    columns: [
        { text: '접수일시',  dataIndex: 'insert_dt', align:'center'},
        { text: '접수번호', dataIndex: 'service_no', align:'center'},
        { text: '서비스구분', dataIndex: 'service_type_nm', align:'center'},
        { text: '처리상태', dataIndex: 'service_status_nm', align:'center'},
        { text: '제품명', dataIndex: 'prd_nm', align:'center'},
        { text: '제조년월', dataIndex: 'manufacture_year', align:'center', renderer: manufactureDate},
        { text: '주문금액', dataIndex: 'payment_amt', align:'right', renderer: Ext.util.Format.numberRenderer('0,000')},        
        { text: '담당자', dataIndex: 'service_member_nm', align:'center'},
        { text: '처리일시', dataIndex: 'service_dt', align:'center'}
    ],
    listeners: {
     	'cellclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
     		
     		var rec = custServiceListStore.getAt(iRowIdx);
     		var service_no = rec.get('service_no');
     		
     		loadCRMServiceForm(service_no);
     	}
    }
});

/**
 * 보유제품리스트
 */
function loadCustServiceList(cust_no) {
	
	custServiceListStore.getProxy().extraParams = {'cust_no':cust_no};
	custServiceListStore.load();	
}