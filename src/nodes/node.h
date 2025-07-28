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
    int idNode;
    std::string label;
    Orientation orientation;
    ImVec2 pos;

public:
    Node(int idNode, std::string label, int orientation, ImVec2 pos);

    virtual ~Node() = default;

    // idNode
    int getIdNode() const { return idNode; }
    void setIdNode(int idNode) { this->idNode = idNode; }

    // label
    std::string getLabel() const { return label; }
    void setLabel(std::string label) { this->label = label; }

    // orientation
    Orientation getOrientation() const { return orientation; }
    void setOrientation(Orientation orient) { orientation = orient; }

    // pos
    ImVec2 getPos() const { return pos; }
    void setPos(ImVec2 pos) { this->pos = pos; }
};
