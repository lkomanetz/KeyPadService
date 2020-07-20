export class KeyBinding {

    gamepadButton: string;
    keyboardButton: number;
    
    constructor(gamepadButton: string, keyboardButton: number) {
        this.gamepadButton = gamepadButton;
        this.keyboardButton = keyboardButton;
    }
}
