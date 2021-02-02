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

### 메모리 관리와 관련된 용어
---
### 물리적 메모리의 할당 방식
---
### 페이징 기법
---
### 세그멘테이션
---