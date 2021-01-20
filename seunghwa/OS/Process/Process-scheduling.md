# Process Scheduling

## Scheduling Queues
스케줄링 큐의 종류 2가지
1. Ready Queue</br>
  -> 프로세스들이 처음 초기화되서 시스템에 들어오게 되면 `ready queue`에 놓여진다</br>
  -> OS에 <span style="color:orange">1개</span> 존재한다
2. Wait Queue</br>
  -> 특정 이벤트나 I/O가 발생했을 때는 `wait queue`로 가게된다</br>
  -> I/O 장치가 여러개 존재하기 때문에 <span style="color:orange">1개 이상</span> 존재한다

위의 `Queue`들은 PCB들을 `Linked List`로 만들어서 구현한다

## Context Switch (문맥 교환)
프로세스의 context란 PCB를 가리키는 말이라고 생각하면 된다</br>
### Context Switch가 하는 일
CPU에서 다른 프로세스가 불렸을 때 `Context Switch`를 통해 **현재의 시점을 저장**하고 다른 프로세스를 부른다</br>
다른 프로세스가 끝났을 때 `Context Switch`를 통해 저장되었던 것을 PCB로 부터 불러와서 **정지시점**부터 다시 실행한다</br>

> 위와 같이 **Context Switch**와 **Scheduling Queue**가 존재하기 때문에</br>
> OS에서 **time sharing**과 **multiprogramming**이 가능한 것이다

`time sharing` : CPU가 비는 시간 없이 자신의 비는 곳을 쪼개서 다른 프로그램들을 실행한다</br>
`multiprogramming` : 프로세스에서 CPU를 사용률을 최대로 이끌어내기 위한 방법이다

### 동시성에 대한 같은말 다른말
**같은말**
- at then same time
- simultaneously
- concurrently
   
**다른말**
- parallelism