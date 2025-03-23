#pragma once
#include "gate.h"

class AndGate : public Gate {

  public:
    AndGate(int idGate, int nInputs,std::vector<std::bitset<3>> inputs,  const std::string &label, ImVec2 pos);
    
    std::bitset<3> process(std::bitset<3> input) override;
};
