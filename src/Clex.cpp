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

// initializes the maps
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
void Clex::setSimilarity(const vector<string> &vASSimilarity){
	for(int i = 0; i < vASSimilarity.size(); i++){
		vSimilarity.push_back(mapSimilarity[vASSimilarity[i]]);
	}
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
		for(vector<Similarity*>::iterator itSimilarity = vSimilarity.begin(); itSimilarity != vSimilarity.end(); itSimilarity++){
			vRelationSDN.push_back(new RelationSDN(*itSimilarity, *itDataSet, iANumNn));
		}
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

// calculate the validation indexes
void Clex::calculateValidationIndex(){
	calculateInternalIndex();
	calculateExternalIndex();
}

// calculate the internal validation indexes
void Clex::calculateInternalIndex(){
	for(vector<RelationSDN*>::iterator itRelationSDN = vRelationSDN.begin(); itRelationSDN != vRelationSDN.end(); itRelationSDN++){
		for(set<ValidationIndex*>::iterator itValidationIndex = sInternalIndex.begin(); itValidationIndex != sInternalIndex.end(); itValidationIndex++){
			for(vector<Partition*>::iterator itPartition = mapGeneratedPartitions[(*itRelationSDN)->getDataSet()].begin(); itPartition != mapGeneratedPartitions[(*itRelationSDN)->getDataSet()].end(); itPartition++){
				mapCalculatedInternalIndex[(*itRelationSDN)->getDataSet()][*itPartition][(*itRelationSDN)->getNnList()->getNumberOfNn()][*itValidationIndex] = (*itValidationIndex)->calculate(*itPartition, *itRelationSDN, (*itRelationSDN)->getDataSet());	
			}
		}
	}
}

// calculate the external validation indexes
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

// shows the calculated indexes
void Clex::showInternalIndex(){
	cout << "Internal Validation Index" << endl;
	for(map<DataSet*, map<Partition*, map<int, map<ValidationIndex*, double> > > >::iterator itDataSet = mapCalculatedInternalIndex.begin(); itDataSet != mapCalculatedInternalIndex.end(); itDataSet++){
		cout << endl << "DataSet: " << itDataSet->first->getNameDataSet() << endl;
		for(map<Partition*, map<int, map<ValidationIndex*, double> > >::iterator itPartition = mapCalculatedInternalIndex[itDataSet->first].begin(); itPartition != mapCalculatedInternalIndex[itDataSet->first].end(); itPartition++){
			cout << "Partition: " << itPartition->first->getPartitionName() << endl;
			for(map<int, map<ValidationIndex*, double> >::iterator itNumNn = mapCalculatedInternalIndex[itDataSet->first][itPartition->first].begin(); itNumNn != mapCalculatedInternalIndex[itDataSet->first][itPartition->first].end(); itNumNn++){
				cout << "NumNn: " << itNumNn->first << endl;
				for(map<ValidationIndex*, double>::iterator itValidationIndex = mapCalculatedInternalIndex[itDataSet->first][itPartition->first][itNumNn->first].begin(); itValidationIndex != mapCalculatedInternalIndex[itDataSet->first][itPartition->first][itNumNn->first].end(); itValidationIndex++){
					cout << typeid(*(itValidationIndex->first)).name() << "\t" << mapCalculatedInternalIndex[itDataSet->first][itPartition->first][itNumNn->first][itValidationIndex->first] << endl;;
				}
			}
			cout << endl;
		}
	}
}

// shows the external calculated Indexes
void Clex::showExternalIndex(){
	cout << "External Validation Index" << endl;
	for(map<DataSet*, map<Partition*, map<Partition* , map<ValidationIndex*, double> > > >::iterator itDataSet = mapCalculatedExternalIndex.begin(); itDataSet != mapCalculatedExternalIndex.end(); itDataSet++){
		cout << endl << "DataSet: " << itDataSet->first->getNameDataSet() << endl;
		for(map<Partition*, map<Partition*, map<ValidationIndex*, double> > >::iterator itRealPartition = mapCalculatedExternalIndex[itDataSet->first].begin(); itRealPartition != mapCalculatedExternalIndex[itDataSet->first].end(); itRealPartition++){
			cout << "Real Partition: " << itRealPartition->first->getPartitionName() << endl;
			for(map<Partition*, map<ValidationIndex*, double> >::iterator itGeneratedPartition = mapCalculatedExternalIndex[itDataSet->first][itRealPartition->first].begin(); itGeneratedPartition != mapCalculatedExternalIndex[itDataSet->first][itRealPartition->first].end(); itGeneratedPartition++){
				cout << "Generated Partition: " << itGeneratedPartition->first->getPartitionName() << endl;
				for(map<ValidationIndex*, double>::iterator itValidationIndex = mapCalculatedExternalIndex[itDataSet->first][itRealPartition->first][itGeneratedPartition->first].begin(); itValidationIndex != mapCalculatedExternalIndex[itDataSet->first][itRealPartition->first][itGeneratedPartition->first].end(); itValidationIndex++){
					cout << typeid(*(itValidationIndex->first)).name() << "\t" << mapCalculatedExternalIndex[itDataSet->first][itRealPartition->first][itGeneratedPartition->first][itValidationIndex->first] << endl;;
				}
			}
			cout << endl;
		}
	}
}
