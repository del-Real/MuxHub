#pragma once
#include "gate.h"

class NotGate : public Gate {

  public:
    NotGate(int idGate, int nInputs, std::vector<int> inputs,
            const std::string &label, ImVec2 pos);

    NotGate();
    
    std::bitset<3> process(std::bitset<3> input) override;
};
