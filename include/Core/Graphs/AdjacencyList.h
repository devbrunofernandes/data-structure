#ifndef DATASTRUCTURES_ADJACENCY_LIST_H
#define DATASTRUCTURES_ADJACENCY_LIST_H

typedef struct AdjacencyList AdjacencyList;

AdjacencyList* createAdjacencyList(int vertices);

void destroyAdjacencyList(AdjacencyList* graph);

void displayAdjacencyList(const AdjacencyList* graph);

void connectAdjacencyListWeight(AdjacencyList* graph, int vertexA, int vertexB, int weight);

void connectAdjacencyList(AdjacencyList* graph, int vertexA, int vertexB);

void disconnectAdjacencyList(AdjacencyList* graph, int vertexA, int vertexB);

int getWeightAdjacencyList(const AdjacencyList* graph, int vertexA, int vertexB);

void bfsAdjacencyList(const AdjacencyList* graph, int startingVertex);

void dfsAdjacencyList(const AdjacencyList* graph, int startingVertex);

#endif //DATASTRUCTURES_ADJACENCY_LIST_H