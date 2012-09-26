/*
 * SingleLink.h
 *
 *  Created on: 16/12/2010
  *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef SINGLELINK_H_
#define SINGLELINK_H_

#include "../ClusteringAlgorithms.h"
#include "../SettingsAlgorithm/SettingsAlgorithmSingleLink.h"
#include "../Similarity.h"

/* This class is responsible for implementation the Single Link algorithm. */

class SingleLink: public ClusteringAlgorithms {
public:
	SingleLink();
	virtual ~SingleLink();

	/** Return an object partition with the result of Single Link algorithm */
	/** @param Object settings Single Link algorithms, dataset and a measure similarity  */
	/** @return Object partition */
	Partition *run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity);
};

#endif /* SINGLELINK_H_ */
