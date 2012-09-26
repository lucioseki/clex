/*
 * SettingsAlgorithm.h
 *
 *  Created on: 16/12/2010
  *      Author: Gustavo Henrique Rodrigues Pinto Tomas
 */

#ifndef SETTINGSALGORITHM_H_
#define SETTINGSALGORITHM_H_

using namespace std;

/**Abstract class with two calculate methods,abstract class responsible for
 * the parameters needed for each clustering algorithm */
class SettingsAlgorithm {
	public:
		SettingsAlgorithm();
		virtual ~SettingsAlgorithm();
};

#endif /* SETTINGSALGORITHM_H_ */
