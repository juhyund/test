$(document).ready(function() {	
	var height = $(document).height();
	
	if(height > 800) {
		$("#contentsFrame",parent.document).height(height + 10);
	} 
});