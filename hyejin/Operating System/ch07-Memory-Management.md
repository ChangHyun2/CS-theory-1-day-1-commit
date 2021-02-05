## 7장 - 메모리 관리

### 메모리 저장 단위와 메모리 크기 표시 단위
---
*참고 블로그 : https://blog.naver.com/tipsware/221537443580 , https://thrillfighter.tistory.com/116*
- 비트(bit)와 바이트(Byte)  
: 메모리에 데이터를 저장할 때 사용하는 최소 단위는 비트(bit)이나, 연산 장치나 메모리는 기본 단위를 비트가 아닌 8개의 비트를 그룹 지은 바이트(byte) 단위로 관리
  > 왜 비트 단위로 관리하지 않지?  
    비트로 관리시 명령이 너무 세분화되어있음. 예로 40+30 연산시 40과 30을 각각 bit로 101000, 11110으로 변경하고 비트 단위별로 연산을 진행해줘야하는 불편함 때문
  - 컴퓨터에서는 byte 단위로 메모리 주소를 부여
- 메모리 크기 표시 단위
![메모리 저장 단위와 메모리 크기 표시 단위 : 네이버 블로그](https://lh3.googleusercontent.com/proxy/hJeWGc5qoTPUDJq6S0-cu9iEH8BU2voihOHAn0SA5UgtXz7qdBJbR3iucQtyydGBvcO0Rii1CdAILMZtEnQbwpMNQrrqSIqnyKg37rWWhnnd9AtxVRObp8UwIkQ3C_btXHXZCKXNyL68muGCIlQjKjWMawalMcv9RF9cCV4Gi2ysTWFmMJq-JhhZx1FQ96QSWlJG4a68ccgE0tAm62wpPGfSGTPJbxuXzYHqL451cIcUQlbR_dj5j4dfybruAps28zfIQ1N_KjpSmSszvDj0GfTnx6Ta9xjBoeZGmZxfQ3gb61U9kxlNEHSN)
  **메모리에서는 1Byte 크기로 주소(Address)를 부여 == 운영체제의 기본 처리 단위**  
    - 메모리의 첫 Byte를 0번지, 다음 Byte를 1번지 등등
    - 32비트 운영체제는 *주소 데이터를 32비트 크기*의 메모리에 저장해서 관리하므로 $2^32$가지의 주소공간 사용 가능
    - 주소공간 하나당 크기는 1Byte이므로 메모리의 용량은 $2^32$Byte이다.
    > 주소 1개당 1Byte의 메모리에 접근할 수 있음, 주소 $2^32$개 있음  
    -> 접근 가능, 즉 메모리 공간에 address할 수 있는, 할당할 수 있는 주소는 $2^32$Byte
### 주소 바인딩
---
CPU는 프로세스마다 독립적으로 갖는 논리적 주소(0번지부터 시작)에 근거해 명령을 실행하고, 그에 해당하는 물리 메모리에 실제로 올라가는 물리적 주소가 어디에 매핑되는지 확인해야한다. 이처럼 논리->물리 주소로 연결시켜주는 작업을 **주소 바인딩(address binding)** 이라고 한다.    
방식은 프로그램이 적재되는 물리적 메모리가 **결정되는 시기**로 분류 
 - **컴파일 타임 바인딩** (compile time binding)  
 : 컴파일 시점에 물리 메모리의 몇 번지에 위치할지 결정, 절대주소로 적재된다는 의미에서 절대코드(absolute code)를 생성하는 바인딩이라고도 부름
   - 물리 메모리 위치를 변경하고 싶다면 다시 컴파일해야하는 번거로움

 - **로드 타임 바인딩** (load time binding)  
 : 프로그램의 실행이 시작될때 물리적 주소가 결정
   - 로더(loader)의 책임하에 물리적 주소가 부여, 종료될때까지 위치 고정
   - 컴파일러가 재배치 가능 코드(relocatable code)를 생성해야 가능
 - **실행시간 바인딩** (execution time binding, run time binding)  
: 프로그램 실행 시작 후에도 물리적 주소가 변경될 수 있으며, CPU가 주소를 참조할 때마다 해당 데이터가 물리적 어느 위치에 존재하는지를 **주소 매핑 테이블(Address mapping table)** 을 이용해 바인딩을 점검해야함
   > **MMU**(Memory Management Unit: 메모리 관리 유닛): 논리 주소를 물리 주소로 매핑해주는 하드웨어 장치  
   **MMU 기법(scheme)**  
   : 해당 주소값 + 기준 레지스터 값(재배치 레지스터, relocation register) = 물리 주소값
    ![mmu scheme 이미지 검색결과](https://img1.daumcdn.net/thumb/R800x0/?scode=mtistory2&fname=https%3A%2F%2Ft1.daumcdn.net%2Fcfile%2Ftistory%2F2134D4355752F6AB1D)
    >  - 단, MMU 기법은 프로그램의 주소 공간이 물리적 메모리의 한 장소에 연속적으로 적재되는 것으로 가정
    > 여기서 logical address는 기준 레지스터값으로부터 요청 위치가 얼마나 떨어져있는지 **offset** 개념
    >
    > 프로세스마다 고유의 주소공간을 가지고 있어서, 동일한 주소값이어도 각 프로세스마다 다른 내용을 담고있다. 100번지라고 해도 서울시 동작구의 100번지인지, 대구 수성구의 100번지인지 서로 다를 수 있다.  
    MMU 기법에서는 context switching으로 CPU에서 수행중인 프로세스가 바뀔때마다 재배치 레지스터의 값을 매번 바꿔주어 하나의 물리 메모리 내에 여러 프로세스가 올라와있을때 프로세스별 논리적 주소를 
    물리 주소로 매핑할 수 있게 도와줌  
    >- 메모리 보안(memory protection)
### 메모리 관리와 관련된 용어
---
### 물리적 메모리의 할당 방식
---
### 페이징 기법
---
### 세그멘테이션
---