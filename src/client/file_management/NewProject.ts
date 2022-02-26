import { textChangeRangeIsUnchanged } from "typescript";

const { contextBridge, ipcRenderer } = require('electron')

// TODO: move to a global include definition or something
declare var api: any;

function OpenProject(): void {
  const files = api.showOpenFileDialog();
  console.log("Done")
}
function NewProject(): void {
  
  console.log("Done")
}

(() => {
  //TODO: After a file is chosen, open the file and read contents. Then use the contents to know how many scenes, and what is on those scenes.
  document.querySelector('#btn-open-project')?.addEventListener('click', () => {
    OpenProject();
  })
  //Go to projectNew.html
  document.querySelector('#btn-new-project')?.addEventListener('click', () => {
    NewProject();
  });
})()
