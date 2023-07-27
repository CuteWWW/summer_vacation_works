import socket
import hashlib
import random
server = socket.socket()
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(('127.0.0.1', 9001))
server.listen()

conn, addr = server.accept()

num = random.randint(2 ** 127, 2 ** 128)
num = str(num)
num=num.encode()#这两步不要合并，否则报错
p=num
for i in range(22):
    p = hashlib.sha256(p)
    p=p.hexdigest()
    p=p.encode()

for i in range(122):
    num = hashlib.sha256(num)
    num=num.hexdigest()
    num=num.encode()

count=0
while True:
    count=count+1
    print(count)
    if count==1:conn.send(b'helloBob')

    c_info = conn.recv(1024) #接受客户端消息

    print(c_info)
    if c_info == b'your proof is right':                      #当客户端发送bye时，服务端给客户端发送bye并结束循环
        break
    elif c_info == b'hello alice i need p':
        conn.send(p)

    elif c_info == b'hello alice i need num':
        conn.send(num)

    elif c_info=='error':
        print(b'error')
        break
conn.close()
server.close()
