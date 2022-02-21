"use strict";
const { dialog } = require('electron');
//console.log(dialog.showOpenDialog({ properties: ['openFile', 'multiSelections'] }))
function NewProject() {
    const files = dialog.showOpenDialogSync({
        properties: ["openFile"],
        filters: [
            {
                name: "Projects",
                extensions: ["DSCProj"],
            },
        ],
    });
    console.log("Done");
}
