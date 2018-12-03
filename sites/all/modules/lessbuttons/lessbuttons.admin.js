function lessbuttons_gCode() {
    
    var opts = [];
    var auto8 = 0;
    var onb8 = 0;
    
    var socIds = ['facebook','twitter','googleplus','linkedin','pinterest','reddit','vkontakte','odnoklassniki','email','printfriendly','googlebookmarks','gmail','outlook','yahoomail','aolmail','mailru','baidu','tumblr','blogger','livejournal','stumbleupon','rediff','taringa','douban','xing','evernote','digg','typepad','scoopit','bufferapp','myspace','mixi','delicious','skyrock','friendfeed','diigo','meneame','dzone','fark','folkd','netlog','bitly','care2','n4g','kaixin001','wanelo','myvidster','draugiem','newsvine','jappy','pdfonline','orkut','surfingbird','tuenti','sulia','bizsugar','blinklist','nujij','youmob','vkrugudruzei','moikrug','sodahead','sonico','instapaper','taaza','newsmeback','citeulike','tapiture','buddymarks','safelinking','diggita','dudu','fwisp','efactor','gg','kaboodle','startaid','svejo','plaxo','blurpalicious','misterwong','jumptags','fashiolista','informazione','bobrdobr','ziczac','thisnext','webnews','mendeley','netvouz','origo','box','blogmarks','govn','tvinx','bookmerken','balltribe','upnews','stuffpit','wirefan','ihavegot','moemesto','me2day','transferr','beat100','mashbord','domelhor','thrillon','100zakladok','posteezy','arto','ekudos','blogkeen','identi','favoritus','linkshares','extraplay','iorbix','goodnoows','scoopat'];
    for (var lbCnt=0; lbCnt<socIds.length; lbCnt++) {
        var id = socIds [lbCnt];
        if (lbCnt < 8) {
            if (document.getElementById ('edit-lessbuttons-placement-custom-buttons-'+id+'-auto').checked) {
                auto8++;
                opts.push (id + '=auto');
            }
        } else {
            if (document.getElementById ('edit-lessbuttons-placement-custom-buttons-'+id+'-1').checked) {
                onb8++;
            }
        }
        if (document.getElementById ('edit-lessbuttons-placement-custom-buttons-'+id+'-1').checked) {
            opts.push (id + '=1');
        }
    }
    if (auto8 == 8 && onb8 == 0) {
        opts = [];
    }

    if (document.getElementById ("edit-lessbuttons-placement-outside-right").checked) opts.push ("position=right");
    if (document.getElementById ("edit-lessbuttons-placement-outside-bottom").checked) opts.push ("position=bottom");
    
    var c = "https://lessbuttons.com/script.js";
    if (opts.length) {
        c += "?" + opts.join ("&");
    }

    var ic = '<div style="padding-left: 50px; padding-right: 50px;">'
    +'<h1>Preview</h1>'
    +'<div id="lessbuttons_holder"></div><script async src="'+c+'"></'+'script>'
    +'<p>'
    +'Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.'
    +'</p>'
    +'<p>'
    +'Sed ut perspiciatis, unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam eaque ipsa, quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt, explicabo. Nemo enim ipsam voluptatem, quia voluptas sit, aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos, qui ratione voluptatem sequi nesciunt, neque porro quisquam est, qui dolorem ipsum, quia dolor sit, amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt, ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit, qui in ea voluptate velit esse, quam nihil molestiae consequatur, vel illum, qui dolorem eum fugiat, quo voluptas nulla pariatur? At vero eos et accusamus et iusto odio dignissimos ducimus, qui blanditiis praesentium voluptatum deleniti atque corrupti, quos dolores et quas molestias excepturi sint, obcaecati cupiditate non provident, similique sunt in culpa, qui officia deserunt mollitia animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis est et expedita distinctio. Nam libero tempore, cum soluta nobis est eligendi optio, cumque nihil impedit, quo minus id, quod maxime placeat, facere possimus, omnis voluptas assumenda est, omnis dolor repellendus. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet, ut et voluptates repudiandae sint et molestiae non recusandae. Itaque earum rerum hic tenetur a sapiente delectus, ut aut reiciendis voluptatibus maiores alias consequatur aut perferendis doloribus asperiores repellat.'
    +'</p>'
    +'</div>';
    
    document.getElementById('lessbuttons_code_iframe').src = "data:text/html;charset=utf-8," + escape(ic);
    
    return true;
}

var lessbuttons_oldonload = window.onload;
if (typeof window.onload != 'function') {
    window.onload = lessbuttons_gCode;
} else {
    window.onload = function() {
        if (lessbuttons_oldonload) {
            lessbuttons_oldonload();
        }
        lessbuttons_gCode();
    }
}
