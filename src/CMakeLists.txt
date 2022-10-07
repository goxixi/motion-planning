find_package(OpenCV REQUIRED)

add_executable(PLANNER main.cpp)

target_link_libraries(PLANNER PRIVATE ${OpenCV_LIBS})