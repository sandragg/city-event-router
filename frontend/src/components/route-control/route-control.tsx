import {MapApi} from "../../react-app-env";
import "./route-control.css";
import React, {useState} from "react";
import {Waypoint} from "../../models/waypoint";

const RouteControl: React.FC<{ mapApi: MapApi }> = ({ mapApi }) => {
	const [ waypoints, setWaypoints ] = useState<Waypoint[]>([]);

	const addWaypoint = () => {
		if (!mapApi || !mapApi.balloon || !mapApi.balloon.isOpen()) return;

		const data = mapApi.balloon.getData();
		const objectData = data && data.properties.getAll();

		if (objectData) {
			setWaypoints(
				waypoints.concat(new Waypoint({
					...objectData,
					coords: objectData.point.slice().reverse() as [number, number]
				}))
			);
		}
	};

	return (
		<section className="route-control">
			<button onClick={addWaypoint}>Add point to route</button>
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

export default RouteControl

