find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

add_executable(PLANNER main.cpp)

target_link_libraries(PLANNER PRIVATE ${OpenCV_LIBS})