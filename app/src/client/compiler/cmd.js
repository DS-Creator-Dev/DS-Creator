"use strict";
(() => {
    var _a;
    (_a = document.querySelector('#CompileButton')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        OpenCmd();
    });
})();
function OpenCmd() {
    const { exec } = require('child_process');
    let commandOne = "start cmd.exe";
    let commandTwo = "cd 'E:/Repos/DS-Creator/DSTest/AutorunnerTests/A_Autorunner'";
    let commandThree = "make";
    exec(`${commandOne} && ${commandTwo} && ${commandThree}`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
            return;
        }
        console.log(`Output: ${stdout}`);
    });
}
