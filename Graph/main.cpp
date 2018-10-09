#include <graph.h>

int main()
{
	// 广度优先搜索测试
	DiGraph<char, int> graph;
	auto vertex_S = graph.insert('S');
	auto vertex_A = graph.insert('A');
	auto vertex_B = graph.insert('B');
	auto vertex_C = graph.insert('C');
	auto vertex_D = graph.insert('D');
	auto vertex_E = graph.insert('E');
	auto vertex_F = graph.insert('F');
	auto vertex_G = graph.insert('G');

	graph.insert(vertex_S, vertex_A, 0);
	graph.insert(vertex_S, vertex_C, 0);
	graph.insert(vertex_S, vertex_D, 0);
	graph.insert(vertex_A, vertex_C, 0);
	graph.insert(vertex_A, vertex_E, 0);
	graph.insert(vertex_C, vertex_B, 0);
	graph.insert(vertex_D, vertex_B, 0);
	graph.insert(vertex_E, vertex_F, 0);
	graph.insert(vertex_E, vertex_G, 0);
	graph.insert(vertex_G, vertex_B, 0);
	graph.insert(vertex_G, vertex_F, 0);

	// graph.show();
	graph.BFS();
	Forest<char*> forest = graph.get_forest();
	forest.show_content();

	// 深度优先搜索测试
	// DiGraph<char, int> graph;
	// auto vertex_A = graph.insert('A');
	// auto vertex_B = graph.insert('B');
	// auto vertex_C = graph.insert('C');
	// auto vertex_D = graph.insert('D');
	// auto vertex_E = graph.insert('E');
	// auto vertex_F = graph.insert('F');
	// auto vertex_G = graph.insert('G');

	// graph.insert(vertex_A, vertex_B, 0);
	// graph.insert(vertex_A, vertex_C, 0);
	// graph.insert(vertex_A, vertex_F, 0);
	// graph.insert(vertex_B, vertex_C, 0);
	// graph.insert(vertex_D, vertex_A, 0);
	// graph.insert(vertex_D, vertex_E, 0);
	// graph.insert(vertex_E, vertex_F, 0);
	// graph.insert(vertex_F, vertex_G, 0);
	// graph.insert(vertex_G, vertex_A, 0);
	// graph.insert(vertex_G, vertex_C, 0);

	// graph.show();
	// Forest<char*> forest = graph.DFS();
	// forest.show_content();

	return 0;
}