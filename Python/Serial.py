import serial
import time

# Replace 'COM3' with the actual port name of your Arduino
arduino_port = '/dev/ttyUSB0'
baud_rate = 9600

# Open the serial connection
ser = serial.Serial(arduino_port, baud_rate, timeout=1)

for i in range(10):
    try:
        # Send data to Arduino
        data_to_send = 10  # Replace with the data you want to send
        ser.write("data_to_send".encode())

    except serial.SerialException as e:
        print(f"Error: {e}")

    #finally:
        # Close the serial connection
        #ser.close()
ser.close()