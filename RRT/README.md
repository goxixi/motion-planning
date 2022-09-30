# RRT planner

# demos

# dependence
## opencv 4.5.2
1.download the Sources(.zip) version from ``
2. 
```
unzip opencv-4.5.2.zip
mkdir opencv-4.5.2/build
cd opencv-4.5.2/build
cmake -D CMAKE_BUILD_TYPE=Release -D OPENCV_GENERATE_PKGCONFIG=YES ..
make -j4
sudo make install
```
3.
```
sudo find / -iname opencv4.pc
sudo vim /etc/profile.d/pkgconfig.sh
```
add the following sentence at the bottom of the file and save it
```
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
```
check if it success
```
pkg-config --libs opencv4
```

# make

# run

# modify some params
1. start_point
2. goal_point
3. stepsize
4. the range of goal_point
