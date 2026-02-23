#ifndef DATASTRUCTURES_SEGMENTTREE_H
#define DATASTRUCTURES_SEGMENTTREE_H

typedef struct SegTree SegTree;

SegTree* segTreeCreate(const int* data, int size);

void segTreeDestroy(SegTree* segTree);

void segTreeUpdate(SegTree* segTree, int index, int value);

int segTreeQuery(SegTree* segTree, int start, int end);

#endif //DATASTRUCTURES_SEGMENTTREE_H