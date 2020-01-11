import {Waypoint} from "./waypoint";
import {Schedule} from "../react-app-env";
import {WeekDay} from "./week-day";

export class WaypointWithMeta extends Waypoint {
	public schedule: Schedule[];

	constructor(data: Partial<WaypointWithMeta>) {
		super(data);

		const daily = {
			TwentyFourHours: true,
			[WeekDay.Everyday]: true
		};
		this.schedule = this.schedule || [daily]
	}
}
