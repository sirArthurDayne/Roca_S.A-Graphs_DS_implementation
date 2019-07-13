#pragma once
#include"olcPixelGameEngine.h"
#include<assert.h>

struct Vertex //also call Node
{
public:
	std::string name;
	int vertexID;
	Vertex(): name(""), vertexID(-1) {};
	Vertex(std::string name) : name(name){ vertexID = -1; }
	Vertex(std::string name, int id) : name(name), vertexID(id) { }
};

struct Edge
{
	Vertex* target;//target node
	Edge* next;
};


class Graph
{
public:
	Graph();
	void addVertex(const Vertex& v);
	void addEdge(int source, int target, int value);
	void addEdgeUndirected(int source, int target, int value);
	void removeEdge(int source, int target);
	
	bool isEdge(Vertex source, Vertex target);
	bool isVertexInArray(const Vertex& v);
	int size() const;
	void printMatrix();
	void BFS(Vertex origin, Vertex target);
	void DFS(Vertex origin, Vertex target);
private:
	static const int MAXSIZE = 8;
	float adyacencyMatrix[MAXSIZE][MAXSIZE];//see the conection in 2d matrix
	std::vector<Vertex> vecVertices;
	int  vertexAmount;
};

