#pragma once

#include "../node.h"

class Gate : public Node {
public:
    Gate(int id_node, const std::string &label, int data_bits,
         std::vector<int> inputs, std::vector<int> outputs, int orientation, ImVec2 pos);

    virtual ~Gate() = default;

    virtual std::bitset<3> evaluate(const std::bitset<3> &input) = 0;

    // dataBits
    int get_data_bits() const { return data_bits; }
    void set_data_bits(int data_bits) { this->data_bits = data_bits; }

    // inputs
    const std::vector<int> &get_inputs() const { return inputs; }
    void add_input(int attr_id) { inputs.push_back(attr_id); }

    // outputs
    const std::vector<int> &get_outputs() const { return outputs; }
    void add_output(int attr_id) { outputs.push_back(attr_id); }

    // (Debug) print gate
    void print_gate() const;
};
