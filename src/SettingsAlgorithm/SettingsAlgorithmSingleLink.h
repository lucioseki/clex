/*
 * SettingsAlgorithmSingleLink.h
 *
 *  Created on: 16/12/2010
  *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef SETTINGSALGORITHMSINGLELINK_H_
#define SETTINGSALGORITHMSINGLELINK_H_

#include "../SettingsAlgorithm.h"

class SettingsAlgorithmSingleLink: public SettingsAlgorithm {
public:
	SettingsAlgorithmSingleLink(int iAk);
	virtual ~SettingsAlgorithmSingleLink();

	int getK();
	void setK(int iAk);
private:
	int iK;
};

#endif /* SETTINGSALGORITHMSINGLELINK_H_ */
