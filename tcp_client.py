import socket
import time

HOST = '127.0.0.1'
PORT = 8080

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

while True:
    data = client_socket.recv(1024)
    print('Received from server:', data.decode())
    time.sleep(1)

client_socket.close()

