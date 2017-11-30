
#ifndef BinomialDeviance_h
#define BinomialDeviance_h

#include "Tree.h"
#include "data.h"
using namespace std;
class Tree;class LeafNode;
class BinomialDeviance{
public:
    vector<double> compute_residual(DataSet* dataset, DataSet* subset, vector<double> f);
    void update_f_value(vector<double>& f, Tree* tree, vector<LeafNode> leaf_nodes, DataSet* subset, DataSet* dataset, double learn_rate);
    void initialize(vector<double>& f, DataSet* dataset);
    double update_terminal_regions(map<int, double>targets, vector<int> idset);
};

#endif /* BinomialDeviance_h */
