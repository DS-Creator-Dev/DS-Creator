

$(document).ready(function(){
	var ptree = $('#ProjectTree');
	ptree.addClass("treeview noselect");
	ptree.append($(`<h6>${ptree.attr('name')}</h6>`));

	var root = $('<ul class="subtree">');
	ptree.append(root);
	root=ptree;
	
	var actors = createNode(root, "actors");
	var assets = createNode(root, "assets");
	var scenes = createNode(root, "scenes");
	var sound = createNode(root, "sound");	
	
	console.log(actors);
	createNode(actors,"actor1");
	createNode(actors,"actor2");
	createNode(actors,"actor3");
	
	createNode(scenes, "scene1");
	createNode(scenes, "scene2");
	
	createNode(sound, "sound1")
	
	function createNode(parent, name, type) {
		
		var item = $(`<li><span class="label">${name}</span></li>`);		
		item.click(function(e){
			if(!$(this).hasClass("expandable")) {				
				console.log($("span.label",this).html())
				e.stopPropagation();
			}
		});
		
		if($("ul.subtree", parent).length==0) {							
			var subtree = $("<ul class='subtree'>");			
			subtree.append(item);						
			parent.append(subtree);
					
			parent.addClass("expandable");
			parent.click(function(e) {						
				if(e.offsetX<10 && e.offsetY<20){
					if($(this).hasClass("expanded")) {
						$(this).removeClass("expanded");
					}
					else {
						$(this).addClass("expanded");
					}				
				}
			});
			
			return item;
		}		
		
		var subtree = $("ul.subtree",parent);
		console.log(subtree);
		subtree.append(item);		
		return item;
	}	
		
})