import * as ko from "knockout";
import { remote } from "electron";
import { FileSystem } from "./file-system";
import { KeyBinding, getGamepadButtonList } from "./key-binding";
import { AppInfo } from "./app-info";
import { GamepadButtonConverter } from "./converters";

const dialog = remote.dialog;

class MainWindowViewModel {

    private fileSystem: FileSystem;
    private _actionName: any;
    private _buttonConverter: GamepadButtonConverter;

    bindings: any;

    constructor(
        fileSystem: FileSystem,
        buttonConverter: GamepadButtonConverter
    ) {
        this.fileSystem = fileSystem;
        this.bindings = ko.observableArray([]);
        this._buttonConverter = buttonConverter;
        this._actionName = ko.observable("");
    }

    get actionName(): any { return this._actionName(); }
    set actionName(action: any) { this._actionName(action); }

    async open(): Promise<void> {
        const filePath = await this.getFilePath();
        const bindings = await this.fileSystem.loadBindings(filePath);
        this.actionName = "update-bindings-template";
        this.bindings(bindings.map(kb => new KeyBindingViewModel(kb)));
    }

    createBindings() {
        let bindings: Array<KeyBinding> = [];
        for (const prop in getGamepadButtonList()) {
            const button = this._buttonConverter.convert(parseInt(prop));
            bindings.push(new KeyBinding(button, -1));
        }
        this.actionName = "new-bindings-template";
        this.bindings(bindings.map(kb => new KeyBindingViewModel(kb)));
    }

    saveBindings() {
        console.log(this.bindings());
    }

    private async getFilePath(): Promise<string> {
        const result = await dialog.showOpenDialog({
            properties: ["openFile"]
        });
        return result.filePaths.length == 1 ? result.filePaths[0] : "";
    }

}

class KeyBindingViewModel {

    public keyboardCode: any;
    public gamepadButton: any;
    public keyboardButton: any;

    constructor(binding: KeyBinding) {
       this.keyboardCode = ko.observable(binding.keyboardButton);
       this.gamepadButton = ko.observable(binding.gamepadButton); 
       this.keyboardButton = ko.observable(String.fromCodePoint(binding.keyboardButton));
    }

    updateBinding(binding:KeyBindingViewModel, evt: KeyboardEvent): void {
        this.keyboardCode(evt.keyCode);
        this.keyboardButton(this.getButton(evt));
        evt.preventDefault();
    }

    toContract(): KeyBinding {
        return new KeyBinding(this.gamepadButton(), this.keyboardCode());
    }

    private getButton(evt: KeyboardEvent) {
        if (evt.keyCode === 0x20) return "Spacebar";
        return evt.key;
    }

}

const appInfo = new AppInfo();

ko.applyBindings(
    new MainWindowViewModel(
        new FileSystem(new GamepadButtonConverter(), "utf8"),
        new GamepadButtonConverter()
    )
);