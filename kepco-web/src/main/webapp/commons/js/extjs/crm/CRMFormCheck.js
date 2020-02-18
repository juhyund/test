/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMFormCheck.js
* @Author : kyunghee.yoon
* @Date : 2015.12.03
**************************************/
var parcelServiceAmt = 3000;	// 택배비

/**
 * 담당자 검색 팝업
 */
function searchMemberWin()
{
	var win = window.open(COMMON_URL + "/jsp/CRM/MemberInfoSearchPop.jsp", "searchMember", "menubar=no, scrollbars=no, resizable=no, width=800, height=600");
}

/**
 * 제품/자재 검색 팝업
 */
function searchPrdWin(site, prd_cate1, prd_cate2, prd_no, func_name)
{
	var win = window.open(COMMON_URL + "/jsp/CRM/PrdInfoSearchPop.jsp?site="+site+"&prd_cate1="+prd_cate1+"&prd_cate2="+prd_cate2+"&prd_no="+prd_no+"&func_name="+func_name, "searchMember", "menubar=no, scrollbars=no, resizable=no, width=1000, height=800");
}

/**
 * 통화예약
 */
function custBookingWin(cust_no, cust_nm, tel_mobile, tel_home, booking_no)
{
	var win = window.open(COMMON_URL + "/jsp/CRM/CRMCustBookingPop.jsp?cust_no="+cust_no+"&cust_nm="+cust_nm+"&tel_mobile="+tel_mobile+"&tel_home="+tel_home+"&booking_no="+booking_no, "custBooking", "menubar=no, scrollbars=no, resizable=no, width=400, height=350");
}

/**
 * 파일업로드 팝업
 */
function fileUploadWin(cust_no, prd_no, prd_nm)
{
	var win = window.open(COMMON_URL + "/jsp/CRM/CRMFileUploaderPop.jsp?cust_no="+cust_no+"&prd_no="+prd_no+"&prd_nm="+prd_nm, "fileupload", "menubar=no, scrollbars=no, resizable=no, width=550, height=600");
}


/**
 * 제조년월
 * @param value
 * @param metaData
 * @param record
 * @returns {String}
 */
function manufactureDate(value, metaData, record) {
	return record.get('manufacture_year') + "-" + record.get('manufacture_month');
}

/**
 * address
 * @param value
 * @param metaData
 * @param record
 * @returns {String}
 */
function rendererAddr(value, metaData, record) {
	return record.get('address1') + " " + record.get('address2');
}
/**
 * form check
 */
function CRMFormCheck() {
	
	var form = Ext.getCmp("serviceFormPanel").getForm();
	
	var service_no = form.findField("service_no").getValue();
	
	if(service_no == "") {
		CRMFormInsert();
	} else {
		CRMFormUpdate();
	}
}


function CRMFormInsert() {
	
	var form = Ext.getCmp("Content").getForm();
	
	var cust_no = form.findField("cust_no");
	var cust_nm = form.findField("cust_nm");
	
	var tel_mobile = form.findField("tel_mobile");
	var tel_home = form.findField("tel_home");
	
	var prd_no = form.findField("prd_no"); // 제품
	
	var service_type = form.findField("service_type");
	var service_status = form.findField("service_status");
	
	var parcel_service_yn = form.findField("parcel_service_yn");	// 택배
	
	var chk_pickup = form.findField("chk_pickup");	// 수거
	var chk_delivery = form.findField("chk_delivery");	// 발송
	var chk_direct = form.findField("chk_direct");	// 직택
	var chk_exchange = form.findField("chk_exchange");	// 한달내맞교환
	
	var bad_cd1 = form.findField("bad_cd1");	// 불량유형1
	var bad_cd2 = form.findField("bad_cd2");	// 불량유형2
	
	var memo = form.findField("memo");	// 상담내용
	
	var order_records = form.findField("order_records");	// 주문내역
	var as_records = form.findField("as_records");	// AS자재사용내역
	
	// 수령지 정보
	var delivery1_owner_nm = form.findField("delivery1_owner_nm");
	var delivery1_tel_mobile = form.findField("delivery1_tel_mobile");
	var delivery1_tel_home = form.findField("delivery1_tel_home");
	var delivery1_zipcode = form.findField("delivery1_zipcode");
	var delivery1_address1 = form.findField("delivery1_address1");
	var delivery1_address2 = form.findField("delivery1_address2");
	
	// 수거지 정보
	var delivery2_owner_nm = form.findField("delivery2_owner_nm");
	var delivery2_tel_mobile = form.findField("delivery2_tel_mobile");
	var delivery2_tel_home = form.findField("delivery2_tel_home");
	var delivery2_zipcode = form.findField("delivery2_zipcode");
	var delivery2_address1 = form.findField("delivery2_address1");
	var delivery2_address2 = form.findField("delivery2_address2");
		
	tel_mobile.setValue(maskPhoneNo(tel_mobile.getValue()));
	tel_home.setValue(maskPhoneNo(tel_home.getValue()));
	
	delivery1_tel_mobile.setValue(maskPhoneNo(delivery1_tel_mobile.getValue()));
	delivery1_tel_home.setValue(maskPhoneNo(delivery1_tel_home.getValue()));
	
	delivery2_tel_mobile.setValue(maskPhoneNo(delivery2_tel_mobile.getValue()));
	delivery2_tel_home.setValue(maskPhoneNo(delivery2_tel_home.getValue()));
			
	if(cust_no.getValue() == "" ) {					
		focusMsgAlert('Warning', '고객정보를 선택해 주세요', cust_no);
		return;
	}
	
	if(tel_mobile.getValue() == "" && tel_home.getValue() == "") {
		focusMsgAlert('Warning', '휴대전화 또는 전화번호를 입력해 주세요');					
		return;
	}
	
	if(tel_mobile.getValue() != "") {
		if ( !regPhone.test(tel_mobile.getValue()) ) {
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_mobile);
			return;
		}
		
		if ( regPhone2.test(tel_mobile.getValue()) ) {	     				
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_mobile);
			return;
		}
	}
	
	if(tel_home.getValue() != "") {
		if ( !regPhone.test(tel_home.getValue()) ) {
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_home);
			return;
		}
		
		if ( regPhone2.test(tel_home.getValue()) ) {	     				
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_home);
			return;
		}
	}
	
	
	if(service_type.getSubmitValue() == "" ) {					
		focusMsgAlert('Warning', '서비스구분을 선택해 주세요', service_type);
		return;
	}
	
	if(service_status.getSubmitValue() == "" ) {					
		focusMsgAlert('Warning', '처리상태를 선택해 주세요', service_status);
		return;
	}
	
	if(service_type.getSubmitValue() == SERVICE_CODE_AS ) {	// AS	
		
		if(prd_no.getSubmitValue() == "") {
			focusMsgAlert('Warning', '고객의 보유제품정보를 선택해 주세요!', prd_no);
			return;
		}
		
		if(chk_pickup.getValue() == false && chk_delivery.getValue() == false) {					
			focusMsgAlert('Warning', 'AS의 수거 또는 발송을 선택해 주세요!', chk_pickup);
			return;
		}
		
		if(bad_cd1.getSubmitValue() == "") {					
			focusMsgAlert('Warning', '불량유형을 선택해 주세요!', bad_cd1);
			return;
		}
		
		if(bad_cd2.getSubmitValue() == "") {					
			focusMsgAlert('Warning', '불량 상세유형을 선택해 주세요!', bad_cd2);
			return;
		}
		
		if(chk_pickup.getValue() == true) { // 수거지 체크					
			
			if(delivery2_owner_nm.getValue() == "") {					
				focusMsgAlert('Warning', '수거자명을 입력하세요', delivery2_owner_nm);
				return;
			}
			
			if(delivery2_tel_mobile.getValue() == "" && delivery2_tel_home.getValue() == "") {					
				focusMsgAlert('Warning', '수거자 연락처를 입력해 주세요!', delivery2_tel_mobile);
				return;
			}
			
			if(delivery2_zipcode.getValue() == "") {					
				focusMsgAlert('Warning', '수거지 주소를 입력해 주세요!', delivery2_zipcode);
				return;
			}
			
			if(delivery2_address1.getValue() == "") {					
				focusMsgAlert('Warning', '수거지 주소를 입력해 주세요!', delivery2_address1);
				return;
			}
			
			if(delivery2_address2.getValue() == "") {					
				focusMsgAlert('Warning', '수거지 상세주소를 입력해 주세요!', delivery2_address2);
				return;
			}
		}
		
		if(chk_delivery.getValue() == true) { // 발송 체크					
			
			if(delivery1_owner_nm.getValue() == "") {					
				focusMsgAlert('Warning', '수령자명을 입력하세요', delivery1_owner_nm);
				return;
			}
			
			if(delivery1_tel_mobile.getValue() == "" && delivery1_tel_home.getValue() == "") {					
				focusMsgAlert('Warning', '수령자 연락처를 입력해 주세요!', delivery1_tel_mobile);
				return;
			}
			
			if(delivery1_zipcode.getValue() == "") {					
				focusMsgAlert('Warning', '수령지 주소를 입력해 주세요!', delivery1_zipcode);
				return;
			}
			
			if(delivery1_address1.getValue() == "") {					
				focusMsgAlert('Warning', '수령지 주소를 입력해 주세요!', delivery1_address1);
				return;
			}
			
			if(delivery1_address2.getValue() == "") {					
				focusMsgAlert('Warning', '수령지 상세주소를 입력해 주세요!', delivery1_address2);
				return;
			}
		}
		
	} else if(service_type.getSubmitValue() == SERVICE_CODE_SALES) {	// 보상판매
		
		if(prd_no.getSubmitValue() == "") {
			focusMsgAlert('Warning', '고객의 보유제품정보를 선택해 주세요!', prd_no);
			return;
		}
				
	} else if(service_type.getSubmitValue() == SERVICE_CODE_CLAIME1 || service_type.getSubmitValue() == SERVICE_CODE_CLAIME2) {	// 클레임
		
		if(prd_no.getSubmitValue() == "") {
			focusMsgAlert('Warning', '고객의 보유제품정보를 선택해 주세요!', prd_no);
			return;
		}
		
		if(bad_cd1.getSubmitValue() == "") {					
			focusMsgAlert('Warning', '불량유형을 선택해 주세요!', bad_cd1);
			return;
		}
		
		if(bad_cd2.getSubmitValue() == "") {					
			focusMsgAlert('Warning', '불량 상세유형을 선택해 주세요!', bad_cd2);
			return;
		}
	}
	
	if(memo.getValue() == "") {					
		focusMsgAlert('Warning', '상담내용을 입력해 주세요!', memo);
		return;
	}
	
	
	if(delivery1_tel_mobile.getValue() != "") {
		if ( !regPhone.test(delivery1_tel_mobile.getValue()) ) {
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", delivery1_tel_mobile);
			return;
		}
		
		if ( regPhone2.test(delivery1_tel_mobile.getValue()) ) {	     				
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", delivery1_tel_mobile);
			return;
		}
	}
	
	if(delivery1_tel_home.getValue() != "") {
		if ( !regPhone.test(delivery1_tel_home.getValue()) ) {
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", delivery1_tel_home);
			return;
		}
		
		if ( regPhone2.test(delivery1_tel_home.getValue()) ) {	     				
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", delivery1_tel_home);
			return;
		}
	}
	
	if(delivery2_tel_mobile.getValue() != "") {
		if ( !regPhone.test(delivery2_tel_mobile.getValue()) ) {
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", delivery2_tel_mobile);
			return;
		}
		
		if ( regPhone2.test(delivery2_tel_mobile.getValue()) ) {	     				
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", delivery2_tel_mobile);
			return;
		}
	}
	
	if(delivery2_tel_home.getValue() != "") {
		if ( !regPhone.test(delivery2_tel_home.getValue()) ) {
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", delivery2_tel_home);
			return;
		}
		
		if ( regPhone2.test(delivery2_tel_home.getValue()) ) {	     				
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", delivery2_tel_home);
			return;
		}
	}
	
	// 주문정보	
	var strOrderRecord = setOrderRecords();
	
	order_records.setValue(strOrderRecord);
	
	// AS자재사용내역	
	var strAsRecord = setAsRecords();
	as_records.setValue(strAsRecord);
	
	form.submit({
    	url: COMMON_URL + '/ajaxInsertCRMForm',
    	submitEmptyText: false,
        success: function(form, action) {
        	
        	if(action.result.result > 0) {
        		Ext.Msg.alert('Success', "저장 되었습니다.");
        		
        		// 2. 보유제품리스트
        		loadCustPrdList(cust_no.getValue());
        		
        		// 3. 서비스상담이력
        		loadCustServiceList(cust_no.getValue());
        		
        		// 4. 서비스상담정보 form reset
        		resetServiceForm();
        		
        		// 5. 주문정보 reset
        		resetOrderForm();
        		
        		// 6. AS 자재정보 reset
        		resetAsForm();
        		
        		// 7. 수령지 & 수거지 reset
        		resetDeliveryForm();
        		
        	} else {
        		var errCd = action.result.result;
        		var errMsg = getErrMsg(errCd);
        		Ext.Msg.alert('Error', "저장 중 오류가 발생하였습니다.<br>[" + errCd + "]" + errMsg);
        	}
        	
        	return;
        },
        failure: function(form, action) {
             
            return;
        }
    });	
}


function CRMFormUpdate() {
	
	var form = Ext.getCmp("Content").getForm();
	
	var cust_no = form.findField("cust_no");
	var cust_nm = form.findField("cust_nm");
	
	var tel_mobile = form.findField("tel_mobile");
	var tel_home = form.findField("tel_home");
	
	var prd_no = form.findField("prd_no"); // 제품
	var service_status = form.findField("service_status");
	
	var memo = form.findField("memo");	// 상담내용
	
	tel_mobile.setValue(maskPhoneNo(tel_mobile.getValue()));
	tel_home.setValue(maskPhoneNo(tel_home.getValue()));
			
	if(cust_no.getValue() == "" ) {					
		focusMsgAlert('Warning', '고객정보를 선택해 주세요', cust_no);
		return;
	}
	
	if(tel_mobile.getValue() == "" && tel_home.getValue() == "") {
		focusMsgAlert('Warning', '휴대전화 또는 전화번호를 입력해 주세요');					
		return;
	}
	
	if(tel_mobile.getValue() != "") {
		if ( !regPhone.test(tel_mobile.getValue()) ) {
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_mobile);
			return;
		}
		
		if ( regPhone2.test(tel_mobile.getValue()) ) {	     				
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_mobile);
			return;
		}
	}
	
	if(tel_home.getValue() != "") {
		if ( !regPhone.test(tel_home.getValue()) ) {
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_home);
			return;
		}
		
		if ( regPhone2.test(tel_home.getValue()) ) {	     				
			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_home);
			return;
		}
	}
	
	if(service_status.getSubmitValue() == "" ) {					
		focusMsgAlert('Warning', '처리상태를 선택해 주세요', service_status);
		return;
	}
	
	if(memo.getValue() == "") {					
		focusMsgAlert('Warning', '상담내용을 입력해 주세요!', memo);
		return;
	}
	
	form.submit({
    	url: COMMON_URL + '/ajaxUpdateCRMForm',
    	submitEmptyText: false,
        success: function(form, action) {
        	
        	if(action.result.result > 0) {
        		
        		Ext.Msg.alert('Success', "저장 되었습니다.");        		
        		
        		// 2. 보유제품리스트
        		loadCustPrdList(cust_no.getValue());
        		
        		// 3. 서비스상담이력
        		loadCustServiceList(cust_no.getValue());
        		
        		// 4. 서비스상담정보 form reset
        		resetServiceForm();
        		
        		// 5. 주문정보 reset
        		resetOrderForm();
        		
        		// 6. AS 자재정보 reset
        		resetAsForm();
        		
        		// 7. 수령지 & 수거지 reset
        		resetDeliveryForm();	
        		
        	} else {
        		
        		var errCd = action.result.result; 
        		var errMsg = getErrMsg(errCd);
        		Ext.Msg.alert('Error', "저장 중 오류가 발생하였습니다.<br>[" + errCd + "]" + errMsg);
        	}
        	
        	return;
        },
        failure: function(form, action) {
            Ext.Msg.alert('Error', "저장 중 오류가 발생하였습니다.");
            return;
        }
    });	
}

/**
 * FORM RESET
 */
function CRMFormResetAll() {
	
	// 고객정보
	custInfoFormPanel.getForm().reset();
	
	custInfoFormPanel.getForm().findField("group_no").setValue("100");
	
	// 보유제품리스트
	custPrdListStore.removeAll();
	
	// 상담이력
	custServiceListStore.removeAll();
	
	// 서비스상담정보 form reset
	resetServiceForm();
	
	// 주문정보 reset
	resetOrderForm();
	
	// AS 자재정보 reset
	resetAsForm();
	
	// 수령지 & 수거지 reset
	resetDeliveryForm();	
	
	serviceFormPanel.getForm().findField("service_type").setDisabled(false);
	
	serviceFormPanel.getForm().findField("prd_nm").setReadOnly(false);
	serviceFormPanel.getForm().findField("free_cost_yn").setDisabled(false);
	serviceFormPanel.getForm().findField("payment_type").setDisabled(false);
	serviceFormPanel.getForm().findField("payment_amt").setReadOnly(false);
}

/**
 * FORM RESET
 */
function CRMFormReset() {
	
	// 서비스상담정보 form reset
	resetServiceForm();
	
	// 주문정보 reset
	resetOrderForm();
	
	// AS 자재정보 reset
	resetAsForm();
	
	// 수령지 & 수거지 reset
	resetDeliveryForm();	
	
	serviceFormPanel.getForm().findField("service_type").setDisabled(false);
	
	serviceFormPanel.getForm().findField("prd_nm").setReadOnly(false);
	serviceFormPanel.getForm().findField("free_cost_yn").setDisabled(false);
	serviceFormPanel.getForm().findField("payment_type").setDisabled(false);
	serviceFormPanel.getForm().findField("payment_amt").setReadOnly(false);
}


/**
 * 주문내역
 * @returns {String}
 */
function setOrderRecords() {
	
	var form = serviceFormPanel.getForm();
	var free_cost_yn = form.findField("free_cost_yn").getSubmitValue();
	
	var strOrderRecord = "";
	
	for(var i = 0; i < orderStore.getCount(); i++) {
		var record = orderStore.getAt(i);
		strOrderRecord = strOrderRecord + record.get("prd_no") + "^" + record.get("price") + "^" + record.get("qty") + "^" + record.get("cost_amt") + "^" + free_cost_yn + "|";  
	}
	
	return strOrderRecord;
}

/**
 * AS 자재사용내역
 * @returns {String}
 */
function setAsRecords() {
	
	var form = serviceFormPanel.getForm();
	var free_cost_yn = form.findField("free_cost_yn").getSubmitValue();
	
	var strAsRecord = "";
	
	for(var i = 0; i < asStore.getCount(); i++) {
		var record = asStore.getAt(i);
		strAsRecord = strAsRecord + record.get("prd_no") + "^" + record.get("price") + "^" + record.get("qty") + "^" + record.get("cost_amt") + "^" + free_cost_yn + "|";  
	}
	
	return strAsRecord;
}

/**
 * CRM 고객정보 & 보유제품리스트 & 서비스상담이력
 */
function loadCRMForm(iRowIdx) {
		
	// 1. 고객정보 
	var rec = custSearchStore.getAt(iRowIdx);			
	custInfoFormPanel.getForm().loadRecord(rec);
	
	custInfoFormPanel.getForm().findField('tel_mobile').setValue(maskPhoneNo(rec.get('tel_mobile')));
	custInfoFormPanel.getForm().findField('tel_home').setValue(maskPhoneNo(rec.get('tel_home')));
	
	// 2. 보유제품리스트
	loadCustPrdList(rec.get('cust_no'));
	
	// 3. 서비스상담이력
	loadCustServiceList(rec.get('cust_no'));
	
	// 4. 서비스상담정보 form reset
	resetServiceForm();
	
	// 5. 주문정보 reset
	resetOrderForm();
	
	// 6. AS 자재정보 reset
	resetAsForm();
	
	// 7. 수령지 & 수거지 reset
	resetDeliveryForm();	
}


/**
 * 서비스 이력 클릭 후 정보 로드
 * @param service_no
 */
function loadCRMServiceForm(service_no) {
	
	Ext.getBody().mask('서비스조회중...');
	
	Ext.Ajax.request({
		
        url: COMMON_URL + 'ajaxSelectCRMForm',
        params: { 'service_no' : service_no},
        success: function(response) {
        	
        	var obj = Ext.decode(response.responseText);
        	
        	var serviceInfoData = obj.serviceInfoData;
        	var custPrdResult = obj.custPrdResult;
        	var serviceOrderList = obj.serviceOrderListResult;
        	var serviceAsList = obj.serviceAsListResult;
        	var serviceDeliveryList = obj.serviceDeliveryListResult;
        	
        	var orderAddrForm1 = orderAddrForm1Panel.getForm(); // 배송
        	var orderAddrForm2 = orderAddrForm2Panel.getForm(); // 수거
        
        	var get_site = custPrdResult.site;
        	var get_prd_cate1 = custPrdResult.prd_cate1;
        	var get_prd_cate2 = custPrdResult.prd_cate2;
        	var get_prd_no = custPrdResult.prd_no;
        	
        	// 1. 서비스 상담정보
        	serviceFormPanel.getForm().setValues(serviceInfoData);
        	
        	// 2. 보유제품정보
        	productFormPanel.getForm().setValues(custPrdResult);
        	
        	setPrdInfoForm(get_site, get_prd_cate1, get_prd_cate2, get_prd_no);
        	
        	// 3. 이관정보
        	transferFormPanel.getForm().setValues(serviceInfoData);
        	
        	// 4. 주문정보
        	orderStore.loadRawData(serviceOrderList);
        	
        	// 5. AS정보
        	asStore.loadRawData(serviceAsList);
        	
        	// 5. 배송 & 수거
        	for(var i = 0; i < serviceDeliveryList.length; i++) {
        		
        		var rec = serviceDeliveryList[i];
        		
        		if(rec.delivery_type == "1") { // 배송
        			
        			orderAddrForm1.findField("delivery1_owner_nm").setValue(rec.delivery_owner_nm);
        			orderAddrForm1.findField("delivery1_owner_type").setValue(rec.delivery_owner_type);
        			orderAddrForm1.findField("delivery1_tel_mobile").setValue(maskPhoneNo(rec.tel_mobile));
        			orderAddrForm1.findField("delivery1_tel_home").setValue(maskPhoneNo(rec.tel_home));
        			orderAddrForm1.findField("delivery1_zipcode").setValue(rec.zipcode);
        			orderAddrForm1.findField("delivery1_address1").setValue(rec.address1);
        			orderAddrForm1.findField("delivery1_address2").setValue(rec.address2);
        			orderAddrForm1.findField("delivery1_remark").setValue(rec.remark);
        			
        		} else if(rec.delivery_type == "2") { // 수거
        			
        			orderAddrForm2.findField("delivery2_owner_nm").setValue(rec.delivery_owner_nm);
        			orderAddrForm2.findField("delivery2_owner_type").setValue(rec.delivery_owner_type);
        			orderAddrForm2.findField("delivery2_tel_mobile").setValue(maskPhoneNo(rec.tel_mobile));
        			orderAddrForm2.findField("delivery2_tel_home").setValue(maskPhoneNo(rec.tel_home));
        			orderAddrForm2.findField("delivery2_zipcode").setValue(rec.zipcode);
        			orderAddrForm2.findField("delivery2_address1").setValue(rec.address1);
        			orderAddrForm2.findField("delivery2_address2").setValue(rec.address2);
        			orderAddrForm2.findField("delivery2_remark").setValue(rec.remark);
        		} 
        	}
        	
        	serviceFormPanel.getForm().findField("service_type").setDisabled(true);
        	
        	serviceFormPanel.getForm().findField("chk_pickup").setDisabled(true);
        	serviceFormPanel.getForm().findField("chk_delivery").setDisabled(true);
        	serviceFormPanel.getForm().findField("chk_direct").setDisabled(true);
        	serviceFormPanel.getForm().findField("chk_exchange").setDisabled(true);
        	
        	serviceFormPanel.getForm().findField("prd_nm").setReadOnly(true);
        	serviceFormPanel.getForm().findField("free_cost_yn").setDisabled(true);
        	serviceFormPanel.getForm().findField("payment_type").setDisabled(true);
        	serviceFormPanel.getForm().findField("payment_amt").setReadOnly(true);
        	
        	Ext.getCmp("btnOrderAdd").setDisabled(true);
        	Ext.getCmp("btnOrderRemove").setDisabled(true);
        	Ext.getCmp("parcel_service_yn").setDisabled(true);
        	Ext.getCmp("btnAsAdd").setDisabled(true);
        	Ext.getCmp("btnAsRemove").setDisabled(true);
        	
        	Ext.getBody().unmask();
        	
        },
        failure: function(result, request) {
        	Ext.getBody().unmask();
        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
    		return;
		}
    });		
}


/**
 * RESET FORM
 */
function resetCRMForm() {
		
	// 1. 고객정보 
	var rec = custSearchStore.getAt(iRowIdx);			
	custInfoFormPanel.getForm().loadRecord(rec);
	
	custInfoFormPanel.getForm().findField('tel_mobile').setValue(maskPhoneNo(rec.get('tel_mobile')));
	custInfoFormPanel.getForm().findField('tel_home').setValue(maskPhoneNo(rec.get('tel_home')));
	
	// 2. 보유제품리스트
	loadCustPrdList(rec.get('cust_no'));
	
	// 3. 서비스상담이력
	loadCustServiceList(rec.get('cust_no'));
	
	// 4. 서비스상담정보 form reset
	resetServiceForm();
	
	// 5. 주문정보 reset
	resetOrderForm();
	
	// 6. AS 자재정보 reset
	resetAsForm();
	
	// 7. 수령지 & 수거지 reset
	resetDeliveryForm();	
}

/**
 * 서비스상담정보 reset
 */
function resetServiceForm() {
	productFormPanel.getForm().reset();
	serviceFormPanel.getForm().reset();
	transferFormPanel.getForm().reset();
}

/**
 * 주문정보 reset
 */
function resetOrderForm() {
	orderStore.removeAll();
	Ext.getCmp("totalOrderAmt").setValue("0");
	Ext.getCmp("parcel_service_yn").setValue(false);
	calcOrderAmt();
}

/**
 * 자재정보 reset
 */
function resetAsForm() {
	asStore.removeAll();
	Ext.getCmp("totalASAmt").setValue("0");
	calcOrderAmt();
}

/**
 * 서비스상담정보 reset
 */
function resetDeliveryForm() {
	orderAddrForm1Panel.getForm().reset();
	orderAddrForm2Panel.getForm().reset();
}

/**
 * 찾서기사 reset
 */
function resetTransferForm() {
	transferFormPanel.getForm().reset();
}

/**
 * 찾서 지역 - 시도
 */
function getAreaSido(addr) {
	
	var arr_addr = addr.split(" ");
	
	var country = "";
	var txtCountry = "";
	
	if(arr_addr.length > 0) country = arr_addr[0];
	
	if(country.indexOf("서울") > -1) {
		txtCountry = "서울";
	} else if(country.indexOf("부산") > -1) {
		txtCountry = "부산";
	} else if(country.indexOf("대구") > -1) {
		txtCountry = "대구";
	} else if(country.indexOf("인천") > -1) {
		txtCountry = "인천";
	} else if(country.indexOf("광주") > -1) {
		txtCountry = "광주";
	} else if(country.indexOf("울산") > -1) {
		txtCountry = "울산";
	} else if(country.indexOf("세종") > -1) {
		txtCountry = "세종";
	} else if(country.indexOf("강원") > -1) {
		txtCountry = "강원";
	} else if(country.indexOf("경기") > -1) {
		txtCountry = "경기";	
	} else if(country.indexOf("경상남") > -1) {
		txtCountry = "경남";
	} else if(country.indexOf("경남") > -1) {
		txtCountry = "경남";	
	} else if(country.indexOf("경상북") > -1) {
		txtCountry = "경북";
	} else if(country.indexOf("경북") > -1) {
		txtCountry = "경북";	
	} else if(country.indexOf("전라남") > -1) {
		txtCountry = "전남";
	} else if(country.indexOf("전남") > -1) {
		txtCountry = "전남";	
	} else if(country.indexOf("전라북") > -1) {
		txtCountry = "전북";
	} else if(country.indexOf("전북") > -1) {
		txtCountry = "전북";	
	} else if(country.indexOf("충청남") > -1) {
		txtCountry = "충남";
	} else if(country.indexOf("충남") > -1) {
		txtCountry = "충남";	
	} else if(country.indexOf("충청북") > -1) {
		txtCountry = "충북";
	} else if(country.indexOf("충북") > -1) {
		txtCountry = "충북";		
	} else if(country.indexOf("제주") > -1) {
		txtCountry = "제주";
	} else if(country.indexOf("대전") > -1) {
		txtCountry = "대전";
	} else {
		txtCountry = "";
	}
		
	country = txtCountry;
	return country;	
}

/**
 * 찾서 지역 - 시군구
 */
function getAreaSigungu(addr) {
	
	var arr_addr = addr.split(" ");
	
	var addr0 = "";
	var addr1 = "";
	var addr2 = "";
	
	var txtAddr0 = "";
	var txtAddr1 = "";
	var txtAddr2 = "";
	
	if(arr_addr.length > 0) addr0 = arr_addr[0];
	if(arr_addr.length > 1) addr1 = arr_addr[1];
	if(arr_addr.length > 2) addr2 = arr_addr[2];
	
	txtAddr0 = getAreaSido(addr0); //시도
	
	if(addr1.lastIndexOf("시") > -1) {		
		if(addr1.length - 1 == addr1.lastIndexOf("시")) {
			txtAddr1 += addr1;
		}
	}
	
	if(addr1.lastIndexOf("구") > -1) {		
		if(addr1.length - 1 == addr1.lastIndexOf("구")) {
			txtAddr1 += addr1;
		}
	}
	
	if(addr2.lastIndexOf("구") > -1) {
		if(addr2.length - 1 == addr2.lastIndexOf("구")) {
			txtAddr1 += " " + addr2;
		}
	}
	
	if(txtAddr0 == "세종") txtAddr1 = "-";
	
	Ext.Ajax.request({
		
        url: COMMON_URL + 'ajaxServiceAreaInfo',
        params: { 'sido' : txtAddr0, 'sigungu': txtAddr1},
        success: function(response) {
        	
        	var obj = Ext.decode(response.responseText);
        	var form = transferFormPanel.getForm();
        	
        	if(obj.result.length > 0) {
        		
        		var rec = obj.result[0]; // 첫번째 레코드
            	
            	form.findField("service_dept_cd").setValue(rec.dept_cd);
            	form.findField("service_member_id").setValue(rec.member_id);
            	form.findField("service_member_nm").setValue(rec.member_nm);
            	form.findField("service_engineer_id").setValue(rec.member_id);
            	form.findField("service_engineer_nm").setValue(rec.member_nm);
            	form.findField("service_engineer_tel_mobile").setValue(rec.agency_tel);
            	
        	} else {        		
        		Ext.Msg.alert('Notice', "고객의 주소지에 해당하는 찾서 지역이 없습니다.");
        		return;
        	}
        },
        failure: function(result, request) {
        	Ext.Msg.alert('Notice', "찾서지역 조회 중 오류가 발생하였습니다.");
    		return;
		}
    });		
}


/**
 * 찾서기사 세팅
 * @param dept_cd
 * @param member_id
 * @param member_nm
 * @param tel_mobile
 */
function setServiceMember(dept_cd, member_id, member_nm, tel_mobile) {
	
	var form = transferFormPanel.getForm();
	form.findField("service_dept_cd").setValue(dept_cd);
	form.findField("service_member_id").setValue(member_id);
	form.findField("service_member_nm").setValue(member_nm);
	
	// 찾서
	if(form.findField("service_type").getSubmitValue() == SERVICE_CODE_GO1 
		|| form.findField("service_type").getSubmitValue() == SERVICE_CODE_GO2) {
		form.findField("service_engineer_id").setValue(member_id);
		form.findField("service_engineer_nm").setValue(member_nm);
		form.findField("service_engineer_tel_mobile").setValue(maskPhoneNo(tel_mobile));
	}
}

/**
 * 서비스 구분
 * @param service_code
 */
function setServiceTypeAtion(service_type) {

	var tform = transferFormPanel.getForm();
	var cform = custInfoFormPanel.getForm();
	var sform = serviceInfoFormPanel.getForm();
	
	if(service_type == SERVICE_CODE_AS) { // AS 선택
		
		Ext.getCmp("chk_as_group").setDisabled(false);	
		
		Ext.getCmp("btnOrderAdd").setDisabled(false);	 
		Ext.getCmp("btnOrderRemove").setDisabled(false);
		
		Ext.getCmp("btnAsAdd").setDisabled(false);
		Ext.getCmp("btnAsRemove").setDisabled(false);
		
		sform.findField("payment_amt").setReadOnly(false);
		
		resetTransferForm();
		tform.findField("service_trans_type").setValue("TR001"); // AS 담당
		
		orderTabPanel.setActiveTab(0);
		
	} else if(service_type == SERVICE_CODE_ORDER) { // 주문 선택
			
		Ext.getCmp("chk_as_group").setDisabled(true);
		
		Ext.getCmp("btnOrderAdd").setDisabled(false); 
		Ext.getCmp("btnOrderRemove").setDisabled(false);
		
		Ext.getCmp("btnAsAdd").setDisabled(true);
		Ext.getCmp("btnAsRemove").setDisabled(true);
		
		sform.findField("payment_amt").setReadOnly(false);
		
		resetTransferForm();
		tform.findField("service_trans_type").setValue("TR003"); // 주문
		
		resetAsForm();
		
		orderTabPanel.setActiveTab(0);
		
	} else if(service_type == SERVICE_CODE_GO1 || service_type == SERVICE_CODE_GO2) { // 찾서 선택
		
		Ext.getCmp("chk_as_group").setDisabled(true);
		
		Ext.getCmp("btnOrderAdd").setDisabled(true); 
		Ext.getCmp("btnOrderRemove").setDisabled(true);
		
		Ext.getCmp("btnAsAdd").setDisabled(false);
		Ext.getCmp("btnAsRemove").setDisabled(false);
		
		sform.findField("payment_amt").setReadOnly(false);
		
		resetTransferForm();
		tform.findField("service_trans_type").setValue("TR002"); // 찾서
		
		resetOrderForm();
		
		// 찾서 지역 검색
		var addr = cform.findField("address1").getValue();
		getAreaSigungu(addr); 
		
		orderTabPanel.setActiveTab(1);
		
	} else if(service_type == SERVICE_CODE_SALES) { // 보상
		
		Ext.getCmp("chk_as_group").setDisabled(true);
		
		Ext.getCmp("btnOrderAdd").setDisabled(false); 
		Ext.getCmp("btnOrderRemove").setDisabled(false);
		
		Ext.getCmp("btnAsAdd").setDisabled(true);
		Ext.getCmp("btnAsRemove").setDisabled(true);
		
		sform.findField("payment_amt").setReadOnly(false);
		
		resetTransferForm();
		tform.findField("service_trans_type").setValue("TR003"); // 판매
		
		resetAsForm();
		
		orderTabPanel.setActiveTab(0);
		
	} else if(service_type == SERVICE_CODE_CLAIME1 || service_type == SERVICE_CODE_CLAIME2) { // 클레임
		
		Ext.getCmp("chk_as_group").setDisabled(true);
		
		Ext.getCmp("btnOrderAdd").setDisabled(true); 
		Ext.getCmp("btnOrderRemove").setDisabled(true);
		
		Ext.getCmp("btnAsAdd").setDisabled(true);
		Ext.getCmp("btnAsRemove").setDisabled(true);
		
		sform.findField("payment_amt").setReadOnly(true);
		
		resetTransferForm();
		tform.findField("service_trans_type").setValue("TR004"); // 클레임
		
		resetOrderForm();		
		resetAsForm();
		
		orderTabPanel.setActiveTab(0);
		
	} else {
		
		Ext.getCmp("chk_as_group").setDisabled(true);
		
		Ext.getCmp("btnOrderAdd").setDisabled(true); 
		Ext.getCmp("btnOrderRemove").setDisabled(true);
		
		Ext.getCmp("btnAsAdd").setDisabled(true);
		Ext.getCmp("btnAsRemove").setDisabled(true);
		
		sform.findField("payment_amt").setReadOnly(true);
		
		tform.findField("service_trans_type").setValue("TR005"); // 기타
		
		resetOrderForm();		
		resetAsForm();
		
		orderTabPanel.setActiveTab(0);
	}
	
	setDeliveryAddr();
	setPickupAddr();
}


/**
 * 수령지 세팅
 */
function setDeliveryAddr() {
	
	var custForm = custInfoFormPanel.getForm();
	var form = orderAddrForm1Panel.getForm();
	
	var cust_no = custForm.findField("cust_no").getValue();
	var cust_nm = custForm.findField("cust_nm").getValue();
	var tel_mobile = custForm.findField("tel_mobile").getValue();
	var tel_home = custForm.findField("tel_home").getValue();
	var zipcode = custForm.findField("zipcode").getValue();
	var address1 = custForm.findField("address1").getValue();
	var address2 = custForm.findField("address2").getValue();
	
	form.findField("delivery1_owner_nm").setValue(cust_nm);
	form.findField("delivery1_tel_mobile").setValue(tel_mobile);
	form.findField("delivery1_tel_home").setValue(tel_home);
	form.findField("delivery1_zipcode").setValue(zipcode);
	form.findField("delivery1_address1").setValue(address1);
	form.findField("delivery1_address2").setValue(address2);	
}

/** 
 * 수거지 세팅
 */
function setPickupAddr() {
	
	var custForm = custInfoFormPanel.getForm();
	var form = orderAddrForm2Panel.getForm();
	
	var cust_no = custForm.findField("cust_no").getValue();
	var cust_nm = custForm.findField("cust_nm").getValue();
	var tel_mobile = custForm.findField("tel_mobile").getValue();
	var tel_home = custForm.findField("tel_home").getValue();
	var zipcode = custForm.findField("zipcode").getValue();
	var address1 = custForm.findField("address1").getValue();
	var address2 = custForm.findField("address2").getValue();
	
	form.findField("delivery2_owner_nm").setValue(cust_nm);
	form.findField("delivery2_tel_mobile").setValue(tel_mobile);
	form.findField("delivery2_tel_home").setValue(tel_home);
	form.findField("delivery2_zipcode").setValue(zipcode);
	form.findField("delivery2_address1").setValue(address1);
	form.findField("delivery2_address2").setValue(address2);
}


var arrFormErrCd = [["-900",  "서비스 번호 오류"]
    , ["-990",  "제품정보 저장 오류"]
	, ["-991", 	"서비스 상담 정보 저장 오류"]
	, ["-992", 	"주문정보 저장"]
	, ["-993", 	"AS사용자재정보 저장"]
	, ["-994", 	"배송지 & 수거지 저장"]
	, ["-995", 	"배송지 & 수거지 저장"]
	, ["-996", 	"이력 저장"]	
	, ["-999", 	"고객정보 저장 오류"]
];
 
 
function getErrMsg(errCd) {
	
	for(i=0; i<arrFormErrCd.length; i++){
		if(arrFormErrCd[i][0] == errCd) {
			return arrFormErrCd[i][1];
		}
	}
	
	return "";
}