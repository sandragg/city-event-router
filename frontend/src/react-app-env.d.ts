/// <reference types="react-scripts" />

import { AnyObject } from "react-yandex-maps";

interface ObjectData extends AnyObject {}

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