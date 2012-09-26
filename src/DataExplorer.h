/*
 * DataExplorer.h
 *
 *  Created on: Dec 19, 2011
 *      Author: Marcus
 */

#ifndef DATAEXPLORER_H_
#define DATAEXPLORER_H_

#include "Partition.h"
#include "Similarity.h"
#include "RelationSDN.h"
#include "DataSet.h"
#include "Pearson.h"
#include "Euclidean.h"
#include "ValidationIndex.h"
#include "ClusteringAlgorithms.h"
#include "SettingsAlgorithm.h"

#include <vector>
#include <map>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string>
#include <iostream>

#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;


/*
 * separar a inserção na população da avaliação
 * fazer combinação de X partições
 * Ler diretórios no loadPartitionK2
 * fazer o boost funcionar
 * fazer o main
 * */

class DataExplorer {
	private:
		vector< ValidationIndex* > vectorValidationIndexes;
		vector< pair< ClusteringAlgorithms*, SettingsAlgorithm* > > vectorAlgorithms;
		vector< pair< Partition*, vector<double> > > vectorPopulation;

		fs::path pathPopulation;
		int iNumNn;
		RelationSDN *pRelationSDN;
		DataSet *pDataSet;
		Similarity *pSimilarity;
		vector<Partition*> vectorPartitions;
		vector<Partition*> vectorPartitionsK2;

	public:
		typedef vector< pair< Partition*, vector<double> > >::iterator itPartitionsOfPopulation;

		DataExplorer(string sAPathToPopulation, int iANumNn, DataSet *pADataSet, Similarity *pASimilarity, vector< pair< ClusteringAlgorithms*, SettingsAlgorithm* > > vectorAAlgorithms, vector< ValidationIndex* > vectorAValidationIndexes);

		void run();
		void generatePartitions();
		void breakPartition(Partition *pAPartition);
		void evaluatePartition(Partition *pAPartition);

		void orCombination(Partition *pAPartition1, Partition *pAPartition2);
		void diffCombination(Partition *pAPartition1, Partition *pAPartition2);
		void intersectionCombination(Partition *pAPartition1, Partition *pAPartition2);

		int loadPartitionsK2();
};

#endif /* DATAEXPLORER_H_ */
