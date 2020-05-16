import * as ko from "knockout";
import { remote } from "electron";
import { FileSystem } from "./file-system";
import { GamepadButtons, KeyBinding} from "./key-binding";
import { GamepadButtonConverter } from "./converters";

const dialog = remote.dialog;

class MainWindowViewModel {

    private fileSystem: FileSystem;
    private bindings: any;
    private _actionName: any;

    constructor(fileSystem: FileSystem) {
        this.fileSystem = fileSystem;
        this.bindings = ko.observableArray([]);
        this._actionName = ko.observable("");
    }

    get actionName(): any { return this._actionName(); }
    set actionName(action: any) { this._actionName(action); }

    async open(): Promise<void> {
        const filePath = await this.getFilePath();
        const bindings = await this.fileSystem.loadBindings(filePath);
        this.actionName = "update-bindings-template";
        this.bindings(bindings);
    }

    private async getFilePath(): Promise<string> {
        const result = await dialog.showOpenDialog({
            properties: ["openFile"]
        });
        return result.filePaths.length == 1 ? result.filePaths[0] : "";
    }

    createBindings() {
        let bindings = [];
        for (const prop in GamepadButtons) {
            bindings.push(new KeyBinding(prop, "NULL"));
        }
        this.actionName = "new-bindings-template";
        this.bindings(bindings);
    }

}

ko.applyBindings(new MainWindowViewModel(new FileSystem(new GamepadButtonConverter(), "utf8")));