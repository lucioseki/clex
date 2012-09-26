/*
 * NMIndex.h
 *
 *  Created on: ??/??/2010
 *      Author: ???
 */

#include "NMIIndex.h"

/* Implementation of both inherited methods */
double NMIIndex::calculate(Partition &objAPartition1, Partition &objAPartition2)
{
	return  mutualInformation(objAPartition1, objAPartition2)/sqrt(entropy(objAPartition1)*entropy(objAPartition2));
}

/* This method is to be used in internal validation measures, since NMI isn't an internal validation measure
    the call of this method will throw an exception */
double NMIIndex::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}
