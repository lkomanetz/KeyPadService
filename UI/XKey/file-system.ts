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

    loadBindings(location: string): Promise<Array<KeyBinding>> {
        let bindings: Array<KeyBinding> = [];
        let data = fs.readFileSync(location, this._encodingStyle).split("\n");

        data.forEach(item => {
            let buttonInfo = item.split("=");
            let button = this._buttonConverter.convert(parseInt(buttonInfo[0]));
            bindings.push(new KeyBinding(button, parseInt(buttonInfo[1], 16)));
        });

        return Promise.resolve(bindings);
    }

    saveBindings(location: string, bindings: Array<KeyBinding>): Promise<void> {
        const fileContents = bindings
            .map(kb => `${kb.gamepadButton}=${kb.keyboardButton}`)
            .join("\n");
        
        fs.writeFile(location, fileContents, { encoding: "utf8" }, e => {});
        return Promise.resolve();
    }

}