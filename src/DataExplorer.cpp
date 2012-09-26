/*
 * DataExplorer.cpp
 *
 *  Created on: Dec 19, 2011
 *      Author: Marcus
 */

#include "DataExplorer.h"

DataExplorer::DataExplorer(string sAPathToPopulation, int iANumNn, DataSet *pADataSet, Similarity *pASimilarity, vector< pair< ClusteringAlgorithms*, SettingsAlgorithm* > > vectorAAlgorithms, vector< ValidationIndex* > vectorAValidationIndexes) {
	pathPopulation = sAPathToPopulation;
	iNumNn = iANumNn;
	pDataSet = pADataSet;
	pSimilarity = pASimilarity;
	vectorAlgorithms = vectorAAlgorithms;
	vectorValidationIndexes = vectorAValidationIndexes;

	pRelationSDN = new RelationSDN(pSimilarity, pDataSet, iANumNn);

	vectorPartitions.clear();
	vectorPartitionsK2.clear();
	vectorPopulation.clear();
}

void DataExplorer::run() {
	generatePartitions();

	for (unsigned int i = 0; i < vectorPartitions.size(); i++)
		breakPartition(vectorPartitions[i]);

	for (unsigned int i = 0; i < vectorPartitionsK2.size(); i++)
		evaluatePartition(vectorPartitionsK2[i]);
}

void DataExplorer::generatePartitions() {
	for (unsigned int i = 0; i < vectorAlgorithms.size(); i++)
		vectorPartitions.insert(vectorPartitions.end(), (vectorAlgorithms[i].first)->run(vectorAlgorithms[i].second, pDataSet, pSimilarity));
}

void DataExplorer::breakPartition(Partition *pAPartition) {
	string sNamePartitionK2;

	if (!exists(pathPopulation))
		fs::create_directory(pathPopulation);

	for (Partition::itClustersOfPartition it = pAPartition->begin(); it != pAPartition->end(); it++){
		int iCurrentClusterLabel = it->getLabel();

		sNamePartitionK2 = fs::basename(pAPartition->getPartitionName()) + "_cluster" +
						   boost::lexical_cast<std::string>(distance (pAPartition->begin(), it) + 1) + ".clu";

		Partition *pTempPartition = new Partition(pDataSet, pathPopulation.string(), sNamePartitionK2);
		Cluster *pTempCluster1 = new Cluster(iCurrentClusterLabel);
		Cluster *pTempCluster2 = new Cluster(iCurrentClusterLabel + 1);

		for (DataSet::itObjectsOfDataSet it2 = pDataSet->begin(); it2 != pDataSet->end(); it2++) {
			if(pAPartition->getClusterOf(it2) == it) {
				pTempCluster1->addObject(it2);
			} else {
				pTempCluster2->addObject(it2);
			}
		}

		pTempPartition->addCluster(pTempCluster1);
		pTempPartition->addCluster(pTempCluster2);

		pTempPartition->calculateCentroid();

		vectorPartitionsK2.insert(vectorPartitionsK2.end(), pTempPartition);
	}
}

void DataExplorer::evaluatePartition(Partition *pAPartition) {
	vector<double> vectorObjectivesValues;
	vectorObjectivesValues.clear();

	for (unsigned int j = 0; j < vectorValidationIndexes.size(); j++)
		vectorObjectivesValues[j] = vectorValidationIndexes[j]->calculate(pAPartition, pRelationSDN, pDataSet);

	vectorPopulation.insert(vectorPopulation.end(), make_pair(pAPartition, vectorObjectivesValues));
}


void DataExplorer::orCombination(Partition *pAPartition1, Partition *pAPartition2) {
	string sNamePartitionK2;

	Partition::itClustersOfPartition itMainCluster1 = pAPartition1->begin();
	Partition::itClustersOfPartition itMainCluster2 = pAPartition2->begin();

	sNamePartitionK2 = "Combination_cluster" + boost::lexical_cast<std::string>(itMainCluster1->getLabel()) + "or" +
					   boost::lexical_cast<std::string>(itMainCluster2->getLabel()) + ".clu";

	Partition *pTempPartition = new Partition(pDataSet, pathPopulation.string(), sNamePartitionK2);

	//TODO QUAL LABEL COLOCAR?
	Cluster *pTempCluster1 = new Cluster(0);
	Cluster *pTempCluster2 = new Cluster(1);

	for (DataSet::itObjectsOfDataSet it2 = pDataSet->begin(); it2 != pDataSet->end(); it2++) {
		if(pAPartition1->getClusterOf(it2) == itMainCluster1 ||
		   pAPartition2->getClusterOf(it2) == itMainCluster2) {
			pTempCluster1->addObject(it2);
		} else {
			pTempCluster2->addObject(it2);
		}
	}

		pTempPartition->addCluster(pTempCluster1);
		pTempPartition->addCluster(pTempCluster2);

		pTempPartition->calculateCentroid();

		evaluatePartition(pTempPartition);
}

void DataExplorer::diffCombination(Partition *pAPartition1, Partition *pAPartition2) {
	string sNamePartitionK2;

	Partition::itClustersOfPartition itMainCluster1 = pAPartition1->begin();
	Partition::itClustersOfPartition itMainCluster2 = pAPartition2->begin();

	sNamePartitionK2 = "Combination_cluster" + boost::lexical_cast<std::string>(itMainCluster1->getLabel()) + "diff" +
					   boost::lexical_cast<std::string>(itMainCluster2->getLabel()) + ".clu";

	Partition *pTempPartition = new Partition(pDataSet, pathPopulation.string(), sNamePartitionK2);

	//TODO QUAL LABEL COLOCAR?
	Cluster *pTempCluster1 = new Cluster(0);
	Cluster *pTempCluster2 = new Cluster(1);

	for (DataSet::itObjectsOfDataSet it2 = pDataSet->begin(); it2 != pDataSet->end(); it2++) {
		if(pAPartition1->getClusterOf(it2) == itMainCluster1 &&
		   pAPartition2->getClusterOf(it2) != itMainCluster2) {
			pTempCluster1->addObject(it2);
		} else {
			pTempCluster2->addObject(it2);
		}
	}

		pTempPartition->addCluster(pTempCluster1);
		pTempPartition->addCluster(pTempCluster2);

		pTempPartition->calculateCentroid();

		evaluatePartition(pTempPartition);
}

void DataExplorer::intersectionCombination(Partition *pAPartition1, Partition *pAPartition2) {
	string sNamePartitionK2;

	Partition::itClustersOfPartition itMainCluster1 = pAPartition1->begin();
	Partition::itClustersOfPartition itMainCluster2 = pAPartition2->begin();

	sNamePartitionK2 = "Combination_cluster" + boost::lexical_cast<std::string>(itMainCluster1->getLabel()) + "inter" +
					   boost::lexical_cast<std::string>(itMainCluster2->getLabel()) + ".clu";

	Partition *pTempPartition = new Partition(pDataSet, pathPopulation.string(), sNamePartitionK2);

	//TODO QUAL LABEL COLOCAR?
	Cluster *pTempCluster1 = new Cluster(0);
	Cluster *pTempCluster2 = new Cluster(1);

	for (DataSet::itObjectsOfDataSet it2 = pDataSet->begin(); it2 != pDataSet->end(); it2++) {
		if(pAPartition1->getClusterOf(it2) == itMainCluster1 &&
		   pAPartition2->getClusterOf(it2) == itMainCluster2) {
			pTempCluster1->addObject(it2);
		} else {
			pTempCluster2->addObject(it2);
		}
	}

		pTempPartition->addCluster(pTempCluster1);
		pTempPartition->addCluster(pTempCluster2);

		pTempPartition->calculateCentroid();

		evaluatePartition(pTempPartition);
}

int DataExplorer::loadPartitionsK2() {
	vector<string> files;
	string sPath;
	Partition *p;
	DIR *dp;
	struct dirent *dirp;

	//Refazer!!----
	if((dp  = opendir(pathPopulation.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << pathPopulation.string() << endl;
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL)
		files.push_back(string(dirp->d_name));

	closedir(dp);
	//------------

	//Load Partitions
	for(unsigned int i = 0; i < files.size(); i++) {
		sPath = pathPopulation.string() + "/" + files[i];
		p = new Partition(pDataSet, pathPopulation.string(), files[i]);

		p->loadPartition();
		//TODO preciso fazer as avaliações da partição para colocá-la na população, certo?
		delete(p);
	}
	return 0;
}
