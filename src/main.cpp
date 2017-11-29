#include <iostream>
#include "data.h"

using namespace std;

int main()
{
	char *filename = "./traindata.xls";

	DataSet train_set(filename);

	getchar();

	return 0;
}