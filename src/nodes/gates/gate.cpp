#include "gate.h"
#include <iostream>

Gate::Gate(int idNode, const std::string &label, int dataBits,
           std::vector<int> inputs, std::vector<int> outputs, int orientation, ImVec2 pos)
    : Node(idNode, label, orientation, pos), dataBits(dataBits), inputs(inputs), outputs(outputs) {
}

void Gate::printGate() const {
    std::cout << "=== Gate Information ===" << std::endl;
    std::cout << "ID: " << getIdNode() << std::endl;
    std::cout << "Label: " << getLabel() << std::endl;
    std::cout << "Data Bits: " << dataBits << std::endl;

    // Convert orientation enum to string for display
    std::string orientStr;
    switch (getOrientation()) {
        case Orientation::UP:    orientStr = "UP ↑"; break;
        case Orientation::RIGHT: orientStr = "RIGHT →"; break;
        case Orientation::DOWN:  orientStr = "DOWN ↓"; break;
        case Orientation::LEFT:  orientStr = "LEFT ←"; break;
    }
    std::cout << "Orientation: " << orientStr << std::endl;
    std::cout << "Position: (" << getPos().x << ", " << getPos().y << ")" << std::endl;

    std::cout << "Inputs (" << inputs.size() << "): ";
    if (inputs.empty()) {
        std::cout << "none";
    } else {
        for (size_t i = 0; i < inputs.size(); ++i) {
            std::cout << inputs[i];
            if (i < inputs.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;

    std::cout << "Outputs (" << outputs.size() << "): ";
    if (outputs.empty()) {
        std::cout << "none";
    } else {
        for (size_t i = 0; i < outputs.size(); ++i) {
            std::cout << outputs[i];
            if (i < outputs.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "========================" << std::endl;
}