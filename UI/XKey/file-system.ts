import * as fs from "fs";
import { KeyBinding, GamepadButtons } from "./key-binding";
import { GamepadButtonConverter } from "./converters";

export class FileSystem {

    private buttonConverter: GamepadButtonConverter;
    private encodingStyle: string;

    constructor(buttonConverter: GamepadButtonConverter, encodingStyle: string) {
        this.buttonConverter = buttonConverter;
        this.encodingStyle = encodingStyle;
    }

    async loadBindings(location: string): Promise<Array<KeyBinding>> {
        let bindings: Array<KeyBinding> = [];
        let data = fs.readFileSync(location, this.encodingStyle).split("\n");

        data.forEach(item => {
            let buttonInfo = item.split("=");
            let button = this.buttonConverter.convert(parseInt(buttonInfo[0]));
            let mappedKey = buttonInfo[1];
            bindings.push(new KeyBinding(button, mappedKey));
        });

        return bindings;
    }

}