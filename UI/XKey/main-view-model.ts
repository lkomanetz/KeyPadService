import * as ko from "knockout";
import { remote } from "electron";
import { FileSystem } from "./file-system";
import { IKeyboardButton } from "./keyboard";
import { KeyBinding } from "./key-binding";
import { AppInfo } from "./app-info";
import { IController } from "./controller/controller";

const dialog = remote.dialog;

class MainWindowViewModel {

    private fileSystem: FileSystem;
    private _actionName: any;
    private _keyboard: IKeyboardButton;
    private readonly _controller: IController;
    private _currentFilePath: string;

    bindings: any;

    constructor(
        fileSystem: FileSystem,
        keyboard: IKeyboardButton,
        controller: IController
    ) {
        this._controller = controller;
        this.fileSystem = fileSystem;
        this.bindings = ko.observableArray([]);
        this._keyboard = keyboard;
        this._actionName = ko.observable("");
    }

    get actionName(): any { return this._actionName(); }
    set actionName(action: any) { this._actionName(action); }

    async open(): Promise<void> {
        const filePath = await this.getFilePath();
        const bindings = await this.fileSystem.loadBindings(filePath);
        this.actionName = "update-bindings-template";
        this.bindings(bindings.map(kb => new KeyBindingViewModel(kb, this._keyboard)));
        this._currentFilePath = filePath;
    }

    createBindings() {
        let bindings: Array<KeyBinding> = [];
        for (const prop in this._controller.getButtonList()) {
            //const button = this._buttonConverter.toButtonName(parseInt(prop));
            const button = this._controller.getButtonName(parseInt(prop));
            bindings.push(new KeyBinding(button, -1));
        }
        this.actionName = "new-bindings-template";
        this.bindings(bindings.map(kb => new KeyBindingViewModel(kb, this._keyboard)));
    }

    saveBindings() {
        if (!this._currentFilePath) this._currentFilePath = dialog.showSaveDialogSync({});
        this._currentFilePath = (!this.containsFileExtension(this._currentFilePath)) ?
            this.appendFileExtensionTo(this._currentFilePath) :
            this._currentFilePath;
        this.fileSystem.saveBindings(this._currentFilePath, this.bindings().map(b => b.toContract()));
    }

    private async getFilePath(): Promise<string> {
        const result = await dialog.showOpenDialog({
            properties: ["openFile"]
        });
        return result.filePaths.length == 1 ? result.filePaths[0] : "";
    }

    private containsFileExtension(path: string): boolean {
        return path.match(/(\.\w{3}$){1}/) != null;
    }

    private appendFileExtensionTo(path: string): string {
        return path + ".txt";
    }

}

class KeyBindingViewModel {

    public keyboardCode: any;
    public gamepadButton: any;
    public keyboardButton: any;
    
    private _keyboard: IKeyboardButton;

    constructor(binding: KeyBinding, keyboard: IKeyboardButton) {
        this._keyboard = keyboard;
        this.keyboardCode = ko.observable(binding.keyboardButton);
        this.gamepadButton = ko.observable(binding.gamepadButton); 
        this.keyboardButton = ko.observable(keyboard.getKeyName(binding.keyboardButton));
    }

    updateBinding(binding:KeyBindingViewModel, evt: KeyboardEvent): void {
        const keyName = evt.key.toUpperCase().replace(/ARROW/, "");
        const keyCode = this._keyboard.toKeyCode(keyName);
        this.keyboardCode(keyCode);
        this.keyboardButton(this.getButton(evt));
        evt.preventDefault();
    }

    toContract(): KeyBinding {
        return new KeyBinding(this.gamepadButton(), this.keyboardCode());
    }

    private getButton(evt: KeyboardEvent) {
        if (evt.key === "Escape") return this._keyboard.getKeyName(-1);
        else return this._keyboard.getKeyName(evt.keyCode);
    }

}

const appInfo = new AppInfo();

ko.applyBindings(
    new MainWindowViewModel(
        new FileSystem(appInfo.controller, "utf8"),
        appInfo.keyboard,
        appInfo.controller
    )
);