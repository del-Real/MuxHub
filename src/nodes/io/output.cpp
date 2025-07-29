#include "output.h"

Output::Output(int id_node, const std::string &label, int data_bits, std::bitset<3> value, std::vector<int> inputs,
               int orientation, ImVec2 pos)
    : Node(id_node, label, orientation, pos), data_bits(data_bits), value(value), inputs(inputs) {
}
