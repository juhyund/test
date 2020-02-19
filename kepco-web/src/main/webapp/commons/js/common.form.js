/******************************
* load form data
* -----------------------------
* @param form : form
* @param data : json data
* @return : boolean
*******************************/
function loadFormData(form, data) {

	for(var i = 0; i < form.elements.length ; i++) {

		var dataVal = eval("data."+form.elements[i].name);
		if(dataVal == undefined) dataVal = "";

		switch(form.elements[i].type.toUpperCase()) {
			case "TEXT" :
				form.elements[i].value = dataVal;
				break;
			case "HIDDEN" :
				form.elements[i].value = dataVal;
				break;
			case "TEXTAREA" :
				form.elements[i].value = dataVal;
				break;
			case "SELECT-ONE" :
				keepSelStat(form.elements[i], dataVal);
				break;
			case "RADIO" :
				checkedBox(form.elements[i], form.elements[i].value, dataVal);
				break;
			case "CHECKBOX" :
				checkedBox(form.elements[i], form.elements[i].value, dataVal);
				break;
		}
	}
	return true;
}

function checkedBox(field, val, data){

	if(val == data) {
		field.checked = true;
	} else {
		field.checked = false;
	}
}

function validFormCheck(form) {

	for(var i = 0; i < form.elements.length ; i++){

		var id = form.elements[i].id;
		var f_name = $("#"+id).attr("f_name");
		var max = $("#"+id).attr("max");
		var min = $("#"+id).attr("min");
		var isChecked = $("#"+id).attr("isChecked");

		if(isChecked != "") {
			if(isChecked == "true") {
				if(swichFormCheck(form.elements[i], f_name) == false) return false;

				//check length
				if(min != "") {
					if(isOutOfRange(form.elements[i], min, max, f_name + "은(는) " + min +"자 이상 " + max + "자 이하로 입력해 주세요!")) return false;
				}
			}
		}
	}
	return true;
}


function swichFormCheck(field, f_name) {

	switch(field.type.toUpperCase()) {
		case "TEXT" :
			if(isEmpty(field, f_name + "을(를) 입력해 주세요")) return false;
			break;
		case "TEXTAREA" :
			if(isEmpty(field, f_name + "을(를) 입력해 주세요")) return false;
			break;
		case "PASSWORD" :
			if(isEmpty(field, f_name + "을(를) 입력해 주세요")) return false;
			break;
		case "SELECT-ONE" :
			if(isNotSelected(field, f_name + "을(를) 선택해 주세요")) return false;
			break;
		case "RADIO" :
			if(isNotCheckedRadio(field, f_name + "을(를) 선택해 주세요")) return false;
			break;
	}
	return true;
}

/**
 * reset form data
 * @param form
 * @param data
 */
function resetForm(form) {

	for(var i = 0; i < form.elements.length ; i++){

		switch(form.elements[i].type.toUpperCase()) {
			case "TEXT" :
				form.elements[i].value = "";
				break;
			case "TEXTAREA" :
				form.elements[i].value = "";
				break;
			case "SELECT-ONE" :
				keepSelStat(form.elements[i], "");
				break;
			case "RADIO" :
				keepRadioStat(form.elements[i], "");
				break;
			case "HIDDEN" :
				form.elements[i].value = "";
				break;
		}
	}
}

/******************************
* page navigation
* -----------------------------
* @param : pageno
*******************************/
function jsPagingNav(pageno)
{
	var Form = document.pagingForm;
   	Form.pageno.value = pageno;
   	Form.submit();
}
