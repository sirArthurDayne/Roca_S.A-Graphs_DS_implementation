#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<set>
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


class Graph
{
public:
	Graph();
	void addVertex(const Vertex& v);
	void addEdge(int source, int target, int value);
	void removeEdge(int source, int target);
	bool isEdge(Vertex source, Vertex target);
	bool isVertexInArray(const Vertex& v);
	int size() const;
	std::set<int> neighbors(int vertex) const;
	void printMatrix();
	int& operator[] (int vertex);//get the value
	int  operator[] (int vertex) const;//copy the value
	
private:
	static const int MAXSIZE = 6;
	int adyacencyMatrix[MAXSIZE][MAXSIZE];//see the conection in 2d matrix
	std::vector<Vertex> vecVertices;
	int  vertexAmount;
};

