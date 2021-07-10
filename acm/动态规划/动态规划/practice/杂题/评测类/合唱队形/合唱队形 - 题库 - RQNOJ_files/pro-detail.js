var lastModified = new Date().getTime();
var aceMode = "c_cpp";
var aceLang = "c";
var aceText = "undefined";
var CodeChange = false;
LazyLoad.js('/static/js/ace/ace.js', function () {
    (function() {
        if (login_state){
            $('#editor').html("");
            window.editor = ace.edit("editor");
            window.editor.setTheme("ace/theme/tomorrow");
            window.editor.getSession().setMode("ace/mode/" + aceMode);
            window.editor.gotoLine(2);
            window.editor.getSession().on("change", function(e){
                aceText = window.editor.getSession().getValue();
                CodeChange = true;
            });
            if (typeof user_code.lang != 'undefined') {
                window.editor.getSession().setValue(user_code.code);
                aceText = user_code.code;
                aceLang = user_code.lang;
                switch(aceLang){
                case 'c': case 'cpp':
                    aceMode = 'c_cpp';
                    break;
                default:
                    aceMode = aceLang;
                    break;
                }
                window.editor.getSession().setMode("ace/mode/" + aceMode);
                $('#language-bar span[data-lang=' + aceLang + ']').click();

            }
        }
    })();
});

$(document).ready(function() {
    getConstantFun();
    setInterval(function(){
        if (aceText != 'undefined')
            writeCodeFun(aceLang, aceText);
    }, 30 * 1000);
    $("#pro-detail-submit-save").click(function(e){
        if (aceText != 'undefined')
            writeCodeFun(aceLang, aceText);
    });
    $('#problem-detail-info .score .chart').html(genChart(quality_chart));
    $('#pro-detail-submit-done').click(function(){
        $.post(
            '/ajax/submit_problem_code',
            {
                "lang" : $("#language-bar span.current").attr('data-lang'),
                "code" : aceText,
                "pid" : pid,
                "vpid" : vpid
            },
            function(data) {
                if (data.code == 0)
                    error(data.msg);
                else {
                    correct('提交成功，正在跳转');
                    setTimeout(function(){
                        window.location.href="/status";
                    }, 3000);
                }

            },
            'json'
            );
    });
});

var getConstantFun = function getConstant() {
    //根据登录状态修改下拉列表
    if (login_state){

    } else {
        $(".status.dropdown-menu").addClass('no-dropdown-menu');
        $(".status.dropdown-menu").removeClass('dropdown-menu');
    }

    //获取题目简单的标签
    var s = '';
    $('#problem-detail-info .tags .before').html('');
    if (simple_tags.length == 0){
        $('#problem-detail-info .tags .before').html('还木有标签哦~');
        $('.tags.dropdown-menu').addClass('no-dropdown-menu');
        $('.tags.dropdown-menu').removeClass('dropdown-menu');
    }
    $.each(simple_tags, function(index, value) {
        $('#problem-detail-info .tags .before').append(value.tag_name + " ");
    });

    //获取题目全部标签
    var s = '';
    $.each(more_tags, function(index, value) {
        s += '<div class="em">' + value.parent_name + '</div>';
        s += '<p>';
        $.each(value.child, function(index, value) {
            s += '<a href="/tags/' + value.tag_id + '">' + value.tag_name + '</a>&nbsp;';
        });
        s += '</p>';
    });
    $("#problem-detail-info .tags .after .moretag").html(s);

    //获取题目通过状态
    if (problem_state.code == 0) {
        $("#problem-detail-info .status .before").html("您还没有登录");
        $("#problem-detail-info .status").addClass('no-dropdown-menu').removeClass('dropdown-menu');
    } else {
        if (problem_state.code == 1) {
            $("#problem-detail-info .status .before").html(problem_state.msg);
            $("#problem-detail-info .status").addClass('no-dropdown-menu').removeClass('dropdown-menu');
        } else {
            //至少有提交过了
            $("#problem-detail-info .status .before").html(problem_state.diff);
            if (problem_state.ac == 1){
                //已通过
                $("#problem-detail-info .status .after .ac").html('已通过');
                $("#problem-detail-info .status .after .timecost").html("运行耗时：" + problem_state.exec_time + " ms");
                $("#problem-detail-info .status .after .ramcost").html("运行内存：" + problem_state.exec_mem + " KB");
            }
            if (problem_state.ac == 2){
                //未通过
                $("#problem-detail-info .status .after .ac").html('未通过');
                $("#problem-detail-info .status .after .ac").addClass('wa').removeClass('ac');
                $("#problem-detail-info .status .after .timecost").html("运行耗时：无效");
                $("#problem-detail-info .status .after .ramcost").html("运行内存：无效");
            }
            if (problem_state.ac == 0){
                //未做过
                $("#problem-detail-info .status .before").html('您还木有做过');
                $("#problem-detail-info .status").addClass('no-dropdown-menu').removeClass('dropdown-menu');
            }
            $("#problem-detail-info .status .after .time").html(problem_state.time);
            $("#problem-detail-info .status .after .extra-bar").on('click', function(event){
                window.location.href="/status/" + problem_state.status_id;
            });
        }
    }
    /*
    $.get(
        '/ajax/user_problem_state',
        {
            "pid" : pid
        },
        function(data) {
            console.log(data);
            if (typeof data.code != "undefined") {
                if (data.code == 0) {
                    $("#problem-detail-info .status .before").html("您还没有登录");
                }
                if (data.code == 1) {
                    $("#problem-detail-info .status .before").html(data.msg);
                    $("#problem-detail-info .status .after").html(data.msg);
                }
            } else {
                $("#problem-detail-info .status .after .ac").html(data.ac);
                if (data.ac == '已通过') {
                    console.log($("#problem-detail-info .tags .extra-bar .tagsplus").html());
                    //$("#problem-detail-info .tags .extra-bar .tagsplus").hide();
                }
                $("#problem-detail-info .status .after .time").html(data.time);
                $("#problem-detail-info .status .after .timecost").html("运行耗时：" + data.exec_time + " ms");
                $("#problem-detail-info .status .after .ramcost").html("运行内存：" + data.exec_mem + " KB");
                $("#problem-detail-info .status .before").html(data.diff);
                $("#problem-detail-info .status .after .extra-bar").on('click', function(event){
                    window.location.href="/status/" + data.status_id;
                });
            }
        },
        'json'
        );
    */
    //获取题目的质量
    var quality = problem_detail.quality;
    if (quality != 0){
        $('#problem-detail-info .score .before').html('质量 ' + quality);
        $('#score-dropdown-after-quality').html(quality);
    } else {
        $('#problem-detail-info .score .before').html('质量还不能统计出来哦~');
        $('#score-dropdown-after-quality').html('无');
    }
}



var writeCodeFun = function writeCode(lang, code) {
    if (!CodeChange)
        return;
    CodeChange = false;
    $.post(
        '/ajax/save_problem_code',
        {
            "lang" : lang,
            "code" : code,
            "pid" : pid
        },
        function(data) {
            if (data.code == 1){
                correct('代码保存成功');
            }
        },
        'json'
        );
}

$(document).ready(function() {
    $('#problem-title-nav').localScroll();
    $('#language-bar span').click(function(){
        $('#language-bar .current').removeClass('current');
        var newmode = $(this).attr('class');
        aceMode = newmode;
        aceLang = $(this).attr('data-lang');
        $('#language .now').text($(this).text());
        $(this).addClass('current');
        editor.getSession().setMode("ace/mode/"+newmode);
        $('#language-bar').slideUp(800);
    });
    $('#language').click(function() {
        if ($('#language-bar').is(':visible')) {
            $('#language-bar').slideUp(200);
        } else {
            $('#language-bar').slideDown(300);
        }
    });
    $('#problem-talk-add-type').click(function() {
        var text = $(this).text().replace(/[ \n]*/g, '');
        if(text == '讨论') {
            $(this).find('strong').text('题解');
        } else {
            $(this).find('strong').text('讨论');
        }
    });
});

$(document).ready(function(){
    $("#problem-detail-talk-add").hide();
    $("#problem-detail-talk-add-button").click(function(e){
        e.preventDefault();
        $("#problem-detail-talk-add").fadeIn('slow');
        $('html, body').animate({
            scrollTop : $("#problem-detail-talk-add").offset().top - 100
        }, 500);
    });
    $("#problem-detail-talk-add-close").on('click', function(e){
        e.preventDefault();
        $("#problem-detail-talk-add").fadeOut('slow');
        $('html, body').animate({
            scrollTop : $("#problem-detail-talk").offset().top - 100
        }, 500);
    });
});

$(document).ready(function(){
    $("#problem-detail-talk-add-submit").on('click', function(e){
        e.preventDefault();
        $.post(
            '/ajax/new_discuss_thread',
            {
                title : $('#problem-talk-add-title').val(),
                content : $("#problem-talk-add-content").val(),
                vpid : vpid,
                voj_id : voj_id,
                pid : pid
            },
            function(e){
                if (e.code == 0) {
                    error(e.msg);
                    return ;
                };
                if (e.code == 10) {
                    correct('讨论发送成功，即将跳转');
                    setTimeout(function(){
                        window.location.href="/discussion/" + e.thread;
                    }, 1000);
                    return ;
                }
            },
            'json'
            );
    });
    $("#problem-detail-talk-more").on('click', function(e){
        e.preventDefault();
        $.get(
            '/ajax/get_more_discuss',
            {
                "voj_id"    : voj_id,
                "pid"       : pid,
                "last_id"   : discuss_lastid,
                'timestamp' : new Date().getTime()
            },
            function(data){
                if (data.length == 0) {
                    $("#problem-detail-talk-more").html('没有更多讨论了~');
                    // error('没有更多的讨论了哦，不过自己可以发表一些哟~');
                    return ;
                }
                var s = '';
                var height = $("#problem-detail-talk ul").height();
                $("#problem-detail-talk ul").css("max-height", height);
                $("#problem-detail-talk ul").css("overflow", "hidden");
                $.each(data, function(index, value){
                    s += "<li><a href=\"/discussion/" + value.thread_id + "\">[ 讨论 ] " + value.title + "</a> " + value.publish_time + "&nbsp;/&nbsp;" + value.reply_count + "&nbsp;回复&nbsp;/&nbsp" + value.ding_count + "&nbsp;顶</li>";
                    if (value.thread_id < discuss_lastid)
                        discuss_lastid = value.thread_id;
                });
                $("#problem-detail-talk ul").append(s);
                $("#problem-detail-talk ul").animate(
                    {
                        maxHeight : "+=200"
                    },
                    500
                    );
            },
            'json'
            );
    });
});


$(document).ready(function() {
    $('.stars .star').hover(function() {
        var exp = $(this).attr('nth');
        $(this).parent().find('.star').each(function() {
            var nth = $(this).attr('nth');
            nth > exp ? $(this).html('☆') : $(this).html('★');
        });
    }, function() {
        $(this).parent().find('.star').each(function() {
            var nth = $(this).attr('nth');
            var star = $(this).parent().attr('star');
            nth > star ? $(this).html('☆') : $(this).html('★');
        });
    });

    $('.stars').on('click', '.star', function(e){
        $.get(
            '/ajax/new_problem_level/' + pid + '/' + $(this).attr('nth'),
            {

            },
            function(e){
                if (typeof e.code == 'undefined') {
                    error('发生未知错误，请刷新页面重试');
                    return ;
                }
                if (e.code == 0){
                    error(e.msg);
                    return;
                } else {
                    correct('评价成功');
                }
            },
            'json'
            );
    });

    if (typeof user_level.code == 'undefined') {
        $('.stars').attr('star', user_level);
    }
    $('.stars').find('.star').each(function() {
        var nth = $(this).attr('nth');
        var star = $(this).parent().attr('star');
        nth > star ? $(this).html('☆') : $(this).html('★');
    });
});

after_login_fun = function(){
    window.location.reload();
}

$(document).ready(function(){
    $("#do_problem_fav").click(function(){
        $.post(
            '/ajax/toggle_problem_fav',
            {
                problem:pid
            },
            function(data){
                if (data.code == 0){
                    error(data.msg);
                } else {
                    if (data.add == 0){
                        $("#do_problem_fav").html('☆');
                        correct('取消收藏成功');
                    } else {
                        $("#do_problem_fav").html('★');
                        correct('添加收藏成功');
                    }
                }
            },
            'json'
            );
    })
})

function show_safecode() {
	load_safecode();
	$("#safecode-info").show();
	$("#safecode").show();
	safecodeRequired = 1;
}

function hide_safecode(){
	$("#safecode-info").hide();
	$("#safecode").hide();
	safecodeRequired = 0;
}

function require_safecode() {
	$.get(
		'/ajax/safecode_required',
		{},
		function(data) {
//			console.log(data);
			if (data.code == 0) {
				hide_safecode();
			}
			else {
				show_safecode();
			}

		},
		'json'
		);

}

function load_safecode() {
	$.get(
		'/ajax/safecode_get',
		{},
		function(data){
//			console.log(data);
			if (typeof data.image != 'undefined') {
				var img = data['image'];
	            img = 'url('+img+') no-repeat right center';
//	            console.log(img);
	            $('#safecode-info').css('background', img);
				}
		},
		'json'
		);
}


function login () {
    var data = {
        'username' : $('[name=username]').val(),
        'password' : $('[name=password]').val(),
        'safecode' : $('[name=safecode]').val(),
        'period' : 7 * 24,
        'redir' : '/problem/' + pid
    };

    $.post(
        '/ajax/member_login',
        data,
        function ( data ) {
//            console.log(data);
            if ( data.code == 1 ) {
                window.location.reload();
            }
            else {
                error( data.msg );
            }
            if ( data.safecode ) {
                show_safecode();
            }
            else {
                hide_safecode();
            }
        },
        'json'
    )
}

$(document).ready(function() {
    require_safecode();
    $('#editor-login').submit(function (e) {
        e.preventDefault();
        login();
        return false;
    });
});
