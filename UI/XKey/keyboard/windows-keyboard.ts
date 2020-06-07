import { IKeyboardButton } from "./keyboard-button-interface";
import { remote, ClientRequest } from "electron";

export class WindowsKeyboard implements IKeyboardButton {

    private _characterMap: Map<number, string>;

    constructor() {
        this._characterMap = new Map<number, string>();
        this.buildCharacterSetAsync()
            .then(chars => this._characterMap = chars);
    }

    getKeyName(keyCode: number): string {
        return this._characterMap.get(keyCode) ?? String.fromCharCode(keyCode).toUpperCase();
    }

    // TODO(Logan) -> Figure out why special keys end up as NULL
    toKeyCode(keyName: string): number {
        const alphaNumericResult = keyName.match(/^[A-Za-z0-9]{1}$/);
        if (alphaNumericResult) return keyName.charCodeAt(0);
        const foundPair = [...this._characterMap].find(([k, v]) => v === keyName);
        return (foundPair) ? foundPair[0] : -1;
    }

    private isInvalidKeyCode(elementCollection: HTMLCollectionOf<HTMLElement>): boolean {
        return (
            !elementCollection ||
            elementCollection[0].innerText === "" ||
            elementCollection[0].innerText.length === 1 ||
            elementCollection[0].innerText.includes("Minimum") ||
            elementCollection[0].innerText.includes("Header") ||
            elementCollection[0].innerText.includes("Winuser")
        );
    }

    private buildCharacterSetAsync(): Promise<Map<number, string>> {
        return new Promise((resolve, reject) => {
            let specialChars = new Map<number, string>();
            
            const textDecoder = new TextDecoder("utf-8");
            const domParser = new DOMParser();
            const url = "https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes";
            const request = remote.net.request(url);
            request.on("response", r => {
                r.on("end", () => resolve(specialChars));
                r.on("data", chunk => {
                    const html = domParser.parseFromString(textDecoder.decode(chunk), "text/html");
                    const keyCodes = html.getElementsByTagName("dl");
                    for (let i = 0; i < keyCodes.length; ++i) {
                        const dt = keyCodes[i].getElementsByTagName("dt");
                        if (this.isInvalidKeyCode(dt)) continue;
                        const isVirtualKey = dt[0].innerText.includes("VK_");
                        const keyText = (isVirtualKey) ? dt[0].innerText.substring(dt[0].innerText.indexOf("_") + 1) : dt[0].innerText;
                        const keyCode = parseInt(dt[1].innerText, 16);

                        if (keyText === "ESCAPE") specialChars.set(-1, "NULL");
                        else specialChars.set(keyCode, keyText);
                    }
                });
            });
            request.end();
        });
    }

}