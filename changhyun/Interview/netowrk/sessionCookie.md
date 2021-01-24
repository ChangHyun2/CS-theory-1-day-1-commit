# 세션과 쿠키

## Cookie

쿠키는 브라우저에 저장되는 key-value 형식의 작은 데이터 파일로 브라우저(유저) 또는 서버에서 생성할 수 있다.

쿠키는 주로 다음과 같은 용도로 사용된다.

- session 관리
- 개인화 정보 관리
- user의 웹사이트 사용 분석

브라우저에 저장되는 쿠키는 자동적으로 매 request마다 `Cookie` HTTP 헤더에 포함되어 쿠키 도메인 서버에 전달된다. 

## Session

세션은 서버에서 자체적으로 관리하는 data store이다. 따라서 세션 정보에 대한 제어 권한은 서버에게 있다.

세션은 서버에서 관리되기 때문에 보안적인 측면에 브라우저에 저장되는 쿠키에 비해 안전하다. 따라서 secure한 유저 데이터를 관리할 떄 사용된다.

세션은 브라우저에서 종료될 경우(`onbeforeunload`) 자동적으로 서버에서 지정한 기간 후(일반적으로 20~30분)에 사라진다. 

## Session & Cookie

제한된 네트워크 자원을 효율적으로 사용하기 위해 HTTP는 stateless한 특징을 갖는다.

때문에 서버의 입장에서 클라이언트로부터의 모든 요청은 독립적이므로 서버에서는 해당 요청이 어떤 유저로부터 요청된 것인지 알 수 없다. 

즉, 유저와 서버가 소통하는 과정에서 서버는 어떤 유저와 대화를 했는지 기억할 수 없는 것이다.

위와 같은 단점을 보완하는 여러 방법 중 하나로 session과 cookie가 사용된다.

user가 서버에 로그인할 때의 상황은 세 가지로 나뉜다.

1. 최초로 서버에 로그인한 경우
2. 최근에 로그인한 적이 있는 경우 (sessionID가 browser의 쿠키에 저장되어 있는 상태)
3. 과거에 로그인했었고 꽤 오랜 시간이 지난 경우 (저장되었던 쿠키가 만료되어 사라진 상태)

서버 user DB에 저장되어있는 유저가 최초로 서버에 로그인하는 경우를 가정해본다면

1. client의 유저는 POST 메소드를 통해 server에 username과 password를 전달한다.
2. server는 client의 request header를 통해 cookie에 sessionID가 없다는 것을 확인한다.
3. server는 username, password를 User DB에서 확인한다.
4. user를 DB에서 확인한 server는 session 객체([IIS](https://webcheatsheet.com/asp/session_object.php#:~:text=The%20Session%20object%20stores%20information,available%20until%20the%20session%20expires.))를 생성하고 이를 server의 세션(data store)에 저장한다. session 객체는 user_id (user DB id) , sessionID, 만료일과 같은 속성들을 포함한다.
5. session 객체를 User DB에 저장하기도 하며(여러 디바이스별 로그인 현황 조회) 서버의 session 정보를 session DB에 저장하기도 한다.
6. server는 client에 response하며, 이 때 `Set-cookie` 헤더를 통해 server의 세션이 저장하고 있는 session객체의 sessionID를 client의 쿠키에 저장한다.

이로써 server는 이후의 요청이 발생할 경우 user DB를 통한 인증이 아닌, client의 cookie에 저장된 sessionID를 통해 srever의 store에서 sessionID에 매핑된 유저 정보를 찾고 유저 정보에 포함된 user_id를 통해 data DB를 곧바로 조회할 수 있게 된다.

[https://www.youtube.com/watch?v=44c1t_cKylo](https://www.youtube.com/watch?v=44c1t_cKylo)

[https://machinesaredigging.com/2013/10/29/how-does-a-web-session-work/#:~:text=Structure of a session,-The session is&text=The session can be stored,and managed by the server](https://machinesaredigging.com/2013/10/29/how-does-a-web-session-work/#:~:text=Structure%20of%20a%20session,-The%20session%20is&text=The%20session%20can%20be%20stored,and%20managed%20by%20the%20server).

[https://medium.com/createdd-notes/starting-with-authentication-a-tutorial-with-node-js-and-mongodb-25d524ca0359]https://medium.com/createdd-notes/starting-with-authentication-a-tutorial-with-node-js-and-mongodb-25d524ca0359