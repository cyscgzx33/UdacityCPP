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
    while (curNode) {
        path_found.push_back(*curNode);
        // Also keep track of the total path distance
        if (curNode->parent) this->distance += curNode->distance(*curNode->parent); 
        curNode = curNode->parent;
    }

    // Scale by multiplying by the model's scale
    this->distance *= m_Model.MetricScale();

    return path_found;
}


void RoutePlanner::AStarSearch() {
    this->start_node->visited = true;
    this->open_list.push_back(this->start_node);
    
    RouteModel::Node* current_node = nullptr;
    while ( !open_list.empty() )
    {
        current_node = this->NextNode();
        if ( current_node->distance(*this->end_node) == 0 ) { // reach the end_node
            m_Model.path = this->ConstructFinalPath(current_node);
            return; // exit the A* search
        } else { // continue A* search
            AddNeighbors(current_node);
        }
    }
    
}

float RoutePlanner::CalculateHValue(const RouteModel::Node* node) {
    return node->distance( *(this->end_node) );
}

RouteModel::Node* RoutePlanner::NextNode() {

    // sort the open_list according to the f-value w/ custom compare func
    std::sort(this->open_list.begin(), this->open_list.end(), RoutePlanner::compareFValue);

    // Note: one can also implement the sort func together w/ compare func
    /* *************************************************************************************  *
    *  std::sort(oepn_list.begin(), open_list.end(), []const auto & _1st, const auto &_2nd) { *
    *   return _1st->h_value + _1st->g_value > _2nd->h_value + 2nd->g_value;                  *
    *  });                                                                                    *
    ****************************************************************************************  */

    // copy the pointer to the node with lowest f-value
    RouteModel::Node* lowest_f_val_node = this->open_list.back();
    this->open_list.pop_back();

    return lowest_f_val_node;
}

// Note: here we don NOT need to explicitly specifiy "static" here
bool RoutePlanner::compareFValue(const RouteModel::Node* node_a, RouteModel::Node* node_b) {
    
    /* Question: Not sure how to access the h_value here for the two nodes */

    // float h_val_a = RoutePlanner::CalculateHValue(node_a);
    // float h_val_b = RoutePlanner::CalculateHValue(node_b);
    
    return node_a->g_value + node_a->h_value > node_b->g_value + node_b->h_value;
}


void RoutePlanner::AddNeighbors(RouteModel::Node* current_node) {
    // update current_node's neighbors vector
    current_node->RouteModel::Node::FindNeighbors();
    for (RouteModel::Node* neighbor : current_node->neighbors) {
        neighbor->parent = current_node;
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        neighbor->h_value = this->CalculateHValue(neighbor);
        this->open_list.push_back(neighbor);
        neighbor->visited = true;
    }
}