<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<title><%=PAGE_TITLE%></title>
<link href="<%=COMMON_PATH_JS%>/bootstrap.min.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/datepicker3.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/font-awesome.css" rel="stylesheet">

<!-- Mainly scripts -->
<script src="<%=COMMON_PATH_JS%>/jquery-3.1.1.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/popper.min.js"></script>
<script src="<%=COMMON_PATH_JS%>/bootstrap.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.metisMenu.js"></script>
<script src="<%=COMMON_PATH_JS%>/jquery.slimscroll.min.js"></script>
<!-- Data picker -->
<script src="<%=COMMON_PATH_JS%>/bootstrap-datepicker.js"></script>

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js"></script>

<script src="https://cdn.jsdelivr.net/npm/sweetalert2@9"></script>

<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript" src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>
<%-- <script src="<%=COMMON_PATH_JS%>/icheckbox.css"></script> --%>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
<link href="<%=COMMON_PATH_CSS%>/style.css?ver=1" rel="stylesheet">
</head>
<body>
<!--  wrapper -->
<div id="content">
<div id="wrapper">
<div id="page-wrapper" style="width:100%" class="gray-bg" >
<!-- navigator -->
<div class="row wrapper page-heading" style="padding:5px">
<div class="col-lg-10" >
	<h3 style="margin-top:6px">사용자관리</h3>
</div>
<div class="col-lg-2" >
	<ol class="breadcrumb" style="float:right;margin-top:10px;">
		<li class="breadcrumb-item">
			<a href="http://webapplayers.com/inspinia_admin-v2.9.2/index.html">Home</a>
		</li>
		<li class="breadcrumb-item active">
			<strong>Layouts</strong>
		</li>
		</ol>
	</div>						
</div>
<!-- navigator -->
<!-- body -->
<div class="row">
	<div class="col-lg-8">	
		<div class="ibox">
			<div class="ibox-content">
				<form name="search_form" id="search_form" method="post">
				<input type="hidden" id="limit" name="limit" value ="10" class="form-control">
				<input type="hidden" id="page" name="page" value ="1" class="form-control" onchange="ajaxSearchForm()">
				<input type="hidden" id="user_yn" name="user_yn" value=0 class="form-control">
				
					<table class="table table-borderless" style="height: 100%; "
						style="margin-bottom: 7px;" border="1">
						<tbody>
							<tr class="table-border">
								<td height="80">
									<div class="form-group row">
										<label class="col-lg-2 col-form-label">사용자 ID</label>
										<div class="col-lg-4">
											<input type="text" id="user_id_search" name="user_id_search" value="" class="form-control">
										</div>
										<label class="col-lg-2 col-form-label">사용자그룹</label>
										<div class="col-lg-4">
											<select class="form-control" name="group_user_seq_search"	id="group_user_seq_search" type="number">
												<option value=0 selected>전체</option>
												<option value=1 >SUPER</option>
												<option value=2 >ADMIN</option>
												<option value=3 >USER</option>
											</select>	
										</div>
									</div>
									<div class="form-group row">
										<label class="col-lg-2 col-form-label">사용자명</label>
										<div class="col-lg-4">
											<input type="text" id="user_name_search" name="user_name_search" class="form-control">
										</div>
									</div>
								</td>
								<td width="210px" height="80" style="text-align: right">
									<button class="btn btn-primary" style="height: 100%; width: 50px" type="button" onclick="ajaxSearchForm();">
										<i class="fa fa-search"></i>
									</button>
									<button class="btn btn-warning" style="height: 100%; width: 50px" type="button" onclick="resetForm();">
										<i class="fa fa-undo"></i>
									</button>
									<button id="create_user_btn" class="btn btn-outline btn-primary" style="height: 100%; width: 70px" type="button" onclick="createUser();">
										<i class="fa fa-plus"></i> <i class="fa fa-user fa-2x"></i>
									</button>
								</td>
							</tr>
						</tbody>
					</table>
			
				</form>
				<div>
					<!-- page option -->
					<div class="row m-t-n-n" style="margin:-1px"  >
						<div style="width :100%;vertical-align:center">
							<label id="cur_page_num" class="col-form-label"></label>
							<div style ="float:right; margin-bottom:5px">
								<select id="data_per_page" class="form-control" name="data_per_page" onchange="javascript:changeLimit(this);">
									<option value=10 selected>10개씩</option>
									<option value=100>100개씩 </option>
									<option value=250>250개씩 </option>
								</select>
							</div>
						</div>
					</div>
					<!-- grid -->
					<div id="grid" style="height:350px;" class="ag-theme-balham"></div>
					
					<!-- grid pagination -->
					<div id="grid-page" style ="display:none;" class="m-t-sm">
							<ul id="pagination" class="pagination"></ul>
					</div>
		        </div>
			   </div>
			</div>
		</div>
		
		
	<!-- 사용자 상세페이지 -->	
	<div class="col-lg-4">	
		<div class="ibox ">
			<div class="ibox-content">
				<!-- 사용자정보 -->
				<div id="user_detail_view" class="m-b-md text-center">
					<table class="table-borderless m-t" style="min-width:200px; display:inline-block" >
						<tbody class="text-left">
							<tr style="height:150px">
								<th class="text-navy text-center" style="padding-right: 10px;">
									<i class="fa fa-user-circle fa-6x"></i>
								</th>
								<td>
									<p id="group_name_view" class="text-navy m-n"></p><!-- ${group_name} -->
									<h1 id="user_name_view" class="m-n" ></h1><!-- ${user_name} -->
									<p id="user_id_view" class="m-n" id=></p><!-- ${user_id} -->
								</td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row"><!-- 전화번호 -->
									<i class="fa fa-phone"></i>
								</th>
								<td id="user_phone_view"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row"><!-- 메일 주소  -->
									<i class="fa fa-envelope"></i>
								</th>
								<td id="user_email_view"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row"><!-- 부서명 -->
									<i class="fa fa-suitcase"></i>
								</th>
								<td id="dept_name_view"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row"><!-- 등록자 IP -->
									<i class="fa fa-desktop"></i>
								</th>
								<td id="reg_user_ip_view"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row"><!-- 등록일시 -->
								<i class="fa fa-clock"></i>
								<td id="reg_dt_view"></td>
							</tr>
						</tbody>
					</table>
				</div>
				
				<!-- 사용자 정보 수정/추가 -->
				<form name="detail_form" id="detail_form" method="post" class="m-b-md text-center" style="display:none">
					<input type="hidden" id="user_seq" name="user_seq" class="form-control">
					<div class="text-navy text-center m-t-xl" style="height:100px;">
						<i class="fa fa-plus fa-3x vertical-align"></i> <i class="fa fa-user fa-6x"></i>
					</div>
					<table class="table-borderless m-t" style="min-width:200px; display:inline-block" >
						<tbody class="text-left">
							<tr>
								<th class="text-navy text-center" scope="row">사용자그룹</th>
								<td>
								<div>
									<select class="form-control" name="group_user_seq"	id="group_user_seq" type="number">
										<option value=1 >SUPER</option>
										<option value=2 >ADMIN</option>
										<option value=3 selected>USER</option>
									</select>	
								</div>
								</td>
							</tr>
							<tr>
								<th class="text-navy text-center">사용자명  </th>
								<td><input type="text" id="user_name" name="user_name" value="" class="form-control"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row"> ID </th>
								<td>
									<input type="text" id="user_id" name="user_id" value="" class="form-control" style="width: 80%;display: inline-block;">
									<button id="check_id_btn" class="btn btn-outline btn-primary text-align" style="width: 18%" type="button" onclick="checkId();">
										<i class="fa fa-check"></i>
									</button>
								</td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row">비밀번호 </th>
								<td>
									<input type="password" id="user_pass" name="user_pass" value="" class="form-control">
									<button id="change_pw_btn" class="btn btn-outline btn-primary text-align" style="width: 100%; display:none" type="button" onclick="changePW();">
									비밀번호 변경
									</button>
								</td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row"></th>
								<td><input type="password" id="user_pass_check" name="user_pass_check" value="" class="form-control" placeholder="비밀번호 재입력"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row">전화번호</th>
								<td><input type="text" id="user_phone" name="user_phone" value="" class="form-control"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row">메일 </th>
								<td><input type="text" id="user_email" name="user_email" value="" class="form-control"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row">부서명 </th>
								<td><input type="text" id="dept_name" name="dept_name" value="" class="form-control"></td>
							</tr>
							<tr>
								<th class="text-navy text-center" scope="row">IP </th>
								<td><input type="text" id="reg_user_ip" name="reg_user_ip" value="" class="form-control"></td>
							</tr>
						</tbody>
					</table>
				</form>
				
				<div class="row m-t-n-n" style="margin:-1px">
					<div style="width :100%;vertical-align:center">
							<div style="float:right; margin-bottom:5px">
								<button id="edit_btn" class="btn btn-outline btn-primary m-t-sm" style="height: 100%" type="button" onclick="editUser();">
									<i class="fa fa-edit"> 데이터 수정</i>
								</button>
								<button id="save_btn" class="btn btn-outline btn-primary m-t-sm" style="height: 100%" type="button" onclick="saveUser();">
									<i class="fa fa-check"> 저장</i>
								</button>
								<button id="cancel_btn" class="btn btn-outline btn-danger m-t-sm" style="height: 100%" type="button" onclick="cancelEditUser();">
									<i class="fa fa-times"> 취소</i>
								</button>
							</div>
					</div>
				<div>
			   
			
			</div>
		</div>
	</div>
</div>
</div>
<!-- body -->
</div>
</div>	
</div>

<script type="text/javascript" charset="utf-8">
var idChecked = false;
var pwChecked = false;
var isEditMode = false;


//specify the columns
var columnDefs = [
	{headerName: "번호", field: "no", width:80},
	{headerName: "그룹이름", field: "group_name" , width:100},
	{headerName: "사용자 명", field: "user_name"},
	{headerName: "사용자 ID", field: "user_id"},
	{headerName: "등록일자", field: "reg_dt"}
];


var initGrid = function() {
    dataGrid = new DataGrid('grid', columnDefs, true, 500, true);    
    dataGrid.makeGrid();
    dataGrid.showNoRows();
};

function ajaxSearchForm() {
	//setSearchParam($("#sdateView").val(), $("#edateView").val());
	
    var options = { 
           beforeSend  : showRequest,
           success     : successResultHandler,
           url         : COMMON_URL + "/ajaxUserInfo",
           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
           type        : "post", /* get, post */
           dataType    : "json", /* xml, html, script, json */
           data        : $("#search_form").serialize()
     };             
    
     $.ajax(options);
}

function showUserDetailView(){
	$("#user_detail_view").show();
	$("#detail_form").hide();
	
	$("#create_user_btn").show();
	$("#edit_btn").show();
	$("#save_btn").hide();
	$("#cancel_btn").hide();
}

function showUserEditView(){
	$("#user_detail_view").hide();
	$("#detail_form").show();
	
	$("#create_user_btn").hide();
	$("#edit_btn").hide();
	$("#save_btn").show();
	$("#cancel_btn").show();
	
}

function createUser() {
	idChecked = false;
	pwChecked = false;
	isEditMode = false;
	
	$("#change_pw_btn").hide();
	$("#user_pass").show();
	$("#user_pass_check").show();
	
	//사용자 수정창 데이터 reset 
	$("#detail_form")[0].reset();
	$("#group_user_seq").attr("disabled",false);
	$("#user_id").attr("readonly",false);
	$("#check_id_btn").attr('disabled',false);
	
	showUserEditView();
}

function saveUser() {
	//password 비교
	if($("#user_pass_check").val() == $("#user_pass").val()){
		pwChecked = true;
	}
	
	if(idChecked==false){
		Swal.fire({
			position: 'center',
			icon: 'warning',
			title: 'ID',
			text: '중복 확인이 필요합니다!',
			showConfirmButton: false,
				timer: 1500
			});
	}else if(pwChecked==false){
		Swal.fire({
			position: 'center',
			icon: 'warning',
			title: '비밀번호',
			text: '다시한번 확인해주세요',
			showConfirmButton: false,
				timer: 1500
			});
	}else{
		if(isEditMode){
			var options = { 
			           beforeSend  : showRequest,
			           success     : successSaveUser,
			           url         : COMMON_URL + "/ajaxUpdateUserInfo",
			           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
			           type        : "post", /* get, post */
			           dataType    : "json", /* xml, html, script, json */
			           data        : $("#detail_form").serialize()
			     };             
			$.ajax(options);
		}else{
			var options = { 
			           beforeSend  : showRequest,
			           success     : successSaveUser,
			           url         : COMMON_URL + "/ajaxSaveUserInfo",
			           contentType : "application/x-www-form-urlencoded;charset=UTF-8",
			           type        : "post", /* get, post */
			           dataType    : "json", /* xml, html, script, json */
			           data        : $("#detail_form").serialize()
			     };             
			$.ajax(options);
		}
	}
}
function successSaveUser(data, status){
	
	if(data.success == true){
		Swal.fire({
			position: 'center',
			icon: 'success',
			title: '저장 완료',
			showConfirmButton: false,
				timer: 2000
			});
	
		createUser();
		ajaxSearchForm();
		
	}else{
		Swal.fire({
			position: 'center',
			icon: 'error',
			title: '저장 실패',
			showConfirmButton: false,
				timer: 2000
			});
	}
}

function editUser() {
	idChecked = true;
	pwChecked = true;
	isEditMode = true;
	
	//그룹 , id 수정못하게
	$("#group_user_seq").attr("disabled",true);
	$("#user_id").attr("readonly",true);
	$("#check_id_btn").attr('disabled',true);
	
	//비밀번호 입력창 대신, '비밀번호변경' 버튼 표시
	$("#change_pw_btn").show();
	$("#user_pass").hide();
	$("#user_pass_check").hide();
	
	showUserEditView();
}

function cancelEditUser(){
	//clearUserDetail();
	showUserDetailView();
}

function checkId(){
	idChecked = true;
	
    var options = { 
            beforeSend  : showRequest,
            success     : function(data, status){
            	if(data.success == false){
            		idChecked = false;
            		Swal.fire({
            			position: 'center',
            			icon: 'error',
            			title: '저런...',
            			text: '사용할 수 없는 ID 입니다!',
            			showConfirmButton: false,
          				timer: 1500
            			})
            	}else{
            		Swal.fire({
            			  position: 'center',
            			  icon: 'success',
            			  text: '사용 가능한 ID 입니다!',
            			  showConfirmButton: false,
            			  timer: 1500
            			})
            	}
            	
            },
            url         : COMMON_URL + "/ajaxCheckId",
            contentType : "application/x-www-form-urlencoded;charset=UTF-8",
            type        : "post", /* get, post */
            dataType    : "json", /* xml, html, script, json */
            data        : { user_id : $("#user_id").val() }
      };             
     
      $.ajax(options);
	
}

function changePW(){
	//비번 입력화면 로딩
	$("#change_pw_btn").hide();
	$("#user_pass").show();
	$("#user_pass_check").show();
	
	$("#user_pass").val("");
	$("#user_pass_check").val("");
	
	pwChecked = false;
}


function loadUserDetail(User){

	//사용자 상세정보 로딩
	$("#group_name_view").text(User.group_name);
	$("#user_name_view").text(User.user_name);
	$("#user_id_view").text("# "+User.user_id);
	$("#user_phone_view").text(User.user_phone);
	$("#user_email_view").text(User.user_email);
	$("#dept_name_view").text(User.dept_name);
	$("#reg_user_ip_view").text(User.reg_user_ip);
	$("#reg_dt_view").text(User.reg_dt);
	
	//사용자 수정창에 데이터 로딩
	$("#group_user_seq").val(User.group_user_seq).prop("selected", true);
	$("#user_seq").val(User.user_seq);
	$("#user_name").val(User.user_name);
	$("#user_id").val(User.user_id);
	$("#user_phone").val(User.user_phone);
	$("#user_email").val(User.user_email);
	$("#dept_name").val(User.dept_name);
	$("#reg_user_ip").val(User.reg_user_ip);
	//$("#user_pass").val(User.user_pass);
	//$("#user_pass_check").val(User.user_pass);
}

onRowClicked = function(event){
	//선택된 row의 user_seq를 파라미터로 UserDetail부분을 로딩한다.
	showUserDetailView();
	
	//데이터 리셋
	$("#detail_form")[0].reset();
	$("#group_name_view").text("");
	$("#user_name_view").text("");
	$("#user_id_view").text("# ");
	$("#user_phone_view").text("");
	$("#user_email_view").text("");
	$("#dept_name_view").text("");
	$("#reg_user_ip_view").text("");
	$("#reg_dt_view").text(""); 
	
	var selectedRows = dataGrid.getSelectedRow();
    var selectedRowsString = '';
    selectedRows.forEach( function(selectedRow, index) {
        if (index!==0) {
            selectedRowsString += ', ';
        }
        selectedRowsString += selectedRow.user_name;
        
        loadUserDetail(selectedRow);
    });
}

function resetForm(){
	$("#search_form")[0].reset();
	$("#grid-page").hide();
};

function showRequest() {
	// $("#loading").show();
}

function successResultHandler(data, status) {
	var dataPerPage = $("#limit").val();
	
	dataGrid.setData(data.resultGrid);
	gridPage(data.totalCount, dataPerPage, 10, 1);
}

function init() {
	
	// init
	initGrid();
	
	// form search
	ajaxSearchForm();
	
	showUserEditView();
	$("#cancel_btn").hide();
}

function setLimit(obj){
	$("#limit").val(obj.value);
}
	
$(document).ready(function() {	
	init();
});
</script>
<script>	
$('#datePicker .input-group.date').datepicker({
	todayBtn: "linked",	
	forceParse: false,
	autoclose: true
});
</script>
<!--  wrapper -->
</body>
</html>