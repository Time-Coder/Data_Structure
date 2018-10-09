#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <limits>

#include <list.h>
#include <queue.h>
#include <tree.h>

template<class VDataType, class EDataType>
class Vertex;

template<class VDataType, class EDataType>
class Edge
{
public:
	enum EType {UNDETERMINED, TREE, CROSS, BACKWARD, FORWARD};

public:
	Vertex<VDataType, EDataType>* _ptr_vertex_to = NULL;
	EDataType _data;
	double _weight = 0;
	EType type = UNDETERMINED;
	
public:
	Edge(){} // finished, tested
	Edge(Vertex<VDataType, EDataType>* ptr_vertex, const EDataType& data, double weight = .0) :
	_ptr_vertex_to(ptr_vertex), _data(data), _weight(weight) {} // finished, testd
	~Edge(){_ptr_vertex_to = NULL;_weight = 0;} // finished, tested
};

template<class VDataType, class EDataType>
class Vertex
{
public:
	enum VStatus {UNDISCOVERED, DISCOVERED, VISITED};

public:
	VDataType _data;
	List< Edge<VDataType, EDataType> > adjacency_list;
	int _out_deg = 0;
	int _in_deg = 0;
	int discover_time = 0;
	int finish_time = 0;
	bool got = false;
	VStatus status = UNDISCOVERED;

public:
	Vertex() : _out_deg(0), _in_deg(0) {} // finished, tested
	Vertex(const VDataType& data) : _data(data), _out_deg(0), _in_deg(0) {} // finished, tested
	~Vertex(){}; // finished, tested
	int out_deg()const{return _out_deg;}; // finished, tested
	int in_deg()const{return _in_deg;}; // finished, tested
};

template<class VDataType, class EDataType>
class DiGraph
{
public:
	List< Vertex<VDataType, EDataType> > vertex_list;
	int _n_edges = 0;

private:
	void dfs(Vertex<VDataType, EDataType>* vertex, int& clock);
	Tree<VDataType*>& bfs(Vertex<VDataType, EDataType>* vertex);

public:
	DiGraph(){} // finished, tested
	DiGraph(const DiGraph<VDataType, EDataType>& graph){vertex_list = graph.vertices;} // finished, tested
	
	// Graph assistance
	void reset();

	// Graph information
	int n_vertice()const; // finished, tested
	int n_edges()const; // finished, tested
	bool empty()const; // finished, tested

	// Vertex operations
	bool exist(Vertex<VDataType, EDataType>* ptr_vertex)const; // finished, tested
	bool exist(int it_vertex)const; // finished, tested
	Vertex<VDataType, EDataType>* insert(const VDataType& v); // finished, tested
	VDataType erase(Vertex<VDataType, EDataType>* ptr_vertex); // finished, tested
	VDataType erase(int it_vertex); // finished, tested
	VDataType& vertex(Vertex<VDataType, EDataType>* ptr_vertex)const; // finished, tested
	VDataType& vertex(int it_vertex)const; // finished, tested
	int in_deg(int it_vertex)const; // finished, tested
	int in_deg(Vertex<VDataType, EDataType>* ptr_vertex)const; // finished, tested
	int out_deg(int it_vertex)const; // finished, tested
	int out_deg(Vertex<VDataType, EDataType>* ptr_vertex)const; // finished, tested

	// Edge operations
	bool exist(int it_vertex_from, int it_vertex_to)const; // finished, tested
	bool exist(Vertex<VDataType, EDataType>* ptr_vertex_from, Vertex<VDataType, EDataType>* ptr_vertex_to)const; // finished, tested
	Vertex<VDataType, EDataType>* insert(int it_vertex_from, int it_vertex_to, const EDataType& edge_data, double edge_weight = .0); // finished, tested
	Vertex<VDataType, EDataType>* insert(Vertex<VDataType, EDataType>* ptr_vertex_from, Vertex<VDataType, EDataType>* ptr_vertex_to,
							  const EDataType& edge_data, double edge_weight = .0); // finished, tested
	EDataType erase(Vertex<VDataType, EDataType>* ptr_vertex_from, Vertex<VDataType, EDataType>* ptr_vertex_to); // finished, tested
	EDataType erase(int it_vertex_from, int it_vertex_to); // finished, tested
	EDataType& edge(Vertex<VDataType, EDataType>* ptr_vertex_from, Vertex<VDataType, EDataType>* ptr_vertex_to)const; // finished, tested
	EDataType& edge(int it_vertex_from, int it_vertex_to)const; // finished, tested

	void show(const string& name = "Graph", bool show_weight = false, const string& layout = "dot")const; // finished, tested
	void write(const string& name = "Graph", bool show_weight = false, const string& layout = "dot")const; // finished, tested

	// Algorithm
	Tree<VDataType*>& get_tree(Vertex<VDataType, EDataType>* vertex);
	Tree<VDataType*>& get_tree();
	Forest<VDataType*>& get_forest(Vertex<VDataType, EDataType>* vertex);
	Forest<VDataType*>& get_forest();

	Forest<VDataType*>& BFS();
	Forest<VDataType*>& BFS(Vertex<VDataType, EDataType>* vertex);
	Forest<VDataType*>& DFS(Vertex<VDataType, EDataType>* vertex);
	Forest<VDataType*>& DFS();
};

#include <graph.cpp>
#endif