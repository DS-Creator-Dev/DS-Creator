$.fn.hasAttr = function(name) {  
   return this.attr(name) !== undefined;
};
	
var tab_selected = null;

function set_tab_view(content_elem, elem, view) {		
	view = $(`<div class="tab_view">${view}</div>`);
	content_elem.append(view);
	elem.data("tab_view", view);
}

function show_tab(content_elem, elem) {
	$("div.tab_view",content_elem).addClass("hidden");
	elem.data("tab_view").removeClass("hidden");
}

function set_content(content_elem, content) {				
	
	content_elem.html(content);
}

function activate_tab(elem) {
	if(tab_selected!==null) {
		tab_selected.removeClass("focus");				
	}		
	
	elem.addClass("focus");
	tab_selected = elem;		
			
	var content_elem = $(`#${elem.attr("content")}`);
	
	if(elem.data("tab_view")===undefined) {
		if(elem.hasAttr("template")) {
			var template_name = elem.attr("template");
			console.log("has template");
			
			// what does AppPath do? 
			api.GetAppPath()
			var path = localStorage.getItem("AppPath");			
			path += `/../src/client/workspace/templates/${template_name}.html`;
			template = api.discop.readTextFileSync(path);
			
			var tab_page = template;
			
			set_tab_view(content_elem, elem, tab_page);							
		}
		else {
			set_tab_view(content_elem, elem, elem.attr("text"));
		}
	}
	
	show_tab(content_elem, elem);				
	
}

function close_tab(elem) {				
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
		activate_tab($(this));
	});
}

api.tabs.on("tab_added", (data)=>{
	console.log(data.tab.title);
})

api.tabs.on("tab_added", (data)=>{
	var tab = data.tab;
	var tab_header = $('<div class="tab-header" content="TabContent"></div>');
	tab_header.attr("text", tab.title);
	tab_header.attr("template", tab.template);
	$("#TabHeaders").append(tab_header);
	render_tab(tab_header);
	activate_tab(tab_header);
})



function add_tab(title, template) {
	api.tabs.add(title, template);	
}


$(document).ready(function(){	
	$("div.tab-headers > div.tab-header").each(function() {		
		render_tab($(this));
	})
	
	activate_tab($("div","#TabHeaders").first())	
	
});