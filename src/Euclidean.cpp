/*
 * Euclidean.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vin’cius
 */

#include "Euclidean.h"

Euclidean::Euclidean() {
	// Euclidean is a distance measure (dissimilarity)
	similarity = false;
}

Euclidean::~Euclidean() {}

double Euclidean::calculate(const Object &objAObject_1, const Object &objAObject_2){

	double dDistance = 0;

	for (int i = 0; i < objAObject_1.getNumberOfFeatures(); i++) {
		dDistance += (objAObject_1.getFeature(i) - objAObject_2.getFeature(i)) * (objAObject_1.getFeature(i) - objAObject_2.getFeature(i));
	}

	dDistance = sqrt(dDistance);

	return dDistance;
}



