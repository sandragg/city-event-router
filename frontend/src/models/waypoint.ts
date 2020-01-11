export class Waypoint {
	public id: string;
	public name: string;
	public coords: [number, number];

	constructor(data: Partial<Waypoint>) {
		this.id = data.id;
		this.name = data.name || "Point";
		this.coords = data.coords;
	}
}
