#include "Core/Graphs/AdjacencyMatrix.h"

#include <stdlib.h>
#include <stdio.h>
#include "Core/Queue/QueueLinked.h"
#include "Core/Stack/StackLinked.h"
#include "Core/Hash/ClosedHashTable.h"

typedef struct AdjacencyMatrix {
    int** matrix;
    int edges;
    int vertices;
} AdjacencyMatrix;

AdjacencyMatrix* createAdjacencyMatrix(const int vertices) {
    AdjacencyMatrix* newMatrix = (AdjacencyMatrix*) malloc(sizeof(*newMatrix));

    newMatrix->vertices = vertices;
    newMatrix->edges = 0;
    newMatrix->matrix = (int**) calloc(vertices, sizeof(int*));
    if (!newMatrix->matrix) {
        free(newMatrix);
        return NULL;
    }

    for (int i = 0; i < vertices; i++) {
        newMatrix->matrix[i] = (int*) calloc(vertices, sizeof(int));
        if (!newMatrix->matrix[i]) {
            newMatrix->vertices = i;
            destroyAdjacencyMatrix(newMatrix);
            return NULL;
        }
    }

    return newMatrix;
}

void destroyAdjacencyMatrix(AdjacencyMatrix* matrix) {
    for (int i = 0; i < matrix->vertices; i++)
        free(matrix->matrix[i]);

    free(matrix->matrix);
    free(matrix);
}

void displayAdjacencyMatrix(const AdjacencyMatrix* matrix) {
    for (int i = 0; i < matrix->vertices; i++) {
        for (int j = 0; j < matrix->vertices; j++) {
            printf("%d ", matrix->matrix[i][j]);
        }
        printf("\n ");
    }
    printf("\n ");
}

void connectAdjacencyMatrixWeight(AdjacencyMatrix* matrix, const int vertexA, const int vertexB, const int weight) {
    if (vertexA < 0 || vertexB < 0) {return;}
    if (vertexA >= matrix->vertices || vertexB >= matrix->vertices) {return;}

    matrix->matrix[vertexA][vertexB] = weight;
}

void connectAdjacencyMatrix(AdjacencyMatrix* matrix, const int vertexA, const int vertexB) {
    connectAdjacencyMatrixWeight(matrix, vertexA, vertexB, 1);
}

void disconnectAdjacencyMatrix(AdjacencyMatrix* matrix, const int vertexA, const int vertexB) {
    if (vertexA < 0 || vertexB < 0) {return;}
    if (vertexA >= matrix->vertices || vertexB >= matrix->vertices) {return;}

    matrix->matrix[vertexA][vertexB] = 0;
}

int getWeightAdjacencyMatrix(const AdjacencyMatrix* matrix, const int vertexA, const int vertexB) {
    if (vertexA < 0 || vertexB < 0) {return 0;}
    if (vertexA >= matrix->vertices || vertexB >= matrix->vertices) {return 0;}

    return matrix->matrix[vertexA][vertexB];
}

void bfsAdjacencyMatrix(const AdjacencyMatrix* graph, const int startingVertex) {
    if (startingVertex < 0 || startingVertex >= graph->vertices) {return;}

    QueueLinked* q = createLinkedQueue();
    ClosedHashTable* visited = createClosedHashTable();

    printf("%d ", startingVertex);
    insertClosedHashTable(visited, startingVertex);
    enqueueLinkedQueue(q, startingVertex);

    while (!isEmptyLinkedQueue(q)) {
        const int vertexIdx = *frontLinkedQueue(q);
        dequeueLinkedQueue(q);

        for (int i = 0; i < graph->vertices; i++) {
            const int weight = graph->matrix[vertexIdx][i];

            if (weight != 0 && !searchClosedHashTable(visited, i)) {
                printf("%d ", i);
                insertClosedHashTable(visited, i);
                enqueueLinkedQueue(q, i);
            }
        }
    }

    printf("\n");
    destroyClosedHashTable(visited);
    destroyLinkedQueue(q);
}

void dfsAdjacencyMatrix(const AdjacencyMatrix* graph, const int startingVertex) {
    if (startingVertex < 0 || startingVertex >= graph->vertices) {return;}

    StackLinked* st = stlCreate();
    ClosedHashTable* visited = createClosedHashTable();

    stlPush(st, startingVertex);

    while (!stlIsEmpty(st)) {
        const int vertexIdx = *stlTop(st);
        stlPop(st);

        if (!searchClosedHashTable(visited, vertexIdx)) {
            insertClosedHashTable(visited, vertexIdx);
            printf("%d ", vertexIdx);
        }

        for (int i = 0; i < graph->vertices; i++) {
            const int weight = graph->matrix[vertexIdx][i];

            if (weight != 0 && !searchClosedHashTable(visited, i)) {
                stlPush(st, vertexIdx);
                stlPush(st, i);
                break;
            }
        }
    }

    printf("\n");
    stlDestroy(st);
    destroyClosedHashTable(visited);
}