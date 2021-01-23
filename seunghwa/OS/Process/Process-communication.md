# Process-communication
여기서는 IPC에 관해서 알아볼 것이다

## IPC란...
IPC는 interProcess Communication의 약자이다</br>
말 그래도 프로세스간의 통신이라고 볼 수 있다</br>
통신이기 때문에 `send data`와 `receive data`로 나뉘어져 있다</br>

프로세스끼리 독립적으로 실행이 된다면 IPC를 전혀 고려할 필요가 없다</br>
`독립적`: 서로 데이터 공유가 없으며 간섭하지 않는다는 뜻이다</br>
프로세스끼리 협력적인 관계라면 IPC가 필요하다</br>
`협력적`: 영향을 주고받으며 서로 데이터를 공유한다

## Shared Memomry (공유 메모리)
공유 메모리 방식은 가장 흔한 패러다임인 Producer-Consumer 방식으로 볼 수 있다</br>
`Producer` : 데이터를 생성하는 곳이다</br>
`Cosumer` : 생성된 데이터를 소비하는 곳이다</br>
예를 들어서 브라우저와 웹서버의 관계로 볼 수 있다</br>
왜냐하면 브라우저는 웹페이지를 `요청(consume)`하고 웹 서버는 html 파일을 `생성(producer)`해서 보내주기 때문이다

![sharedMemory](./img/Process-shardMemory.png)

![region](./img/Process-sharedMemory-region.png)

물론 그림에 나와있는것 처럼 가운데에 위치하지 않을 수도 있지만</br>
메모리 위에 존재함으로써 프로세스에서 접근이 가능하다고 보면 될것 같다

## Message Passing (메시지로 주고받기)