/*
 * ValidationIndex.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#ifndef VALIDATIONINDEX_H_
#define VALIDATIONINDEX_H_

#include <cmath>
#include <iostream>
#include <math.h>

#include "Partition.h"
#include "RelationSDN.h"

using namespace std;


/**Abstract class with two calculate methods, the one with two parameters is
    to be used in external validation measures and the one with one parameter
    is to be used in internal validation measures */
 class ValidationIndex {

public:
	ValidationIndex();
	virtual ~ValidationIndex();

	/** Method virtual from return value of measure validation internal */
	/** @param Partition, RelationSDN and DataSet */
	/** @return Value from measure validation*/
	virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pDataSet) = 0;

	/** Method virtual from return value of measure validation external */
	/** @param Partition */
	/** @return Value from measure validation*/
	virtual double calculate(Partition &objPartition1, Partition &objPartition2) = 0;

};

#endif /* VALIDATIONINDEX_H_ */
