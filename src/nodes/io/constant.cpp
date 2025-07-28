#include "constant.h"

Constant::Constant(int idNode, const std::string &label, int dataBits, std::bitset<3> value, std::vector<int> outputs,
                   int orientation,
                   ImVec2 pos) : Node(idNode, label, orientation, pos), dataBits(dataBits), value(value), outputs(outputs) {
}