/*
 * Partition.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#include "Partition.h"

using namespace boost;
using namespace std;

Partition::Partition(DataSet *pAObjDataSet, string sAPathPartition, string sANamePartition) {
	sPathPartition = sAPathPartition;
	sNamePartition = sANamePartition;
	pObjDataSet = pAObjDataSet;

	pathPartition = sPathPartition + sNamePartition;
	loadPartition();
	cout << "pathPartition>> " << pathPartition << endl;
}

Partition::Partition(DataSet *pAObjDataSet, string sAPathPartition, string sANamePartition, int iANumberOfClusters){
	iNumClusters = iANumberOfClusters;
	sPathPartition = sAPathPartition;
	sNamePartition = sANamePartition;
	pObjDataSet = pAObjDataSet;

	pathPartition = sPathPartition + sNamePartition;

	for(int i = 0; i < iANumberOfClusters; i++){
		Cluster *newCluster = new Cluster(i);
		vectorObjCluster.push_back(*newCluster);
		delete newCluster;
	}

//TODO Ver com professora
// # Corrigir para que todos os clusters criados tenham pelo menos 1 objeto
	for (DataSet::itObjectsOfDataSet it = pObjDataSet->begin(); it != pObjDataSet->end(); it++){
		int iCluster = rand() % iNumClusters + 1; // numero entre 1 e iNumClusters
		vectorObjCluster[iCluster].addObject(it);
	}
	for (itClustersOfPartition it = vectorObjCluster.begin(); it != vectorObjCluster.end(); it++){
		it->calculateCentroid();
	}

	iNumObjects = pObjDataSet->getNumberOfObjects();

	cout << "pathPartition>> " << pathPartition << endl;
}

Partition::~Partition() {}

void Partition::loadPartition() {
	Cluster *pObjCluster;
	string sTemp;
	string sObject;
	istringstream instream;
	int iCluster;
	unsigned int i;

	iNumObjects = 0;
	ifstream in(pathPartition.c_str());

	// define what gonna be the tokenizer character
	char_separator<char> sep("\t");

	while (getline(in, sTemp)) {

		// tokenize the string sTemp that's the line read in the file informed in 'pathAPartition'
		tokenizer<char_separator<char> > tokens(sTemp, sep);

		for (tokenizer<char_separator<char> >::iterator itTokens = tokens.begin(); itTokens != tokens.end(); ++itTokens) {

			// putting the ID of the element in the memory
			// mapVector[sIndexLine].push_back(dNumber);
			sObject = *itTokens;
			++itTokens;

			(istringstream(*itTokens) >> iCluster);

			// check if the cluster already exists
			i = 0;
			while (i < vectorObjCluster.size() && vectorObjCluster[i].getLabel() != iCluster) {
				i++;
			}

			if (i == vectorObjCluster.size()) {
			// create the new cluster if it does not exist
				pObjCluster = new Cluster(iCluster);
				pObjCluster->addObject(pObjDataSet->find(sObject));
				// # ver se push_back faz copia, sen‹o precisa tirar o delete
				vectorObjCluster.push_back(*pObjCluster);
				delete pObjCluster;
			} else
				vectorObjCluster[i].addObject(pObjDataSet->find(sObject));
			iNumObjects++;
		}
	}

	iNumClusters =  vectorObjCluster.size();
}

void Partition::calculateCentroid() {

	for (Partition::itClustersOfPartition it = vectorObjCluster.begin(); it != vectorObjCluster.end(); it++){
		(*it).calculateCentroid();
	}
}

Object* Partition::getCentroidInCluster(int iAClusterLabel){
	itClustersOfPartition it = findCluster(iAClusterLabel);
	if (it != end())
		return (*it).getCentroid();
	return NULL;
}

Partition::itClustersOfPartition Partition::findCluster(int iALabel){
	itClustersOfPartition it;
	for (it = vectorObjCluster.begin(); (*it).getLabel() != iALabel && it != vectorObjCluster.end(); it++);
	return it;
}

Partition::itClustersOfPartition Partition::getClusterOf(DataSet::itObjectsOfDataSet objAObject){
	itClustersOfPartition it;
	for (it = vectorObjCluster.begin(); !((*it).find(objAObject) != (*it).end())  && it != vectorObjCluster.end(); it++);
	return it;
}

//TODO ver com a professora
void Partition::writePartition(string sAFolder, string sANamePartition) {

	string sFolder;
	string sNamePartition;

	cout << "Precisa rever implementa‹o" << endl;
/*	cout << ">> ";
	cin >> sFolder;

	// # ficando o caminho para a nova pasta do tipo da partition
	cout << "New folder in : " << sPathPartition + sFolder << endl;

	//fs::path pathPartition(sFolder);

	// # criando o diret—rio especificado pelo usu‡rio
	fs::create_directories(sPathPartition+sFolder);

	cout << "Inform the name of the file that gonna be your partition" << endl;
	cout << ">> ";
	cin >> sNamePartition;

	string sPath = sPathPartition + sFolder + "/" + sNamePartition + ".clu";

	cout << "sPath no partition >> " << sPath;

	ofstream out(sPath.c_str());

	map <string, int>::iterator itMapObjects;

	for(itMapObjects = mapObjects.begin(); itMapObjects != mapObjects.end(); ++itMapObjects){
		out << itMapObjects->first << "\t" << itMapObjects->second << "\n";
	}

	out.close();
	*/
}


int Partition::getNumClusters() {
	return iNumClusters;
}

int Partition::getNumObjects() {
	return iNumObjects;
}

//TODO ACRESCIDO

string Partition::getPartitionName() {
	return sNamePartition;
}

fs::path Partition::getPathPartition() {
	return pathPartition;
}


DataSet* Partition::getDataSet() {
	return pObjDataSet;
}

void Partition::addCluster(Cluster *pACluster) {
	vectorObjCluster.insert(vectorObjCluster.end(), *pACluster);
}
//-----------

void Partition::print(){

	for (itClustersOfPartition it = begin(); it != end(); ++ it){
		it->print();
	}
}

Partition::itClustersOfPartition Partition::begin() {
	return vectorObjCluster.begin();
}

Partition::itClustersOfPartition Partition::end() {
	return vectorObjCluster.end();
}





