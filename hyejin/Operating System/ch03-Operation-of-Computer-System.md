## 3장 - 컴퓨터 시스템의 동작 원리
### 컴퓨터 시스템 구조
---
- 컴퓨터 내부 장치와 외부 장치
  
![image](https://user-images.githubusercontent.com/59992230/105203236-3651ae00-5b86-11eb-83b6-4fe4da0069d8.png)
-내부 장치: 컴퓨터내 연산을 수행하는 **CPU**, 작업이 수행될 프로세스를 올려두는 **메모리**   
-외부 장치들(입출력장치)

>**입출력(I/O)?**  
 -외부->내부로 데이터를 읽어와서(입력) 연산 수행 후  
 -내부->외부로 데이터를 내보내는(출력)  
 컴퓨터는 위와 같은 방식으로 업무 처리

### Interrupt
---

앞서 하드웨어 자원은 CPU, 메모리, 입출력 장치가 존재한다고 했다.

- 컴퓨터 내부에서 진행하는 연산은 *CPU*가 담당하고, 외부의 연산은 작은 CPU 역할을 하는 각 입출력 장치의 *controller*들이 수행한다.
- 그러나 CPU에 비해 controller들의 연산처리 속도는 현저히 **느리다**. CPU가 입출력 요청을 보내고 controller들이 수행하기를 한참 기다리게 될 경우 자원의 낭비가 생길 수 있다. 그러므로 각 입출력 연산이 완료되었다는 신호를 controller에서 **Interrupt**를 발생시켜서 알리게 되는 것이다.
  
- 입출력 연산 다했어요!  
controller -> "Interrupt 발생" -> Interrupt line  
- 물론, controller만 발생시킬 수 있는건 아니다. 사용자 program 실행시에 비정상 처리를 할 때의 예외 처리(**Exception**)나 OS에 서비스를 요청하고 싶을떄(**System call**) Interrupt Line setting 설정을 통해 interrupt를 발생시킬 수 있다. 장치에서 불러올때와는 달리 소프트웨어 interrupt라 하며, 보통 **trap**이라 불린다.
- CPU는 메모리로부터 명령(instruction)을 읽어와 수행하는데, 각 instruction을 수행할때마다 *Interrupt line*에 Interrupt가 왔는지를 확인해준다. Interrupt가 있다면 다음 instruction은 수행하지 않고, interrupt의 처리를 하러 현재 상태를 저장한다.
- Interrupt를 처리하러가려면?   
  controller -> Interrupt 확인(Interrupt Line) -> 상태저장 -> Interrupt 처리

>### - 상태는 왜 저장?
>CPU는 instruction 연산할때 CPU 내부의 register에서 데이터 읽고쓰는데,
>interrupt를 처리하는 과정에서 새로운 명령 시행시 register의 정보가 사라짐 (다시 돌아올 수 없다)
>### - 그렇다면 상태 저장은 어떻게?
>운영체제에서는 각 프로그램별로 **PCB**를 할당해주며, 그곳에 프로그램의 register 값, 메모리 주소, 하드웨어 상태 등을 저장  
>interrupt를 처리할때 실행하고 있던 프로그램의 정보를 PCB에 저장하고, interrupt 수행 후에 다시 해당 프로그램으로 돌아올때 그 정보를 읽어온다.

### Interrupt는 어떻게 처리?
---
간단하게 Interrupt handler대로 수행하면 된다.
- 개별 Interrupt handler에는 해당하는 Interrupt시에 처리해야할 코드가 정의되어있다.  
- 어느 Interrupt에 어떤 handler를 찾아야하는지는 OS의 커널에 있는 *Interrupt Vector*에 있다.
- 상태 저장하고 온 CPU   
-> Interrupt Vector (handler 주소찾기) -> Interrupt handler -> 코드 수행
### 입출력 연산과 동기성
---
프로그램이 입출력 연산을 요청했을 때, 작업이 완료 되어야 이후 작업을 진행하는 동기식 입출력(synchronous I/O)을 생각해보자.
>*Remind  **입출력(I/O)**?  
 컴퓨터 시스템이 컴퓨터 외부의 입출력 장치들과 데이터를 주고받는 것

- A: 통장 잔고를 0원으로 만드는 프로그램  
B: 통장에 100원을 입금하는 프로그램  
이때의 '통장'이란 장치를 외부 장치의 디스크 처럼 생각해보자. 프로그램의 실행 순서는 잔고를 리셋하고 100원을 입금하는 A->B라 생각해보자.
- ① A에서 I/O 연산을 요청 후 blocked state 전환  
② CPU는 B에게 할당  
③ B가 I/O 연산을 요청 (blocekd)  
④ 통장 잔고를 0원으로 리셋 후 Interrupt 전달  
⑤ CPU가 해당 Interrupt를 수행하고 A의 다음 명령을 실행  
⑥ 이후 B의 I/O Interrupt가 도착, B를 수행

- 수행 결과로 통장의 현재 잔고가 100원으로 남는다.  
하지만 4.에서 **A의 입출력 연산보다 B의 연산이 먼저 수행된다면?** B의 입출력 연산으로 기껏 넣은 100원이 A의 입출력 연산으로 다시 리셋된다.
- 이런 불상사를 방지하기 위해 각 controller들은 입출력 연산을 순서대로 수행하는 **Queue**를 둔다. A->B의 요청 순서가 잘 이루어지게끔 처리한다.
  
---
  
>Interrupt를 정리해보자면...  
CPU에게 하드웨어 장치로부터 신호를 보내거나 혹은 프로그램 내부의 Interrupt line setting을 통해 처리 요청신호를 보내는 것을 말한다.  
그 신호를 받은 CPU는 실행중이던 프로그램의 상태를 저장하고 CPU의 할당을 OS로 옮겨가게 된다.  
그곳에서 interrupt service routine (=interrupt handler)의 순서에 따라 각 interrupt에 해당하는 처리를 진행한다.  

### DMA
---
![image](https://user-images.githubusercontent.com/59992230/105498707-d84ad500-5d03-11eb-8a0d-151b44eb7431.png)  
(*사진은 저자 교수님의 KMOOC 강의)
- 메모리는 CPU에서만 접근 가능한 장치다. 메모리 접근 연산이 필요할 때 CPU에 interrupt를 보내서 대행하는 식의 처리를 진행한다. 이렇게 매 자잘한 접근마다 CPU의 처리를 요청한다면 프로그램을 실행하던 CPU의 효율성이 떨어진다. 
- 그래서 메모리에게도 작은 cpu 역할을 하는 **DMA(Direct Memory Access)** controller를 두어 CPU의 역할을 분담한다.
- DMA가 직접 메모리에 접근한다는 의미보다는, 메모리로 보내려는 데이터를 작은 Byte 단위가 아닌 큰 Block 단위로 읽어오고,  작업 수행이 다 되었다고 CPU에게 interrupt를 보낸다. 메모리 접근 연산으로 인한 interrupt의 빈도를 줄여서 CPU를 좀 더 효율적으로 사용할 수 있게 한다.

### 저장장치
---
- 보조기억장치는 **file system**과 **swap area**로 구분  
- 프로그램 수행에 당장 필요한 부분은 메모리에, 나머지는 디스크의 swap area에 swap out 시키는 형태로 활용
- file system은 비휘발성을 활용한다면, swap area는 메모리의 연장공간으로 활용하는 것

- 계층구조
![image](https://user-images.githubusercontent.com/59992230/105499541-f8c75f00-5d04-11eb-8ff3-55dcb850172f.png)

>**캐싱기법**?
>상위 계층으로 갈수록 접근 속도가 월등히 빨라지나, 용량은 상대적으로 적다. 하지만 필요한 정보만 선별적으로 저장해둔다면?
>책장을 정리한다고 생각해보자. 팔이 잘 닿는 곳보다 수그리거나 의자에 올라가야 닿을 수 있는 공간이 더 넓을 것이라고 가정한다면, 닿기 쉬운 곳엔 무엇을 두어야할까. 그야 물론 자주 쓰이는 책들일 것이다. 이처럼 저장장치에서 빈번히 사용되는 정보를 선별 저장하는 기법을 의미한다. 이를 토대로 적은 적장공간으로 평균 성능 향상 가능하다.

### 보안
---
**하드웨어 보안**
- 다른 프로그램의 실행 방해 or 프로그램간 충돌 문제 막아야함
- OS에서는 이를 위해 중요 명령을 수행할 수 있는 커널모드(kernel mode, system mode)와 사용자모드(user mode)로 구분하여 권한 부여
- 그러나 OS가 아니라 CPU에서 실행될때에는 모드로 권한 판단이 어려움, 그래서 CPU 내부에 **모드비트(mode bit)**를 설정
- 0: 커널모드, 1: 사용자모드
- 보안 명령 수행하기 전에는 mode bit을 조사해서 값이 0으로 세팅되어 있을때만 실행, OS에게 점유권을 넘기고 커널모드로 실행
- 이후에 OS-> CPU로 제어권을 넘길땐 모드비트 1으로 전환해줌
- interrupt 발생시 mode bit 0으로 자동 세팅, 결국 특권 명령은 OS만 실행 가능

**메모리 보안**
- 사용자 프로그램이 타 프로그램 or OS의 메모리 영역 참조하지 못하게 방지
- 2개의 register를 사용하여 프로그램이 접근하려는 메모리 부분이 합법적인지 체크
-
 ![image](https://user-images.githubusercontent.com/59992230/105503634-2e227b80-5d0a-11eb-96c8-3313a65bc4d9.png)
![image](https://user-images.githubusercontent.com/59992230/105503648-324e9900-5d0a-11eb-97fe-fc0b4b5b8bc5.png) 
- **base register**: 어떤 프로그램이 수행되는 동안 그 프로그램이 합법적으로 접근할 수 있는 메모리상의 가장 작은 주소 (**시작주소**)
- **limit register**:  그 프로그램이 base register부터 접근할 수 있는 메모리의 범위 (**길이**)
- 접근하려는 주소가  base < address < base + limit 인지 확인, 아닐시 interrupt 발생 후 강제종료
- 두 register의 지정은 OS의 특권명령으로 셋팅
> *여기서는 한 프로그램이 메모리 한 영역 안에 연속적으로 위치할 때의 경우*를 말한다. 메모리의 여러 영역에 나뉘어 위치하는 paging은 7장에서 다룸


**CPU 보호**
- 특정 프로그램이 CPU 사용 권한을 독점하는걸 방지하기 위한 **timer** 존재
- CPU 점유 일정 시간 경과 -> timer에서 interrupt 발생 -> handler: CPU를 타 프로그램에게 이양
- timer는 일정 시간 단위로 세팅 가능(OS에서 load timer)하며, 매 clock tick마다 1씩 감소하고 0이 될때 interrupt 발생

**입출력 수행**
- 사용자 프로그램에서 입출력 명령을 수행시킬 땐 system call로 interrupt를 발생시켜 OS의 커널모드에서 특권명령으로 실행해야하며, 사용자 프로그램은 직접 수행하지 못한다. 