
#include "Tree.h"
#include <iostream>

double Tree::get_predict_value(map<string, int> instance) {

    if(leaf_node != NULL) {
        return leaf_node->get_predict_value();
    }
    if (split_feature == "") {
        throw "the tree is null";
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
    return addtion_info + "{split_feature:" + split_feature + ",split_value:" + to_string(condition_value) + "[left_tree:" + left_info + ",right_tree:" + right_info + "]}";
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

Tree* construct_decision_tree(DataSet* dataset, std::vector<int> &remainedSet, map<int, double>targets, int depth,
                              vector<LeafNode*> &leaf_nodes, int max_depth, BinomialDeviance* loss) {
    if (depth < max_depth) {
        std::vector<std::string> attributes = dataset->get_attributes();
        double mse = -1.0;
        std::string selectedAttribute = "";
        int conditionValue = 0;
        std::vector<int> selectedLeftIdSet;
        std::vector<int> selectedRightIdSet;
        for (auto attribute : attributes) {
            std::set<int> attrValues = dataset->get_distinct_valueset(attribute);
            for (auto attrValue : attrValues) {
                std::vector<int> leftIdSet;
                std::vector<int> rightIdSet;
                for (auto Id : remainedSet) {
                    std::map<std::string, int> instance = dataset->get_instance(Id);
                    int value = instance[attribute];
                    if (value < attrValue) {
                        leftIdSet.push_back(Id);
                    } else {
                        rightIdSet.push_back(Id);
                    }
                }
                std::vector<double> leftTargets;
                std::vector<double> rightTargets;
                for (auto id : leftIdSet) {
                    leftTargets.push_back(targets[id]);
                }
                for (auto id : rightIdSet) {
                    rightTargets.push_back(targets[id]);
                }
                double sum_mse = MSE(leftTargets)+MSE(rightTargets);
                if (mse < 0 || sum_mse < mse) {
                    selectedAttribute = attribute;
                    conditionValue = attrValue;
                    mse = sum_mse;
                    selectedLeftIdSet = leftIdSet;
                    selectedRightIdSet = rightIdSet;
                }
            }
        }
        if (selectedAttribute == ""|| mse < 0) {
            throw "cannot determine the split attribute.";
        }
        Tree *tree = new Tree();
        tree->split_feature = selectedAttribute;
        tree->condition_value = conditionValue;
        tree->left_tree = construct_decision_tree(dataset, selectedLeftIdSet, targets, depth+1, leaf_nodes, max_depth, loss);
        tree->right_tree = construct_decision_tree(dataset, selectedRightIdSet, targets, depth+1, leaf_nodes, max_depth, loss);
        return tree;
    } else {
        LeafNode *node = new LeafNode(remainedSet);
        node->update_predict_value(targets, loss);
        leaf_nodes.push_back(node);
        Tree *tree = new Tree();
        tree->leaf_node = node;
        return tree;
    }
}

