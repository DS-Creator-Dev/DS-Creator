(() => {
    document.querySelector('#CompileButton') ?. addEventListener('click', () => {
        OpenCmd();
    })
})()

function OpenCmd(): void {
    const { exec } = require('child_process');

    let commandOne = "start cmd.exe";
    let commandTwo = "cd 'E:/Repos/DS-Creator/DSTest/AutorunnerTests/A_Autorunner'";
    let commandThree = "make";

    exec(`${commandOne} && ${commandTwo} && ${commandThree}`, (error : any, stdout : any, stderr : any) => {
        if (error) {
            console.log(`error: ${
                error.message
            }`);
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
            return;
        }
        console.log(`Output: ${stdout}`);
    });
}
