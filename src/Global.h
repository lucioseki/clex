#ifndef GLOBAL_H
#define GLOBAL_H

#include "DataSet.h"
#include <vector>

class Global{
	int m_value;
	static std::vector<DataSet*> vDataSet;

	public:
		Global(){}
		std::vector<DataSet*> get_vDataSet(){
			return vDataSet;
		}
		
		void push_vDataSet(DataSet* ds){
			vDataSet.push_back(ds);
		}
		

};

#endif
