# motion-planning

## Statement
I am learning motion-planning algorithms, so I plan to implement some classical ones in C++, which may make me understand them much deeplier.

By the way, this is my first public repo!

## demos
### 1.RRT
<img src='demo/demo01.gif' width=30%>　<img src='demo/demo02.gif' width=28.8%>

### 2.Dijkstra
<img src='demo/dijkstra_demo01.gif' width=30%>


### 3.A*
<img src='demo/astar_demo01.gif' width=30%>

## dependence
### 1.cmake
### 2.opencv 4
* [how to configurate opencv 4.5.2 in Linux](https://github.com/goxixi/motion-planning/wiki#how-to-configurate-opencv)
### 3.eigen3

## make
### Linux
```
mkdir build
cd build
cmake ..
make
```
## run
```
./bin/PLANNER
```
ps: please run the programme at the folder `"motion-planning/build"` of run it at `"motion-planning/build/bin"` with `./PLANNER`      

input `ctrl+c` to exit
