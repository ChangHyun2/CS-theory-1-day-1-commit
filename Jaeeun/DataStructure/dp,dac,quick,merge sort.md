# 동적 계획법(Dynamic Programming)과 분할 정복(Divide and Conquer)



### 1. 동적계획법 (DP)

> 입력 크기가 작은 부분 문제들을 해결한 후, 해당 부분 문제의 해를 활용해서 보다 큰 크기의 부분 문제를 해결해서 최종적으로 문제를 해결하는 것이다. 상향식 접근법으로, 가장 최하위 해답을 구한 후, 이를 저장하고, 해당 결과값을 이용해서 상위 문제를 풀어가는 방식이다. **부분 문제는 중복되어 상위 문제 해결 시 재활용된다.**

`Memorization` : 프로그램 실행 시 이전에 계산한 값을 저장하여, 다시 계산하지 않도록 하여 전체 실행 속도를 빠르게 하는 기술이다.

```
//피보나치

def fibo (num):
	if num <= 1:
		return num
	return fibo(n-1) + fibo(n-2)

def fibo_dp (num):
	cache = [0 for index in range(num+1)]
	cache[0] = 0
	cache[1] = 1
	
	for index in range(2, num+1):
		cahce[index] = cahce[index-1] + cache[index-2]
	return cache[num]
```

### 2. 분할 정복

> 문제를 나눌 수 없을 때까지 나누어서 각각을 풀면서 다시 합병하여 문제의 답을 얻는 알고리즘이다.
> 하향식 접근법으로 상위의 해답을 구하기 위해, 아래로 내려가면서 하위의 해답을 구하는 방식이다.
> 문제를 나눌 때, **부분 문제는 서로 중복되지 않는다.**

### 3. 퀵정렬

> 기준점(pivot)을 정해서 기준점보다 작은 데이터는 왼쪽, 큰 데이터는 오른쪽으로 모으는 함수를 작성한다. 
> 각 왼쪽(left), 오른쪽(right)은 재귀요법을 사용해서 다시 동일 함수를 호출하여 위 ㅎ마수를 호출한다.

```
def qsort(data):
	if len(data) <=1
		return data
	left, right = list(), list()
	pivot = data[0]
	
	for index in range(1, len(list)):
		if pivot > data[index]:
			left.append(data[index])
		else:
			right.append(data[index])
	return qsort(left) + [pivot] + qsort(right)
```

```
def qsort(data):
	if len(data) <=1
		return data
	left, right = list(), list()
	pivot = data[0]
	
	left = [item for item in range(data[1:]) if pivot > item]
	right = [item for item in range(data[1:]) if pivot < item]
	
	return qsort(left) + [pivot] + qsort(right)
```

### 4. 병합 정렬 (merge sort)

> 재귀용법을 활용한 정렬 알고리즘이다. 
> 리스트를 절반으로 잘라 비슷한 크기의 두부분 리스트로 나눈다. 각 부분 리스트를 재귀적으로 합병 정렬을 이용해 정렬한다. 두 부분 리스트를 다시 하나의 정렬된 리스트로 합병한다.

