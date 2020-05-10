class KeyBinding {
    
    constructor(gamepadButton, keyboardButton) {
        this.gamepadButton = gamepadButton;
        this.keyboardButton = keyboardButton;
    }
}

const GamepadButtons = Object.freeze({
    A: 0,
    B: 1,
    X: 2,
    Y: 3,
    LeftShoulder: 4,
    RightShoulder: 5,
    Back: 6,
    Menu: 7,
    Home: 8,
    LeftStick: 9,
    RightStick: 10,
    DpadRight: 11,
    DpadLeft: 12,
    DpadUp: 13,
    DpadDown: 14
});

module.exports = { KeyBinding, GamepadButtons };