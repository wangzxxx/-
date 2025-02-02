import serial
import time

ser = serial.Serial('COM10', 9600, timeout=1)

while True:
    timestamp = int(time.time()) 
    ser.write(f"{timestamp+28800}\n".encode())
    print("正在发送:", timestamp+28800)
    time.sleep(1)
