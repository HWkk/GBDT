#include <string>
#include <map>
#include <set>
#include "BasicExcel.hpp"

using namespace YExcel;

typedef map<string,int> instanceMap;

typedef set<int> intSet;

class DataSet
{
public:
	DataSet(const char *filename)
	{
		file = new BasicExcel;
		if (!file->Load(filename))
		{
			std::cerr << "Open " << filename << " failed" << std::endl;
			exit(-1);
		}
			
		// only have 1 sheet
		sheet = file->GetWorksheet(size_t(0));
		if (sheet == NULL)
		{
			std::cerr << "Read worksheet failed" << std::endl;
			exit(-1);
		}

		size_t max_rows = sheet->GetTotalRows();
		size_t max_cols = sheet->GetTotalCols();

		BasicExcelCell* cell;

		for(int line_cnt=0; line_cnt<max_rows; line_cnt++)
		{
			// read field names
			if(line_cnt == 0)
			{
				for(int i=0; i<max_cols; i++)
				{
					cell = sheet->Cell(line_cnt,i);
					if(cell->Type() != BasicExcelCell::STRING)
					{
						std::cerr << "Field name is not string" << std::endl;
						exit(-1);
					}
					string field_name = cell->GetString();
					field_names.push_back(field_name);
				}
			}
			else
			{
				// init distinct valueset
				if(line_cnt == 1)
					for(int i=0; i<max_cols; i++)
						distinct_valueset[field_names[i]] = new intSet;
				// read every instances
				instances.push_back(construct_instance(line_cnt));
			}
		}

		cout<< "read file successfully" << endl;
	}

	~DataSet()
	{
		field_names.clear();

		for(std::vector<instanceMap*>::iterator it=instances.begin();
			it!=instances.end(); it++)
		{
			delete *it;
			*it = NULL;
		}
		instances.clear();

		for(std::map<string, intSet*>::iterator it=distinct_valueset.begin();
			it!=distinct_valueset.end(); it++)
		{
			delete it->second;
		}
		distinct_valueset.clear();
	}

	void describe();

	std::vector<int> get_instances_idset();

	int get_label_size();

	intSet get_label_valueset();

	int size();

	instanceMap get_instance(int id);

	vector<string> get_attributes();

	intSet get_distinct_valueset(string name);

	std::vector<string> field_names;

	std::vector<instanceMap*> instances;

	std::map<string, intSet*> distinct_valueset;

private:

	instanceMap* construct_instance(int line_cnt);

	BasicExcel *file;

	BasicExcelWorksheet *sheet;
};