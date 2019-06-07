#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel& model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float GetDistance() { return distance; }
    void AStarSearch();
    
  private:
    // Add private variables or methods declarations here.
    RouteModel &m_Model;
    RouteModel::Node* start_node;
    RouteModel::Node* end_node;
    float distance = 0.0f;
    std::vector<RouteModel::Node*> open_list;

    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node*);
    float CalculateHValue(const RouteModel::Node* node); // TODO: make sure it is the correct way to receive a "const" pointer
    RouteModel::Node* NextNode();
    static bool compareFValue(const RouteModel::Node* node_a, const RouteModel::Node* node_b); // A static member function shall not be declared "const".
    void AddNeighbors(RouteModel::Node*);
};
