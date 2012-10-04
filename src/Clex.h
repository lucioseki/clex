#ifndef CLEX_H
#define CLEX_H

#include "Partition.h"
#include "DataSet.h"
#include "Similarity.h"
#include "RelationSDN.h"
#include "ValidationIndex.h"

#include <map>
#include<set>

class Clex{

	private:
		Similarity *pSimilarity; //< pointer to the measure of Similarity

		vector<DataSet*> vDataSet; //< vector containing pointers to the DataSets

		set<string> sValidationIndex; //< set containing a vector of validation indexes to be used

		map<DataSet*, vector<Partition*> > mapRealPartitions; //< map containing a vector of real partitions for each DataSet

		map<DataSet*, vector<Partition*> > mapGeneratedPartitions; //< map containing a vector of calculated partitions for each DataSet

		map<DataSet*, map<Partition*, map<Partition*, double > > > mapCRIndex; //< map that contains the CRIndex value for each calculated partition, for each real partition, for each DataSet

		map<DataSet*, map<Partition*, map<Partition*, double > > > mapNMIIndex; //< map that contains the NMIIndex value for each calculated partition, for each real partition, for each DataSet

		map<DataSet*, map<Partition*, map<Partition*, double > > > mapVIIndex; //< map that contains the VIIndex value for each calculated partition, for each real partition, for each DataSet

		map<DataSet*, map<Partition*, map<int, double > > > mapConnectivity; //< map that contains the Connectivity value for a given number of Neighbours, for each calculated partition for each DataSet

		map<DataSet*, map<Partition*, map<int, double > > > mapDeviation; //< map that contains the Connectivity value for a given number of Neighbours, for each calculated partition for each DataSet

		map<DataSet*, map<Partition*, map<int, double > > > mapSilhouette; //< map that contains the Silhouette value for a given number of Neighbours, for each calculated partition for each DataSet

		map<Similarity*, map<DataSet*, map<int, RelationSDN* > > > mapRelationSDN; //< map that contains the RelationSDN for each combination of Similarity, DataSet and NumNn
	public:
		typedef vector<DataSet*>::iterator itDataSetOfClex;
		typedef vector<Partition*>::iterator itPartitionOfClex;

		// sets the similarity measure
		void setSimilarity(Similarity* s);

		// sets the DataSets
		// @param a vector of paths for each DataSet
		// instanciates a DataSet for each path and inserts in the vDataSet
		void setDataSet(vector<pair<string, string> > vASDataSet);

		// sets the Validation Indexes to be used
		// @param a vector of names of the indexes
		void setValidationIndex(vector<string> vASValidationIndex);

		// creates RelationSDN for each combination of Similarity, DataSet and NumNn
		void createRelationSDN(int iANumNn);

		// sets a Real Partition for a DataSet
		// @param the position of the DataSet in the vDataSet
		// and a vector of paths for each Partition
		void setRealPartition(int iADataSet, vector<pair<string, string> > vASPartition);

		// sets a Generated Partition for a DataSet
		// @param the position of the DataSet in the vDataSet
		// and a vector of paths for each Partition
		void setGeneratedPartition(int iADataSet, vector<pair<string, string> > vASPartition);

		// calculates the validation Indexes
		void calculateValidationIndex();

		// calculates the CRIndex for each generated Partition with each real Partition
		void calculateCRIndex();

		// calculates the NMIIndex for each generated Partition with each real Partition
		void calculateNMIIndex();

		// calculates the VIIndex for each generated Partition with each real Partition
		void calculateVIIndex();

		// calculates the Connectivity for each generated Partition
		// @param number of Nearest neighbours
		void calculateConnectivity(int);

		// calculates the Deviation for each generated Partition
		// @param number of Nearest neighbours
		void calculateDeviation(int);

		// calculates the Silhouette for each generated Partition
		// @param number of Nearest neighbours
		void calculateSilhouette(int);

		// shows the calculated Indexes
		void showValidationIndex();

		// shows the calculated CRIndex
		void showCRIndex();

		// shows the calculated VIIndex
		void showVIIndex();

		// shows the calculated NMIIndex
		void showNMIIndex();

		// shows the calculated Connectivity
		void showConnectivity();

		// shows the calculated Deviation 
		void showDeviation();

		// shows the calculated Deviation 
		void showSilhouette();
};
#endif
