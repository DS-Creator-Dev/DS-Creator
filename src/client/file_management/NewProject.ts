<<<<<<< Updated upstream
import { textChangeRangeIsUnchanged } from "typescript";

const { contextBridge, ipcRenderer } = require('electron')
=======
>>>>>>> Stashed changes

// TODO: move to a global include definition or something
declare var api: any;

function OpenProject(): void {
  const files = api.showOpenFileDialog();
<<<<<<< Updated upstream
  console.log("Done")
}
function NewProject(): void {
  
  console.log("Done")
=======
  console.log("Done")
  if(files != null){
    location.href='./views/projectOpen.html'
  }
>>>>>>> Stashed changes
}

(() => {
  //TODO: After a file is chosen, open the file and read contents. Then use the contents to know how many scenes, and what is on those scenes.
  document.querySelector('#btn-open-project')?.addEventListener('click', () => {
    OpenProject();
  })
<<<<<<< Updated upstream
  //Go to projectNew.html
  document.querySelector('#btn-new-project')?.addEventListener('click', () => {
    NewProject();
  });
=======
>>>>>>> Stashed changes
})()
