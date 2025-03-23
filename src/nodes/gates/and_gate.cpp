#include "and_gate.h"

AndGate::AndGate(int idGate, int nInputs, std::vector<std::bitset<3>> inputs,
                 const std::string &label, ImVec2 pos)
    : Gate(idGate, nInputs, inputs, label, pos) {
    if (nInputs < 2) {
        throw std::invalid_argument("AND gate #" + std::to_string(idGate) +
                                    " must have at least 2 inputs");
    }
}

std::bitset<3> AndGate::process(std::bitset<3> input) {
    return input; // Bitwise AND
}
