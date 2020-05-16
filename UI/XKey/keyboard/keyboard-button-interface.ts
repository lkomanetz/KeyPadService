export interface IKeyboardButton {

    getKeyName(keyCode: string): string;
    toKeyCode(keyName: string): string;

}