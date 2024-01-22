//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, Nov 2023
//
// Graph - Using a list of adjacency lists representation
//

#include "Graph.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "SortedList.h"
#include "instrumentation.h"

#define ITERATIONS InstrCount[0] // Number of iterations

struct _Vertex
{
  unsigned int id;
  unsigned int inDegree;
  unsigned int outDegree;
  List *edgesList;
};

struct _Edge
{
  unsigned int adjVertex;
  double weight;
};

struct _GraphHeader
{
  int isDigraph;
  int isComplete;
  int isWeighted;
  unsigned int numVertices;
  unsigned int numEdges;
  List *verticesList;
};


// The comparator for the VERTICES LIST

int graphVerticesComparator(const void *p1, const void *p2)
{
  unsigned int v1 = ((struct _Vertex *)p1)->id;
  unsigned int v2 = ((struct _Vertex *)p2)->id;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

// The comparator for the EDGES LISTS

int graphEdgesComparator(const void *p1, const void *p2)
{
  unsigned int v1 = ((struct _Edge *)p1)->adjVertex;
  unsigned int v2 = ((struct _Edge *)p2)->adjVertex;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

Graph *GraphCreate(unsigned int numVertices, int isDigraph, int isWeighted)
{
  Graph *g = (Graph *)malloc(sizeof(struct _GraphHeader));
  if (g == NULL)
    abort();

  g->isDigraph = isDigraph;
  g->isComplete = 0;
  g->isWeighted = isWeighted;

  g->numVertices = numVertices;
  g->numEdges = 0;

  g->verticesList = ListCreate(graphVerticesComparator);

  for (unsigned int i = 0; i < numVertices; i++)
  {
    struct _Vertex *v = (struct _Vertex *)malloc(sizeof(struct _Vertex));
    if (v == NULL)
      abort();

    v->id = i;
    v->inDegree = 0;
    v->outDegree = 0;

    v->edgesList = ListCreate(graphEdgesComparator);

    ListInsert(g->verticesList, v);
  }

  assert(g->numVertices == ListGetSize(g->verticesList));

  return g;
}

Graph *GraphCreateComplete(unsigned int numVertices, int isDigraph)
{
  Graph *g = GraphCreate(numVertices, isDigraph, 0);

  g->isComplete = 1;

  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    struct _Vertex *v = ListGetCurrentItem(vertices);
    List *edges = v->edgesList;
    for (unsigned int j = 0; j < g->numVertices; j++)
    {
      if (i == j)
      {
        continue;
      }
      struct _Edge *new = (struct _Edge *)malloc(sizeof(struct _Edge));
      if (new == NULL)
        abort();
      new->adjVertex = j;
      new->weight = 1;

      ListInsert(edges, new);
    }
    if (g->isDigraph)
    {
      v->inDegree = g->numVertices - 1;
      v->outDegree = g->numVertices - 1;
    }
    else
    {
      v->outDegree = g->numVertices - 1;
    }
  }
  if (g->isDigraph)
  {
    g->numEdges = numVertices * (numVertices - 1);
  }
  else
  {
    g->numEdges = numVertices * (numVertices - 1) / 2;
  }

  return g;
}

void GraphDestroy(Graph **p)
{
  assert(*p != NULL);
  Graph *g = *p;

  List *vertices = g->verticesList;
  if (ListIsEmpty(vertices) == 0)
  {
    ListMoveToHead(vertices);
    unsigned int i = 0;
    for (; i < g->numVertices; ListMoveToNext(vertices), i++)
    {
      struct _Vertex *v = ListGetCurrentItem(vertices);

      List *edges = v->edgesList;
      if (ListIsEmpty(edges) == 0)
      {
        unsigned int i = 0;
        ListMoveToHead(edges);
        for (; i < ListGetSize(edges); ListMoveToNext(edges), i++)
        {
          struct _Edge *e = ListGetCurrentItem(edges);
          free(e);
        }
      }
      ListDestroy(&(v->edgesList));
      free(v);
    }
  }

  ListDestroy(&(g->verticesList));
  free(g);

  *p = NULL;
}

Graph *GraphCopy(const Graph *g)
{
  assert(g != NULL);

  // TO BE COMPLETED !!

  // create a new graph with the same characteristics
  Graph *copy = GraphCreate(g->numVertices, g->isDigraph, g->isWeighted);
  assert(copy != NULL);

  // copy the edges from the original graph to the new graph
  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    struct _Vertex *v = ListGetCurrentItem(vertices);
    List *edges = v->edgesList;
    ListMoveToHead(edges);
    unsigned int j = 0;
    for (; j < ListGetSize(edges); ListMoveToNext(edges), j++)
    {
      ITERATIONS++; // count iterations
      struct _Edge *e = ListGetCurrentItem(edges);
      if (g->isWeighted)
      {
        GraphAddWeightedEdge(copy, i, e->adjVertex, e->weight);
      }
      else
      {
        GraphAddEdge(copy, i, e->adjVertex);
      }
    }
  }

  return copy;
}

Graph *GraphFromFile(FILE *f)
{
  assert(f != NULL);

  // TO BE COMPLETED !!
  int isDigraph;
  int isWeighted;
  unsigned int numVertices;
  unsigned int numEdges;

  // Read the initial data from the header of the file line by line
  if (fscanf(f, "%d", &isDigraph) != 1)
  {
    return NULL;
  }

  if (fscanf(f, "%d", &isWeighted) != 1)
  {
    return NULL;
  }

  if (fscanf(f, "%u", &numVertices) != 1)
  {
    return NULL;
  }

  if (fscanf(f, "%u", &numEdges) != 1)
  {
    return NULL;
  }

  // Create the graph with the initial data
  Graph *g = GraphCreate(numVertices, isDigraph, isWeighted);

  // Read the remaining data from the file line by line
  // vertice1 vertice2 weight(if weighted)
  for (unsigned int i = 0; i < numEdges; i++)
  {
    unsigned int start;
    unsigned int end;
    double weight;

    // if the graph is weighted, read the weight of the edge as well
    if (isWeighted)
    {
      if (fscanf(f, "%u %u %lf", &start, &end, &weight) != 3)
      {
        GraphDestroy(&g);
        return NULL;
      }
    }
    else
    {
      if (fscanf(f, "%u %u", &start, &end) != 2)
      {
        GraphDestroy(&g);
        return NULL;
      }
    }

    // if the start and end vertices are the same, ignore the edge
    if (start != end)
    {
      // check if the edge already exists
      unsigned int* adjacents = GraphGetAdjacentsTo(g, start);
      int exists = 0;
      // adjacents[0] = number of adjacents
      // adjacents[1] = first adjacent and so on
      for (unsigned int j = 1; j <= adjacents[0]; j++)
      {
        if (adjacents[j] == end)
        {
          exists = 1;
          break;
        }
      }
      free(adjacents);
      // if the edge does not exist, add it to the graph
      // this is done to avoid allocating memory for an edge that already exists and not use it
      if (!exists){
        // add the edge to the graph
        if (isWeighted)
        {
          GraphAddWeightedEdge(g, start, end, weight);
        }
        else
        {
          GraphAddEdge(g, start, end);
        }
      }
    }
  }

  return g;
}

// Graph

int GraphIsDigraph(const Graph *g) { return g->isDigraph; }

int GraphIsComplete(const Graph *g) { return g->isComplete; }

int GraphIsWeighted(const Graph *g) { return g->isWeighted; }

unsigned int GraphGetNumVertices(const Graph *g) { return g->numVertices; }

unsigned int GraphGetNumEdges(const Graph *g) { return g->numEdges; }

//
// For a graph
//
double GraphGetAverageDegree(const Graph *g)
{
  assert(g->isDigraph == 0);
  return 2.0 * (double)g->numEdges / (double)g->numVertices;
}

static unsigned int _GetMaxDegree(const Graph *g)
{
  List *vertices = g->verticesList;
  if (ListIsEmpty(vertices))
    return 0;

  unsigned int maxDegree = 0;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    struct _Vertex *v = ListGetCurrentItem(vertices);
    if (v->outDegree > maxDegree)
    {
      maxDegree = v->outDegree;
    }
  }
  return maxDegree;
}

//
// For a graph
//
unsigned int GraphGetMaxDegree(const Graph *g)
{
  assert(g->isDigraph == 0);
  return _GetMaxDegree(g);
}

//
// For a digraph
//
unsigned int GraphGetMaxOutDegree(const Graph *g)
{
  assert(g->isDigraph == 1);
  return _GetMaxDegree(g);
}

// Vertices

//
// returns an array of size (outDegree + 1)
// element 0, stores the number of adjacent vertices
// and is followed by indices of the adjacent vertices
//
unsigned int *GraphGetAdjacentsTo(const Graph *g, unsigned int v)
{
  assert(v < g->numVertices);

  // Node in the list of vertices
  List *vertices = g->verticesList;
  ListMove(vertices, v);
  struct _Vertex *vPointer = ListGetCurrentItem(vertices);
  unsigned int numAdjVertices = vPointer->outDegree;

  unsigned int *adjacent =
      (unsigned int *)calloc(1 + numAdjVertices, sizeof(unsigned int));

  if (numAdjVertices > 0)
  {
    adjacent[0] = numAdjVertices;
    List *adjList = vPointer->edgesList;
    ListMoveToHead(adjList);
    for (unsigned int i = 0; i < numAdjVertices; ListMoveToNext(adjList), i++)
    {
      struct _Edge *ePointer = ListGetCurrentItem(adjList);
      adjacent[i + 1] = ePointer->adjVertex;
    }
  }

  return adjacent;
}

//
// returns an array of size (outDegree + 1)
// element 0, stores the number of adjacent vertices
// and is followed by the distances to the adjacent vertices
//
double *GraphGetDistancesToAdjacents(const Graph *g, unsigned int v)
{
  assert(v < g->numVertices);

  // Node in the list of vertices
  List *vertices = g->verticesList;
  ListMove(vertices, v);
  struct _Vertex *vPointer = ListGetCurrentItem(vertices);
  unsigned int numAdjVertices = vPointer->outDegree;

  double *distance = (double *)calloc(1 + numAdjVertices, sizeof(double));

  if (numAdjVertices > 0)
  {
    distance[0] = numAdjVertices;
    List *adjList = vPointer->edgesList;
    ListMoveToHead(adjList);
    for (unsigned int i = 0; i < numAdjVertices; ListMoveToNext(adjList), i++)
    {
      struct _Edge *ePointer = ListGetCurrentItem(adjList);
      distance[i + 1] = ePointer->weight;
    }
  }

  return distance;
}

//
// For a graph
//
unsigned int GraphGetVertexDegree(Graph *g, unsigned int v)
{
  assert(g->isDigraph == 0);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex *p = ListGetCurrentItem(g->verticesList);

  return p->outDegree;
}

//
// For a digraph
//
unsigned int GraphGetVertexOutDegree(Graph *g, unsigned int v)
{
  assert(g->isDigraph == 1);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex *p = ListGetCurrentItem(g->verticesList);

  return p->outDegree;
}

//
// For a digraph
//
unsigned int GraphGetVertexInDegree(Graph *g, unsigned int v)
{
  assert(g->isDigraph == 1);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex *p = ListGetCurrentItem(g->verticesList);

  return p->inDegree;
}

// Edges

static int _addEdge(Graph *g, unsigned int v, unsigned int w, double weight)
{
  struct _Edge *edge = (struct _Edge *)malloc(sizeof(struct _Edge));
  edge->adjVertex = w;
  edge->weight = weight;

  ListMove(g->verticesList, v);
  struct _Vertex *vertex = ListGetCurrentItem(g->verticesList);
  int result = ListInsert(vertex->edgesList, edge);
  if (result == -1)
  {
    return 0;
  }
  else
  {
    g->numEdges++;
    vertex->outDegree++;

    ListMove(g->verticesList, w);
    struct _Vertex *destVertex = ListGetCurrentItem(g->verticesList);
    destVertex->inDegree++;
  }

  if (g->isDigraph == 0)
  {
    // Bidirectional edge
    struct _Edge *edge = (struct _Edge *)malloc(sizeof(struct _Edge));
    edge->adjVertex = v;
    edge->weight = weight;

    ListMove(g->verticesList, w);
    struct _Vertex *vertex = ListGetCurrentItem(g->verticesList);
    result = ListInsert(vertex->edgesList, edge);

    if (result == -1)
    {
      return 0;
    }
    else
    {
      // g->numEdges++; // Do not count the same edge twice on a undirected
      // graph !!
      vertex->outDegree++;
    }
  }
  return 1;
}

int GraphAddEdge(Graph *g, unsigned int v, unsigned int w)
{
  assert(g->isWeighted == 0);
  assert(v != w);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  return _addEdge(g, v, w, 1.0);
}

int GraphAddWeightedEdge(Graph *g, unsigned int v, unsigned int w,
                         double weight)
{
  assert(g->isWeighted == 1);
  assert(v != w);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  return _addEdge(g, v, w, weight);
}

int GraphRemoveEdge(Graph *g, unsigned int v, unsigned int w)
{
  assert(g != NULL);

  // TO BE COMPLETED !!

  ListMove(g->verticesList, v);
  struct _Vertex *vertex = ListGetCurrentItem(g->verticesList);

  List *edges = vertex->edgesList;
  ListMoveToHead(edges); // move to the first edge
  struct _Edge *edge = ListGetCurrentItem(edges);

  // search for the edge
  while (edge != NULL)
  {
    // if the edge is found, remove it
    if (edge->adjVertex == w)
    {
      ListRemoveCurrent(edges);
      g->numEdges--;
      vertex->outDegree--;

      ListMove(g->verticesList, w);
      struct _Vertex *destVertex = ListGetCurrentItem(g->verticesList);
      destVertex->inDegree--;
      free(edge);
      break;
    }
    // if the edge is not found, move to the next edge
    ListMoveToNext(edges);
    edge = ListGetCurrentItem(edges);
  }

  // if the graph is undirected, remove the edge in the opposite direction
  if (g->isDigraph == 0)
  {
    ListMove(g->verticesList, w);
    struct _Vertex *vertex = ListGetCurrentItem(g->verticesList);
    List *edges = vertex->edgesList;
    ListMoveToHead(edges);
    struct _Edge *edge = ListGetCurrentItem(edges);
    while (edge != NULL)
    {
      if (edge->adjVertex == v)
      {
        ListRemoveCurrent(edges);
        vertex->outDegree--;
        free(edge);
        break;
      }
      ListMoveToNext(edges);
      edge = ListGetCurrentItem(edges);
    }
  }

  return 1;
}

// CHECKING

int GraphCheckInvariants(const Graph *g)
{
  assert(g != NULL);
  // TO BE COMPLETED !!

  // check if the number of vertices is correct
  if (g->numVertices != ListGetSize(g->verticesList))
  {
    return 0;
  }

  // check if the number of edges is correct
  unsigned int numEdges = 0;
  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  for (unsigned int i = 0; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    struct _Vertex *v = ListGetCurrentItem(vertices);
    numEdges += v->outDegree;
  }
  // if the graph is undirected, divide the number of edges by 2
  if (g->isDigraph == 0)
  {
    numEdges /= 2;
  }

  if (g->numEdges != numEdges)
  {
    return 0;
  }

  // assert edges if the graph is complete
  if (g->isComplete)
  {
    // check if the graph is undirected
    if (g->isDigraph == 0)
    {
      // check if the number of edges is correct
      if (g->numEdges != g->numVertices * (g->numVertices - 1) / 2)
      {
        return 0;
      }
    }
    // check if the graph is directed
    else
    {
      // check if the number of edges is correct
      if (g->numEdges != g->numVertices * (g->numVertices - 1))
      {
        return 0;
      }
    }
  }

  // check if the graph is weighted
  if (g->isWeighted)
  {
    // check if the weights are correct
    List *vertices = g->verticesList;
    ListMoveToHead(vertices);
    for (unsigned int i = 0; i < g->numVertices; ListMoveToNext(vertices), i++)
    {
      struct _Vertex *v = ListGetCurrentItem(vertices);
      List *edges = v->edgesList;
      ListMoveToHead(edges);
      for (unsigned int j = 0; j < v->outDegree; ListMoveToNext(edges), j++)
      {
        struct _Edge *e = ListGetCurrentItem(edges);
        if (e->weight < 0 || e->weight > 1)
        {
          return 0;
        }
      }
    }
  }


  return 1;
}

// DISPLAYING on the console

void GraphDisplay(const Graph *g)
{
  printf("---\n");
  if (g->isWeighted)
  {
    printf("Weighted ");
  }
  if (g->isComplete)
  {
    printf("COMPLETE ");
  }
  if (g->isDigraph)
  {
    printf("Digraph\n");
    printf("Max Out-Degree = %d\n", GraphGetMaxOutDegree(g));
  }
  else
  {
    printf("Graph\n");
    printf("Max Degree = %d\n", GraphGetMaxDegree(g));
  }
  printf("Vertices = %2d | Edges = %2d\n", g->numVertices, g->numEdges);

  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    printf("%2d ->", i);
    struct _Vertex *v = ListGetCurrentItem(vertices);
    if (ListIsEmpty(v->edgesList))
    {
      printf("\n");
    }
    else
    {
      List *edges = v->edgesList;
      unsigned int i = 0;
      ListMoveToHead(edges);
      for (; i < ListGetSize(edges); ListMoveToNext(edges), i++)
      {
        struct _Edge *e = ListGetCurrentItem(edges);
        if (g->isWeighted)
        {
          printf("   %2d(%4.2f)", e->adjVertex, e->weight);
        }
        else
        {
          printf("   %2d", e->adjVertex);
        }
      }
      printf("\n");
    }
  }
  printf("---\n");
}

void GraphListAdjacents(const Graph *g, unsigned int v)
{
  printf("---\n");

  unsigned int *array = GraphGetAdjacentsTo(g, v);

  printf("Vertex %d has %d adjacent vertices -> ", v, array[0]);

  for (unsigned int i = 1; i <= array[0]; i++)
  {
    printf("%d ", array[i]);
  }

  printf("\n");

  free(array);

  printf("---\n");
}
