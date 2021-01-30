# ch4 connection management

- 어떻게 HTTP가 TCP 연결을 이용하는지
- TCP 연결에서의 Delay, bottlnecks, clogs
- hTTP 최적화 (parallel, keep-alive, pipelined connections)
- Dos and Don'ts for managing connections

## TCP Connection

HTTP communication의 대부분은 TCP/IP를 통해 전송된다.
client application은 server application에 TCP/IP 연결을 open할 수 있으며
연결이 성립되면, client와 server가 교환하는 메세지는 절대 없어지거나 손상되거나 전송되는 순서가 바뀌지 않는다.

http://www.joes-hardware.com:80/power-tools.html url에 접속할 경우
- hostname에 해당되는 www.joes-hardware.com(DNS)의 IP 주소(202.43.48.3)를 찾고
- 202.43.48.3의 port 80로 TCP 연결을 이루어낸다.
- 브라우저는 server에 HTTP GET 요청을 보내고
- server로부터 전달된 response message를 read하고
- 연결을 종료한다.

## TCP Reliable Data Pipes

HTTP 연결은 TCP 연결 위에서 몇 가지의 규칙만을 더해 이루어진다. 
TCP 연결은 신뢰성 있는 인터넷 연결로, 이를 잘 이해함으로써 data를 정확하고 빠르게 전송할 수 있다.
TCP는 HTTP에 reliable bit pipe를 전달한다. 한 쪽에서 전달하는 Bytes 정보는 이를 수신하는 쪽에서도 원 데이터와 동일한 순서로 전달된다.

