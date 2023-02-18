import serial

ser = serial.Serial('COM3', 9600)
while True:

    data = ser.readline().decode().strip().split(':')
    print(data)
