/*
 * Cluster.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#include "Cluster.h"

using namespace boost;
using namespace std;

Cluster::Cluster(int iAClusterLabel) {
	iLabel = iAClusterLabel;
	objCentroid.initialize();
}

void Cluster::addObject(DataSet::itObjectsOfDataSet objAObject) {
	vectorObjects.push_back(objAObject);
}

void Cluster::calculateCentroid() {
	double dSum = 0;
	int iNumFeatures = vectorObjects[0]->getNumberOfFeatures();

	string sIdCentroid = "centroid" + boost::lexical_cast<string>(iLabel);
	objCentroid.setId(sIdCentroid);
	for (int i = 0; i < iNumFeatures; i++) {
		for (itObjectsOfCluster it = vectorObjects.begin(); it != vectorObjects.end(); it++){
			dSum += (*it)->getFeature(i);
		}
		objCentroid.addFeature(dSum/getNumberOfObjects());
	}
}

int Cluster::getLabel() {
	return iLabel;
}

int Cluster::getNumberOfObjects() {
	return vectorObjects.size();
}

Object *Cluster::getCentroid(){
	return &objCentroid;
}

Cluster::itObjectsOfCluster Cluster::begin() {
	return vectorObjects.begin();
}

Cluster::itObjectsOfCluster Cluster::end() {
	return vectorObjects.end();
}

Cluster::itObjectsOfCluster Cluster::find(DataSet::itObjectsOfDataSet objAObject){
	Cluster::itObjectsOfCluster itObj;
	for (itObj = begin(); itObj != end() && (*itObj) != objAObject; itObj++);
	return itObj;
}

void Cluster::removeObject(DataSet::itObjectsOfDataSet objAObject){
	itObjectsOfCluster itObj = find(objAObject);

	if ( itObj != vectorObjects.end()){ //found
		vectorObjects.erase(itObj);
	}
}

void Cluster::print(){
	cout << "Cluster Label: " << iLabel << endl;
	cout << "Cluster Objects:" << endl;
	for (itObjectsOfCluster it = begin(); it != end(); it++){
		(*it)->print();
		cout << endl;
	}
	cout << "Cluster Centroid: " << endl;
	objCentroid.print();
	cout << endl;
}

//TODO ACRESCIDO
/*Cluster::Cluster(int iAClusterLabel, int iANumberObjectsOfCluster) {
	iLabel = iAClusterLabel;
	iNumberObjectsOfCluster = iANumberObjectsOfCluster;
	vectorCentroid.initialize();
}*/

DataSet::itObjectsOfDataSet Cluster::getObject(int iAIndex) {
	return vectorObjects[iAIndex];
}
