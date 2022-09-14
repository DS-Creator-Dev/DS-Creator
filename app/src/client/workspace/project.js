let PROJECT;

$(document).ready(async function(){
	PROJECT = await api.windowData.get("project");	
	if(PROJECT===undefined) {
		alert("Error: No project.");
		return;
	}
	
	document.title = `DSC : ` + PROJECT.name;	
	$("#ProjectTree").setRootName(PROJECT.name);
	
	console.log(PROJECT)
})

//TOOLBAR

let saveBtn = document.querySelector(".tb-save");
let saveAsBtn = document.querySelector(".tb-save-as");
let compileBtn = document.querySelector(".tb-build");
let runBtn = document.querySelector(".tb-run");
let settingsBtn = document.querySelector(".tb-settings");

saveBtn.addEventListener('click', async function(){
	await api.project_manager.save(PROJECT);
})
saveAsBtn.addEventListener('click', async function(){
})
compileBtn.addEventListener('click', async function(){
	await api.project_manager.build(PROJECT);
	var make_result = await api.project_manager.make(PROJECT);	
	if(make_result.error != null) {		
		console.log(`Make failed\n\n${make_result.error}\n\n${make_result.stderr}`);
		return;
	}
	
})
runBtn.addEventListener('click', async function(){
	//await api.project_manager.build(PROJECT);
	var make_result = await api.project_manager.make(PROJECT);
	if(make_result.error != null) {		
		console.log(`Make failed\n\n${make_result.error}\n\n${make_result.stderr}`);
		return;
	}
	await api.EmulatorOpen()
})
settingsBtn.addEventListener('click', async function(){
})