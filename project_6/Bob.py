import socket
import hashlib
import random
client = socket.socket()
client.connect(('127.0.0.1', 9001))
count=0
while True:
    count=count+1
    print(count)
    s_info = client.recv(1024)               #接受服务端的消息并解码
    print(s_info)
    if count==2:
        p=s_info
        client.send(b'hello alice i need num')

    elif count==3:
        num=s_info
        for i in range(100):
            p=hashlib.sha256(p)
            p=p.hexdigest()
            p=p.encode()
        if p==num:client.send(b'your proof is right')
        else: client.send(b'error')
        break
    if s_info == b'helloBob':
        print(count)
        client.send(b'hello alice i need p')



client.close()