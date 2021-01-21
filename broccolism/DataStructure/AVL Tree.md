# What for?

- To be BALANCED!
- '탐색'을 잘 하려면 잘 찾기만 해서는 안된다. 잘 찾을 수 있도록 저장해야한다.
  - array보다는 binary search tree가, binary search tree 보다는 AVL tree가 탐색 시간을 더 줄여준다.
- 기존 binary search tree가 갖고 있던 문제점
  - 저장 순서에 따라 search 알고리즘의 성능 차이가 크게 난다.
    - 왜냐하면 저장 순서에 따라 전체 트리의 height가 달라지기 때문이다.
    - 최악일때는 O(N)이라는 끔찍한 결과를 낳는다.
      - 키 값이 1, 2, 3, ... 혹은 10, 9, 8, ... 처럼 늘어나거나 줄어들 때의 결과다.
- 일반 binary search tree에 비해 AVL tree가 갖는 장점
  - 저장 순서에 관계없이 탐색의 성능을 일정하게 유지할 수 있다.
  - how?
    - 균형을 잡아서.
    - 이런식으로 균형을 잡아 성능 불균형을 개선한 트리는 AVL트리 외에도 여러가지가 있다.
      - 2-3 트리, 2-3-4 트리, Red-Black 트리, B 트리, B+ 트리, ...

# 그러면 균형을 어떻게 잡나

- 균형 잡기(=rebalancing)의 핵심 요소 2가지
  1. Balance Factor
  2. Rotation
- 균형 잡기가 실행되는 타이밍
  - = 균형이 깨졌을 때
    - 새 노드를 넣을 때
    - 노드를 뺄 때
      - 당연하지만 검색할 때에는 균형잡아줄 필요가 없다. 아니, 균형을 잡을 일이 생기면 잘못 만든거다.

### Balance Factor

- 언제, 어디서 균형을 잡을 지 기준점이 되는 값. 각 노드별로 갖는 값으로, 아래 수식으로 정의된다.

```markdown
(balance factor) = (left subtree's height) - (right subtree's height)
```

- rebalancing은 balance factor의 절댓값이 2 이상일 때 일어난다.
  - 좀 더 엄밀히 말하자면 AVL 트리가 제대로 만들어졌다면 balance factor의 절댓값이 2일 때 일어나야한다.
    - 이 값이 3이나 4가 될 때까지 방치했다는건 이미 균형 잡는게 제대로 이루어지지 않았다는것이고, 잘못 만들었다는 뜻이다.
  - 그리고 절댓값이 2 이상이 된 노드를 기준으로 일어난다.

### Rotation

- rebalancing은 rotation을 통해 이루어진다.
- 상황에 따라 적절한 rotation 기법을 사용해서 모든 노드의 balance factor가 2 미만이 되도록 만들어야한다.

### Rebalancing해야 하는 상황

= 균형이 무너진 상황

- 4가지 상황으로 일반화할 수 있다.

  - 순서대로 LL, RL, LR, RR 상태
    ![unbalanced-avl-trees](https://user-images.githubusercontent.com/45515332/105164579-a1848b80-5b58-11eb-8793-ba4e6b643020.png)

- LL, RR 상황에서 균형을 잡기 위해 하는 rotation을 각각 LL rotation, RR rotation이라고 부른다.
  - LL rotation이라고 왼쪽으로 2번, RR rotation이라고 오른쪽으로 2번 회전하는게 아니다.

### LL rotation, RR rotation

- 위의 그림에서 LL rotation 과정은 다음과 같다.
  1. 3번 노드의 right subtree를 5번 노드의 left subtree로 만든다.
  2. 새 left subtree와 함께 5번 노드를 3번 노드의 right subtree로 만든다.
- 위의 그림에서 RR rotation 과정은 다음과 같다.
  1. 7번 노드의 left subtree를 5번 노드의 right subtree로 만든다.
  2. 새 right subtree와 함께 5번 노드를 7번 노드의 left subtree로 만든다.

### RL state, LR state에서의 rotation

- 먼저 RR이나 LL 상황을 만드는 것을 시작으로 한다.
- 위의 그림에서 RL 상황을 해결하는 과정은 다음과 같다.
  1. LL rotation
  2. RR rotation
- 위의 그림에서 LR 상황을 해결하는 과정은 다음과 같다.
  1. RR rotation
  2. LL rotation
