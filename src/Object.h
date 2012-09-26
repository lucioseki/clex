/*
 * Object.h
 *
 *  Created on: Jun 21, 2011
 *      Author: Marcus Vin’cius
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/// Represents an Object and its features
/** Represents an Object and its features */
class Object {

	private:
		string sId; ///< Object id
		vector<double> vectorFeatures; ///< Vector of Object features

	public:
		typedef vector<double>::iterator itFeaturesOfObject;

		/** Initializes the vector of features with zeros */
		/** @param Don't have */
		void initialize();

		/** Sets the Object id */
		/** @param Object Id */
		void setId(string sAId);

		/** Gets the Object id */
		/** @param Don't have */
		/** @return Returns the Object id */
		string getId();

		/** Adds in the vector, the feature of the Object */
		/** @param Feature to be added */
		void addFeature(double dAFeature);

		/** Prints the Object */
		/** @param Don't have */
		void print();

		/** Gets the number of features that the Object has */
		/** @param Don't have */
		/** @return Returns the number of features of the Object */
		int getNumberOfFeatures() const;

		/** Accesses the iAIndex-th position of the features' vector */
		/** @param The index of the wished feature */
		/** @return Returns the iAIndex-th feature of the Object */
		double & operator[] (const int iAIndex);

		/** Gets the iAIndex-th position of the features' vector */
		/** @param The index of the wished feature */
		/** @return Returns the iAIndex-th feature of the Object */
		double getFeature(const int iAIndex) const;

		/** Iterator that points to the beginning of the features' vector */
		/** @param Don't have */
		itFeaturesOfObject begin();

		/** Iterator that points to the end of the features' vector */
		/** @param Don't have */
		itFeaturesOfObject end();
};

#endif /* OBJECT_H_ */
