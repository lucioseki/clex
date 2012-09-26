/*
 * Cluster.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <sstream>
#include <time.h>

#include "DataSet.h"

/// Represents a group of objects that were considered similar according some clustering algorithm
/** Represents a group of objects that were considered similar according some clustering algorithm */
class Cluster {
	private:
		int iLabel; ///< Label of the cluster
		Object objCentroid; ///< A object that will receive the centroids of each cluster
		vector<DataSet::itObjectsOfDataSet> vectorObjects; ///< Vector that will receive the iterators of object of the dataset

		//TODO int iNumberObjectsOfCluster;//PRECISA?

	public:
		typedef vector<DataSet::itObjectsOfDataSet>::iterator itObjectsOfCluster;

		/** Class constructor */
		/** @param  Cluster label */
		Cluster(int iAClusterLabel);

		/** Adds the object in the vector of objects */
		/** @param  string sID */
		void addObject(DataSet::itObjectsOfDataSet objAObject);

		/** Calculates the centroid of the cluster */
		/** @param  Don't have */
		void calculateCentroid();

		/** Gets the cluster label */
		/** @param Don't have  */
		/** @return Returns the label of the cluster */
		int getLabel();

		/** Gets the number of objects that the cluster has */
		/** @param  Don't have.*/
		/** @return Returns the size of the vectorObjects */
		int getNumberOfObjects();

		/** Returns the begin of the objects vector */
		itObjectsOfCluster begin();

		/** Returns the end of the objects vector */
		itObjectsOfCluster end();

		/** Gets the centroids of the cluster */
		/** @param Don't have  */
		/** @return Returns the centroids of the cluster */
		Object* getCentroid();

		/** Removes an object of the cluster */
		/** @param String object  */
		void removeObject(DataSet::itObjectsOfDataSet objAObject);

		/** Prints the cluster */
		/** @param Don't have */
		void print();

		/** Return the object with the label sAId*/
		/** @param  */
		/** @return  */
		itObjectsOfCluster find(DataSet::itObjectsOfDataSet objAObject);

		//TODO ACRESCIDO
		//Cluster(int iAClusterLabel, int iANumberObjectsOfCluster);

		DataSet::itObjectsOfDataSet getObject(int iAIndex);
};

#endif /* CLUSTER_H_ */
