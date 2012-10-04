#include <exception>
#include "Clex.h"
#include "DataSet.h"
#include "Partition.h"
#include "Euclidean.h"
#include "Pearson.h"

int main(){
	Clex clex;

	vector<pair<string, string> > vSDataSet;
	vector<pair<string, string> > vSRealPartition;
	vector<pair<string, string> > vSGeneratedPartition;
	vector<string> vSValidationIndex;

	// setar Similarity
	clex.setSimilarity(new Pearson);
	
	// receber vDataSet de winDataSet;
	// vDataSet = winDataSet.get_DataSet();
	vSDataSet.push_back(make_pair("DataSet/", "simpsons.txt"));
	vSDataSet.push_back(make_pair("DataSet/", "simpsons2.txt"));
	
	// setar vDataSet do clex
	clex.setDataSet(vSDataSet);

	// preencher mapRelationSDN passando NumNn como parametro
	clex.createRelationSDN(3);
	clex.createRelationSDN(2);

	// receber vRealPartition de winRealPartition
	// vRealPartition = winRealPartition.getPartition();

	// para cada DataSet, setar um vector de Partitions reais
	
	vSRealPartition.push_back(make_pair("Partition/", "simpsonsR.clu"));
	vSRealPartition.push_back(make_pair("Partition/", "simpsonsR2.clu"));
	clex.setRealPartition(0, vSRealPartition);
	vSRealPartition.clear();

	vSRealPartition.push_back(make_pair("Partition/", "simpsonsR.clu"));
	vSRealPartition.push_back(make_pair("Partition/", "simpsonsR2.clu"));
	clex.setRealPartition(1, vSRealPartition);
	vSRealPartition.clear();

	// receber vGeneratedPartition de winGeneratedPartition
	// vGeneratedPartition = winGeneratedPartition.getPartition();

	// para cada DataSet, setar um vector de Partitions calculados

	vSGeneratedPartition.push_back(make_pair("Partition/", "simpsons.clu"));
	vSGeneratedPartition.push_back(make_pair("Partition/", "simpsons1.clu"));
	clex.setGeneratedPartition(0, vSGeneratedPartition);
	vSGeneratedPartition.clear();

	vSGeneratedPartition.push_back(make_pair("Partition/", "simpsons.clu"));
	vSGeneratedPartition.push_back(make_pair("Partition/", "simpsons1.clu"));
	clex.setGeneratedPartition(1, vSGeneratedPartition);
	vSGeneratedPartition.clear();

	// setar os indices de validacao
	vSValidationIndex.push_back("CRIndex");
	vSValidationIndex.push_back("NMIIndex");
	vSValidationIndex.push_back("VIIndex");
	vSValidationIndex.push_back("Connectivity");
	vSValidationIndex.push_back("Deviation");
	vSValidationIndex.push_back("Silhouette");

	clex.setValidationIndex(vSValidationIndex);
	clex.calculateValidationIndex();
	clex.showValidationIndex();
/*
	clex.calculateCRIndex();
	clex.showCRIndex();
	
	clex.calculateVIIndex();
	clex.showVIIndex();
	clex.calculateNMIIndex();
	clex.showNMIIndex();

	clex.calculateConnectivity(3);
	clex.showConnectivity();

	clex.calculateDeviation(4);
	clex.showDeviation();
	clex.calculateSilhouette(4);
	clex.showSilhouette();
*/
	return 0;
}
