## 운영체제와 정보기술의 원리 2장 - 운영체제 개요  
  
### 운영체제 분류 (Uniprocessor 기준)
---
#### Multi tasking (다중작업)
- 운영체제가 동시작업을 진행할수있는지? (==interactive system)
-*이때 고려해야할 점: 여러 프로그램이 CPU와 메모리를 공유중*
- cpu의 작업시간을 여러프로그램들이 나누어쓸수 있는지? time sharing system
- memory의 공간을 조금씩 보유하여 동시에 메모리에 올려놓고 처리하는 multi programming system

#### 다중사용자 동시지원

- 단일 사용자용(DOS, MS윈도우), 다중사용자용(이메일, 웹서버)

#### 작업처리방식
- batch processing (일괄처리): 요청된 작업을 일정략씩 모아서 한꺼번에 처리
- 시분할:  여러 작업을 수행할때 컴퓨터의 처리능력을 일정시간단위로 분할
- 실시간(real time): 정해진 시간 안에 어떠한 일이 반드시 처리됨을 보장
 -> 즉, 시간안에 작업완료되지 못하면 동작 X 큰 위험
-경성 실시간 시스템(hard realtime system): 시간 못지키면매우위험
-연성 실시간 시스템(soft realtime system): 정해진 시간단위로 전달해야 올바른 기능수행 (ex 멀티미디어 스트리밍)

#### Multi-processor system
여기까지는 CPU가 하나인 컴퓨터도 해당

multi-processor system은 하나의 컴퓨터 안에 여러개의 CPU 존재
서로 다른 CPU에서 여러 프로그램이 동시 실행 가능, but 관리 어려움!
(책에서는 하나의 CPU 탑재된 컴퓨터 다룸)  
  
### 자원 관리 기능
---
### 하드웨어 자원
>CPU, memory, 주변장치 및 입출력 장치  
>CPU와 메모리는 전원 off시 처리중 정보가 모두 지워짐  
> -> 저장위해 I/O장치중 보조기억장치에 파일형태로 저장

### CPU scheduling
- FIFO
 : CPU를 사용하려는 프로세스 순서대로 처리, CPU 사용 효율적 but 전체 시스템 비효율
 - Round Robin
  : CPU 할당받는 시간을 일정 고정시간으로 제한 (보통 밀리초 단위)
  - Priority
   : 우선순위 높은 프로세스 먼저 CPU 할당
    (오래 기다린 프로세스를 우대하기 위해 우선순위를 높여주는 방안도 있음)
    
### Memory 관리
: 메모리의 어느부분이 어떤 프로그램에 의해 사용되고 있는지? **address**로 관리
 - 메모리가 필요할때 할당, 필요X시 회수
 - 서로 다른 프로세스의 영역 침범 못하게 보안유지 필요


|     |Fixed partition      |Variable partition|  Virtual memory | 
|---- |---------------------|-----------------|---------------------|
|특징|물리 메모리 분할|물리 메모리 분할| 가상 메모리 주소 page분할 |
|비교|정해진(정적) 크기, 수 | 프로그램에 맞춘(동적) 크기, 수 |사용->메모리, 나머지->스왑영역 
|단점|**internal fragmentation**|**external fragmentation**|  |

>**가상 메모리 주소**?
>모든 프로그램은 물리적 메모리와는 독립적으로 0번지부터 시작하는 자신만의 가상메모리 주소를 갖는다. 운영체제는 이 가상메모리의 주소를 물리적 메모리 주소로 mapping하는 기술을 이용해 주소를 변환시킨 후 프로그램을 물리적 메모리에 올리게 된다.

### Interrupt
 : 주변장치 및 입출력 장치가 CPU 할당을 원할때 서비스 요청시키는 신호
 - Interrupt 발생 및 처리
 ```mermaid
 graph LR 
 A[CPU 작업 수행] -->  C(수행 상태 저장) 
 C --> E(OS의 interrupt handler)
 E --CPU 할당--> B[주변장치]
 D[Controller]
 B --요청 --> D
 D -- Interrupt 발생 --> A
 ```

 CPU scheduling을 따르던 CPU는 Interrupt 발생시 잠시 중단 후 요청 서비스 수행  
 *ex) 키보드의 글자를 입력시 interrupt 발생시키고 입력이 들어왔음을 알림 (입력데이터 전달)*
>**Interrupt 처리 루틴(=Interrupt handler)?**  
>Interrupt가 발생했을 때 해주어야할 작업을 정의한 프로그램 코드, Interrupt 종류마다 다름  
**Controller**?  
주변 장치는 각 장치마다 그 장치에서 일어나는 업무관리하는 일종의 작은 CPU (controller) 존재, 해당 장치의 업무 처리 및 메인 CPU에 interrupt 발생시켜 보고하는 역할