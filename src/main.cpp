#include "RRT/RRT.h"
#include "graph_search/dijkstra.h"
#include "graph_search/a_star.h"

int main(void){
    string picture = "../map/map1.png";
    GripMap map(picture, 100, 20, 500, 600); // map.png
        
    // GripMap map(picture, 400, 400, 400, 50); // map3.png
    // RRT rrt(map);
    // rrt.findPath();

    Dijkstra dijkstra;
    dijkstra.setMap(map);
    dijkstra.findPath();

    // AStar astar;
    // astar.setMap(map);
    // astar.findPath();


    return 0;
}
