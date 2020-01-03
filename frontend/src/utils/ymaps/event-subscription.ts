import {EventCallback, IDomEventEmitter} from "../../react-app-env";

export function subscribe(obj: IDomEventEmitter<any>, event: string, cb: EventCallback) {
	obj.events.add(event, cb);
	return () => obj.events.remove(event, cb);
}
