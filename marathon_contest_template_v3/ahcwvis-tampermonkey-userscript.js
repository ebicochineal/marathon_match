// ==UserScript==
// @name         ahc-visualizer-outoput-json-loader
// @namespace    https://github.com/ebicochineal/marathon_match
// @version      0.1
// @description  -
// @author       ebicochineal
// @match        https://img.atcoder.jp/*
// @grant        none
// ==/UserScript==

const options = {
    types: [
        {
            description: "Text Files",
            accept: {
                "application/json": [".json"],
            },
        },
    ],
};
function outputupdate () {
    if (jf == null) { return; }
    output.value = seed.value in jf ? jf[seed.value] : "";
    updateOutput();
}
async function fileselect () {
    const [handle] = await window.showOpenFilePicker(options);
    const file = await handle.getFile();
    const text = await file.text();
    jf = JSON.parse(text);
    outputupdate();
}
var jf = null;
var seed = document.getElementById("seed");
var output = document.getElementById("output");
let btn = document.createElement("button");
btn.innerHTML = "File";
btn.addEventListener('click', fileselect);
output.parentNode.insertBefore(btn, output.previousElementSibling);
seed.addEventListener("change", outputupdate);
