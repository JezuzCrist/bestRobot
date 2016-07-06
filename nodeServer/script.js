var ajax = function callAjax(url, callback){
    var xmlhttp;
    // compatible with IE7+, Firefox, Chrome, Opera, Safari
    xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function(){
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
            callback(xmlhttp.responseText);
        }
    }
    xmlhttp.open("GET", url, true);
    xmlhttp.send();
}

var refreshImage = function () {
	document.body.getElementsByTagName("img")[0].src = "/data/logic.png?kaka="+Math.random();
}



var refreshText = function () {
  ajax("/data/robot_positions.json", function (data){
  	document.getElementById("robotLocation").innerHTML = data;
  });
}

var refreshData = function () {
	refreshImage();
	refreshText();
}

setInterval(refreshData,1000);