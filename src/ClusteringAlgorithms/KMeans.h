/*
 * KMeans.h
 *
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef KMEANS_H_
#define KMEANS_H_

#include "../ClusteringAlgorithms.h"
#include "../SettingsAlgorithm/SettingsAlgorithmKMeans.h"
#include "../Similarity.h"

/* This class is responsible for implementation the KMeans algorithm. */

class KMeans: public ClusteringAlgorithms {
public:
	KMeans();
	virtual ~KMeans();

	/** Return an object partition with the result of KMeans algorithm */
	/** @param Object settings KMeans algorithms, dataset and a measure similarity  */
	/** @return Object partition */
	Partition *run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity);

	static const double DISTANCE;
};

#endif /* KMEANS_H_ */
