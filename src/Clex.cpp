#include "Clex.h"
#include "ValidationIndex.h"
#include "ValidationIndex/CRIndex.h"
#include "ValidationIndex/NMIIndex.h"
#include "ValidationIndex/VIIndex.h"
#include "ValidationIndex/Connectivity.h"
#include "ValidationIndex/Deviation.h"
#include "ValidationIndex/Silhouette.h"
#include <iostream>
using namespace std;

Clex::Clex(){
	mapSimilarity["Euclidean"] = new Euclidean();
	mapSimilarity["Pearson"] = new Pearson();
	mapExternalIndex["CRIndex"] = new CRIndex();
	mapExternalIndex["NMIIndex"] = new NMIIndex();
	mapExternalIndex["VIIndex"] = new VIIndex();
	mapInternalIndex["Deviation"] = new Deviation();
	mapInternalIndex["Silhouette"] = new Silhouette();
	mapInternalIndex["Connectivity"] = new Connectivity();
}

// sets the similarity measure
void Clex::setSimilarity(const string &sASimilarity){
	pSimilarity = mapSimilarity[sASimilarity];
}

// sets the DataSet vector
void Clex::setDataSet(vector<pair<string, string> > &vASDataSet){
	for(int i = 0; i < vASDataSet.size(); i++){
		vDataSet.push_back(new DataSet(vASDataSet[i].first, vASDataSet[i].second));
	}
}

// sets the External Validation Indexes to be used
// @param a vector of names of the indexes
void Clex::setExternalIndex(vector<string> &vASValidationIndex){
	for(int i = 0; i < vASValidationIndex.size(); i++){
		sExternalIndex.insert(mapExternalIndex[vASValidationIndex[i]]);
	}
}

// sets the External Validation Indexes to be used
// @param a vector of names of the indexes
void Clex::setInternalIndex(vector<string> &vASValidationIndex){
	for(int i = 0; i < vASValidationIndex.size(); i++){
		sInternalIndex.insert(mapInternalIndex[vASValidationIndex[i]]);
	}
}

// creates RelationSDN for each combination of Similarity, DataSet and NumNn
void Clex::createRelationSDN(int iANumNn){
	for(vector<DataSet*>::iterator itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		vRelationSDN.push_back(new RelationSDN(pSimilarity, *itDataSet, iANumNn));
	}
}

// sets the vector of real partitions for a DataSet
void Clex::setRealPartition(int iADataSet, vector<pair<string, string> > &vASPartition){
	for(int i = 0; i < vASPartition.size(); i++){ 
		mapRealPartitions[vDataSet[iADataSet]].push_back(new Partition(vDataSet[iADataSet], vASPartition[i].first, vASPartition[i].second));
	}
}

// sets the vector of generated partitions for a DataSet
void Clex::setGeneratedPartition(int iADataSet, vector<pair<string, string> > &vASPartition){
	for(int i = 0; i < vASPartition.size(); i++){
		mapGeneratedPartitions[vDataSet[iADataSet]].push_back(new Partition(vDataSet[iADataSet], vASPartition[i].first, vASPartition[i].second));
	}
}

void Clex::calculateValidationIndex(){
	calculateExternalIndex();
	calculateInternalIndex();
}

// calculate the validation indexes
void Clex::calculateExternalIndex(){
	// for each dataset
	for(vector<DataSet*>::iterator itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each real partition
		for(vector<Partition*>::iterator itRealPartition = mapRealPartitions[*itDataSet].begin(); itRealPartition != mapRealPartitions[*itDataSet].end(); itRealPartition++){
			// for each generated partition
			for(vector<Partition*>::iterator itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
				// calculate the indexes of generated partition and real partition and save on the map
				for(set<ValidationIndex*>::iterator itValidationIndex = sExternalIndex.begin(); itValidationIndex != sExternalIndex.end(); itValidationIndex++){
					mapCalculatedExternalIndex[*itDataSet][*itRealPartition][*itGeneratedPartition][*itValidationIndex] = (*itValidationIndex)->calculate(**itGeneratedPartition, **itRealPartition);
				}
			}
		}
	}
}

void Clex::calculateInternalIndex(){
	for(vector<RelationSDN*>::iterator itRelationSDN = vRelationSDN.begin(); itRelationSDN != vRelationSDN.end(); itRelationSDN++){
		for(set<ValidationIndex*>::iterator itValidationIndex = sInternalIndex.begin(); itValidationIndex != sInternalIndex.end(); itValidationIndex++){
			for(vector<Partition*>::iterator itPartition = mapGeneratedPartitions[(*itRelationSDN)->getDataSet()].begin(); itPartition != mapGeneratedPartitions[(*itRelationSDN)->getDataSet()].end(); itPartition++){
				mapCalculatedInternalIndex[(*itRelationSDN)->getDataSet()][*itPartition][(*itRelationSDN)->getNnList()->getNumberOfNn()][*itValidationIndex] = (*itValidationIndex)->calculate(*itPartition, *itRelationSDN, (*itRelationSDN)->getDataSet());	
			}
		}
	}
}

// shows the calculated indexes
void Clex::showValidationIndex(){
		/*
	if(sValidationIndex.find("CRIndex") != sValidationIndex.end())
		showCRIndex();
	if(sValidationIndex.find("NMIIndex") != sValidationIndex.end())
		showNMIIndex();
	if(sValidationIndex.find("VIIndex") != sValidationIndex.end())
		showVIIndex();
	if(sValidationIndex.find("Connectivity") != sValidationIndex.end())
		showConnectivity();
	if(sValidationIndex.find("Deviation") != sValidationIndex.end())
		showDeviation();
	if(sValidationIndex.find("Silhouette") != sValidationIndex.end())
		showSilhouette();
		*/
}
