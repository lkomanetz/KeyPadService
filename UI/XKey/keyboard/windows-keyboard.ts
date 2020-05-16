import { IKeyboardButton } from "./keyboard-button-interface";

export class WindowsKeyboard implements IKeyboardButton {

    private _map: Map<string, string>;

    constructor() {
        this._map = this.buildMap();
    }

    getKeyName(keyCode: string): string {
        return [...this._map].find(([k, v]) => v === keyCode)[0];
    }

    toKeyCode(keyName: string): string {
        return this._map.get(keyName);
    }

    private buildMap(): Map<string, string> {
        const keyMap = new Map<string, string>();
        keyMap.set("Z", "0x5a");
        keyMap.set("X", "0x58");
        keyMap.set("Spacebar", "0x20");
        keyMap.set("Enter", "0x0D");
        keyMap.set("Left Arrow", "0x25");
        keyMap.set("Up Arrow", "0x26");
        keyMap.set("Right Arrow", "0x27");
        keyMap.set("Down Arrow", "0x28");
        return keyMap;
    }

}