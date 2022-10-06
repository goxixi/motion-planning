#include "RRT.h"

int main(void)
{
    string picture = "../map/newmap.png";
    Map map(picture, 100, 20, 500, 600);
    RRT rrt(map);
    rrt.findPath();
    return 0;
}
