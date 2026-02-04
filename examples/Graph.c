#include "Core/Graphs/AdjacencyMatrix.h"
#include "Core/Graphs/AdjacencyList.h"

int main() {
    AdjacencyMatrix* graph = createAdjacencyMatrix(5);
    
    connectAdjacencyMatrix(graph, 0, 3);
    connectAdjacencyMatrix(graph, 0, 1);
    connectAdjacencyMatrix(graph, 3, 1);
    connectAdjacencyMatrix(graph, 4, 0);
    
    disconnectAdjacencyMatrix(graph, 3, 1);
    disconnectAdjacencyMatrix(graph, 3, 0);
    
    dfsAdjacencyMatrix(graph, 0);

    destroyAdjacencyMatrix(graph);
}