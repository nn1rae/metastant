from flask import Flask, render_template , jsonify
import serial
import random
import threading

temperature, wind_direction, wind_speed, rain = 0,0 ,0, 0
windCodeDict = {0: "N", 1: "NNE", 2: "NE", 3: "ENE", 4: "E", 5: "ESE", 6: "SE", 7: "SSE", 8: "S", 9: "SSW", 10: "SW", 11: "WSW", 12: "W", 13: "WNW", 14: "NW", 15: "NNW" , 16: "UNDERFINED"}


#ser = serial.Serial('COM3', 9600)
ser = serial.Serial('/dev/cu.usbmodem1401', 9600)




def get_data():
    global windCodeDict
    while True:
        global temperature, wind_direction, wind_speed, rain
        dataFromBoard = tuple(ser.readline().decode().strip().split(':'))
        temperature = int(float(dataFromBoard[0]))
        wind_direction = windCodeDict[int(dataFromBoard[1])]
        wind_speed = dataFromBoard[2]
        rain = dataFromBoard[3]

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
    response = jsonify(sensor_data)
    response.headers.add('Access-Control-Allow-Origin', '*')
    return response

@app.route('/')
def index():
    
    return render_template('index.html')

if __name__ == '__main__':
    app.run(host="0.0.0.0", port= 4577,debug=False)
