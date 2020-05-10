const ko = require("knockout");
const FileSystem = require("./file-system");
const { GamepadButtons, KeyBinding } = require("./key-binding");
const { GamepadButtonConverter } = require("./converters");

class MainWindowViewModel {

    constructor(fileSystem) {
        this.fileSystem = fileSystem;
        this.bindings = ko.observableArray([]);
    }

    async open() {
        const bindings = await this.fileSystem.loadBindings();
        this.bindings(bindings);
    }

    createBindings() {
        let bindings = [];
        for (const prop in GamepadButtons) {
            bindings.push(new KeyBinding(prop, "NULL"));
        }
        this.bindings(bindings);
    }

}

ko.applyBindings(new MainWindowViewModel(new FileSystem(new GamepadButtonConverter(), "utf8")));