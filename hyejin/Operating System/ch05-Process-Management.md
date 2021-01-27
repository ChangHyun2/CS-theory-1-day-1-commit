## 5장 - 프로세스 관리
### Process
---
- **실행중인 program (program in execution)** 을 의미
 > 디스크에 실행파일 형태로 존재하던 program은 memory에 적재되어 CPU를 할당받아 instruction을 수행하면 실행된다. 이 때 program을 실행시키는 실행 주체인 program의 instance가 process이다.
- CPU를 획득해 자신의 코드를 수행하기도 하고, CPU 반환하고 입출력 작업을 수행하기도 함
> **프로세스 문맥(Process Context)**
> :Process가 현재 어떤 상태에서 수행되고 있는지 규명하기 위해 필요한 정보  
>①**하드웨어 context**, ②**process 주소공간**, ③**커널상의 context**로 분류
>  - 하드웨어 Context: CPU의 수행 상태 (PC값, 각종 register값)
>  - 커널상의 Context: PCB, kernel stack 
- Process state 변화도
 ![](https://www2.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_02_ProcessState.jpg)
process의 상태는 **실행**(running), **준비**(ready), **봉쇄**(blocked, wait, sleep) 크게 세 가지로 구분할 수 있다. 실행 상태는 process가 CPU를 보유 및 기계어 명령 실행 중이고, 준비 상태는 해당 process가 CPU를 보유하면 당장 명령을 실행할 수 있는 상태, 봉쇄는 CPU를 할당받더라도 입출력 대기 등으로 당장 명령을 실행할 수 없는 상태이다. 그밖에 process 생성 및 종류 중인 일시적 상태를 각각 시작(new), 종료(terminated)라 부른다. 
>참고: running -> ready로 가는 interrupt는 *timer interrupt*


### PCB
----
: OS가 system 내의 process를 관리하기 위해 process마다 유지하는 정보를 담는 kernel 내 자료구조다.
![운영체제(4)-프로세스 관리:man_factory_worker: - 개발새발정리노트](https://t1.daumcdn.net/cfile/tistory/99F6404A5B00FF8D16)
출처: https://getchan.github.io/cs/OS_4/
process state는 CPU 할당해도 되는지 여부 결정을 위해 필요하고,  program counter는 다음에 수행할 명령의 위치 가리킨다. CPU registers는 현 시점에 레지스터에 어떤 값을 저장하고 있는지를 나타내며, memory limits는 메모리 할당을 위해 필요하다.

### Context Switch
---
![3-1. Process](https://img1.daumcdn.net/thumb/R720x0.q80/?scode=mtistory2&fname=http%3A%2F%2Fcfile26.uf.tistory.com%2Fimage%2F997E5B425A42EFD10BC54B)
- CPU 할당되어있는 Process A가 timer interrupt나 입출력 요청 system call에 의해 CPU 회수가 될 때 자신의 process context를 자신의 PCB에 저장하고,  
- 새롭게 실행시킬 Process B에게 CPU를 이양한다. 이때 B는 자신의 process context를 PCB -> 하드웨어로 복원한다.
> 이때 주의해야 할 점은, Process가 실행중인 상태로 이행되는 그외 interrupt와 system call은 OS로 CPU 점유가 넘어가긴 하지만, 여전히 process를 수행하고 있는 것이므로 *실행모드가 user mode->kernel mode로의 변환*일 뿐이고 context switch는 아니다. (여기서도 마찬가지로 PCB에 자신의 process context 일부를 저장함)
- context switch는 **overhead**를 고려야해야하므로, timer에 의한 interrupt시 CPU 할당시간을 짧게하면 overhead가 커질 것이고, 그렇다고 할당 시간을 길게 잡으면 시분할의 의미가 사라지므로 적절한 time 설정이 필요

### Process Scheduling Queue
---
Process의 상태는 Kernel의 주소영역 중 data에서 Queue라는 자료구조로 관리한다.
![3-1. Process](https://img1.daumcdn.net/thumb/R720x0.q80/?scode=mtistory2&fname=http%3A%2F%2Fcfile6.uf.tistory.com%2Fimage%2F99D2B3435A42EF4C208C3E)
- process가 CPU를 기다리는지(Ready Queue, 이때의 Process는 Ready state), 입출력을 기다리는지(Device Queue, Blocked state) 등등 각 상태를 관리해준다.
- 하드웨어 자원을 기다리는 것 뿐만 아니라 공유 데이터인 소프트웨어 자원을 기다리는 경우도 있다.  (Resource queue)
  >공유 자원에 접근한다는 의미는 CPU를 점유중인 process 기준이 아니라 데이터를 기다리는 queue 순서대로 접근 권한을 부여한다. CPU를 할당하여 running중인 Process A가 공유 data에 접근하려면, 봉쇄 상태로 전환하여 Resource Queue에 들어가 줄을 서야한다.

- Job Queue: system 내 모든 process를 관리한다. process의 상태와는 관계없이 모든 process가 Job queue에 속하며, 즉 Ready queue와 Device queue에 존재하면 여기에도 반드시 존재해야한다.

- Queue의 자료구조 형태
	![프로세스 스케줄링 (Process Scheduling)](https://img1.daumcdn.net/thumb/R720x0.q80/?scode=mtistory2&fname=http%3A%2F%2Fcfile28.uf.tistory.com%2Fimage%2F99E2FA395BDA5AD4243427)
	- Queue의 가장 앞부분인 Queue header를 시작으로 들어온 순서대로 Pointer가 연결된 LinkedList의 형태로 저장된다.  
	- CPU를 할당받다가 입출력 요청이 발생한 Process의 진행 과정
		- 1) Device Queue에서 봉쇄 상태로 대기한다. 
		- 2) 순서가 되면 장치의 Service를 받는다.
		- 3) 해당 device로부터의 요청 작업이 완료되면 device controller가 interrupt를 보낸다.
		- 4) interrupt handler 처리를 통해 Process가 Ready state로 바뀐다.
		- 5) Ready queue로 이동해 CPU의 할당을 기다린다.

### Scheduler
---
- **Long term scheduler**  
: 장기 스케줄러는 작업스케줄러(job scheduler)라고도 부른다. **시작 상태의 process를 ready 큐에 진입시킬지 결정**하는 역할을 하며, process에게 메모리를 할당하는 문제에 관여한다.*메모리에 동시에 올라가있는 프로세스의 수(degree of multiprogramming)를 조절*
  - 현대의 시분할 시스템에서는 장기 스케줄러는 대부분 두지 않는다. 이전에는 적은 양의 메모리를 많은 process에게 할당하면 프로세스당 메모리 보유량이 지나치게 적어져 시스템 효율이 떨어졌으나, 이제는 시분할 시스템용으로 중기 스케줄러를 두는 경우가 많다. 
- **Short term scheduler**  
  : CPU 스케줄러라고도 하며, ready 큐에 있는 여러 process 중에서 어떤 것을 running 상태로, CPU를 할당할 것인지 결정한다. 시분할 시스템에서 timer interrupt가 발생하면 호출된다.
- **Medium term scheduler**  
  : 메모리에 적재된 프로세스 수를 동적으로 조절한다. 메모리에 너무 많은 프로세스가 적재되어 프로세스당 보유 메모리양이 극도로 적어지면 CPU 수행에 당장 필요한 주소공간도 메모리에 올려놓기 어려워진다. (디스크 입출력 多) -> 이를 막기위해 blocked 상태, ready queue로 이동하는 process 순으로 메모리를 빼앗아 디스크의 스왑 영역에 저장한다. *(Swap out)* 이렇게 swap out된 상태를 중지(suspended, stopped) 상태라 부른다.  

  ![What is a suspended process in an OS? - Quora](https://qph.fs.quoracdn.net/main-qimg-8da20a8502dc9d7ed01c08b8bafc8599)


### Process 생성
---
- system 부팅 후 최초의 process는 OS가 생성, 그 이후에는 이미 존재하는 process(부모 프로세스)가 다른 process(자식 프로세스)를 복제 생성한다.
- 생성된 process가 작업을 수행하기 위해선 자원 필요하다. 부모와 자식이 CPU를 획득하기 위해 경쟁하는 관계로 공존하며 수행되는 모델과, 자식이 terminated 될때까지 부모가 wait하는(동기화) 모델 존재한다. 

   > wait 모델의 예시  
UNIX 명령어 command 입력시 command 수행 종료될때까지 프롬프트를 다시 띄우지 않음   
부모: 명령어 입력창, 자식: command를 수행중
- 생성된 자식 프로세스도 별도의 주소공간을 보유한다. **fork()** 시스템 콜을 하면 부모의 프로세스에서 **프로세스 ID를 제외한 모든 문맥(context)를 복사**하여 자식 프로세스를 만든다. 자식은 프로그램을 수행하는 지점도 부모와 동일하다. 

  > *그렇다면 부모와 자식을 어떻게 구분하는가?  
바로 fork()의 반환값이 자식은 0, 부모는 양수이다.(분기지점) 다른 독자적인 수행을 원한다면 자식에게 **exec() 시스템 콜을 통해 주소 공간을 새롭게** 덮어씌워준다.  
![Image for post](https://miro.medium.com/max/1374/1*uWytsHCicvTwVHB7hoSuWg.png)

- 부모 프로세스는 해당 자식 프로세스들이 모두 종료된 후에 종료될 수 있다. 이와 관련해 프로세스의 종료 두가지를 알아보자.
  - 자발적 종료: process가 명령(instrcution)을 모두 수행한 후 exit() 시스템 콜을 통해 OS에게 자신이 종료됨을 알린다. -> OS는 자원을 회수하고 process를 정리한다.
  - 비자발적 종료: 부모 프로세스가 abot()라는 함수를 통해 자식 프로세스의 수행을 강제로 종료시킨다.
> 부모 프로세스가 종료되어도 자식을 유지시키고 싶으면?  
  ->종료되지 않을 다른 프로세스의 양자로 자식 프로세스를 보내는 방식을 이용한다.

### Process간 협력
---
- process는 각자 자신만의 주소공간을 가지고 수행되며, 다른 프로세스의 주소 공간을 참조하는 것은 허용되지 않는다. (다른 프로세스의 수행에 영향을 미칠 수 없다)
- 독립적인 프로세스들이 경우에 따라 협력할 떄 효율성이 좋아질 수 있다.
- 대표적인 협력 메커니즘은 OS가 제공하는 IPC(Inter-Process Communication), 하나의 컴퓨터 안에서 실행 중인 서로 다른 프로세스 간 발생하는 통신이다. *의사소통(통신)+동기화 보장*
  - 메세지 전달 (message passing) 방식
  - 공유 메모리(shared memory) 방식
 