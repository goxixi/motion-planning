#include "RRT/RRT.h"
#include "graph_search/dijkstra.h"

int main(void)
{
    string picture = "../map/newmap.png";
    Map map(picture, 100, 20, 500, 600); // map.png
    // Map map(picture, 400, 400, 400, 50); // map3.png
    // RRT rrt(map);
    // rrt.findPath();
    Dijkstra dijkstra;
    dijkstra.setMap(map);
    dijkstra.findPath();

    return 0;
}
