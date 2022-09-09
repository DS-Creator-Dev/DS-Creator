const discop = require("./discop.js")


function Asset(name) {
	var self = this;
	self.name = name;
		
	self.precompile = function() {
		
	}
	
	return this;
}

function Actor(name) {
	var self = this;
	self.name = name;
	
	self.precompile = function() {
		
	}
		
	
	return this;
}

function Scene(name) {
	var self = this;
	self.name = name;		
	
	self.precompile = function() {
		
	}
	
	return this;
}

function Sound(name) {
	var self = this;
	self.name = name;		
	
	self.precompile = function() {
		
	}
	
	return this;
}


function Project (path, action) {
	let self=this;
	self.path = path;
	self.name = "UntitledProject";
	self.assets = [];
	self.actors = [];
	self.scenes = [];
	self.sounds = [];		
	
	console.log(arguments);
	
	self.getRelPath = function(...rel_path) {
		return discop.combinePaths(self.path, ...rel_path);
	}
	
	
	self.setName = function(new_name) {
		self.name = new_name;
	}		
	
	// create .DSCProj file 
	self.writeProjFile = function() {				
		discop.writeTextFileSync(self.getRelPath(`.DSCProj`), 
			JSON.stringify(self,
				function(key, val) { 
					if (key !== "path") return val; // exclude internal property .path
				},
				2) // spacing level
		);
	};
	
	self.loadProjFile = function() {
		var data = JSON.parse(discop.readTextFileSync(self.getRelPath(`.DSCProj`)));
		// copy file contents to this
		for(var key in data) {
			self[key] = data[key];
		}		
	}
	
	self.addAsset = function(path) {
		var fname = discop.fileName(path);
		if(discop.existsFile(self.getRelPath("assets/",fname))) {
			if(confirm("An asset with the same name already exists. Overwrite?")) {
				
				assets.add(new Asset(fname));
			}
			else {
				return;
			}
		}
	}
	
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

module.exports.get_file = function(project, rel_path) {
	return discop.readFileSync(project.getRelPath(rel_path));
}

module.exports.set_file = function(project, rel_path, data) {
	discop.writeFileSync(project.getRelPath(rel_path), data);
}



