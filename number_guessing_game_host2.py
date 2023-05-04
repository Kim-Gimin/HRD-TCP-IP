import socket                                                   # 소켓 통신을 위한 라이브러리
import threading                                                # 멀티스레딩을 위한 라이브러리
import random                                                   # 난수 생성을 위한 라이브러리
import RPi.GPIO as GPIO                                         # 라즈베리 파이의 GPIO 핀 제어를 위한 라이브러리
import time                                                     # 시간 지연 기능을 위한 라이브러리

HOST = 'localhost'                                              # 서버의 호스트 주소를 지정
PORT = 9999                                                     # 서버의 포트 번호를 지정

# GPIO 설정
GPIO.setmode(GPIO.BCM)                                          # BCM 모드를 사용하여 GPIO 핀 번호를 설정
leds = [23, 24, 25, 1]                                      # 사용할 LED 핀 번호를 리스트로 저장
for i in leds:                                                  # 각 LED 핀에 대해 설정을 진행
    GPIO.setup(i, GPIO.OUT)                                     # 핀을 출력 모드로 설정
    GPIO.output(i, GPIO.LOW)                                    # LED를 초기 상태로 끄도록 설정

def generate_random_number():                                   # 난수를 생성하는 함수를 정의
    return random.randint(1, 100)                               # 1부터 100 사이의 난수를 반환

def check_guess(guess, answer):                                 # 추측한 숫자와 정답을 비교하는 함수를 정의
    if guess < answer:                                          # 추측한 숫자가 정답보다 작으면,
        return '더 큰 숫자입니다.'                               # '더 큰 숫자입니다.'를 반환
    elif guess > answer:                                         # 추측한 숫자가 정답보다 크면,
        return '더 작은 숫자입니다.'                             # '더 작은 숫자입니다.'를 반환
    else:                                                       # 추측한 숫자가 정답과 같으면,
        return '정답입니다.'                                     # '정답입니다.'를 반환

def received_message(clnt, answer):                             # 클라이언트로부터 받은 메시지를 처리하는 함수를 정의
    wrong_attempts = 0                                          # 틀린 시도 횟수를 초기화
    while wrong_attempts < 5:                                   # 틀린 시도가 5번 미만일 때까지 반복
        data = clnt.recv(1024).decode(encoding='utf-8')         # 클라이언트로부터 데이터를 받아 디코딩
        data = data.strip()                                     # 문자열의 양쪽 공백을 제거
        if data.isdigit():                                      # 받은 데이터가 숫자인지 확인
            guess = int(data)                                   # 숫자로 변환하여 추측한 값에 저장
            result = check_guess(guess, answer)                 # 추측한 값과 정답을 비교한 결과를 가져옵니다.
            clnt.sendall(result.encode(encoding='utf-8'))       # 결과를 인코딩하여 클라이언트에게 전송
            if result == '정답입니다.':                         # 결과가 정답일 경우,
                for i in range(3):                              # 3번 반복하면서,
                    for led in leds:                            # 각 LED 핀에 대해,
                        GPIO.output(led, GPIO.HIGH)             # LED를 켭니다.
                    time.sleep(0.5)                             # 0.5초 동안 대기
                    for led in leds:                            # 각 LED 핀에 대해,
                        GPIO.output(led, GPIO.LOW)              # LED를 종료
                    time.sleep(0.5)                             # 0.5초 동안 대기
                break                                           # 정답을 맞췄으므로 반복문을 빠져나옵니다.
            else:                                               # 결과가 오답일 경우,
                GPIO.output(leds[wrong_attempts], GPIO.HIGH)    # 틀린 시도 횟수에 해당하는 LED를 점등
                wrong_attempts += 1                             # 틀린 시도 횟수를 1 증가

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server: # 서버 소켓 객체를 생성
    server.bind((HOST, PORT))                                   # 서버의 호스트 주소와 포트 번호를 바인드
    server.listen()                                             # 서버가 클라이언트의 연결을 기다리도록 설정

    while True:                                                 # 무한 루프를 실행
        print("연결을 기다리고 있습니다...")                      # 연결 대기 상태를 출력
        clnt, addr = server.accept()                            # 클라이언트와 연결을 수락
        print("연결되었습니다 ==>", addr)                        # 연결된 클라이언트의 주소를 출력

        answer = generate_random_number()                       # 무작위 숫자를 생성
        print("무작위 번호가 생성되었습니다:", answer)            # 생성된 무작위 숫자를 출력

        t = threading.Thread(target=received_message, args=(clnt, answer)) # 새로운 스레드를 생성하고, received_message 함수를 실행
        t.start()                                               # 스레드를 시작
        t.join()                                                # 스레드가 종료될 때까지 대기

        # GPIO 초기화 및 연결 종료
        for led in leds:                                        # 각 LED 핀에 대해,
            GPIO.output(led, GPIO.LOW)                          # LED를 종료
        clnt.close()                                            # 클라이언트와의 연결을 종료
        print("클라이언트가 연결을 해제했습니다.")                # 클라이언트 연결 종료 메시지를 출력
