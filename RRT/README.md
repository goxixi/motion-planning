# RRT planner

## demos
<img src='demo01.gif' width=30%>　<img src='demo02.gif' width=28.8%>

## dependence
### cmake
### opencv 4
* [opencv 4.5.2](https://github.com/goxixi/motion-planning/wiki#how-to-configurate-opencv)

## make
```
mkdir RRT/build
cd RRT/build
cmake ..
make
```
## run
```
./bin/RRT_PLANNER
```
input `ctrl+c` to exit

## modify some params
1.start_point

main.cpp

2.goal_point

main.cpp

3.stepsize

RRT.h

4.the range of goal_point

RRT.h
