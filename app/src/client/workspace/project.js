let PROJECT;

$(document).ready(async function(){
	PROJECT = await api.windowData.get("project");	
	if(PROJECT===undefined) {
		alert("Error: No project.");
		return;
	}
	
	document.title = PROJECT.name;	
	$("#ProjectTree").setRootName(PROJECT.name);
	
	
})