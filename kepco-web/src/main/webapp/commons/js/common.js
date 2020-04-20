var URL_LINK = "http://"+window.location.hostname+"/";
var URL_LINKS = "https://"+window.location.hostname+"/";
var NUM = "0123456789";
var NUM1 = "0123456789_-";
var SALPHA = "abcdefghijklmnopqrstuvwxyz";
var UALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
var ALPHA = UALPHA+SALPHA;
var EMAIL = "!#$%&*+-./=?@^_`{|}"+NUM+ALPHA;
var WATCHWORD = "!@.#,$%^*&_-" + ALPHA + NUM;
var ERRORMSG = "";
var SPECIALCHAR = "!#$%&*+-./=?@^`{|}";
var BPROCESSING = 0;
var PAGE_SIZE = 20;

var COMMON_URL = CONTEXT_PATH;
var COMMON_PATH = "";
var COMMON_PATH_JS =  COMMON_PATH + "/common/js";
var COMMON_PATH_IMG =  COMMON_PATH + "/common/images";
var COMMON_URL_FILE =  COMMON_URL + "/files";
var COMMON_URL_FILE_DOWN =  COMMON_URL_FILE + "/download";
var COMMON_URL_FILE_TEMPLATE =  COMMON_URL_FILE + "/template";


var TIMEOUT_SEC = 600000000;

var MARK_ASTERISK = '<span style="color:red;font-weight:bold" data-qtip="Required">*</span>';
var FRAME_CONTENT_HEIGHT = document.documentElement.scrollHeight;

var formLabelStyle = 'border: 1px solid #cccccc;background:#f3f3f3;text-align:center;height:22px;align:absmiddle;margin-top:0px;';

var regPhone = /^(01([1|6|7|8|9])-([0-9]{3,4})-([0-9]{4})|010-([0-9]{4})-([0-9]{4})|(15|16|18)([0-9]{2})-([0-9]{4})|(030|050)([0-9]{1})-([0-9]{4})-([0-9]{4})|(02|051|053|032|062|042|052|044|031|033|043|041|063|061|054|055|064)-([0-9]{3,4})-([0-9]{4}))$/;

var regPhone2 = /^((01([0|1|6|7|8|9])-([0]{3,4})-([0-9]{4})))$/;

function getWeekDay() {
	 var now = new Date();
     var nowDate = now.getDate();
     now.setDate( nowDate - 7 );     
     return Ext.Date.format(now,'Ymd');
}

function getTenDay() {
	var now = new Date();
    var nowDate = now.getDate();
    now.setDate( nowDate - 11 );     
    return Ext.Date.format(now,'Ymd');
}

function getYesterDay() {
	var now = new Date();
    var nowDate = now.getDate();
    now.setDate( nowDate - 1 );     
    return Ext.Date.format(now,'Ymd');
}

function getMonthDay() {
	 var now = new Date();
    var nowDate = now.getDate();
    now.setDate( nowDate - 30 );     
    return Ext.Date.format(now,'Ymd');
}


/**
 * "yyyyMMddHHmmSS" 날짜를 miliseconds 단위로 변환.
 * @param str
 * @returns
 */
function getTimeMilisec(str){
	var y = str.substr(0, 4);
	var m = str.substr(4, 2);
	var d = str.substr(6, 2);
	var hh = str.substr(8, 2);
	var mm = str.substr(10, 2);
	var ss = str.substr(12, 2);
	
	return Date.UTC(y,m-1,d,hh,mm,ss,0);
}


/**
 * <PRE>
 * selectComboBox
 * </PRE>
 * @param   combo_id : 콤보box id
 * @param   code : 부모 코드(parent_code) 아이디
 */
function selectComboBox(combo_id, parent_code) {
	
    var options = { 
           	beforeSend  : showRequest,
           	success     : function(data, status) {           		
           		$('#'+combo_id).append(new Option("선택", ""));
           		$.each(data.result, function(i, combo) 
				{  
					$('#'+combo_id).append(new Option(combo.code_local_nm, combo.code));
         		});
           },
           url         : COMMON_URL + "/ajaxCodeCombo",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : {parent_code: parent_code}
     };             
    
     $.ajax(options);
}

/**
 * <PRE>
 * setSearchPeriod
 * </PRE>
 * @param   period : 검색기간(String)
 */
function setSearchPeriod(period){ 
	var settingDate = new Date();
	var today = new Date();	
	var settingEndDate;
	
	switch(period){
		case 'today': //오늘
			$( "#sdateView" ).datepicker( "setDate", today);
			$( "#edateView" ).datepicker( "setDate", today);
			break;
			
		case 'weekly': //7일전부터
			settingDate.setDate(today.getDate()-7);
			$( "#sdateView" ).datepicker( "setDate", settingDate);
			$( "#edateView" ).datepicker( "setDate", today);
			break;
			
		case 'montly': //한달전부터
			settingDate.setMonth(today.getMonth()-1);
			$( "#sdateView" ).datepicker( "setDate", settingDate);
			$( "#edateView" ).datepicker( "setDate", today);
			break;
			
		case 'thisMonth': //이번달 1일~오늘
			settingDate.setMonth(today.getMonth());
			settingDate.setDate(1);
			$( "#sdateView" ).datepicker( "setDate", settingDate);
			$( "#edateView" ).datepicker( "setDate", today);
			break;	
		
		case 'lastMonth': //저번달 1일~말일
			settingDate.setMonth(today.getMonth()-1);
			settingDate.setDate(1);
			$( "#sdateView" ).datepicker( "setDate", settingDate);
			
			settingEndDate = settingDate;
			settingEndDate.setMonth(settingDate.getMonth()+1);
			settingEndDate.setDate(settingDate.getDate()-1);
			$( "#edateView" ).datepicker( "setDate", settingEndDate);
			break;
		
		case 'twoMonthsAgo': //2개월전 1일~말일
			settingDate.setMonth(today.getMonth()-2);
			settingDate.setDate(1);
			$( "#sdateView" ).datepicker( "setDate", settingDate);
			
			settingEndDate = settingDate;
			settingEndDate.setMonth(settingDate.getMonth()+1);
			settingEndDate.setDate(settingDate.getDate()-1);
			$( "#edateView" ).datepicker( "setDate", settingEndDate);
			break;
			
	}
}

/**
 * setSearchParam
 * 
 * @param  sdateView : 검색 시작일
 * @param  edateView : 검색 종료일 
 * @desr   yyyy/mm/dd --> yyyymmdd0000--으로 변경
 */
function setSearchParam(sdateView, edateView){
	//2019/12/12 --> 20191212000000으로 변경
	var sdate = sdateView.split("/").join("")+"000000";
	var edate = edateView.split("/").join("")+"235959";
	
	$("#sdate").val(sdate);
	$("#edate").val(edate);
}

/**
 * setSearchParam2
 * 
 * @param  sdateView : 검색 시작일
 * @param  edateView : 검색 종료일 
 * @desr   yyyy/mm/dd --> yyyymmdd0000으로 변경
 */
function setSearchParam2(sdateView, edateView){
	//2019/12/12 --> 201912120000으로 변경
	var sdate = "";
	var edate = "";
	
	if(sdateView && edateView){
		sdate = sdateView.split("/").join("")+"0000";
		edate = edateView.split("/").join("")+"2359";
	}
	
	$("#sdate").val(sdate);
	$("#edate").val(edate);
}

/**
 * changeLimit
 * 
 * @param	selectbox : data_per_page를 결정하는 selectbox
 * @desr	
 */
function changeLimit(selectbox){
	$("#limit").val(selectbox.value);
	$("#page").val(1);
}


/**
 * <PRE>
 * Scroll 이 없는 새 창을 띄운다
 * </PRE>
 * @param   theURL : 새로 띄울 파일 이름이다
 * @param   winName : 새창 이름
 * @param   winTitle : 새창 title
 * @param width : 새창 가로 크기
 * @param height : 새창 세로 크기
 * @param   param : 추가적인 화면 argument
 */
function openNoScrollWin(theURL, winName, winTitle, width, height, param)
{
  var win = window.open(theURL + "?popupTitle=" + winTitle + "&tableWidth=" + width + param, winName, "menubar=no, scrollbars=no, resizable=no, width=" + width + ", height=" + height);
}

/**
 * <PRE>
 * Scroll 이 있는 새 창을 띄운다
 * </PRE>
 * @param   theURL : 새로 띄울 파일 이름이다
 * @param   winName : 새창 이름
 * @param   winTitle : 새창 title
 * @param width : 새창 가로 크기
 * @param height : 새창 세로 크기
 * @param   param : 추가적인 화면 argument
 */
function openScrollWin(theURL, winName, winTitle, width, height, param)
{
  var win = window.open(theURL + "?popupTitle=" + winTitle + "&tableWidth=" + width + param, winName, "menubar=no, scrollbars=yes, resizable=yes, width="+width+", height="+height) ;
}

/******************************
* Scroll 이 없는 새 창을 띄운다
* -----------------------------
* @param theURL : url 경로
* @param winName : 새창 이름
* @param width : popup width size
* @param height :popup height size
*******************************/
function openNoScrollWin(theURL, winName, width, height)
{
	var win = window.open(theURL, winName, "menubar=no, scrollbars=no, resizable=no, width=" + width + ", height=" + height);
	win.focus();
}


/******************************
* Scroll 이 있는 새 창을 띄운다
* -----------------------------
* @param theURL : url 경로
* @param winName : 새창 이름
* @param width : popup width size
* @param height :popup height size
*******************************/
function openScrollWin(theURL, winName, width, height)
{
  	var win = window.open(theURL, winName, "menubar=no, scrollbars=yes, resizable=yes, width=" + width + ", height=" + height);
	win.focus();
}


/******************************
* Scroll 이 있고, 크기조절 불가 새 창을 띄운다
* -----------------------------
* @param theURL : url 경로
* @param winName : 새창 이름
* @param width : popup width size
* @param height :popup height size
*******************************/
var popups = new Array();
function openScrollWinResizeN(theURL, winName, width, height)
{
  	var popUp = window.open(theURL, winName, "menubar=no, scrollbars=yes, resizable=no, width=" + width + ", height=" + height);
    popups.push(popUp);  	
    popUp.focus();
}


/******************************
* openScrollWinResizeN()함수로 열린 창을 모두 닫는다
*******************************/
function destroyPopUps() 
{
	if(popups.length > 0) { 
	    for(i=0; i<popups.length; i++) 
	    {
	        popups[i].close(); 
	    }
	}
}


/******************************
* 문자열 Valid 검사처리
* -----------------------------
* @param : string, space
* @return : boolean
*******************************/
function checkValid(String, space)
{
	var retvalue = false;

	for (var i=0; i<String.length; i++)
	{
		//String이 0("" 이나 null)이면 무조건 false
		if (space == true)
		{
			if (String.charAt(i) == ' ')
			{
				//String이 0이 아닐때 space가 있어야만 true(valid)
				retvalue = true;
				break;
			}
		}
		else
		{
			if (String.charAt(i) != ' ')
			{
				//string이 0이 아닐때 space가 아닌 글자가 있어야만 true(valid)
				retvalue = true;
				break;
			}
		}
	}//end for

	return retvalue;
}

/******************************
*  Empty 및 공백 처리
* -----------------------------
*  @param : field, error_msg
*  @return : boolean
*******************************/
function isEmpty(field, error_msg)
{
	// error_msg가 ""이면 alert와 focusing을 하지 않는다
	if(error_msg == "") {
		if(!checkValid(field.value, false))	{
			return true;
		} else {
			return false;
		}
	} else {
		if(!checkValid(field.value, false)) {
			alert(error_msg);
			field.focus() ;
			return true;
		} else {
			return false;
		}
	}
}

/******************************
* 문자열 Valid 검사처리 (for hidden value)
* -----------------------------
* @param : field, error_msg
* @return : boolean
*******************************/
function isNotSet(field, error_msg)
{
	//for hidden field....
	if(field.value == "")
	{
		alert(error_msg);
		return true;
	}else{
		return false;
	}
}


/******************************
* space 있는지 검사
* -----------------------------
* @param : field, error_msg
* @return : boolean
*******************************/
function haveSpace(field, error_msg)
{
	if(checkValid(field.value, true))
	{
		alert(error_msg);
		field.focus();
		field.select();
		return true;
	}
	return false;
}


/******************************
* check number
* -----------------------------
* @param : field, error_msg
* @return : boolean
*******************************/
function isNotNumber(field, error_msg)
{
	var val = field.value;

	if(isNaN(val) ) {
		if(error_msg.length > 0) {
			alert(error_msg);
			field.focus();
			field.select();
		}
		return true;
	} else {
		return false;
	}
}


/******************************
*  기능 : 숫자만 입력 가능
*******************************/
function onlyNumber()
{
 
  if((event.keyCode >= 48 && event.keyCode <= 57) || (event.keyCode >= 96 && event.keyCode <= 105) || event.keyCode == 46)
  {
    event.returnValue = true;
  }
  else
  {
    switch(event.keyCode)
    {
    case 8:         /* Backspace */
    	event.returnValue = true;
    case 9:         /* Tab */
    	event.returnValue = true;
    case 13:        /* Enter */
    case 35:        /* End */
    case 36:        /* Home */
    case 37:        /* Left Arrow */
    case 38:        /* Up Arrow */
    case 39:        /* Right Arrow */
    case 40:        /* Down Arrow */
    case 45:
    case 46:        /* Del */
    case 109:
    case 144:       /* Num lock */
    case 189:       /* - */
        event.returnValue = true;
        break;    
    default:
        event.returnValue = false;
        break;
    }    
  }
}

/******************************
* NumberCheck And Empty Check
* -----------------------------
* @param : field, error_msg
* @return : boolean
*******************************/
function isNotNumberOrEmpty(field, error_msg)
{
	var val = field.value;

	if(val.length == 0 || isNaN(val) ) {
		if(error_msg.length > 0) {
			alert(error_msg);
			field.focus();
			field.select();
		}
		return true;
	} else {
		return false;
	}
}


/******************************
* alertAndFocus
* -----------------------------
* @param : field, error_msg
* @return : void
*******************************/
function alertAndFocus(field, error_msg)
{
  	alert(error_msg);
  	field.focus();
  	field.select();
}

/******************************
* alertAndFocus
* -----------------------------
* @param : String 알파벳과 숫자만~ Check
* @return : boolean
*******************************/
function isNotAlphaNumeric(field, error_msg)
{
	for (var i=0; i < field.value.length; i++)
	{
		if ( ( (field.value.charAt(i) < "0") || (field.value.charAt(i) > "9") ) &&
		( ( (field.value.charAt(i) < "A") || (field.value.charAt(i) > "Z") ) &&
		( (field.value.charAt(i) < "a") || (field.value.charAt(i) > "z") ) ) )
		{
			alert(error_msg);
			field.focus();
			field.select();
			return true;
		}
	}
	return false;
}
/******************************
* @param : String 알파벳~ Check
* @return : boolean
*******************************/
function isNotAlpha(field, error_msg)
{
	for (var i=0; i < field.value.length; i++)
	{
		if ( ( (field.value.charAt(i) < "A") || (field.value.charAt(i) > "Z") ) &&
		( (field.value.charAt(i) < "a") || (field.value.charAt(i) > "z") ))
		{
			alert(error_msg);
			field.focus();
			field.select();
			return true;
		}
	}
	return false;
}

/******************************
* @param : String 알파벳~ Check* 
*******************************/

function isNotUpperAlpha(field, error_msg)
{

	for (var i=0; i < field.value.length; i++)
	{
		if ( (field.value.charAt(i) < "A") || (field.value.charAt(i) > "Z"))
			{
			alert(error_msg);
			field.focus();
			field.select();			
			field.value = "";			

		}
	}
}

/******************************
* @param : String 숫자만~ Check
* @return : boolean
*******************************/
function isNotNumeric(field, error_msg)
{
	for (var i=0; i < field.value.length; i++)
	{
		if ((field.value.charAt(i) < "0") || (field.value.charAt(i) > "9"))
		{
			alert(error_msg);
			field.focus();
			field.select();
			return true;
		}
	}
	return false;
}

/******************************
* @param : String 이메일~ Check
* @return : boolean
*******************************/
function isEmail(field, error_msg){
	var checkEmail = /([\w-\.]+)@((\[[0 -9]{1,3}\.[0 -9]{1,3}\.[0 -9]{1,3}\.)|(([\w -]+\.)+))([a -zA -Z]{2,4}|[0 -9]{1,3})(\]?)$/;	
	if(!checkEmail.test(field)){
		alert(error_msg);
		field.focus();
		field.select();
		return true;
	}
	return false;
}

function isExtjsEmail(value, error_msg){
	var checkEmail = /([\w-\.]+)@((\[[0 -9]{1,3}\.[0 -9]{1,3}\.[0 -9]{1,3}\.)|(([\w -]+\.)+))([a -zA -Z]{2,4}|[0 -9]{1,3})(\]?)$/;	
	if(!checkEmail.test(value)){
		Ext.Msg.alert('Error',error_msg);
		return true;
	}
	return false;
}

/******************************
* String length return
* -----------------------------
* @param : field
* @return : int
*******************************/
function strLength(field)
{
	var Length = 0;
	var Nav = navigator.appName;
	var Ver = navigator.appVersion;
	var IsExplorer = false;
	var ch;

	if ( (Nav == 'Microsoft Internet Explorer') && (Ver.charAt(0) >= 4) )
	{
		IsExplorer = true;
	}

	if(IsExplorer)
	{
		for(var i = 0 ; i < field.value.length; i++)
		{
			ch = field.value.charAt(i);

			if ((ch == "\n") || ((ch >= "ㅏ") && (ch <= "히")) || ((ch >="ㄱ") && (ch <="ㅎ"))) {
		    	Length += 2;
			} else {
		    	Length += 1;
			}
		}
	} else {
		Length = field.value.length ;
	}
	return Length;
}

/******************************
* 문자열 길이제한
* -----------------------------
* @param : field, min, max, error_msg
* @return : boolean
*******************************/
function isOutOfRange(field, min, max, error_msg)
{
	if(strLength(field) < min || strLength(field) > max)
	{
		alert(error_msg);
		field.focus();
		field.select();
		return true;
	}
	return false;
}


/******************************
* 문자열 길이제한
* -----------------------------
* @param : field, min, error_msg
* @return : boolean
*******************************/
function isOutOfMinRange(field, min, error_msg)
{
	if(strLength(field) < min )
	{
		alert(error_msg);
		field.focus();
		field.select();
		return true;
	}
	return false;
}



/******************************
* exact length check
* -----------------------------
* @param : field, len, error_msg
* @return : boolean
*******************************/
function isNotExactLength(field, len, error_msg) {

  if(strLength(field) != len) {
    alert(error_msg);
    field.focus();
    field.select();
    return true;
  }
  return false;
}


/******************************
* check only number
* -----------------------------
* @param : field
* @return : String
*******************************/
function isNumber(field) {

	var num = field.value;

	if(num.match(/^\d+$/ig) == null){
		return false;
	} else {
		return true;
	}
}


/******************************
* check number range
* -----------------------------
* @param : field, min, max, error_msg
* @return : boolean
*******************************/
function isOutOfNumericRange(field, min, max, error_msg) {

	if(field.value < min || field.value > max) {
		alert(error_msg);
		field.focus();
		field.select();
		return true;
	}
	return false;
}


/******************************
* get only number
* -----------------------------
* @param : field
* @return : String
*******************************/
function getOnlyNumber(field) {

	var regExp = /[^0-9]/;
	var str = "";

	for(var i=0; i<field.value.length; i++){
		var checkStr = field.value.charAt(i);
		str += checkStr.replace(regExp,"");
	}
	return str;
}


/******************************
* select box selected check
* -----------------------------
* @param : field, error_msg
* @return : boolean
*******************************/
function isNotSelected(field, error_msg) {

	if(getSelectedVal(field) == "") {
		alert(error_msg);
		field.focus() ;
		return true;
	} else {
		return false;
	}
}

/******************************
* return selected value
* -----------------------------
* @param : field
* @return : String
*******************************/
function getSelectedVal(field) {
	return field.options[field.selectedIndex].value;
}


/******************************
* keep selectbox status
* -----------------------------
* @param : field, val
* @return : String
*******************************/
function keepSelStat(field, val){

	var count = field.length;

	for(i=0; i<count; ++i) {
		if(field.options[i].value == val) {
			field.options[i].selected = true;
			return;
		}
	}
}

/******************************
* check radio button
* -----------------------------
* @param : field, error_msg
* @return : String
*******************************/
function isNotCheckedRadio(field, error_msg) {
	if ( field == null ) {
		alert(error_msg);
		return true;
	}

	if ( field.length == null ) {
		if ( field.checked == true ) {
			return false;
		} else {
			alert(error_msg);
			return true;
		}
	}

	for(i = 0; i < field.length; i++) {
		if(field[i].checked == true) {
			return false;
		}
	}
	alert(error_msg);
	return true;
}

/******************************
* getCheckedRadioIndex
* -----------------------------
* @param : field, error_msg
* @return : int
*******************************/
function getCheckedRadioIndex(field){

	for(i = 0; i < field.length; i++) {
		if(field[i].checked) {
			return i;
		}
	}
	return -1;
}

/******************************
* uncheck radio button
* -----------------------------
* @param : field
* @return : void
*******************************/
function uncheckRadio(field) {
	for(i = 0; i < field.length; i++) {
		field[i].checked = false;
	}
}

/******************************
* return checked value
* -----------------------------
* @param : field
* @return : void
*******************************/
function getRadioVal(field) {
	for(i = 0; i < field.length; i++) {
		if(field[i].checked == true)
	  	return field[i].value;
	}
	return "";
}


/************************************************/
/*     radio 셀렉트박스 상태유지함수                                     */
/************************************************/
function keepRadioIndexStat(field,index){	
	field[index].checked = true;
}

/******************************
* check field type
* -----------------------------
* @param : field, spc
* @return : boolean
*******************************/
function checkType(field, spc) {
	var i;
	var s = field.value;
	for(i=0; i<s.length; i++) {
		if (spc.indexOf(s.substring(i, i+1)) < 0) {
			return false;
		}
	}
	return true;
}


/******************************
* checkTypeAtLeast
* -----------------------------
* @param : field, spc
* @return : boolean
*******************************/
function checkTypeAtLeast(field, spc) {
 	var i;
    var j = 0;
    var s = field.value;

    for(i=0; i < s.length; i++) {
        if (spc.indexOf(s.substring(i, i+1)) > 0) {
            j++;
        }
    }

    if(j > 0){
        return true;
    }else{
        return false;
    }
}

/******************************
 * check email
 * -----------------------------
 * @param : field
 * @return : String
 *******************************/
function checkEmail(field) {
	var email = field.value;
	var pattern = /^[_a-zA-Z0-9-\.]+@[\.a-zA-Z0-9-]+\.[a-zA-Z]+$/;
	return pattern.test(email);
}


/******************************
 * check URL
 * -----------------------------
 * @param : field
 * @return : String
 *******************************/
function checkUrl(field){

	var s = field.value;
	if(s.search(/^\s*['http://']+[\w\~\-\.]+\.[\w\~\-]+(\.[\w\~\-]+)+\s*$/g)>=0){
		return true;
	}else{
		alert("url 형식이 잘못되었습니다.");
		field.focus();
		field.select();
		return false;
	}
}



/******************************
* 일정 개수의 문자가 입력되면 포커스를 이동
* -----------------------------
* @param : current, next, len
* @return : boolean
*******************************/
function moveFocus(current, next, len)
{
	if(len == '0')
	{
		next.focus();
		return;
	}

	if(current.value.length == len)
	{
		next.focus();
		return;
	}
}

/******************************
* trim
* -----------------------------
* @param : str
* @return : String
*******************************/
function trim(str) {
	return str.replace(/(^\s*)|(\s*$)/g, "");
}

/******************************
* _trim
* -----------------------------
* @param : str
* @return : String
*******************************/
function _trim(field)
{
	field.value = trim(field.value);
}


/******************************
* lpad
* -----------------------------
* @param : str, fillLength, fillStr
* @return : String
*******************************/
function lpad(str, fillLength, fillStr) {

	str = str + "";

	if(str == '' || str.length >= fillLength || fillStr == '') {
		return str;
	}

	var padStr = "";
	for(var i = 0; i < fillLength - str.length; i++ ) {
		padStr += fillStr;
	}

	return padStr + "" + str;
}


/******************************
* rpad
* -----------------------------
* @param : str, fillLength, fillStr
* @return : String
*******************************/
function rpad(str, fillLength, fillStr) {

	str = str + "";

	if(str == '' || str.length >= fillLength || fillStr == '') {
		return str;
	}

	var padStr = "";
	for(var i = 0; i < fillLength - str.length; i++ ) {
		padStr += fillStr;
	}

	return str + "" + padStr;
}

/******************************
* ucase
* -----------------------------
* @param : field
* @return : String
*******************************/
function ucase(field)
{
	return field.value.toUpperCase();
}


/******************************
* lcase
* -----------------------------
* @param : field
* @return : String
*******************************/
function lcase(field)
{
	return field.value.toLowerCase();
}


/******************************
* addComma
* -----------------------------
* @param : num
* @return : Number
*******************************/
/*function addComma(num)
{alert(num);
	return Number(String(num).replace(/\..*|[^\d]/g,"")).toLocaleString().slice(0,-3);
}*/

function addComma(nStr){
	nStr += '';
	x = nStr.split('.');
	x1 = x[0];
	x2 = x.length > 1 ? '.' + x[1] : '';
	var rgx = /(\d+)(\d{3})/;
	while (rgx.test(x1)) {
		x1 = x1.replace(rgx, '$1' + ',' + '$2');
	}
	return x1 + x2;
}

function commify(n) {
	  var reg = /(^[+-]?\d+)(\d{3})/;   // 정규식
	  n += '';                          // 숫자를 문자열로 변환

	  while (reg.test(n))
	    n = n.replace(reg, '$1' + ',' + '$2');

	  return n;
	}

/******************************
* replaceComma
* -----------------------------
* @param : num
* @return : String
*******************************/
function replaceComma(num)
{
	return String(num).replace(/\,/g,"");
}

/******************************
* replaceComma
* -----------------------------
* @param : num
* @return : String
*******************************/
function chkLength(obj, obj2, length_limit) {

    var length = calculate_msglen(obj.value);

    obj2.value = length;

    if (length > length_limit) {
        alert("최대 " + length_limit + "byte이므로 초과된 글자수는 자동으로 삭제됩니다.");
        obj.value = obj.value.replace(/\r\n$/, "");
        obj.value = assert_msglen(obj.value, obj2, length_limit);
    }
}


/************************************************/
/*     			byte 계산		        	*/
/************************************************/
function calculate_msglen(message) {
    var nbytes = 0;

    for (i=0; i<message.length; i++) {

        var ch = message.charAt(i);

        if(escape(ch).length > 4) {
            nbytes += 2;
        } else if (ch == '\n') {
            if (message.charAt(i-1) != '\r') {
                nbytes += 1;
            }
        } else if (ch == '<' || ch == '>') {
            nbytes += 4;
        } else {
            nbytes += 1;
        }
    }

    return nbytes;
}


function assert_msglen(message, maximum) {
    var inc    = 0;
    var nbytes = 0;
    var msg    = "";
    var msglen = message.length;

    for (i=0; i<msglen; i++) {
    	
        var ch = message.charAt(i);
        if (escape(ch).length > 4) {
            inc = 2;
        } else if (ch == '\n') {
            if (message.charAt(i-1) != '\r') {
                inc = 1;
            }
        } else if (ch == '<' || ch == '>') {
            inc = 4;
        } else {
            inc = 1;
        }
        nbytes += inc;
        
        if ((nbytes) > maximum) {
        	
            break;
        }
    
        msg += ch;
    }
    
    return msg;
}

/************************************************/
/*    특정키 다운 시 function 실행      		*/
/************************************************/

/******************************
 *  ENTER키 다운 되었을때 넘겨받은 Function실행
 * -----------------------------
 * @param : func
 * @return : void
 *******************************/
function enterKeyDown(func)
{
	enter = event.keyCode;

	if(enter == 13){
		eval(func);
	}
}

/******************************
 *  TAB키 다운 되었을때 넘겨받은 Function실행
 * -----------------------------
 * @param : func
 * @return : void
 *******************************/
function tabKeyDown(func)
{
	enter = event.keyCode;

	if(enter == 09){
		eval(func);
	}
}

/******************************
 *  char to ascii
 * ----------------------------
 * @param : str
 * @return : String
 ******************************/
function Chr2Asc(str)
{
	var Alpha = ' !"#$%& ()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ ]^_`abcdefghijklmnopqrstuvwxyz{|}~'

	if (str == "'") {
		return 39;
	} else if (escape(str) == "%5C") {
		return 92;
	} else if (Alpha.indexOf(str) < 0) {
		return Alpha.indexOf(str);
	} else {
		return Alpha.indexOf(str)+ 32;
	}
}



/******************************
 *  ascii to char
 * ----------------------------
 * @param : str
 * @return : String
 ******************************/
function Asc2Chr(Code)
{
	var Alpha = ' !"#$%& ()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[ ]^_`abcdefghijklmnopqrstuvwxyz{|}~'

	if (Code == 39) return "'";

	else if (Code == 92) return unescape("%5C");

	else return Alpha.charAt(Code - 32);
}

/******************************
 *  get age
 * ----------------------------
 * @param : jumin1 - 앞(7)
 * @return : String
 ******************************/
 function getAge(jumin1) {

	var now = new Date();
	
//	now.setMonth(now.getMonth() - 6);
//	now.setDate(now.getDate() + 1);
	
	var year = now.getFullYear();
	var mon = now.getMonth()+1;
	var day = now.getDate();

	
//	alert(year+" : "+mon+" : "+day);
	
	var myFlag = parseInt(jumin1.substring(6));
	var myYear 	= (myFlag > 2) ? parseInt("20" + jumin1.substring(0,2)) : parseInt("19" + jumin1.substring(0,2));
	var myMonth = parseInt(jumin1.substring(2,4));
	var age = year - myYear;
	
	if(myMonth > mon) age = age - 1;

	return age;
}

 function getbirthAge(birth) {

	var now = new Date();
	var year = now.getFullYear();
	var mon = now.getMonth()+1;
	var day = now.getDate();


	var myYear 	= birth.substr(0,4);
	var myMonth = parseInt(birth.substring(4,6));
	var age = year - myYear;
	if(myMonth > mon) age = age - 1;

	return age;

} 

/******************************
 *  masked phone no
 * ----------------------------
 * @param : phone
 * @return : String
 ******************************/
 function maskPhoneNo(phone) {

	var RegNotNum  = /[^0-9]/g;
	var RegPhonNum = "";
	var DataForm   = "";
	var str = phone;

	// return blank
	if( str == "" || str == null ) return "";

	// delete not number
	str = str.replace(RegNotNum, "");

	if( str.length < 4 ) return str;

	if( str.length > 3 && str.length < 7 )
	{
		DataForm = "$1-$2";
		RegPhonNum = /([0-9]{3})([0-9]+)/;
	}
	else if(str.length == 7 )
	{
		DataForm = "$1-$2";
		RegPhonNum = /([0-9]{3})([0-9]{4})/;
	}
	else if(str.length == 8 )
	{
		DataForm = "$1-$2";
		RegPhonNum = /([0-9]{4})([0-9]{4})/;
	}
	else if(str.length == 9 )
	{
		DataForm = "$1-$2-$3";
		RegPhonNum = /([0-9]{2})([0-9]{3})([0-9]+)/;
	}
	else if(str.length == 10)
	{
		if(str.substring(0,2) == "02") {
			DataForm = "$1-$2-$3";
			RegPhonNum = /([0-9]{2})([0-9]{4})([0-9]+)/;
		} else {
			DataForm = "$1-$2-$3";
			RegPhonNum = /([0-9]{3})([0-9]{3})([0-9]+)/;
		}
	}
	else if(str.length > 10)
	{
		DataForm = "$1-$2-$3";
		RegPhonNum = /([0-9]{3})([0-9]{4})([0-9]+)/;
	}

	while(RegPhonNum.test(str)) {
		str = str.replace(RegPhonNum, DataForm);
	}

	return str;
}

/******************************
 *  masked phone no
 * ----------------------------
 * @param : phone
 * @return : String
 ******************************/
function MaskPhoneNo2(phone, flag){

	var RegNotNum  	= /[^0-9]/g;
	var RegPhonNum 	= "";
	var DataForm 	= "$1-$2-****";
	var str = phone;

	if(flag == "2") {
		DataForm = "$1$2****";
	}

	if( str == "" || str == null ) return "";

	str = str.replace(RegNotNum, "");
	if( str.length < 9 ) return str;

	if(str.length == 9 ) {

		RegPhonNum = /([0-9]{2})([0-9]{3})([0-9]+)/;

	} else if(str.length == 10) {

		if(str.substring(0,2) == "02" ){
			RegPhonNum = /([0-9]{2})([0-9]{4})([0-9]+)/;
		} else {
			RegPhonNum = /([0-9]{3})([0-9]{3})([0-9]+)/;
		}

	} else if(str.length > 10) {

		RegPhonNum = /([0-9]{3})([0-9]{4})([0-9]+)/;
	}

	while(RegPhonNum.test(str)) {
		str = str.replace(RegPhonNum, DataForm);
	}

	return str;
}

function formatCurrencyGrid(amount, meta, rec, rowIndex, colIndex) {
    amount = new String(amount);

	  var amountLength = amount.length;
	  var modulus = amountLength % 3;
	  var currencyString = amount.substr(0,modulus);
	  
	  for(i=modulus; i<amountLength; i=i+3) {
	    
	    if(currencyString != "")
	      currencyString += ",";
	    
	    currencyString += amount.substr(i, 3);
	  }
	  
	  return currencyString;
	  
}


/************************************************/
/*     			날짜관련함수			        	*/
/************************************************/

function DateFunc(sign){
    var date=new Date();
    date = new Date(date.getFullYear(),date.getMonth(),date.getDate());
	return date.getFullYear()+sign+((date.getMonth()+1)<10 ? '0'+(date.getMonth()+1) : (date.getMonth()+1))+sign+(date.getDate()<10 ? '0'+date.getDate() : date.getDate() )+sign;
}


function DateForm(Date, sign){
	
	var year = Date.substring(0,4);
	var month = Date.substring(4,6);
	var day = Date.substring(6,8);
	
	if(Date.length == 6) {
		return year+""+sign+""+month;
	} else if(Date.length == 8) {
		return year+""+sign+""+month+""+sign+""+day;
	} else {
		return
	}
	
}

/* 20150105112536 = 2015-01-05 11:25:36 */
function DateForm2(val){
	
	var year;
	var month;
	var day;
	var hh;
	var mm;
	var ss;
	
	if(val.length == 6){
		hh = val.substring(0,2);
		mm = val.substring(2,4);
		ss = val.substring(4,6);
		return hh+":"+mm+":"+ss;
	}else if(val.length == 8){
		year = val.substring(0,4);
		month = val.substring(4,6);
		day = val.substring(6,8);
		return year+"-"+month+"-"+day;
	}else{
		year = val.substring(0,4);
		month = val.substring(4,6);
		day = val.substring(6,8);
		hh = val.substring(8,10);
		mm = val.substring(10,12);
		ss = val.substring(12,14);
		return year+"-"+month+"-"+day+" "+hh+":"+mm+":"+ss;
	}
}

/* 20150105112536 = 11:25:36 */
function DateTime2Time(val){
	var hh;
	var mm;
	var ss;
	
	hh = val.substring(8,10);
	mm = val.substring(10,12);
	ss = val.substring(12,14);
	return hh+":"+mm+":"+ss;
}

// 현재 날짜값을 yyyy-mm-dd 형식으로 변환해주는 함수
Date.prototype.yyyymmdd = function() {
    var yyyy = this.getFullYear().toString();
    var mm = (this.getMonth() + 1).toString();
    var dd = this.getDate().toString();
    return  yyyy + "-" + (mm[1] ? mm : "0" + mm[0]) + "-" + (dd[1] ? dd : "0" + dd[0]);
}

function toJson(obj){	
	try {

        this.chain = eval('(' + obj + ')');
    } catch (e){

        throw 'JSON convert Error';
    };	

    return this.chain;
}

/******************************
*  Empty 및 공백 처리
* -----------------------------
*  @param : field, error_msg
*  @return : boolean
*******************************/
function isEmptyNotFocus(field, error_msg)
{
	// error_msg가 ""이면 alert와 focusing을 하지 않는다
	if(error_msg == "") {
		if(!checkValid(field.value, false))	{
			return true;
		} else {
			return false;
		}
	} else {
		if(!checkValid(field.value, false)) {
			alert(error_msg);
//			field.focus() ;
			return true;
		} else {
			return false;
		}
	}
}

/************************************************/
/*     			첨부파일다운			        	*/
/************************************************/

function fileDown(filename, org_filename, filepath){
	
	url = COMMON_URL + '/common/FileCheck.jsp?filename='+filename+'&org_filename='+org_filename+'&filepath='+filepath;

	var options = {
	       success     : function(data, result){
	    	  if(data.result == "failure"){
	    		  alert('File Not Found!!');
	    		  return;
	    	  } else {
	    		 location.href = COMMON_URL + '/common/FileDown.jsp?fileName='+filename+'&org_filename='+org_filename+'&fileDir='+filepath;
	    	  }
	       },
	       url         : url,
	       contentType : "application/x-www-form-urlencoded;charset=UTF-8",
	       type        : "get", /* get, post */
	       dataType    : "json"
	};
	
	$.ajax(options);	
	
}

function fileDownload(real_file_name, file_name, file_save_path){
    var options = {
           success     : FileDownResultHandler,
           url         : COMMON_URL + "/FileDown.hrms?filename="+real_file_name+"&org_filename="+file_name+"&filepath="+file_save_path,
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json" /* xml, html, script, json */
    };
    
    $.ajax(options);    
}

function FileDownResultHandler(data, status){
	if(data.result == "success"){
		location.href = COMMON_URL + '/common/FileDown.jsp?fileName='+data.fileName+'&org_filename='+data.orgFileName+'&fileDir='+data.fileDir;
	}else{
		alert("파일이  존재하지 않습니다.");
	}

}	



function fileDown1(filename, org_filename, filepath){

	location.href = COMMON_URL + '/common/FileDown.jsp?fileName='+filename+'&org_filename='+org_filename+'&fileDir='+filepath;	
}



/******************************
* 기능 : 파일 확장자 체크
* @param : f2
*******************************/
function uploadfile_check(f2) {
    var  str_dotlocation,str_ext,str_low;
    str_value  = f2;
   
    str_low   = str_value.toLowerCase(str_value);
    str_dotlocation = str_low.lastIndexOf(".");
    str_ext   = str_low.substring(str_dotlocation+1);
    switch (str_ext) {
     case "csv" :
         return true;
         break;
     default:
         return false;
    }
    
}



/******************************
* 기능 : 파일 확장자 체크
* @param : f2
*******************************/
function uploadfile_checkXlsx(f2) {
    var  str_dotlocation,str_ext,str_low;
    str_value  = f2;
   
    str_low   = str_value.toLowerCase(str_value);
    str_dotlocation = str_low.lastIndexOf(".");
    str_ext   = str_low.substring(str_dotlocation+1);
    switch (str_ext) {
     case "xlsx" :
         return true;
         break;
     default:
         return false;
    }
    
}

/******************************
* 기능 : 일정 개수의 문자가 입력되면 포커스를 이동시킨다.
* @param : current, next, len
*******************************/
function focusMove(current, next, len)
{
  if(len == '0')
  {
    next.focus();
    return;
  }
  
  if(current.value.length == len)
  {
    next.focus();
    return;
  }
}

//radio 상태유지함수
function keepRadioStat(obj,val){
    var count = obj.length;

    //default 설정
    obj[0].checked = true;
    
    for(i = 0; i < count; i++) {
      if(obj[i].value == val){  
        obj[i].checked = true;        
      }
    }    
}

/******************************
* 기능 : extjs form serialize
*******************************/
function serialize_form_values(form)
{
    var serial = '',
        values = form.getValues();

    for(var value in values)
        serial += '&' + value + '=' + values[value];

    return serial.substr(1);
};

function focusMsgAlert(status, msg, field) {		
	Ext.Msg.alert(status, msg, function(btn, text) {
          if (btn == 'ok') {
        	 if(field != undefined) {
        		 field.focus(); 
        	 }
          }
    });
}


//달의 마지막날
function getLastDay(year, month) {	
	return  lastDay = ( new Date( year, month, 0) ).getDate();
}


//숫자를 한글로
function NUM2KOR(obj) {
	
	var str 	= "";	// return할 문자
	var results = "";	// 전달받은 숫자를 지정한 문자와 매칭
	var text = "";		// 매칭된 숫자만큼 문자조합
	var obj_val = obj;

	if (obj !='') {
		results = obj.match(/0/g);
		
		for(i=0; i<results.length; i++) {
			text += "0";
		}
		obj = obj.replace(text,'');

		if (results.length==8) {
			str = "억원";
		} else if (results.length==7) {
			str = "천만원";
			if(obj.length==2) {
				obj = obj.substring(0,1) +"억"+ obj.substring(1,2);
			}
		} else if (results.length==6) {
			str = "백만원";
			if(obj.length==2) {
				obj = obj.substring(0,1) +"천"+ obj.substring(1,2);
			} else {
				obj = obj;
			}
		} else if (results.length==5) {
			str = "십만원";
			if(obj.length==2) {
				obj = obj.substring(0,1) +"백"+ obj.substring(1,2);
			}
		} else if (results.length==4) {
			str = "만원";
		} else if (results.length==3) {
			str = "천원";
		} else if (results.length==2) {
			str = "백원";
		} else if (obj.length>1 && results.length==1) {
			str = "십원";
		} else if (obj.length==1 && results.length==1) {
			str = "원";
		}
		
		str = obj + str;	// +"("+ obj_val +")";
	}
	return str;
};


/*********************************
* 특수문자들을 모두 제거하는 함수
* @param str - 입력받은 값
* 패턴 => 특수문자 또는 대소문구분없는CR(캐리지 리턴) 또는 대소문구분없는LF(줄바꾸기) 또는 대소문구분없는BS(백스페이스)
* @return String
*********************************/
function specialTxT(str){

	//var regExp = /([\{\}\[\]\/?.,;:|\)*~`!^\-_+<>@\#$%&\\\=\(\'\"]|CR|ASCII 0x0d|LF|ASCII 0x0a|BS|ASCII 0x08)/gi;
	var regExp = /([~!@\#$%^&*\(\)_+`\-\=\{\}|\[\]\\:\";\'<>?,.\/]|CR|ASCII 0x0d|LF|ASCII 0x0a|BS|ASCII 0x08)/gi;
	var change_txt = "";
	var return_txt = "";	
	
	//특수문자 제거
	if(regExp.test(str)){
		change_txt = str.replace(regExp, "")
		return_txt = change_txt;
		//alert("특수문자를 제거했습니다. ==>" + t)
	}else{
		return_txt = str;
		//alert("정상적인 문자입니다. ==>" + str)
	}
	
	return return_txt;
};



/*********************************
* 특수문자 제거하고 숫자만 남김
*********************************/
function remainNumber(str) {
	var RegNotNum  = /[^0-9]/g;
	
	// return blank
	if( str == "" || str == null ) return "";

	// delete not number
	str = str.replace(RegNotNum, "");

	return str;
}

/*********************************
 * 제품자재구분 
 *********************************/
function getPrdTypeNm(dat) {
	if(dat == "1") 
		return "제품";
	else if(dat == "2") 
		return "자재";
	else
		return "";
} 


/*********************************
 * 사이트구분 
 *********************************/
function getSiteNm(dat) {
	if(dat == "1") 
		return "한경희생활과학";
	else if(dat == "2") 
		return "리빙(뷰티)";
	else if(dat == "3") 
		return "카페이탈리아";
	else if(dat == "4") 
		return "홈케어";
	else
		return "";
} 

/*********************************
 * 사이트구분 
 *********************************/
function getSiteTelNo(dat) {
	if(dat == "1") 
		return "1577-3555";
	else if(dat == "2") 
		return "1577-3222";
	else if(dat == "3") 
		return "1566-1181";
	else if(dat == "4") 
		return "1566-3321";
	else
		return "1577-3555";
} 

/*********************************
 * 배송추적 
 *********************************/
function popupDeliveryTrack(invoice_no, cop)
{
	invoice_no = (invoice_no) ? invoice_no : "";	// 송장번호	
	cop = (cop) ? cop : "";	// 배송사
	if (cop != "" && invoice_no != "")
	{
		if (cop == "DP001")
		{	// CJ 택배 배송 추적.
			var url = "http://nexs.cjgls.com/web/info.jsp?slipno="+ invoice_no;
			window.open(url, "popupDeliveryTrack", "top=60, left=120, width=690, height=500, toolbar=no, status=no, menubar=no, scrollbars=yes, resizable=no, directories=no");			
		} 
		else if (cop == "DP002") 
		{	// 현대
			var url = "http://www.hlc.co.kr/hydex/jsp/tracking/trackingViewCus.jsp?InvNo="+ invoice_no;
			window.open(url, "popupDeliveryTrack", "top=60, left=120, width=660, height=500, toolbar=no, status=no, menubar=no, scrollbars=yes, resizable=no, directories=no");		
		} 
		else if (cop == "DP003") 
		{	// 한진
			var url = "http://www.hanjin.co.kr/Delivery_html/inquiry/result_waybill.jsp?wbl_num="+ invoice_no;
			window.open(url,"_blank");				
		} 
		else if (cop == "DP004") 
		{	// 우체국
			var url = "http://service.epost.go.kr/trace.RetrieveRegiPrclDeliv.postal?sid1="+ invoice_no;
			window.open(url, "popupDeliveryTrack", "top=60, left=120, width=700, height=500, toolbar=no, status=no, menubar=no, scrollbars=yes, resizable=no, directories=no");		
		}
		else
		{
			alert("배송추적을 지원하지 않는 배송사 입니다.");
		}
	}
	else
	{
		alert("배송 정보를 확인 할 수 없습니다.");	
	}			

}

/**
 * formatNumber(value, n)
 * @param value,n
 * @descr 
 * @returns
 */
function formatNumber(value, n){
	  if(typeof value =="number"){
	    return value.format(n);
	  }else{
	    return "";
	  }
}

/**
 * 포매팅 추가 (프로토타입 추가)
 * @param n
 * @descr 천 단위 표현(,) 및 소수점 표현(n째 자리까지 표현 )
 * @returns
 */
Number.prototype.format = function(n){
  var reg = /\B(?=(\d{3})+(?!\d))/g;
  var strNum = this.toFixed(Math.max(0, ~~n)).replace(reg,',');
  if (n!=0){
	  return strNum.split(".")[0] + "." + strNum.split(".")[1].replace(/,/gi,'');
  }else{
	  return strNum.split(".")[0];
  }
	  
}

function showLoading(){
	$("#loading").show();
}

function hideLoading(){
	$("#loading").hide();
}

