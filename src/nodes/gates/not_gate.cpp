#include "not_gate.h"

// Constructor
NotGate::NotGate(int idNode, const std::string &label, int dataBits, std::vector<int> inputs,
                 std::vector<int> outputs, int orientation, ImVec2 pos)
    : Gate(idNode, label, dataBits, inputs, outputs, orientation, pos) {
}

// Bitwise NOT operation
std::bitset<3> NotGate::evaluate(const std::bitset<3> &input) {
    return ~input;
}