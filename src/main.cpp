#include "RRT/RRT.h"
#include "graph_search/dijkstra.h"
#include "graph_search/a_star.h"
#include "mathematics/obvp_solver.hpp"

int main(void)
{
    string picture = "../map/map1.png";
    Map map(picture, 100, 20, 500, 600); // map.png
    
    // Map map(picture, 400, 400, 400, 50); // map3.png
    // RRT rrt(map);
    // rrt.findPath();

    // Dijkstra dijkstra;
    // dijkstra.setMap(map);
    // dijkstra.findPath();

    AStar astar;
    astar.setMap(map);
    astar.findPath();


    return 0;
}
