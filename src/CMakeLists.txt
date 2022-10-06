find_package(OpenCV REQUIRED)

add_executable(RRT_PLANNER main.cpp)

target_link_libraries(RRT_PLANNER PRIVATE ${OpenCV_LIBS})