//
//  Tree.cpp
//  GBDT
//
//  Created by 康锴 on 2017/11/23.
//  Copyright © 2017年 康锴. All rights reserved.
//
#include "Tree.h"
#include <iostream>

double Tree::get_predict_value(vector<double>& instance) {
        
    if(leaf_node != NULL) {
        return leaf_node->get_predict_value();
    }
    if(!split_feature) {
        cout << "the tree is null" << endl;
        return 0.0;
    }
    if(instance[split_feature] <= condition_value) {
        return left_tree->get_predict_value(instance);
    }
    return right_tree->get_predict_value(instance);
}

string Tree::describe(string addtion_info) {
    if(left_tree == NULL && right_tree == NULL)
        return leaf_node->describe();
    string left_info = left_tree->describe("");
    string right_info = right_tree->describe("");
    return addtion_info + "{split_feature:" + to_string(split_feature) + ",split_value:" + to_string(condition_value) + "[left_tree:" + left_info + ",right_tree:" + right_info + "]}";
}

double MSE(vector<double>& values) {
    if(values.size() < 2)
        return 0.0;
    double sum = 0.0;
    for (int i = 0; i < values.size(); i++) {
        sum += values[i];
    }
    double mean = sum / float(values.size());
    double error = 0.0;
    for (int i = 0; i < values.size(); i++) {
        error += (mean - values[i]) * (mean - values[i]);
    }
    return error;
}

double FriedmanMSE(vector<double>& left_values, vector<double>& right_values) {
    int weighted_n_left = int(left_values.size());
    int weighted_n_right = int(right_values.size());
    double sum_left = 0.0, sum_right = 0.0;
    for (int i = 0; i < weighted_n_left; i++) {
        sum_left += left_values[i];
    }
    for (int i = 0; i < weighted_n_right; i++) {
        sum_right += right_values[i];
    }
    double total_meal_left = sum_left / float(weighted_n_left);
    double total_meal_right = sum_right / float(weighted_n_right);
    double diff = total_meal_left - total_meal_right;
    return double(weighted_n_left) * double(weighted_n_right) * diff * diff / double(weighted_n_left + weighted_n_right);
}


