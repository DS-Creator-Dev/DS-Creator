$(document).ready(function(){
	const name_input = document.getElementById("name-input");
	const path_input = document.getElementById("path-input");

	$(name_input).on('input propertychange change', function(e){
		$("#name-input-error").html("");
		$(this).val($(this).val().replaceAll(' ','_'))
	})	
	
	$(path_input).on('input propertychange change', function(e) {
		$("#path-input-error").html("");
		if($(this).val().includes(' ')) {
			$("#path-input-error").html("Project path cannot contain spaces.");
			return;
		}		
	})
	
	
	$('#back-btn').click(function() {
      window.location.href = '../index.html';
    })
	
	
	$("#path-selector").click(async function(){			
		var path = await api.dialogs.pickDirectory()
		$(path_input).val(path);
		$(path_input).trigger("change");
	})
	
	$("#create-proj-btn").click(function(e) {				
		var proj_name = $("#name-input").val();
		var proj_path = api.discop.combinePaths($('#path-input').val(), $("#name-input").val());
		
		if(proj_name.length==0) {
			$("#name-input-error").html("Project name cannot be empty");
			return;
		}
		
		if($('#path-input').val().length==0) {
			$("#path-input-error").html("Project path cannot be empty");
			return;
		}				
		
		var project = api.project_manager.create_project(proj_path, proj_name);
		api.windowData.set("project", project);
		window.location.href="./workspace.html";
	});
});