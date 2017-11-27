//
//  Tree.h
//  GBDT
//
//  Created by 康锴 on 2017/11/25.
//  Copyright © 2017年 康锴. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include "LeafNode.h"

class Tree {
public:
    Tree() {
        split_feature = 0;
        left_tree = NULL;
        right_tree = NULL;
        condition_value = 0.0;
        leaf_node = NULL;
    }
    double get_predict_value(vector<double>& instance);
    string describe(string addtion_info);
    
private:
    int split_feature;
    Tree* left_tree;
    Tree* right_tree;
    double condition_value;
    LeafNode* leaf_node;
};

#endif /* Tree_h */
