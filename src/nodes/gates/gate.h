#pragma once

#include "imgui.h"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

class Gate {

  protected:
    int idGate;
    int numInputs;
    std::vector<int> inputs;
    std::string label;
    ImVec2 pos;

  public:
    Gate(int idGate, int nInputs, std::vector<int> inputs,
         const std::string &label, ImVec2 pos);

    Gate();

    virtual ~Gate() = default;

    virtual std::bitset<3> process(std::bitset<3>) = 0;

    // idGate
    int getIdGate() { return idGate; }
    void setIdGate(int idGate) { this->idGate = idGate; }

    // nInputs
    int getNumInputs() { return numInputs; }
    void setNumInputs(int numInputs) { this->numInputs = numInputs; }

    // inputs
    std::vector<int> getInputs() { return inputs; }
    void addInput(int attr_id) { inputs.push_back(attr_id); }

    // label
    std::string getLabel() { return label; }
    void setLabel(std::string label) { this->label = label; }

    // pos
    ImVec2 getPos() { return pos; }
    void setPos(ImVec2 pos) { this->pos = pos; }

    // Debug print
    void printGate();
};
