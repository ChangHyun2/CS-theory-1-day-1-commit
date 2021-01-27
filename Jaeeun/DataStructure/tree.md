### 1. 트리(Tree) 🎄

`Node` : 트리에서 데이터를 저장하는 기본 요소
`Root Node` : 트리 맨 위에 있는 노드
`Level` : 최상위 노드를 Level 0으로 하였을 때, 하위 Branch로 연결된 노드의 길이를 나타낸다.
`Parent Node` : 어떤 노드의 다음 레벨에 연결된 노드
`Child Node` : 어떤 노드의 상위 레벨에 연결된 노드

### 2. 이진 트리(Binary Tree) 와 이진 탐색 트리(Binary Search Tree)
이진 트리 : 노드의 최대 Branch 가 2인 트리
이진 탐색 트리 : 이진 트리에 추가적인 조건이 있는 트리 (ex 왼쪽 노드는 해당 노드보다 작은 값, 오른쪽 노드는 해당 노드보다 큰 값을 가진다.)

#### 2-1 장점
데이터 검색할 때, 탐색 속도를 개선할 수 있다. 하지만 복잡하는 단점이 있다.

#### 2-2 노드 클래스 만들기

```
Class Node:
	def _init_(self, value):
    self.value = value
    self.left = None
    self.right = None
    
Class NodeMgmt:
	def insert(self, value):
    	self.current_node = self.head
        while True:
        		if value < self.current_node:
            		if self.current_node.left != None:
                	self.current_node = self.current_node.left
              	else:
                	slef.current_node.left = Node(value)
                  break;
            else:
            	if self.current_node.right != None:
                	self.current_node = self.current_node.right
                else:
                	self.current_node.right = Node(value)
                    
	def search(self, value):
   		self.current_node = self.head
    	while self.current_node:
    			if self.current_node.value == value:
        			return True
        	elif value < self.current_node.value:
        			self.current_node = self.current_node.left
        	elif alue > self.current_node.value:
        			self.current_node = self.current_node.right
```

### 3. 이진 탐색 트리 삭제

```
def delete(self, vlaue):
	searched = False // 해당 노드를 찾았는가 아닌가
    self.current_node = self.head
    self.parent = self.head
    while self.current_node:
    	if self.current_node.value == value:
        	searched = True
          break
      elif value < self.current_node.value:
      		self.parent = self.current_node
          self.current_node = self.current_node.left
      else:
        	self.parent = self.current_node
          self.current_node = self.current_node.right
       if searched == False:
        		return False
        
### 이후부터 Case들을 분리해서, 코드 작성
```

#### 3-1 Leaf Node 삭제

```
if self.current_node.left != None and self.current_node.right == None
		if value < self.parent.value:
    		self.parent.left = self.current_node.left
    else:
        self.parent.right = self.current_node.left
```

#### 3-2 Chiled Node 1개 삭제

```
if self.current_node.left != None and self.current_node.right == None // 왼쪽 노드를 가지고 있을 경우
		if value < self.parent.value:
    		self.parent.left = self.current_node.left
    else:
        self.parent.right = self.current_node.left
        	
if self.current_node.left == Node and self.current_node.right != None // 오른쪽 노드를 가지고 있을 경우
		if value < self.parent.vlaue:
       self.parent.left = self.current_node.right
    else:
       slef.parent.right = self.current_node.right
```

