/// <reference types="react-scripts" />

import { AnyObject } from "react-yandex-maps";

/* Payload */

interface Range<T> {
	from: T;
	to: T;
}

enum WeekDay {
	Monday = "Monday",
	Tuesday = "Tuesday",
	Thursday = "Thursday",
	Friday = "Friday",
	Saturday = "Saturday",
	Sunday = "Sunday",
	Everyday = "Everyday"
}

interface Schedule {
	Intervals?: Range<string>[];
	TwentyFourHours?: boolean;
	[key: WeekDay]: boolean;
}

interface Category {
	name: string;
	class: string;
}

interface ResponseMetaData {
	id?: string;
	name: string;
	address: string;
	url?: string;
	Categories: Category[];
	Hours: {
		text: string;
		Availabilities: Schedule[];
	};
}

interface MetroStationData {
	id: string;
	type: string;
	title: string;
	isUndergroundExit: boolean;
	undergroundLineMeta: {
		name: string;
		color: string;
	}
}

interface Rating {
	ratings: number;
	reviews: number;
	score: number;
}

interface ObjectData extends AnyObject {
	id?: string;
	name: string;
	description: string;
	type: string;
	address: string;
	boundedBy: [number, number][];
	point: [number, number];
	url?: string;
	responseMetaData: ResponseMetaData;
	rating?: Rating;
	mtrData?: MetroStationData;
}

/* Map API */

interface InfoObject {
	properties: {
		getAll() : ObjectData
	};
	map: MapApi;
}

interface IEvent {
	get(name: string) : object;
}

interface EntityEvent extends IEvent {
	originalEvent: object;
	sourceEvent: IEvent;
}

type EventCallback = (e: IEvent) => any;

interface EventManager<T extends string> {
	add(types: T | T[], callback: EventCallback) : this;
	remove(types: T | T[], callback: EventCallback) : this;
	fire(type: T, event?: EntityEvent) : this;
}

type BalloonEvents =
	"open"
	| "close"
	| "userclose"
	| "beforeuserclose";

interface BalloonApi {
	events: EventManager<BalloonEvents>;

	isOpen() : boolean;
	setData(data: InfoObject) : Promise<undefined>;
	getData() : InfoObject | null;
	getPosition() : number[] | null;
	destroy() : void;
	close(force?: boolean) : Promise<undefined>
}

type MapEvents =
	"actionbegin"
	| "actionend"
	| "actionbreak"
	| "balloonopen"
	| "balloonclose"
	| "hintopen"
	| "hintclose"
	| "contextmenu";

interface MapApi {
	events: EventManager<MapEvents>;
	balloon: BalloonApi;
}