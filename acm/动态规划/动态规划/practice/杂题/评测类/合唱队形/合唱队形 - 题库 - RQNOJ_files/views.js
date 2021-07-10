var genChart = function(array) {
    for(var i=0, html=''; i<array.length; i++) {
        var len = array[i]/1.2;
        if(len > 0) len++;
        html += '<div style="border-left:'+len+'px solid #8a8a8a">'+array[i]+'%</div>';
    }
    return html;
};

var setUpButton = function () {
    var scrollTop = $(window).scrollTop();
    if (scrollTop > 1000) {
        $('#up').removeClass('hide');
    }
    else {
        $('#up').addClass('hide');
    }
};

var scrollUp = function () {
    $.scrollTo(0, 500);
};

$(document).ready(function() {
    // local scroll
    $.localScroll({ offset:-70 });

    // Up button
    $(window).on('scroll', setUpButton);
    $('#up').on('click', scrollUp);
});
