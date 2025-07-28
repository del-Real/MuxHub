#pragma once

#include "../node.h"

class Output : public Node {
protected:
    int dataBits;
    std::bitset<3> value;
    std::vector<int> inputs;

public:
    Output(int idNode, const std::string &label, int dataBits,
             std::bitset<3> value, std::vector<int> inputs, int orientation, ImVec2 pos);

    virtual ~Output() = default;

    // dataBits
    int getDataBits() const { return dataBits; }
    void setDataBits(int dataBits) { this->dataBits = dataBits; }

    // value
    std::bitset<3> getValue() const { return value; }
    void setValue(std::bitset<3> value) { this->value = value; }

    // inputs
    const std::vector<int> &getInputs() const { return inputs; }
    void addInput(int attr_id) { inputs.push_back(attr_id); }
};
