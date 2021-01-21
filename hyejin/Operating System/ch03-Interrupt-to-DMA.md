## 3장 - 컴퓨터 시스템의 동작 원리 (~5. 입출력구조)
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