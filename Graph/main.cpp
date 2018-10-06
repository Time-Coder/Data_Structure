#include <graph.h>

int main()
{
	DiGraph<char, int> graph;
	graph.show();
	auto vertex_A = graph.insert('A');
	auto vertex_B = graph.insert('B');
	auto vertex_C = graph.insert('C');
	auto vertex_D = graph.insert('D');
	graph.insert(vertex_B, vertex_A, 0, 7);
	graph.insert(vertex_B, vertex_C, 0, 9);
	graph.insert(vertex_B, vertex_D, 0, 2);
	graph.insert(vertex_D, vertex_B, 0, 5);
	graph.insert(vertex_A, vertex_C, 0, 3);
	graph.insert(vertex_C, vertex_A, 0, 4);

	// graph.show("Graph", false, "neato");
	cout << "n_vertice = " << graph.n_vertice() << endl;
	cout << "n_edges = " << graph.n_edges() << endl;
	graph.erase(vertex_A);
	cout << graph.exist(5) << endl;
	// graph.erase(vertex_A);
	// graph.show("Graph2", false, "neato");
	// graph.erase(1);
	// graph.erase(vertex_C);
	// graph.show("Graph2", false, "neato");

	return 0;
}