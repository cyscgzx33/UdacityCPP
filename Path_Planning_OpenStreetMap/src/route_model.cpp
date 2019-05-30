#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
    int counter = 0;
    for ( auto node : this->Nodes() ) { // this->Nodes() calls the func in Model class
                                        // and return a Model::Node
        m_Nodes.push_back( Node(counter, this, node) );
        counter++;
    }

    CreateNodeToRoadHashmap();
}

float RouteModel::Node::distance(RouteModel::Node anotherNode) const {
    return std::sqrt( std::pow(this->x - anotherNode.x, 2) + std::pow(this->y - anotherNode.y, 2) );
}

void RouteModel::CreateNodeToRoadHashmap() {
    for ( auto road : Roads() ) {
        if (road.type != Model::Road::Type::Footway) {
            for ( auto node_idx : Ways()[road.way]) {
                if ( node_to_road.find(node_idx) == node_to_road.end() ) {
                    node_to_road[node_idx] = std::vector<Model::Road*>{}; // put into an empty vector
                }
                node_to_road[node_idx].push_back(&road);
            }
        }
    }
}