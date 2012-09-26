/*
 * ClusteringAlgorithms.h
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef CLUSTERINGALGORITHMS_H_
#define CLUSTERINGALGORITHMS_H_

#include "Partition.h"
#include "SettingsAlgorithm.h"
#include "DataSet.h"
#include "Similarity.h"

using namespace std;

/**Abstract class with a method called run responsible for
 * running an clustering algorithm */
class ClusteringAlgorithms {
public:
	ClusteringAlgorithms();
	virtual ~ClusteringAlgorithms();

	/** Return an object partition with the result of clustering algorithm */
	/** @param Object settings algorithms, dataset and a measure similarity  */
	/** @return Object partition */
	virtual Partition *run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity) =0;
};

#endif /* CLUSTERINGALGORITHMS_H_ */
