#ifndef CLEX_H
#define CLEX_H

#include "Partition.h"
#include "DataSet.h"
#include "Similarity.h"

#include <map>

class Clex{

	private:
		Similarity *pSimilarity; //< pointer to the measure of Similarity

		vector<DataSet*> vDataSet; //< vector containing pointers to the DataSets

		map<DataSet*, vector<Partition*> > mapRealPartitions; //< map containing a vector of real partitions for each DataSet

		map<DataSet*, vector<Partition*> > mapGeneratedPartitions; //< map containing a vector of calculated partitions for each DataSet

		map<DataSet*, map<Partition*, map<Partition*, double > > > mapCRIndex; //< map that contains the CRIndex value for each calculated partition, for each real partition, for each DataSet
		map<DataSet*, map<Partition*, map<Partition*, double > > > mapNMIIndex; //< map that contains the NMIIndex value for each calculated partition, for each real partition, for each DataSet
		map<DataSet*, map<Partition*, map<Partition*, double > > > mapVIIndex; //< map that contains the VIIndex value for each calculated partition, for each real partition, for each DataSet

	public:
		typedef vector<DataSet*>::iterator itDataSetOfClex;
		typedef vector<Partition*>::iterator itPartitionOfClex;

		// sets the similarity measure
		void setSimilarity(Similarity* s);

		// inserts a DataSet
		void setDataSet(DataSet *pADataSet);
		// passar so pointer pra dataset, por dentro guarda no vector
		// idem pra partitions

		// sets a Real Partition for a DataSet
		void setRealPartition(DataSet* pADataSet, Partition *pAVPartition);

		// sets a Generated Partition for a DataSet
		void setGeneratedPartition(DataSet* pADataSet, Partition *pAVPartition);

		// calculates the CRIndex for each generated Partition with each real Partition
		void calculateCRIndex();

		// calculates the NMIIndex for each generated Partition with each real Partition
		void calculateNMIIndex();

		// calculates the VIIndex for each generated Partition with each real Partition
		void calculateVIIndex();

		// shows the calculated CRIndex
		void showCRIndex();

		// shows the calculated VIIndex
		void showVIIndex();

		// shows the calculated NMIIndex
		void showNMIIndex();
};
#endif
