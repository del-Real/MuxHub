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
    Orientation orientation;
    ImVec2 pos;

public:
    Node(int id_node, std::string label, int orientation, ImVec2 pos);

    virtual ~Node() = default;

    // idNode
    int get_id_node() const { return id_node; }
    void set_id_node(int idNode) { this->id_node = idNode; }

    // label
    std::string get_label() const { return label; }
    void set_label(std::string label) { this->label = label; }

    // orientation
    Orientation get_orientation() const { return orientation; }
    void set_orientation(Orientation orient) { orientation = orient; }

    // pos
    ImVec2 get_pos() const { return pos; }
    void set_pos(ImVec2 pos) { this->pos = pos; }
};
