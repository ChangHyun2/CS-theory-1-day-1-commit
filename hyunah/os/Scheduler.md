# [OS] 스케줄러

> 여기서 스케줄러는 process 스케줄러를 말한다. 자원(CPU와 같은)들이 제한되어 있기 때문에 process들이 자원들을 어떤 순서로 쓸지 정한다.

# 스케줄러

-   스케줄링한다는 것은 여러 프로세스들에게 자원을 어떻게 나누어 줄것인지를 정하는 것
-   우선 프로세스의 상태에 대해 알아보자.
    -   New: 프로그램이 메인 메모리에 할당
    -   Ready: 할당된 프로그램이 초기화와 같은 작업을 통해 실행되기 위한 모든 준비를 마침
    -   Running: CPU가 해당 프로세스를 실행
    -   Waiting: 프로세스가 끝나지 않은 시점에서 I/O로 인해 CPU를 사용하지 않고 다른 작업을 함 (해당 작업이 끝나면 다시 CPU에 의해 실행되기 위해 ready 상태로 돌아감)
    -   Terminated: 프로세스 종료

![image](https://user-images.githubusercontent.com/42240771/105362292-11b90d00-5c3e-11eb-9d97-7e87d07b172d.png)

-   프로세스 상태가 변할때 일반적으로 여러개가 한번에 수행되므로 순서를 지킬 필요가 있다. 이러한 순서를 대기하는 곳을 queue라고 함
    _ Job Queue: 현재 시스템 내에 잇는 모든 프로세스의 집합, 하드디스크에 있는 프로그램이 실행되기 위해 메인 메모리의 할당 순서를 기다리는 큐
    _ Ready Queue: 현재 메모리 내에 있으면서 CPU를 잡아서 실행되기를 기다리는 프로세스의 집합 \* Device Queue: Device I/O 작업을 대기하고 있는 프로세스의 집합
    ![image](https://user-images.githubusercontent.com/42240771/105362821-b2a7c800-5c3e-11eb-9771-77f719eab8e1.png)

-   각각의 Queue가 순서를 기다리는 공간이라면 이 순서를 정해주는 알고리즘이 스케줄링이다.
    -   Job Queue -> Job Scheduler(Long-term scheduler)
        -   스케줄링이 발생하는 시간이 비교적 오래 걸림
        -   어떤 프로세스에 메모리를 할당하여 ready queue로 보낼지 결정
        -   메모리와 디스크 사이의 스케줄링을 담당
        -   프로세스에 메모리 및 각종 리소스를 할당
        -   실행중인 프로세스의 수 제어(degree of multiprogramming)
        -   프로세스의 상태 new -> ready
    -   Ready Queue -> CPU Scheduler(Short-term scheduler)
        -   스케줄링이 발생하는 시간이 비교적 짧게 걸림
        -   프로세스가 CPU를 점유하는 순서를 정해줌. 즉, CPU와 메모리 사이의 스케줄링 담당
        -   Ready Queue에 존재하는 프로세스 중 어떤 프로세스를 running 시킬지 결정
        -   프로세스에 CPU를 할당
        -   프로세스의 상태 ready -> running -> waiting -> ready
        -   현대의 컴퓨터가 여러 프로그램을 동시에 사용하는 것과 같은 효과를 주는 이유가 이 스케줄링 속도가 매우 빠르기 때문
    -   Swapper(Medium-term scheduler)
        -   여유 공간 마련을 위해 프로세스를 통째로 메모리에서 디스크로 쫒아냄(swapping)
        -   프로세스에게서 memory를 deallocate하고 하드디스크로 옮겨줌(swap out)
        -   프로세스가 다시 사용되려고 하면 하드디스크에서 메인 메모리에 할당(swap in)
        -   degree of Multiprogramming 제어
        -   현 시스템에서 메모리에 너무 많은 프로그램이 동시에 올라가는 것을 조절하는 스케줄러
        -   프로세스의 상태 ready -> suspended(stopped, 메모리에서 내려간 상태)
    -   Device Queue -> Device Scheduler
