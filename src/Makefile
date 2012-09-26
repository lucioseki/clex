CC = g++
FLAGS = -lboost_system -lboost_filesystem
OBJS = Object.o Cluster.o DataSet.o Partition.o Similarity.o ValidationIndex.o InformationTheory.o NMIIndex.o VIIndex.o CRIndex.o Clex.o

main: main.cpp Clex.o
	$(CC) main.cpp -o teste $(OBJS) $(FLAGS)

Clex.o: Clex.h Clex.cpp Partition.o DataSet.o Similarity.o CRIndex.o NMIIndex.o VIIndex.o
	$(CC) -c Clex.cpp $(FLAGS)

CRIndex.o: ValidationIndex/CRIndex.h ValidationIndex/CRIndex.cpp ValidationIndex.o Exception.h Partition.o
	$(CC) -c ValidationIndex/CRIndex.cpp

VIIndex.o: ValidationIndex/VIIndex.h ValidationIndex/VIIndex.cpp ValidationIndex.o Exception.h Partition.o InformationTheory.o
	$(CC) -c ValidationIndex/VIIndex.cpp

NMIIndex.o: ValidationIndex/NMIIndex.h ValidationIndex/NMIIndex.cpp ValidationIndex.o Exception.h Partition.o InformationTheory.o
	$(CC) -c ValidationIndex/NMIIndex.cpp

InformationTheory.o: InformationTheory.h InformationTheory.cpp Partition.o
	$(CC) -c InformationTheory.cpp

ClusteringAlgorithms.o: ClusteringAlgorithms.h ClusteringAlgorithms.cpp Partition.o SettingsAlgorithm.o DataSet.o Similarity.o
	$(CC) -c ClusteringAlgorithms.cpp

SettingsAlgorithm.o: SettingsAlgorithm.h SettingsAlgorithm.cpp
	$(CC) -c SettingsAlgorithm.cpp

ValidationIndex.o: ValidationIndex.h ValidationIndex.cpp Partition.o RelationSDN.o
	$(CC) -c ValidationIndex.cpp -lm

RelationSDN.o: RelationSDN.h RelationSDN.cpp DataSet.o SimilarityMatrix.h Similarity.o NnList.h
	$(CC) -c RelationSDN.cpp

SimilarityMatrix.o: SimilarityMatrix.h SimilarityMatrix.cpp RelationSDN.h DataSet.o Euclidean.o Object.o Pearson.o
	$(CC) -c SimilarityMatrix.cpp $(FLAGS)

NnList.o: NnList.h NnList.cpp RelationSDN.h DataSet.o
	$(CC) -c NnList.cpp

Euclidean.o: Euclidean.h Euclidean.cpp Similarity.o
	$(CC) -c Euclidean.cpp -lm

Pearson.o: Pearson.h Pearson.cpp Similarity.o
	$(CC) -c Pearson.cpp -lm

Similarity.o: Similarity.h Similarity.cpp Object.o
	$(CC) -c Similarity.cpp

Partition.o: Partition.h Partition.cpp Cluster.o DataSet.o
	$(CC) -c Partition.cpp $(FLAGS)

Cluster.o: Cluster.h Cluster.cpp DataSet.o
	$(CC) -c Cluster.cpp $(FLAGS)

DataSet.o: DataSet.h DataSet.cpp Object.o
	$(CC) -c DataSet.cpp $(FLAGS)

Object.o: Object.h Object.cpp
	$(CC) -c Object.cpp

clean:
	rm *~ *.o
