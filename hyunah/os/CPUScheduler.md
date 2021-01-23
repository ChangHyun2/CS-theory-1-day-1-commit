# [OS] CPU 스케줄러

> CPU 스케줄러란 ready queue에 들어있는 프로세스들의 CPU 점유 순서를 정하는 알고리즘이다.

## CPU 스케줄러

-   이번에 얘기하는 CPU 스케줄러는 저번 포스팅에서 언급했던 ready queue에 있는 프로세스들의 CPU 점유 순서를 정하는 알고리즘을 말함
-   오늘은 이 CPU 스케줄러의 종류에 대해 좀더 자세히 알아보고자 함

---

> CPU 스케줄러는 크게 선점형, 비선점형으로 나뉜다.

## 비선점형(Non-preemptive) 스케줄링

-   이미 할당된 CPU를 다른 프로세스가 강제로 빼앗아 사용할 수 없는 스케줄링 기법
-   프로세스가 CPU를 할당받으면 해당 프로세스가 완료될 때까지 CPU를 사용

## 선점형(Preemptive) 스케줄링

-   프로세스가 CPU를 점유하고 있는 동안 I/O나 인터럽트가 발생한 것도 아니고 모든 작업을 끝내지도 않았는데 다른 프로세스가 해당 CPU를 강제로 점유할 수 있는 스케줄링 기법

---

## FCFS(First Come First Served)

-   ready queue에 먼저온 프로세스를 먼저 처리하는 방식
-   Non-preemptive
-   장점: 도착 순서에 따라 공평
-   단점: Convoy effect 소요시간이 긴 프로세스가 먼저 도달하면 효율성이 떨어짐

## SJF(Shortest Job First)

-   실행시간이 가장 짧은 프로세스가 먼저 CPU를 할당하는 방식
-   가장 적은 평균 대기 시간을 제공하는 최적의 알고리즘
-   None-preemptive
-   단점
    -   Starvation 실행시간이 긴 프로세스는 CPU를 할당받지 못하고 무한히 대기하는 현상 발생
    -   비현실적. CPU 점유 시간을 미리 알 수 없음

## Priority Scheduling

-   우선순위가 가장 높은 프로세스에게 CPU를 할당하는 스케줄링
-   Preemptive 방식: 더 높은 우선순위의 프로세스가 도착하면 실행중인 프로세스를 멈취고 CPU를 선점
-   Non-Preemptive 방식: 더 높은 우선순위의 프로세스가 도착하면 ready queue의 head에 넣음
-   단점: Starvation, Indefinite blocking
-   해결책: Aging 우선순위가 낮아 CPU를 선점하지 못하는 프로세스라도 오래 기다리면 우선순위를 높여줌

## Round Robin

-   현대적인 CPU 스케줄링
-   각 프로세스는 동일한 크기의 할당 시간(time quantum)을 가짐
-   할당 시간이 지나면 프로세스는 선점당하고 ready queue의 제일 뒤에 가서 다시 줄을 섬
-   Round Robin은 CPU 사용시간이 랜덤한 프로세스들이 섞여있을 때 효율적
-   프로세스의 context를 저장할 수 있기 때문에 가능
-   단점: 설정한 time quantum이 너무 커지면 FCFS와 같아지고 너무 작아지면 잦은 context switch로 overhead가 커지기 때문에 적당한 정도를 설정하는 것이 중요
-   장점
    -   Response time이 빨라짐
    -   공정한 스케줄링
