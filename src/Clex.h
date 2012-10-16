#ifndef CLEX_H
#define CLEX_H

#include "Partition.h"
#include "DataSet.h"
#include "Similarity.h"
#include "Euclidean.h"
#include "Pearson.h"
#include "RelationSDN.h"
#include "ValidationIndex.h"

#include <map>
#include<set>

class Clex{

	private:
		Similarity *pSimilarity; //< pointer to the measure of Similarity
		map<string, Similarity*> mapSimilarity;

		vector<DataSet*> vDataSet; //< vector containing pointers to the DataSets

		map<string, ValidationIndex*> mapExternalIndex;

		map<string, ValidationIndex*> mapInternalIndex;

		set<ValidationIndex*> sExternalIndex; //< set containing a vector of external validation indexes to be used

		set<ValidationIndex*> sInternalIndex; //< set containing a vector of internal validation indexes to be used

		map<DataSet*, vector<Partition*> > mapRealPartitions; //< map containing a vector of real partitions for each DataSet

		map<DataSet*, vector<Partition*> > mapGeneratedPartitions; //< map containing a vector of calculated partitions for each DataSet

		map<DataSet*, map<Partition*, map<int , map<ValidationIndex*, double> > > > mapCalculatedInternalIndex;

		map<DataSet*, map<Partition*, map<Partition*, map<ValidationIndex*, double> > > > mapCalculatedExternalIndex;

		vector<RelationSDN*> vRelationSDN; // vector that contains the RelationSDN for each combination of Similarity, DataSet and NumNn

	public:
		// constructor
		Clex();

		// sets the similarity measure
		void setSimilarity(const string &sASimilarity);

		// sets the DataSets
		// @param a vector of paths for each DataSet
		// instanciates a DataSet for each path and inserts in the vDataSet
		void setDataSet(vector<pair<string, string> > &vASDataSet);

		// sets the External Validation Indexes to be used
		// @param a vector of names of the indexes
		void setExternalIndex(vector<string> &vASValidationIndex);

		// sets the Internal Validation Indexes to be used
		// @param a vector of names of the indexes
		void setInternalIndex(vector<string> &vASValidationIndex);

		// creates RelationSDN for each combination of Similarity, DataSet and NumNn
		void createRelationSDN(int iANumNn);

		// sets a Real Partition for a DataSet
		// @param the position of the DataSet in the vDataSet
		// and a vector of paths for each Partition
		void setRealPartition(int iADataSet, vector<pair<string, string> > &vASPartition);

		// sets a Generated Partition for a DataSet
		// @param the position of the DataSet in the vDataSet
		// and a vector of paths for each Partition
		void setGeneratedPartition(int iADataSet, vector<pair<string, string> > &vASPartition);

		// calculates the validation Indexes
		void calculateValidationIndex();

		// calculates the external validation Indexes
		void calculateExternalIndex();

		// calculates the internal validation Indexes
		void calculateInternalIndex();

		// shows the internal calculated Indexes
		void showInternalIndex();

		// shows the external calculated Indexes
		void showExternalIndex();

};
#endif
