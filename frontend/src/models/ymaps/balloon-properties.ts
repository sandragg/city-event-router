import {ObjectData} from "./object-data";

export class BalloonProperties {
	private objectData: ObjectData | object;

	constructor(data: ObjectData) {
		this.setAll(data || {});
	}

	public get(key: string) {
		return this.objectData[key];
	}

	public getAll() {
		return this.objectData as ObjectData;
	}

	public setAll(value: ObjectData | object) {
		return this.objectData = value;
	}

	public unsetAll() {
		return this.objectData = {} as ObjectData;
	}
}
