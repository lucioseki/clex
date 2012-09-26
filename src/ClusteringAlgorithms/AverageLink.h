/*
 * AverageLink.h
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef AVERAGELINK_H_
#define AVERAGELINK_H_

#include "../ClusteringAlgorithms.h"
#include "../SettingsAlgorithm/SettingsAlgorithmAverageLink.h"
#include "../Similarity.h"

/* This class is responsible for implementation the Average Link algorithm. */

class AverageLink:public ClusteringAlgorithms {
public:
	AverageLink();
	virtual ~AverageLink();

	/** Return an object partition with the result of Average Link algorithm */
	/** @param Object settings Average Link algorithms, dataset and a measure similarity  */
	/** @return Object partition */
	Partition *run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity);
};

#endif /* AVERAGELINK_H_ */
