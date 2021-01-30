# [Algorithm] 덱 (Deque)

## 덱 (Deque)

### 정의

-   Double-ended Queue의 약자로 양쪽 끝에서 삽입과 삭제가 모두 가능한 자료구조.
-   덱 (Deque)
-   연산/함수

    (1) push_front(item) : item을 덱의 앞에 넣는다.

    (2) push_back(item) : item을 덱의 뒤에 넣는다.

    (3) pop_front() : 덱의 가장 앞에 있는 item을 반환하며 삭제한다.

    (4) pop_back() : 덱의 가장 뒤에 있는 item을 반환하며 삭제한다.

    (5) front : 덱의 가장 앞에 있는 item을 반환한다.

    (6) back : 덱의 가장 뒤에 있는 item을 반환한다.

-   특징

    (1) 스택의 특징과 큐의 특징 모두 가지고 있음

-   시간복잡도

    (1) 원소 추가: O(1)

    (2) 원소 제거: O(1)

    (3) 원소 확인: O(1)

-   구현

    (1) C++ STL Deque을 이용한 구현

    (2) 배열을 이용한 구현

### 문제: 백준 10866번 덱

-   push_front X: 정수 X를 덱의 앞에 넣는다.
-   push_back X: 정수 X를 덱의 뒤에 넣는다.
-   pop_front: 덱의 가장 앞에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
-   pop_back: 덱의 가장 뒤에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
-   size: 덱에 들어있는 정수의 개수를 출력한다.
-   empty: 덱이 비어있으면 1을, 아니면 0을 출력한다.
-   front: 덱의 가장 앞에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
-   back: 덱의 가장 뒤에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
-   입력

    -   첫째 줄에 주어지는 명령의 수 N (1 ≤ N ≤ 10,000)이 주어진다. 둘쨰 줄부터 N개의 줄에는 명령이 하나씩 주어진다. 주어지는 정수는 1보다 크거나 같고, 100,000보다 작거나 같다. 문제에 나와있지 않은 명령이 주어지는 경우는 없다.

-   출력
    -   출력해야하는 명령이 주어질 때마다, 한 줄에 하나씩 출력한다.

## 내 코드

<pre><code>
#include <iostream> 
#include <string>

using namespace std;

int deque[1000000];
int front = 500000, rear = 500000;
//스택, 큐와는 다르게 왼쪽으로도 활장되기 때문에 중간에서 시작, 길이는 여전히 rear-front

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);

	//배열로 선형덱 구현
	int n = 0;
	cin >> n;

	while (n--) {
		string input;
		cin >> input;

		if (input == "push_front") {
			int tmp = 0;
			cin >> tmp;
			deque[--front] = tmp;
		}
		else if (input == "push_back") {
			int tmp = 0;
			cin >> tmp;
			deque[rear++] = tmp;
		}
		else if (input == "pop_front") {
			if (rear != front) {
				cout << deque[front++] << endl;
			}
			else cout << -1 << endl;
		}
		else if (input == "pop_back") {
			if (rear != front) {
				cout << deque[--rear] << endl;
			}
			else cout << -1 << endl;
		}
		else if (input == "size") {
			cout << rear - front << endl;
		}
		else if (input == "empty") {
			if (rear != front) cout << 0 << endl;
			else cout << 1 << endl;
		}
		else if (input == "front") {
			if(rear != front) cout << deque[front] << endl;
			else cout << -1 << endl;
		}
		else if (input == "back") {
			if (rear != front) cout << deque[rear -	1] << endl;
			else cout << -1 <<code endl;
		}
	}

	return 0;
}
</code></pre>
