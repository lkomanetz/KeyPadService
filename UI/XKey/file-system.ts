import * as fs from "fs";
import { KeyBinding } from "./key-binding";
import { IController } from "./controller/controller";

export class FileSystem {

    private readonly _controller: IController;
    private _encodingStyle: string;

    constructor(controller: IController, encodingStyle: string) {
        this._controller = controller;
        this._encodingStyle = encodingStyle;
    }

    loadBindings(location: string): Promise<Array<KeyBinding>> {
        return new Promise<Array<KeyBinding>>((resolve, reject) => {
            let bindings: Array<KeyBinding> = [];
            let data = fs.readFileSync(location, this._encodingStyle).split("\n");

            data.forEach(item => {
                let buttonInfo = item.split("=");
                let button = this._controller.getButtonName(parseInt(buttonInfo[0]));
                const keyCode = (buttonInfo[1].trim() === "NULL") ? -1 : parseInt(buttonInfo[1], 16);
                bindings.push(new KeyBinding(button, keyCode));
            });
            resolve(bindings);
        });
    }

    saveBindings(location: string, bindings: Array<KeyBinding>): Promise<void> {
        return new Promise((resolve, reject) => {
            try {
                const fileContents = bindings
                    .map(b => this.toOutputString(b))
                    .join("\n");
                
                fs.writeFileSync(location, fileContents, { encoding: "utf8"});
                resolve();
            }
            catch (err) {
                reject(err);
            }
        });
    }

    private toOutputString(binding: KeyBinding): string {
        const toHex = (n: number) => n.toString(16).toUpperCase();
        const buttonId = this._controller.getButtonId(binding.gamepadButton);
        return `${buttonId}=${binding.keyboardButton === -1 ? 'NULL' : toHex(binding.keyboardButton)}`;
    }

}