import socket                                                   #소켓 통신을 위한 라이브러리

HOST = 'localhost'                                              #서버의 호스트 주소 지정

def play_game(clnt):                                            #게임을 진행하는 함수 정의 (클라이언트 소켓)
    attempts = 0                                                #시도 횟수 초기화
    while attempts < 5:                                         #5번 시도할동안 반복
        guess = input("추측해보세요! (1-100): ")                 #추측 숫자 입력
        clnt.sendall(guess.encode(encoding='utf-8'))            #추측 숫자를 서버에 전송 (문자열을 utf-8로 디코딩)
        result = clnt.recv(1024).decode(encoding='utf-8')
        print("Server:", result)                                #서버 메시지 출력
        if result == '정답입니다.':                              #서버의 메시지가 '정답입니다'인 경우 break
            break
        attempts += 1                                           #시도 횟수 1 증가

port_input = input("연결하려면 포트번호를 입력하세요: ")          #포트 번호를 입력
try:
    PORT = int(port_input)                                      #포트 번호를 정수로 변환
except ValueError:                                              #유효한지 확인
    print("무효한 포트번호입니다. 정수를 입력해주세요.")          
    exit()                                                      #유효하지 않으면 프로그램 종료

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as clnt: #소켓 객체 생성, 클라이언트 소켓에 할당 IPv4 TCP/IP
    clnt.connect((HOST, PORT))                                  #서버의 호스트와 포트에 연결 시도
    print("서버에 연결되었습니다.")                               #서버 연결 메시지 출력
    play_game(clnt)                                             #게임 진행
    print("게임이 종료되었습니다.")                               #게임 종료 메시지 출력
