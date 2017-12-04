#include <iostream>
#include "data.h"
#include "gbdt_class.h"

using namespace std;

int main()
{
	//char *filename = "..\\data\\traindata.xls";
	char *filename = "../../GBDT/src/traindata.xls";

	DataSet train_set(filename);

	GBDT gbdt(1/*20*/, 1.0, 0.5, 4, "binary-classification", 0);

	gbdt.fit(&train_set, train_set.get_instances_idset());

	int num_records = train_set.size();
	int right_predicts = 0;
	for (int i=0; i<train_set.size(); i++)
    {
        auto instance  = train_set.get_instance(i);
        int pred_label = gbdt.predict_label(instance);
        int real_label = instance["label"];
        if (real_label == pred_label)
            right_predicts ++;
    }
    cout<<"full precision = "<<1.0*right_predicts / num_records << endl;
	cout << "finish" << endl;
	//getchar();

	return 0;
}
