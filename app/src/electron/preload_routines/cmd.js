const { exec, execSync } = require('child_process');

https://stackoverflow.com/questions/41037042/nodejs-wait-for-exec-in-function

function execCommand(cmd, attributes) {
	return new Promise((resolve, reject)=> {
		exec(cmd, attributes, (error, stdout, stderr) => {
		var __result = {
			"error": error,
			"stdout": stdout,
			"stderr": stderr
		}		             
		resolve(__result)
	   });
   })
}

module.exports.make = async function(path) {	
	return await execCommand('make', {cwd: path});
}