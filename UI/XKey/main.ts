import { BrowserWindow } from "electron";

export default class Main {
    static mainWindow: BrowserWindow;
    static app: Electron.App;
    static browserWindow;

    private static onWindowAllClosed(): void {
        if (process.platform !== "darwin") Main.app.quit();
    }

    private static onClose(): void {
        Main.mainWindow = null;
    }

    private static onReady(): void {
        Main.mainWindow = new BrowserWindow({
            width: 800,
            height: 600,
            webPreferences: {
                nodeIntegration: true
            }
        });
        Main.mainWindow.loadFile("main.html");
        Main.mainWindow.on("closed", Main.onClose);
    }

    static main(app: Electron.App, browserWindow: typeof BrowserWindow) {
        Main.browserWindow = browserWindow;
        Main.app = app;
        Main.app.on("window-all-closed", Main.onWindowAllClosed);
        Main.app.on("ready", Main.onReady);
    }

}