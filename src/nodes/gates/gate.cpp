#include "gate.h"

Gate::Gate(int idGate, int numInputs, std::vector<int> inputs,
           const std::string &label, ImVec2 pos)
    : idGate(idGate), numInputs(numInputs), inputs(inputs), label(label), pos(pos) {}

Gate::Gate(){}

void Gate::printGate() {
    std::cout << "Id Gate: " << idGate << std::endl;
    std::cout << "N inputs: " << numInputs << std::endl;
    std::cout << "Label: " << label << std::endl;
}
