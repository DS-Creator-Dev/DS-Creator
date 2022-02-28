// TODO: move to a global include definition or something
declare var api: any;
declare var thing: any;

function OpenProject(): void {
  const files = api.showOpenFileDialog();
  console.log("Done")
}
function NewProject(): void{
  //Sending the logs but not doing the api function
  //Api function in preload.ts/preload.js
  console.log("Before")
  api.NewProject();
  console.log("After")
}

(() => {
  document.querySelector('#btn-open-project')?.addEventListener('click', () => {
    OpenProject();
  })
  document.querySelector('#btn-new-project')?.addEventListener('click', () => {
    NewProject();
  })
})()