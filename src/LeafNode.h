//
//  LeafNode.h
//  GBDT
//
//  Created by 康锴 on 2017/11/25.
//  Copyright © 2017年 康锴. All rights reserved.
//

#ifndef LeafNode_h
#define LeafNode_h

#include <vector>
#include <string>
#include "BinomialDeviance.h"
using namespace std;

class LeafNode {
public:
    LeafNode(vector<int>& ids, double pridict_v) : idset(ids), predict_value(pridict_v) {}
    string describe();
    vector<int> get_idset();
    double get_predict_value();
    void update_predict_value(vector<double> targets, BinomialDeviance* loss);
    
private:
    vector<int> idset;
    double predict_value;
};


#endif /* LeafNode_h */
