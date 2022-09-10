$.fn.setRootName = function(name) {
	$(this).attr("name", name);
	$("h6", $(this)).html(name);
}

$(document).ready(function(){
	var ptree = $('#ProjectTree');
	ptree.addClass("treeview noselect");
	ptree.append($(`<h6>${ptree.attr('name')}</h6>`));

	var root = $('<ul class="subtree">');
	ptree.append(root);
	root=ptree;
	
	var actors = createNode(root, "actors", {"node":"folder", "spec":"actor"});
	var assets = createNode(root, "assets", {"node":"folder", "spec":"asset"});
	var scenes = createNode(root, "scenes", {"node":"folder", "spec":"scene"});
	var sound = createNode(root, "sound", {"node":"folder", "spec":"sound"});	
	
	
	createNode(actors,"actor1");
	createNode(actors,"actor2");
	createNode(actors,"actor3");
	
	createNode(scenes, "scene1");
	createNode(scenes, "scene2");
	
	createNode(sound, "sound1")
	
	function createNode(parent, name, type) {
		
		var item = $(`<li><span class="label"><span>${name}</span>&nbsp;</span></li>`);	

		if(type!==undefined) {
			if(type["node"]=="folder") {
				var new_btn = $(`<a class="create_new" href="#">(new)</a>`);
				new_btn.attr("what",type["spec"]);
				$("span.label",item).append(new_btn);
				new_btn.click(async function(){										
					var item_type = $(this).attr("what");
					await api.windowData.set("inDialog", true);
					api.openNewResourceDialog(`./workspace/new_dialogs/new_${item_type}.html`);									
					// wait for dialog to close (better approach?)
					
					while(await api.windowData.get("inDialog")==true) {
						await api.utils.sleep(10);
					};																	
					console.log("Dialog closed");					
					
					var result = await api.windowData.get("new_dialog_result")
					console.log(result);
					
					if(item_type=="asset") {
						// TO DO list:
						// copy resource to project directory;
						// generate the appropiate resource Object;
						// insert it in the project tree;
						createNode(assets, result.name);
					}
				});
			}
		}
		
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