$(document).ready(function(){
	
	var tab_selected = null;
	
	$("div.tab-headers > div.tab-header").each(function() {		
		render_tab($(this));
	})
	
	function set_content(content_elem, content) {		
		content_elem.html(content);
	}
	
	function activate_tab(elem) {
		if(tab_selected!==null) {
			tab_selected.removeClass("focus");				
		}
		
		elem.addClass("focus");
		tab_selected = elem;
		
		var text = elem.attr("text");
		var content_elem = $(`#${elem.attr("content")}`);
		set_content(content_elem, text);
	}
	
	function close_tab(elem) {		
		console.log(elem[0]);
		console.log(tab_selected[0]);
		console.log(Object.is(elem[0], tab_selected[0]));
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
		
});