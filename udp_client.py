import socket
import time 

udp_client=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

server_address=('localhost',12346)
message = "hello server"

while True:
    udp_client.sendto(message.encode(),server_address)
    data, addr =udp_client.recvfrom(1024)
    print("server say",data.decode())
    time.sleep(1)
    
    
udp_client.close()