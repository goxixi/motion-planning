#include "RRT/RRT.h"
#include "graph_search/dijkstra.h"
#include "graph_search/a_star.h"

int main(void){
    string picture = "../map/map1.png";
    GripMap map(picture); // map.png
        
    common::Point point_start{500, 500};
    common::Point point_goal{100, 100};
    RRT rrt(map, point_start, point_goal);
    rrt.findPath();

    // Dijkstra dijkstra(map, 100, 100);
    // dijkstra.findPath();

    // AStar astar;
    // astar.setMap(map);
    // astar.findPath();


    return 0;
}
