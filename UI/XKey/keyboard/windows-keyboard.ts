import { IKeyboardButton } from "./keyboard-button-interface";

export class WindowsKeyboard implements IKeyboardButton {

    private _map: Map<number, string>;
    private _specialChars: Map<number, string>;

    constructor() {
        this._map = this.buildMap();
        this._specialChars = this.specialCharacterSet();
    }

    getKeyName(keyCode: number): string {
        return this._specialChars.get(keyCode) ?? String.fromCharCode(keyCode).toUpperCase();
    }

    toKeyCode(keyName: string): number {
        const foundPair = [...this._map].find(([k, v]) => v === keyName);
        return (foundPair) ? foundPair[0] : -1;
    }

    private buildMap(): Map<number, string> {
        return new Map<number, string>([
            [0x5A, "Z"],
            [0x58, "X"],
            [0x20, "SPACEBAR"],
            [0x0D, "ENTER"],
            [0x25, "ARROWLEFT"],
            [0x26, "ARROWUP"],
            [0x27, "ARROWRIGHT"],
            [0x28, "ARROWDOWN"]
        ]);
    }

    private specialCharacterSet(): Map<number, string> {
        return new Map<number, string>([
            [NaN, "NULL"],
            [0x20, "SPACEBAR"],
            [0x0D, "ENTER"],
            [0x25, "ARROWLEFT"],
            [0x26, "ARROWUP"],
            [0x27, "ARROWRIGHT"],
            [0x28, "ARROWDOWN"],
            [0x09, "TAB"],
            [0x60, "NUMPAD_0"],
            [0x61, "NUMPAD_1"],
            [0x62, "NUMPAD_2"],
            [0x63, "NUMPAD_3"],
            [0x64, "NUMPAD_4"],
            [0x65, "NUMPAD_5"],
            [0x66, "NUMPAD_6"],
            [0x67, "NUMPAD_7"],
            [0x68, "NUMPAD_8"],
            [0x69, "NUMPAD_9"],
            [0xA0, "Left Shift"],
            [0xA1, "Right Shift"],
            [0xA2, "Left Control"],
            [0xA3, "Right Control"]
        ]);
    }

}