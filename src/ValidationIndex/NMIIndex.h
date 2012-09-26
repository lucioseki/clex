/*
 * NMIndex.h
 *
 *  Created on: ??/??/2010
 *      Author: ???
 */

#ifndef __NMI_INDEX_H__
#define __NMI_INDEX_H__

#include "../Exception.h"
#include "../InformationTheory.h"
#include "../Partition.h"
#include "../ValidationIndex.h"

/* Vinicius, colocar um breve comentário sobre o que a NMIIndex faz */
/* Colacar um comentário mais detalhado sobre o que faz a NMIIndex e porque herda de InformatinTheory e ValidationIndex */
/* External validation index that uses InformationTheory */
class NMIIndex : public InformationTheory, ValidationIndex {
    public:
            virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
            virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset);

};

#endif
