/*
 * SettingsAlgorithmCentroidLink.h
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef SETTINGSALGORITHMCENTROIDLINK_H_
#define SETTINGSALGORITHMCENTROIDLINK_H_

#include "../SettingsAlgorithm.h"

class SettingsAlgorithmCentroidLink: public SettingsAlgorithm {
public:
	SettingsAlgorithmCentroidLink(int iAK);
	virtual ~SettingsAlgorithmCentroidLink();

	int getK();
	void setK(int iAk);
private:
	int iK;
};

#endif /* SETTINGSALGORITHMCENTROIDLINK_H_ */
