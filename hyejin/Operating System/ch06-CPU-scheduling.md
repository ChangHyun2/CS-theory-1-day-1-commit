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
### Scheduling 성능평가 지표
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
    $a$와 $1-a$은 곱해질수록 작아지므로, $t_{n-1}$의 계수는 $t_{n}$보다 작은 값이 되고, 점점 이전의 실제 CPU 버스트 시간이 기여하는 값이 작아진다.

- **우선순위 (Priority)**
 : 우선순위가 가장 높은 프로세스에게 먼저 CPU를 할당
  - 우선순위를 CPU 버스트 시간으로 두면, SJF와 동일한 의미
   - 선점형: CPU에서 수행 중인 프로세스보다 우선순위가 높은 프로세스가 도착하면 CPU를 빼앗고 할당시켜줌
   - 비선점형: 우선순위가 높은 프로세스가 오더라도 CPU 자진반납 후 할당
   ![scheduling algorithm](https://i0.wp.com/sciencerack.com/wp-content/uploads/2018/12/prrs-min.jpg?resize=300%2C252&ssl=1)

    - starvation에 대비한 aging 기법 이용 (기다린 시간 ↑ -> 우선순위 ↑) 
  
  
- **라운드 로빈 (Round Robin)**
   - 시분할 성질을 가장 잘 이용 
   - 각 프로세스가 CPU 최대 사용 시간(할당시간, time quantum) 제한
   ![scheduling algorithm](https://i0.wp.com/sciencerack.com/wp-content/uploads/2018/12/rr-min.jpg?resize=315%2C313&ssl=1)
     
   - 이질적인 프로세스가 같이 실행될때 효과적이고, *CPU 버스트 시간*과 프로세스의 *대기시간*이 비례한다.
     > $n$개의 프로세스가 ready queue에서, 할당시간이 $q$일때
      모든 프로세스는 $(n-1)q$시간 이내에 적어도 한 번 CPU를 할당받을 수 있다.
       -> 이런 방식은 대화형 프로세스에서 빠른 응답을, 긴 프로세스에서도 불이익 없이 할당이 가능하다. 
   - 할당 시간 ↓ -> context switch (문맥교환) ↑
   - 다른 알고리즘과의 비교
     - SJF의 경우엔 평균 대기시간에선 우수하나 But CPU 버스트 시간이 짧은 프로세스에만 유리하고 긴 프로세스는 불리한 반면,
     R.R은 CPU 버스트 시간에 대기시간 뿐만 아니라 소요시간도 비례하므로 매우 공정
      > R.R : CPU 버스트 시간이 1초인 프로세스가 작업을 완료하기까지 10초가 걸렸으면, CPU 버스트가 10초인 프로세스는 10배인 100초가 걸릴 것이다. 
        SJF: 버스트시간 1초는 10초에 끝나도, 10초인 프로세스는 앞에 더 짧은 CPU 버스트를 가진 프로세스가 계속 들어온다면 무한정 기다려야한다.
      - FCFS와의 비교
    : 버스트 시간이 거의 동일할때 R.R은 비효율적이나 대부분의 환경에선 제각각인 경우가 많으므로 합리적이다. 반면에 FCFS는 프로세스마다 편차가 매우 크다.
    
       > CPU 버스트 시간이 10인 프로세스 10개가 엇비슷하게 도착
        FCFS: CPU를$P_1, P_2, ... P_10$이 순서대로 사용하는 식이며,
          - 대기시간, 응답시간 : 0, 10, ... 90  평균: 45
          - 소요시간: 10, 20, ... 10 평균: 55
         R.R: (할당시간이 매우 짧다는 가정) 10개의 프로세스가 100이라는 시간에 거의 동시 종료
         - 대기시간:  평균 90, 평균 응답시간은 매우 짧음
         - 소요시간: 평균 100
 - **멀티레벨 큐(Multi-level Queue)**
  :Ready queue를 여러개로 분할하여 관리하며, process별 성격 맞춤 스케줄링이 가능하다.
   - 일반적으로 전위큐/후위큐 분할운영을 한다.
      - 전위큐(foreground queue): 응답시간을 짧게 하기 위해 Round robin 사용, 대화형 작업
      - 후위큐(background queue): context switch를 줄이기 위해 FCFS 사용, 계산위주 작업
   - 어떤 queue를 먼저 할당할지 *Queue scheduling 필요*
       - fixed priority scheduling: 고정된 우선 순위를 부여
       - time slice: 각 queue에서 CPU 시간을 적절한 비율로 할당 
    
           
![MODULE 5 - VIDEO 2 - MLQ and MLFQ CPU scheduling - YouTube](https://i.ytimg.com/vi/NmFpCJdLd1g/maxresdefault.jpg)
 
 
 - **멀티레벨 피드백 큐(Multilevel Feedback Queue)**
 : 멀티레벨에서 process queue가 이동이 가능한 알고리즘이다.
   - aging 기법을 이용할 수 있다.
   - queue의 수, queue scheduling, process를 상위 큐로 승격 혹은 하위큐로 강등, process 도착시 들어갈 queue 결정 기준 등을 고려야해야한다.
 ![Scheduling algorithms](https://image.slidesharecdn.com/csc4320chapter5-2-101203002830-phpapp01/95/scheduling-algorithms-29-728.jpg?cb=1291336136)
   - 상위의 큐일수록 높은 우선순위를 지니며, 작업시간이 빠른 큐는 높은 우선순위에서 작업을 완료할 수 있으며, 이후 할당시간으로도 작업이 완료되지 않는 CPU 처리가 긴 프로세스의 경우 FCFS 처리를 이용한다.
  (예제찾기)

- **다중처리기(Multi-processor)**
 : CPU가 여러개인 multi-processor system에서 처리하는 스케줄링
  - 처리할 수 있는 CPU가 여러개이므로 ready queue에서 알아서 꺼내어가도록 작업할 순 있겠지만, 특정 CPU에서 수행되어야하는 프로세스가 있는 경우엔 문제가 생긴다.
  - 이런 문제는 CPU별로 다른 준비줄을 세우는 방법을 생각해볼 수 있겠지만, 이번에는 일부 CPU에 작업이 편중될 수 있는 우려가 생긴다
  - 고로 이걸 방지하기 위해 CPU별 부하를 적절히 분산시키는 **부하균형(load balancing)**이 필요하다.
  
- **실시간 (real-time)**
 : 실시간 시스템(real-time system)에서는 작업마다 데드라인이 존재
  - 데드라인을 지키는 것이 우선이며, 데드라인이 얼마 남지 않은 요청을 우선 처리하는 EPF(Earlist Deadline First) 스케줄링을 널리 사용
  - 경성 실시간 시스템 (hard real-time system): 정해진 시간 안에 반드시 작업 완료되어야함(치명)
  - 연성 실시간 시스템 (soft real-time system): 데드라인이 존재하지만, 지켜지지 않았다고 위험한 상황이 발생하진 않는다. ex) 멀티미디어 스트리밍 시스템
### Scheduling 알고리즘 평가 방법
---
- 큐잉 모델(queueing model): 수학적 계산으로 성능 지표를 구함
- 시뮬레이션 모델(simulation model): 가상 스케줄링 프로그램을 작성하고 CPU 요청을 입력값으로 넣어 어떤 결과가 나오는지 확인하는 방법
  >입력값?
  >실제 시스템에서 CPU 요청 내역(트레이스, trace)을 추출해 사용
 - 구현 및 실측(implementation & measurement): OS의 커널 코드중 CPU scheduling을 수행하는 코드를 수정한 후 컴파일하여 시스템에 설치하고, 이후 동일 프로그램을 원래 커널과 수정 커널에서 수행시켜 보고 실행시간을 측정하여 알고리즘의 성능을 평가한다. 