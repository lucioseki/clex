/*
 * InformationTheory.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#include"InformationTheory.h"

/* Implementation of methods in InformationTheory class */
double InformationTheory::entropy(Partition &objPartition) {
	double dSummation = 0;
	double dStore;

	for(Partition::itClustersOfPartition it1 = objPartition.begin(); it1 != objPartition.end(); it1++){
		dStore = (*it1).getNumberOfObjects()	/ static_cast<double> (objPartition.getNumObjects());
		if (dStore != 0) dStore *= log10(dStore); // assumindo log0 = 0
		dSummation += dStore;
	}

	return -dSummation;
}

double InformationTheory::intersection(Partition &objPartition1, Partition &objPartition2, Partition::itClustersOfPartition itPartition1, Partition::itClustersOfPartition itPartition2) {
	//itPartition1 e itPartition2 representam os clusters
	int iCounter = 0;

	for (Cluster::itObjectsOfCluster itObjects1 = (*itPartition1).begin(); itObjects1 != (*itPartition1).end(); itObjects1++) {
		if (itPartition2->find((*itObjects1)) != itPartition2->end())
			iCounter++;
	}

	return iCounter / static_cast<double> (objPartition1.getNumObjects());
}

double InformationTheory::mutualInformation(Partition &objPartition1, Partition &objPartition2) {
	double dSummation = 0;
	double dStore = 0, dProbabilityPartition1 = 0, dProbabilityPartition2 = 0;

	for(Partition::itClustersOfPartition it1 = objPartition1.begin(); it1 != objPartition1.end(); it1++){
		for(Partition::itClustersOfPartition it2 = objPartition1.begin(); it2 != objPartition1.end(); it2++){
			dStore = intersection(objPartition1, objPartition2, it1, it2);

			dProbabilityPartition1 = (*it1).getNumberOfObjects() / static_cast<double> (objPartition1.getNumObjects());
			dProbabilityPartition2 = (*it2).getNumberOfObjects() / static_cast<double> (objPartition2.getNumObjects());

			if (dStore != 0 && dStore / (dProbabilityPartition1 * dProbabilityPartition2) != 0) {
				dStore *= log10(dStore / ((dProbabilityPartition1 * dProbabilityPartition2)));
				dSummation += dStore;
			}
		}
	}

	return dSummation;
}



