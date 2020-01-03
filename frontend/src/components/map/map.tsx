import React, {useCallback, useEffect, useState} from 'react';
import {Map, GeolocationControl, RouteEditor} from 'react-yandex-maps';

import {IEvent, MapApi} from '../../react-app-env';
import RouteControl from "../route-control";
import "./map.css";
import {subscribe} from "../../utils/ymaps/event-subscription";
import {BalloonProperties} from "../../models/ymaps/balloon-properties";
import {ObjectData} from "../../models/ymaps/object-data";

const MainMap: React.FC = () => {
	const [ mapApi, setMapApi ] = useState<MapApi>(null);

	const setMapRef = useCallback((map: MapApi) => map && setMapApi(map), []);

	useEffect(
		() => {
			if (!mapApi) return;

			const unsubscribers = [
				subscribe(mapApi, "click", openCustomBalloon)
			];
			return () => unsubscribers.forEach(cb => cb());
		},
		[mapApi]
	);

	return (
		<div className="map-container">
			<Map
				className="map"
				instanceRef={setMapRef as any}
				defaultState={{center: [59.939240, 30.315513], zoom: 10}}
			>
				<GeolocationControl />
				<RouteEditor />
			</Map>
			<section className="sidebar align_right">
				<RouteControl mapApi={mapApi} />
			</section>
		</div>
	);
};

function openCustomBalloon(e: IEvent) {
	const coords = e.get('coords');
	const map = e.get('map');

	map && map.balloon.open(coords, {
		contentHeader: 'Point',
		contentBody: `
			<p>Point coordinates:
			${[coords[0].toPrecision(6), coords[1].toPrecision(6)]}
			</p>
		`,
		properties: new BalloonProperties(new ObjectData({
			point: coords.slice().reverse()
		}))
	});
}


export default MainMap;
