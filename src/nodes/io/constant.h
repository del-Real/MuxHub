#pragma once

#include "../node.h"

class Constant : public Node {
protected:
    int dataBits;
    std::bitset<3> value;
    std::vector<int> outputs;

public:
    Constant(int idNode, const std::string &label, int dataBits,
             std::bitset<3> value, std::vector<int> outputs, int orientation, ImVec2 pos);

    virtual ~Constant() = default;

    // dataBits
    int getDataBits() const { return dataBits; }
    void setDataBits(int dataBits) { this->dataBits = dataBits; }

    // value
    std::bitset<3> getValue() const { return value; }
    void setValue(std::bitset<3> value) { this->value = value; }

    // outputs
    const std::vector<int> &getOutputs() const { return outputs; }
    void addOutput(int attr_id) { outputs.push_back(attr_id); }
};
