import * as fs from "fs";
import { KeyBinding, GamepadButtons } from "./key-binding";
import { GamepadButtonConverter } from "./converters";
import { IKeyboardButton } from "./keyboard";

export class FileSystem {

    private _buttonConverter: GamepadButtonConverter;
    private _encodingStyle: string;
    private _keyboard: IKeyboardButton;

    constructor(buttonConverter: GamepadButtonConverter, encodingStyle: string, keyboard: IKeyboardButton) {
        this._buttonConverter = buttonConverter;
        this._encodingStyle = encodingStyle;
        this._keyboard = keyboard;
    }

    async loadBindings(location: string): Promise<Array<KeyBinding>> {
        let bindings: Array<KeyBinding> = [];
        let data = fs.readFileSync(location, this._encodingStyle).split("\n");

        data.forEach(item => {
            let buttonInfo = item.split("=");
            let button = this._buttonConverter.convert(parseInt(buttonInfo[0]));
            let mappedKey = this._keyboard.getKeyName(parseInt(buttonInfo[1], 16)); // I need to remove \n char
            bindings.push(new KeyBinding(button, mappedKey));
        });

        return bindings;
    }

}