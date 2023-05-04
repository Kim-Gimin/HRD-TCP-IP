import socket
import threading
import random
import RPi.GPIO as GPIO

HOST = 'localhost'
PORT = 9999

# GPIO 설정
GPIO.setmode(GPIO.BCM)
leds = [23, 24, 25, 1, 18]  # LED 추가
for i in leds:
    GPIO.setup(i, GPIO.OUT)
    GPIO.output(i, GPIO.LOW)

def generate_random_number():
    return random.randint(1, 100)

def check_guess(guess, answer):
    if guess < answer:
        return '더 큰 숫자입니다.'      # smaller
    elif guess > answer:
        return '더 작은 숫자입니다.'    # greater
    else:
        return '정답입니다.'            # correct

def received_message(clnt, answer):
    wrong_attempts = 0
    while wrong_attempts < 5:  # 최대 틀린 횟수를 5회로 조절
        data = clnt.recv(1024).decode(encoding='utf-8')
        data = data.strip()
        if data.isdigit():
            guess = int(data)
            result = check_guess(guess, answer)
            clnt.sendall(result.encode(encoding='utf-8'))
            if result == '정답입니다.':
                break
            else:
                GPIO.output(leds[wrong_attempts], GPIO.HIGH)
                wrong_attempts += 1

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.bind((HOST, PORT))
    server.listen()

    while True:
        print("연결을 기다리고 있습니다...")  # Waiting for connection...
        clnt, addr = server.accept()
        print("연결되었습니다 ==>", addr)   # Connected by

        answer = generate_random_number()
        print("무작위 번호가 생성되었습니다:", answer)  # Random number generated:

        t = threading.Thread(target=received_message, args=(clnt, answer))
        t.start()
        t.join()

        # GPIO 초기화 및 연결 종료
        for led in leds:
            GPIO.output(led, GPIO.LOW)
        clnt.close()
        print("클라이언트가 연결을 해제했습니다.") # Client disconnected
