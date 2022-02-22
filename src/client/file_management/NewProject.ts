// TODO: move to a global include definition or something
declare var api: any;

function NewProject(): void {
  const files = api.showOpenFileDialog();
  console.log("Done")
}

(() => {
  document.querySelector('#btn-open-project')?.addEventListener('click', () => {
    NewProject();
  })
})()