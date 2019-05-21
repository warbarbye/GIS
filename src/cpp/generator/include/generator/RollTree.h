//
// Created by Konstantin on 20.04.2019.
//

#ifndef BAGENERATOR_ROLLTREE_H
#define BAGENERATOR_ROLLTREE_H

#include "PreferentialAttachement.h"
#include "Bucket.h"
#include "RandomImp.hpp"
#include "RollNode.h"
#include <map>


class RollTree : public PreferentialAttachement{
private:
    // wheel structure
    RollNode* root;
    std::unique_ptr<Random> r;
    // set of buckets, access in need of moving nodes todo consider class
    std::map<int, RollNodeLeaf*> buckets;
    // keep status of selection
    mutable SNode selectedNode;
    mutable RollNodeLeaf* selectedLeaf;

    ulong rollSeed(const RollNode*) const;
    // insert item
    void insertBucket(SNode&, int degree);
    // updating tree
    void updateTree(SNode& node, RollNodeLeaf* oldBucket);

    void updateAncestorWeights(RollNode* node);
    void updateWeights(RollNodeLeaf* node);
    inline void updateNodeWeight(RollNode* node) {
        const ulong lweight = node->leftChild != nullptr ? node->leftChild->weight : 0;
        const ulong rweight = node->rightChild != nullptr ? node->rightChild->weight : 0;
        node->weight = lweight + rweight;
    }


    // delete item
    void deleteNode(RollNodeLeaf *node);
public:



    void confirmSelection() override;
    // find an item
    SNode selectNode() const override;
    virtual void insertNode(SNode &node, int degree);

    RollTree();

    ~RollTree();
};


#endif //BAGENERATOR_ROLLTREE_H
