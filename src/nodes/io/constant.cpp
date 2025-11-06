#include "constant.h"

Constant::Constant(int id_node, const std::string &label, int data_bits, std::bitset<3> value, std::vector<int> outputs,
                   int orientation, ImVec2 pos)
    : Node(id_node, label, data_bits, inputs, outputs, orientation, pos), value(value) {
    if (outputs.empty()) {
        throw std::invalid_argument("Constant must have at least one output");
    }

    if (!inputs.empty()) {
        throw std::logic_error("Constant cannot have inputs");
    }
}
