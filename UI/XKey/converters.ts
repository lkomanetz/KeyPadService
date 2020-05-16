import { GamepadButtons } from "./key-binding";

export class GamepadButtonConverter {

    convert(buttonId) {
       return Object.keys(GamepadButtons).find(k => GamepadButtons[k] === buttonId);
    }

}

// module.exports = { GamepadButtonConverter };