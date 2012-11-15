from Clex_module import *
a = Clex()

a.setSimilarity("Pearson")

arr = StrPairVector(2)
arr[0] = StrPair("DataSet/", "simpsons.txt")
arr[1] = StrPair("DataSet/", "simpsons2.txt")
a.setDataSet(arr)

a.createRelationSDN(3)
a.createRelationSDN(2)

arr[0] = StrPair("Partition/", "simpsonsR.clu")
arr[1] = StrPair("Partition/", "simpsonsR2.clu")
a.setRealPartition(0, arr)
a.setRealPartition(1, arr)

arr[0] = StrPair("Partition/", "simpsons.clu")
arr[1] = StrPair("Partition/", "simpsons1.clu")
a.setGeneratedPartition(0, arr)
a.setGeneratedPartition(1, arr)

arr = StrVector(3)
arr[0] = "CRIndex"
arr[1] = "NMIIndex"
arr[2] = "VIIndex"
a.setExternalIndex(arr)

arr[0] = "Deviation"
arr[1] = "Silhouette"
arr[2] = "Connectivity"
a.setInternalIndex(arr)

a.calculateValidationIndex()
a.showExternalIndex()
a.showInternalIndex()
