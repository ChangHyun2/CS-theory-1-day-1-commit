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

## TCP Streams are Segmented and Shipped by IP Packets

TCP는 데이터를 IP패킷(데이터그램)이라 불리는 작은 chunks로 쪼개어 전송하며 이러한 전송 방식에서 HTTP > TCP > IP > Network Interface 순으로 계층이 형성된다. 
HTTPS는 HTTP와 TCP 사이에 cryptographic encryption 계층이 추가된 계층 구조를 가지며 TSL 또는 SSL을 사용한다.
![](./ch4-connection-management/2021-02-01-23-51-34.png)

HTTP가 메세지 전송을 시도할 경우, HTTP는 TCP 연결을 open하고 TCP는 데이터 스트림을 받아 segments라 불리는 작은 단위로 쪼개고 이를 IP packets으로 캡슐화해 전송한다. HTTP는 TCP 연결을 open할 뿐, TCP를 통해 진행되는 과정에는 전혀 관여하지 않는다.
IP 패킷은 다음 요소를 포함한다.

- IP packet header : IP 주소 정보, 패킷 크기, other flags
- TCP segment header : TCP 포트 번호, TCP control flags, 순서 정보, 무결성 확인을 위한 숫자 정보
- chunk of TCP data

![](./ch4-connection-management/2021-02-01-23-51-15.png)!

## Keeping TCP Connections Straight

컴퓨터는 동시에 여러 개의 TCP 연결을 가질 수 있는데, TCP는 이를 port numbers를 통해 유지한다.
TCP 연결은 4 종류의 숫자 정보를 통해 구분될 수 있다.
1. source IP 주소
2. source port
3. destination IP 주소
4. destination port

