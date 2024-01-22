//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Topological Sorting
//

#include "GraphTopologicalSorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "instrumentation.h"

struct _GraphTopoSort
{
  int *marked;                    // Aux array
  unsigned int *numIncomingEdges; // Aux array
  unsigned int *vertexSequence;   // The result
  int validResult;                // 0 or 1
  unsigned int numVertices;       // From the graph
  Graph *graph;
};

#define ITERATIONS InstrCount[0] // Number of iterations

// AUXILIARY FUNCTION
// Allocate memory for the struct
// And for its array fields
// Initialize all struct fields
//
static GraphTopoSort *_create(Graph *g)
{
  assert(g != NULL);
  GraphTopoSort *p = (GraphTopoSort *)malloc(sizeof(struct _GraphTopoSort));
  assert(p != NULL);
  // TO BE COMPLETED
  // Allocate memory for the struct
  p->graph = g;

  p->numVertices = GraphGetNumVertices(g);

  p->validResult = 0; // 0 - not valid, 1 - valid

  p->vertexSequence = (unsigned int *)calloc(p->numVertices, sizeof(unsigned int)); // array with the topological sorting

  p->marked = (int *)calloc(p->numVertices, sizeof(int)); // 0 - not visited, 1 - visited

  // Initialize numIncomingEdges with the in-degree of each vertex
  p->numIncomingEdges = (unsigned int *)malloc(p->numVertices * sizeof(unsigned int));
  for (unsigned int i = 0; i < p->numVertices; i++)
  {
    p->numIncomingEdges[i] = GraphGetVertexInDegree(g, i);
  }

  return p;
}

//
// Computing the topological sorting, if any, using the 1st algorithm:
// 1 - Create a copy of the graph
// 2 - Successively identify vertices without incoming edges and remove their
//     outgoing edges
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort *GraphTopoSortComputeV1(Graph *g)
{
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort *topoSort = _create(g);
  // Build the topological sorting

  // TO BE COMPLETED
  Graph *copy = GraphCopy(g); /// 1 - Create a copy of the graph
  
  unsigned int count = 0;
  int found; // aux variable to check if a vertex without incoming edges was found

  while (count < GraphGetNumVertices(copy))
  {
    found = 0; // reset found
    for (unsigned int i = 0; i < GraphGetNumVertices(copy); i++)
    {      
      ITERATIONS++; // count iterations
      // find vertex without incoming edges
      if (GraphGetVertexInDegree(copy, i) == 0 && topoSort->marked[i] == 0)
      {
        found = 1; // found a vertex without incoming edges
        topoSort->vertexSequence[count++] = i;
        topoSort->marked[i] = 1;

        // remove outgoing edges
        unsigned int* adjacents = GraphGetAdjacentsTo(copy, i);
        // adjacents[0] = number of adjacents
        // adjacents[1] = first adjacent and so on
        for (unsigned int j = 1; j <= adjacents[0]; j++)
        {
          ITERATIONS++; // count iterations
          GraphRemoveEdge(copy, i, adjacents[j]);
        }
        free(adjacents);
        break;
      }
    } 
    // if no vertex without incoming edges was found, break the loop because it is a cycle
    if (found == 0)
    {
      break;
    }  
  }
  // check if valid
  if (count == GraphGetNumVertices(topoSort->graph))
  {
    topoSort->validResult = 1;
  }
  
  GraphDestroy(&copy);
  return topoSort;
}

//
// Computing the topological sorting, if any, using the 2nd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort *GraphTopoSortComputeV2(Graph *g)
{
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort *topoSort = _create(g);

  // Build the topological sorting

  // TO BE COMPLETED
  //...
  unsigned int count = 0;
  int found; // aux variable to check if a vertex without incoming edges was found

  while (count < GraphGetNumVertices(g))
  {
    found = 0; // reset found
    for (unsigned int i = 0; i < GraphGetNumVertices(g); i++)
    {
      ITERATIONS++; // count iterations
      // find vertex without incoming edges
      if (topoSort->numIncomingEdges[i] == 0 && topoSort->marked[i] == 0)
      {
        found = 1; // found a vertex without incoming edges
        topoSort->vertexSequence[count++] = i;
        topoSort->marked[i] = 1;

        // remove outgoing edges
        unsigned int* adjacents = GraphGetAdjacentsTo(g, i);
        // adjacents[0] = number of adjacents
        // adjacents[1] = first adjacent and so on
        for (unsigned int j = 1; j <= adjacents[0]; j++)
        {
          ITERATIONS++; // count iterations
          unsigned int w = adjacents[j]; // w is an adjacent of v
          topoSort->numIncomingEdges[w]--;  // remove edge (i,w)
        }
        free(adjacents);
        break;
      }
    } 
    // if no vertex without incoming edges was found, break the loop because it is a cycle
    if (found == 0)
    {
      break;
    }  
  }
  // check if valid
  if (count == GraphGetNumVertices(topoSort->graph))
  {
    topoSort->validResult = 1;
  }
  
  return topoSort;
}

//
// Computing the topological sorting, if any, using the 3rd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort *GraphTopoSortComputeV3(Graph *g)
{
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort *topoSort = _create(g);

  // Build the topological sorting

  // TO BE COMPLETED
  //...
  Queue *q = QueueCreate(GraphGetNumVertices(g));
  for (unsigned int i = 0; i < GraphGetNumVertices(g); i++)
  {
    ITERATIONS++; // count iterations
    if (topoSort->numIncomingEdges[i] == 0)
    {
      QueueEnqueue(q, i);
    }
  }

  unsigned int count = 0;
  while (!QueueIsEmpty(q))
  {
    ITERATIONS++; // count iterations
    unsigned int v = QueueDequeue(q); // v is a vertex without incoming edges
    topoSort->vertexSequence[count++] = v; // add v to the topological sorting
    unsigned int* adjacents = GraphGetAdjacentsTo(g, v); // get adjacents of v
    // adjacents[0] = number of adjacents
    // adjacents[1] = first adjacent and so on
    for (unsigned int j = 1; j <= adjacents[0]; j++)
    {
      ITERATIONS++; // count iterations
      unsigned int w = adjacents[j]; // w is an adjacent of v
      topoSort->numIncomingEdges[w]--;   // remove edge (v,w)
      if (topoSort->numIncomingEdges[w] == 0)  // if w has no incoming edges add it to the queue
      {
        QueueEnqueue(q, w);
      }
    }
    free(adjacents);
  }
  QueueDestroy(&q);

  // check if valid
  if (count == GraphGetNumVertices(topoSort->graph))
  {
    topoSort->validResult = 1;
  }
  
  return topoSort;
}

void GraphTopoSortDestroy(GraphTopoSort **p)
{
  assert(*p != NULL);

  GraphTopoSort *aux = *p;

  free(aux->marked);
  free(aux->numIncomingEdges);
  free(aux->vertexSequence);

  free(*p);
  *p = NULL;
}

//
// A valid sorting was computed?
//
int GraphTopoSortIsValid(const GraphTopoSort *p) { return p->validResult; }

//
// Getting an array containing the topological sequence of vertex indices
// Or NULL, if no sequence could be computed
// MEMORY IS ALLOCATED FOR THE RESULTING ARRAY
//
unsigned int *GraphTopoSortGetSequence(const GraphTopoSort *p)
{
  assert(p != NULL);
  // TO BE COMPLETED
  // ...
  if (p->validResult == 0)
  {
    return NULL;
  }
  return p->vertexSequence;
}

// DISPLAYING on the console

//
// The toplogical sequence of vertex indices, if it could be computed
//
void GraphTopoSortDisplaySequence(const GraphTopoSort *p)
{
  assert(p != NULL);

  if (p->validResult == 0)
  {
    printf(" *** The topological sorting could not be computed!! *** \n");
    return;
  }

  printf("Topological Sorting - Vertex indices:\n");
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++)
  {
    printf("%d ", p->vertexSequence[i]);
  }
  printf("\n");
}

//
// The toplogical sequence of vertex indices, if it could be computed
// Followed by the digraph displayed using the adjecency lists
// Adjacency lists are presented in topologic sorted order
//
void GraphTopoSortDisplay(const GraphTopoSort *p)
{
  assert(p != NULL);

  // The topological order
  GraphTopoSortDisplaySequence(p);

  if (p->validResult == 0)
  {
    return;
  }

  // The Digraph
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++)
  {
    GraphListAdjacents(p->graph, p->vertexSequence[i]);
  }
  printf("\n");
}
