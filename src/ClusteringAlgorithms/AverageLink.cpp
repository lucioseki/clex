/*
 * AverageLink.cpp
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#include "AverageLink.h"

AverageLink::AverageLink() {
	// TODO Auto-generated constructor stub

}

AverageLink::~AverageLink() {
	// TODO Auto-generated destructor stub
}

Partition *AverageLink::run(SettingsAlgorithm *pASettingsAlgorithms, DataSet *pADataSet, Similarity *pASimilarity){
	cout << "Entrou no run da classe average link" << endl;
	SettingsAlgorithmAverageLink *pSettingsAlgorithmAverageLink = dynamic_cast <SettingsAlgorithmAverageLink*> (pASettingsAlgorithms);

	if (pSettingsAlgorithmAverageLink == NULL){
		cout << "erro no cast" << endl;
		//Lançar excecao!
	}

}
