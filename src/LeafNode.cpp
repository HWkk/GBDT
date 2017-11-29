

#include "LeafNode.h"

string LeafNode::describe() {
    return "{LeafNode" + to_string(get_predict_value()) + "}";
}

vector<int> LeafNode::get_idset() {
    return idset;
}

double LeafNode::get_predict_value() {
    return predict_value;
}

void LeafNode::update_predict_value(map<int, double> targets, BinomialDeviance* loss) {
    predict_value = loss->update_terminal_regions(targets, idset);
}


