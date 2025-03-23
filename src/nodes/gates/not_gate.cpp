#include "not_gate.h"

NotGate::NotGate(int idGate, int nInputs, std::vector<std::bitset<3>> inputs, const std::string &label, ImVec2 pos)
    : Gate(idGate, 1, inputs, label, pos) {}

// Bitwise NOT
std::bitset<3> NotGate::process(std::bitset<3> input) {
    std::bitset<3> output(~input);
    return output;
}
