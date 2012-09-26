/*
 * Object.cpp
 *
 *  Created on: Jun 21, 2011
 *      Author: Marcus Vin’cius
 */

#include "Object.h"

void Object::initialize() {
	fill(vectorFeatures.begin(),vectorFeatures.end(), 0);
}

void Object::setId(string sAId) {
	sId = sAId;
}

string Object::getId() {
	return sId;
}

void Object::addFeature(double dAFeature) {
	vectorFeatures.insert(vectorFeatures.end(), dAFeature);
}

void Object::print() {
	cout << sId << "\t";

	for (itFeaturesOfObject it = begin(); it != end(); it++) {
		cout << (*it) << "\t";
	}
	cout << endl;
}

int Object::getNumberOfFeatures() const {
	return vectorFeatures.size();
}

double & Object::operator [](const int iAIndex) {
	return vectorFeatures[iAIndex];
}

double Object::getFeature(const int iAIndex) const {
	return vectorFeatures[iAIndex];
}

Object::itFeaturesOfObject Object::begin() {
	return vectorFeatures.begin();
}

Object::itFeaturesOfObject Object::end() {
	return vectorFeatures.end();
}
