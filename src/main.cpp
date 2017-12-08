#include <iostream>
#include "data.h"
#include "gbdt_class.h"
#include <time.h>

using namespace std;

int main()
{
	//char *filename = "..\\data\\traindata.xls";
	char *filename = "../../GBDT/src/traindata_small.xls";

	DataSet train_set(filename);

	/*
	for (int i = 0; i < train_set.size(); i++)
	{

		instanceMap ins_map = train_set.get_instance(i);

		printf("%d\n",ins_map["total_online_time(mins)"]);
	}*/

	GBDT gbdt(5/*20*/, 1.0, 0.5, 4, "binary-classification", 0);
    clock_t t1, t2;
    t1 = clock();
	gbdt.fit(&train_set, train_set.get_instances_idset());
    t2 = clock();
    float train_time_s = 1.0*(t2-t1)/CLOCKS_PER_SEC;
    cout<<"training time  = "<<train_time_s<<" seconds"<<endl;

	int num_records = train_set.size();
	int right_predicts = 0;
	for (int i = 0; i<train_set.size(); i++)
	{
		auto instance = train_set.get_instance(i);
		int pred_label = gbdt.predict_label(instance);
		int real_label = instance["label"];
		if (real_label == pred_label)
			right_predicts++;
	}
	cout << "full precision = " << 1.0*right_predicts / num_records << endl;

	int real_T_pred_T=0;
	int real_T_pred_F=0;
	int real_F_pred_T=0;
	int real_F_pred_F=0;
	for (int i = 0; i<train_set.size(); i++)
	{
		auto instance = train_set.get_instance(i);
		int pred_label = gbdt.predict_label(instance);
		int real_label = instance["label"];

		if (real_label >0 && pred_label >0)
            real_T_pred_T++;
        else if (real_label>0 && pred_label<0)
            real_T_pred_F++;
        else if(real_label<0 && pred_label>0)
            real_F_pred_T++;
        else if(real_label<0 && pred_label<0)
            real_F_pred_F++;
	}
	cout<<"confusion matrix"<<endl;
	cout<<"\tpred_T\tpred_F"<<endl;
	cout<<"real_T\t"<<real_T_pred_T<<"\t"<<real_T_pred_F<<endl;
	cout<<"real_F\t"<<real_F_pred_T<<"\t"<<real_F_pred_F<<endl;
	cout << "finish" << endl;

	getchar();

	return 0;
}
