# 창현

그래프에서 Single Source Shortest Path를 찾을 떄 사용되며

방향성과 무관하게 모든 weighted graph에 적용 가능하다.

시작 노드를 결정할 수 있고 시작 노드로부터 path에 존재하는 모든 노드까지의 최소 비용을 구할 수 있다. 

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled.png)

### 알고리즘 적용 순서

1. **initialize**

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%201.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%201.png)

임의의 시작 노드에서 인접한 노드가 아닐 경우 값을 Infinity로 할당하고

인접한 노드는 해당 노드까지의 비용을 할당한다.

2. **Relaxation**

탐색을 마친 시작 노드는 방문한 노드로 마킹하고

시작 노드(1)로부터 최소 거리에 있는 노드를(2) 탐색한다.

시작 노드 이후로 탐색하는 노드는 Relaxation을 진행한다.

Relaxation

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%202.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%202.png)

인접한 노드까지의 비용을 계산하고 인접한 노드에 기록된 최소비용보다 작을 경우 값을 갱신한다.

방문했던 노드는 고려하지 않는다.

Relaxation

u : 노드 2

v : 노드 3

d[a] : a까지의 최단 거리

c(a,b) : a에서 b로 이동할 때 소요되는 비용

if(d[u] +c(u,v)≤ d[v]){

d[v] = d[u] + c(u,v)

}

위 과정을 통해 다익스트라 알고리즘으로 시작노드부터 그래프에 위치하는 다른 노드까지의 최소 거리를 구할 수 있다.

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%203.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%203.png)

아래 그림과 같이 다익스트라 알고리즘은 음수의 weight를 포함할 경우 알고리즘이 성립하지 않을 수도 있다.

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%204.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%204.png)

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%205.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%200d8e0fca46d14833bb22624e0fe8c688/Untitled%205.png)

### 예제

[카카오 2021 4번](https://programmers.co.kr/learn/courses/30/lessons/72413) 

```jsx
function solution(n, s, a, b, fares) {  
    // n 노드 수, s : 출발, a,b : 도착지, fares : weights
    
    const dijkstra = (start) => {
        const graph = new Map()
        for(let i=1; i<=n; i++){
            graph.set(i, [])
        }
        
        fares.forEach(fare => {
            const [n1, n2, cost] = fare
            
            graph.get(n1).push([n2, cost])
            graph.get(n2).push([n1, cost])
        }) 
    
        const visited = Array(n+1).fill(0)
        const costs = Array(n+1).fill(Infinity)
        costs[0] = 0
        costs[start] = 0
        
        while(true){
            let minNode
            let minCost = Infinity
            
            for(let i=1; i<=n; i++){
                if(!visited[i] && costs[i] < minCost){
                    minNode =i
                    minCost = costs[i]
                }
            }
            
            if(!minNode){
                break   
            }
            visited[minNode] = 1
            
            const adjacents = graph.get(minNode)
            adjacents.forEach(adj => {
                const [adjNode, cost] = adj
                costs[adjNode] = Math.min(costs[minNode]+cost, costs[adjNode])
            })
        }
        
        return costs
    }
    
    const costs = [a,b,s].map(s => dijkstra(s))
    
    let answer = costs[2][a] + costs[2][b]
    
    for(let i=1; i<=n; i++){
        answer = Math.min(answer, costs[2][i] + costs[1][i] + costs[0][i])
    }
    
    return answer;
}
```

[https://leetcode.com/problems/network-delay-time/submissions/](https://leetcode.com/problems/network-delay-time/submissions/)

DFS로 전부 순회할 경우 시간 초과 

```jsx
var networkDelayTime = function(times, n, k) {
    
    const list = {}
    times.forEach(time => {
        const [start, end, sec] = time
        if(!list[start]){
            list[start] = []
        }
        list[start].push([end,sec])
    })
    
    const costs = Array(n+1).fill(Infinity)
    costs[0] = 0
    costs[k] = 0
    const set = new Set()
    set.add(k)
    
    const dfs = (start, set) => {
        const adjacents = list[start]||[]
    
        adjacents.forEach((node) => {
            const [end, sec] = node
            if(set.has(end)) return
            
            const newSet = new Set(set)
            newSet.add(end)

            if(costs[end] > cos dkwlts[start]+sec){
                costs[end] = costs[start]+sec
                dfs(end, newSet)
            }
        })
    }
    
    dfs(k,set)
    return costs.some(cost => cost===Infinity) ? -1 : Math.max(...costs)

};
```

릿코드 dfs 솔루션 ⇒ 5%

```jsx
var networkDelayTime = function(times, n, k) {
    
    const graph = new Map()
    
    times.forEach(edge => {
        const [start, end, sec] = edge
        if(!graph.has(start)){
            graph.set(start, [])
        }
        graph.get(start).push([end, sec])
    })
    
    const adjacents = graph.values()
    while(true){
        const {value, done} = adjacents.next()
        if(done) break
        
        value.sort()
    }
    
    const dist = Array(n+1).fill(Infinity)
    dist[0] = 0
    const dfs = (graph, node, elapsed) => {
        if(elapsed >= dist[node]) return
        dist[node] = elapsed
        
        if(graph.has(node)){
            const adjacents = graph.get(node)
            adjacents.forEach(next => {
                const [node, sec] = next
                dfs(graph, node, elapsed + sec)
            })
        }
    }
    dfs(graph, k, 0)
    return dist.some(d => d===Infinity) ? -1 : Math.max(...dist)
};
```

하위 5% 풀이..

bfs로 푼 풀이나 마찬가지

```jsx
/**
 * @param {number[][]} times
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var networkDelayTime = function(times, n, k) {
    const relax = Array(n+1).fill(Infinity)
    relax[0] = 0

    const list = {}
    
    times.forEach(time => {
        const [start, end, value] = time
        
        if(!list[start]){
            list[start] = []
        }
        
        list[start].push([end, value])
    })
    
    relax[k]=0
    
    list[k]
    
    const stack = list[k] ? list[k].map(v => ([k, ...v])) : []
    
    while(stack.length){
        const [start, end, time] = stack.shift()
        
        if(relax[end] > time + relax[start]){
            relax[end] = time + relax[start]
            
            list[end] && list[end].forEach(v => stack.push([end,...v]))
        }
    }
    
    if(relax.some(v => v===Infinity)) return -1
        
    return Math.max(...relax)
};
```

다익스트라 풀이 leetcode 참고

다른 알고리즘과는 달리 **시작 노드부터 각 노드까지 소요되는 최소 비용을 모두 구할 수 있다**.

```jsx
var networkDelayTime = function(times, n, k) {
    
    const graph = new Map()
    
    times.forEach(edge => {
        const [start, end, cost] = edge
        if(!graph.has(start)){
            graph.set(start, [])
        }
        graph.get(start).push([end, cost])
    })
    
    const dist = Array(n+1).fill(Infinity)
    const visited = Array(n+1).fill(0)
    dist[0] = 0
    dist[k] = 0
    
    while(true){
        let minNode
        let min = Infinity
        
        for(let i=1; i<=n; i++){
            if(!visited[i] && dist[i] < min){
                min = dist[i]
                minNode = i
            }
        }
        
        if(!minNode) break
        visited[minNode] = 1

        if(graph.has(minNode)){
            graph.get(minNode).forEach(adj => {
                const [next, cost] = adj
                dist[next] = Math.min(dist[next], dist[minNode] + cost)
            })
        }
    }
    
    let ans = 0

    return dist.some(d => d===Infinity) ? -1 : Math.max(...dist)
};
```