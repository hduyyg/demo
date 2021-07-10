var isLogin = false;
$(document).ready(function() {
    getData('member_get_current_session',function(data) {
//        console.log(data);
        if(data['code'] != 0) {
            isLogin = true;
            var username = data['username'],
                avatar = data['avatar'],
                uid = data['uid'];
            $('#user .info .main').html(username);
            $('#user .info .sub').html('<a href="/member">用户中心</a>');
            $('#user .img').html('<img src="'+avatar+'">');
            $('#user .img').show();
            $('#user .img').click(function() {
                window.location.href = '/member/';
            });
        } else {
            isLogin = false;
            var href = '/member/login?redir=' + window.location.href;
            $('#user .info .main').html('<a href="'+href+'">登录</a>');
            href = 'http://www.rqnoj.cn/member/register?redir=' + window.location.href;
            $('#user .info .sub').html('<a href="'+href+'">注册账号</a>');
        }
    });
});
