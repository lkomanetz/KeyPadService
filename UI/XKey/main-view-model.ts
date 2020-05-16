import * as ko from "knockout";
import { remote } from "electron";
import { FileSystem } from "./file-system";
import { GamepadButtons, KeyBinding, getGamepadButtonList } from "./key-binding";
import { AppInfo } from "./app-info";
import { GamepadButtonConverter } from "./converters";
import { IKeyboardButton } from "./keyboard";

const dialog = remote.dialog;

class MainWindowViewModel {

    private fileSystem: FileSystem;
    private _actionName: any;
    private _buttonConverter: GamepadButtonConverter;
    private _keyboard: IKeyboardButton;

    bindings: any;

    constructor(
        fileSystem: FileSystem,
        buttonConverter: GamepadButtonConverter,
        keyboard: IKeyboardButton
    ) {
        this._keyboard = keyboard;
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
        this.bindings(bindings.map(kb => new KeyBindingViewModel(kb, this._keyboard)));
    }

    createBindings() {
        let bindings: Array<KeyBinding> = [];
        for (const prop in getGamepadButtonList()) {
            const button = this._buttonConverter.convert(parseInt(prop));
            bindings.push(new KeyBinding(button, "NULL"));
        }
        this.actionName = "new-bindings-template";
        this.bindings(bindings.map(kb => new KeyBindingViewModel(kb, this._keyboard)));
    }

    private async getFilePath(): Promise<string> {
        const result = await dialog.showOpenDialog({
            properties: ["openFile"]
        });
        return result.filePaths.length == 1 ? result.filePaths[0] : "";
    }

}

class KeyBindingViewModel {

    private readonly _keyboard: IKeyboardButton;

    public keyboardButton: any;
    public gamepadButton: any;

    constructor(binding: KeyBinding, keyboard: IKeyboardButton) {
       this.keyboardButton = ko.observable(binding.keyboardButton);
       this.gamepadButton = ko.observable(binding.gamepadButton); 
       this._keyboard = keyboard;
    }

    updateBinding(binding:KeyBindingViewModel, evt: KeyboardEvent): void {
        const key: string = this._keyboard.getKeyName(evt.keyCode);
        this.keyboardButton(key);
    }
}

const appInfo = new AppInfo();

ko.applyBindings(
    new MainWindowViewModel(
        new FileSystem(new GamepadButtonConverter(), "utf8", appInfo.keyboard),
        new GamepadButtonConverter(),
        appInfo.keyboard
    )
);