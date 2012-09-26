/*
 * CRIndex.cpp
 *
 *      Author: Vinicius
 */

#include "CRIndex.h"

/* Implementation of both inherited methods */
double CRIndex::calculate(Partition &objAPartition1, Partition &objAPartition2){

	int iNObjects;
    int i, j;
	double dCr = 0;
    double dT1, dT2, dT3, dT4, dT5;

    vector<vector<int> > contingencyTable(objAPartition1.getNumClusters());
    vector<int> mSomaPartition1(objAPartition1.getNumClusters(),0); // create and initialize
    vector<int> mSomaPartition2(objAPartition2.getNumClusters(),0);

    dT1 = dT2 = dT3 = dT4 = dT5 = 0;

    for (vector<vector<int> >::iterator it = contingencyTable.begin(); it != contingencyTable.end(); it++){
    	it->resize(objAPartition2.getNumClusters(),0);
    }

    //TODO Mudar para itClusterOnPartition
    Partition::itClustersOfPartition itPartition1, itPartition2;
    //TODO MUDADO Partition::Cluster::itObjectsOfCluster itCluster1, itCluster2;
    Cluster::itObjectsOfCluster itObjectOnCluster1, itObjectOnCluster2;

    for (itPartition1 = objAPartition1.begin(), i = 0; itPartition1 != objAPartition1.end(); itPartition1++, i++){
    	for (itPartition2 = objAPartition2.begin(), j = 0; itPartition2 != objAPartition2.end(); itPartition2++, j++){
    		for (itObjectOnCluster1 = itPartition1->begin(); itObjectOnCluster1 != itPartition1->end(); itObjectOnCluster1++){ // for each object in the i th cluster of partition 1
    			itObjectOnCluster2 = find(itPartition2->begin(), itPartition2->end(), *itObjectOnCluster1); // search for the object in the j th cluster of partition 2
				if(itObjectOnCluster2 != itPartition2->end())
					contingencyTable[i][j]++;
    		}
    	}
    }

    for (i = 0; i < objAPartition1.getNumClusters(); i++){
        for (j = 0; j < objAPartition2.getNumClusters(); j++){
            mSomaPartition1[i] += contingencyTable[i][j];
        }
    }

    for (j = 0; j < objAPartition2.getNumClusters(); j++){
        for (i = 0; i < objAPartition1.getNumClusters(); i++){
            mSomaPartition2[j] += contingencyTable[i][j];
        }
    }

    for (i = 0; i < objAPartition1.getNumClusters(); i++){
        for (j = 0; j < objAPartition2.getNumClusters(); j++){
            dT1 += (contingencyTable[i][j] * contingencyTable[i][j] - contingencyTable[i][j])/2;
        }
    }

    for (i = 0; i < objAPartition1.getNumClusters(); i++){
        dT2 += (mSomaPartition1[i] * mSomaPartition1[i] - mSomaPartition1[i]) / 2;
    }

    for (j = 0; j < objAPartition2.getNumClusters(); j++){
       dT3 += (mSomaPartition2[j] * mSomaPartition2[j] - mSomaPartition2[j]) / 2;
    }

    iNObjects = objAPartition2.getNumObjects();
    dT4 = (iNObjects * iNObjects - iNObjects) / 2;
    dT5 = (dT2 * dT3) / dT4;
    dCr = (dT1 - dT5) / ( (dT2 + dT3) / 2 - dT5);

    return dCr;

}

/* This method is to be used in internal validation measures, since CR isn't an internal validation measure
    the call of this method will throw an exception */
double CRIndex::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}

