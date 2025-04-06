## 1. 기능
간단한 publish, subscribe 예제
- 메세지를 publish하면 subscriber가 메세지를 읽어온다.

## 2. 실행 방법

1. cpp_pubsub 폴더 아래에서 빌드를 한다.

    ```
    colcon build
    ```

2. 워크스페이스의 환경 설정을 불러온다. 
    ```
    . install/setup.bash
    ```

3. 퍼블리셔를 실행한다.
    ```
    ros2 run cpp_pubsub simple_publisher
    ```

4. 서브스크라이버를 실행한다.
    ```
    ros2 run cpp_pubsub simple_subscriber
    ```

## 3. 출력 예시

```
# 터미널 1 : ros2 run cpp_pubsub simple_publisher
[simple_publisher]: publishing at 1 Hz

# 터미널2 : ros2 run cpp_pubsub simple_subscriber
[simple_subscriber]: I heard: Hello ROS2 - counter: 1
[simple_subscriber]: I heard: Hello ROS2 - counter: 2
[simple_subscriber]: I heard: Hello ROS2 - counter: 3
...

```