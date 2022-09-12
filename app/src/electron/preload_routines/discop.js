/// Module to handle filesystem operations

const fs = require('fs')
const { exec, execSync } = require('child_process');
const nodePath = require("path");

// A\\B\\C --> A\\B
// if nodes_to_pass == 2 then  A\\B\\C --> A etc..
const parentPath = function(path, nodes_to_pass) {
	if(nodes_to_pass === undefined) {
		nodes_to_pass = 1;
	}
	for(var i=0;i<nodes_to_pass;i++)
		path = nodePath.parse(path).dir;
	return path;
}

module.exports.parentPath = parentPath;

// returns "{dirs...}/DS-Creator/app"
function executionPath() {
	var result = __dirname;
	result = parentPath(result, 3);
	return result;
}
module.exports.executionPath = executionPath;

function combinePaths(...args) {
	return nodePath.join(...args);
}

// path to the static library files.
// idea : DSCEngine path should reside in %%PATH%% just 
// like $(DESVKITARM) does 
module.exports.engineLibPath = function() {
	return combinePaths(executionPath(), "../engine");
}

module.exports.appRelPath = function(...args) {
	return combinePaths(executionPath(), ...args);
}

module.exports.combinePaths = combinePaths;

function fileName(path) {
	return nodePath.basename(path)
}
module.exports.fileName = fileName;

function existsDir(dirname) {	
	try {
		execSync(`test -d "${dirname}"`);
	}
	catch(error) {
		return false;
	}
	return true;
}

module.exports.existsDir = existsDir;


function existsFile(filename) {
	try {
		execSync(`test -f "${filename}"`);
	}
	catch(error) {
		return false;
	}
	return true;
}

module.exports.existsFile = existsFile;

module.exports.createDir = function(dirname) {
	var result = {error:false, content:null};
	try {
		execSync(`mkdir "${dirname}"`, (error, stdout, stderr) => {
			if (error) {	
				result.error = true;
				result.content = error;
			}
			if (stderr) {
				result.error = true;
				result.content = stderr;
			}
			
			result.content = stdout;     		
		})
	}
	catch(error) {
		result.error = true;
		result.content = error;
	}
	return result;	
}

module.exports.removeDirRec = function(dirname) {
	var result = {error:false, content:null};
	if(!existsDir(dirname)) 
		return result;
	
	try {
		execSync(`rm -rf "${dirname}"`, (error, stdout, stderr) => {
			if (error) {	
				result.error = true;
				result.content = error;
			}
			if (stderr) {
				result.error = true;
				result.content = stderr;
			}
			
			result.content = stdout;     		
		})
	}
	catch(error) {
		result.error = true;
		result.content = error;
	}
	return result;	
}

module.exports.removeFile = function(fname) {
	var result = {error:false, content:null};
	if(!existsFile(fname)) 
		return result;
	
	try {
		execSync(`rm -f "${fname}"`, (error, stdout, stderr) => {
			if (error) {	
				result.error = true;
				result.content = error;
			}
			if (stderr) {
				result.error = true;
				result.content = stderr;
			}
			
			result.content = stdout;     		
		})
	}
	catch(error) {
		result.error = true;
		result.content = error;
	}
	return result;	
}

module.exports.readFileSync = function (filename) {
	const data = fs.readFileSync(filename);
	return data;
}

module.exports.readTextFileSync = function (filename) {
	const data = fs.readFileSync(filename, 'utf8');
	return data;
}

module.exports.writeFileSync = function (filename, data) {
	fs.writeFileSync(filename, data);
}

module.exports.writeTextFileSync = function (filename, data) {
	fs.writeFileSync(filename, data, "utf8");
}

module.exports.writeCache = function(filename, data) {
	console.log(combinePaths(executionPath(),"cache",filename))
	fs.writeFileSync(combinePaths(executionPath(),"cache",filename), data);
}

module.exports.readCache = function(filename) {
	return fs.readFileSync(combinePaths(executionPath(),"cache",filename));
}

module.exports.copyTextFileSync = function(source, dest, dictionary) {
	var text = fs.readFileSync(source, 'utf8');
	for(var key in dictionary) {
		text = text.replaceAll(key, dictionary[key]);
	}
	fs.writeFileSync(dest, text, 'utf8');
}

module.exports.copyFileSync = function(source, dest) {
	var data = fs.readFileSync(source);	
	fs.writeFileSync(dest, data);
}