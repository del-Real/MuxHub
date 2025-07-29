#include "not_gate.h"

// Constructor
NotGate::NotGate(int id_node, const std::string &label, int data_bits, std::vector<int> inputs,
                 std::vector<int> outputs, int orientation, ImVec2 pos)
    : Gate(id_node, label, data_bits, inputs, outputs, orientation, pos) {
}

// Bitwise NOT operation
std::bitset<3> NotGate::evaluate(const std::bitset<3> &input) {
    return ~input;
}