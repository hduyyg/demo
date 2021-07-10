function getData(api, callback) {
    var url = '/ajax/'+api;
    jQuery.support.cors = true;
    $.getJSON(url, function(data) {
        if(typeof(callback) != "function") return;
        callback(data);
    });
}
function error(e) {
    window.msg('error', e);
}
function correct(e) {
    window.msg('success', e);
}
function get_avatar(img, uid){
    $.get(
        '/ajax/member_get_avatar',
        {
            uid : uid
        },
        function(data){
            if (typeof img.attr == 'function'){
                img.attr('src', data.avatar);
            } else {
                $(img).attr('src', data.avatar);
            }
        },
        'json'
        );
}
function get_all_avatar(){
    $("img[data-avatar]").each(function(index, value){
        get_avatar(value, $(value).attr('data-avatar'));
    });
}

function get_group_logo(img, vid){
    $.get(
        '/ajax/group_get_logo',
        {
            vid : vid
        },
        function(data){
            if (typeof img.attr == 'function'){
                img.attr('src', data.avatar);
            } else {
                $(img).attr('src', data.avatar);
            }
        },
        'json'
        );
}
function get_all_group_logo(){
    $("img[data-group-logo]").each(function(index, value){
        get_group_logo(value, $(value).attr('data-group-logo'));
    });
}

function check_new_message() {
    if (uid == 0) {
        return;
    }
	$.get(
		'/ajax/pm_unread_long',
		{},
		function(data){
			if (data.code == 1){
				msg('message', '新消息', data.msg, '/message');
			} else if ($('#msg').attr('class') == 'message') {
				$('#msg').attr('style', '');
			}
		},
		'json'
	);
}

var QueryString = function () {
  var query_string = {};
  var query = window.location.search.substring(1);
  var vars = query.split("&");
  for (var i=0;i<vars.length;i++) {
    var pair = vars[i].split("=");
    if (typeof query_string[pair[0]] === "undefined") {
      query_string[pair[0]] = pair[1];
    } else if (typeof query_string[pair[0]] === "string") {
      var arr = [ query_string[pair[0]], pair[1] ];
      query_string[pair[0]] = arr;
    } else {
      query_string[pair[0]].push(pair[1]);
    }
  } 
    return query_string;
} ();

$(document).ready(function(){
   get_all_avatar();
   check_new_message();
   window.setInterval(check_new_message, 10000);
});
