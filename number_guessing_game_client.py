import socket

HOST = 'localhost'
PORT = 9999

def play_game(clnt):
    attempts = 0
    while attempts < 5:
        guess = input("Enter your guess (1-100): ")
        clnt.sendall(guess.encode(encoding='utf-8'))
        result = clnt.recv(1024).decode(encoding='utf-8')
        print("Server:", result)
        if result == '정답입니다.':
            break
        attempts += 1

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as clnt:
    clnt.connect((HOST, PORT))
    print("Connected to the server")
    play_game(clnt)
    print("Game over")
