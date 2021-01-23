# General Types

일반적으로 **어떤** language든, 아래 세 종류의 type을 사용할 수 있다.

1. `Each of(Product)`: `t` 는 `t1`, `t2`, `...`, `tn` 의 모든 value를 갖는다.

   e.g) Tuple in SML: (3, true) 는 3과 true 모두를 의미한다.

2. `One of(sum)`: `t` 는 `t1`, `t2`, `...`, `tn` 중 하나의 value만을 갖는다.

   e.g) `int option` in SML: 특정 int type 값 하나를 갖거나, 아무런 값을 갖지 않을 수 있다. (NONE의 경우.)

3. `Self reference(recursive)`: `t` 는 또다른 `t` 의 value를 가질 수 있다.

e.g) `int list` in SML: int list는 int, int list의 value 모두를 가질 수 있고 또한 아무런 값을 가지지 않을 수도 있다.([ ]의 경우.) 따라서 int list는 위의 세가지 타입 모두를 사용한다고 볼 수 있다.

---

# Records

- Syntax

```elm
(* building *)
{f1 = e1, f2 = e2, f3 = e3, ..., fn = en}

(* accessing *)
#fieldname e
```

`f1`, `f2`, ..., `fn` 을 `field` 라고 부른다.

- Type-checking

각 field는 서로 다른 type을 가질 수 있다. f1 은 e1, f2는 e2, .. , fn 은 en의 type을 갖는다. 전체 record는 `{f1: t1, f2: t2, ..., fn: tn}` type을 갖는다.

- Evaluation

각 fiedl는 서로 다른 value를 가질 수 있다. 전체 record는 `{f1 = v1, f2 = v2, ..., fn = vn}` 이라는 value를 갖는다.

사실 ML은 이 방법을 사용해서 tuple을 정의하고 있다. 만약 우리가 `(1111, "Julia")` 라는 튜플을 만들었다면 ML은 이것을 `{1 = 1111, 2 = "Julia"}` 라는 레코드로 본다는 것이다.

튜플의 각 원소에 어떻게 접근했는지를 떠올려보자. 위의 예시에서 "Julia"라는 두 번째 원소를 얻고 싶다면 `#2 (튜플의 이름)` 이라는 표현을 썼다. 이는 레코드에서 각 원소를 얻는 방법과 동일하다!

## Syntactic Sugar

> Tuples are just **\*syntactic sugar** for records with fields named 1, 2, ..., n"\*

앞서 배웠던 튜플을 여기서 다시 생각해 볼 수 있다. 튜플의 모든 semantics를 레코드를 이용해 표현할 수 있다. 이럴 때 우리는 레코드는 튜플의 syntactic sugar 라는 표현을 쓸 수 있다.

이런 관계의 또 다른 예시로는 `andalso` 와 `orelse` , 그리고 `if then else` 간의 관계가 있다.

_참고로 ML에서 andalso, orelse는 **short-circuit**을 사용한다. 그래서 ..._

```erlang
true orelse (null (tl p[)); (* true *)
(null (tl [])) orelse ture; (* exception! *)
```

\_이와 같은 결과가 나타난다. 원래 `tl []` 자체가 exception인데, 윗줄에서는 orelse의 첫 번째 operand 때문에 이미 `true`라고 판단하고 두 번째 operand는 넘어가버리기 때문이다.

---

# Datatype bindings

one-of type을 만드는 특이한 방법이 있다.

```erlang
datatype mytype = TwoInts of int * int
				| Str of string
				| Pizza
```

datatype은 말그대로 새로운 자료형을 정의할 수 있게 해준다. 위의 코드를 실행시키면 현재 환경에 `mytype`이라는 새로운 type이 생긴다. 여기서 datatype은 one-of type이기 때문에

1. int \* int
2. string
3. Pizza

위의 세가지 타입 중 한가지를 갖게 된다. 새로운 타입이 생겼으니 새로운 constructor 역시 환경에 추가된다. 총 3가지 생성자가 추가되는데, 아래와 같다.

1. TwoInts : int \* int → mytype
2. Str: string → mytype
3. Pizza: mytype

즉, 생성자는 새로운 datatype과 같은 type을 갖는 value를 만들어주는 `function` 이거나 (1번과 2번) value 그 자체이다. 3번의 `Pizza` 는 그 자체로 생성자이자 value가 되는 것이다.

필자는 그동안 이런 datatype의 필요성을 전혀 느끼지 못했다. 오히려 datatype을 처음 접했을 때 이것을 이해하기 어려웠다. 하지만 그동안 필요성을 느끼지 못했던건 datatype의 존재 자체를 몰랐기 때문이 아니었을까? 실제로 필자는 이 수업에서 datatype을 알게 된 후 파이썬으로 간단한 프로그램을 짜면서 파이썬에도 datatype과 같은 타입이 있으면 참 좋겠다고 느낀 적이 있다.

- 파이썬으로 만드려던 프로그램은 [색상 코드 변환기]였다. 사용자가 RGB로 입력한 색상값을 hex로, hex로 입력한 값은 RGB식 표현법으로 바꾸어 return하는 프로그램이다.
- 그런데 이게 생각보다 만들기 까다로웠다. 만약 input이 RGB format이라면 int값 3개를, hex format이라면 int값 1개를 받아서 저장해야하기 때문이다. output을 낼 때에도 마찬가지이다.
- 아직 프로그램을 완성하진 않아 여러가지 방식을 생각해보고는 있지만 파이썬에도 SML의 datatype과 비슷한 형식이 있었다면 주저하지 않고 그것을 썼을 것이다!

## Accessing Datatype

datatyp뿐만 아니라 `one-of type` value 모두에 해당되는 이야기이다. ML에서는 강력한 case expression을 제공한다. 오히려 if-then-else를 쓸 때보다 훨씬 좋다. 그 이유를 알아보자.

우선 ML에서 case expression은 아래와 같이 사용할 수 있다.

```erlang
(* f has type (mytype -> int) *)
fun f x =
	case x of
		  Pizza => 3
		| TwoInts(i1, i2) => i1 + i2
		| Str s => String.size s
```

함수 `f`의 argument인 `x` 에 따라 return value를 계산하는 방식을 달리 하는 경우이다.

### tip SML에서 함수의 인자가 하나뿐인 경우 괄호를 생략할 수 있다

- 나중에 또 나올 이야기이니 기억해두자.

아무튼 다시 본론으로 돌아가서 함수 `f` 의 동작을 좀 더 자세히 살펴보자.

1. `x` 가 `Pizza` 인 경우: return 3
2. `x` 가 `TwoInts` 타입인 경우: 두 정수를 더해서 return
3. `x`가 `String` 타입인 경우: `x` 의 길이를 return
