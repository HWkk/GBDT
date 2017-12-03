#include <iostream>
#include "data.h"
#include "gbdt_class.h"

using namespace std;

int main()
{
	char *filename = "..\\data\\traindata.xls";

	DataSet train_set(filename);

	GBDT gbdt(20, 1.0, 0.5, 4, "binary-classification", 0);

	gbdt.fit(&train_set, train_set.get_instances_idset());

	cout << "finish" << endl;
	getchar();

	return 0;
}
