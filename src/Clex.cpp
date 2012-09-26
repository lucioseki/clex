#include "Clex.h"
#include "ValidationIndex.h"
#include "ValidationIndex/CRIndex.h"
#include "ValidationIndex/NMIIndex.h"
#include "ValidationIndex/VIIndex.h"
#include "ValidationIndex/Connectivity.h"
#include <iostream>
using namespace std;

// sets the similarity measure
void Clex::setSimilarity(Similarity* s){
	pSimilarity = s;
}

// sets the DataSet vector
void Clex::setDataSet(DataSet *pAVDataSet){
	vDataSet.push_back(pAVDataSet);
}

// sets the vector of real partitions for a DataSet
void Clex::setRealPartition(DataSet* pADataSet, Partition *pAVPartition){
	mapRealPartitions[pADataSet].push_back(pAVPartition);
}

// sets the vector of generated partitions for a DataSet
void Clex::setGeneratedPartition(DataSet* pADataSet, Partition *pAVPartition){
	mapGeneratedPartitions[pADataSet].push_back(pAVPartition);
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

// calculates the Connectivity for each generated Partition with each real Partition
void Clex::calculateConnectivity(int iANumNn){
	RelationSDN *pObjRelationSDN;
	Connectivity obConnectivity;

	// for each DataSet in vDataSet
	for(itDataSetOfClex itDataSet = vDataSet.begin(); itDataSet != vDataSet.end(); itDataSet++){
		// for each generated partition
		for(itPartitionOfClex itGeneratedPartition = mapGeneratedPartitions[*itDataSet].begin(); itGeneratedPartition != mapGeneratedPartitions[*itDataSet].end(); itGeneratedPartition++){
			// calculate Connectivity of generated partition
			// and save on mapConnectivity
			pObjRelationSDN = new RelationSDN(pSimilarity, *itDataSet, iANumNn);
			mapConnectivity[*itDataSet][*itGeneratedPartition] = make_pair(iANumNn, obConnectivity.calculate(*itGeneratedPartition, pObjRelationSDN, *itDataSet));
		}	
	}
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
			// show the Connectivity of generated partition
			cout << (*itGeneratedPartition)->getPartitionName()	<< "\t" << mapConnectivity[*itDataSet][*itGeneratedPartition].first << "\t" << mapConnectivity[*itDataSet][*itGeneratedPartition].second << endl;
		}
	}
}
