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

<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-grid.css?ver=1">
<link rel="stylesheet" href="<%=COMMON_PATH_CSS%>/ag-theme-balham.css">

<script src="<%=COMMON_PATH_JS%>/ag-grid/ag-grid-enterprise.js"></script>
<script src="<%=COMMON_PATH_JS%>/ag-grid/aggrid.js?ver=1"></script>
<script src="https://cdn.jsdelivr.net/npm/sweetalert2@9"></script>

<script>
var CONTEXT_PATH = "<%=COMMON_URL%>";
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
						<h2 style="margin-top: 10px; font-weight: bold"><i class="fas fa-angle-double-right"></i> 정기검침 - 상세 데이터 조회</h2>
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
													<th>모뎀 시간</th>
													<th>계기 시간</th>
													<th>(본부)지사 </th>
													<th>계기 타입</th>
													<th>계기 번호</th>
													<th>모뎀 번호</th>
												</tr>
											</thead>
											<tbody>
												<tr>
													<td><h3 id = "billing_dt"></h3></td>
													<td><h3 id = "itime"></h3></td>
													<td><h3 id = "mtime"></h3></td>
													<td><h3 id = "parent_branch_nm"></h3><h3 id = "branch_nm"></h3></td>
													<td><h3 id = "meter_type"></h3></td>
													<td><h3 id = "meter_serial"></h3></td>
													<td><h3 id = "device_serial"></h3></td>
												</tr>
											</tbody>
										</table>
									</div>
								</div>
								<!--  end : summary_area  -->

								<!--  start : search_area  -->
								<form name="search_form" id="search_form" method="post">
									<%-- <table class="table table-borderless"
										style="width: 100%; margin-bottom: 7px;" border="1">
										<tbody>
											<tr class="table-border">
												<td>
													<div class="form-group row">
														<label class="col-sm-1 col-form-label ">검침기간</label>

														<div class="col-sm-5" id="datePicker">
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
														<label class="col-form-label" style="width: 4%; float: left; text-align: center"></label>
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
													<button class="btn btn-primary" style="height: 100%; width: 50px" type="button" onclick="ajaxSearchForm();">
														<i class="fa fa-search"></i>
													</button>
													<button class="btn btn-warning" style="height: 100%; width: 50px" type="button" onclick="resetForm();">
														<i class="fa fa-undo"></i>
													</button>
													<button class="btn btn-outline btn-primary" style="height: 100%; width: 50px" type="button" onclick="excelDownload();">
														<i class="fa fa-download"></i>
													</button>
												</td>
											</tr>
										</tbody>
									</table> --%>
									<input type="hidden" id="meter_id" name="meter_id"value="${meter_id}" class="form-control">
									<input type="hidden" id="billing_dt" name="billing_dt"value="${billing_dt}" class="form-control">
								</form>
								<!--  end : search_area  -->

								<!--  start : table_area  -->
								<div name="table_area">
									<div class="row" style="width: 100%; margin: 40px 0px 0px 0px">
										<table name="순방향 " class="table table-bordered white-bg billing-detail-table" style="width: 49.5%">
											<thead>
												<tr>
													<th class="text-navy" colspan="5">순방향</th>
												</tr>
												<tr>
													<th></th>
													<th>합계</th>
													<th>중부하</th>
													<th>최대부하</th>
													<th>경부하</th>
												</tr>
												<tr>
													<th>유효전력량(kWh)</td>
													<td id = "ACTIVE_IMP_TOT"></td>
													<td id = "ACTIVE_IMP_T1"></td>
													<td id = "ACTIVE_IMP_T2"></td>
													<td id = "ACTIVE_IMP_T3"></td>
												</tr>
												<tr>
													<th>피상전력량(kVah)</td>
													<td id = "APPRENT_IMP_TOT"></td>
													<td id = "APPRENT_IMP_T1"></td>
													<td id = "APPRENT_IMP_T2"></td>
													<td id = "APPRENT_IMP_T3"></td>
												</tr>
												<tr>
													<th>지상무효전력량(kVarh)(+)</td>
													<td id = "LEAD_IMP_TOT"></td>
													<td id = "LEAD_IMP_T1"></td>
													<td id = "LEAD_IMP_T2"></td>
													<td id = "LEAD_IMP_T3"></td>
												</tr>
												<tr>
													<th>진상무효전력량(kVarh)(-)</td>
													<td id = "LAGGING_IMP_TOT"></td>
													<td id = "LAGGING_IMP_T1"></td>
													<td id = "LAGGING_IMP_T2"></td>
													<td id = "LAGGING_IMP_T3"></td>
												</tr>
												<tr>
													<th>평균역률(pf)</td>
													<td id = "PF_IMP_TOT"></td>
													<td id = "PF_IMP_T1"></td>
													<td id = "PF_IMP_T2"></td>
													<td id = "PF_IMP_T3"></td>
												</tr>
											</thead>
										</table>
										<table style="width: 1%"></table>
										<table name="table2" class="table table-bordered white-bg billing-detail-table" style="width: 49.5%">
											<thead>
												<tr>
													<th class="text-navy" colspan="5">역방향</th>
												</tr>
												<tr>
													<th></th>
													<th>합계</th>
													<th>중부하</th>
													<th>최대부하</th>
													<th>경부하</th>
												</tr>
												<tr>
													<th>(역)유효전력량(kWh)</td>
													<td id = "ACTIVE_EXP_TOT"></td>
													<td id = "ACTIVE_EXP_T1"></td>
													<td id = "ACTIVE_EXP_T2"></td>
													<td id = "ACTIVE_EXP_T3"></td>
												</tr>
												<tr>
													<th>(역)피상전력량(kVah)</td>
													<td id = "APPRENT_EXP_TOT"></td>
													<td id = "APPRENT_EXP_T1"></td>
													<td id = "APPRENT_EXP_T2"></td>
													<td id = "APPRENT_EXP_T3"></td>
												</tr>
												<tr>
													<th>(역)지상무효전력량(kVarh)(+)</td>
													<td id = "LEAD_EXP_TOT"></td>
													<td id = "LEAD_EXP_T1"></td>
													<td id = "LEAD_EXP_T2"></td>
													<td id = "LEAD_EXP_T3"></td>
												</tr>
												<tr>
													<th>(역)진상무효전력량(kVarh)(-)</td>
													<td id = "LAGGING_EXP_TOT"></td>
													<td id = "LAGGING_EXP_T1"></td>
													<td id = "LAGGING_EXP_T2"></td>
													<td id = "LAGGING_EXP_T3"></td>
												</tr>
												<tr>
													<th>(역)평균역률(pf)</td>
													<td id = "PF_EXP_TOT"></td>
													<td id = "PF_EXP_T1"></td>
													<td id = "PF_EXP_T2"></td>
													<td id = "PF_EXP_T3"></td>
												</tr>
											</thead>
										</table>
									</div>
									<button class="btn btn-outline btn-primary m-t-sm" style="margin-right: 5px; height: 35px; float: right" type="button" onclick="javascript:history.back(-1)">
										<i class="fa fa-undo"> 목록으로 돌아가기</i>
									</button>	
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

		$(document).ready(function() {
			init();

		});

		function init() {
			ajaxSearchForm();
		}
		
		function ajaxSearchForm() {

			var options = {
				beforeSend : showRequest,
				success : successResultHandler,
				url : COMMON_URL + "/ajaxMeterBillingDetail",
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

		function showRequest() {
			// $("#loading").show();
		}
		
		function successResultHandler(data, status) {
			
			var branch_nm = "("+data.resultGrid[0].parent_branch_nm+")"+data.resultGrid[0].branch_nm;
			
			$('#billing_dt'		).text(data.resultGrid[0].billing_dt);
			$('#mtime'			).text(data.resultGrid[0].mtime);
			$('#itime'			).text(data.resultGrid[0].itime);
			$('#branch_nm'		).text(branch_nm);
			$('#meter_type'		).text(data.resultGrid[0].meter_type);
			$('#meter_serial'	).text(data.resultGrid[0].meter_serial);
			$('#device_serial'	).text(data.resultGrid[0].device_serial);
			
			//유효 전력량 
			$('#ACTIVE_IMP_TOT'	).text(formatNumber(data.resultGrid[0].active_imp_tot,4));
			$('#ACTIVE_IMP_T1'	).text(formatNumber(data.resultGrid[0].active_imp_rate1,4));
			$('#ACTIVE_IMP_T2'	).text(formatNumber(data.resultGrid[0].active_imp_rate2,4));
			$('#ACTIVE_IMP_T3'	).text(formatNumber(data.resultGrid[0].active_imp_rate3,4));
			$('#ACTIVE_EXP_TOT'	).text(formatNumber(data.resultGrid[0].active_exp_tot,4));
			$('#ACTIVE_EXP_T1'	).text(formatNumber(data.resultGrid[0].active_exp_rate1,4));
			$('#ACTIVE_EXP_T2'	).text(formatNumber(data.resultGrid[0].active_exp_rate2,4));
			$('#ACTIVE_EXP_T3'	).text(formatNumber(data.resultGrid[0].active_exp_rate3,4));
			
			//피상 전력량
			$('#APPRENT_IMP_TOT').text(formatNumber(data.resultGrid[0].apprent_imp_tot,4));
			$('#APPRENT_IMP_T1'	).text(formatNumber(data.resultGrid[0].apprent_imp_rate1,4));
			$('#APPRENT_IMP_T2'	).text(formatNumber(data.resultGrid[0].apprent_imp_rate2,4));
			$('#APPRENT_IMP_T3'	).text(formatNumber(data.resultGrid[0].apprent_imp_rate3,4));
			$('#APPRENT_EXP_TOT').text(formatNumber(data.resultGrid[0].apprent_exp_tot,4));
			$('#APPRENT_EXP_T1'	).text(formatNumber(data.resultGrid[0].apprent_exp_rate1,4));
			$('#APPRENT_EXP_T2'	).text(formatNumber(data.resultGrid[0].apprent_exp_rate2,4));
			$('#APPRENT_EXP_T3'	).text(formatNumber(data.resultGrid[0].apprent_exp_rate3,4));
			
			//지상 무효 전력량
			$('#LEAD_IMP_TOT'	).text(formatNumber(data.resultGrid[0].lead_imp_tot,4));
			$('#LEAD_IMP_T1'	).text(formatNumber(data.resultGrid[0].lead_imp_rate1,4));
			$('#LEAD_IMP_T2'	).text(formatNumber(data.resultGrid[0].lead_imp_rate2,4));
			$('#LEAD_IMP_T3'	).text(formatNumber(data.resultGrid[0].lead_imp_rate3,4));
			$('#LEAD_EXP_TOT'	).text(formatNumber(data.resultGrid[0].lead_exp_tot,4));
			$('#LEAD_EXP_T1'	).text(formatNumber(data.resultGrid[0].lead_exp_rate1,4));
			$('#LEAD_EXP_T2'	).text(formatNumber(data.resultGrid[0].lead_exp_rate2,4));
			$('#LEAD_EXP_T3'	).text(formatNumber(data.resultGrid[0].lead_exp_rate3,4));
			
			//진상 무효 전력량
			$('#LAGGING_IMP_TOT').text(formatNumber(data.resultGrid[0].lagging_imp_tot,4));
			$('#LAGGING_IMP_T1').text(formatNumber(data.resultGrid[0].lagging_imp_rate1,4));
			$('#LAGGING_IMP_T2').text(formatNumber(data.resultGrid[0].lagging_imp_rate2,4));
			$('#LAGGING_IMP_T3').text(formatNumber(data.resultGrid[0].lagging_imp_rate3,4));
			$('#LAGGING_EXP_TOT').text(formatNumber(data.resultGrid[0].lagging_exp_tot,4));
			$('#LAGGING_EXP_T1').text(formatNumber(data.resultGrid[0].lagging_exp_rate1,4));
			$('#LAGGING_EXP_T2').text(formatNumber(data.resultGrid[0].lagging_exp_rate2,4));
			$('#LAGGING_EXP_T3').text(formatNumber(data.resultGrid[0].lagging_exp_rate3,4));
			
			//평균 역률
			$('#PF_IMP_TOT'		).text(formatNumber(data.resultGrid[0].pf_imp_tot,2));		
			$('#PF_IMP_T1'		).text(formatNumber(data.resultGrid[0].pf_imp_rate1,2));		
			$('#PF_IMP_T2'		).text(formatNumber(data.resultGrid[0].pf_imp_rate2,2));		
			$('#PF_IMP_T3'		).text(formatNumber(data.resultGrid[0].pf_imp_rate3,2));	
			$('#PF_EXP_TOT'		).text(formatNumber(data.resultGrid[0].pf_exp_tot,2));		
			$('#PF_EXP_T1'		).text(formatNumber(data.resultGrid[0].pf_exp_rate1,2));		
			$('#PF_EXP_T2'		).text(formatNumber(data.resultGrid[0].pf_exp_rate2,2));		
			$('#PF_EXP_T3'		).text(formatNumber(data.resultGrid[0].pf_exp_rate3,2));
			
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