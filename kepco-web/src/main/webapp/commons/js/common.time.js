/******************************
* 초를 시분초로
*******************************/
function SecToTime(data)
{
	var str = "";
	var s = m = h = -1;
	var stxt = mtxt = htxt = ""; 
	var data = parseInt(data);
	if(!data) return "00:00:00";
	else if(data < 10) return "00:00:0"+data;
	else if(data < 60) return "00:00:"+data;
	
	s = data % 60;
	
	if(data >= 60)
	{
		m = parseInt(data / 60);
		
		if(m >= 60)
		{
			h = parseInt(m / 60);
			m = m % 60;
		}
	}
	stxt = s;
	mtxt = m;
	htxt = h;
			
	if (s<10) {
		stxt = "0"+ s;
	}
	if (m<10) 
	{
		mtxt = "0"+ m;
	}	
	if (h<10) 
	{
		htxt = "0"+ h;
	}
	
	if(m > -1) {
		mtxt = mtxt;
	}
	else 
	{
		mtxt = "00";
	}
	
	if(h > -1)
	{
		htxt = htxt;
	}
	else
	{
		htxt = "00";
	}

	str = htxt +":"+ mtxt +":"+ stxt;

	return str;
}


/******************************
* 시분초 -> 초
*******************************/
function TimeToSec(data)
{
	var hour = Number(data.substr(0,2));
	var min =  Number(data.substr(2,2));
	var sec =  Number(data.substr(4,2));
	
	hour = hour * 60 * 60;
	min = min * 60;
	sec = hour + min + sec;
	
	return sec;
}


/******************************
* 시분초 -> 초
*******************************/
function diffTime(end, start)
{	
	var endTime = TimeToSec(end.substr(8,6));
	var startTime = TimeToSec(start.substr(8,6));	
	var sec = endTime - startTime;
	
	return SecToTime(sec);
}

/******************************
* 시분초 -> 초
*******************************/
function diffTime2(end, start)
{	
	var endTime = TimeToSec(end.substr(8,6));
	var startTime = TimeToSec(start.substr(8,6));	
	var sec = endTime - startTime;
	
	return sec;
}