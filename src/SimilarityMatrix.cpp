/*
 * SimilarityMatrix.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vin’cius
 */

#include "SimilarityMatrix.h"

SimilarityMatrix::SimilarityMatrix(RelationSDN *pARelationSDN) {
	for (DataSet::itObjectsOfDataSet it1 = pARelationSDN->getDataSet()->begin(); it1 != pARelationSDN->getDataSet()->end(); it1++) {
		for (DataSet::itObjectsOfDataSet it2 = pARelationSDN->getDataSet()->begin(); it2 != pARelationSDN->getDataSet()->end(); it2++) {
			mapMatrix[it1.base()][it2.base()] = pARelationSDN->getSimilarity()->calculate(*it1, *it2);
		}
	}
}

SimilarityMatrix::~SimilarityMatrix() {}

double SimilarityMatrix::getSimilarity(Object *objAObject1, Object *objAObject2){
	return mapMatrix[objAObject1][objAObject2];
}

//For tests
void SimilarityMatrix::print(RelationSDN *pARelationSDN) {
	for (DataSet::itObjectsOfDataSet it1 = pARelationSDN->getDataSet()->begin(); it1 != pARelationSDN->getDataSet()->end(); it1++) {
		for (DataSet::itObjectsOfDataSet it2 = pARelationSDN->getDataSet()->begin(); it2 != pARelationSDN->getDataSet()->end(); it2++) {
			cout << mapMatrix[it1.base()][it2.base()] << "\t";
		}
		cout << endl;
	}
}
