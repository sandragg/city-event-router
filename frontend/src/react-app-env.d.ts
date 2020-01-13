/// <reference types="node" />
/// <reference types="react" />
/// <reference types="react-dom" />

declare namespace NodeJS {
  interface ProcessEnv {
    readonly NODE_ENV: 'development' | 'production' | 'test';
    readonly PUBLIC_URL: string;
  }
}

declare module '*.bmp' {
  const src: string;
  export default src;
}

declare module '*.gif' {
  const src: string;
  export default src;
}

declare module '*.jpg' {
  const src: string;
  export default src;
}

declare module '*.jpeg' {
  const src: string;
  export default src;
}

declare module '*.png' {
  const src: string;
  export default src;
}

declare module '*.webp' {
    const src: string;
    export default src;
}

declare module '*.svg' {
  import * as React from 'react';

  export const ReactComponent: React.FunctionComponent<React.SVGProps<SVGSVGElement>>;

  const src: string;
  export default src;
}

declare module '*.module.css' {
  const classes: { readonly [key: string]: string };
  export default classes;
}


import {BalloonProperties} from "./models/ymaps/balloon-properties";
import {WeekDay} from "./models/week-day";

/* Payload */

interface Range<T> {
	from: T;
	to: T;
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

/* Map API */

interface InfoObject {
	properties: BalloonProperties;
	map: MapApi;
}

interface IEvent {
	get(name: string) : any;
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

interface IDomEventEmitter<T> {
	events: EventManager<T>;
}

type BalloonEvents =
	"open"
	| "close"
	| "userclose"
	| "beforeuserclose";

interface BalloonApi extends IDomEventEmitter<BalloonEvents> {
	isOpen() : boolean;
	setData(data: InfoObject) : Promise<undefined>;
	getData() : InfoObject | null;
	getPosition() : number[] | null;
	destroy() : void;
	// [ latitude, longitude ]
	open(position?: [number, number], data?: any, options?: any) : Promise<undefined>
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

interface MapApi extends IDomEventEmitter<MapEvents> {
	balloon: BalloonApi;
	geoObjects: any;
}
