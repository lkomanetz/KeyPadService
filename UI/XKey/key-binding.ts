export class KeyBinding {

    gamepadButton: string;
    keyboardButton: string;
    
    constructor(gamepadButton: string, keyboardButton: string) {
        this.gamepadButton = gamepadButton;
        this.keyboardButton = keyboardButton;
    }
}

export enum GamepadButtons {
    A = 0,
    B = 1,
    X = 2,
    Y = 3,
    LeftShoulder = 4,
    RightShoulder = 5,
    Back = 6,
    Menu = 7,
    Home = 8,
    LeftStick = 9,
    RightStick = 10,
    DpadRight = 11,
    DpadLeft = 12,
    DpadUp = 13,
    DpadDown = 14
}

export function getGamepadButtonList(): Array<string> {
    const buttons = [];
    for (const member in GamepadButtons) {
        const isValueProperty = parseInt(member, 10) >= 0;
        if (isValueProperty) buttons.push(GamepadButtons[member]);
    }
    return buttons;
}