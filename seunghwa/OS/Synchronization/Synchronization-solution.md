<<<<<<< .merge_file_mJ3yax
# Synchronization solution

## 소프트웨어적 해결
### Peterson's 알고리즘
```C
//공유 데이터 영역
flag[0] = false;
flag[1] = false;
turn = 0;

//P1
flag[0] = true;
while(flag[1] == true){
  if(turn == 1){
    flag[0] = false;
    while(turn == 1); //turn이 1일 경우에는 무한정 대기
    flag[0] = true;
  }
}
/*임계영역*/
turn = 1;
flag[0] = false;

//P2
flag[1] = true;
while(flag[0] == true){
  if(turn == 0){
    flag[1] = false;
    while(turn == 0); //turn이 0일 경우에는 무한정 대기
    flag[1] = true;
  }
}
/*임계영역*/
turn = 0;
flag[1] = false;
```

### 피터슨 알고리즘
데커와 아이젠버그와 맥과이어의 알고리즘등...있지만  
동시성 문제가 존재하는 피터슨 알고리즘을 중점적으로 보는 이유는  
개념적으로 완벽하며 알고리즘적으로 설명이 잘 되어있다  
**장점**
- 특별한 하드웨어 명령문이 필요없다
- 임계영역에 들어갈려는 프로세스를 기다리게 하지 않는다

## 하드웨어적 해결
소프트웨어적으로 해결할려고하면 알고리즘도 복잡하여지고 오류도 발생하게 되지만  
하드웨어적으로 지원을 하면 상대적으로 오류도 덜나고 좀 더 간단하게 해결이 가능하다

### TestAndSet atomic variables
메모리영역의 값에대해 원자적으로 연산을 수행할 수 있는 TestAndSet을 이용하는 것이다  
lock이라는 변수를 TestAndSet으로 넘김으로써 true면 대기 false면 실행으로 분기된다  
하지만 2개 이상의 프로세스가 접근한다고 했을 때 기아상태와 교착상태가 발생할 수 있다

**장점**
- lock변수 수에 상관없이 구현할 수 있다
- 구현이 단순하고 확인이 쉽다

**단점**
- 프로세서 시간소모가 크다
- 기아 상태 발생
- 교착 상태 발생

## 세마포어와 뮤텍스

## 모니터
=======
# Synchronization-solution
이번에는 OS kernel에서 지원해주는 방법으로 어떻게 해결하는지 알아보도록 한다

## Mutex Locks
Mutex (mutual exclustion) 즉 상호배제를 잠그는 형식으로 사용된다는 것이다  
`Mutex Lock`은 2개의 프로세스만 다루는 방식이다  
여기서는 `acquire()`와 `releases()` 두가지만 사용함으로써 해결한다  
**흐름**  
`acquire() -> critical section -> releases()` 순서로 이루어진다  
available이라는 부울 변수를 들어갈때는 false로 해서 다른 프로세스가 진입을 못하도록 막고  
releases를 할때는 available을 true로 바꿈으로써 해결한다  
```c
acquire() {
  while(!available);
  //busy waiting
  available = false;
}

//critical section

releases() {
  available = true;
}
```

### Busy Waiting 문제
acquire라는 함수를 실행할 때 available이 true로 바뀔때까지 무한 루프를 돌게된다  
하지만 코어가 하나만 존재하는 프로세서라면 해당 프로세스가 프로세서의 자원을 낭비한다고 볼 수 있다  
이 부분이 Mutex lock의 주된 문제라고 볼 수 있다  
하지만 코어가 여러개가 존재하게 된다면  
`Busy Waiting`이라는 것은 오히려 context switch를 발생하지 않기 때문에  
오버헤드가 발생하지 않는 장점으로 바뀌기도 한다  

## Semaphores
`Mutex Lock`에서는 2개의 프로세스를 다루는 방식이였다면 `Semaphores`에서는 2개 이상의 프로세스를 다루는 방식이다  
세마포어는 신호장치라는 말인데 N이라는 임의의 값을 줌으로써 해당 값이 남아있다면  
들어올 수 있다라는 신호를 값이 없다면 들어올 수 없다라는 신호를 준다  
```c
wait(s) {
  while(s <= 0);
  //busy waiting
  s--
}

signal(s) {
  s++;
}
```
위에 코드에서 볼 수 있듯이  
s값이 남아있다면 critical section으로 들어갈 수 있다  
s값이 없다면은 들어갈 수 없이 무한대기를 해야한다  

s값을 설정하는 기준은 현재 가용할 수 있는 자원의 개수를 표시한다  
이용할 수 있는 자원이 3개가 존재한다면 s값을 3으로 주면된다  

### busy waiting
Mutex Locks와 같이 Semaphores도 busy waiting문제가 발생한다  
위에서는 언급하지 않았지만 이문제는 waiting queue와 ready queue를 이용하여 해결 가능하다  
busy waiting대신에 waiting queue로 들어간다  
그다음 진입 가능하게 되면 ready queue로 들어가서 차례를 기다린다  

>>>>>>> .merge_file_jJFhcw
