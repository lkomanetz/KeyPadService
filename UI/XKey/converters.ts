export class KeyboardCodeConverter {

    convert(keyCode: number): string {
        try {
            return String.fromCharCode(keyCode);
        }
        catch (err) {
            return "NULL";
        }
    }

}