/******************************
* get now date
* -----------------------------
* @param : dateFormat (ex.yyyy-mm-dd) 
* @return : String
*******************************/
function getNowDate(dateFormat) {
	
	var now = new Date();
	
	if(dateFormat == "" || dateFormat == null) {
		dateFormat = "yyyymmdd";
	}
		
	return now.format(dateFormat);
}

/******************************
* get today
* -----------------------------
* @param : sperator
* @return : String
*******************************/
function getToday(separator) {
	
	var currentTime = new Date();
	var month 	= currentTime.getMonth() + 1;
	var day 	= currentTime.getDate();
	var year 	= currentTime.getFullYear();
	
	if(separator == "" || separator == null){
		separator = "";
	}
	
	return year + separator + lpad(month,2,'0') + separator + lpad(day,2,'0');
}

/******************************
* get year
* -----------------------------
* @return : String
*******************************/
function getNowYear() {
	
	var currentTime = new Date();
	var year = currentTime.getFullYear();
	
	return year;
}


/******************************
* get month
* -----------------------------
* @return : String
*******************************/
function getNowMonth() {
	
	var currentTime = new Date();
	var month 	= currentTime.getMonth() + 1;
	
	return lpad(month,2,'0');
}


/******************************
* get day
* -----------------------------
* @return : String
*******************************/
function getNowDay() {
	
	var currentTime = new Date();
	var day = currentTime.getDate();
	
	return lpad(day,2,'0');
}

/******************************
* get day of week
* -----------------------------
* @return : String
*******************************/
function getDayOfWeek() {

	var now = new Date();
	var day = now.getDay(); //일요일=0,월요일=1,...,토요일=6
	var week = new Array('일','월','화','수','목','금','토');

	return week[day];
}


/******************************
* isValidDate - 필드로 입력받는 경우
* -----------------------------
* @return : String
*******************************/
var mInputYear = /^\d{4}$/;
var mInputMonth = /^\d{2}$/;
var mInputDay = /^\d{2}$/;

function isValidDate(obj1, obj2, obj3) {

	var y = parseInt(obj1.value,10);
	var m = parseInt(obj2.value,10)-1;
	var d = parseInt(obj3.value,10);
	var dt = new Date(y, m, d);
	
	if(!mInputYear.test(obj1.value)) {
		alert("유효한 날짜 형식이 아닙니다. 년도는 YYYY 형식으로 입력해 주세요!");
		obj1.value = "";
		obj1.focus();
		return false;
	} else if(parseInt(obj1.value) < 1900 || parseInt(obj1.value) > 2050) {
		alert("유효한 날짜 형식이 아닙니다. 년도는 YYYY 형식으로 입력해 주세요!");
		obj1.value = "";
		obj1.focus();
		return false;
	} else if(!mInputMonth.test(obj2.value)) {
		alert("유효한 날짜 형식이 아닙니다. 월은  MM 형식으로 입력해 주세요!");		
		obj2.value = "";
		obj2.focus();
		return false;
	} else if(!mInputDay.test(obj3.value)) {
		alert("유효한 날짜 형식이 아닙니다. 일은  DD 형식으로 입력해 주세요!");		
		obj3.value = "";
		obj3.focus();
		return false;
	} else if(dt.getFullYear() != y || dt.getMonth() != m || dt.getDate() != d) {
		alert("유효한 날짜가 아닙니다. 다시 확인해 주세요~");
		obj1.value = "";
		obj2.value = "";
		obj3.value = "";
		obj1.focus();
		return false;
	}
	return true;
}