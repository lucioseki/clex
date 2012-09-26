/*
 * SettingsAlgorithmKMeans.h
 *
 *  Created on: 16/12/2010
  *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef SETTINGSALGORITHMKMEANS_H_
#define SETTINGSALGORITHMKMEANS_H_

#include "../SettingsAlgorithm.h"

class SettingsAlgorithmKMeans: public SettingsAlgorithm {
public:
	SettingsAlgorithmKMeans(int iAk);
	virtual ~SettingsAlgorithmKMeans();

	int getK();
	void setK(int iAk);
private:
	int iK;
};

#endif /* SETTINGSALGORITHMKMEANS_H_ */
