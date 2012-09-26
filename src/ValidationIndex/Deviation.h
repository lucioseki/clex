/*
 * Deviation.h
 *
 *  Created on: 12/03/2010
 *      Author: Gustavo
 */

#ifndef DEVIATION_H_
#define DEVIATION_H_

#include "../DataSet.h"
#include "../Partition.h"
#include "../ValidationIndex.h"

using namespace std;

/**
 *  @author Gustavo Rodrigues
 *  @since 12/03/10
 *  @version 2.0
 */

/* This class is responsible for implementing internal validation of the Index of Total
 * Deviation. This index indicates the degree of compaction of a partition from the
 * evaluation of the average distance (or maximum) of ordered pairs intra-cluster or
 * the average (or maximum) similarity of centroids or using graphics-based approaches;*/
class Deviation:public ValidationIndex {
public:
	/** Does nothing */
	/** @param Don't have any parameter */
	Deviation();
	virtual ~Deviation();

	/** Return value of deviation from parameter partition*/
	/** @param Partition, RelationSDN and DataSet */
	/** @return Value deviation*/
	virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataSet);

	/** Does nothing */
	virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
};

#endif /* DEVIATION_H_ */
