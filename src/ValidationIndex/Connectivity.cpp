/*
 * Connectivity.cpp
 *
 *  Created on: 12/03/2010
 *      Author: Gustavo
 */

#include "Connectivity.h"

Connectivity::Connectivity() {
}

Connectivity::~Connectivity() {
}

double Connectivity::calculate(Partition *pAPartition, RelationSDN *pARelation,	DataSet *pADataSet) {
	double connectivity = 0;
	for (Partition::itClustersOfPartition itClusterOnPartition = pAPartition->begin(); itClusterOnPartition != pAPartition->end(); itClusterOnPartition++){

		/* TODO MUDADO
		for(Partition::Cluster::itObjectsOfCluster itObjectsOnCluster1 = (*itClusterOnPartition)->begin(); itObjectsOnCluster1 != (*itClusterOnPartition)->end(); itObjectsOnCluster1++){
			// vizinhos
			for (int j = 1; j <= pARelation->getNnList()->getNumberOfNn(); j++){
				if (pAPartition->getClusterOf((pARelation->getNnList()->nearestNeighbor(j))) !=  itClusterOnPartition)
				connectivity += 1.0/j;
			}
		}*/
		for(Cluster::itObjectsOfCluster itObjectsOnCluster1 = (*itClusterOnPartition).begin(); itObjectsOnCluster1 != (*itClusterOnPartition).end(); itObjectsOnCluster1++){
			// vizinhos
			for (int j = 1; j <= pARelation->getNnList()->getNumberOfNn(); j++){
				if (pAPartition->getClusterOf((pARelation->getNnList()->nearestNeighbor(*itObjectsOnCluster1, j))) !=  itClusterOnPartition)
					connectivity += 1.0/j;
			}
		}
	}

	return connectivity;
}

double Connectivity::calculate(Partition &objAPartition1, Partition &objAPartition2) {
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}
