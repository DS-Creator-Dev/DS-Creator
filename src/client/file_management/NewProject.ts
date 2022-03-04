// TODO: move to a global include definition or something
declare var api: any;
declare var thing: any;

function OpenProject(): void {
  const file = api.showOpenFileDialog();
  console.log("Done")
  location.href='./views/projectOpen.html'
}

//NewProject() is no longer needed.
//Note to self. Remove these comments after this commit.

(() => {
  document.querySelector('#btn-open-project')?.addEventListener('click', () => {
    OpenProject();
  })
})()