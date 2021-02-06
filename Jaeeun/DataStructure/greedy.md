### 탐욕 알고리즘 (Greedy algorithm)

> 최적의 해에 가까운 값을 구하기 위해 사용한다. 여러 경우 중 하나를 결정해야할 때마다, **매순간 최적**이라고 생각되는 경우를 선택하는 방식이다.

#### 동전문제 (가장 기본적인 탐욕문제)

```
coin_list = [500, 100, 50, 1]
def min_coin_count(value, coin_list):
	total_coin_count = 0
	details = list()
	coin_list.sort(reverse=True)
	for coin in coin_list:
		coin_num = value // coin
		total_coin_count += coin_num
		value -= coin_num * coin
		details.append([coin, coin_num])
		return total_coin_count, details
```

#### 부분 배낭 문제

```
data_list = [(10,10),(15,12),(20,10),(25,8),(30,5)]

dat_list = sorted(data_list, key=lamda x[1] / x[0], reverse=True) // 무게당 가치가 큰 순서대로 정렬한다.

def get_max_value(data_list, capacity):
	data_list = sorted(data_list, key=lamda x[1] / x[0], reverse=True)
	total_value = 0
	details = list()
	
	for data in data_list:
		if capacity - data[0] >= 0:
			capacity -= data[0]
			total_value += data[1]
			details.append([data[0], data[1],1])
		else:
    	fraction = capacity / data[0]
    	total_value += data[1] * fraction // 가치를 무게만큼 만든다.
			details.append([data[0], data[1],fraction])
			break
		return total_value, details
```

### 최단 경로 알고리즘

**단일 출발 및 단일 도착 최단 경로 문제**
그래프 내의 특정 노드 u에서 출발, 또 다른 특정 노드 v에 도착하는 가장 짧은 경로를 찾는 문제이다.
가중치 그래프에서 간선의 가중치 합이 최소가 되도록 하는 것이 목적이다.

**단일 출발 최단 경로 문제**
그래프 내의 특정 노드 u와 그래프 내 다른 모든 노드 각각의 가장 짧은 경로를 찾는 문제

**전체 쌍 최단 경로**
그래프 내의 모든 노드 쌍(u,v)에 대한 최단 경로를 찾는 문제

#### 다익스트라 알고리즘 로직

> 첫 정점을 기준으로 연결되어 있는 정점들을 추가해 가며, 최단 거리를 갱신하는 기법
> BFS와 유사하다. 정점에 연결되어 있는 모든 노드들을 먼저 가기 때문이다. 가장 개선된 우선순위 큐를 사용하는 방식에 집중해서 설명하도록 한다.

```
1단계 : 우선순위 큐에 첫 정점을 먼저 넣는다.
mygraph = {
    'A' : {'B' : 8, 'C': 1, 'D':2},
    'B : {}
    'C : {'B' : 5, 'D' : 2},
    'D': {'E' : 3, 'F' : 5},
    'E' : {'F' :1},
    'F' : {'A' : 5}
}

def dijkstra(graph, start):
    distances = {node:float('inf') for node in graph}
    distancse[start] = 0
    queue = []

    heapq.heappush(queue, [distances[start], start])

    while queue:
        current_distance, current_node = heapq.heappop(queue)

        if distances[current_node] < current_distance:
            continue // 만약 작다면 더이상 해주지 않아도 된다.
        for adjacent, weight in graph[current_node].items():
            distance = current_distance + weight

            if distance < distances[adjacent]:
                distances[adjacent] = distance
                heapq.heappush(queue, [distance, adjacent])

    return distancse
```

