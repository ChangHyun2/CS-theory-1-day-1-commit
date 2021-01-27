# CPU-Scheduling의 이해

## CPU Scheduling이란...
멀티태스킹이나 멀티프로그래밍을 하기위해서 필수적인 요소라고 볼 수 있다  
여러개의 프로세스들이 메모리에 적재 되어있을텐데 싱글 코어라고 가정했을때  
CPU를 점유할수 있는 프로세스는 하나만 가능하다  
그러므로 메모리에 있는 프로세스들을 어떤식으로 순서를 매겨야 효율적으로 CPU를 사용할지  
정하는것이 `CPU-Scheduling` 이라고 볼 수 있다

### 목적
- 프로세스들이 항상 실행하기 위해서
- CPU의 사용률을 극대화 시키기 위해서

### 할일
ready queue에 들어있는 프로세스중에서 선택해서 CPU로 넘겨주는 일  

**여기서 발생하는 문제**
- LinkedList의 FIFO queue로 만들것인지
- Binary Tree의 Priority Queue로 만들것인지  

## Preemptive (선점형) / Non-Preemptive (비선점형)
- `Non-Preemptive` Scheduling  
 CPU는 프로세스가 스스로 나가기 전까지는 붙잡고 있어야 한다  
   스스로 나간다라는 표현은 waiting 이나 terminating이다  

- `Preemptive` Scheduling  
 프로세스는 스케줄러에의해서 상태가 변할 수 있다

### CPU-Scheduling을 결정하는 요인
1. 프로세스가 `running -> waiting` 으로 바뀔때
2. 프로세스가 `running -> ready` 로 바뀔때
3. 프로세스가 `waiting -> ready` 로 바뀔때
4. 프로세스가 `terminate` 되었을 때

1번과 4번은 스케줄러가 따로 할 수 는 없고 비선점형으로 진행된다  
2번과 3번은 선점형으로 스케줄러가 조절할 수 있다

## Dispatcher
실질적으로 Context Switch를 실행하는 모듈이라고 보면 된다  
스케줄러가 선택하고 실행은 Dispatcher가 한다  

### 기능
- 실행중인 프로세스를 다른 프로세스로 context-switching
- user mode로의 변경
- 유저 프로그램을 적절한 위치로 이동시켜준다

Dispatcher같은 경우에는 context switch가 발생할때마다 실행되어야하기 때문에 매우 빨라야한다  

### Dispatcher latency
프로세서에서 Context Switch가 일어날때 걸리는 시간이라고 보면된다  
프로세스0 실행 -> PCB0 저장 -> PCB1불러오기 -> 프로세스1 실행  

## Scheduling의 목적성
- `CPU utilization` : 가능한 cpu가 쉬지 않게 만들기
- `Throughput` : 단위 시간내에 많은 프로세스를 완료하기
- `Turnaround time` : 프로세스가 실행에서 종료까지의 시간을 최소화시키기
- `Waiting time` : ready queue에서 보내는 시간을 줄이기
- `Response time` : 응답시간을 줄이기

위에 5가지 중에서 `Throughput`, `Turnaround time`이 중요하다






