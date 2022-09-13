$.fn.hasAttr = function(name) {  
   return this.attr(name) !== undefined;
};
	
var tab_selected = null;
var iframe_data = null;

function show_tab(title) {		
	var template = api.tabs.template(title)
	iframe_data = api.tabs.data(title);
	$("#TabBody").attr("src",`../src/client/workspace/templates/${template}.html`);	
}

function set_content(content_elem, content) {				
	
	content_elem.html(content);
}

function get_tab_header(title) {
	return $(`div.tab-header[text='${title}']`);
}

function get_near_tab(title) {
	var elem = $(`div.tab-header[text='${title}']`);
	var next = elem.next();
	var prev = elem.prev();	
	if(prev[0]==undefined) {
		if(next[0]==undefined) {
			console.log("prev=null, next=null");
			return null;			
		}
		else {
			console.log("choose next");
			return next;
		}					
	}
	else {
		console.log("choose prev");
		return prev;
	}
}

function activate_tab(title) {
	if(tab_selected!==null) {
		tab_selected.removeClass("focus");				
	}			
	
	var header = get_tab_header(title)
	header.addClass("focus");
	tab_selected = header;
	
	iframe_data = api.tabs.data(title);
	console.log("Data:", iframe_data);
	var template = api.tabs.template(title)
	$("#TabBody").attr("src",`../src/client/workspace/templates/${template}.html`);	
	
	show_tab(title);
	
}

function close_tab(title) {
	var header  = get_tab_header(title);
	
	var near = get_near_tab(title);
	header.remove();
	if(near==null) {
		$("#TabBody")[0].contentWindow.document.write("<h1 align='center'>All tabs closed</h1>");					
		return;
	}	
	console.log(near);
	
	activate_tab(near.attr("text"));
}

// Creates tab header
function render_tab(elem) {
	var text = elem.attr("text");
	elem.append(`<span>${text}</span>`);
	elem.addClass("noselect");
	
	var close_btn = $('<button class="tab-close-btn"/>');
	elem.append(close_btn);
	close_btn.click(function(e){			
		close_tab(elem.attr("text"));
		e.stopPropagation();
	});	
	
	elem.click(function(e){						
		activate_tab($(this).attr("text"));
	});	
}

api.tabs.on("tab_added", (data)=>{
	console.log(data.tab.title);
})

function createTabHeader(title, template) {
	var tab_header = $('<div class="tab-header" content="TabContent"></div>');
	tab_header.attr("text", title);
	tab_header.attr("template", template);
	render_tab(tab_header);
	return tab_header;
}

function showInTabBody(title) {
	console.log(title);
	var data = api.tabs.data(title);
	var template = api.tabs.template(title);
		
	iframe_data = data;	
	
}

function createTab(title, template) {		
	var tab_header = createTabHeader(title, template);
	$("#TabHeaders").append(tab_header);
	
	showInTabBody(title);
	
	activate_tab(title);
}

api.tabs.on("tab_added", (data)=>{	
	var tab = data.tab;
	console.log(tab)
	createTab(tab.title, tab.template);
})

function add_tab(title, template, data) {	
	if(!api.tabs.add(title, template, data)) {
		// tab already exists, show it		
		activate_tab(title);
	}
}


$(document).ready(function(){	
	$("div.tab-headers > div.tab-header").each(function() {		
		var title = $(this).attr("text")
		var template = $(this).attr("template");
		$(this).remove();
		add_tab(title, template, null);		
	})
	
	activate_tab($("div","#TabHeaders").first().attr("text"))	
	
	
	$("#TabBody").on("load",function(){		
		/*if(iframe_data === undefined) {
			return; // prevent event firing multiple times [js is wierd :( ]
		}*/		
		if($(this)[0].contentWindow.loader !== undefined) {			
			$(this)[0].contentWindow.document.title = tab_selected.attr("text");
			$(this)[0].contentWindow.loader(iframe_data);
			console.log("Template : Loader called");			
		}
		else {
			console.log("Template Warning : No loader script attached."); 
		}
	});
});