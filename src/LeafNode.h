

#ifndef LeafNode_h
#define LeafNode_h

#include <map>
#include <vector>
#include <string>
#include "BinomialDeviance.h"
using namespace std;

class LeafNode {
public:
    LeafNode(vector<int>& ids, double pridict_v) : idset(ids), predict_value(pridict_v) {}
    LeafNode(vector<int>& ids){}
    string describe();
    vector<int> get_idset();
    double get_predict_value();
    void update_predict_value(map<int, double> targets, BinomialDeviance* loss);
    
private:
    vector<int> idset;
    double predict_value;
};


#endif /* LeafNode_h */
