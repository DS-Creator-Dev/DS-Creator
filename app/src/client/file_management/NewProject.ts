// TODO: move to a global include definition or something
declare var api: any;

function OpenProject(): void {
  const file = api.showOpenFileDialog();
  const filedir = api.showOpenDirDialog(file);
  console.log("Done")
  if(file != null){
    if(filedir != null){
      localStorage.setItem('ProjectPath', file);
      localStorage.setItem('DirPath', filedir);
      location.href='./views/projectOpen.html'
    }
  }
}



(() => {
  document.querySelector('#btn-open-project')?.addEventListener('click', () => {
    OpenProject();
  }),
  document.querySelector('#btn-new-project')?.addEventListener('click', () => {
    location.href='./views/projectNew.html'
  })
})()