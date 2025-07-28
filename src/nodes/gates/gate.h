#pragma once

#include "../node.h"

class Gate : public Node {
protected:
    int dataBits;
    std::vector<int> inputs;
    std::vector<int> outputs;

public:
    Gate(int idNode, const std::string &label, int dataBits,
         std::vector<int> inputs, std::vector<int> outputs, int orientation, ImVec2 pos);

    virtual ~Gate() = default;

    virtual std::bitset<3> evaluate(const std::bitset<3> &input) = 0;

    // dataBits
    int getDataBits() const { return dataBits; }
    void setDataBits(int dataBits) { this->dataBits = dataBits; }

    // inputs
    const std::vector<int> &getInputs() const { return inputs; }
    void addInput(int attr_id) { inputs.push_back(attr_id); }

    // outputs
    const std::vector<int> &getOutputs() const { return outputs; }
    void addOutput(int attr_id) { outputs.push_back(attr_id); }

    // (Debug) print gate
    void printGate() const;
};
