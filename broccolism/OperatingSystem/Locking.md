# Race Condition

- **race condition**: 서로 다른 프로세스가 같은 data 하나에 접근하거나 그 값을 바꾸려 하는 상황
  - 이런 상황이 생기면 같은 동작을 하더라도 결과값이 달라질 수 있다. 순서가 달라질 수 있기 때문!
- race condition을 막는 가장 simple하고 안전한 방법은 **locking**을 사용하는 것이다.

### Mutual Exclusion

단 하나의 프로세스(혹은 스레드)만이 특정 영역에 접근할 수 있도록 하는 것. 즉, 다른 프로세스는 해당 프로세스가 작업을 끝내기 전까지 그 영역에 접근하지 못하게 막아주는 것.

- locking을 통해 mutual exclusion을 달성할 수 있다.

# What is Lock

- **lock**: 다수의 프로세스(혹은 스레드)가 실행 중인 환경에서 resource 접근에 대한 제한을 거는 **synchronization mechanism**
  - lock을 통해 mutual excusion을 달성 할 수 있다는 말은 곧,
  - lock을 건 시점에는 단 하나의 CPU만 code를 실행될 수 있다는 뜻이다.
- lock은 **critical section**을 보호하는 역할을 한다.

  - **critical section**: race condition이 발생할 수 있기 때문에 수행 시 해당 영역을 보호해야 할 필요가 있는 section.
  - e.g) in xv6

  ```c
  // filedup function in file.c
  // Increment ref count for file f.
  struct file* filedup(struct file *f)
  {
  	acquire(&ftable.lock);
  	if(f->ref < 1)
  		panic("filedup)";
  	f->ref++;
  	release(&ftable.lock);
  	return f;
  }
  ```

- xv6에서 `acquire`, `release` 함수는 미리 구현되어 있다.
  - 바꾸어 말하면 `acquire`, `release` 함수는 저절로 동작하는게 아니라 _누군가가_ 구현해야 할 사항이다.
  - 어떤 object를 `acquire`한 프로세스나 스레드가 있다면 해당 object가 `release`되기 전까지 다른 프로세스나 스레드가 그 object를 사용할 수 없다.
    - 만약 `release`되지 않은 object에 대해 추가로 `acquire`를 요청한다면 그걸 호출한 스레드(혹은 프로세스)의 코드 진행은 `acquire`에서 그대로 멈춰 `release`되기를 기다린다.
- xv6에서는 특정 object가 lock 되어있는지 아닌지를 구조체를 사용해서 나타낸다.

```c
// Mutual exclusion lock.
struct spinlock {
	unit locked;   // Is the lock held?

	// For debugging:
	char*name      // Name of lock.
	structcpu *cpu;// The cpu holding the lock.
	unit pcs[10];  // The call stack (an array of program counters)
                 // that locked the lock.
};
```

- `locked`: object가 lock 되었으면 1, 그렇지 않으면 0.
- `cpu`: object의 lock을 누군가 잡고 있다면 해당 프로세스의 정보를 알 수 있는 변수.

- race condition은 전역변수를 사용하는 곳 어디에서든 발생할 수 있다.
  - **acquire** 함수 내에서도 일어날 수 있다. parameter로 전역변수로 선언된 spinlock object를 받기 때문이다.
  - 그 spinlock object를 read/write하는 작업은 **_atomic_**하게 이루어져야만 한다!
    - 따라서 이를 위해 하드웨어의 도움을 받는다.
    - **xchg**함수: 첫번째 parameter로 전달된 곳에 두번째 parameter로 전달된 값을 저장하고, 첫번째 parameter가 가리키고 있던 곳에 원래 저장되어 있던 값을 return한다. 이 모든 일이 atomic하게 이루어질 수 있다!

그러니까 아래 두 코드는 **atomic**한지 아닌지의 여부만 빼고 완벽히 같은 코드이다.

```c
/* not atomic: can cause race condition!! */
for(;;) {
	if(!lk->locked) {
		lk->locked = 1;
		break;
	}
}

/* Atomic!! */
while(xchg(&lk->locked, 1) != 0)
	;
```

~~와 너무 똑똑해 . . . ......~~

- 이 과목을 배우면 배울수록 역시 소프트웨어 혼자 잘나서는 안되구나..를 깨닫게 된다.

# Deadlock

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/1e811dc4-bde3-4287-bae0-af78ee2bdec0/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/1e811dc4-bde3-4287-bae0-af78ee2bdec0/Untitled.png)

(시간의 흐름: 위 → 아래)

- 그러니까 여러 프로세스(혹은 스레드, 혹은 자기자신)가 서로(혹은 자기가 이미 잡고 있는)의 lock이 풀리기를 기다리면서 영원히 다음 코드를 실행할 수 없게 되는 상황을 뜻한다.

### Deadlock Prevention

- 위의 예시에서 일어난 데드락의 원인은 A, B의 락을 잡는 순서가 thread마다 달랐기 때문이다.
- 해결방법 1) Lock order를 동일하게 맞추는 것.
  - 그러니까 Thread1이 `acquire(&A.lock); acquire(&B.lock);`을 했다면 Thread2에서도 `acquire(&B.lock); acquire(&A.lock);` 이 아닌, `acquire(&A.lock); acquire(&B.lock);` 을 해줘야 하는 것이다.

# Interrupt Handler

interrupt handler 역시 deadlock을 발생시킬 수 있다. xv6는 이미 이를 유의하여 코드가 짜여져있으며 우리도 이를 신경써서 코드를 수정해야 한다.

- 핸들러 A가 interrupt a를 처리하기 위해 object `x`에 대한 lock을 **aquire**한 후에 interrupt b가 발생해버려서 핸들러 B가 호출된 경우, B 역시 `x`에 대한 lock을 잡을 필요가 있어 **aquire해버린다면..?**
  - 자기 자신이 이미 **aquire**한 lock을 다시 요청하고 있기 때문에 **aquire** 함수 내에서 `panic`을 부르며 시스템이 죽어버릴 것이다.

위와 같은 nested aquire 문제를 방지하기 위해서 xv6에서는 acquire, release 함수에 각각 코드 한 줄씩을 넣어두었다.

```c
/* in acquire() */
pushcli(); // disable interrupts to avoid deadlock.

/* in release() */
popcli(); //
```

- `pushcli`: 이 함수가 호출된 이후에는 다른 interrupt가 발생하여 해당 interrupt가 생겼음을 알게 되더라도 그것을 처리하지 않고 무시한다.
  - 여기서 주의할 점은 디바이스가 interrupt를 아예 보내지 못하게 하는 것이 아니라는 사실이다.
  - 디바이스는 멀쩡하게 interrupt를 잘 발생시키지만(e.g: timer interrupt) OS가 그것을 알고도 모른체 하겠다는 뜻이다.
- `popcli`: "다시 interrupt 처리를 시작하겠어!"

# Memory Ordering

read/write instruction 간의 reordering이 일어나버릴 경우, 또 예기치 못한 문제가 발생할 수 있다. reordering을 일으키는 주체는 하드웨어(CPU)와 컴파일러이기 때문에 이들에게 reordering을 하지 말라고 알려줄 방법이 필요하다.

- reordering은 보통 최적화를 위해 일어난다.
- x86 아키텍처의 경우 write instruction 간의 reordering은 하지 않지만 read instruction 간의 reordering은 일어날 수 있다고 한다.

```c
x = 42;
__sync_synchronize();
f = 1;
```

`__sync_synchronize` 함수로 간단하게 reordering을 막을 수 있다.

- "memory barrier"라고도 부른다.
- 이 함수는 xv6에서 만든게 아니라..
  - 무려 C의 built-in function이기 때문에 어떠한 헤더도 추가로 include하지 않고 바로 사용할 수 있다.
- 이 함수가 해주는 일은...
  - 해당 함수를 사용한 line을 기준으로 위쪽 section과 아래쪽 section의 reordering이 일어나면 안됨을 하드웨어 및 컴파일러에게 알려주는 작업!
