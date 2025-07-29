#include "node.h"

// In node.cpp
Node::Node(int id_node, std::string label, int orientation, ImVec2 pos)
    : id_node(id_node), label(label), orientation(static_cast<Orientation>(orientation)), pos(pos) {

    // // Validate orientation value
    // if (orientation < 0 || orientation > 3) {
    //     std::cerr << "Warning: Invalid orientation value " << orientation
    //               << " for node " << label << ". Defaulting to RIGHT." << std::endl;
    //     this->orientation = Orientation::RIGHT;
    // }
}