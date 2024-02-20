# CH 2.3

환경은 역동적이고 내부 상태를 지닌다. 로봇은 이러한 환경을 센서를 통해 정보를 얻을 수 있으나 센서의 데이터 값은 노이즈를 포함하며, 직접적으로 관찰하는 것이 어렵다. 로봇은 환경의 상태에 따라 internal belief를 생성하고, 환경 상태 또한 로봇의 행동에 영향을 받는다.

**2.3.1 State**

환경은 상태에 따라 정의된다.  환경을 미래에 영향을 줄 수 있는 로봇과 그 환경의 모든 정보들로 해석하면 이해가 쉽다. 어떠한 상태 변수는 이동하는 사람과 같이 시간에 따라 달라지기도 하고, 또 다른 어떠한 상태는 벽과 같이 그 상태로 계속 남는다.

- dynamic state
- static state

주변 환경 뿐만 아니라 로봇의 pose, velocity 등과 같은 로봇의 정보 또한 상태 변수에 속한다.

상태를 x, 특정 t에서의 상태를 $x_t$와 같이 표현한다.

- Pose : global coordinate frame에 대한 로봇의 상대적인 위치와 각도. 보통 3개의 Cartesian coordinates, 3개의 angular orientation(pitch, roll and yaw)로 나타낸다.

대부분의 로보틱스에서는 $x_t$는 continous하다. 예를 들면 로봇의 pose는 실제 좌표 시스템에 나타낼 수 있다. 반면에 discrete할 수도 있는데 예를 들어 binary state를 가지는 변수가 있다. 두가지 모두 특징을 가지는 경우엔 hybrid라 한다.

**2.3.2 Environment Interaction**

로봇과 환경 사이에는 두 가지 타입의 상호작용이 있을 수 있다. 로봇은 actuators를 통해 환경에 영향을 줄 수 있고, actuators는 센서를 통해서 상태의 정보를 얻을 수 있다. 두 가지 상호작용은 동시에 발생할 수 있으나 이 책에서는 이를 분리하여 고려한다.

- Environment sensor measurements
    
    로봇의 센서를 사용해 주변 환경의 상태를 얻으려는 과정을 perception이라 한다. Perceptual interaction의 결과를 measurement, observation 혹은 percept라 부른다. 센서의 관측 결과는 약간의 delay를 동반한다.
    
- Control actions
    
    로봇의 모션, 물체의 조작과 같은 control actions는 주변 환경을 변화 시킨다. 로봇이 어떠한 액션을 취하지 않더라도 환경은 계속하여 변한다. 따라서 지속성을 위해 우리는 로봇이 항상 control action을 행한다고 가정한다.
    

이론적으로 로봇은 과거의 모든 센서의 관측 값과 control actions의 기록을 저장하고 있다. 이러한 기록들을 data라고 하며, 상호작용과 마찬가지로 데이터 또한 두 가지 다른 종류를 지닌다.

- Environment measurement data
    
    사진과 같이 환경의 상태에 대한 순간적인 정보를 의미한다. t시간에 관측된 정보는 $z_t$로 표현한다. 이 책 대부분에서는 특정 시간동안 하나의 관측 정보를 지닌다고 가정하지만 특정 시간동안 여러 관측 정보를 지닐때는 아래와 같이 표현할 수 있다.
    
    $$z_{t1:t2} = z_{t1}, z_{t1+1},z_{t1+2}+...+z_{t2}$$
    
- Control data
    
    로봇의 속도와 같이 환경의 변화하는 상태에 대한 정보를 지니고 있다. 예를 들어 로봇의 속도를 10cm/s으로 정의하면, 로봇의 위치는 5초 후에 대략 50cm를 이동한다. 따라서 상태의 변화에 대한 정보를 전달한다. 또 다른 예시로는 odometers가 있다. odometry는 센서임에도 control action에 대한 영향을 다루기 때문에 control data로 분류된다.  Control data는 $u_t$로 표현한다.
    

 Environmet perception은 환경 상태에 대한 정보를 주기 때문에 로봇의 지식을 늘려주지만, motion은 센서의 노이즈와 환경의 확률성 때문에 로봇의 지식을 줄인다.

**2.3.3 Probabilistic Generative Laws**

상태의 변화와 관측은 확률적 법칙을 따른다. 주로 $x_t$은 $x_{t-1}$ 상태에서 확률에 따라 도출된다. $x_t$는 이전에 관측된 정보에 따라 달라질 수 있으므로 $x_t$의 probabilistic distribution은 다음과 같이 표현할 수 있다. 

$$
p(x_t | x_{0:t-1}, z_{1:t-1}, u_{1:t})
$$

하지만 사실 $x_{t-1}$ 상태만 안다면 수행한 control action $u_t$가 중요하다. 따라서 아래와 같이 다시 표현할 수 있다.

$$
p(x_t | x_{0:t-1}, z_{1:t-1}, u_{1:t}) = p(x_t | x_{t-1}, u_t)
$$

Probabilistic robotics에서 중요한 또 다른 하나는 belief이다. belief는 로봇이 환경에 대해 알고 있는 정보를 반영하지만 로봇은 정보를 직접적으로 얻을 수 없기 때문에 관측한 데이터를 바탕으로 추론해야 한다. 따라서 실제 정보와 belief는 어느 정도 차이가 있을 수 있다. 이 책에서 belief는 state of knowlede, information state와 같은 단어로 표현할 수도 있다. 

Belief는 조건부 확률 분포로 표현되며, 실제 상태와 상관없이 가능한 가설에 따른다.  

$$
bel(x_t) = (x_t|z_{1:t}, u_{1:t})
$$

Belief는 지금까지 관측된 모든 정보 $z_{1:t}$ 와 모든 control $u_{1:t}$ 를 바탕으로 계산할 수 있다. 하지만 이러한 $bel(x_t)$는 관측 $z_t$가 일어난 후임을 알 수 있다.

따라서 probability distribution은 주로 2단계로 이루어진다. $\bar{bel(x_t)} = (x_t|z_{1:t-1}, u_{1:t})$를 예측라 하며 이후 correction을 통해 $\bar{bel(x_t)}$에서 $bel(x_t)$를 구한다.
