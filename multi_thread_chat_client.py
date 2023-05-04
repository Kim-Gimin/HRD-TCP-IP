# include
import socket
import threading
HOST = 'localhost' #127.0.0.1
PORT = 9999

name:str = input("Nick Name? ")
# task function
def sending_message(clnt):
    while True:
        input_msg:str = input() # hello blah blah
        input_msg.strip() # \r\n 제거
        input_msg = "[" + name + "]\t:\t" + input_msg
        clnt.sendall(input_msg.encode('utf-8')) # network

def receiving_message(clnt):
    while True:
        data = clnt.recv(1024).decode('utf-8')
        print(data)

with socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM, proto=0) as clnt:
    clnt.connect((HOST, PORT))
    t1 = threading.Thread(target=sending_message, args=(clnt,))
    t2 = threading.Thread(target=receiving_message, args=(clnt,))
    t1.start() #시작
    t2.start()
    t1.join()
    t2.join()


    
