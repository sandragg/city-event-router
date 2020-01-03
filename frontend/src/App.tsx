import React from 'react';
import {YMaps} from 'react-yandex-maps';

import './App.css';
import MainMap from "./components/map";

const App: React.FC = () => {
	return (
		<div className="App">
			<YMaps
				query={{
					apikey: 'a34ea76d-0ca3-478d-9629-f2bffc19d418',
					lang: 'ru_RU'
				}}
			>
				<MainMap/>
			</YMaps>
		</div>
	);
};

export default App;
