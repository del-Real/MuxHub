#include "output.h"

Output::Output(int idNode, const std::string &label, int dataBits, std::bitset<3> value, std::vector<int> inputs,
               int orientation, ImVec2 pos)
    : Node(idNode, label, orientation, pos), dataBits(dataBits), value(value), inputs(inputs) {
}
