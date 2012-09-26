/*
 * CompleteLink.h
 *
 *  Created on: 16/12/2010
  *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef COMPLETELINK_H_
#define COMPLETELINK_H_

#include "../ClusteringAlgorithms.h"
#include "../SettingsAlgorithm/SettingsAlgorithmCompleteLink.h"
#include "../Similarity.h"

/* This class is responsible for implementation the Complete Link algorithm. */

class CompleteLink: public ClusteringAlgorithms {
public:
	CompleteLink();
	virtual ~CompleteLink();

	/** Return an object partition with the result of Complete Link algorithm */
	/** @param Object settings Complete Link algorithms, dataset and a measure similarity  */
	/** @return Object partition */
	Partition *run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity);
};

#endif /* COMPLETELINK_H_ */
