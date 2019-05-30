#pragma once

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        // Add public Node variables and methods here.
        
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
        Node* parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0;
        bool visited = false;
        std::vector<Node*> neighbors;

        // create a func to return the euclidean distance btw 2 Nodes
        float distance(Node) const; // this method shouldn't change the object being passed
                                    // so one can make it a "const" method by adding "const"
                                    // AFTER the function name.

      private:
        // Add private Node variables and methods here.
        int index;
        RouteModel* parent_model = nullptr;
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);  
    std::vector<Node> path; // This variable will eventually store the path that is found by the A* search.
    std::vector<Node>& SNodes() { return m_Nodes; }

    std::unordered_map< int, std::vector<const Model::Road*> >& GetNodeToRoadMap() { return node_to_road };

  private:
    // Add private RouteModel variables and methods here.
    std::vector<Node> m_Nodes;
    std::unordered_map< int, std::vector<const Model::Road*> > node_to_road;

    void CreateNodeToRoadHashmap();

};
