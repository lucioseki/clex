/*
 * SettingsAlgorithmKMeans.cpp
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#include "SettingsAlgorithmKMeans.h"

SettingsAlgorithmKMeans::SettingsAlgorithmKMeans(int iAK) {
	// TODO Auto-generated constructor stub
	iK = iAK;

}

SettingsAlgorithmKMeans::~SettingsAlgorithmKMeans() {
	// TODO Auto-generated destructor stub
}

int SettingsAlgorithmKMeans::getK() {
	// TODO Auto-generated destructor stub
	return iK;
}

void SettingsAlgorithmKMeans::setK(int iAK) {
	// TODO Auto-generated destructor stub
	iK = iAK;
}
