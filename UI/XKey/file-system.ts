import * as fs from "fs";
import { KeyBinding, GamepadButtons } from "./key-binding";
import { GamepadButtonConverter } from "./converters";

export class FileSystem {

    private _buttonConverter: GamepadButtonConverter;
    private _encodingStyle: string;

    constructor(buttonConverter: GamepadButtonConverter, encodingStyle: string) {
        this._buttonConverter = buttonConverter;
        this._encodingStyle = encodingStyle;
    }

    async loadBindings(location: string): Promise<Array<KeyBinding>> {
        let bindings: Array<KeyBinding> = [];
        let data = fs.readFileSync(location, this._encodingStyle).split("\n");

        data.forEach(item => {
            let buttonInfo = item.split("=");
            let button = this._buttonConverter.convert(parseInt(buttonInfo[0]));
            bindings.push(new KeyBinding(button, parseInt(buttonInfo[1], 16)));
        });

        return bindings;
    }

}