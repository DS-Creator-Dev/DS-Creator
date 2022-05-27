const { app } = require('electron')
const contextBridge = require('electron').contextBridge;
const ipcRenderer = require('electron').ipcRenderer;
const { exec } = require('child_process');
//const { remote } = require('electron').remote;
const { dialog } = require('electron');
const fs = require('fs/promises');
const remote_1 = require('@electron/remote');

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
            'openEmu'
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
contextBridge.exposeInMainWorld("api", {
    //Open The CMD/Terminal
    OpenCmd: (path, isPlay) => exec(`cd ${path} && make && exit`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
            document.getElementById('Console-Text').textContent = error.message;
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
            return;
        }
        console.log(`Output: ${stdout}`);
        if(!error){
            document.getElementById('Console-Text').textContent = stdout;
        }
        if(isPlay){
            ipcRenderer.invoke('openEmu')
                .then((ROM) => {
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
        }
        else{
            PathApp = nodePath.parse(PathApp).dir;
            PathApp = PathApp + ".obj";
            PathApp = nodePath.parse(PathApp).dir;
            PathApp = nodePath.parse(PathApp).dir;
            PathApp = PathApp + ".obj";
            PathApp = nodePath.parse(PathApp).dir;
        }
        localStorage.setItem("SoundBank", `${PathApp}`)
    })(),
    //Makes A Blank Project
    MakeBlankProject: (ProName, ProPath, MakefileText, MainCText, SoundbankBinHText, SoundbankHText) => exec(`cd ${ProPath}\\ && mkdir ${ProName} && cd ${ProName} && mkdir art && mkdir src && mkdir include && mkdir sound && mkdir data && mkdir build && exit`, (error, stdout, stderr) => {
        if (error) {
            confirm(`Error: There was an error making your project. This is most likely due to a misspelling in the Project Path.\n Close DS Creator.`);
            console.log(`error: ${error.message}`);
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
        }
        console.log(`Output: ${stdout}`);
        if(!error){
            var Path = ProPath + '\\' + ProName;
            CreateBlankProjFiles(Path, MakefileText, MainCText, ProName, SoundbankBinHText, SoundbankHText);
        }
    })
});

//Creates Blank Project Files
function CreateBlankProjFiles(CdPath, MakefileText, MainCText, Name, SoundbankBinHText, SoundbankHText){
    let ProjectFileErr = false;
    fs.writeFile(`${CdPath}\\Makefile`, MakefileText, err => {
        if(err){
            confirm("Error: Error Making Makefile.\n Close DS Creator.");
        }
    });
    fs.writeFile(`${CdPath}\\src\\main.c`, MainCText, err => {
        if(err){
            confirm("Error: Error Making main.c.\n Close DS Creator.");
        }
    });
    fs.writeFile(`${CdPath}\\${Name}.DSCProj`, MainCText, err => {
        if(err){
            confirm(`Error: Error Making ${Name}.DSCProj.\n Close DS Creator.`);
            ProjectFileErr = true;
        }
    });
    fs.writeFile(`${CdPath}\\build\\soundbank_bin.h`, SoundbankHText, err => {
        if(err){
            confirm("Error: Error Making soundbank_bin.h.\n Close DS Creator.");
            ProjectFileErr = true;
        }
    });
    fs.writeFile(`${CdPath}\\build\\soundbank.h`, SoundbankBinHText, err => {
        if(err){
            confirm("Error: Error Making soundbank.h.\n Close DS Creator.");
            ProjectFileErr = true;
        }
    });
    fs.copyFile(`${localStorage.getItem("SoundBank")}\\soundbank.bin`, `${CdPath}\\build\\soundbank.bin`);
    fs.copyFile(`${localStorage.getItem("SoundBank")}\\events.dll`, `${CdPath}\\include\\events.c`);
    
    if(ProjectFileErr == false){
        localStorage.setItem('ProjectFile', `${CdPath}\\${Name}.DSCProj`);
        localStorage.setItem('ProjectDir', `${CdPath}`);
        localStorage.setItem('ProjectFileName', `${Name}`);
        location.href = './projectOpen.html';
    }
}