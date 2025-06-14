cmake_minimum_required(VERSION 3.10)
project(ProcessScheduler)

set(CMAKE_CXX_STANDARD 11)

include_directories(
	${CMAKE_SOURCE_DIR}/include
)
file(GLOB_RECURSE CPPS "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(ProcessScheduler
	main.cpp
	${CPPS}
)

# 链接线程库（如果需要）
target_link_libraries(ProcessScheduler PRIVATE pthread)