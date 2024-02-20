# CH 2.1 ~ 2.2

## **2.1 Introduction**

로봇의 정확한 위치와 주변 물체에 대한 모든 정보가 있다면 로봇의 이동은 어렵지 않게 실행할 수 있다. 하지만 대부분 이러한 정보를 아는 것이 어려우므로 로봇은 센서 데이터로부터 현재 상태를 예측한다. 

센서로부터 얻은 데이터는 전체 정보의 일부이며, 노이즈를 포함한 상태이다. State estimation은 이러한 데이터로부터 원래 상태 정보를 복원하는 역할을 하며, probabilistic state estimation algorithm은 가능한 모든 상태에 대한 belief distribution을 계산한다.

## 2.2 Probabilistic Inference

Probabilistic Inference이란 다른 random variable과 관찰된 데이터를 바탕으로 새로운 random variable을 추론하는 것으로 random variable을 X, X가 가질 수 있는 특정한 값을 x라 하면, p(X=x)로 표현할 수 있다. 또한 각 확률은 항상 양수의 값을 가진다.

Random variable의 모든 x 값에 대한 확률의 합은 1이며 아래와 같이 표현할 수 있다.

$$
\sum_x p(X=x) = 1
$$

보통 식 p(X=x)와 같이 다 적기 보다는 P(x)와 같이 간단하게 표현한다.

이 책의 대부분의 기술들은 연속적인 공간에서 정의되며, random variable 또한 연속적인 값을 가진다. 특별히 명시되어 있지 않는 한, continuous random variable은 probability density functions(PDF)를 지닌다. 평균이 $\mu$이고, 분산이 $\sigma^2$인 정규분포의 PDF는 아래와 같은 Gaussian 함수 형태로 주어진다.

$$
(2.3): p(x) = (2\pi\sigma^2)^\frac{1}{2} exp(-\frac{1}{2}\frac{(x-\mu)^2}{\sigma^2})
$$

앞으로 정규분포는 $N(x;\mu, \sigma^2)$ 형태로 축약해서 사용한다. 위의 가우시안 함수는 x를 스칼라 값으로 가정한다. x가 muti-dimensional vector 형태로 주어지면 이를 multivariate normal distribution이라 하며, 아래와 같은 density function을 가진다.

$$
(2.4): p(x) = det(2\pi\sum)^\frac{-1}{2} exp(-\frac{1}{2}(x-\mu)^T\sum^{-1}(x-\mu))
$$

위에서 $\sum$은 covariance matrix라 하며, 정치행렬이자 대칭행렬이다. 식 (2.4)는 $\sum = \sigma^2$ 인 (2.3)의 특수한 형태이다. discrete probability distribution의 PDF 적분은 항상 1이다. 

$$
p(x,y) = p(X=x \ and \  Y=y)
$$

두 random variable X, Y의 joint distribution은 위와 같이 표현할 수 있으며, 만약 두 random variable이 독립인 경우에는 $p(x, y) = p(x)p(y)$로 나타낼 수 있다.

만약 우리가 하나의 random varible의 값을 알고 있는 경우에 다른 random variable의 확률을 표현하고 싶다면 아래와 같은 표현식을 가지며 조건부 확률이라 칭한다.

$$
p(x|y) = (pX=x | Y=y) = \frac{p(x,y)}{p(y)}
$$

만약 X, Y가 독립이면 p(x|y) = p(x)가 된다. 즉, Y의 값을 아는 것이 X의 확률을 구하는데 아무 도움이 되지 않는다는 것을 의미한다.

$$
p(x|y) = \frac{p(y|x)p(x)}{p(y)} = \frac{p(y|x)p(x)}{p(y)}\sum_{x_0}p(y|x_0)p(x_0)
$$

p(x)는 prior probability distribution이라 하고 y는 data라 부른다.  또한 p(x|y)는 X에 대한 posterior probability distribution로 정의한다.

$p(y)^{-1}$을 $\eta$라 하면 $p(x|y) = \eta p(y|x)p(x)$라 표현할 수 있다. η  기호는 최종 결과가 1에 정규화되어 있음을 의미한다.

$$
p(x|y,z) = p(y|x,z)p(x|z)/p(y|z)
$$

$$
p(x,y|z) = p(x|z)p(y|z)
$$

위와 같이 표현할 수 있으며 또한 위의 식을 바탕으로 p(x|z) = p(x|z,y)와 p(x|z) = p(y|z,x)로 도출할 수 있다. 하지만 conditional independence가 정말로 independence를 의미하지 않기 때문에 위의 식이 p(x,y) =p(z)p(y)을 의미하진 않는다. 

probability distribution의 엔트로피는 아래와 같이 표현된다.

$$
H_p(x) = E[-log_2p(x)] = -\sum_xp(x)log_2p(x)
$$

엔토로피는 x가 가지는 값에 대한 정보량을 의미한다. discrete 상황에서 $-log_2p(x)$는 x를 인코딩하는데 필요한 비트의 수를 의미하며, p(x)는 x가 관찰되는 확률을 의미한다. 따라서 엔트로피는 로봇의 정보를 모으는데 사용되며, 특정 행동 수행의 결과로 로봇이 얻는 정보를 표현한다.
