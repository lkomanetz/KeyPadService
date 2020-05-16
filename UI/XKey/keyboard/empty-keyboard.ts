import { IKeyboardButton } from "./keyboard-button-interface";

export class EmptyKeyboard implements IKeyboardButton {

    getKeyName(keyCode: number): string {
        throw new Error("Method not implemented.");
    }

    toKeyCode(keyName: string): number {
        throw new Error("Method not implemented.");
    }

}