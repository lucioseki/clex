/*
 * CentroidLink.h
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef CENTROIDLINK_H_
#define CENTROIDLINK_H_

#include "../ClusteringAlgorithms.h"
#include "../SettingsAlgorithm/SettingsAlgorithmCentroidLink.h"
#include "../Similarity.h"

/* This class is responsible for implementation the Centroid Link algorithm. */

class CentroidLink: public ClusteringAlgorithms {
public:
	CentroidLink();
	virtual ~CentroidLink();

	/** Return an object partition with the result of Centroid Link algorithm */
	/** @param Object settings Centroid Link algorithms, dataset and a measure similarity  */
	/** @return Object partition */
	Partition *run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity);
};

#endif /* CENTROIDLINK_H_ */
