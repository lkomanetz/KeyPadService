import { IKeyboardButton } from "./keyboard/keyboard-button-interface";
import { WindowsKeyboard, EmptyKeyboard } from "./keyboard";

export class AppInfo {
    private _keyboard: IKeyboardButton;

    constructor() {
        switch (process.platform) {
            case "darwin": 
            case "linux":
                this._keyboard = new EmptyKeyboard();
                break;
            default: this._keyboard = new WindowsKeyboard();
        }
    }

    get keyboard(): IKeyboardButton { return this._keyboard; }

}