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
- Long term scheduler
- Short term scheduler
- Medium term scheduler