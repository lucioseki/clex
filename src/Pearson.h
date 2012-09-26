/*
 * Pearson.h
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vin’cius
 */

#ifndef PEARSON_H_
#define PEARSON_H_

#include <cmath>

#include "Similarity.h"

/// Represents the calculation of the Pearson correlation coefficient
/** Represents the calculation of the Pearson correlation coefficient */
class Pearson:public Similarity {

	public:
		/** Class constructor */
		/** @param  Don't have */
		Pearson();

		/** Class destructor */
		/** @param  Don't have */
		virtual ~Pearson();

		/** Calculates the Pearson correlation coefficient. */
		/** @param Patterns used to calculate Pearson correlation coeficient */
		/** @return Returns the Pearson correlation coefficient */
		double calculate(const Object &objAObject_1, const Object &objAObject_2);
};

#endif /* PEARSON_H_ */
