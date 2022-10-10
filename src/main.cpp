#include "RRT/RRT.h"
#include "graph_search/dijkstra.h"

int main(void)
{
    string picture = "../map/newmap2.png";
    // Map map(picture, 100, 20, 500, 600); // newmap.png
    Map map(picture, 400, 400, 50, 50); // newmap2.png
    // RRT rrt(map);
    // rrt.findPath();
    Dijkstra dijkstra;
    dijkstra.setMap(map);
    dijkstra.findPath();

    return 0;
}
