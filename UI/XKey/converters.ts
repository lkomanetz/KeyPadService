import { GamepadButtons } from "./key-binding";

export class GamepadButtonConverter {

    convert(buttonId: number) {
       return Object.keys(GamepadButtons).find(k => GamepadButtons[k] === buttonId);
    }

}