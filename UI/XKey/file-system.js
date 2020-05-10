const fs = require("fs");
const { dialog } = require("electron").remote;
const { KeyBinding, GamepadButtons } = require("./key-binding");
const { GamepadButtonConverter } = require("./converters");

class FileSystem {

    constructor(buttonConverter, encodingStyle) {
        this.buttonConverter = buttonConverter;
        this.encodingStyle = encodingStyle;
    }

    async loadBindings(location) {
        const result = await dialog.showOpenDialog({
            properties: ["openFile"]
        });

        if (result.filePaths.length === 0) return [];
        let bindings = [];
        let data = fs.readFileSync(result.filePaths[0], this.encodingStyle).split("\n");

        data.forEach(item => {
            let buttonInfo = item.split("=");
            let button = this.buttonConverter.convert(parseInt(buttonInfo[0]));
            let mappedKey = buttonInfo[1];
            bindings.push(new KeyBinding(button, mappedKey));
        });

        return bindings;
    }

}

module.exports = FileSystem;