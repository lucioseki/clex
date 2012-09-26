/*
 * DataSet.h
 *
 *  Created on: Jun 21, 2011
 *      Author: Marcus Vin’cius
 */

#ifndef DATASET_H_
#define DATASET_H_

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Object.h"

namespace fs = boost::filesystem;
using namespace boost;
using namespace std;

/// Represents a vector of Objects and the DataSet label
/** Represents a vector of Objects and the DataSet label */
class DataSet {

	private:
		int iNumObjects; ///< Number of Objects in the DataSet
		int iNumFeatures; ///< Number of Object features in the DataSet

		string sPathToDataSet; ///< DataSet path
		string sNameDataSet; ///< DataSet name

		vector <string> vectorDataSetLabel; ///< Vector of the DataSet labels
		vector <Object> vectorObjects; ///< Vector of objects in the DataSet

	public:
		typedef vector <Object>::iterator itObjectsOfDataSet;

		/** Class constructor */
		/** @param  Path and name of the DataSet */
		DataSet(string sPathADataSet, string sANameDataSet);

		/** Tabulates the DataSet */
		/** @param  Don't have */
		void tabulateMappingDataSet();

		/** Gets the number of features that Objects of the DataSet has */
		/** @param Don't have */
		/** @return Returns the number of features of these Objects in the DataSet */
		int getNumberOfFeatures();

		/** Gets the number of Objects that the DataSet has */
		/** @param Don't have */
		/** @return Returns the number of Objects of this DataSet */
		int getNumberOfObjects();

		/** Gets the name of the DataSet */
		/** @param Don't have */
		/** @return Returns the name of the DataSet */
		string getNameDataSet();

		/** Gets the path of the DataSet */
		/** @param Don't have */
		/** @return Returns the path of the DataSet */
		fs::path getPathToDataSet();

		/** Sets the name of the DataSet */
		/** @param DataSet name */
		void setNameDataSet(string sANameDataSet);

		/** Prints the DataSet */
		/** @param Don't have */
		void print();

		//For tests
		Object& getObject(int position);

		/** Iterator that point the beginning of the Objects' vector */
		/** @param Don't have */
		itObjectsOfDataSet begin();

		/** Iterator that points to the end of the Objects' vector */
		/** @param Don't have */
		itObjectsOfDataSet end();

		/** Iterator that points to the object called sAId of the Objects' vector */
		/** @param Don't have */
		itObjectsOfDataSet find(string sAId);
};

#endif /* DATASET_H_ */

