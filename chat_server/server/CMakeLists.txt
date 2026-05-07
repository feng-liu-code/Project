add_executable(server server.cpp)

# 链接线程库（Linux 必须）
target_link_libraries(server pthread)