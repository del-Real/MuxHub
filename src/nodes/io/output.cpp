#include "output.h"

Output::Output(int id_node, const std::string &label, int data_bits, std::bitset<3> value, std::vector<int> inputs,
               int orientation, ImVec2 pos)
    : Node(id_node, label, data_bits, inputs, outputs, orientation, pos), value(value) {
    if (inputs.empty()) {
        throw std::invalid_argument("Output must have at least one input");
    }
    if (!outputs.empty()) {
        throw std::logic_error("Output cannot have outputs");
    }
}
