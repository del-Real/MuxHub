#pragma once

#include "../node.h"

class Output : public Node {
protected:
    int data_bits;
    std::bitset<3> value;
    std::vector<int> inputs;

public:
    Output(int id_node, const std::string &label, int data_bits,
             std::bitset<3> value, std::vector<int> inputs, int orientation, ImVec2 pos);

    virtual ~Output() = default;

    // dataBits
    int get_data_bits() const { return data_bits; }
    void set_data_bits(int data_bits) { this->data_bits = data_bits; }

    // value
    std::bitset<3> get_value() const { return value; }
    void set_value(std::bitset<3> value) { this->value = value; }

    // inputs
    const std::vector<int> &get_inputs() const { return inputs; }
    void add_input(int attr_id) { inputs.push_back(attr_id); }
};
