# OSI 7계층별 이해
## 1계층 (Physical Layer)

 1계층은 물리적 연결과 관련된 정보를 정의한다. 주로 **전기 신호를 전달**하는 데 초점이 맞추어져 있다. 1계층의 주요 장비로는 허브(Hub), 리피터(Repeater), 케이블(Cable), 커넥터(Connector), 트랜시버(Tranceiver), 탭(TAP)이 있다. 

 허브와 리피터는 네트워크 통신을 중재하는 네트워크 장비이고, 케이블과 커넥터는 케이블, 그리고 트랜시버는 컴퓨터의 랜 카드와 케이블을 연결하는 장치이다. 탭은 네트워크 모니터링과 패킷 분석을 위해 전기 신호를 다른 장비로 복제해 준다.

 1계층에서는 들어온 전기 신호를 그대로 잘 전달하는 것이 목적이므로 전기 신호가 1계층 장비에 들어오면 이 전기 신호를 재생성하여 내보낸다. 1계층 장비는 주소의 개념이 없으므로 전기 신호가 들어온 포트를 제외하고 모든 포트에 같은 전기 신호를 전송한다.

## 2계층 (Data Link Layer)

 2계층은 **전기 신호를 모아 우리가 알아볼 수 있는 데이터 형태로 처리**한다. 1계층과는 다르게 전기 신호를 정확히 전달하기보다는 주소 정보를 정의하고 정확한 주소로 통신이 되도록 하는 데 초점이 맞추어져 있다. 

 전기 신호를 모아 데이터 형태로 처리하므로 데이터에 대한 에러를 탐지하거나 고치는 역할을 수행할 수 있다. 현대에는 물리 계층이 신뢰할 수 있다만 과거에는 신뢰할 수 없는 미디어를 이용해 통신하는 경우도 많아 2계층에서 에러를 탐지하고 고치거나 재전송했지만 이더넷 기반 네트워크의 2계층에서는 에러를 탐지하는 역할만 수행한다.

 또한 2계층에서는 1계층과는 다르게 출발지와 도착지 주소를 확인하고 내게 보낸 것이 맞는지, 또는 내가 처리해야 하는지에 대해 검사한 후 데이터 처리를 수행한다.

 주소 체계가 생긴다는 의미는 한 명과 통신하는 것이 아니라 동시에 여러 명과 통신할 수 있다는 것이므로 무작정 데이터를 던지는 것이 아니라 받는 사람이 현재 데이터를 받을 수 있는지 확인하는 작업부터 해야 한다. 이 역할을 [Flow Control](https://www.notion.so/Flow-Control-67ffacf62b3c4a88b177fc40fc9667dc)이라고 한다. 

 이 계층에서 동작하는 네트워크 구성 요소는 **네트워크 인터페이스 카드**와 **스위치(Switch)**이다. 2계층의 가장 중요한 특징은 **MAC 주소**라는 주소 체계가 있다는 것인데 NIC와 스위치 모두 MAC 주소를 이해할 수 있고 스위치는 MAC 주소를 보고 통신해야 할 포트를 지정해 내보내는 능력이 있다.

 **네트워크 인터페이스 카드**에는 고유 MAC 주소가 있다. 네트워크 인터페이스 카드가 동작하는 방식은 다음과 같다.

1. 전기 신호를 데이터 형태로 만든다.
2. 목적지 MAC 주소와 출발지 MAC 주소를 확인한다.
3. 네트워크 인터페이스 카드의 MAC 주소를 확인한다.
4. 목적지 MAC 주소와 네트워크 인터페이스 카드가 갖고 있는 MAC 주소가 맞으면 데이터를 메모리에 적재하고 다르면 데이터를 폐기한다.

 **스위치**는 단말이 어떤 MAC 주소인지, 연결된 포트는 어느 것인지 주소 습득 (Address Learning) 과정에서 알 수 잇다. 이 데이터를 기반으로 단말들이 통신할 때 포트를 적절히 필터링하고 정확한 포트로 포워딩해준다. 반면, 1계층에서 동작하는 허브는 한 포트에서 전기 신호가 들어오면 전체 포트로 전기 신호를 전달하다 보니 전체 네트워크에서 동시에 오직 하나의 장비만 데이터를 보낼 수 있다. 스위치의 적절한 **필터링**과 **포워딩** 기능으로 통신이 필요한 포트만 사용하고 네트워크 전체에 불필요한 처리가 감소하면서 이더넷 네트워크 효율성이 크게 향상 되었고 이더넷 기반 네트워크가 급증하는 계기가 되었다.

### ※네트워크 인터페이스 카드

 네트워크 인터페이스 카드를 부르는 용어는 매우 많다.

1. 네트워크 인터페이스 카드 또는 네트워크 인터페이스 컨트롤러 (Network Interface Controller) 줄여서 NIC라고도 부른다.
2. 네트워크 카드 (Network Card)
3. 랜 카드 (Lan Card), 과거에 이더넷은 LAN (Local Area Network)에서만 사용되다 보니 랜 카드라고 부르게 되었다.
4. 물리 네트워크 인터페이스 (Physical Network Interface)
5. 이더넷 카드 (Ethernet Card)
6. 네트워크 어댑터 (Network Adapter)

 

## 3계층 (Network Layer)

 3계층에서는 **IP 주소**와 같은 논리적인 주소가 정의된다. MAC 주소와 달리 IP 주소는 사용자가 환경에 맞게 변경해 사용할 수 있고 네트워크 주소 부분과 호스트 주소 부분으로 나뉜다. 3계층을 이해할 수 있는 장비나 단말은 네트워크 주소 정보를 이용해 자신이 속한 네트워크와 원격지 네트워크를 구분할 수 있고 원격지 네트워크를 가려면 어디로 가야 하는지 경로를 지정하는 능력이 있다.

 3계층에서 동작하는 장비는 라우터이다. 라우터는 IP 주소를 이해할 수 있어서 이를 사용해 최적의 경로를 찾아주고 해당 경로로 패킷을 전송하는 역할을 한다.

## 4계층 (Transport Layer)

 1,2,3 계층에서 신호와 데이터를 올바른 위치로 보내고 실제 신호를 잘 만들어 보내는 데 집중하는 반면 4계층은 실제로 해당 데이터들이 정상적으로 잘 보내지도록 확인하는 역할을 한다.

  패킷 네트워크는 데이터를 분할해 패킷에 실어보내니 중간에 패킷이 유실되거나 순서가 바뀌는 경우가 생길 수 있다. 4계층에서는 패킷을 분할할 때 패킷 헤더에 **보내는 순서와 받는 순서를 적어** 통신하므로 패킷이 유실되면 **재전송을 요청**할 수 있고 순서가 뒤바뀌더라도 바로잡을 수 있다.

 패킷에 순서를 명시한 것이 Sequence Number이고 받는 순서를 나타낸 것이 Acknowledgement Number 이다. 뿐만 아니라 장치 내의 많은 애플리케이션을 구분할 수 있도록 포트 번호를 사용해 **상위 애플리케이션을 구분**한다.

 4계층에서 동작하는 장비로는 **로드 밸런서**와 **방화벽**이 있다. 이 장비들은 포트 번호와, 시퀀스, ACK 번호 정보를 이용해 부하를 분산하거나 보안 정책을 수립해 패킷을 통과, 차단하는 기능을 수행한다.

## 5계층 (Session Layer)

 5계층은 응용 프로세스가 연결을 성립하도록 도와주고 연결이 안정적으로 유지되도록 관리하고 작업 완료 후에는 이 연결을 끊는 역할을 한다. "세션"을 관리하는 것이 주요 역할인 세션 계층은 TCP/IP 세션을 만들고 없애는 책임을 진다. 또한, 에러로 중단된 통신에 대한 에러 복구와 재전송도 수행한다.

## 6계층 (Presentation Layer)

 6계층은 프레젠테이션