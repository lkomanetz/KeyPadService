const { app, BrowserWindow } = require("electron");
const { ko } = require("knockout");

function createWindow() {
    const window = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true
        }
    });
    window.loadFile("main.html");
}

app.whenReady().then(createWindow);