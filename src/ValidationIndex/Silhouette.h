/*
 * Silhouette.h
 *
 *  Created on: 22/03/2010
 *      Author: Gustavo
 */

#ifndef SILHOUETTE_H_
#define SILHOUETTE_H_

#include "Deviation.h"
#include "../DataSet.h"
#include "../Partition.h"
#include "../RelationSDN.h"
#include "../ValidationIndex.h"

/**
 *  @author Gustavo Rodrigues
 *  @since 22/03/10
 *  @version 2.0
 */

/* Gustavo, colocar um breve comentário sobre o que a silhouette faz */
/* Colacar um comentário mais detalhado sobre o que faz a silhoutte e porque ela herda da ValidationIndex */
class Silhouette: public ValidationIndex {
private:
	/*TODO MUDADO
	double a(Partition::Cluster::itObjectsOfCluster itAObjectsOnCluster, Partition::itClustersOfPartition itAClusterOnPartition, RelationSDN *pARelation);
	double bSimilarity(Partition::Cluster::itObjectsOfCluster itAObjectOnCluster, Partition::itClustersOfPartition itAClusterOfObject, Partition *pAPartition, RelationSDN *pARelation);
	double bDissimilarity(Partition::Cluster::itObjectsOfCluster itAObjectOnCluster, Partition::itClustersOfPartition itAClusterOfObject, Partition *pAPartition, RelationSDN *pARelation);
	*/

	double a(Cluster::itObjectsOfCluster itAObjectsOnCluster, Partition::itClustersOfPartition itAClusterOnPartition, RelationSDN *pARelation);
	double bSimilarity(Cluster::itObjectsOfCluster itAObjectOnCluster, Partition::itClustersOfPartition itAClusterOfObject, Partition *pAPartition, RelationSDN *pARelation);
	double bDissimilarity(Cluster::itObjectsOfCluster itAObjectOnCluster, Partition::itClustersOfPartition itAClusterOfObject, Partition *pAPartition, RelationSDN *pARelation);

public:
	Silhouette();
	virtual ~Silhouette();

	/** Return value of silhouette from parameter partition*/
	/** @param Partition, RelationSDN and DataSet */
	/** @return Value silhouette*/
	virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset);

	/** Does nothing */
	virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
};

#endif /* SILHOUETTE_H_ */
