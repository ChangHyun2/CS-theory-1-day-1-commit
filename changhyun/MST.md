# 창현

# 이론

## 선행 알고리즘 : Union Find

[https://www.youtube.com/watch?v=wU6udHRIkcc&list=PLDN4rrl48XKpZkf03iYFl-O29szjTrs_O&index=17](https://www.youtube.com/watch?v=wU6udHRIkcc&list=PLDN4rrl48XKpZkf03iYFl-O29szjTrs_O&index=17)

[Union Find](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Union%20Find%202d51154181294240953c60ce2caa70b5.md)

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled.png)

### **최소 신장 트리( minimum spanning tree )**

주어진 그래프에서 싸이클이 발생하지 않으며 모든 노드를 방문할 수 있는  경로 (tree 조건을 만족하게 된다.)

### 최소 신장 트리 수학적 조건

graph로 만들 수 있는 최소 신장 트리를 sub graph (S)라 할 경우

1. S는 Vertex(V') V개, Edge(E') E - 1개로 이루어지며

    S (V', E')

    V' = V 

    E' = E - 1

2. MST가 될 수 있는 Tree의 개수는 V` c E` (콤비네이션)이다. 

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%201.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%201.png)

위와 같이 싸이클이 발생할 경우

MST는 V c (E - cycle)개 존재한다

### Minimum Cost Spanning Tree

그래프의 edge에 weight가 부여될 경우(weighted graph) 모든 vertex를 방문할 수 있는 최소 비용

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%202.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%202.png)

### Minimum Cost Spanning Tree 구하기

그리디하게 풀 경우 모든 MST를 조사하지 않고 답을 구할 수 있다.

ex) Kruskal's & Prim's 알고리즘

## MST 그리디 알고리즘

[https://www.youtube.com/watch?v=4ZlRH0eK-qQ](https://www.youtube.com/watch?v=4ZlRH0eK-qQ)

### Prim's 알고리즘

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%203.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%203.png)

1. 최소 비용의 edge로 시작해 
2. edge와 연결된 edges 중 최소 비용을 갖는 edge를 선택하며 그리디하게 MST를 만들면 

Minimum Cost Spanning Tree가 된다.

단, 탐색할 그래프가 1 connected graph ( 1 component )이어야 한다.

아래의 경우 2개의 component이므로, 위의 그리디 조건으로 문제를 풀 경우 떨어져있는 컴포넌트의 edge를 방문하지 않게 되므로 답을 구할 수 없다.

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%204.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%204.png)

### Kruskal's 알고리즘

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%205.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%205.png)

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%206.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%206.png)

1. 최소 비용을 갖는 edge를 더해나간다.
2. edge를 더했을 때 사이클이 발생하는 경우에는 다음 최소 비용의 edge를 더한다.

오른쪽 그래프를 Kruskal's 알고리즘으로 풀 경우 edge를 선택하는 순서는 다음과 같다.

1-6 ⇒ 3-4 ⇒ 2-7 ⇒ 2-3 ⇒ 7-4 (싸이클이 발생하므로 선택 X, 다음 최소 비용 탐색) ⇒ ...

크러스칼 알고리즘은 최소를 찾을 떄 edge 간의 상관 관계가 없으므로 여러 컴포넌트를 갖는 그래프에서도 사용될 수 있다.

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%204.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%204.png)

MST 개념을 숙지하고 있다면 MST라는 조건이 주어질 경우 

아래 그래프를 통해 하나의 MST를 찾을 수 있다.

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%207.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%207.png)

![%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%208.png](%E1%84%8E%E1%85%A1%E1%86%BC%E1%84%92%E1%85%A7%E1%86%AB%2072f97460a85a4a91ab82e35d87c577ce/Untitled%208.png)

# 예제

[https://leetcode.com/problems/min-cost-to-connect-all-points/discuss/?currentPage=1&orderBy=hot&query=](https://leetcode.com/problems/min-cost-to-connect-all-points/discuss/?currentPage=1&orderBy=hot&query=)

### 프림 알고리즘

[참고 풀이](https://leetcode.com/problems/min-cost-to-connect-all-points/discuss/882386/Java-JavaScript-Greedy-algorithm-faster-than-99%2B-submissions) 

모든 edges를 포함하는 그래프를 가정하고

시작 노드부터 연결될 수 있는 모든 노드와의 min cost를 더해나간다.

```jsx
/**
 * @param {number[][]} points
 * @return {number}
 */
var minCostConnectPoints = function(points) {
    const manhattanDistance = (pos1, pos2) =>{
        const [x1,y1] = pos1
        const [x2,y2] = pos2
        
        return Math.abs(x2-x1) + Math.abs(y2-y1)
    }
    
    let total = 0

    const costs = Array(points.length).fill(Infinity)
    let current = 0
    costs[current] = 0
    
    for(let edges=0; edges<points.length-1; edges++){
        let min =Infinity
        let next
        
        for(let i=0; i<points.length; i++){
            if(costs[i]===0) {
                continue;
            }
            
            const base = points[current]
            const compare = points[i]
            
            costs[i] = Math.min(costs[i], manhattanDistance(base, compare))

            if(costs[i] < min){
                min = costs[i]
                next = i
            }
        }
        
        total += min
        costs[next] = 0
        current = next
    }
    
    return total
};
```

### 크러스칼 알고리즘

```jsx
// brute force

var minCostConnectPoints = function(points) {
    const manhattanDistance = (pos1, pos2) =>{
        const [x1,y1] = pos1
        const [x2,y2] = pos2
        
        return Math.abs(x2-x1) + Math.abs(y2-y1)
    }
    
    const disjointSet = {
        parent:Array(points.length).fill(-1),
        find:function(i){
            const ip = this.parent[i]
            if(ip>=0){
                return this.find(ip)
            }
            return i
        },
        union:function(i,j){
            const ip = this.find(i)
            const jp = this.find(j)
            
            if(ip === jp){
                return false;
            }
            
            this.parent[ip] = this.parent[ip] + this.parent[jp]
            this.parent[jp] = ip
            
            return true;
        }
    }
    
    const edges = []
    for(let i=0; i<points.length-1; i++){
            for(let j=i+1; j<points.length; j++){
                edges.push([i,j,manhattanDistance(points[i], points[j])])
        }
    }
    edges.sort((a,b) => a[2] - b[2])
    console.log(edges)

    let total = 0;
    edges.forEach((edge, i) => {
        const [a,b,cost] = edge
        
        total += disjointSet.union(a,b) ? cost : 0
    })
    
    return total
};
```