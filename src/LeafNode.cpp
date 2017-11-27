//
//  LeafNode.cpp
//  GBDT
//
//  Created by 康锴 on 2017/11/23.
//  Copyright © 2017年 康锴. All rights reserved.
//

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


