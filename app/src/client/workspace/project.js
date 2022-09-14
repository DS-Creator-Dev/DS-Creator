let PROJECT;

function loadProjectTree() {
	$("#ProjectTree").setRootName(PROJECT.name);
	
	for(var i=0;i<PROJECT.assets.length;i++) {
		createNode(pt_assets, PROJECT.assets[i].name,
		{"node":"file", "spec":"asset"});
	}
	
}

$(document).ready(async function(){
	PROJECT = await api.windowData.get("project");	
	if(PROJECT===undefined) {
		alert("Error: No project.");
		return;
	}
	
	document.title = `DSC : ` + PROJECT.name;		
	
	loadProjectTree();
	
	console.log(PROJECT)
})

//TOOLBAR

let saveBtn = document.querySelector(".tb-save");
let saveAsBtn = document.querySelector(".tb-save-as");
let compileBtn = document.querySelector(".tb-build");
let runBtn = document.querySelector(".tb-run");
let settingsBtn = document.querySelector(".tb-settings");

saveBtn.addEventListener('click', async function(){
	// await api.project_manager.save(PROJECT);
	
	// Idea : Could we use this for saving individual resources?	
	// api_manager.save() only writes the .DSCProj file and is called
	// each time the project tree is affected, calling it on click is futile
})

saveAsBtn.addEventListener('click', async function(){
	// Idea : Use this to make a copy of a resource with other name
	// e.g. create Scene1, Save it As Scene2 and do slight modifications on it
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