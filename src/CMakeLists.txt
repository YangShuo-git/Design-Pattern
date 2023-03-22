# 观察者模式
add_executable(Observer Observer/Observer.cpp)

add_executable(ProducerAndConsumer ProducerAndConsumer/ProducerAndConsumer.cpp)

# 这里需要pthread
target_link_libraries(ProducerAndConsumer pthread)