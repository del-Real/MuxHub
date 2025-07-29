#include "constant.h"

Constant::Constant(int id_node, const std::string &label, int data_bits, std::bitset<3> value, std::vector<int> outputs,
                   int orientation,
                   ImVec2 pos) : Node(id_node, label, orientation, pos), data_bits(data_bits), value(value), outputs(outputs) {
}