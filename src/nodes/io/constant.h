#pragma once

#include "../node.h"

class Constant : public Node {
protected:
    std::bitset<3> value;

public:
    Constant(int id_node, const std::string &label, int data_bits,
             std::bitset<3> value, std::vector<int> outputs, int orientation, ImVec2 pos);

    virtual ~Constant() = default;

    // dataBits
    int get_data_bits() const { return data_bits; }
    void set_data_bits(int dataBits) { this->data_bits = dataBits; }

    // value
    std::bitset<3> get_value() const { return value; }
    void set_value(std::bitset<3> value) { this->value = value; }

    // outputs
    const std::vector<int> &get_outputs() const { return outputs; }
    void add_output(int attr_id) { outputs.push_back(attr_id); }
};
