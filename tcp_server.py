import socket
import time

HOST = '127.0.0.1'
PORT = 8080

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

print(f"Server listening on {HOST}:{PORT}")

connection_socket, client_address = server_socket.accept()
print(f"Connected by {client_address}")

while True:
    connection_socket.sendall(b'Hello from server')
    time.sleep(1)

connection_socket.close()
server_socket.close()
