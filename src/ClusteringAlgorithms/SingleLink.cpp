/*
 * SingleLink.cpp
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#include "SingleLink.h"

SingleLink::SingleLink() {
	// TODO Auto-generated constructor stub

}

SingleLink::~SingleLink() {
	// TODO Auto-generated destructor stub
}

Partition *SingleLink::run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity){
	cout << "Entrou no run da classe Single Link" << endl;

	SettingsAlgorithmSingleLink *pSettingsAlgorithmSingleLink = dynamic_cast <SettingsAlgorithmSingleLink*> (pASettingsAlgorithms);

	if (pSettingsAlgorithmSingleLink == NULL){
		cout << "erro no cast" << endl;
		//Lançar excecao!
	}
}
