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

### 메모리 관리 용어
---
- **동적로딩(Dynamic Loading)**  
 : 메모리를 효율적으로 사용하기 위해 프로세스가 시작될 때 전부 적재하는 것이 아닌 *실행에 필요한 부분만 메모리에 적재*하는 것
     - OS 지원 없이 프로그램 자체에서도 구현 가능, OS의 라이브러리도 이용 가능
- **동적연결(Dynamic Linking)**
  Linking? : 소스 코드를 컴파일하여 생성된 목적 파일(Object file)과 이미 컴파일된 라이브러리 파일(library file)들을 묶어서 하나의 실행파일을 생성하는 과정
  Dynamic Linking? : *연결을 프로그램 실행 시점*까지 지연시킴 (<-> static linking  코드와 라이브러리 코드가 모두 합쳐져서 실행파일 생성, 메모리 낭비)
    -  실행파일의 라이브러리 호출 부분에 해당 라이브러리 위치를 찾기위한 스텁(stub) 코드를 둠
       > 라이브러리 호출시
       > 1-stub을 참조하여 이미 메모리에 존재하면 직접참조
       > 2-없으면 디스크에서 동적 라이브러리를 찾아 메모리에 적재 후 수행
     - OS 지원 필요
- **중첩(Overlays)**
  : 프로세스의 *주소 공간을 분할해 실제 필요한 부분만 메모리에 적재*
   > 동적 로딩과 *개념은 유사하나 사용하는 이유는 다르다.*
   > 중첩은 물리적 메모리의 크기 제약으로 하나의 프로세스조차도 메모리에 한꺼번에 올릴 수 없을때 주소공간을 분할해서 당장 필요한 일부분을 메모리에 올려서 실행하는 기법이고, 해당 부분의 실행이 끝나면 나머지 부분을 올려 실행한다. 즉 프로그램의 크기가 물리적 메모리 크기에 비해 작다면 주소공간 전체를 한꺼번에 올릴 수 있지만, 그렇지 않으면 분할해 올리는 것이다.
   > 동적 로딩에서는 다중프로그래밍 환경에서 *메모리의 이용률을 향상*시키기 위해 주소공간중 당장 실행에 필요한 부분을 그때그때 메모리에 올린다는 점에서 중첩과는 다르다. 메모리에 더 많은 프로세스를 동시에 올려놓고 실행, 중첩은 단일 프로세스만을 메모리에 올려놓는 환경에서 메모리 용량보다 큰 프로세스를 실행하기 위한 어쩔 수 없는 선택이다.
   - 프로그래머에 의해 *직접 구현* (수작업 중첩, manual overlays라고 부름)
  
- **스와핑(Swapping)**
: 메모리에 올라온 프로세스 주소 공간 전체를 일시적으로 스왑아웃(swap out, 디스크의 swap area (=backing store)로 보내는것) 하는 것  
    
    ![OS 스와핑의 예 이미지 검색결과](https://img1.daumcdn.net/thumb/R720x0.q80/?scode=mtistory2&fname=http%3A%2F%2Fcfile29.uf.tistory.com%2Fimage%2F99D56D385C74261A04E7B6)
  - swapping 방향에 따라 디스크 -> 메모리 swap in, 메모리 -> 디스크 swap out
  - swapper로 불리는 중기 스케줄러(medium-term scheduler)에 의해 결정
  - 메모리에 존재하는 프로세스 수, 즉 다중 프로그래밍의 정도(degree of multiprogramming) 조절
  - 다시 swap in 될 때의 위치 
   : 컴파일 타임 바인딩과 로드 타임 바인딩에서는 원래 존재하던 메모리 위치로 올라가야하나, 실행시간 바인딩에서는 아무 곳에나 프로세스를 올릴 수 있다.
  - 소요시간
   : 스왑영역에 주소공간이 순차적으로 저장, 고로 디스크의 탐색시간(seek time)이나 회전지연시간(rotational latency)보다는 실제 데이터를 읽고 쓰는 전송시간(transfer time)이 대부분을 차지
	  

### 물리적 메모리의 할당 방식
---
물리적 메모리는 OS 상주영역/사용자 프로세스 영역으로 구분
 - OS 상주영역
   : interrupt vector와 함께 낮은 주소 영역 사용, OS의 kernel이 해당
 - 사용자 프로세스 영역
   : 높은 주소, 사용자 프로세스들이 적재
   
이 중에서 사용자 프로세스 영역의 관리방법을 살펴본다.  

**1.  연속 할당(contiguous allocation) 방식**
: 물리적 메모리의 연속적인 공간, 즉 메모리를 다수의 분할로 나누어 1분할 1프로세스 적재
  - **고정 분할 방식 (fixed partition allocation)**
    :주어진 개수만큼의 영구적인 분할(partition)로 나누어 프로세스를 적재
       - 외부조각 (external fragmentation)
         :프로그램 크기보다 분할 크기가 작아 분할이 비어있어도 적재하지 못하는 메모리 공간
        ![external fragmentation 이미지 검색결과](https://prepinsta.com/wp-content/uploads/2019/01/External-Fragmentation.png)
       - 내부조각 (internal fragmentation)
         :프로그램 크기보다 분할 크기가 커서 프로그램을 적재하고도 남는 메모리 공간
        ![external fragmentation 이미지 검색결과](https://prepinsta.com/wp-content/uploads/2019/01/Internal-Fragmentation.png)
  - **가변 분할 방식 (variable partition allocation)**
    - 크기 변동이 가능하므로 내부조각은 발생하지 않으나 메모리에 있던 프로그램 종료시 중간에 빈 공간이 생기며 이 공간이 새로 시작하는 프로그램보다 작으면 외부조각 발생
    >중요 쟁점: **동적 메모리 할당 문제(dymamic storage-allocation problem)**
     <*주소공간의 크기가 n인 프로세스를 적재할때 가용 공간중 어떤 위치에 올릴 것인가?*>
     가용공간? 사용되지 않은 메모리 공간, 메모리 내 여러 곳에 존재
     (OS는 이미 사용중인 메모리 공간과 가용공간에 대한 정보를 각각 유지중)
     >
     >해결방법 세가지
     > - 1_최초적합(first-fit)  
     : 크기가 n 이상인 가용 공간 중 가장 먼저 찾은 곳에 프로세스 할당(시간효율)
     > - 2_ 최적적합(best-fit)  
     : 크기가 n 이상인 가장 작은 공간을 찾아 할당(오버헤드)
     > - 3_최악적합(worst-fit)
     : 가용공간 중 가장 크기가 큰 곳에 할당(오버헤드, 큰 프로그램 담을 공간 적어짐)
     
     > Compaction?  
     : 물리적 메모리 중에서 프로세스에 의해 사용중인 메모리 영역을 한쪽으로 몰고 가용 공간을 다른 한쪽으로 모아서 하나의 큰 가용 공간을 만드는 방법  
     외부 조각을 해결할 수는 있겠지만 비용이 매우 多, 실행시간 바인딩에서만 가능

 #### **2.  불연속 할당(noncontiguous allocation) 기법**  
: 하나의 프로세스를 물리적 메모리의 여러 영역에 분산해 적재하는 방식  
페이징, 세그멘테이션, 페이지드 세그멘테이션 기법 등이 존재  

  **2-1. 페이징 기법**  
  : 프로세스의 주소 공간을 동일한 크기의 *페이지(page)*  단위로 나누어 물리적 메모리의 서로 다른 위치에 페이지들을 저장하는 방식
  일부는 백킹 스토어, 일부는 물리 메모리에 혼재 가능
   물리적 메모리를 페이지와 크기가 같은*프레임(frame)* 단위로 나누어둠
     > 메모리에 올리는 페이지의 크기와 동일하므로 어디에 올려도 똑같기 때문에 동적할당 문제는 일어나지 않음.
     
  - 페이지 테이블과 주소 변환
              ![페이지 테이블을 이용한 주소 변환 이미지 검색결과](https://blog.kakaocdn.net/dn/cbhG2a/btqDyMQyDS6/xvfb2hsFMTVQe1RLK67K5k/img.png)
    
    모든 프로세스가 각각의 주소 변환을 위한 *페이지 테이블(page table)* 을 가짐
    > Page Table?
    > 물리적 메모리에 위치
    > CPU에서 실행중인 페이지 테이블에 접근하기 위해서 OS에서 page-table base register (테이블의 시작위치 가리킴)와 page-table length register(테이블의 크기 보관) 사용
    
    CPU가 사용하는 논리적 주소를 페이지 번호(p)와 페이지 오프셋(d)로 나누어 주소 변환에 사용
    > *p*: page table 접근 index, 해당 entry에는 page의 base address(f) 저장
    > *d*: page 내의 변위(displacement), base address + 변위를 더하여 물리 메모리 상의 주소(물리적 주소)를 얻어냄
    
    메모리 접근 연산은 page table 접근 1 + 변환 주소에서 실제 데이터로 접근 1 로 구성되어있으므로 overhead 고려
    -> 이를 위해 *TLB(Translation Look-aside Buffer)* 사용  
    ![tlb에 의한 페이징 기법의 주소 변환 이미지 검색결과](https://blog.kakaocdn.net/dn/Wq8Bt/btqDJgw11i7/TQ5egPOteEpm3pcvkVle51/img.png)
    > **TLB**?
    > 고속의 주소 변환용 하드웨어 캐시
    > 빈번히 참조되는 페이지의 주소 변환 정보를 담음
    > 프로세스별로 담고있는 TLB의 내용이 다르므로 context switch시 내용을 지워야함
    > - page table
    >    - 모든 page의 정보가 순차로 담김 p  == 페이지 번호 -> page table 시작 위치에서 p만큼 떨어진 항목
    >     -  f에 빠르게 접근 가능  
    > - TLB
    >    -  모든 페이지x, (page 번호,  프레임 번호) pair로 저장
    >   -   찾으려는 페이지 정보가 TLB에 있는지 찾기위해 모든 항목(entry) 조사 overhead 
     -> 이를 위해선 병렬탐색(parelle search) 가능한 연관 레지스터(associative register) 사용
    
     평균 메모리 접근 시간
      $$EAT = (1+)a $$
  - 계층적 페이징
     32bit 주소체계는 $2^{32}$byte (=4GB)의 주소공간을 갖는 프로그램이 지원 가능하다.
     이 때, 페이지의 크기가 4KB라면, 페이지 테이블의 크기는? (페이지 항목당 4byte 필요)
      > 페이지는 총  4GB/4KB = 1M 개이며, 이는 페이지 테이블의 항목의 수와 동일하다.
        (참고:  $2^{10} = K, 2^{20} = M, 2^{30} = G$ )
        각 페이지 항목이 4byte씩 필요하므로 1M X 4byte = 4MB
       
       그렇다면  
        
  - 역페이지 테이블
  - 공유 페이지
  - 메모리 보호

  **2-2. 세그멘테이션**  
  :
  
  **2-3. 페이지드 세그멘테이션**
  **2-2. 세그멘테이션**  
  :
  
  **2-3. 페이지드 세그멘테이션**
