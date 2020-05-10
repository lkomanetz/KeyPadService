const { GamepadButtons } = require("./key-binding");

class GamepadButtonConverter {

    convert(buttonId) {
       return Object.keys(GamepadButtons).find(k => GamepadButtons[k] === buttonId);
    }

}

module.exports = { GamepadButtonConverter };