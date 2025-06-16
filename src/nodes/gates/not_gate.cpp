#include "not_gate.h"

NotGate::NotGate(int idGate, int nInputs, std::vector<int> inputs, const std::string &label, ImVec2 pos)
    : Gate(idGate, 1, inputs, label, pos) {}

NotGate::NotGate(){}

// Bitwise NOT
std::bitset<3> NotGate::process(std::bitset<3> input) {
    std::bitset<3> output(~input);
    return output;
}
