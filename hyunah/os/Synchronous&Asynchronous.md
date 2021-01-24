# [OS] 동기와 비동기

> 동기는 어떤 일이 끝난 후에 다음일을 하는 것, 비동기는 어떤 일이 끝나지 않더라도 다음 일을 수행할 수 있는 것이다.

---

## Blocking & None-Blocking

-   동기 & 비동기를 살펴보기 전에 blocking & none-blocking 먼저 살펴보자

### Blocking

![image](https://user-images.githubusercontent.com/42240771/105632605-686d5380-5e97-11eb-8819-5cf81e869240.png)

-   I/O 작업은 user level에서 직접 수행할 수 없고 kernel level로 들어가야 한다. 따라서 user level에서 kernel level로system call을 보내서 I/O 작업을 수행한다. 이때 application 단의 스레드에 block이 걸린다. (I/O 작업이 끝나기 전까지 반환되지 않기 때문) 그리고 kernel level에서 해당 I/O 작업이 끝나고 데이터를 반환하면 그때서야 application 단의 스레드에 걸렸던 block이 풀린다. 즉, application 단에서는 아무런 동작도 안하는 것처럼 보이는 것이다.
-   단점: cpu 낭비가 심함

### Non-Blocking

![image](https://user-images.githubusercontent.com/42240771/105632621-7a4ef680-5e97-11eb-8b21-ad80ac4fb698.png)

-   앞에서 설명한 blocking I/O 방식과 다르게 Non-blocing I/O 방식은 kernel level에서 I/O 작업을 수행하는 동안 user 단의 작업을 중단시키지 않는다. 즉, user가 system call을 보내면 kernel에서는 일단 바로 결과를 반환한다. 여기서 반환하는 값은 그 순간 가져올 수 있는 데이터에 해당한다. 이후에 계속적으로 가져올 수 있는 데이터를 축적한다.
-   단점: 가져올 수 있는 데이터를 축적하는 과정에서 user level에서 원하는 사이즈가 되었는지 계속해서 확인해줘야 한다.(polling) 이 과정에서 수많은 클라이언트의 요청이 동시 다발적으로 일어나면 cpu에 부담이 될 수 있다.

---

## Synchronous & Asynchronous

### Synchronous

![image](https://user-images.githubusercontent.com/42240771/105632632-8d61c680-5e97-11eb-9ba8-daf9233832db.png)

-   Synchronous는 system call이 끝날때까지 기다리고 결과물을 가져온다.

### Asynchronous

![image](https://user-images.githubusercontent.com/42240771/105632636-9488d480-5e97-11eb-8926-20d27e1ad21f.png)

-   Asynchronous에서는 system call이 완료되지 않아도 기다리지 않는다. 나중에 완료가 되면 그때 결과물을 가져온다.

---

> Blocking/Non-Blocking은 호출되는 함수가 바로 리턴하느냐 마느냐가 포인트

> Synchronous/Asynchronous는 호출되는 함수의 작업 완료 여부를 누가 신경쓰냐가 포인트

---

## Blocking VS Synchronous

-   Synchronous: 시스템의 반환을 기다리는 동안 waiting queue에 머무는 것이 필수가 아님, 호출하는 함수가 호출되는 함수의 작업 완료 후 리턴을 기다리거나, 또는 호출되는 함수로부터 바로 리턴 받더라도 작업 완료 여부를 호출하는 함수 스스로 계속 확인하며 신경쓰면 synchronous
-   Blocking: 시스템의 반환을 기다리는 동안 waiting queue에 머무는 것이 필수, 호출된 함수가 자신의 작업을 모두 마칠 때까지 호출한 함수에게 제어권을 넘겨주지 않고 대기하게 만들면 blocking
    둘다 시스템의 반환을 기다린다는 측면에서 같은 개념

## Non-Blocking VS Asynchronous

-   Asynchronous: system call이 반환될 때 실행된 결과와 함께 반환될 경우, 호출되는 함수에게 callback을 전달해서, 호출되는 함수의 작업잉 완료되면 호출되는 함수가 전달받은 callback을 실행하고, 호출하는 함수는 작업 완료 여부를 신경쓰지 않으면 Asynchronous
-   Non-Blocking: system call이 반환될 때 실행된 결과와 함께 반환되지 않는 경우, 호출된 함수가 바로 리턴해서 호출한 함수에게 제어권을 넘겨주고, 호출한 함수가 다른 일을 할 수 있는 기회를 줄 수 있으면 Non-Blocking

---

## Non-Blocking & Synchronous

-   그럼 이 조합을 살펴보자. 위의 설명에 따르면 Non-Blocking & Synchronous는 호출되는 함수는 바로 리턴하고 호출하는 함수는 작업 완료 여부를 신경쓴다. 즉, 함수를 호출하고 바로 반환 받아서 다른 작업을 할 수 있지만(non-blocking) 호출 후 수행되는 작업이 완료되는 것은 아니며, 호출하는 함수가 호출된 함수 쪽에 작업 완료 여부를 계속 묻는다.

## Blocking & Asynchronous

-   이 조합은 위의 설명에 따르면 호출되는 함수가 바로 리턴하지 않고, 호출하는 함수는 작업 완료 여부를 신경쓰지 않는 것이다.
