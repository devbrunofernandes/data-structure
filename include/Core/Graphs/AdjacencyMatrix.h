#ifndef DATASTRUCTURES_ADJACENCY_MATRIX_H
#define DATASTRUCTURES_ADJACENCY_MATRIX_H

typedef struct AdjacencyMatrix AdjacencyMatrix;

AdjacencyMatrix* createAdjacencyMatrix(int vertices);

void destroyAdjacencyMatrix(AdjacencyMatrix* matrix);

void displayAdjacencyMatrix(const AdjacencyMatrix* matrix);

void connectAdjacencyMatrixWeight(AdjacencyMatrix* matrix, int vertexA, int vertexB, int weight);

void connectAdjacencyMatrix(AdjacencyMatrix* matrix, int vertexA, int vertexB);

void disconnectAdjacencyMatrix(AdjacencyMatrix* matrix, int vertexA, int vertexB);

int getWeightAdjacencyMatrix(const AdjacencyMatrix* matrix, int vertexA, int vertexB);

void bfsAdjacencyMatrix(const AdjacencyMatrix* graph, int startingVertex);

void dfsAdjacencyMatrix(const AdjacencyMatrix* graph, int startingVertex);

#endif //DATASTRUCTURES_ADJACENCY_MATRIX_H