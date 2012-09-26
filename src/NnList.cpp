/*
 * NnList.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vin’cius
 */

#include "NnList.h"

NnList::NnList(RelationSDN *pARelationSDN, int iANumNn) {
	iNumNn = iANumNn;
	vector<pair<DataSet::itObjectsOfDataSet, double> > vectorObjectTemp, vectorObjectTempSorted;

	//Similarity
	if (pARelationSDN->getSimilarity()->isSimilarity()){
		for (DataSet::itObjectsOfDataSet it1 = pARelationSDN->getDataSet()->begin(); it1 != pARelationSDN->getDataSet()->end(); it1++){
			for (DataSet::itObjectsOfDataSet it2 = pARelationSDN->getDataSet()->begin(); it2 != pARelationSDN->getDataSet()->end(); it2++){
				if (it1 != it2)
					vectorObjectTemp.insert(vectorObjectTemp.end(), make_pair(it2, pARelationSDN->getSimilarityMatrix()->getSimilarity(it1.operator->(), it2.operator->())));
			}
			vectorObjectTempSorted.resize(iANumNn);

			partial_sort_copy(vectorObjectTemp.begin(), vectorObjectTemp.end(), vectorObjectTempSorted.begin(), vectorObjectTempSorted.end(), CompareObjectL());

			for (vector<pair<DataSet::itObjectsOfDataSet, double> >::iterator it = vectorObjectTempSorted.begin(); it != vectorObjectTempSorted.end(); it++){
				mapNnList[it1].insert(mapNnList[it1].end(), it->first);
			}

		}
	// Dissimilarity
	} else {
		for (DataSet::itObjectsOfDataSet it1 = pARelationSDN->getDataSet()->begin(); it1 != pARelationSDN->getDataSet()->end(); it1++){
			for (DataSet::itObjectsOfDataSet it2 = pARelationSDN->getDataSet()->begin(); it2 != pARelationSDN->getDataSet()->end(); it2++){
				if (it1 != it2)
					vectorObjectTemp.insert(vectorObjectTemp.end(), make_pair(it2, pARelationSDN->getSimilarityMatrix()->getSimilarity(it1.operator->(), it2.operator->())));
	        }
			vectorObjectTempSorted.resize(iANumNn);

			partial_sort_copy(vectorObjectTemp.begin(), vectorObjectTemp.end(), vectorObjectTempSorted.begin(), vectorObjectTempSorted.end(), CompareObjectL());

			for (vector<pair<DataSet::itObjectsOfDataSet, double> >::iterator it = vectorObjectTempSorted.begin(); it != vectorObjectTempSorted.end(); it++){
				mapNnList[it1].insert(mapNnList[it1].end(), it->first);
			}
		}
	}
}

NnList::~NnList() {}

DataSet::itObjectsOfDataSet NnList::nearestNeighbor(DataSet::itObjectsOfDataSet objAObject, int iAIndex) {
	return mapNnList[objAObject][iAIndex -1];
}

int NnList::getNumberOfNn() {
	return iNumNn;
}

void NnList::print() {
	for (itNeighborsOfObject it = mapNnList.begin() ; it != mapNnList.end(); it++) {
		cout << it->first->getId() << " => ";
		for (vector<DataSet::itObjectsOfDataSet>::iterator it2 = it->second.begin(); it2 < it->second.end(); it2++) {
			cout << " " << it2->operator->()->getId();
		}
		cout << endl;
	}
}
