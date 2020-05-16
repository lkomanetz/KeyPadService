export interface IKeyboardButton {

    getKeyName(keyCode: number): string;
    toKeyCode(keyName: string): number;

}