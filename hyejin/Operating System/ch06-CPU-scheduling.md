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
: scheduling 기법의 성능을 평가하기 위한 지표 <System 관점 지표/User 관점 지표>
- System 관점 지표
   -  CPU 이용률(CPU utilization)
   - 처리량(throughput)
- User 관점 지표
   - 소요시간(turnaround time)
   - 대기시간(waiting time)
   - 응답시간(response time)