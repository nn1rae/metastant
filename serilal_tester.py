import serial

ser = serial.Serial('/dev/cu.usbmodem1401', 9600)
while True:

    data = ser.readline().decode().strip().split(':')
    print(data)
