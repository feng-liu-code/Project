add_executable(client client.cpp)

# 链接线程库（Linux 必须）
target_link_libraries(client pthread)