/*
 * Deviation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: Gustavo
 */

#include "Deviation.h"


Deviation::Deviation() { }

Deviation::~Deviation() { }

double Deviation::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){

	double dDev = 0;


	//walk all cluster from partition
	/*TODO MUDADO
	for(Partition::itClustersOfPartition itP = pAPartition->begin(); itP != pAPartition->end(); itP++){
		Object* centroid = (*itP).getCentroid();
		for(Partition::Cluster::itObjectsOfCluster itC = (*itP).begin(); itC != (*itP).end(); itC++){
			dDev +=  pARelation->getSimilarity()->calculate((*itC), (*centroid));
		}
	}*/
	for(Partition::itClustersOfPartition itP = pAPartition->begin(); itP != pAPartition->end(); itP++){
		Object *centroid = itP->getCentroid();
		for(Cluster::itObjectsOfCluster itC = itP->begin(); itC != itP->end(); itC++){
			dDev +=  pARelation->getSimilarity()->calculate((*(*itC)), *centroid);
		}
	}

	return dDev;
}

double Deviation::calculate(Partition &objAPartition1, Partition &objAPartition2){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}
