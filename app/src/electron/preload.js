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
            'loadPNG',			
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
    //Saves The Project
    SaveProject: () => void(() => {
        localStorage.setItem('Contents', "No");
        console.log("\nFile Contents of file before append:",
        fs.readFile(localStorage.getItem('ProjectFile'), "utf8"));
  
        fs.appendFile(localStorage.getItem('ProjectFile'), "World", (err) => {
        if (err) {
            console.log(err);
        }
        else {
            console.log("\nFile Contents of file after append:",
            fs.readFile(localStorage.getItem('ProjectFile'), "utf8"));
        }
    });
    })(),
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
    //Makes A Blank Project
    MakeBlankProject: (ProName, ProPath) => void(() => {
        CreateBlankProjFiles(ProPath, ProName);
    })(),	
    LoadEvents: () => void(() => {
        fs.readdir(`${nodePath.parse(localStorage.getItem("AppPath")).dir}\\Events`, (err, files) => {
            //confirm(files);
            localStorage.removeItem("Events");
            localStorage.setItem("Events", JSON.stringify(files));
            console.log(files);
        })
    })(),
    LoadMusicAndSfx: () => void(() => {
        var mods = fs2.readdirSync(`${localStorage.getItem('ProjectDir')}\\audio`).filter(f=> f.endsWith(".mod"));
        var wavs = fs2.readdirSync(`${localStorage.getItem('ProjectDir')}\\audio`).filter(f=> f.endsWith(".wav"));
        localStorage.setItem(".MODs",  JSON.stringify(mods));
        localStorage.setItem(".WAVs",  JSON.stringify(wavs));

        var backrounds = fs2.readdirSync(`${localStorage.getItem('ProjectDir')}\\backgrounds`).filter(f=> f.endsWith(".png"));
        var sprites = fs2.readdirSync(`${localStorage.getItem('ProjectDir')}\\sprites`).filter(f=> f.endsWith(".png"));
        localStorage.setItem("Backgrounds",  JSON.stringify(backrounds));
        localStorage.setItem("Sprites",  JSON.stringify(sprites));

        console.log(mods);
        console.log(wavs);
        console.log(backrounds);
        console.log(sprites);
    })(),
    clickedDisBtn: () => void(() => {
        store.set("discordbtnclicked", "clicked")
    })(),
	
	
	readFile: (filename) => {
		const data = fs2.readFileSync(filename);
		return data;
	},	
	readTextFile: (filename) => {
		const data = fs2.readFileSync(filename, 'utf8');
		return data;
	},
	
	openNewResourceDialog: (path, title) => {		
		ipcRenderer.invoke('newResourceDialog', {"path":path})
			.then(() => {								
				console.log(`Opened dialog: ${path}`);
			});		
	}
}

//Creates Blank Project Files
function CreateBlankProjFiles(CdPath, Name){

    exec(`cd ${CdPath}\\ && mkdir ${Name} && cd ${Name} && mkdir sprites && mkdir backgrounds && mkdir source && mkdir include && mkdir audio && mkdir data && exit`, (error, stdout, stderr) => {
        if (error) {
            confirm(`Error: There was an error making your project. This is most likely due to a misspelling in the Project Path.\n Close DS Creator.`);
            console.log(`error: ${error.message}`);
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
        }
        console.log(`Output: ${stdout}`);
        if(!error){
            CdPath = CdPath + "\\" + Name;

            fs.copyFile(`${localStorage.getItem("AppPath")}\\Makefile.bin`, `${CdPath}\\Makefile`);
            fs.writeFile(`${CdPath}\\${Name}.DSCProj`, "");
            fs.copyFile(`${localStorage.getItem("AppPath")}\\events.dll`, `${CdPath}\\include\\events.c`);
            fs.copyFile(`${localStorage.getItem("AppPath")}\\main.dll`, `${CdPath}\\source\\main.c`);
                
            localStorage.setItem('ProjectFile', `${CdPath}\\${Name}.DSCProj`);
            localStorage.setItem('ProjectDir', `${CdPath}`);
            localStorage.setItem('ProjectFileName', `${Name}`);
            location.href = './Engine.html';
        }
    })
}

//api.emulator = ...
api.project_manager = require("./preload_routines/project.js");
api.discop = require("./preload_routines/discop.js");

contextBridge.exposeInMainWorld("api", api);