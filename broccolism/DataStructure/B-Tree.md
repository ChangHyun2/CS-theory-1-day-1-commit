### Balanced(?) Tree

- 사실 B트리 창시자조차 B가 무엇을 의미하는지 말하지 않았다고 한다. 그저 balanced가 아닐까 하고 추측할 뿐..
- binary search tree의 확장판이다.
  - 기존 BST는 노드 하나당 데이터 하나만을 저장했다면,
  - B-Tree에서는 노드 하나당 데이터 여러개를 저장할 수 있다.
    - 따라서 child도 2개 이상 가질 수 있다.

# 규칙

- 어떤 트리가 B-Tree가 되기 위해서는 따라야할 규칙이 있다.

1. 노드 하나가 가질 수 있는 데이터는 최대 m 개다.
2. 루트 노드를 제외하고, 어떤 노드가 가질 수 있는 데이터는 최소 ceil((m - 1) / 2)개이다.
3. 루트 노드는 데이터를 최소 1개 가질 수 있다.
4. 모든 노드는 자신이 갖고 있는 데이터보다 child를 하나 더 가진다.
   - 따라서, 루트 노드를 제외하고 한 노드가 가질 수 있는 child 갯수는 최대 m + 1, 최소 ceil((m - 1) / 2) + 1이 된다.
   - 루트 노드는 child를 최소 2개 가져야 한다.
5. 모든 leaf 노드는 같은 level에 있어야 한다.

### children

![b tree](http://www.cs.cornell.edu/courses/cs312/2008sp/recitations/images/B-trees.gif)

- B트리 노드는 그림과 같이 값을 여러개 저장할 수 있다. 따라서 AVL트리처럼 left, right 포인터 두개만으로 children을 모두 나타낼 수는 없다.
  - 따라서, 아래와 같이 정의한다.

```C++
typedef NodeStruct_ {
    DataType *keys;
    NodeStruct_ **children;
    int num_of_keys;
} NodeStruct;

typedef Node *NodeStruct_
```

- `num_of_keys`가 없으면
  - keys, children을 배열로 구현했을 때 정확한 갯수를 알 수 없게 되고
  - keys, children을 링크드리스트로 구현했을 때 매번 갯수를 세어야하는 불편함이 생긴다.

# 연산

### 삽입

- B Tree 삽입의 특징은 오직 **leaf 노드에서만 이루어진다**는 점이다.
  - 그렇다면 leaf 노드만 key를 잔뜩 갖게 되지 않나요?
    - 그래서 균형을 맞추기 위해 `split` 연산이 일어난다.
  - 구현 방식은 아래와 같이 2가지 방식이 있다.
    1. 진짜로 leaf까지 내려가서 key를 삽입한 후, 필요한 경우 위로 점점 거슬러 올라가면서 split하는 방식
    - 보통 이 방식을 많이 사용한다.
    2. leaf까지 내려가는 과정에서 필요한 노드에 미리 split을 해주는 방식
    - 왜 이걸 잘 안쓰냐하면, 불필요한 split이 일어날 수도 있기 때문이다.

#### Split()

![split](https://media.geeksforgeeks.org/wp-content/cdn-uploads/BTreeSplit.jpg)

- 한 노드가 너무 많은 key를 담게 되었을 때 그 노드를 나누는 연산.
- split이 일어나면, 새로운 노드 2개가 생기고 기존 노드에 있던 key 중 하나가 parent node로 들어간다.
  - 만약 parent node에서 overflow가 발생하면 그 노드에서도 split을 해줘야한다.
- parent node로 들어가는 key는 기존 노드의 중간값이다.
  - 그래서 새로운 노드 2개는 각각 그 중간값보다 작은 keys의 모임과 큰 keys의 모임이 된다.
    - AVL tree, BST의 left, right 느낌이 솔솔 난다.
