#include "gate.h"
#include <iostream>

Gate::Gate(int id_node, const std::string &label, int data_bits,
           std::vector<int> inputs, std::vector<int> outputs, int orientation, ImVec2 pos)
    : Node(id_node, label, data_bits, inputs, outputs, orientation, pos) {
}

void Gate::print_gate() const {
    std::cout << "=== Gate Information ===" << std::endl;
    std::cout << "ID: " << get_id_node() << std::endl;
    std::cout << "Label: " << get_label() << std::endl;
    std::cout << "Data Bits: " << data_bits << std::endl;

    // Convert orientation enum to string for display
    std::string orient_str;
    switch (get_orientation()) {
        case Orientation::UP: orient_str = "UP ↑";
            break;
        case Orientation::RIGHT: orient_str = "RIGHT →";
            break;
        case Orientation::DOWN: orient_str = "DOWN ↓";
            break;
        case Orientation::LEFT: orient_str = "LEFT ←";
            break;
    }
    std::cout << "Orientation: " << orient_str << std::endl;
    std::cout << "Position: (" << get_pos().x << ", " << get_pos().y << ")" << std::endl;

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
