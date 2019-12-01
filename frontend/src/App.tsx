import React from 'react';
import {YMaps, Map, GeolocationControl} from 'react-yandex-maps';

import './App.css';

const App: React.FC = () => {
  return (
    <div className="App">
      <YMaps
          query={{
            apikey: '34ea76d-0ca3-478d-9629-f2bffc19d418',
            lang: 'ru_RU'
          }}
      >
        <div>My awesome application with maps!</div>
        <Map defaultState={{ center: [59.939240, 30.315513], zoom: 10 }}>
          <GeolocationControl options={{ float: 'left' }} />
        </Map>
      </YMaps>
    </div>
  );
};

export default App;
