import { GamepadButtons } from "./key-binding";

export class GamepadButtonConverter {

    toButtonName(buttonId: number) {
       return Object.keys(GamepadButtons).find(k => GamepadButtons[k] === buttonId);
    }

    toButtonId(buttonName: string): number {
       const enumVal = Object.values(GamepadButtons).find(name => name === buttonName);
       return GamepadButtons[enumVal];
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