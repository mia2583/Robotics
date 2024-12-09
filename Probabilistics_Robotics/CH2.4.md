# CH 2.4

**2.4.1 Bayes Filters**

belief를 계산하는 가장 일반적인 알고리즘은 Bayes filter 알고리즘이다. 이 알고리즘은 measurement와 control data로부터 belief의 분산인 $bel$을 생성한다. 먼저 기본적인 알고리즘 구조를 살펴본다.

[테이블 2.1]
<br/>1: Algorithm Bayes filter $(bel(x_t−1), u_t, z_t)$:
<br/>2: &emsp;for all $x_t$ do
<br/>3: &emsp;&emsp;$\int\bar{bel(x_t)} = p(x_t | u_t, x*{t−1}) bel(x*{t−1}) dx*{t−1}$
<br/>4: &emsp;&emsp;$bel(x_t) = η p(z_t | x_t) \bar{bel(x_t)}$
<br/>5: &emsp;endfor
<br/>6: &emsp;return $bel(x_t)$

테이블2.1은 기본 Bayes filter 알고리즘의 의사코드이다. Bayes filter은 시간 t의 belief $bel(x_t)$은 시간 t-1의 $bel(x_{t-1})$로부터 도출되는 recursive 구조를 가진다. 시간 t-1에서의 $bel$은 control $u_t$와 measurement $z_t$를 입력으로 받는다.

Bayes filter 알고리즘은 두개의 주요 스텝으로 이루어져있다. 3번째 줄에서 state $x_t$에 대한 belief $\bar{bel(x_t)}$는 state $x_{t-1}$과 control $u_t$에 대한 prior belif를 계산한 합($\int$)으로 계산된다. 이 수식은 공식 2.12인 $p(x) = \int p(x|y)p(y)dy$ (continuous) 와 유사한 형태를 지니고 있다. 이 업데이트 스텝을 contorl update 또는 prediction이라고 한다.

두 번째 스텝은 measurement update라고 하는데, 4번째 줄에서 belief $\bar{bel(x_t)}$를 measurement $z_t$에 곱한다. 이렇게 곱해진 결과물은 확률값이 아니게 된다. 즉, 합이 1이 되지 않는다. 따라서 정규화 상수 η를 통해서 결과를 정규화해야한다.

이 모든 과정을 거치면 최종적인 belief $bel(x_t)$를 얻을 수 있다. (6번째줄)

알고리즘을 수행하기 위해선 y=0에서의 초기 belief $bel(x_0)$이 필요하다. $bel(x_0)$은 높은 확률을 가진 하나의 점으로 초기화(=full knowledge) 될 수도 있고, uniform한 분산(=full ignorance)을 가질 수도 있다. 주의할 점은 3, 4번째 줄에서 finite한 값이 만들어지도록 해야한다.

**2.3.2 Example , 2.4.3 Mathematical Derivation**

Bayes filter를 활용한 예제 문제와 수학적 유도 정리는 생략한다. 책을 따라서 계산하면 쉽게 이해할 수 있을 것이다.

**2.4.4 Markov Assumption**

Markov 가정 혹은 완전 상태 가정는 이 책을 이해하기 위한 기초적인 지식으로 필요로 한다. Markov 가정은 현재 상태 $x_t$를 알고 있고 과거와 미래의 데이터는 이와 독립적이다는 가정에서 시작한다. 얼마나 제약적인 가정임을 이해하기 위해서 예제를 살펴본다. 이동 가능한 로봇이 있다고 하자. $x_t$는 로봇의 위치를 의미하고, Bayes filter를 사용해서 위치를 예측한다. 아래 요인은 Markov 가정을 위반하는 원인이 된다.

- $x_t$에 포함되지 않은 환경의 모델링되지 않은 동적 요소

  &emsp;이동 중인 사람으로 인한 센서 측정값

- 확률 모델 $p(z_t|x_t)$ 와 $p(x_t|u_t,x_{t-1})$의 부정확성

  &emsp;로봇 위치 추정에 사용되는 지도가 잘못된 경우

- belif 함수의 근사 표현에 따른 오류

  &emsp;belif 함수를 grid나 Gaussian과 같은 근사 방식으로 표현하는 경우
  <br/>&emsp;(나중에 뒤에서 다룰 예정이다.)

- 로봇 제어 소프트웨어에서 여러 제어에 영향을 미치는 소프트웨어 변수

  &emsp;특정 변수가 제어 명령 전체 시컨스에 영향을 미치는 경우

많은 변수들이 상태를 표현하는데 사용되지만, Bayes filter 알고리즘 계산의 복잡성을 줄이기 위해 불확실한 상태 표현이 더 선호된다. 실제로 이러한 가정 위반에서도 Bayes filter 알고리즘은 동작한다. 따라서 모델링되지 않는 상태 변수의 영향이 무작위하게 나타나도록 상태를 정의하는 것이 중요하다.

**2.4.5 Representation and Computation**

Probabilistic robotics에서 Bayes filter는 다양한 방식으로 구현된다. 다음 두 챕터에서는 Bayes filter로부터 유도된 다양한 기술과 알고리즘을 살펴본다. 초기 belief와 measurement 그리고 상태 이동 확률에 따라 다른 기술이 사용될 수 있다. 이러한 기술들은 매우 특정한 상황에 적용될 수 있으므로 실제 상황에 적용하기 위해서는 belief를 최대한 근사해야한다. 이러한 근사는 상당히 어려운 문제이고, 모든 상황에 적용되는 최고의 답은 없다. 아래는 근사를 찾기 위해 고려해야 할 trade-off를 소개한다.

1. 계산 효율

   예를 들어, 선형 가우시안 근사법은 상태 공간의 차원에 대해 polynomial한 시간으로 belief를 계산할 수 있다. 또한 particle-based 기술은 정확도와 계산 효율성이 trade-off된다.

2. 근사의 정확성

   예를 들어, 선형 가우시안 근사법은 unimodal 분포만 가능하고, 히스토그램 표현 방식은 multi-modal 분포를 근사할 수 있지만, 정확도에 한계가 있다.

3. 구현의 쉬움

   알고리즘 구현의 어려움은 다양한 요소에 의해 결정된다. particle 표현 방식은 복잡한 비선형 시스템에 대해서도 생각보다 간단한 구현을 보여준다.
