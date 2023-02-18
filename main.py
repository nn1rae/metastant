from flask import Flask, render_template , jsonify
import serial
import random
import threading

temperature, wind_direction, wind_speed, rain = 0,0 ,0, 0


#ser = serial.Serial('COM3', 9600)
ser = serial.Serial('/dev/cu.usbmodem1401', 9600)




def get_data():
    while True:
        global temperature, wind_direction, wind_speed, rain
        temperature, wind_direction, wind_speed, rain = ser.readline().decode().strip().split(':')
        
threading.Thread(target=get_data).start()

app = Flask(__name__)

@app.route('/sensors')
def get_sensor_data():
    global temperature, wind_direction, wind_speed, rain
    
  
    sensor_data = {
        'temperature': temperature,
        'wind_direction': wind_direction,
        'wind_speed': wind_speed,
        'rain': rain
    }

    return jsonify(sensor_data)

@app.route('/')
def index():
    
    return render_template('index.html')

if __name__ == '__main__':
    app.run(host="0.0.0.0", port= 4577,debug=False)
