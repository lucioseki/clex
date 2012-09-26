#include <exception>
#include "Clex.h"
#include "DataSet.h"
#include "Partition.h"
#include "Euclidean.h"
#include "Pearson.h"

int main(){
	Clex clex;

	vector<Partition*> vRealPartition;
	vector<Partition*> vRealPartition2;
	vector<Partition*> vGeneratedPartition;
	vector<Partition*> vGeneratedPartition2;

	// receber vDataSet de winDataSet;
	// vDataSet = winDataSet.get_DataSet();
	DataSet *pObjDataSet;
	DataSet *pObjDataSet2;
	Partition *pObjPartition;

	pObjDataSet = new DataSet("DataSet/", "simpsons.txt");
	pObjDataSet2 = new DataSet("DataSet/", "simpsons2.txt");
	
	// setar vDataSet do clex
	clex.setDataSet(pObjDataSet);
	clex.setDataSet(pObjDataSet2);

	// receber vRealPartition de winRealPartition
	// vRealPartition = winRealPartition.getPartition();

	// para cada DataSet, setar um vector de Partitions reais
	
	pObjPartition = new Partition(pObjDataSet, "Partition/", "simpsonsR.clu");
	clex.setRealPartition(pObjDataSet, pObjPartition);

	pObjPartition = new Partition(pObjDataSet, "Partition/", "simpsonsR2.clu");
	clex.setRealPartition(pObjDataSet, pObjPartition);

	pObjPartition = new Partition(pObjDataSet2, "Partition/", "simpsonsR.clu");
	clex.setRealPartition(pObjDataSet2, pObjPartition);

	pObjPartition = new Partition(pObjDataSet2, "Partition/", "simpsonsR2.clu");
	clex.setRealPartition(pObjDataSet2, pObjPartition);

	// receber vGeneratedPartition de winGeneratedPartition
	// vGeneratedPartition = winGeneratedPartition.getPartition();

	// para cada DataSet, setar um vector de Partitions calculados

	pObjPartition = new Partition(pObjDataSet, "Partition/", "simpsons.clu");
	clex.setGeneratedPartition(pObjDataSet, pObjPartition);
	pObjPartition = new Partition(pObjDataSet, "Partition/", "simpsons1.clu");
	clex.setGeneratedPartition(pObjDataSet, pObjPartition);

	pObjPartition = new Partition(pObjDataSet2, "Partition/", "simpsons.clu");
	clex.setGeneratedPartition(pObjDataSet2, pObjPartition);
	pObjPartition = new Partition(pObjDataSet2, "Partition/", "simpsons1.clu");
	clex.setGeneratedPartition(pObjDataSet2, pObjPartition);

	clex.calculateCRIndex();
	clex.showCRIndex();
	clex.calculateVIIndex();
	clex.showVIIndex();
	clex.calculateNMIIndex();
	clex.showNMIIndex();
	clex.setSimilarity(new Pearson);
	clex.calculateConnectivity(5);
	clex.showConnectivity();
	clex.calculateConnectivity(3);
	clex.showConnectivity();

	return 0;
}
