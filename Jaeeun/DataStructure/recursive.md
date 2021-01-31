# 재귀 용법 (recursive call, 재귀 호출)



### 1. 재귀 용법 (recursive call)

> 함수 안에서 동일한 함수를 호출하는 형태이다. 쉬운 알고리즘 작성시 사용되므로 익숙해지는 것이 중요하다.
> 재귀 호출은 스택의 전형적인 예이다. (함수는 내부적으로 스택처럼 관리된다.)

````
// 가장 기본적인 팩토리얼
def factorial (num):
	if n > 1:
		return n * factorial (num-1) // 자기 함수를 호출하는 것이 중요하다.
   else:
   	return num
````

```
// num 부터 1까지 곱셈을 구하시오
def multiple (num):
if num <= 1:
	return data
return num * multiple(num-1)
```

```
// 숫자가 들어있는 리스트가 주어졌을 때, 리스트 내부의 합을 구하시오
def sum_list (data):
	if len(data) == 1:
		return data[0]
	return data[0] + sum_list(data[1:])
```

```
//회문은 순서를 거꾸로 읽어도 제대로 읽은 것과 같은 단어
def pal (string):
	if len(string) <= 1:
		return True
	if string[0] == string[-1]:
		return pal(string[1:-1])
	else:
		return False
```

```
// 정수 n에 대하여 n이 홀수이면 3 * n +1 을 하고, n이 짝수이면 n을 2로 나눈다.
이렇게 계속 진행해서 n이 결국 1이 될 때까지 2와 3의 과정을 반복한다.

def recusive (n):
	if n == 1: // 1이 될 때까지
		return n
	elif n % 2 == 0:
		return recusive(int(n/2))
	else:
		return recusive ((n*3)+1)
```

```
정수 4를 1, 2, 3의 조합으로 방법은 7가지가 있다.
1 + 1 + 1 + 1
1 + 1 + 2
1 + 2 + 1
2 + 1 + 1
1 + 3
3 + 1
2 + 2
d
def func (data):
	if data == 1:
		return 1
	elif data == 2:
		return 2
	elif data == 3:
		return 4	
	return func(data-1) + func(data-2) + func(data-3)
```

