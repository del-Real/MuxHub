#pragma once
#include "gate.h"

class NotGate : public Gate {
public:
    NotGate(int idNode, const std::string &label, int dataBits, std::vector<int> inputs,
            std::vector<int> outputs, int orientation, ImVec2 pos);

    virtual ~NotGate() = default;

    std::bitset<3> evaluate(const std::bitset<3> &input) override;
};
