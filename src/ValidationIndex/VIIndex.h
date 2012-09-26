#ifndef __VI_INDEX_H__
#define __VI_INDEX_H__

/* External validation index that uses InformationTheory */

#include "../InformationTheory.h"
#include "../ValidationIndex.h"

/**
 *  @author Vinicius
 *  @since ??/??/??
 *  @version 2.0
 */

/* Vinicius, colocar um breve comentário sobre o que a VIIndex faz */
/* Colacar um comentário mais detalhado sobre o que faz a VIIndex e porque herda de InformatinTheory e ValidationIndex */
class VIIndex : public InformationTheory, ValidationIndex {
    public:
            virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
            virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset);

};

#endif


