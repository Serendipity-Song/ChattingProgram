# ChattingProgram
이 레포지토리는 채팅 프로그램의 클라이언트와 서버 코드를 포함하고 있으며, 다중 사용자 스레드를 지원하는 채팅 서비스를 구현하고 있습니다.

## 프로젝트 구조
```
.
├── Chat.sln                  # 솔루션 파일
├── ChatClient.class          # 클라이언트 컴파일된 자바 클래스 파일
├── ChatClient.java           # 클라이언트 자바 소스 파일
├── ChatServer.class          # 서버 컴파일된 자바 클래스 파일
├── ChatServer.java           # 서버 자바 소스 파일
├── ChattingProgram.iml       # IntelliJ IDEA 프로젝트 파일
├── ReadThread.class          # 읽기 스레드 컴파일된 자바 클래스 파일
├── UserThread.class          # 사용자 스레드 컴파일된 자바 클래스 파일
├── UserThread.java           # 사용자 스레드 자바 소스 파일
├── WriteThread.class         # 쓰기 스레드 컴파일된 자바 클래스 파일
├── .gitignore                # Git에서 무시할 파일 목록
├── .gitattributes            # Git의 행동을 커스터마이징하는 파일
└── README.md                 # 프로젝트 설명서
```

## 사용 방법
1. 먼저 서버를 시작합니다. 이를 위해 `ChatServer.java`를 실행합니다.
2. 다음으로 클라이언트를 시작합니다. 이를 위해 `ChatClient.java`를 실행합니다.
3. 이후 클라이언트 콘솔에 메시지를 입력하면 서버에서 이를 수신하고 다른 연결된 클라이언트에 메시지를 전송합니다.

## 개발 환경
- Java 11 이상
- IntelliJ IDEA

## 라이센스
이 프로젝트는 [MIT 라이센스](./LICENSE)를 따릅니다.

---

이 정보는 프로젝트의 간략한 개요, 파일 구조, 사용 방법 등에 대한 정보를 제공합니다. 상세한 사용 방법이나 프로젝트에 대한 더 많은 정보를 제공하려면 추가적인 섹션을 README에 추가하실 수 있습니다.
