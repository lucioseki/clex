/*
 * Partition.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#ifndef PARTITION_H_
#define PARTITION_H_


#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

#include "Cluster.h"
#include "DataSet.h"

namespace fs = boost::filesystem;
using namespace std;

/// Responsible by manage the Partition file into the memory.
/** Responsible by manage the Partition file into the memory. */
class Partition {

	private:
		int iNumObjects; ///< The number of Objects existing in the Partition
		int iNumClusters; ///< The number of Clusters existing in the Partition
		string sPathPartition; ///< Partition path
		string sNamePartition; ///< Partition name

		vector<Cluster> vectorObjCluster; ///< Vector of Clusters

		fs::path pathPartition; ///< The path to the Partition in the computer
		DataSet *pObjDataSet;

	public:
		typedef vector<Cluster>::iterator itClustersOfPartition;


		/** Class constructor: creates a Partition by loading it from a file */
		/** @param  Path and name of the Partition */
		Partition(DataSet *pAObjDataSet, string sAPathPartition, string sANamePartition);

		/** Class constructor: creates a Partition with a given number of clusters by randomly assigning the objects to the clusters */
		/** @param  Path and name of the Partition and number of Clusters */
		Partition(DataSet *pAObjDataSet, string sAPathPartition, string sANamePartition, int iANumberOfClusters);

		/** Class destructor */
		/** @param  Don't have */
		virtual ~Partition();

		/** Charges to the Partition in the memory, passing in the argument the path to load the Partition in memory, passing as argument the path to the Partition */
		/** @param Don't have */
		void loadPartition();

		/** Calculates the centroid of the Cluster */
		/** @param Don't have */
		/** @see calculateCentroid(DataSet &obADataSet) */
		void calculateCentroid();

		/** Prints the labels of the Partition */
		/** @param Don't have */
		void print();

		itClustersOfPartition findCluster(int iALabel);

		//VER COM A PROFESSORA
		/** Writes the Partition in disk, passing in the argument the path where the user want to save  */
		/** @param  pathSaveIn */
		/** @return Don't have. */
		void writePartition(string sAFolder, string sANamePartition);

		/** Returns the number of Clusters existing on the Partition */
		/** @param Don't have */
		/** @return iNumClusters */
		/** @see loadPartition(fs::path pathAPartition), iNumClusters */
		int getNumClusters();

		/** Returns the number of Objects existing on the Partition */
		/** @param Don't have */
		/** @see loadPartition(fs::path pathAPartition) */
		int getNumObjects();

		//ACRESCIDO
		string getPartitionName();
		fs::path getPathPartition();
		DataSet* getDataSet();
		void addCluster(Cluster *pACluster);
		//----------

		itClustersOfPartition getClusterOf(DataSet::itObjectsOfDataSet objAObject);

		/** Returns the centroid of Cluster*/
		/** @param Cluster Label */
		/** @return vector<double> */
		Object* getCentroidInCluster(int iAClusterLabel);

		itClustersOfPartition begin();

		itClustersOfPartition end();
};

#endif /* PARTITION_H_ */
