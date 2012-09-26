/*
 * SettingsAlgorithmAverageLink.h
 *
 *  Created on: 16/12/2010
  *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef SETTINGSALGORITHMAVERAGELINK_H_
#define SETTINGSALGORITHMAVERAGELINK_H_

#include "../SettingsAlgorithm.h"

class SettingsAlgorithmAverageLink: public SettingsAlgorithm {
public:
	SettingsAlgorithmAverageLink(int iAK);
	virtual ~SettingsAlgorithmAverageLink();

	int getK();
	void setK(int iAk);
private:
	int iK;
};

#endif /* SETTINGSALGORITHMAVERAGELINK_H_ */
