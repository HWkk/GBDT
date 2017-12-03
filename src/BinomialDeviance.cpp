
#include "BinomialDeviance.h"
#include <cmath>

map<int, double> BinomialDeviance::compute_residual(DataSet* dataset, DataSet* subset, vector<double> f) {
    map<int, double> residual;
    for (auto id : subset->get_instances_idset()) {
        int y_i = dataset->get_instance(id)["label"];
        residual[id] = 2.0 * y_i / (1 + exp(2 * y_i * f[id]));
    }
    return residual;
}

void BinomialDeviance::update_f_value(vector<double>& f, Tree* tree, vector<LeafNode> leaf_nodes,
                    DataSet* subset, DataSet* dataset, double learn_rate) {
    vector<int> data_idset = dataset->get_instances_idset();
    for(auto node : leaf_nodes) {
        for(auto id : node.get_idset()) {
            f[id] += learn_rate * node.get_predict_value();
        }
    }
    /*for (auto id : data_idset) {
        f[id] += learn_rate * tree->get_predict_value(dataset->get_instance(id));
    }*/
}

void BinomialDeviance::initialize(vector<double>& f, DataSet* dataset) {
    vector<int> ids = dataset->get_instances_idset();
    for (auto id : ids) {
        f.push_back(0.0);
    }
}

double BinomialDeviance::update_terminal_regions(map<int, double>targets, vector<int> idset) {
    double sum1 = 0.0;
    for (int i = 0; i < idset.size(); i++) {
        sum1 += targets[idset[i]];
    }
    if(sum1 == 0.0)
        return sum1;
    double sum2 = 0.0;
    for (int i = 0; i < idset.size(); i++) {
        sum2 += abs(targets[idset[i]]) * (2 - abs(targets[idset[i]]));
    }
    return sum1 / sum2;
}
