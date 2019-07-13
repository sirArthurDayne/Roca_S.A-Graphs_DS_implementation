#include "Graph.h"

Graph::Graph()
{
	vertexAmount = 0;//start at 0
	for (int rows = 0;  rows < MAXSIZE; rows++)
		for (int columns = 0; columns < MAXSIZE; columns++)
			adyacencyMatrix[rows][columns] = 0.0;
		
}

void Graph::addVertex(const Vertex& v)
{
	
	if (vertexAmount < MAXSIZE)
	{
		bool isInside = isVertexInArray(v);
	
		if (!isInside)
		{
			vecVertices.push_back(v);
			vertexAmount++;//increase the size
		}
		else std::cout << "ERROR, VERTEX ALREADY EXITS\n";
	}
	else std::cout << "ERROR, VERTEX MAX CAPACITY\n";

}

void Graph::addEdge(int source, int target, int value)
{
	assert(source < MAXSIZE && target < MAXSIZE);

	adyacencyMatrix[source][target] = value;
}

void Graph::addEdgeUndirected(int source, int target, int value)
{
	assert(source < MAXSIZE && target < MAXSIZE);

	adyacencyMatrix[source][target] = value;
	adyacencyMatrix[target][source] = value;
}

void Graph::removeEdge(int source, int target)
{
	assert(source < MAXSIZE && target < MAXSIZE);

	adyacencyMatrix[source][target] = 0.0;
}


bool Graph::isEdge(Vertex source, Vertex target)
{
	assert(source.vertexID < MAXSIZE && target.vertexID < MAXSIZE);
	
	bool foundEdge = (adyacencyMatrix[source.vertexID][target.vertexID] != 0);

	return foundEdge;
}

bool Graph::isVertexInArray(const Vertex& v)
{
	int i = 0;
	bool found = false;
	while (i < vertexAmount  && !found)
	{
		found = (vecVertices[i].name == v.name);

		if (!found) i++;
	}
	return found;
}

int Graph::size() const
{
	return vertexAmount;
}

float Graph::getValueInMatrix(int source, int target) const
{
	//first colums then rows
	return adyacencyMatrix[source][target];
}


void Graph::printMatrix()
{
	for (int rows = 0; rows < MAXSIZE; rows++)
	{
		std::cout << vecVertices[rows].name << " ";
		for (int col = 0; col < MAXSIZE; col++)
		{
			std::cout << adyacencyMatrix[rows][col] << " - ";
		}
		std::cout << std::endl;
	}
}
