# 정렬

정렬(sroting) : 어떤 데이터들이 주어졌을 때 이를 정해진 순서대로 나열하는 것

### 1. 버블 정렬 (bubble sort)

> 두 인접한 데이터를 비교해서, 앞에 있는 데이터가 뒤에 있는 데이터보다 크면, 자리를 바꾸는 정렬 알고리즘

```
for index in range(len(data)-1):
	swap = False
	for index2 in range(len(data)-index-1): // 맨 마지막에 데이터가 가니까 비교할 필요 없다.
		if data[index2] > data[index2+1]:
			ata[index2], data[index2+1] = data[index2+1], data[index2]
			swap = True // 변경이 일어나면
		if swap == False:
			break
```



### 2. 선택 정렬 (selection sort)

> 주어진 데이터 중에서 최소값을 찾고, 해당 최소값을 데이터 맨 앞에 위치한 값과 교체한다.
> 맨 앞의 위치를 뺀 나머지 데이터를 동일한 방법으로 반복한다.

```
for stand in range(len(data)-1):
	lowest = stand
	for index in range(stand+1, len(data)):
		if data[lowest] > data[index]:
			lowest = index
		data[lowest], data[stand] = data[stand], data[lowest]
		return data
```



### 3. 삽임 정렬 (insertion sort)

> 삽입 정렬은 두 번째 인데스부터 시작한다. 해당 인덱스(key 값) 앞에 있는 데이터부터 비교해서
> key 값이 더 작으면 B값을 뒤 인덱스로 복사한다. 이를 key값이 더 큰 데이터를 만날 때 까지 반복한다. 그리고 큰 데이터를 만난 위치 바로 뒤에 key값을 이동한다.

```
for index in range(len(data)-1):
	for index2 in range(index+1, 0, -1): // index부터 앞으로 반복한다.
		if data[index2] < data[index2-1]:
			data[index2], data[index2-1] = data[index2-1], data[index2]
		else:
			break // 더이상 반복 할 필요가 없기 때문에 멈춘다.	
```

### 4. 공간 복잡도

`시간복잡도` : 얼마나 빠르게 실행되는지
`공간복잡도` : 얼마나 많은 저장 공간이 필요한지

