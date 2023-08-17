# 观察者模式
add_executable(Observer Observer/Observer.cpp)

# 生产者消费者模式
add_executable(ProducerAndConsumer ProducerAndConsumer/ProducerAndConsumer.cpp)

# 工厂模式
add_executable(Factory Factory/Factory.cpp)

# 这里需要pthread
target_link_libraries(ProducerAndConsumer pthread)