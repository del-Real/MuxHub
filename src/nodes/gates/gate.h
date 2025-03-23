#pragma once

#include "imgui.h"
#include <iostream>
#include <string>

class Gate {

  protected:
    int idGate;
    int numInputs;
    std::vector<std::bitset<3>> inputs;
    std::string label;
    ImVec2 pos;

  public:
    Gate(int idGate, int nInputs, std::vector<std::bitset<3>> inputs,
         const std::string &label, ImVec2 pos);
    virtual ~Gate() = default;

    virtual std::bitset<3> process(std::bitset<3>) = 0;

    // idGate
    int getIdGate() { return idGate; }
    void setIdGate(int idGate) { this->idGate = idGate; }

    // nInputs
    int getNumInputs() { return numInputs; }
    void setNumInputs(int numInputs) { this->numInputs = numInputs; }

    // inputs
    std::vector<std::bitset<3>> getInputs() { return inputs; }
    // void setInputs(int nInputs) { this->nInputs = nInputs; }

    // label
    std::string getLabel() { return label; }
    void setLabel(std::string label) { this->label = label; }

    // pos
    ImVec2 getPos() { return pos; }
    void setPos(ImVec2 pos) { this->pos = pos; }

    // Debug print
    void printGate();
};
