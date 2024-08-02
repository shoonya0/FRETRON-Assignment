import React from 'react';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend } from 'recharts';

function Graph({ data }) {
  return (
    <LineChart
      width={1700}
      height={740}
      margin={{ top: 20, right: 20, bottom: 20, left: 20 }}
    >
      <CartesianGrid />
      <XAxis type="number" dataKey="x" name="X" tickCount={10} />
      <YAxis type="number" dataKey="y" name="Y" tickCount={10} />
      <Tooltip cursor={{ strokeDasharray: '3 3' }} />
      <Legend />
      {Object.keys(data).map((flight, index) => (
        <Line key={flight} type="monotone" dataKey="y" data={data[flight]}
          stroke={index === 0 ? "#8884d8" : index === 1 ? "#82ca9d" : "#ff7300"}
          dot={{ r: 5 }}
          name={`Flight ${flight}`}
        />
      ))}
    </LineChart>
  );
}

export default Graph;
