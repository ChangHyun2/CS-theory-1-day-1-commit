# [OS] Process 동기화(1)

> Process 동기화란 여러 프로세스가 공유하는 자원의 일관성을 유지하는 것

## 임계구역(Critical Section) 문제

<pre><code>do {
    entry section
    	critical section
    exit section
    	remainder section
} while(TRUE);
</code></pre>

-   임계구역은 여러개의 프로세스가 수행되는 시스템에서 각 프로세스들이 공유하는 데이터를 변경하는 코드 영역을 말함
-   간단하게 말하면, A라는 변수를 2개의 프로세스가 공유한다고 해보자. 각 프로세스가 코드에서 A 값을 변경한다면 해당 코드는 임계구역이다.
-   임계구역을 해결하기 위해서 만족해야 하는 조건
    -   Mutual exclusion(상호배타): 임계구역에 오직 한 프로세스만 진입 가능
    -   Progress(진행): 임계구역에서 실행중인 프로세스가 없다면, 어느 프로세스가 들어갈 것인지 적절한 선택 필요
    -   Bounded waiting(유한대기): 기아 상태 방지를 위해, 한번 들어갔다 나온 프로세스는 다음에 들어갈 때 제한을 줌

## 임계구역(Critical Section) 문제 해결 방식

1. 피터슨 알고리즘 (Peterson's Algorithm)

-   flag, turn 변수를 사용
-   flag: 특정한 프로세스가 임계구역으로 들어갈 준비가 되었다는 것을 나타냄 (true, false)
-   turn: 임계구역으로 진입할 프로세스의 순번 (1, 2, ...)
-   Mutual exclusion, Progress, bounded waiting 모두 만족
<pre><code>// 프로세스 i 의 실행구조
do {
    flag[i] = true; // 프로세스 i가 임계구역에 들어갈 준비가 됨
    turn = j; // 프로세스 j가 실행될 차례
    while (flag[j] && turn == j); // 프로세스 j가 임계구역에 들어갈 준비가 됬는지 && 프로세스 j가 임계구역에 들어갈 차례인지
    	critical section // 프로세스 j가 임계구역 작업 마치고 flag[i]가 false가 되면 i는 무한루프 빠져나와 임계구역에 들어감
    flag[i] = false; // 프로세스 i가 작업 완료 후, flag[i] = false로 설정
        remainder section
} while (true);
</code></pre>

2. 뮤텍스 락 (Mutex Lock)

-   프로세스가 임계구역에 들어가기전에 lock을 획득하고, 나올때는 lock을 반환하는 방식
-   mutex lock에서는 available이라는 변수를 가지고, 이 available 변수를 가지고 lock의 가용 여부를 판단
-   단점: busy waiting (기다리면서 계속 반복 실행, CPU 시간 낭비)
<pre><code>do {
    acquire lock // lock이 가용하다면 acquire()를 호출해서 lock을 획득하고, 다른 프로세스가 접근하지 못하도록 lock은 사용불가 처리
        critical section
    release lock // lock을 반환
        remainder section
} while (true);

acquire() {
while (!available) /_ busy wait _/
available = false;
}

release() {
available = true;
}</code></pre>

3. 세마포어 (Semaphore)

-   카운팅 세마포어, 이진 세마포어가 있음.
-   이진 세마포어는 0, 1로 동작하고 mutex lock과 유사
-   카운팅 세마포어: 세마포어(S)는 프로세스가 임계구역에 들어가려할때, 즉 wait()을 호출할 때 값이 감소하고, 임계구역의 작업을 끝내고 lock을 반납할때(signal() 호출할때) 값이 증가. 만약 세마포어(S)가 0이 된다면 모든 자원들이 프로세스들에 의해 모두 사용중임을 의미. 이후 자원을 사용하려면 세마포어(S)가 0보다 커지기를 기다려야함.
<pre><code>wait(S) {
    while (S <= 0)
        /* busy wait */
    S--;
}

signal(S) {
S++;
}</code></pre>
