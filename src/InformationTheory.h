/*
 * InformationTheory.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#ifndef INFORMATIONTHEORY_H_
#define INFORMATIONTHEORY_H_

#include <math.h>

#include"Partition.h"

/* Vinicius, colocar um breve coment‡rio sobre o que a information_theory faz */
/* Colacar um coment‡rio mais detalhado sobre o que faz a information_theory */
/* This class contains methods to be used in external validation measures based on Information Theory */
class InformationTheory {

    protected:
              double entropy(Partition &objPartition);
              double mutualInformation(Partition &objPartition1, Partition &objPartition2);
    private:
              double intersection(Partition &objPartition1, Partition &objPartition2, Partition::itClustersOfPartition itPartition1, Partition::itClustersOfPartition itPartition2);

};

#endif /* INFORMATIONTHEORY_H_ */
