/*
 * Connectivity.h
 *
 *  Created on: 12/03/2010
 *      Author: Gustavo
 */

#ifndef CONNECTIVITY_H_
#define CONNECTIVITY_H_

#include "../ValidationIndex.h"

using namespace std;

/**
 *  @author Gustavo Rodrigues
 *  @since 12/03/10
 *  @version 2.0
 */

/* This class is responsible for calculating the connectivity index of internal validation,
 * using the partition, dataset and some distance of (dis)similarity.
 * The connctivity indicates the degree of partitioning observed locally and the density of
 * data objects together with the nearest neighbors in space data;
 */
class Connectivity: public ValidationIndex {
//private:
	//float fSizeNn; ///< number of neighbor from calculate connectivity
public:

	/** Does nothing */
	/** @param Integer indicated size of nearest neighbor list */
	Connectivity();
	virtual ~Connectivity();

	/** Return value of connectivity from parameter partition*/
	/** @param Partition, RelationSDN and DataSet */
	/** @return Value connectivity*/
	virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataSet);

	/** Does nothing */
	virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
};

#endif /* CONNECTIVITY_H_ */
