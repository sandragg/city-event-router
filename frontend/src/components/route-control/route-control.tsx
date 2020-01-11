import {MapApi} from "../../react-app-env";
import "./route-control.css";
import React, {useState} from "react";
import {Waypoint} from "../../models/waypoint";
import {withYMaps, YMapsApi} from "react-yandex-maps";
import {WaypointWithMeta} from "../../models/waypoint-with-meta";

const RouteControl: React.FC<{ ymaps: YMapsApi, map: MapApi,  }> = ({ ymaps, map }) => {
	const [ waypoints, setWaypoints ] = useState<Waypoint[]>([]);

	const addWaypoint = () => {
		if (!map || !map.balloon || !map.balloon.isOpen()) return;

		const newWaypoint = getWaypointFromBalloon(map);
		newWaypoint && setWaypoints(waypoints.concat(newWaypoint));
	};

	const calculateRoute = () => {
		calculateDistanceMatrix(waypoints, getDistance(ymaps, map))
			.then(res => {
				console.log(res);
				// call wasm module
			})
			.catch(err => console.log(err));
	};

	return (
		<section className="route-control">
			<button onClick={addWaypoint}>Add point to route</button>
			<button onClick={calculateRoute}>Calculate route</button>
			<ul>
				{waypoints.length
					? waypoints.map(
						wp =>
						<li key={wp.coords.toString()}>
							{wp.name} - {wp.coords.toString()}
						</li>
					)
					: "An empty list"}
			</ul>
		</section>
	);
};

function getWaypointFromBalloon(map: MapApi) {
	const data = map.balloon.getData();
	const objectData = data && data.properties.getAll();

	if (!objectData) {
		return null;
	}
	const params: Waypoint = {
		id: Math.random().toString(),
		...objectData,
		coords: objectData.point.slice().reverse() as [number, number]
	};
	const schedule = objectData.responseMetaData && objectData.responseMetaData.Hours;

	return !schedule ? new Waypoint(params) : new WaypointWithMeta({
		...params,
		schedule: schedule.Availabilities
	});
}

function getDistance(ymaps: YMapsApi, map: MapApi) {
	const params = {
		multiRoute: true,
		routingMode: "masstransit"
	};

	return (from: Waypoint, to: Waypoint): Promise<number> =>
		ymaps.route(
			[ from.coords, to.coords ],
			params
		)
			.then(route => {
				const activeRoute = route.getActiveRoute();
				if (!activeRoute) {
					throw new Error("No route available");
				}
				map.geoObjects.add(route);
				return activeRoute.properties.getAll();
			});
}

function calculateDistanceMatrix(points: Waypoint[], getDistance: (from: Waypoint, to: Waypoint) => Promise<number>) {
	const distances: Promise<number>[] = [];

	for (let from = 0; from < points.length; from++)
		for (let to = from + 1; to < points.length; to++)
			distances.push(getDistance(points[from], points[to]));

	return Promise.all(distances);
}

export default withYMaps(RouteControl, true, ['route'])

