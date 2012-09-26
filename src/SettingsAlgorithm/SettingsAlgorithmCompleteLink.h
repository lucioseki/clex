/*
 * SettingsAlgorithmCompleteLink.h
 *
 *  Created on: 16/12/2010
 *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef SETTINGSALGORITHMCOMPLETELINK_H_
#define SETTINGSALGORITHMCOMPLETELINK_H_

#include "../SettingsAlgorithm.h"

class SettingsAlgorithmCompleteLink: public SettingsAlgorithm {
public:
	SettingsAlgorithmCompleteLink(int iAK);
	virtual ~SettingsAlgorithmCompleteLink();

	int getK();
	void setK(int iAk);
private:
	int iK;
};

#endif /* SETTINGSALGORITHMCOMPLETELINK_H_ */
