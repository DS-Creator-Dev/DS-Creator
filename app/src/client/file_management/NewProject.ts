// TODO: move to a global include definition or something
declare var api: any;

function OpenProject(): void {
  const file = api.showOpenFileDialog();
  console.log("Done")
  if(file != null){
    localStorage.setItem('path', file);
    location.href='./views/projectOpen.html'
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