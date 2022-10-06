#include "RRT/RRT.h"

int main(void)
{
    string picture = "../map_demo/newmap.png";
    Map map(picture, 100, 20, 500, 600);
    RRT rrt(map);
    rrt.findPath();
    return 0;
}
