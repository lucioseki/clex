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

// sets the similarity measure
void Clex::setSimilarity(string sASimilarity){
	if(sASimilarity.compare("Euclidean") == 0){
		pSimilarity = &objEuclidean;
	}else if(sASimilarity.compare("Pearson") == 0){
		pSimilarity = &objPearson;
	}else{
		cout << "Unknown similarity measure" << endl;
	}
}

// sets the DataSet vector
void Clex::setDataSet(vector<pair<string, string> > vASDataSet){
	for(int i = 0; i < vASDataSet.size(); i++){
		vDataSet.push_back(new DataSet(vASDataSet[i].first, vASDataSet[i].second));
	}
}

// sets the Validation Indexes to be used
// @param a vector of names of the indexes
void Clex::setValidationIndex(vector<string> vASValidationIndex){
	for(int i = 0; i < vASValidationIndex.size(); i++){
		sValidationIndex.insert(vASValidationIndex[i]);
	}
}

// creates RelationSDN for each combination of Similarity, DataSet and NumNn
void Clex::createRelationSDN(int iANumNn){
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		mapRelationSDN[pSimilarity][*itDataSet][iANumNn] = new RelationSDN(pSimilarity, *itDataSet, iANumNn);
	}
}

// sets the vector of real partitions for a DataSet
void Clex::setRealPartition(int iADataSet, vector<pair<string, string> > vASPartition){
	for(int i = 0; i < vASPartition.size(); i++){ 
		mapRealPartitions[vDataSet[iADataSet]].push_back(new Partition(vDataSet[iADataSet], vASPartition[i].first, vASPartition[i].second));
	}
}

// sets the vector of generated partitions for a DataSet
void Clex::setGeneratedPartition(int iADataSet, vector<pair<string, string> > vASPartition){
	for(int i = 0; i < vASPartition.size(); i++){
		mapGeneratedPartitions[vDataSet[iADataSet]].push_back(new Partition(vDataSet[iADataSet], vASPartition[i].first, vASPartition[i].second));
	}
}

// calculate the validation indexes
void Clex::calculateValidationIndex(){
	CRIndex obCRIndex;
	NMIIndex obNMIIndex;
	VIIndex obVIIndex;
	Connectivity obConnectivity;
	Deviation obDeviation;
	Silhouette obSilhouette;

	// for each dataset
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// for each real partition
			for(itPartitionOfClex itRealPartition = mapRealPartitions[*itDataSet].begin(); itRealPartition != mapRealPartitions[*itDataSet].end(); itRealPartition++){
				// calculate the indexes of generated partition and real partition
				// and save on the maps
				if(sValidationIndex.find("CRIndex") != sValidationIndex.end()){
					mapCRIndex[*itDataSet][*itGeneratedPartition][*itRealPartition] = obCRIndex.calculate(**itGeneratedPartition, **itRealPartition);
				}
				if(sValidationIndex.find("NMIIndex") != sValidationIndex.end()){
					mapNMIIndex[*itDataSet][*itGeneratedPartition][*itRealPartition] = obNMIIndex.calculate(**itGeneratedPartition, **itRealPartition);
				}
				if(sValidationIndex.find("NMIIndex") != sValidationIndex.end()){
					mapVIIndex[*itDataSet][*itGeneratedPartition][*itRealPartition] = obNMIIndex.calculate(**itGeneratedPartition, **itRealPartition);
				}
			}
		}
	}
	for(map<Similarity*, map<DataSet*, map<int, RelationSDN*> > >::iterator itMapSimilarity = mapRelationSDN.begin(); itMapSimilarity != mapRelationSDN.end(); itMapSimilarity++){
		for(map<DataSet*, map<int, RelationSDN*> >::iterator itMapDataSet = mapRelationSDN[itMapSimilarity->first].begin(); itMapDataSet != mapRelationSDN[itMapSimilarity->first].end(); itMapDataSet++){
			for(map<int, RelationSDN*>::iterator itMapNumNn = mapRelationSDN[itMapSimilarity->first][itMapDataSet->first].begin(); itMapNumNn != mapRelationSDN[itMapSimilarity->first][itMapDataSet->first].end(); itMapNumNn++){
				for(itPartitionOfClex itPartition = mapGeneratedPartitions[itMapDataSet->first].begin(); itPartition != mapGeneratedPartitions[itMapDataSet->first].end(); itPartition++){
					if(sValidationIndex.find("Connectivity") != sValidationIndex.end()){
						mapConnectivity[itMapDataSet->first][*itPartition][itMapNumNn->first] = obConnectivity.calculate(*itPartition, mapRelationSDN[itMapSimilarity->first][itMapDataSet->first][itMapNumNn->first], itMapDataSet->first);
					}
					if(sValidationIndex.find("Deviation") != sValidationIndex.end()){
						mapDeviation[itMapDataSet->first][*itPartition][itMapNumNn->first] = obDeviation.calculate(*itPartition, mapRelationSDN[itMapSimilarity->first][itMapDataSet->first][itMapNumNn->first], itMapDataSet->first);
					}
					if(sValidationIndex.find("Silhouette") != sValidationIndex.end()){
						mapSilhouette[itMapDataSet->first][*itPartition][itMapNumNn->first] = obSilhouette.calculate(*itPartition, mapRelationSDN[itMapSimilarity->first][itMapDataSet->first][itMapNumNn->first], itMapDataSet->first);
					}
				}
			}
		}
	}
}

// calculates the CRIndex for each generated Partition with each real Partition
void Clex::calculateCRIndex(){
	CRIndex obCRIndex;

	// for each DataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// for each real partition
			for(itPartitionOfClex itRealPartition = mapRealPartitions[*itDataSet].begin(); itRealPartition != mapRealPartitions[*itDataSet].end(); itRealPartition++){
				// calculate CRIndex of generated partition and real partition
				// and save on mapCRIndex
				mapCRIndex[*itDataSet][*itGeneratedPartition][*itRealPartition] = obCRIndex.calculate(**itGeneratedPartition, **itRealPartition);
			}
		}	
	}
}

// calculates the NMIIndex for each generated Partition with each real Partition
void Clex::calculateNMIIndex(){
	NMIIndex obNMIIndex;

	// for each DataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// for each real partition
			for(itPartitionOfClex itRealPartition = mapRealPartitions[*itDataSet].begin(); itRealPartition != mapRealPartitions[*itDataSet].end(); itRealPartition++){
				// calculate NMIIndex of generated partition and real partition
				// and save on mapNMIIndex
				mapNMIIndex[*itDataSet][*itGeneratedPartition][*itRealPartition] = obNMIIndex.calculate(**itGeneratedPartition, **itRealPartition);
			}
		}
	}
}

// calculates the VIIndex for each generated Partition with each real Partition
void Clex::calculateVIIndex(){
	VIIndex obNMIIndex;

	// for each DataSet in vDataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// for each real partition
			for(itPartitionOfClex itRealPartition = mapRealPartitions[*itDataSet].begin(); itRealPartition != mapRealPartitions[*itDataSet].end(); itRealPartition++){
				// calculate VIIndex of generated partition and real partition
				// and save on mapVIIndex
				mapVIIndex[*itDataSet][*itGeneratedPartition][*itRealPartition] = obNMIIndex.calculate(**itGeneratedPartition, **itRealPartition);
			}
		}	
	}
}

// calculates the Connectivity for each generated Partition
// @param number of Nearest neighbours
void Clex::calculateConnectivity(int iANumNn){
	RelationSDN *pObjRelationSDN;
	Connectivity obConnectivity;

	// for each DataSet in vDataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each generated partition
		pObjRelationSDN = new RelationSDN(pSimilarity, *itDataSet, iANumNn);
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// calculate Connectivity of generated partition
			// and save on mapConnectivity
			mapConnectivity[*itDataSet][*itGeneratedPartition][iANumNn] = obConnectivity.calculate(*itGeneratedPartition, pObjRelationSDN, *itDataSet);
		}	
	}
}

// calculates the Deviation for each generated Partition
// @param number of Nearest neighbours
void Clex::calculateDeviation(int iANumNn){
	RelationSDN *pObjRelationSDN;
	Deviation obDeviation;

	// for each DataSet in vDataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each generated partition
		pObjRelationSDN = new RelationSDN(pSimilarity, *itDataSet, iANumNn);
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// calculate Connectivity of generated partition
			// and save on mapConnectivity
			mapDeviation[*itDataSet][*itGeneratedPartition][iANumNn] = obDeviation.calculate(*itGeneratedPartition, pObjRelationSDN, *itDataSet);
		}
	}
}

// calculates the Silhouette index for each generated Partition
// @param number of Nearest neighbours
void Clex::calculateSilhouette (int iANumNn){
	RelationSDN *pObjRelationSDN;
	Silhouette obSilhouette;

	// for each DataSet in vDataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each generated partition
		pObjRelationSDN = new RelationSDN(pSimilarity, *itDataSet, iANumNn);
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// calculate Connectivity of generated partition
			// and save on mapConnectivity
			mapSilhouette[*itDataSet][*itGeneratedPartition][iANumNn] = obSilhouette.calculate(*itGeneratedPartition, pObjRelationSDN, *itDataSet);
		}
	}
}

// shows the calculated indexes
void Clex::showValidationIndex(){
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
}

// shows the calculated CRIndex
void Clex::showCRIndex(){

	// for each DataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		cout << endl << "CRIndex of " << (*itDataSet)->getNameDataSet() << endl;

		// show the label of each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			cout << "\t" << (*itGeneratedPartition)->getPartitionName();
		}

		// for each real partition
		for(itPartitionOfClex itRealPartition = mapRealPartitions[*itDataSet].begin(); itRealPartition != mapRealPartitions[*itDataSet].end(); itRealPartition++){
			// show the label of each real partition
			cout << endl << (*itRealPartition)->getPartitionName();

			for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
				// show the CRIndex between generated partition and real partition
				cout << "\t" << mapCRIndex[*itDataSet][*itGeneratedPartition][*itRealPartition];
			}
		}	
		cout << endl;
	}
}

// shows the calculated NMIIndex
void Clex::showNMIIndex(){

	// for each DataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		cout << endl << "NMIIndex of " << (*itDataSet)->getNameDataSet() << endl;

		// show label of each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			cout << "\t" << (*itGeneratedPartition)->getPartitionName();
		}

		// for each real partition
		for(itPartitionOfClex itRealPartition = mapRealPartitions[*itDataSet].begin(); itRealPartition != mapRealPartitions[*itDataSet].end(); itRealPartition++){
			// show the label of the real partition
			cout << endl << (*itRealPartition)->getPartitionName();

			for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
				// show the NMIIndex of generated partition and real partition
				cout << "\t" << mapNMIIndex[*itDataSet][*itGeneratedPartition][*itRealPartition];
			}
		}	
		cout << endl;
	}
}

// shows the calculated VIIndex
void Clex::showVIIndex(){

	// for each DataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		cout << endl << "VIIndex of " << (*itDataSet)->getNameDataSet() << endl;

		// show label of each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			cout << "\t" << (*itGeneratedPartition)->getPartitionName();
		}
		
		// for each real partition
		for(itPartitionOfClex itRealPartition = mapRealPartitions[*itDataSet].begin(); itRealPartition != mapRealPartitions[*itDataSet].end(); itRealPartition++){
			// show label of the real partition
			cout << endl << (*itRealPartition)->getPartitionName();

			for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
				// show the VIIndex of generated partition and real partition
				cout << "\t" << mapVIIndex[*itDataSet][*itGeneratedPartition][*itRealPartition];
			}
		}	
		cout << endl;
	}
}

// shows the calculated Connectivity
void Clex::showConnectivity(){

	// for each DataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		cout << endl << "Connectivity of " << (*itDataSet)->getNameDataSet() << endl;
		cout << "\t" << "NumNn" << "\t" << "Value" << endl;
		// show label of each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// for each NumNn
			for(map<int, double>::iterator it = mapConnectivity[*itDataSet][*itGeneratedPartition].begin(); it != mapConnectivity[*itDataSet][*itGeneratedPartition].end(); it++){
			// show the Connectivity of generated partition
				cout << (*itGeneratedPartition)->getPartitionName()	<< "\t" << it->first << "\t" << it->second << endl;
			}
		}
	}
}

// shows the calculated Deviation
void Clex::showDeviation(){

	// for each DataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		cout << endl << "Deviation of " << (*itDataSet)->getNameDataSet() << endl;
		cout << "\t" << "NumNn" << "\t" << "Value" << endl;
		// show label of each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// for each NumNn
			for(map<int, double>::iterator it = mapDeviation[*itDataSet][*itGeneratedPartition].begin(); it != mapDeviation[*itDataSet][*itGeneratedPartition].end(); it++){
			// show the Connectivity of generated partition
				cout << (*itGeneratedPartition)->getPartitionName()	<< "\t" << it->first << "\t" << it->second << endl;
			}
		}
	}
}

// shows the calculated Silhouette
void Clex::showSilhouette(){

	// for each DataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		cout << endl << "Silhouette of " << (*itDataSet)->getNameDataSet() << endl;
		cout << "\t" << "NumNn" << "\t" << "Value" << endl;
		// show label of each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// for each NumNn
			for(map<int, double>::iterator it = mapSilhouette[*itDataSet][*itGeneratedPartition].begin(); it != mapSilhouette[*itDataSet][*itGeneratedPartition].end(); it++){
			// show the Silhouette of generated partition
				cout << (*itGeneratedPartition)->getPartitionName()	<< "\t" << it->first << "\t" << it->second << endl;
			}
		}
	}
}
