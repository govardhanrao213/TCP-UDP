import socket
import time

udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Allow reuse of the port
udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

udp_socket.bind(('localhost', 12346))

print("Server listening on port 12346")

try:
    while True:
        data, addr = udp_socket.recvfrom(1024)
        message = data.decode()
        print("Client says:", message)

        if message == "hello server":
            response = "hello from server"
            udp_socket.sendto(response.encode(), addr)
            time.sleep(1)
except KeyboardInterrupt:
    print("\nServer stopped.")
finally:
    udp_socket.close()
