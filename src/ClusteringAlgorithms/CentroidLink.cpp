/*
 * CentroidLink.cpp
 *
 *  Created on: 16/12/2010
  *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#include "CentroidLink.h"

CentroidLink::CentroidLink() {
	// TODO Auto-generated constructor stub

}

CentroidLink::~CentroidLink() {
	// TODO Auto-generated destructor stub
}

Partition *CentroidLink::run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity){
	cout << "Entrou no run da classe centroid link" << endl;
	SettingsAlgorithmCentroidLink *pSettingsAlgorithmCentroidLink = dynamic_cast <SettingsAlgorithmCentroidLink*> (pASettingsAlgorithms);

	if (pSettingsAlgorithmCentroidLink == NULL){
		cout << "erro no cast" << endl;
		//Lançar excecao!
	}
}
