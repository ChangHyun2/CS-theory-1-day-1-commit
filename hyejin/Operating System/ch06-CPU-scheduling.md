## 6장 - CPU 스케줄링
### CPU 작업과 I/O 작업
---
- 기계어 명령  
   - CPU 내에서 수행 (ex Add)              -> 일반
   - 메모리 접근 필요 (ex Store, Load) -> 일반
   - 입출력을 동반 -> 특권
 - 사용자 프로그램은 CPU 작업과 I/O 작업의 반복으로 구성  
   - CPU burst: CPU를 직접 가지고 빠른 명령을 수행하는 단계
   - I/O burst: I/O 요청이 발생해 커널에 의해 입출력 작업을 진행하는 비교적 느린 단계
  (그림)
   - 각 프로그램마다 CPU burst와 I/O burst가 차지하는 비율이 서로 다름
     - I/O burst가 빈번해서 CPU burst가 짧은 프로세스 : **I/O bound process**
     - I/O를 거의 하지 않아 CPU burst가 긴 프로세스 : **CPU bound process**
     - I/O bound process는 주로 사용자로부터 interaction을 계속 받아서 수행시키는 대화형 프로그램(interactive program)이 해당되고, CPU bound process는 CPU 작업 계산 위주의 프로그램이다.
    - (CPU버스트의 분포 그림) 
      - CPU 버스트가 모두 균일하면 상관없겠지만, 시분할 시스템에서 CPU 버스트가 제각각인 프로그램이 공존하기에 CPU scheduling 기법이 반드시 필요
      -  CPU 잠깐 I/O 작업 수행하는 process 多, interactive 작업이라 사용자에게 빠른 응답 보내는게 중요 => 우선적으로 CPU 할당 필요
      
### CPU Scheduler
 ---
  : Ready 상태에 있는 process들 중 어떤 process에게 CPU를 할당할지 결정하는 OS의 code
 - CPU scheduler가 필요한 상황
    - 1. Running 중인 process가 I/O 요청 등에 의해 blocked되는 경우
    - 2. Running process가 timer interrupt에 의해 Ready 상태로 바뀌는 경우
    - 3. I/O 요청으로 blocked 되어있던 process의 I/O 작업이 완료되어 interrupt 발생 후 다시 process가 Ready 상태로 되는 경우(I/O 완료 process의 우선순위가 더 ↑)
    - 4. CPU에서 실행하고 있던 process가 terminated되는 경우
- Schduling 방식
  - 비선점형(nonpreemptive) : CPU를 획득한 process가 스스로 반납하기까지 CPU를 빼앗기지 않는 방법 (1, 4)
  - 선점형(preemptive) : process가 CPU를 계속 사용하길 원하더라도 강제로 빼앗을 수 있는 방법 (2, 3)
### Dispatcher
---
: CPU scheduler가 어떤 process에게 할당할지 결정하고 난 후엔 실제로 CPU를 이양하는 작업이 필요하다. 새로 선택된 process가 CPU 할당받고 작업 수행할 수 있도록 환경설정을 하는 OS의 코드를 Dispatcher라고 부른다.
- 수행중이던 process의 context를 그 PCB에 저장
- 새로운 process의 문맥을 PCB로부터 복원 후 user mode로 전환해 CPU의 제어권을 넘김
- 하나의 process 정지 ~ 다른 process에게 CPU 전달까지 소요되는 시간을 **dispatch latency** (디스패치 지연시간)이라 부르며, 대부분 context switch의 overhead에 해당
### Scheduling 성능평가
---
: scheduling 기법의 성능을 평가하기 위한 지표 <System 관점 지표/User 관점 지표>
- System 관점 지표
   - **CPU 이용률**(CPU utilization)
    : CPU가 일을 한 시간의 비율
   - **처리량**(throughput)
   : 주어진 시간동안 ready 큐에서 기다리고 있던 프로세스 중 몇 개를 끝마쳤는지 (CPU 버스트를 완료한 프로세스 수)
- User 관점 지표
   - **소요시간**(turnaround time)
    : CPU 요청 시점(Ready큐에서 대기) ~ CPU 버스트가 끝날때까지 (프로세스 종료가 아님!!!) 
   - **대기시간**(waiting time)
   : CPU 버스트 기간 중 프로세스가 ready 큐에서 CPU를 얻기 위해 기다린 시간의 합
   - **응답시간**(response time)
  : ready 큐에 들어온 후 처음으로 CPU를 획득하기까지 기다린 시간


### Scheduling Algorithm
---
- **선입선출 (Frist-Come First-Served: FCFS)**
 : 프로세스가 준비 큐에 도착한 시간 순서대로 CPU를 할당하는 방식, 비선점형
   - 단점: CPU 버스트가 긴 프로세스가 먼저 올 경우 CPU 버스트가 짧은 프로세스가 오랜 시간을 기다려야하는 Convoy effect가 일어난다.
  ![scheduling algorithm](https://i2.wp.com/sciencerack.com/wp-content/uploads/2018/12/fcfs-min.jpg?resize=352%2C297&ssl=1)
	해당 그림에서의 Average waiting time = (0 + 4 + 6) / 3 = 3.3
- **최단작업 우선 (Shortest-Job First: SJF)**
 : CPU 버스트가 가장 짧은 프로세스에게 먼저 CPU를 할당하는 방식
   - 프로세스가 ready 큐에서 기다리는 전체적인 시간이 줄어들어, 평균 대기시간을 가장 짧게 만드는 최적 알고리즘(optimal algorithm) 이다.
   - 비선점형(nonpreemptive) 방식: CPU를 스스로 반납하기 전까지는 빼앗기지 않는 방식
   ![scheduling algorithm](https://i0.wp.com/sciencerack.com/wp-content/uploads/2018/12/SJF-min.jpg?resize=372%2C309&ssl=1)
  - 선점형(preemptive) 방식: 진행중인 프로세스의 남은 CPU 버스트 시간보다 더 짧은 CPU 버스트 시간을 가지는 프로세스가 도착할 경우, CPU를 빼앗고 해당 CPU에게 할당시켜주는 방식이다. SRTF(Shortest Remaining Time First)라고도 부른다.
  
      ![CPU Scheduling Basic Concepts Scheduling Criteria - ppt video online  download](https://slideplayer.com/slide/5264072/16/images/18/Example+for+Preemptive+SJF+%28SRTF%29.jpg)

  - SJF에서의 문제점은 *CPU 버스트 시간을 미리 알 수 없다*는 것이다. 그래서 예측을 통해 CPU 버스트 시간을 구하고, 그 예측한 값중에서 가장 작은 값을 지니는 프로세스에게 할당한다.
    > (n+1) 번째 CPU 버스터의 예측시간 $T_{n+1}$은 $$T_{n+1}  = at_n + (1 - a)T_n$$
    $t_n$: n번째 **실제** CPU 버스트 시간 $T_n$: n번째 **예측** CPU 버스트 시간
    $a$: 0~1 사이 상수, 두 요소를 조절하는 매개변수(parameter)
    $T_n=at_{n-1} + (1 - a)T_{n-1}$이고, $T_n$의 자리에 넣는 방식으로 계산하다보면
    $$T_{n+1}  = at_n + (1 - a)at_{n-1} +  ... + (1-a)^jat_{n-j} + ...$$
    $a$와 $1-a$은  

- 우선순위 (Priority)
    ![scheduling algorithm](https://i0.wp.com/sciencerack.com/wp-content/uploads/2018/12/prrs-min.jpg?resize=300%2C252&ssl=1)
- 라운드 로빈 (Round Robin)
  ![scheduling algorithm](https://i0.wp.com/sciencerack.com/wp-content/uploads/2018/12/rr-min.jpg?resize=315%2C313&ssl=1)