#pragma once

#include "imgui.h"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

enum class Orientation {
    UP = 0, // ↑
    RIGHT = 1, // →
    DOWN = 2, // ↓
    LEFT = 3 // ←
};

class Node {
protected:
    int id_node;
    std::string label;
    int data_bits;
    std::vector<int> inputs;
    std::vector<int> outputs;
    Orientation orientation;
    ImVec2 pos;

public:
    Node(int id_node, std::string label, int data_bits, std::vector<int> inputs, std::vector<int> outputs,
         int orientation, ImVec2 pos);

    virtual ~Node() = default;

    // idNode
    int get_id_node() const { return id_node; }
    void set_id_node(int idNode) { this->id_node = idNode; }

    // label
    std::string get_label() const { return label; }
    void set_label(std::string label) { this->label = label; }

    // dataBits
    int get_data_bits() const { return data_bits; }
    void set_data_bits(int data_bits) { this->data_bits = data_bits; }

    // inputs
    const std::vector<int> &get_inputs() const { return inputs; }
    void add_input(int attr_id) { inputs.push_back(attr_id); }

    // outputs
    const std::vector<int> &get_outputs() const { return outputs; }
    void add_output(int attr_id) { outputs.push_back(attr_id); }

    // orientation
    Orientation get_orientation() const { return orientation; }
    void set_orientation(Orientation orient) { orientation = orient; }

    // pos
    ImVec2 get_pos() const { return pos; }
    void set_pos(ImVec2 pos) { this->pos = pos; }
};
