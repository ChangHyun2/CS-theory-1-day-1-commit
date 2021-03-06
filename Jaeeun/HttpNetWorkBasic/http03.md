### 1. 지속 연결로 접속량을 절약하는 HTTP
> 초기의 HTTP는 작은 사이즈의 텍스트를 보내는 정도였기 때문에, HTTP 통신을 한 번 할 때마다 TCP에 의해 연결과 종료를 할 필요가 있었습니다.
> 하지만 여러 이미지가 포함되어 있는 이미지를 전송하기 위해서는 다량의 리퀘스트를 전송해야 해서 통신량이 늘어나게 된다.

#### 1-1 지속 연결
HTTP/1.1 과 일부 HTTP/1.0 에서는 TCP 연결 문제를 해결하기 위해서 **지속연결**이라는 방법을 고안했다. TCP 커넥션의 연결과 종료를 반복되는 오버헤드를 줄여주기 때문에 서버에 대한 부하가 경감되면서 속도가 빨라 졌다.

#### 1-2 파이프라인화
파이프라인화에 의해서, 이전에는 리퀘스트 송신 후에 리스폰스를 수신할 때까지 기다린 뒤에 리퀘스트랄 발행했지만, **리스폰스를 기다리지 않고 다음 리퀘스트를 보낼 수 있다.**

### 2. 쿠키를 사용한 상태 관리

![](https://images.velog.io/images/jaeeunxo1/post/99d0f52f-c5f2-4f02-8ebc-26ebcd022746/image.png)

**HTTP는 스테이트리스(stateless) 프로토콜이기 때문에, 과거에 교환했던 리퀘스트와 리스폰스의 상태를 관리하지 않는다.** 
인증이 필요한 웹 페이지에서 상태 관리를 하지 않는다면, 인증을 마친 상태를 잊어버리기 때문에 새로운 페이지로 이동할 때마다 재차 로그인 상태를 관리해야 한다.

> 쿠키는 서버에서 **리스폰스로 보내진 Set-Cookie라는 헤더 필드에 의해 쿠키를 클라이언트에 보존한다.** 다시 클라이언트가 같은 서버로 리퀘스트를 보낼 때, **자동으로 쿠키 값을 넣어서 송신**한다. 
> 서버는 클라이언트가 보내온 쿠리를 확인해서 어느 클라이언트가 접속했는지 체크하고 서버 상의 기록을 확인해 이전 상태를 확인한다.

### 3. HTTP 메시지
> HTTP에서 교환하는 정보는 HTTP 메세지라고 불리는데, 리퀘스트 측 HTTP 메세지를 리퀘스트 메시지, 리스폰스 측 HTTP 메세지를 리스폰스 메시지라고 부른다.

`메세지 헤더` : 서버와 클라이언트가 꼭 처리해야 하는 리퀘스트와 리스폰스 내용과 속성
`CR+LF` : 개행 문자
`메세지 바디` : 꼭 전송되는 데이터 그 자체

#### 3-1 리퀘스트와 리스폰스 메세지 구조
<img src="https://images.velog.io/images/jaeeunxo1/post/96bfde79-21eb-4540-a397-a87ac5d2e4d0/image.png">

`리퀘스트 라인` : 리퀘스트에 사용하는 **메소드와 리퀘스트 URI**와 사용하는 **HTTP 버전**이 포함된다.
`상태 라인` : 리스폰스를 나타내는 **상태코드와 설명**, **사용하는 HTTP 버전**이 포함된다.
`헤더필드` : 여러 조건과 속성 등을 나타내는 각종 헤더 필드 포함된다.

### 4. 인코딩으로 전송 효율 높이다.
> HTTP로 데이터를 전송할 경우 그대로 전송할 수도 있지만 전송할 때에 인코딩(변환)을 실시함으로써 **전송 효율을 높일 수 있다.**

#### 4-1 메세지와 엔티티

`메세지(message)` : HTTP 통신의 기본 단위로 옥텟 시퀀스로 구성되고 통신을 통해서 전송된다.
`엔티티(entity)` : 리퀘스트랑 리스폰스의 페이로드로 전송되는 정보로 엔티티 헤더 필드와 엔티티 바디로 구성된다.

**HTTP 메세지 바디의 역할은 리퀘스트랑 리스폰스에 관한 엔티티 바디를 운반하는 것이다.** 기본적으로 엔티티 바디와 메세지 바디는 같지만 전송 코딩이 적용된 경우에 엔티티 바디의 내용이 변화하기 때문에 달라진다.

#### 4-2 콘텐츠 코딩
콘텐츠 코딩이란 엔티티에 적용하는 인코딩 기능이다. **엔티티 정보를 유지한채로 압축**하고 콘텐츠 코딩된 엔티티는 **수신한 클라이언트 측에서 디코딩** 한다.

#### 4-2 청크 전송 코딩
사이즈가 큰 데이터를 전송하는 경우에는 **데이터를 분할해서 조금씩 표시**하는 것을 청크 전송 코딩이라 한다.
엔티티 바디를 덩어리로 분해한다. **16진수로 사용해서 단락을 표시하고 엔티티 바디 끝에는 0을 기록**한다. 


<hr>

#### 참고
https://medium.com/@ddinggu/cookie%EB%9E%80-a650c6d2803e