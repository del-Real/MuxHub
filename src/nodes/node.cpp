#include "node.h"

Node::Node(int id_node, std::string label, int data_bits, std::vector<int> inputs, std::vector<int> outputs,
           int orientation, ImVec2 pos)
    : id_node(id_node), label(label), data_bits(data_bits), inputs(inputs), outputs(outputs),
      orientation(static_cast<Orientation>(orientation)), pos(pos) {
    // // Validate orientation value
    // if (orientation < 0 || orientation > 3) {
    //     std::cerr << "Warning: Invalid orientation value " << orientation
    //               << " for node " << label << ". Defaulting to RIGHT." << std::endl;
    //     this->orientation = Orientation::RIGHT;
    // }
}
