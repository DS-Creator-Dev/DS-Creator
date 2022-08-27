$(document).ready(function(){
	
	var tab_selected = null;
	
	$("div.tab-headers > div.tab-header").each(function() {		
		render_tab($(this));
	})
	
	function render_tab(elem) {
		var text = elem.attr("text");
		elem.append(`<span>${text}</span>`);
		elem.addClass("noselect");
		elem.click(function(e){
			if(tab_selected!==null) {
				tab_selected.removeClass("focus");				
			}
			
			$(this).addClass("focus");
			tab_selected = $(this);
			
			var content_elem = $(`#${elem.attr("content")}`);
			content_elem.html(text);
		});
	}
});