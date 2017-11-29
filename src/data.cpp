#include "data.h"

instanceMap* DataSet::construct_instance(int line_cnt)
{
	instanceMap *instance = new instanceMap;
	BasicExcelCell* cell;
	for(int i=0; i<field_names.size(); i++)
	{
		string field_name = field_names[i];
		cell = sheet->Cell(line_cnt,i);
		// all types are real
		if(cell->Type() != BasicExcelCell::DOUBLE)
					{
						std::cerr << "Field type is not double" << std::endl;
						exit(-1);
					}
		(*instance)[field_name] = int(cell->GetDouble());
		distinct_valueset[field_name]->insert(int(cell->GetDouble()));

	}

	return instance;
}

void describe()
{
	// TO DO:

}

std::vector<int> DataSet::get_instances_idset()
{
	std::vector<int> idset;
	for(int i=0; i<instances.size(); i++)
		idset.push_back(i);

	return idset;
}

int DataSet::get_label_size()
{
	return distinct_valueset["label"]->size();
}

intSet DataSet::get_label_valueset()
{
	return *(distinct_valueset["label"]);
}

int DataSet::size()
{
	return instances.size();
}

instanceMap DataSet::get_instance(int id)
{
	return *(instances[id]);
}

vector<string> DataSet::get_attributes()
{
	std::vector<string> attribute_names;

	for(auto x:field_names)
		if(x!="label")
			attribute_names.push_back(x);

	return attribute_names;
}

intSet DataSet::get_distinct_valueset(string name)
{
	return *(distinct_valueset[name]);
}

