import {MetroStationData, Rating, ResponseMetaData} from "../../react-app-env";

export class ObjectData {
	public id?: string;
	public name: string;
	public description: string;
	public type: string;
	public address: string;
	public boundedBy: [number, number][];
	// [ longitude, latitude ]
	public point: [number, number];
	public responseMetaData: ResponseMetaData;

	public url?: string;
	public rating?: Rating;
	public mtrData?: MetroStationData;

	constructor(data: Partial<ObjectData>) {
		Object.assign(this, data);
	}
}
