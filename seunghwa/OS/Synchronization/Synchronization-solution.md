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

