## 4장 - 프로그램의 구조와 실행
### 컴퓨터 시스템의 작동 개요
---
- System의 동작은 CPU에서의 명령(instruction) 수행 + 입출력 장치와의 입출력으로 구성된다.
- System의 하드웨어는 CPU와 메모리, 그리고 입출력 장치와 그의 전담 CPU와 메모리(controller와 local buffer)로 구성된다.
- CPU는 매 시점 메모리의 특정 주소에 존재하는 명령을 하나씩 읽어와 그대로 실행한다. 이러한 실행해야할 메모리 주소를 담고있는 Register를 **프로그램 카운터(Program Counter, PC)** 이라 부르며, CPU는 이 PC가 가리키는 메모리 위치의 명령을 처리한다.
- PC가 가리키는 영역이 OS라면 kernel mode에서 코드를 수행중인 것이고, 프로그램을 가리키면 user mode로 프로그램의 코드를 수행

### 프로그램의 구조와 실행
---
- 프로그램이 CPU에서 명령을 수행하려면 해당 instruction을 담은 프로그램의 **주소 공간**이 메모리에 올라가있어야한다.
> **주소 공간**  
> 코드(code), 데이터(data), 스택(stack) 영역으로 구분  
> - 코드: 프로그램 함수들의 코드가 CPU에서 수행할 수 있는 기계어 명령(machine instruction) 형태로 변환되어 저장  
> - 데이터: 전역변수 등 프로그램이 사용하는 데이터를 저장하는 부분
> - 스택: 함수 호출될 떄 호출된 함수의 수행을 마치고 복귀할 주소 및 데이터를 임시 저장  
> -함수1 -> 함수2를 호출 할 때 함수2 수행 후에는 함수1로 복귀를 해야하는데, 그 때의 위치를 저장해주는걸 의미 (interrupt에서 PCB에 저장해주는 것과 유사)  
>
> **OS의 주소 공간**도 마찬가지다.  
![image](https://user-images.githubusercontent.com/59992230/105607368-8f694e00-5de1-11eb-9b3d-8e714af45432.png)
> - 코드: 하드웨어 자원 관리, 사용자에게 편리 인터페이스 제공, system call과 interrupt를 처리할 수 있는 코드들
> - 데이터: 자원관리를 위한 자료구조 이는 하드웨어 용과 수행 프로그램(=process)용 (PCB)이 존재
> - 스택: process와는 별도 stack이 존재 why?   
-1) system call 내부에서 함수 호출시 복귀 주소가 커널 내 주소여야하며  
-2) 모든 User program이 system call을 이용해 커널 함수에 접근이 가능하므로, 일관성 유지를 위해  
> - 다시 한 번 정리해보자면,  
  process가 자기 코드 내에서 함수 호출 후 복귀는 **자신 주소공간의 stack** 으로,  
  process -> OS 일땐 **PCB**에 저장 후 복귀,  
  OS내의 함수 호출 후 복귀는 **OS의 process별 stack**  
>
> 주소 공간은 프로그램마다 별도로 존재하고, 이를 **가상 메모리(virtual memory)** 혹은 **논리적 메모리(logical memory)** 라고 부른다. 
>![image](https://user-images.githubusercontent.com/59992230/105607258-18cc5080-5de1-11eb-8649-ef6a99bd9a98.png) 

- 프로그램은 어떠한 PL로 작성되었든 그 내부구조는 **함수**들로 구성되어있다.

> **함수**  
>함수는 사용자 정의 함수, 라이브러리 함수, 커널 함수 세 가지로 구분된다.  
>사용자 정의함수와 라이브러리 함수는 프로그램의 코드영역에, 커널 함수는 커널의 코드에 정의되어있다.  
>입출력을 사용해야하는 상황에서는 사용자 프로그램에서 커널 함수를 호출해야한다. 다음은 printf()의 예시
![image](https://user-images.githubusercontent.com/59992230/105608269-57183e80-5de6-11eb-8c8b-b6d7155727fb.png)
*(참고: https://medium.com/pocs/%EB%A6%AC%EB%88%85%EC%8A%A4-%EC%BB%A4%EB%84%90-%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C-%EA%B0%95%EC%9D%98%EB%85%B8%ED%8A%B8-2-78406a13c5c9)*

### Interrupt 처리
---
- interrupt 처리중에는 다른 interrupt의 발생을 허용하지 않아야한다. 데이터의 일관성을 유지하기 위해서다.
- 그러나 먼저 처리해줘야하는 interrupt가 올 수도 있을 것이다. 급하게 처리해야하는 예외처리 등을 위해 **우선순위** 를 부여하여 높은 우선순위의 interrupt가 들어왔을 땐 먼저 처리해주고, 다시 해당 interrupt의 진행으로 돌아오게 된다.
- process에서 CPU 점유를 빼앗기는 경우는 time에 의한 interrupt, 입출력 요청을 위해 system call을 호출하는 두 가지로 나뉠 수 있다.
- process가 완료될때까지 자신의 코드만 실행하는 것이 아니라 커널의 코드도 실행한다. 자신의 주소공간에서 실행되는 상태를 **user mode running**, system call 함수를 실행하는 **kernel mode running**라 부른다. CPU를 커널에게 빼앗겨도 여전히 해당 process의 실행 상태로 간주하며, kernel mode에서 실행한다고 부른다.