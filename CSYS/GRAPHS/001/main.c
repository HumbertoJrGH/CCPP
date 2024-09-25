#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// CONSTANTS
#define MAX_NODES 10
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

// GRAPH STRUCT
typedef struct
{
	int adjMatrix[MAX_NODES][MAX_NODES];
	int numNodes;
} Graph;


void initGraph(Graph *g, int nodes)
{
	g->numNodes = nodes;
	for (int i = 0; i < nodes; i++)
		for (int j = 0; j < nodes; j++)
			g->adjMatrix[i][j] = 0;
}

void addEdge(Graph *g, int src, int dest)
{
	if (src < g->numNodes && dest < g->numNodes)
	{
		g->adjMatrix[src][dest] = 1;
		g->adjMatrix[dest][src] = 1;
	}
}

void printGraph(Graph *g)
{
	printf(COLOR_BLUE "Graph Adjacency Matrix:\n" COLOR_RESET);
	printf("  ");
	for (int i = 0; i < g->numNodes; i++)
	{
		printf(COLOR_GREEN "%d " COLOR_RESET, i);
	}
	printf("\n");

	for (int i = 0; i < g->numNodes; i++)
	{
		// Print row header (node index)
		printf(COLOR_GREEN "%d " COLOR_RESET, i);

		// Print adjacency matrix with color for edges
		for (int j = 0; j < g->numNodes; j++)
		{
			if (g->adjMatrix[i][j] == 1)
			{
				printf(COLOR_RED "1 " COLOR_RESET); // Edge
			}
			else
			{
				printf("0 "); // No edge
			}
		}
		printf("\n");
	}
}

int main()
{
	printf("Creating Graphs");
	Graph g;
	int numNodes = 5; // Example with 5 nodes

	initGraph(&g, numNodes);

	// Add some edges
	addEdge(&g, 0, 1);
	addEdge(&g, 0, 2);
	addEdge(&g, 1, 2);
	addEdge(&g, 1, 3);
	addEdge(&g, 3, 4);

	// Print the graph
	printGraph(&g);

	return 0;
}