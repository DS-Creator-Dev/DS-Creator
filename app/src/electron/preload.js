const { app } = require('electron')
const contextBridge = require('electron').contextBridge;
const ipcRenderer = require('electron').ipcRenderer;
const { exec } = require('child_process');
const { dialog } = require('electron');
const fs = require('fs/promises');
const fs2 =  require("fs");


const nodePath = require("path");

const Store = require('electron-store');
const store = new Store('project');

var IsDev = true;
var PathApp;
var DefaultPath;

//Check If isDev to See Where We Need to Start Looking
if(IsDev){
    DefaultPath = __dirname + ".obj";
}
else{
    DefaultPath = __dirname;
}


// White-listed channels.
const ipc = {
    'render': {
        // From render to main.
        'send': [],
        // From main to render.
        'receive': [],
        // From render to main and back again.
        'sendReceive': [
            'getPath',
            'openEmu',
            "OpenDocs",			
            "newResourceDialog",
			"openDirectorySelectorDialog",
            'loadPNG',			
			
			"getWindowData",
			"setWindowData",
			"clearWindowData",
			"pushWindowData",
			"popWindowData",
        ]
    }
};

// Exposed protected methods in the render process.
contextBridge.exposeInMainWorld(
    // Allowed 'ipcRenderer' methods.
    'ipcRender', {
        // From render to main.
        send: (channel, args) => {
            let validChannels = ipc.render.send;
            if (validChannels.includes(channel)) {
                ipcRenderer.send(channel, args);
            }
        },
        // From main to render.
        receive: (channel, listener) => {
            let validChannels = ipc.render.receive;
            if (validChannels.includes(channel)) {
                // Deliberately strip event as it includes `sender`.
                ipcRenderer.on(channel, (event, ...args) => listener(...args));
            }
        },
        // From render to main and back again.
        invoke: (channel, args) => {
            let validChannels = ipc.render.sendReceive;
            if (validChannels.includes(channel)) {
                return ipcRenderer.invoke(channel, args);
            }
        }
    }
);


//Create Api Functions
let api = {
    //Open The CMD/Terminal
    OpenCmd: (path, isPlay) => exec(`cd ${path} && make && exit`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
            document.getElementById('Console-Text').textContent = error.message;
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
        }
        console.log(`Output: ${stdout}`);
        if(!error){
            document.getElementById('Console-Text').textContent = stdout;
        }
        if(isPlay){
            console.log("isPlay")
            ipcRenderer.invoke('openEmu')
                .then(() => {
                    localStorage.setItem('ROMPath', localStorage.getItem('ProjectDir') + "\\" + localStorage.getItem('ProjectFileName') + '.nds');
                    console.log(localStorage.getItem('ROMPath'));
                });
        }
    }),      
    //Opnes The Settings
    Settings: () => void(() => {
        console.log('Settings');
    })(),
    //Sets LocalStorage Stuff
    GetPaths: (filePath) => void(() => {
        //Sets the localStorage
        localStorage.setItem('ProjectFile', filePath);
        localStorage.setItem('ProjectDir', store.get('ProjectDir'));
        localStorage.setItem('ProjectFileName', nodePath.parse(filePath).name);
        console.log("Done Setting localStorage!");
    })(),
    //Gets The Path to The App
    GetAppPath: () => void(() => {
        PathApp = DefaultPath;

        if(IsDev){
            PathApp = nodePath.parse(PathApp).dir;
            PathApp = PathApp + ".obj";
            PathApp = nodePath.parse(PathApp).dir;
            PathApp = PathApp + "\\copy_files"
        }
        else{
            PathApp = nodePath.parse(PathApp).dir;
            PathApp = PathApp + ".obj";
            PathApp = nodePath.parse(PathApp).dir;
            PathApp = nodePath.parse(PathApp).dir;
            PathApp = PathApp + ".obj";
            PathApp = nodePath.parse(PathApp).dir;
        }
        localStorage.setItem("AppPath", `${PathApp}`)
    })(),      
    clickedDisBtn: () => void(() => {
        store.set("discordbtnclicked", "clicked")
    })(),	
	
	openNewResourceDialog: (path, title) => {		
		ipcRenderer.invoke('newResourceDialog', {"path":path})
			.then(() => {								
				console.log(`Opened dialog: ${path}`);
			});		
	}
}



//api.emulator = ...
api.project_manager = require("./preload_routines/project.js");
api.discop = require("./preload_routines/discop.js");
api.utils = require("./preload_routines/utils.js");


// between pages communications
//
// a.html : api.windowData.set("message", "some message")
//          window.location.href = "b.html"
//
// b.html : api.windowData.get("message") // === "some message"
//          api.windowData.clear()        // removes all entries
//          api.windowData.get("message") // === undefined
api.windowData = {
	get : async (field) => { 		
		let result = await ipcRenderer.invoke("getWindowData", field);
		if(result===undefined) return result;
		result = JSON.parse(result);
		return result;		
	},
	set : async (field, value) => { await ipcRenderer.invoke("setWindowData", field, JSON.stringify(value)); },
	clear : async () => { await ipcRenderer.invoke("clearWindowData"); },
	push : async(value) => { await ipcRenderer.invoke("pushWindowData", JSON.stringify(value));},
	pop : async() => {
		let result = await ipcRenderer.invoke("popWindowData");
		if(result===undefined) return result;
		result = JSON.parse(result);
		return result;		
	},
};

api.dialogs = {
	pickDirectory : () => {
		return ipcRenderer.invoke('openDirectorySelectorDialog')
	}	
};

contextBridge.exposeInMainWorld("api", api);