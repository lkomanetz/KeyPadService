export interface IController {

    getButtonId(buttonName: string): number;
    getButtonName(buttonId: number): string;
    getButtonList(): Array<string>;

}