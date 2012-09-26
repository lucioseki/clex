/*
 * Pearson.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vin’cius
 */

#include "Pearson.h"

Pearson::Pearson() {
	// Pearson is a correlation measure (similarity)
	similarity = true;
}

Pearson::~Pearson() {}

double Pearson::calculate(const Object &objAObject_1, const Object &objAObject_2) {

	int i, iSize;
	double dCorrelation = 0;
	double dAverage1 = 0, dAverage2 = 0, dS1 = 0, dS2 = 0, dS3 = 0;

	iSize = objAObject_1.getNumberOfFeatures();

	//TODO Certificates if both vector of features have the same size
	if (iSize != objAObject_2.getNumberOfFeatures()) {
		cout << "Patterns should have the same size." << endl;
		return -1;
	}

	// Calculates the average of each pattern
	for (int i = 0; i < objAObject_1.getNumberOfFeatures(); i++){
		dAverage1 += objAObject_1.getFeature(i);
		dAverage2 += objAObject_2.getFeature(i);
	}

	dAverage1 /= iSize;
	dAverage2 /= iSize;

	for (i = 0; i < iSize; i++) {
		dS1 += (objAObject_1.getFeature(i) - dAverage1) * (objAObject_2.getFeature(i) - dAverage2);
		dS2 += (objAObject_1.getFeature(i) - dAverage1) * (objAObject_1.getFeature(i) - dAverage1);
		dS3 += (objAObject_2.getFeature(i) - dAverage2) * (objAObject_2.getFeature(i) - dAverage2);
	}

	if (dS2 * dS3 == 0) {
		dCorrelation = 0;
	} else {
		dCorrelation = abs(dS1 / (sqrt(dS2 * dS3)));
	}

	return dCorrelation;
}
