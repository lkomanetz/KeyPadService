import { GamepadButtons } from "./key-binding";

export class GamepadButtonConverter {

    convert(buttonId: number) {
       return Object.keys(GamepadButtons).find(k => GamepadButtons[k] === buttonId);
    }

}

export class KeyboardCodeConverter {

    convert(keyCode: number): string {
        try {
            return String.fromCharCode(keyCode);
        }
        catch (err) {
            return "NULL";
        }
    }

}