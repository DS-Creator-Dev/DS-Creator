const discop = require("./discop.js")
const cmd = require("./cmd.js")

function Asset(name, width, height) {
	var self = this;	
	self.name = name;
	self.width = width;
	self.height = height;	
	
	return this;
}

Asset.prototype.precompile = function() {
	
}

function Actor(name) {
	var self = this;
	self.name = name;			
	
	return this;
}

Actor.prototype.precompile = function() {
	
}

function Scene(name) {
	var self = this;
	self.name = name;			
	
	return this;
}

Scene.prototype.precompile = function() {
	
}

function Sound(name) {
	var self = this;
	self.name = name;			
	
	return this;
}

Sound.prototype.precompile = function() {
	
}

function Project (path, action) {
	let self=this;	
	self.path = path;
	
	/// This is the object's part we can see from renderer:
	self.name = "UntitledProject";
	
	self.assets = [];
	self.actors = [];
	self.scenes = [];
	self.sounds = [];			
	
	self.startupScene = -1; // an index pointing to self.scenes[..]
	
		
	///--------------------------
	
	/////////////////////////////////////////////////////////////////////////////////
	
	if(action == "create") {
		
		if(discop.existsDir(path)) {			
			if(confirm("There is already a directory with this name. If you want to create the project anyway, " +
				"all the files in the directory will be wiped. Are you sure you want to continue?")) {
					
				console.log("wiping previous data...");
				discop.removeDirRec(path)				
			}			
			else {
				throw "Could not create project. Operation halted by user.";
			}
		}		
		
		if( discop.createDir(self.path).error ||
			discop.createDir(self.getRelPath("assets")).error ||
			discop.createDir(self.getRelPath("actors")).error ||
			discop.createDir(self.getRelPath("scenes")).error ||
			discop.createDir(self.getRelPath("sounds")).error ) 
		{			
			throw "Could not create project. Directory creation failed";
		}		
		
		self.setName(arguments[2]);	
		self.writeProjFile();
	}
	else if(action == "open") {
		if(!discop.existsFile(self.getRelPath(`.DSCProj`))) {
			if(confirm("Project config file is missing. Create a new one anyway?")) {
				// this is a sign of file corruption or user simply trying to open
				// a non-project file
				// At this step would be nice to automatically identify the entities
				// from assets, scenes... directory and write their appropriate objects
				// to the *.DSCProj file.
				self.writeProjFile();
			}			
			else {
				throw "Could not open project.";
			}
		}
		self.loadProjFile();	
		
		// load resources here...
	}		
	
	return this;
};

Project.prototype.getRelPath = function(...rel_path) {
	return discop.combinePaths(this.path, ...rel_path);
}


Project.prototype.setName = function(new_name) {
	this.name = new_name;
}		

// create .DSCProj file 
Project.prototype.writeProjFile = function() {		
	var self = this;
	discop.writeTextFileSync(self.getRelPath(`.DSCProj`), 
		JSON.stringify(self,
			function(key, val) { 
				if (key !== "path") return val; // exclude internal property .path
			},
			2) // spacing level
	);
};

Project.prototype.loadProjFile = function() {
	var self = this;
	var data = JSON.parse(discop.readTextFileSync(self.getRelPath(`.DSCProj`)));
	// copy file contents to this
	for(var key in data) {
		self[key] = data[key];
	}		
}

Project.prototype.removeAsset = function(name) {
	var target = this.assets.filter(x=>x.name==name);
	
	if(target.length==0) return;
	if(target.length>1) {
		confirm("Asset duplicate. Something's really messed up");
		return;
	}
	target = target[0];
	discop.removeFile(this.getRelPath("assets",`${name}.png`));
	this.assets = this.assets.filter(x=>x.name!=name);
}

Project.prototype.addAsset = function(path, name, width, height) {
	var self = this;
	var fname = discop.fileName(path);
	if(discop.existsFile(self.getRelPath("assets/", name+".png"))) {
		if(confirm("An asset with the same name already exists. Overwrite?")) {									
			self.removeAsset(name);
		}
		else {
			return false;
		}
	}
	
	discop.copyFileSync(path, this.getRelPath("assets", name+".png"));
	this.assets.push(new Asset(name, width, height));
	return true;
}

let cpaths = discop.combinePaths;

Project.prototype.generateBuildFiles = function() {
	// this is called before each compilation
	
	var self = this;
	var build_path = self.getRelPath(".build");
	
	var include_path = cpaths(build_path,"include");
	var source_path = cpaths(build_path,"source");
	var data_path = cpaths(build_path,"data");
	
	
	discop.removeDirRec(build_path);
	discop.createDir(build_path);
	discop.createDir(include_path);
	discop.createDir(source_path);
	discop.createDir(data_path);	
	
	// generate Makefile
	discop.copyTextFileSync(
		discop.appRelPath("presets/project_default/Makefile"),
		cpaths(build_path, "Makefile"),
		{
			"@{LIBDSC}" : discop.engineLibPath(),
			"@{PROJ_NAME}" : self.name
		}
	)
	
	
	// generate Launcher file
	// this sets the first scene to play (could be as well a DSC slash screen?)
	// scene transitions are performed in c++ via engine's Scene::close()->next(new Scene) api
	discop.copyTextFileSync(
		discop.appRelPath("presets/project_default/source/launcher.cpp"),
		cpaths(build_path, "source/launcher.cpp"),
		{
			"@{STARTUP_SCENE}" : (self.startupScene == -1 ? "DummyScene" : "<Not Implemented>"),
		}
	)		

	// at this point, <PROJECT_FILE>/.build/ contains a compileable libnds project	
	
}

module.exports.create_project = function(path, name) {
	try {
		var project = new Project(path, "create", name);
		return project;
	}
	catch(err) {
		alert(err);
		return null;
	}
};

module.exports.load_project = function(path) {
	try {
		var project = new Project(path, "load");
		
		return project;
	}
	catch(err) {
		alert(err);
		return null;
	}
};

module.exports.rel_path = function(project, ...args) {
	Object.setPrototypeOf(project, Project.prototype)	
	return project.getRelPath(...args);
}

module.exports.get_file = function(project, rel_path) {
	Object.setPrototypeOf(project, Project.prototype)	
	return discop.readFileSync(project.getRelPath(rel_path));	
}

module.exports.set_file = function(project, rel_path, data) {
	Object.setPrototypeOf(project, Project.prototype)
	discop.writeFileSync(project.getRelPath(rel_path), data);
}

module.exports.build = function(project) {
	Object.setPrototypeOf(project, Project.prototype)
	project.generateBuildFiles();
}

module.exports.make = async function(project) {
	Object.setPrototypeOf(project, Project.prototype)
	return await cmd.make(project.getRelPath(".build"));
}

module.exports.add_asset = function(project, path, name, width, height) {
	Object.setPrototypeOf(project, Project.prototype);
	var succeeded = project.addAsset(path, name, width, height);
	console.log(project);
	return {"succeeded":succeeded, "project":project};
}

module.exports.save = function(project) {
	Object.setPrototypeOf(project, Project.prototype);
	project.writeProjFile();
}

module.exports.get_resource_path = function(project, res_type, res_name) {
	var res_dir = "";
	var res_ext = "";
	switch(res_type) {
		case "asset" : res_dir = "assets", res_ext="png"; break;
		case "actor" : res_dir = "actors", res_ext="???"; break;
		case "scene" : res_dir = "scenes", res_ext="???"; break;
		case "sound" : res_dir = "sound", res_ext="???"; break;		
	}
	Object.setPrototypeOf(project, Project.prototype);
	return project.getRelPath(res_dir, `${res_name}.${res_ext}`);
}