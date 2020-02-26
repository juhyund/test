<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8" isELIgnored="false"%>
<%@ include file="/commons/common_define.jsp"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<title><%=PAGE_TITLE%></title>
<link href="<%=COMMON_PATH_JS%>/bootstrap.min.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/font-awesome.css" rel="stylesheet">
<link href="<%=COMMON_PATH_JS%>/datepicker3.css" rel="stylesheet">
<link href="<%=COMMON_PATH_CSS%>/style.css?ver=2" rel="stylesheet">

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
var CONTEXT_PATH = "<%=COMMON_URL%>
	";
</script>
<script src="<%=COMMON_PATH_JS%>/inspinia.js"></script>
<script type="text/javascript"
	src="<%=COMMON_PATH_JS%>/common.js" charset="UTF-8"></script>
<script src="<%=COMMON_PATH_JS%>/resize_window.js"></script>
<link href="<%=COMMON_PATH_CSS%>/style.css" rel="stylesheet">
<!-- <link href="css/plugins/awesome-bootstrap-checkbox/awesome-bootstrap-checkbox.css" rel="stylesheet"> -->



<script src="https://code.highcharts.com/highcharts.js"></script>
<script src="https://code.highcharts.com/modules/data.js"></script>
<script src="https://code.highcharts.com/modules/series-label.js"></script>
<script src="https://code.highcharts.com/modules/exporting.js"></script>
<script src="https://code.highcharts.com/modules/export-data.js"></script>
<script src="https://code.highcharts.com/modules/no-data-to-display.js"></script>

<!-- Additional files for the Highslide popup effect -->
<script
	src="https://www.highcharts.com/media/com_demo/js/highslide-full.min.js"></script>
<script
	src="https://www.highcharts.com/media/com_demo/js/highslide.config.js"
	charset="utf-8"></script>
<link rel="stylesheet" type="text/css"
	href="https://www.highcharts.com/media/com_demo/css/highslide.css" />



</head>
<body>
	<!--  wrapper -->
	<div id="content">
		<div id="wrapper">
			<div id="page-wrapper" style="width: 100%" class="gray-bg">
				<!-- navigator -->
				<div class="row wrapper page-heading" style="padding: 5px">
					<div class="col-lg-10">
						<h3 style="margin-top: 6px">정기검침 > 상세정보</h3>
					</div>
					<div class="col-lg-2">
						<ol class="breadcrumb" style="float: right; margin-top: 10px;">
							<li class="breadcrumb-item">Home</a>
							</li>
							<li class="breadcrumb-item active"><strong>Layouts</strong>
							</li>
						</ol>
					</div>
				</div>
				<!-- navigator -->
				<!-- body -->
				<div class="row">

					<div class="col-lg-12">
						<div class="ibox">
							<div class="ibox-content">
								<!-- start :summary_area -->

								<div class="row m-b-md gray-bg">
									<div>
										<div class="widget-left-color-box p-sm m-l-n-sm navy-bg" >
											<div>
												<i class="fa fa-sitemap fa-5x"></i>
											</div>
										</div>
									</div>
									<div class=" gray-bg m-r-n-sm" style="width: 88%;height :100%">
										<table class="table-borderless text-center m-t" style="width:100%" >
											<thead>
												<tr class="text-navy">
													<th>검침일</th>
													<th>(본부)지사 </th>
													<th>계기타입</th>
													<th>계기번호</th>
													<th>모뎀번호</th>
												</tr>
											</thead>
											<tbody>
												<tr>
													<td><h3>${meter_id}</h3></td>
													<td><h3 id = "device_id"></h3></td>
													<td><h3 id = "meter_type"></h3></td>
													<td><h3 id = "last_comm_dt"></h3></td>
													<td><h3 id = "last_comm_dt"></h3></td>
												</tr>
											</tbody>
										</table>
									</div>
								</div>
								<!--  end : summary_area  -->

								<!--  start : search_area  -->
								<form name="search_form" id="search_form" method="post">
									<table class="table table-borderless"
										style="width: 100%; margin-bottom: 7px;" border="1">
										<tbody>
											<tr class="table-border">
												<td>
													<div class="form-group row">
														<label class="col-sm-1 col-form-label ">검침기간</label>

														<div class="col-sm-3" id="datePicker">
															<div class="input-group date"
																style="width: 48%; float: left;">
																<input type="hidden" id="sdate" name="sdate" value="">
																<input type="text" class="form-control" id="sdateView"
																	name="sdateView" value="${sdate}"> <span
																	class="input-group-addon" style="list-style: none;">
																	<i class="fa fa-calendar"></i>
																</span>
															</div>
															<label class="col-form-label"
																style="width: 4%; float: left; text-align: center">~</label>
															<div class="input-group date" style="width: 48%;">
																<input type="hidden" id="edate" name="edate" value="">
																<input type="text" class="form-control" id="edateView"
																	name="edateView" value="${edate}"> <span
																	class="input-group-addon" style="list-style: none;">
																	<i class="fa fa-calendar"></i>
																</span>
															</div>
														</div>
														<div class="col-sm-3 btn-group">
															<button type="button" class="btn btn-outline btn-primary"
																clicked onclick="setSearchPeriod('today')">오늘</button>
															<button type="button" class="btn btn-outline btn-primary"
																onclick="setSearchPeriod('weekly')">주간</button>
															<button type="button" class="btn btn-outline btn-primary"
																onclick="setSearchPeriod('montly')">월간</button>
														</div>
													</div>
												</td>
												<td width="180" style="text-align: right">
													<button class="btn btn-primary"
														style="height: 100%; width: 50px" type="button"
														onclick="ajaxSearchForm();">
														<i class="fa fa-search"></i>
													</button>
													<button class="btn btn-warning"
														style="height: 100%; width: 50px" type="button"
														onclick="resetForm();">
														<i class="fa fa-undo"></i>
													</button>
													<button class="btn btn-outline btn-primary"
														style="height: 100%; width: 50px" type="button"
														onclick="excelDownload();">
														<i class="fa fa-download"></i>
													</button>
												</td>
											</tr>
										</tbody>
									</table>
									<input type="hidden" id="meter_id" name="meter_id"
										value="${meter_serial}" class="form-control">
								</form>
								<!--  end : search_area  -->

								<!--  start : table_area  -->
								<div name="table_area">
									<div class="row" style="width: 100%; margin: 40px 0px 0px 0px">
										<table name="table1" class="table table-bordered white-bg billing-detail-table" style="width: 48%">
											<thead>
												<tr>
													<th class="text-navy" colspan="5">순방향 유효전력</th>
												</tr>
												<tr>
													<th>Total</th>
													<th>T1</th>
													<th>T2</th>
													<th>T3</th>
													<th>T4</th>
												</tr>
												<tr>
													<!-- <td class="device-detail-body">{{device_info.device_id}}</td> -->
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
												</tr>

											</thead>
										</table>
										<table style="width: 4%"></table>
										<table name="table2" class="table table-bordered white-bg billing-detail-table" style="width: 48%">
											<thead>
												<tr>
													<th class="text-navy" colspan="5">순방향 유효전력</th>
												</tr>
												<tr>
													<th>Total</th>
													<th>T1</th>
													<th>T2</th>
													<th>T3</th>
													<th>T4</th>
												</tr>
												<tr>
													<!-- <td class="device-detail-body">{{device_info.device_id}}</td> -->
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
												</tr>

											</thead>
										</table>
									</div>
									<div class="row" style="width: 100%; margin: 0px">
										<table name="table3" class="table table-bordered white-bg billing-detail-table" style="width: 48%">
											<thead>
												<tr>
													<th class="text-navy" colspan="5">순방향 유효전력</th>
												</tr>
												<tr>
													<th>Total</th>
													<th>T1</th>
													<th>T2</th>
													<th>T3</th>
													<th>T4</th>
												</tr>
												<tr>
													<!-- <td class="device-detail-body">{{device_info.device_id}}</td> -->
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
												</tr>

											</thead>
										</table>
										<table style="width: 4%"></table>
										<table name="table4" class="table table-bordered white-bg billing-detail-table" style="width: 48%">
											<thead>
												<tr>
													<th class="text-navy" colspan="5">순방향 유효전력</th>
												</tr>
												<tr>
													<th>Total</th>
													<th>T1</th>
													<th>T2</th>
													<th>T3</th>
													<th>T4</th>
												</tr>
												<tr>
													<!-- <td class="device-detail-body">{{device_info.device_id}}</td> -->
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
												</tr>

											</thead>
										</table>
									</div>
									<div class="row" style="width: 100%; margin: 0px">
										<table name="table5" class="table table-bordered white-bg billing-detail-table" style="width: 48%">
											<thead>
												<tr>
													<th class="text-navy" colspan="5">순방향 유효전력</th>
												</tr>
												<tr>
													<th>Total</th>
													<th>T1</th>
													<th>T2</th>
													<th>T3</th>
													<th>T4</th>
												</tr>
												<tr>
													<!-- <td class="device-detail-body">{{device_info.device_id}}</td> -->
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
												</tr>

											</thead>
										</table>
										<table style="width: 4%"></table>
										<table name="table6" class="table table-bordered white-bg billing-detail-table" style="width: 48%">
											<thead>
												<tr>
													<th class="text-navy" colspan="5">순방향 유효전력</th>
												</tr>
												<tr>
													<th>Total</th>
													<th>T1</th>
													<th>T2</th>
													<th>T3</th>
													<th>T4</th>
												</tr>
												<tr>
													<!-- <td class="device-detail-body">{{device_info.device_id}}</td> -->
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
													<td>0.000</td>
												</tr>

											</thead>
										</table>
										
									</div>





















								</div>
								<!--  end : table_area  -->



							</div>
						</div>
					</div>
				</div>
				<!-- body -->
			</div>
		</div>
	</div>

	<script type="text/javascript" charset="utf-8">
		//var meter_id = $('#detail_meter_id').val();// ${meterId};

		$(document).ready(function() {
			init();

		});

		function init() {
			//ajaxSearchForm();

			initDate();

		}
		function initDate() {

			var initSdate = $("#sdateView").val();
			var initEdate = $("#edateView").val();

			setSearchParam2(initSdate, initEdate);
		}

		function ajaxMeterInfoSummary() {
			var options = {
				beforeSend : showRequest,
				success : loadMeterInfo,
				url : COMMON_URL + "/ajaxMeterInfoSummary",
				contentType : "application/x-www-form-urlencoded;charset=UTF-8",
				type : "post", /* get, post */
				dataType : "json", /* xml, html, script, json */
				data : $("#search_form").serialize()
			};

			$.ajax(options);
		}

		function ajaxChannelList() {
			var options = {
				beforeSend : showRequest,
				success : useChannelList, /*미터가 사용하는 채널에 따라 유동적으로 헤더를 생성*/
				url : COMMON_URL + "/ajaxChannelList",
				contentType : "application/x-www-form-urlencoded;charset=UTF-8",
				type : "post", /* get, post */
				dataType : "json", /* xml, html, script, json */
				data : $("#search_form").serialize()
			};

			$.ajax(options);
		}

		function ajaxSearchForm() {
			setSearchParam2($("#sdateView").val(), $("#edateView").val());

			var options = {
				beforeSend : showRequest,
				success : successResultHandler,
				url : COMMON_URL + "/ajaxMeterValueDetail",
				contentType : "application/x-www-form-urlencoded;charset=UTF-8",
				type : "post", /* get, post */
				dataType : "json", /* xml, html, script, json */
				data : $("#search_form").serialize()
			};

			$.ajax(options);
		}

		function resetForm() {
			$("#search_form")[0].reset();
		};

		function excelDownload() {
			setSearchParam2($("#sdateView").val(), $("#edateView").val());

			$('#search_form').attr('action',
					"/ewsn-app/downloadMeterValueDetail");
			$('#search_form').attr('method', "GET");
			$('#search_form').submit();
			Swal.fire({
				position : 'center',
				icon : 'info',
				text : 'excel 생성중',
				showConfirmButton : false,
				timer : 1500
			});

		}

		function showRequest() {
			// $("#loading").show();
		}

		function successResultHandler(data, status) {
			//grid에 데이터 로딩 
			dataGrid.setData(data.resultGrid);
			//chart에 데이터 로딩
			loadChart(data, status);
		}

		function loadMeterInfo(data, status) {
			//받아온 데이터를 미터Info에 로딩
			var device_id;
			var meter_type;
			var last_comm_dt;

			device_id = data.resultGrid[0].device_id;
			meter_type = data.resultGrid[0].meter_type;
			last_comm_dt = data.resultGrid[0].last_comm_dt;

			$('#device_id').text(device_id);
			$('#meter_type').text(meter_type);
			$('#last_comm_dt').text(last_comm_dt);
		}
	</script>


	<script>
		$('#datePicker .input-group.date').datepicker({
			todayBtn : "linked",
			forceParse : false,
			autoclose : true
		});
	</script>
	<!--  wrapper -->
</body>
</html>
