import React, { useState } from 'react';
import Graph from './grid/graph';
import collisionControl from './collisionControl/collisionControl';

function App() {
  const [data, setData] = useState({ flight1: [], flight2: [], flight3: [] });
  const [x, setX] = useState('');
  const [y, setY] = useState('');
  const [flight, setFlight] = useState('flight1');
  const [finalData, setFinalData] = useState(null);

  const handleAddPoint = () => {
    const newData = { ...data, [flight]: [...data[flight], { x: parseFloat(x), y: parseFloat(y) }] };
    setData(newData);
    setX('');
    setY('');
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    const dataAfterCollisionControl = collisionControl(data);
    setFinalData(dataAfterCollisionControl);
  };

  return (
    <div className="App">
      <h1>Dynamic 2D Points Graph for Three Flights</h1>
      <form onSubmit={handleSubmit}>
        <label>
          Flight:
          <select value={flight} onChange={(e) => setFlight(e.target.value)}>
            <option value="flight1">Flight 1</option>
            <option value="flight2">Flight 2</option>
            <option value="flight3">Flight 3</option>
          </select>
        </label>
        <label>
          <br />
          X:
          <input type="number" value={x} onChange={(e) => setX(e.target.value)} required />
        </label>
        <label>
          Y:
          <input type="number" value={y} onChange={(e) => setY(e.target.value)} required />
        </label>
        <button type="button" onClick={handleAddPoint}>Add Point</button>
        <button type="submit">Submit</button>
      </form>
      {finalData && <Graph data={finalData} />}
    </div>
  );
}

export default App;
