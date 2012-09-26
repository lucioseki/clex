/*
 * CompleteLink.cpp
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#include "CompleteLink.h"

CompleteLink::CompleteLink() {
	// TODO Auto-generated constructor stub

}

CompleteLink::~CompleteLink() {
	// TODO Auto-generated destructor stub
}

Partition *CompleteLink::run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity){
	cout << "Entrou no run da classe complete link" << endl;

	SettingsAlgorithmCompleteLink *pSettingsAlgorithmCompleteLink = dynamic_cast <SettingsAlgorithmCompleteLink*> (pASettingsAlgorithms);

	if (pSettingsAlgorithmCompleteLink == NULL){
		cout << "erro no cast" << endl;
		//Lançar excecao!
	}
}
