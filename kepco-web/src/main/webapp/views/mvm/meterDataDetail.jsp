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
						<h3 style="margin-top: 6px">기타검침 > 상세 데이터 조회</h3>
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
													<th>계기 번호</th>
													<th>모뎀 번호</th>
													<th>계기 타입</th>
													<th>검침 항목</th>
													<th>검침일</th>
													<th>최종 통신일자</th>
												</tr>
											</thead>
											<tbody>
												<tr>
													<td><h3 id = "meter_serial"></h3></td>
													<td><h3 id = "device_serial"></h3></td>
													<td><h3 id = "meter_type"></h3></td>
													<td><h3 id = "obis_code_descr"></h3></td>
													<td><h3 id = "read_dt"></h3></td>
													<td><h3 id = "last_comm_dt"></h3></td>
												</tr>
											</tbody>
										</table>
									</div>
								</div>
								<!--  end : summary_area  -->

								<!--  start : search_area  -->
								<form name="search_form" id="search_form" method="post">
									<input type="hidden" id="meter_id" name="meter_id"value="${meter_id}" class="form-control">
									<input type="hidden" id="read_dt" name="read_dt"value="${read_dt}" class="form-control">
									<input type="hidden" id="obis_code" name="obis_code"value="${obis_code}" class="form-control">
									
								</form>
								<!--  end : search_area  -->

								<!--  start : payload_area  -->
								<div>
									<div style="width: 99%; height: 250px margin: 40px 0px 0px 0px">
										<h3><textarea id="payload" style=" width: 100%;  height: 240px; font-size: 25px; font-weight: bold;" readonly></textarea></h3>
									</div>
								</div>
								<!--  end : payload_area  -->

										
								
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
				url : COMMON_URL + "/ajaxMeterDataDetail",
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
			
			$('#read_dt'		).text(data.resultGrid[0].read_dt);
			$('#mtime'			).text(data.resultGrid[0].mtime);
			$('#itime'			).text(data.resultGrid[0].itime);
			$('#branch_nm'		).text(branch_nm);
			$('#meter_type'		).text(data.resultGrid[0].meter_type);
			$('#meter_serial'	).text(data.resultGrid[0].meter_serial);
			$('#device_serial'	).text(data.resultGrid[0].device_serial);
			$('#last_comm_dt'	).text(data.resultGrid[0].last_comm_dt);
			
			$('#payload'	    ).text(data.resultGrid[0].payload);
			$('#obis_code_descr').text(data.resultGrid[0].obis_code_descr);
			
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
