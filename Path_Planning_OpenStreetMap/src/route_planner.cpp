#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel& model, 
                           float start_x, 
                           float start_y, 
                           float end_x, 
                           float end_y)
                           : m_Model(model) 
{   
    // Convert inputs to percentage:
    // Since the nodes store their coordinates between 0-1, 
    // and user is supposed to input the floats from 0-100
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node* current_node) {

    std::vector<RouteModel::Node> path_found;
    // keep looping until it finds the start node, whose parent is nullptr
    RouteModel::Node* curNode = current_node;
    while (!curNode) {
        path_found.push_back(*curNode);
        // Also keep track of the total path distance
        if (!curNode->parent) this->distance += curNode->distance(*curNode->parent); 
        curNode = curNode->parent;
    }

    // Scale by multiplying by the model's scale
    this->distance *= m_Model.MetricScale();

    return path_found;
}
