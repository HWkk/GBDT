#include <iostream>
#include "data.h"
#include "gbdt_class.h"

using namespace std;

int main()
{
	char *filename = "./traindata.xls";

	DataSet train_set(filename);

	getchar();

	return 0;
}
