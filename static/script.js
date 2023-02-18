function updateSensorValues() {
  fetch('http://localhost:4577/sensors')
    .then(response => response.json())
    .then(data => {
      const tempSensorValue = document.getElementById('temp-sensor').getElementsByClassName('sensor-value')[0];
      const windSpeedSensorValue = document.getElementById('wind-speed-sensor').getElementsByClassName('sensor-value')[0];
      const windDirectionSensorValue = document.getElementById('wind-direction-sensor').getElementsByClassName('sensor-value')[0];
      const precipitationSensorValue = document.getElementById('precipitation-sensor').getElementsByClassName('sensor-value')[0];

      tempSensorValue.textContent = data.temperature;
      windSpeedSensorValue.textContent = data.wind_speed;
      windDirectionSensorValue.textContent = data.wind_direction;
      precipitationSensorValue.textContent = data.rain;
    })
    .catch(error => console.error('Error fetching sensor data:', error));
}setInterval(updateSensorValues, 100);

const sensors = document.querySelectorAll('.sensor');


sensors.forEach(sensor => {
  const popup = sensor.querySelector('.sensor-popup');
  sensor.addEventListener('mouseover', () => {
    popup.style.display = 'block';
  });
  sensor.addEventListener('mouseout', () => {
    popup.style.display = 'none';
  });
});
