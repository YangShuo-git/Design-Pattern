# 观察者模式
add_executable(WeatherData WeatherData/main.cpp)

# 观察者模式
add_executable(Observer Observer/Observer.cpp)

# 生产者消费者模式
add_executable(ProducerAndConsumer ProducerAndConsumer/ProducerAndConsumer.cpp)

# 工厂模式
add_executable(Factory_simple Factory/Factory_simple.cpp)

# 懒汉模式
add_executable(Singleton_lh Singleton/Singleton_lh.cpp)

# 建造者模式
add_executable(Builder Builder/builder.cpp)

# 代理模式
add_executable(Proxy Proxy/proxy.cpp)

# 适配器模式
add_executable(Adapter Adapter/adapter.cpp)

# 生消模式需要pthread
target_link_libraries(ProducerAndConsumer pthread)

# 懒汉模式需要pthread
target_link_libraries(Singleton_lh pthread)