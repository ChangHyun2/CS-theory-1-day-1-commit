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

## 