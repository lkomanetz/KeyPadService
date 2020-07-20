import { IController } from "./controller";

export class XboxController implements IController {

    private _buttonMap: Map<number, string>;

    constructor() {
        this._buttonMap = this.buildButtonMap();
    }

    public getButtonId(buttonName: string): number {
        for (const [key, value] of this._buttonMap) {
            if (value === buttonName.toUpperCase()) return key;
        }
        return -1;
    }

    public getButtonName(buttonId: number): string {
        return this._buttonMap.get(buttonId);
    }

    public getButtonList(): Array<string> {
        const buttonCollection = [];
        for (const [_, value] of this._buttonMap) buttonCollection.push(value);
        return buttonCollection;
    }

    private buildButtonMap(): Map<number, string> {
        const buttonMap = new Map<number, string>();
        buttonMap.set(0, "A");
        buttonMap.set(1, "B");
        buttonMap.set(2, "X");
        buttonMap.set(3, "Y");
        buttonMap.set(4, "LeftShoulder");
        buttonMap.set(5, "RightShoulder");
        buttonMap.set(6, "Back");
        buttonMap.set(7, "Menu");
        buttonMap.set(8, "Home");
        buttonMap.set(9, "LeftStick");
        buttonMap.set(10, "RightStick");
        buttonMap.set(11, "DpadRight");
        buttonMap.set(12, "DpadLeft");
        buttonMap.set(13, "DpadUp");
        buttonMap.set(14, "DpadDown");
        return buttonMap;
    }

}