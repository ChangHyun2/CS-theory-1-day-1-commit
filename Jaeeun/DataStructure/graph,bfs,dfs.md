### 1. 순차탐색

> 탐색은 여러 데이터 중에서 원하는 데이터를 찾아내는 것을 의미한다. 데이터가 담겨있는 리스트를 앞에서부터 하나씩 비교해서 원하는 데이터를 찾는 방법이다.

```
def sequential (data_list, search):
	for i index in range(len(data_list)):
		if data_list[index] == search:
			return index
		return -1
```



### 2. 그래프의 이해

> 그래프는 실제 세계의 현상이나 사물을 정점 또는 노드와 간선으로 표현하기 위해 사용한다.

`무방향 그래프` : 간선에 방향이 없는 그래프, 양쪽 방향으로 갈 수 있다. 
`방향 그래프` : 간선에 방향이 있는 그래프
`가중치 그래프` : 간선에 비용 또는 가중치가 할당된 그래프 
`연결 그래프`  : 무방향 그래프에 있는 모든 노드에 대해 항상 경로가 존재한다.
`비연결 그래프` : 무방향 그래프에서 특정 노드에 대한 경로가 존재하지 않는 그래프이다.
`사이클과 그래프` : 단순 경로의 시작 노드와 종료 노드가 동일한 경우 
`비순환 그래프` : 사이클이 없는 그래프 
`완전 그래프` : 그래프의 모든 노드가 서로 연결되어 있는 그래프



### 3. 너비 우선 탐색 (Branch-First Search)

>  정점들과 같은 레벨에 있는 노드들을 먼저 탐색하는 방식

<img src="image-20210204001647389](/Users/jaeeunlim/Library/Application Support/typora-user-images/image-20210204001647389.png" width=400>

```
def bfs(graph, start_node):
	visited = list()
	need_visit = list()
	
	need_visit.append(start_node)
	
	while need_visit:
		node = need_visit.pop(0) // 맨 앞을 빼면 뒤에서부터 다시 차례로 이어진다.
		if node not in visited:
			visited.append(node)
			need_visit.extand(graph[node]) // 뒤에 채워주는 것이다.
		
		return visited // 방문 된 노드가 순서대로 나올 것이다
```



### 4. 깊이 우선 탐색 (Depth-First Search)

> 정점의 자식들을 먼저 탐색하는 방식

<img src="image-20210204001709886](/Users/jaeeunlim/Library/Application Support/typora-user-images/image-20210204001709886.png" width=400>

```
def dfs(graph, start_node):
	visited, need_visit = list(), list()
	need_visit.append(start_node)
	
	while need_visit:
		node = need_visit.pop() // 맨 끝의 데이터를 가져온다.
		if node not in visited:
			visited.append(node)
			need.visit.extend(graph[node])
	return visited
```





