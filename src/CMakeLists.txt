# 观察者模式
add_executable(Observer Observer/Observer.cpp)

# 生产者消费者模式
add_executable(ProducerAndConsumer ProducerAndConsumer/ProducerAndConsumer.cpp)

# 工厂模式
add_executable(Factory Factory/Factory.cpp)

# 懒汉模式
add_executable(Singleton Singleton/Singleton_lh.cpp)


# 生消模式需要pthread
target_link_libraries(ProducerAndConsumer pthread)

# 懒汉模式需要pthread
target_link_libraries(Singleton pthread)