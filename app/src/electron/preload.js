// Import the necessary Electron components.
const contextBridge = require('electron').contextBridge;
const ipcRenderer = require('electron').ipcRenderer;
const { exec } = require('child_process');
const { dialog } = require('electron');
const fs = require('fs/promises');
const remote_1 = require('@electron/remote');

// White-listed channels.
const ipc = {
    'render': {
        // From render to main.
        'send': [],
        // From main to render.
        'receive': [],
        // From render to main and back again.
        'sendReceive': [
            'getPath'
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

contextBridge.exposeInMainWorld("api", {
    OpenCmd: (path) => exec(`cd ${path} && make && exit`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
            document.getElementById('Console-Text').textContent = error.message;
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
            //document.getElementById('Console-Text').textContent = stderr;
            return;
        }
        console.log(`Output: ${stdout}`);
        if(!error){
            document.getElementById('Console-Text').textContent = stdout;
        }
    }),
    SaveProject: () => void(() => {
        localStorage.setItem('Contents', "No");
        fs.writeFile(localStorage.getItem('ProjectFile'), localStorage.getItem('Contents'), (err) => {
            if(err){
                console.log("Error:" + err.message)
                return
            }

            alert("File Saved");
        });
    })(),
    PlayGame: () => void(() => {
        console.log('Playing');
    })(),
    Settings: () => void(() => {
        console.log('Settings');
    })()
});