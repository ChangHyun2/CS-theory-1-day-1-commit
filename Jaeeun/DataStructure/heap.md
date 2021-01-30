###  1. 힙(Heap) 

> 데이터에서 **최대값과 최소값을 빠르게 찾기 위해 고안된 완전 이진 트리**이다. 힙은 일종의 **반정렬 상태(느슨한 정렬 상태)**를 유지한다.

`완전 이진 트리` : 노드를 삽입할 때 최하단 왼쪽 노드부터 차례대로 삽입하는 트리이다.

#### 1-1 힙을 사용하는 이유

배열에 데이터를 넣고, 최대값과 최소값을 찾으려면 오래 걸린다.
이에 반해, 힙에 데이터를 넣고, 최대값과 최소값을 찾으면 O(logn) 이 걸린다.

### 2. 힙(Heap) 구조

힙은 최대값을 구하기 위한 구조와 최소값을 구하기 위한 구조로 분류 할 수 있다.

`최대 힙(max heap)` : 부모 노드의 키 값이 자식 노드의 키 값보다 크거나 같은 완전 이진 트리 <br>
`최소 힙(min heap)` : 부모 노드의 키 값이 자식 노드의 키 값보다 작거나 같은 완전 이진 트리 <br>

#### 2-1 이진 탐색 트리와의 공통점과 차이점

힙은 각 노드의 값이 자식 노드보다 크거나 같다. 
이진 탐색 트리는 왼쪽 자식 노드의 값이 가장 작고, 그다음은 부모 노드이고 오른쪽 자식 노드의 값이 가장 크다. 반면에 힙은 왼쪽 및 오른쪽 자식 노드의 오른쪽이 클 수도 있고 왼쪽이 클 수도 있다.

**이진 탐색 트리는 탐색을 위한 구조, 힙은 최대/최소값 검색을 위한 구조중 하나이다.**

### 3. 힙(Heap) 동작

#### 3-1 힙의 데이터 삽입하기

힙은 완전 이진 트리이므로, 삽입할 노드는 기본적으로 왼쪽 최하단부 노드부터 채워지는 형태로 삽입한다. 
채워진 후에는 부모노드와 비교해서 바꿔주는 작업을 반복한다. (Max Heap의 경우) 

#### 3-2 힙의 데이터 삭제하기

보통 삭제는 최상단 노드(root 노드)를 삭제하는 것이 일반적이다.
가장 마지막에 들어갔던 노드를 최상단 노드로 변경한다. 
채워진 후에는 자식노드와 부모노드를 비교해서 바꿔주는 작업을 반복한다.

### 4. 힙(Heap) 구현

> 일반적으로 힙 구현시 **배열 자료구조**를 활용한다. 
> 배열은 인덱스가 0번부터 시작하지만, **힙 구현의 편의를 위해, root 노드 인덱스 번호를 1로 지정하면, 구현이 좀 더 수월**하다.

`부모 노드 인덱스 번호  (parent node's index)` : 자식 노드 인덱스 번호 (child node's index) // 2

`왼쪽 자식 노드 인덱스 번호 (left child node's index)` :부모 노드 인덱스 * 2

`오른쪽 자식 노드 인덱스 번호 (right child node's index)` : (부모 노드 인덱스 * 2 )+1

#### 4-1 힙(Heap) 데이터 추가

```
class Heap:
	def _init_(self, data):
		self.heap_array = list()
		self.heap_array.append(None) // 0 인덱스는 사용 안한다.
		self.heap_array.append(data)
		
	def move_up(self., inserted_data):
	if inserted_idx <= 1:
		return False
	
	parent_idx = inseted_idx // 2
	if self.heap_array[inserted_idx] > self.heap_array[parent_idx]
		return True
	else:
		return False
  
	def insert(self, data):
		if len(self.heap_array) == 0:
			self.heap_array.append(None)
			self.heap_array.append(data)
			return True
		self.heap_array.append(data)
		
		inserted_idx = len(self.heap_array) -1 // 처음 인덱스는 없으니까
		
		while self.move_up(inserted_idx):
			parent_idx = inserted_idx // 2
			self.heap_array[inserted_idx] , self.heap_array[parent_idx] = self.heap_array[parent_idx], self.heap_array[inserted_idx]
			inserted_idx = parent_idx	
			return True
					
```

#### 4-2 힙(Heap) 데이터 삭제

```
class Heap:
	def _init_(self, data):
		self.heap_array = list()
		self.heap_array.append(None) // 0 인덱스는 사용 안한다.
		self.heap_array.append(data)
	
	def move_down(self, popped_idx):
		left_child_popped_idx = popped_idx * 2 // 왼쪽의 자식 노드
		right_child_popped_idx = popped_idx * 2 + 1 // 오른쪽 자식 노드
		
		# 왼쪽 자식 노드도 없을 때
		if left_child_popped_idx >= len(self.heap_array):
			return False
		
		#오른쪽 자식 노드 없을 때
		elif right_child_popped_idx >= len(self.heap_array):
    	if self.heap_array[popped_idx] < self.heap_array[left_child_popped_idx]
    		self.heap_array[popped_idx], self.heap_array[left_child_popped_idx] =
    		self.heap_array[left_child_popped_idx] , self.heap_array[popped_idx]
    	else
    		return False
    	
     #오른쪽 왼쪽 자식 노드 모두 있을때
    	else:
    		if self.heap_array[popped_idx] < self.heap_array[left_child_popped_idx]
    			self.heap_array[popped_idx], self.heap_array[left_child_popped_idx] =
    			self.heap_array[left_child_popped_idx], self.heap_array[popped_idx]
    			popped_idx = left_child_popped_idx
    		else
    			return False
    		if self.heap_array[popped_idx] < self.heap_array[right_child_popped_idx]
    			self.heap_array[popped_idx], self.heap_array[right_child_popped_idx]
    			= self.heap_array[right_child_popped_idx], self.heap_array[popped_idx]
    		else
    			return False
		
	def pop(self):
		if len(self.heap_array) <= 1:
			return None
		returned_data = self.heap_array[1]
		self.heap_array[1] = self.heap_array[-1] // 맨 마지막으로 root로 바꿔준다.
		del self.heap_array[-1] // 마지막 데이터를 지워준다.
		return returned_data
		poped_idx = 1
		
	
```

#### 참고

https://gmlwjd9405.github.io/2018/05/10/data-structure-heap.html