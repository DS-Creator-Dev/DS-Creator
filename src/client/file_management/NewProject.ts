// TODO: move to a global include definition or something
declare var api: any;

function OpenProject(): void {
  const files = api.showOpenFileDialog();
  console.log("Done")
  if(files != null){
    location.href='./views/projectOpen.html'
  }
}

(() => {
  //TODO: After a file is chosen, open the file and read contents. Then use the contents to know how many scenes, and what is on those scenes.
  document.querySelector('#btn-open-project')?.addEventListener('click', () => {
    OpenProject();
  })
})()
