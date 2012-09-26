/*
 * Silhouette.cpp
 *
 *  Created on: 22/03/2010
 *      Author: Gustavo
 */

#include "Silhouette.h"

Silhouette::Silhouette() {
	// TODO Auto-generated constructor stub
}

Silhouette::~Silhouette() {
	// TODO Auto-generated destructor stub
}

double Silhouette::a(Cluster::itObjectsOfCluster itAObjectsOnCluster, Partition::itClustersOfPartition itAClusterOnPartition, RelationSDN *pARelation){
	double dSimilarity = 0;
	for(Cluster::itObjectsOfCluster itObjectsOnCluster2 = itAClusterOnPartition->begin(); itObjectsOnCluster2 != itAClusterOnPartition->end(); itObjectsOnCluster2++){
		//TODO VER O QUE FAZER
		//dSimilarity += pARelation->getSimilarityMatrix()->getSimilarity((*itAObjectsOnCluster), (*itObjectsOnCluster2));
	}
	return dSimilarity / itAClusterOnPartition->getNumberOfObjects();
}

double Silhouette::bSimilarity(Cluster::itObjectsOfCluster itAObjectOnCluster, Partition::itClustersOfPartition itAClusterOfObject, Partition *pAPartition, RelationSDN *pARelation){
	Partition::itClustersOfPartition itOtherCluster = pAPartition->begin();
	double dBxi;
	if(itAClusterOfObject == itOtherCluster)
		itOtherCluster++;
	dBxi = a(itAObjectOnCluster, itOtherCluster, pARelation);
	itOtherCluster++;
	for (; itOtherCluster != pAPartition->end(); itOtherCluster++){
		if(itAClusterOfObject != itOtherCluster){
			double dBxiAux = a(itAObjectOnCluster, itOtherCluster, pARelation);
			if (dBxiAux < dBxi)
				dBxi = dBxiAux;
		}
	}
	return dBxi;
}

double Silhouette::bDissimilarity(Cluster::itObjectsOfCluster itAObjectOnCluster, Partition::itClustersOfPartition itAClusterOfObject, Partition *pAPartition, RelationSDN *pARelation){
	Partition::itClustersOfPartition itOtherCluster = pAPartition->begin();
	double dBxi;
	if(itAClusterOfObject == itOtherCluster)
		itOtherCluster++;
	dBxi = a(itAObjectOnCluster, itOtherCluster, pARelation);
	itOtherCluster++;
	for (; itOtherCluster != pAPartition->end(); itOtherCluster++){
		if(itAClusterOfObject != itOtherCluster){
			double dBxiAux = a(itAObjectOnCluster, itOtherCluster,pARelation);
			if (dBxiAux > dBxi)
				dBxi = dBxiAux;
		}
	}
	return dBxi;
}

double Silhouette::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){

	//Declaration variables used by Silhouette
	double silhouette = 0;
	// # retirar Similarity *pObjSimilarity = pARelation->getSimilarity();

	//Walk vector of all clusters
	for (Partition::itClustersOfPartition itClusterOnPartition = pAPartition->begin(); itClusterOnPartition != pAPartition->end(); itClusterOnPartition++){

		//Walk each object of cluster
		for(Cluster::itObjectsOfCluster itObjectsOnCluster1 = itClusterOnPartition->begin(); itObjectsOnCluster1 != itClusterOnPartition->end(); itObjectsOnCluster1++){
			double dAxi = a(itObjectsOnCluster1, itClusterOnPartition, pARelation);

			double dBxi, dSxi;
			if (pARelation->getSimilarity()->isSimilarity()){
				dBxi = bSimilarity(itObjectsOnCluster1, itClusterOnPartition, pAPartition, pARelation);
				if (dAxi > dBxi)
					dSxi = 1 - (dBxi / dAxi);
				else if (dAxi == dBxi)
					dSxi = 0;
				else
					dSxi = (dAxi / dBxi) - 1;
			}
			else {
				dBxi = bDissimilarity(itObjectsOnCluster1, itClusterOnPartition, pAPartition, pARelation);
				if (dAxi < dBxi)
					dSxi = 1 - (dAxi / dBxi);
				else if (dAxi == dBxi)
					dSxi = 0;
				else
					dSxi = (dBxi / dAxi) - 1;
			}
			silhouette += dSxi;
		}
	}
	silhouette = silhouette / pAPartition->getNumObjects();
	return silhouette;
}

double Silhouette::calculate(Partition &objAPartition1, Partition &objAPartition2){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}

