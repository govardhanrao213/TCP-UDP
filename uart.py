import serial
import time

# Replace with your actual port name and baud rate
SERIAL_PORT = '/dev/ttyUSB2'  # Use 'COM3' on Windows
BAUD_RATE = 9600

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")

    while True:
        ser.write(b'hello\n')  # Send 'hello' followed by newline
        print("Sent: hello")
        time.sleep(1)  # Wait 1 second

except serial.SerialException as e:
    print(f"Error: {e}")
except KeyboardInterrupt:
    print("Stopped by user.")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Serial port closed.")
