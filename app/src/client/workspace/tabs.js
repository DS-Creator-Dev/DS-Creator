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

function activate_tab(title) {
	if(tab_selected!==null) {
		tab_selected.removeClass("focus");				
	}			
	
	var header = get_tab_header(title)
	header.addClass("focus");
	tab_selected = header;
	
	var template = api.tabs.template(title)
	$("#TabBody").attr("src",`../src/client/workspace/templates/${template}.html`);	
		
	show_tab(title);
	
}

function close_tab(elem) {				
	alert("Closing tabs is currently not working");
	return;
	if(elem[0]===tab_selected[0]) {			
		var content_elem = $(`#${elem.attr("content")}`);
		var prev = elem.prev();
		var next = elem.next();
		if(prev[0]==undefined) {
			if(next[0]==undefined) {
				console.log("prev=null, next=null");
				set_content(content_elem, "<h1 align='center'>All tabs closed</h1>");
			}
			else {
				console.log("choose next");
				activate_tab(next);
			}					
		}
		else {
			console.log("choose prev");
			activate_tab(prev);
		}
	}	
	// TO DO: ask for save progress here
	elem.data("tab_view").remove();
	elem.remove();
}

// Creates tab header
function render_tab(elem) {
	var text = elem.attr("text");
	elem.append(`<span>${text}</span>`);
	elem.addClass("noselect");
	
	var close_btn = $('<button class="tab-close-btn"/>');
	elem.append(close_btn);
	close_btn.click(function(e){			
		close_tab(elem);
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
	api.tabs.add(title, template, data);	
}


$(document).ready(function(){	
	$("div.tab-headers > div.tab-header").each(function() {		
		var title = $(this).attr("text")
		var template = $(this).attr("template");
		$(this).remove();
		add_tab(title, template, null);
		//render_tab($(this));
	})
	
	activate_tab($("div","#TabHeaders").first().attr("text"))	
	
	
	$("#TabBody").on("load",function(){		
		/*if(iframe_data === undefined) {
			return; // prevent event firing multiple times [js is wierd :( ]
		}*/		
		if($(this)[0].contentWindow.loader !== undefined) {			
			$(this)[0].contentWindow.loader(iframe_data);
			console.log("Template : Loader called");			
		}
		else {
			console.log("Template Warning : No loader script attached."); 
		}
	});
});