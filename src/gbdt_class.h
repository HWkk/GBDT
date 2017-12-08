#ifndef GBDT_CLASS_H
#define GBDT_CLASS_H

#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include "BinomialDeviance.h"
#include "data.h"

using namespace std;

typedef map<string, int> INSTANCE;

class GBDT
{
public:
	GBDT(int max_iter, float sample_rate,
		float learn_rate, int max_depth,
		string loss_type, int split_points = 0)
	{
		this->max_iter = max_iter;
		this->sample_rate = sample_rate;
		this->learn_rate = learn_rate;
		this->max_depth = max_depth;
		this->loss_type = loss_type;
		this->split_points = split_points;
	}
	void fit(DataSet* dataset, vector<int> train_data)
	{
	    for (auto inst : dataset->instances)
        {
            int label = (*inst)["label"];
            if (label == 0)
                (*inst)["label"] = -1;
        }
		// binary-classification
		this->loss = BinomialDeviance();
		vector<double> f;
		this->loss.initialize(f, dataset);
		if (0 < this->sample_rate && this->sample_rate <1 - 0.001)
		{
			//subset = sample(subset, subset.size()*this->sample_rate);            cout<<"sample rate is 1"<<endl;            exit(1);
		}
		for (int iter = 1; iter <= this->max_iter; iter++)
		{
			auto& subset = train_data;
			map<int, double> residual = this->loss.compute_residual(dataset, dataset, f);
			std::vector<LeafNode*> leaf_pnodes;
			map<int, double> targets = residual;
			Tree* tree = construct_decision_tree(dataset, subset, targets, 0, leaf_pnodes, this->max_depth, &this->loss); //, this->split_points);
			std::vector<LeafNode> leaf_nodes;
			for (LeafNode* p : leaf_pnodes)
			{ leaf_nodes.push_back(*p); }
			this->trees[iter] = tree;
			this->loss.update_f_value(f, tree, leaf_nodes, /*subset*/dataset, dataset, this->learn_rate);

			float train_loss = this->compute_loss(dataset, train_data, f);
			printf("iter%d : train loss=%f\n", iter, train_loss);
		}
	}

	float compute_loss(DataSet* dataset, vector<int> subset, vector<double> &f)
	{
		float loss = 0.0;
		vector<int> idset = dataset->get_instances_idset();
		for (int id : idset)
		{
			instanceMap pdict = dataset->get_instance(id);
			double y_i = pdict["label"];
			double f_value = f[id];
			float p_1 = 1.0 / (1 + exp(-2 * f_value));
			loss -= (1 + y_i)*log(p_1) / 2 +
				(1 - y_i)*log(1 - p_1) / 2;
		}        return loss / dataset->size();
	}


	float compute_instance_f_value(INSTANCE& instance)
	{
		float f_value = 0;
		for (auto pp : this->trees)
		{
			Tree* tree = pp.second;
			f_value += this->learn_rate * tree->get_predict_value(instance);
		}
		return f_value;
	}

	float predict(INSTANCE& instance)
	{
		return this->compute_instance_f_value(instance);
	}

	std::map<string, float> predict_prob(INSTANCE& instance)
	{
		float f_value = this->compute_instance_f_value(instance);
		std::map<string, float> probs;
		probs["+1"] = 1.0 / (1 + exp(-2 * f_value));
		probs["-1"] = 1 - probs["+1"];
		return probs;
	}

	int predict_label(INSTANCE& instance)
	{
		std::map<string, float> probs =
			this->predict_prob(instance);
		int p_label;
		if (probs["+1"] >= probs["-1"])
			p_label = 1;
		else p_label = -1;
		return p_label;
	}



public:
	int max_iter;
	float sample_rate;
	float learn_rate;
	int max_depth;
	std::string loss_type;
	int split_points;
	BinomialDeviance loss;
	std::map<int, Tree*> trees;

};

#endif // GBDT_CLASS_H
