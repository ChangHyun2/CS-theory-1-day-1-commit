# Union Find

싸이클이 존재하는지 확인하는 알고리즘으로 disjoint set 자료구조를 활용하며

그리디하게 최소 비용 거리를 구하는 알고리즘인 kruskal's 알고리즘에서 사용된다.

1 find : edge가 어떤 집합에 포함되는지 찾고

2. union : edge의 vertex가 다른 집합에 위치할 경우 두 집합을 묶어준다.

### Find Union

최소값을 갖는 edge부터 edge를 결합시켜준다면

1,2  (1)g

1,2 / 3,4  (2)

1,2 / 3,4 / 5,6 (3)

1,2 / 3,4 / 5,6 / 7,8  (4)

1,2,3,4 / 5,6 / 7,8  (45

1,2,3,4,5,6 / 7,8  (6)

(7) ⇒ 1-3 싸이클 발생하므로 union하지 않는다.

1,2,3,4,5,6,7,8 (8)

![Union%20Find%202d51154181294240953c60ce2caa70b5/Untitled.png](Union%20Find%202d51154181294240953c60ce2caa70b5/Untitled.png)

### 그래프로 union 표현하기

 

![Union%20Find%202d51154181294240953c60ce2caa70b5/Untitled%201.png](Union%20Find%202d51154181294240953c60ce2caa70b5/Untitled%201.png)

edge의 vertex가 서로 다른 set에 포함될 경우, 

setA를 setB의 child로 추가해준다. (순서 상관x)

### 배열로 union 표현하기

-1(음수)는 자기 자신을 set으로 가지고 있다는 것을 의미한다. (집합의 root를 표현)

두 set을 union할 때 두 set의 개수를 더해주고 부모의 노드를 자식에게 마킹해준다.

부모는 음수로 자신을 포함한 set의 개수를 저장하고, 

자식은 양수로 부모의 위치 정보를 저장한다.

![Union%20Find%202d51154181294240953c60ce2caa70b5/Untitled%202.png](Union%20Find%202d51154181294240953c60ce2caa70b5/Untitled%202.png)

```jsx
	const edges = [
  [1, 3],
  [3, 4],
  [4, 2],
  [2, 1],
  [2, 5],
  [5, 6],
  [6, 8],
  [8, 7],
  [7, 5],
];
const vertextCount = 8;

const disjointSet = function () {
  this.parent = Array(vertextCount + 1).fill(-1);

  this.find = (x) => {
    const parent = this.parent[x];

    if (parent > 0) {
      return this.find(parent);
    }

    return x;
  };

  this.union = (x, y) => {
    const xp = this.find(x);
    const yp = this.find(y);

    if (xp === yp) {
      return false; // 싸이클 발생
    }

    this.parent[xp] = this.parent[xp] + this.parent[yp];
    this.parent[yp] = xp;

    return true;
  };
};

const ds = new disjointSet();

edges.forEach((edge) => {
  ds.union(...edge);
});

console.log(ds);

```

## 예제

1. [https://leetcode.com/problems/redundant-connection/submissions/](https://leetcode.com/problems/redundant-connection/submissions/)

```jsx
/**
 * @param {number[][]} edges
 * @return {number[]}
 */
var findRedundantConnection = function(edges) {
    const set = {
        parent:Array(edges.length+1).fill(-1),
        find:function(x){
            const xp = this.parent[x]
            
            if(xp>0){
                return this.find(xp)
            }
            
            return x
        },
        union:function(x,y){
            const xp = this.find(x)
            const yp = this.find(y)
            
            if(xp === yp) return false
            
            this.parent[yp] = this.parent[xp] + this.parent[yp]
            this.parent[xp] = yp
            
            return true
        }
    }
    
    for(const edge of edges){
        const [x,y] = edge
        
        if(!set.union(x,y)){
            return edge
        }
    }
};
```