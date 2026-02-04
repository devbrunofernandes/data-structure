#include "Core/Graphs/AdjacencyList.h"

#include "Core/Array/Vector.h"
#include "Core/Array/Array.h"
#include <stdlib.h>
#include <stdio.h>
#include "Core/Queue/QueueLinked.h"
#include "Core/Hash/ClosedHashTable.h"
#include "Core/Stack/StackLinked.h"

typedef struct Vertex {
    Vector* edges;
    Vector* weights;
} Vertex;

typedef struct AdjacencyList {
    Vertex** list;
    int edges;
    int vertices;
} AdjacencyList;

static Vertex* createVertex() {
    Vertex* vertex = (Vertex*) malloc(sizeof(Vertex));
    vertex->edges = createVector();
    vertex->weights = createVector();
    return vertex;
}

static void destroyVertex(Vertex* vertex) {
    destroyVector(vertex->edges);
    destroyVector(vertex->weights);
    free(vertex);
}

AdjacencyList* createAdjacencyList(const int vertices) {
    AdjacencyList* newList = (AdjacencyList*) malloc(sizeof(*newList));

    newList->vertices = vertices;
    newList->edges = 0;
    newList->list = (Vertex**) calloc(vertices, sizeof(Vertex*));

    if (!newList->list) {
        free(newList);
        return NULL;
    }

    return newList;
}

void destroyAdjacencyList(AdjacencyList* graph) {
    for (int i = 0; i < graph->vertices; i++)
        if (graph->list[i]) {
            destroyVertex(graph->list[i]);
        }

    free(graph->list);
    free(graph);
}

void displayAdjacencyList(const AdjacencyList* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        printf("Edge %d: ", i);
        if (graph->list[i]) {
            printArray(graph->list[i]->edges->array, graph->list[i]->edges->size);
        } else {
            printf("\n ");
        }
    }

    printf("\n ");
}

void connectAdjacencyListWeight(AdjacencyList* graph, const int vertexA, const int vertexB, const int weight) {
    if (vertexA < 0 || vertexB < 0) {return;}
    if (vertexA >= graph->vertices || vertexB >= graph->vertices) {return;}

    if (!graph->list[vertexA]) {
        graph->list[vertexA] = createVertex();
    }

    pushBackVector(graph->list[vertexA]->edges, vertexB);
    pushBackVector(graph->list[vertexA]->weights, weight);
}

void connectAdjacencyList(AdjacencyList* graph, const int vertexA, const int vertexB) {
    connectAdjacencyListWeight(graph, vertexA, vertexB, 1);
}

void disconnectAdjacencyList(AdjacencyList* graph, const int vertexA, const int vertexB) {
    if (vertexA < 0 || vertexB < 0) {return;}
    if (vertexA >= graph->vertices || vertexB >= graph->vertices) {return;}

    if (!graph->list[vertexA]) {return;}

    const int index = searchVector(graph->list[vertexA]->edges, vertexB);
    if (index < 0) {return;}

    deleteVector(graph->list[vertexA]->edges, index);
    deleteVector(graph->list[vertexA]->weights, index);
}

int getWeightAdjacencyList(const AdjacencyList* graph, const int vertexA, const int vertexB) {
    if (vertexA < 0 || vertexB < 0) {return 0;}
    if (vertexA >= graph->vertices || vertexB >= graph->vertices) {return 0;}

    if (!graph->list[vertexA]) {return 0;}

    const int index = searchVector(graph->list[vertexA]->edges, vertexB);
    if (index < 0) {return 0;}

    return graph->list[vertexA]->weights->array[index];
}

void bfsAdjacencyList(const AdjacencyList* graph, const int startingVertex) {
    if (startingVertex < 0 || startingVertex >= graph->vertices) {return;}

    QueueLinked* q = createLinkedQueue();
    ClosedHashTable* visited = createClosedHashTable();

    printf("%d ", startingVertex);
    insertClosedHashTable(visited, startingVertex);
    enqueueLinkedQueue(q, startingVertex);

    while (!isEmptyLinkedQueue(q)) {
        const int vertexIdx = *frontLinkedQueue(q);
        dequeueLinkedQueue(q);
        const Vertex* vertex = graph->list[vertexIdx];

        if (!vertex) {continue;}

        for (int i = 0; i < vertex->edges->size; i++) {
            const int edge = vertex->edges->array[i];

            if (!searchClosedHashTable(visited, edge)) {
                printf("%d ", edge);
                insertClosedHashTable(visited, edge);
                enqueueLinkedQueue(q, edge);
            }
        }
    }

    printf("\n");
    destroyClosedHashTable(visited);
    destroyLinkedQueue(q);
}

void dfsAdjacencyList(const AdjacencyList* graph, const int startingVertex) {
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

        const Vertex* vertex = graph->list[vertexIdx];

        if (!vertex) {continue;}

        for (int i = 0; i < vertex->edges->size; i++) {
            const int edge = vertex->edges->array[i];

            if (!searchClosedHashTable(visited, edge)) {
                stlPush(st, vertexIdx);
                stlPush(st, edge);
                break;
            }
        }
    }

    printf("\n");
    stlDestroy(st);
    destroyClosedHashTable(visited);
}