import socket
import time
import serial
import threading

uart =serial.Serial('/dev/ttyUSB0',115200,timeout=1)
latest_uart_data="no uart data yet"


def read_uart():
    global latest_uart_data
    while True:
        if uart.in_waiting:
            try:
                line = uart.readline().decode().strip()
                if line:
                    latest_uart_data= line
                    print("uart:",latest_uart_data)
                    
            except UnicodeDecodeError:
                continue

uart_thread=threading.Thread(target=read_uart,daemon=True)
uart_thread.start()

           
udp_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
udp_socket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
udp_socket.bind(('localhost',12346))

print("udp server listening on port 12346")

while True:
    data,addr=udp_socket.recvfrom(1024)
    message=data.decode().strip()
    print("client says",message)
    
    if message == "hello server":
        udp_socket.sendto(latest_uart_data.encode(),addr)