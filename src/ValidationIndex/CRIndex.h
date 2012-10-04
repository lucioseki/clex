/*
 * CRIndex.h
 *
 *      Author: Vinicius
 */

#ifndef __CR_INDEX_H__
#define __CR_INDEX_H__

#include <algorithm>
#include <vector>
#include <iostream>

#include "../Exception.h"
#include "../Partition.h"
#include "../ValidationIndex.h"


class CRIndex : public ValidationIndex {
  public:
        virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
        
        /* This method is to be used in internal validation measures, since CR isn't an internal validation measure
    the call of this method will throw an exception */
        virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset);
};

#endif
