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