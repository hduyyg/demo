// 全局调用的 js 文件

(function($) {
    ////////////////////
    // 通知模块
    // type: error, success, message
    // msg('error', 'Ooops...Wrong', 'SID8979编译错误', '/viewdetail.html')
    ////////////////////
    window.msg = function(type, title, msg, link) {
        if(window.hideMsgTimeout)
          clearTimeout(window.hideMsgTimeout);
        $('#msg').attr('class', type);
        $('#msg .title').html(title);
        $('#msg .msg').html(msg);
        if(link) {
            $('#msg .link').show();
            $('#msg .link a').attr('href', link);
			if (type == 'message') {
				$('#msg .title').html('<b>' + title + '</b>');
				$('#msg .link a').html('点这里阅读');
			}
        } else {
            window.hideMsgTimeout = setTimeout(function() {
                $('#msg').fadeOut();
            }, 5000);
            $('#msg .link').hide();
        }
        if (!$('#msg').is(':visible'))
          $('#msg').fadeIn();
    }

    window.correct = function(msg) {
        window.msg('success', '操作成功', msg, undefined);
    }

    window.error = function(msg) {
        window.msg('error', '操作失败', msg, 'link');
    }

    $(document).ready(function() {

        ////////////////////
        // 搜索模块
        ////////////////////

        $('#search-icon').on('click', function() {
            $('#search').submit();
        });
        $("#search").keydown(function(e){
	    if (e.keyCode==13){
                $(this).submit();
	    }
        });
        $('#search').on('submit', function(e) {
            var submit = function(keyword) {
                if(!keyword) return;
                window.location.href = "/search?name="+encodeURI(keyword);
            };
            submit($(this).val());
            e.preventDefault();
            e.stopPropagation();
            return false;
        });

        /////////////////////////
        // section添加奇偶的class
        /////////////////////////

        // :odd is not part of the CSS specification, so use .filter(":odd") here to get better perfermence
        $(".section").filter(':odd').addClass('odd-section');
        $(".section").filter(':even').addClass('even-section');

        //////////////////////////////////////
        // .bar 内部元素的垂直居中
        // 自动按照右边ul的高度撑开左边的title
        //////////////////////////////////////

        var height = $('.bar ul').height()
        if(height < 24) {
            height = 24;
            $('.bar ul').css('line-height', height+'px');
        }
        //$('.bar .title').css('line-height', height+'px');

        /////////////////////
        // 裁切dropdown高度
        /////////////////////

        // $('.dropdown-menu').hover(function() {
        //     var max = $(this).find('.after').height();
        //     $(this).css('max-height', max+'px');
        // }, function() {
        //     $(this).css('max-height'
        // });


    });
})(jQuery);
