#include <stdlib.h>

#include "Core/Trees/SegmentTree.h"

typedef struct SegTree {
    int* array;
    int size;
    int capacity;
} SegTree;

static void segTreeBuild(SegTree* segTree, const int* data, const int node, const int start, const int end) {
    if (start == end) {
        segTree->array[node] = data[start];
        return;
    }

    const int mid = (start + end) / 2;

    segTreeBuild(segTree, data, 2 * node, start, mid);
    segTreeBuild(segTree, data, (2 * node) + 1, mid + 1, end);

    const int value = segTree->array[2 * node] + segTree->array[2 * node + 1];
    segTree->array[node] = value;
}

SegTree* segTreeCreate(const int* data, const int size) {
    SegTree* segTree = (SegTree*)malloc(sizeof(SegTree));

    segTree->capacity = size * 4;
    segTree->array = (int*) malloc(sizeof(int) * segTree->capacity);
    segTree->size = size;

    segTreeBuild(segTree, data, 1, 0, size - 1);

    return segTree;
}

void segTreeDestroy(SegTree* segTree) {
    if (segTree == NULL) return;

    if (segTree->array != NULL) free(segTree->array);
    free(segTree);
}

static void segTreeUpdateHelper(SegTree* segTree, const int index, const int value, const int node, const int start, const int end) {
    if (start == end) {
        segTree->array[node] = value;
        return;
    }

    const int mid = (start + end) / 2;

    if (index <= mid) {
        segTreeUpdateHelper(segTree, index, value, 2 * node, start, mid);
    } else {
        segTreeUpdateHelper(segTree, index, value, 2 * node + 1, mid + 1, end);
    }

    const int newValue = segTree->array[2 * node] + segTree->array[2 * node + 1];
    segTree->array[node] = newValue;
}

void segTreeUpdate(SegTree* segTree, const int index, const int value) {
    segTreeUpdateHelper(segTree, index, value, 1, 0, segTree->size - 1);
}

static int segTreeQueryHelper(SegTree* segTree, const int node, const int finalStart, const int finalEnd, const int currStart, const int currEnd) {
    if (currStart >= finalStart && currEnd <= finalEnd)
        return segTree->array[node];

    if (currStart > finalEnd || currEnd < finalStart)
        return 0;

    const int mid = (currStart + currEnd) / 2;

    const int left = segTreeQueryHelper(segTree, node * 2, finalStart, finalEnd, currStart, mid);
    const int right = segTreeQueryHelper(segTree, node * 2 + 1, finalStart, finalEnd, mid + 1, currEnd);

    return left + right;
}

int segTreeQuery(SegTree* segTree, const int start, const int end) {
    if (start > end || start < 0 || end >= segTree->size) return 0;

    return segTreeQueryHelper(segTree, 1, start, end, 0, segTree->size - 1);
}
