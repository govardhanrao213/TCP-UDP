import socket
import time

udp_client=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server_address =('localhost',12346)

try:
    while True:
        udp_client.sendto("hello server".encode(),server_address)
        data,_=udp_client.recvfrom(1024)
        print("received from server:",data.decode())
except KeyboardInterrupt:
    print("exiting...")


finally:
    udp_client.close()