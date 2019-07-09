#include"Graph.h"

int main()
{
	Graph graph;
	Vertex a("alfa", 0);
	Vertex b("beta", 1);
	Vertex c("gamma", 2);
	Vertex d("delta", 3);
	Vertex e("echo", 4);
	Vertex f("foxtrot", 5);

	graph.addVertex(a);
	graph.addVertex(b);
	graph.addVertex(c);
	graph.addVertex(d);
	graph.addVertex(e);
	graph.addVertex(f);
	


	graph.addEdge(a.vertexID, b.vertexID, 10);
	graph.addEdge(e.vertexID, d.vertexID, 20);

	if (graph.isEdge(a, b)) std::cout << "edge found between: " << a.name <<
		" -->" << b.name;
	if (!graph.isEdge(c, d))  std::cout << "\nedge NOT found between: " << c.name <<
		" -->" << d.name;
	
	std::cout << std::endl;
	
	graph.printMatrix();

	graph.removeEdge(a.vertexID, b.vertexID);

	std::cout << std::endl;
	graph.printMatrix();


	std::cin.get();
	std::cin.get();
	return 0;
}