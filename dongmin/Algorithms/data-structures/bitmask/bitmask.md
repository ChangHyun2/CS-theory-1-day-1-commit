# 비트마스크
- 정수의 이진수 표현을 자료 구조로 쓰는 기법 = 비트 마스크
- 컴퓨터는 이진수를 사용하기 때문에 이진법 관련 연산들은 아주 빠르다.

### ➕이점

- 집합 연산을 반복문 없이 한 줄에 쓸 수 있다.
- 단순히 int[]로 map<vector<bool>, int>를 대체할 수 있다.
- 비트마스크 연산은 거의 O(1)에 구현 가능하다.
- 메모리를 효율적으로 사용할 수 있다.

### ⚠️주의

- &, |, ^ 등의 비트 연산자는 비교 연산자 == 나 ≠보다 낮다.
- 상수는 부호 있는 32비트 상수로 취급된다. → 부호 없는 64비트 비트마스크를 사용할 때 오버플로가 발생할 수 있다.

    ```cpp
    // example
    bool isBitSet(unsigned long long a, int b) {
    	return (a & (1 << b)) > 0;
    }

    // solution
    return (a & (1ull << b)) > 0;
    ```

- 부호 있는 정수형을 비트마스크로 사용하면 모든 비트를 전부 사용할 때 부호 비트가 켜지므로 자잘한 버그가 발생한다. → **부호 없는 정수형**을 쓰는 것이 안전하다.
- N비트 정수를 N비트 이상 왼쪽으로 시프트할 때, 연산의 결과가 0이 나오지 않는 예상 외의 결과가 나오므로 안쓰는 것이 좋다. → 혹은 직접 확인해서 쓰는 것이 좋다.

### 📌활용

- 집합의 구현
    - N비트 정수 변수 := 0부터 N-1까지의 정수 원소를 가질 수 있는 집합
    - 원소 i가 집합에 속해 있는지 여부 := $2^i$을 나타내는 비트가 켜져 있는 지 여부

    ### 👨🏻‍💻코드

    - 공집합과 꽉 찬 집합 구현

        ```cpp
        //집합 크기 N
        const int N = 5;

        //공집합
        unsigned int emptySet = 0;

        /**
         * 꽉 찬 집합
         * 0000 0000 0000 0000 0000 0000 0000 0001 (1)
         * 0000 0000 0000 0000 0000 0000 0010 0000 (1 << N)
         * 0000 0000 0000 0000 0000 0000 0001 1111 ( (1 << N) - 1 )
         */
        unsigned int fullSet = (1 << N) - 1;
        ```

    - 원소 추가 구현

         1을 왼쪽으로 p비트 시프트하면 p번 비트만 켜진 정수를 만들 수 있다.

        ```cpp
        /**
         * 주어진 집합에 p번째 원소를 추가하고 싶다.
         * 집합 크기 3, 주어진 집합 101
         */

        const int N = 3;
        const int p = 1;
        unsigned int givenSet = 5;

        // 101 | 010 = 111
        givenSet |= (1 << p);
        ```

    - 원소의 포함 여부 확인 구현

        ```cpp
        /**
         * 주어진 집합 0 1011
         * p번째 원소 (p=2) = 0
         */

        const int N = 5;
        const int p = 2;
        unsigned int givenSet = 11;

        if(givenSet & (1 << p)) cout << "is in" << endl;
        else cout << "not in" << endl;

        // not in 출력
        ```

    - 원소의 삭제 구현
        - 1을 왼쪽으로 p비트 만큼 시프트하고 비트별 NOT 연산을 수행 → 해당 비트만 꺼지고 나머지는 다 켜짐
        - 이를 주어진 집합과 AND 연산하면 주어진 집합의 나머지 비트는 유지, p번 비트는 항상 꺼짐

        ```cpp
        // 주어진 집합 0 1011 에서 p번째 원소 (p=3) 삭제

        const int N = 5;
        const int p = 3;
        unsigned int givenSet = 11;

        givenSet &= ~(1 << p);
        ```

    - 원소의 토글
        - 주어진 집합에서 p번째 원소가 들어가 있으면 빼고, 빠져 있으면 넣는 경우
        - XOR 연산 사용

        ```cpp
        givenSet ^= (1 << p);
        ```

    - 두 집합에 대해 연산

        ```cpp
        unsigned int added = (a | b);         //합집합
        unsigned int intersection = (a & b);  //교집합
        unsigned int removed = (a & ~b);      //차집합
        unsigned int toggled = (a ^ b);       //a와 b중 하나에만 포함된 원소들의 집합
        ```

    - 집합의 크기 구하기
        - 집합의 크기 N에 대해 lg(N) 시간에 구할 수 있다.

        ```cpp
        int bitCount(unsigned int x) {
        	if(x==0) return 0;
        	return x % 2 + bitCount(x/2);
        }
        ```

        - 하지만 특정 프로그래밍 환경에서 관련 내장 명령어를 제공한다.
            - gcc/g++ : **__builtin_popcount(givenSet)**
            - Visual C++: __popcnt(givenSet)
            - Java: Integer.bitCount(givenSet)

    - 최소 원소 찾기
        - 집합에 포함된 가장 작은 원소를 찾아라 → 정수의 이진수 표현에서 끝에 붙어 있는 0이 몇 개인가?
        - 최소 원소의 비트를 찾는 방법
        - 2의 보수를 이용한 방법

        ```cpp
        /**
         * givenSet  = 0000 0000 0000 0000 0000 0010 0110 0111
         * -givenSet = 1111 1111 1111 1111 1111 1101 1001 1001
         *&---------------------------------------------------
         * result    = 0000 0000 0000 0000 0000 0000 0000 0001
         */

        unsigned int firstElement = (givenSet & -givenSet);
        ```

        - 크기에서 처럼 언어나 컴파일러에서 지원하는 명령어가 있다.
            - gcc/g++: **__builtin_ctz(givenSet)**
            - Visual C++: **_BitScanForward(&index, givenSet)**
            - Java: **Integer.numberOfTrailingZeros(givenSet)**

    - 최소 원소 지우기
        - 주어진 집합에서 -1을 하면 최하위 비트가 꺼지고 그 하위 비트들이 켜진다.
        - 이를 AND 연산하면 최하위 비트가 꺼져 있으므로 최소 원소를 지울 수 있다.

        ```cpp
        givenSet &= (givenSet - 1);
        ```

    - 모든 부분 집합 순회

        ```cpp
        for(int subset = givenSet; subset; ((subset-1) & givenSet)) {
        	//subset은 givenSet의 부분집합
        }
        ```

### 🏷️문제

1. [프로그래머스] [카카오 2019 공채 - 후보키](https://programmers.co.kr/learn/courses/30/lessons/42890)
2. [백준] [P17142 - 연구소3](https://www.acmicpc.net/problem/17142)