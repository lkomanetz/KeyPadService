import { IKeyboardButton } from "./keyboard-button-interface";

export class WindowsKeyboard implements IKeyboardButton {

    private _map: Map<number, string>;

    constructor() {
        this._map = this.buildMap();
    }

    getKeyName(keyCode: number): string {
        return this._map.get(keyCode) ?? "NULL";
    }

    toKeyCode(keyName: string): number {
        const foundPair = [...this._map].find(([k, v]) => v === keyName);
        return (foundPair) ? foundPair[0] : -1;
    }

    private buildMap(): Map<number, string> {
        return new Map<number, string>([
            [0x5A, "Z"],
            [0x58, "X"],
            [0x20, "Spacebar"],
            [0x0D, "Enter"],
            [0x25, "Left Arrow"],
            [0x26, "Up Arrow"],
            [0x27, "Right Arrow"],
            [0x28, "Down Arrow"]
        ]);
    }

}