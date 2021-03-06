#ifdef GRAPH_H

template<class DataType>
void ptr_check(const DataType*& ptr)
{
	if(!ptr)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
}

// Graph information
template<class VDataType, class EDataType>
int DiGraph<VDataType, EDataType>::n_vertice()const
{
	return vertex_list.size();
}

template<class VDataType, class EDataType>
int DiGraph<VDataType, EDataType>::n_edges()const
{
	return _n_edges;
}

template<class VDataType, class EDataType>
bool DiGraph<VDataType, EDataType>::empty()const
{
	return vertex_list.empty();
}

// Vertex operations
template<class VDataType, class EDataType>
bool DiGraph<VDataType, EDataType>::exist(Vertex<VDataType, EDataType>* ptr_vertex)const
{
	return (vertex_list.locate(ptr_vertex) != -1);
}

template<class VDataType, class EDataType>
bool DiGraph<VDataType, EDataType>::exist(int it_vertex)const
{
	return (it_vertex >= 0 && it_vertex < vertex_list.size());
}

template<class VDataType, class EDataType>
Vertex<VDataType, EDataType>* DiGraph<VDataType, EDataType>::insert(const VDataType& v)
{
	vertex_list.push_back(Vertex<VDataType, EDataType>(v));
	return vertex_list.rear().ptr();
}

template<class VDataType, class EDataType>
VDataType DiGraph<VDataType, EDataType>::erase(Vertex<VDataType, EDataType>* ptr_vertex)
{
	if(!exist(ptr_vertex))
	{
		cout << "Warning in 'VDataType DiGraph<VDataType, EDataType>::erase(Vertex<VDataType, EDataType>* ptr_vertex)'" << endl
			 << "Current graph dosen't has this vertex" << endl
			 << "Nothing has been done and return nan" << endl;
		return numeric_limits<VDataType>::quiet_NaN();
	}

	VDataType vertex_data = ptr_vertex->_data;
	for(auto it_vertex = vertex_list.begin(); it_vertex != vertex_list.end(); it_vertex++)
	{
		for(auto it_edge = it_vertex->adjacency_list.begin();
			it_edge != it_vertex->adjacency_list.end(); it_edge++)
		{
			if(it_edge->_ptr_vertex_to == ptr_vertex)
			{
				it_vertex->adjacency_list.erase(it_edge);
				it_vertex->_out_deg--;
				_n_edges--;
				break;
			}
		}
	}
	_n_edges -= ptr_vertex->out_deg();
	vertex_list.erase(ptr_vertex);

	return vertex_data;
}

template<class VDataType, class EDataType>
VDataType DiGraph<VDataType, EDataType>::erase(int it_vertex)
{
	return erase(&vertex_list[it_vertex]);
}

template<class VDataType, class EDataType>
VDataType& DiGraph<VDataType, EDataType>::vertex(Vertex<VDataType, EDataType>* ptr_vertex)const
{
	if(!exist(ptr_vertex))
	{
		cout << "Error in 'VDataType& DiGraph<VDataType, EDataType>::vertex(Vertex<VDataType, EDataType>* ptr_vertex)'" << endl
			 << "Current graph dosen't has this vertex!" << endl;
		exit(-1);
	}
	return ptr_vertex->_data;
}

template<class VDataType, class EDataType>
VDataType& DiGraph<VDataType, EDataType>::vertex(int it_vertex)const
{
	return vertex_list[it_vertex]._data;
}

template<class VDataType, class EDataType>
int DiGraph<VDataType, EDataType>::in_deg(int it_vertex)const
{
	return vertex_list[it_vertex].in_deg();
}

template<class VDataType, class EDataType>
int DiGraph<VDataType, EDataType>::in_deg(Vertex<VDataType, EDataType>* ptr_vertex)const
{
	if(!exist(ptr_vertex))
	{
		cout << "Error in 'int DiGraph<VDataType, EDataType>::in_deg(Vertex<VDataType, EDataType>* ptr_vertex)'" << endl
			 << "Current graph dosen't has this vertex!" << endl;
		exit(-1);
	}
	return ptr_vertex->in_deg();
}

template<class VDataType, class EDataType>
int DiGraph<VDataType, EDataType>::out_deg(int it_vertex)const
{
	return vertex_list[it_vertex].out_deg();
}

template<class VDataType, class EDataType>
int DiGraph<VDataType, EDataType>::out_deg(Vertex<VDataType, EDataType>* ptr_vertex)const
{
	if(!exist(ptr_vertex))
	{
		cout << "Warning in 'int DiGraph<VDataType, EDataType>::out_deg(Vertex<VDataType, EDataType>* ptr_vertex)'" << endl
			 << "Current graph dosen't has this vertex!" << endl;
		return -1;
	}
	return ptr_vertex->out_deg();
}

// Edge operations
template<class VDataType, class EDataType>
bool DiGraph<VDataType, EDataType>::exist(int it_vertex_from, int it_vertex_to)const
{
	Vertex<VDataType, EDataType>* ptr_vertex_dest = vertex_list[it_vertex_to];
	for(auto it = vertex_list[it_vertex_from].adjacency_list.begin();
		it != vertex_list[it_vertex_from].adjacency_list.end(); it++)
	{
		if(it->_ptr_vertex_to == ptr_vertex_dest)
		{
			return true;
		}
	}

	return false;
}

template<class VDataType, class EDataType>
bool DiGraph<VDataType, EDataType>::exist(Vertex<VDataType, EDataType>* ptr_vertex_from,
		   Vertex<VDataType, EDataType>* ptr_vertex_to)const
{
	if(!exist(ptr_vertex_from))
	{
		return false;
	}
	for(auto it = ptr_vertex_from->adjacency_list.begin(); it != ptr_vertex_from->adjacency_list.end(); it++)
	{
		if(it->_ptr_vertex_to == ptr_vertex_to)
		{
			return true;
		}
	}
	return false;
}

template<class VDataType, class EDataType>
Vertex<VDataType, EDataType>* DiGraph<VDataType, EDataType>::insert(int it_vertex_from, int it_vertex_to,
									  const EDataType& edge_data, double edge_weight)
{
	if(exist(it_vertex_from, it_vertex_to))
	{
		cout << "Warning in function:" << endl
			 << "'void DiGraph<VDataType, EDataType>::insert(int, int, const EDataType&, double)'" << endl
			 << "Current graph already has this edge, nothing has been done." << endl;

		return NULL;
	}

	vertex_list[it_vertex_from].adjacency_list.push_back
	(
		Edge<VDataType, EDataType>(&vertex_list[it_vertex_to], edge_data, edge_weight)
	);
	vertex_list[it_vertex_from]._out_deg++;
	vertex_list[it_vertex_to]._in_deg++;
	_n_edges++;
	return &vertex_list[it_vertex_from];
}

template<class VDataType, class EDataType>
Vertex<VDataType, EDataType>* DiGraph<VDataType, EDataType>::insert(Vertex<VDataType, EDataType>* ptr_vertex_from,
										   Vertex<VDataType, EDataType>* ptr_vertex_to,
										   const EDataType& edge_data, double edge_weight)
{
	if( !(exist(ptr_vertex_from) && exist(ptr_vertex_to)) )
	{
		cout << "Warning in 'Vertex* DiGraph::insert(Vertex*, Vertex*, const EDataType&, double)'" << endl
			 << "Current graph dosen't has one of these vertice!" << endl
			 << "Nothing has been done!" << endl;
		return NULL;
	}

	if(exist(ptr_vertex_from, ptr_vertex_to))
	{
		cout << "Warning in function:" << endl
			 << "'void DiGraph<VDataType, EDataType>::insert" << endl
			 <<	"(" << endl
			 <<	"	Vertex<VDataType, EDataType>* ptr_vertex_from," << endl
			 <<	"	Vertex<VDataType, EDataType>* ptr_vertex_to," << endl
			 <<	"	const EDataType& edge_data, double edge_weight" << endl
			 <<	")'" << endl
			 << "Current graph already has this edge, nothing has been done." << endl;

		return NULL;
	}

	ptr_vertex_from->adjacency_list.push_back
	(
		Edge<VDataType, EDataType>(ptr_vertex_to, edge_data, edge_weight)
	);
	ptr_vertex_from->_out_deg++;
	ptr_vertex_to->_in_deg++;

	_n_edges++;

	return ptr_vertex_from;
}

template<class VDataType, class EDataType>
EDataType DiGraph<VDataType, EDataType>::erase(Vertex<VDataType, EDataType>* ptr_vertex_from,
											   Vertex<VDataType, EDataType>* ptr_vertex_to)
{
	if(!exist(ptr_vertex_from))
	{
		cout << "Warning in 'EDataType DiGraph::erase(Vertex* ptr_vertex_from, Vertex* ptr_vertex_to)'" << endl
			 << "Current Graph dosen't have vertex:ptr_vertex_from." << endl
			 << "Nothing has been done and return nan." << endl;
		return numeric_limits<EDataType>::quiet_NaN();
	}

	for(auto it = ptr_vertex_from->adjacency_list.begin();
		it != ptr_vertex_from->adjacency_list.end(); it++)
	{
		if(it->_ptr_vertex_to == ptr_vertex_to)
		{
			EDataType edge_data = it->_data;
			ptr_vertex_from->adjacency_list.erase(it);
			_n_edges--;
			return edge_data;
		}
	}

	cout << "Warning in 'EDataType DiGraph::erase(Vertex* ptr_vertex_from, Vertex* ptr_vertex_to)'" << endl
		 << "Current Graph dosen't have this edge." << endl
		 << "Nothing has been done and return nan." << endl;
	return numeric_limits<EDataType>::quiet_NaN();
}

template<class VDataType, class EDataType>
EDataType DiGraph<VDataType, EDataType>::erase(int it_vertex_from, int it_vertex_to)
{
	Vertex<VDataType, EDataType>* ptr_vertex_to = &vertex_list[it_vertex_to];
	for(auto it = vertex_list[it_vertex_from]->adjacency_list.begin();
		it != vertex_list[it_vertex_from]->adjacency_list.end(); it++)
	{
		if(it->_ptr_vertex_to == ptr_vertex_to)
		{
			EDataType edge_data = it->_data;
			vertex_list[it_vertex_from]->adjacency_list.erase(it);
			_n_edges--;
			return edge_data;
		}
	}

	cout << "Warning in function:" << endl
		 << "'EDataType& DiGraph<VDataType, EDataType>::erase(int, int)'" << endl
		 << "Current Graph dosen't have this edge!" << endl
		 << "Nothing has been done and return nan." << endl;
	return numeric_limits<EDataType>::quiet_NaN();
}

template<class VDataType, class EDataType>
EDataType& DiGraph<VDataType, EDataType>::edge(Vertex<VDataType, EDataType>* ptr_vertex_from,
											   Vertex<VDataType, EDataType>* ptr_vertex_to)const
{
	if(!exist(ptr_vertex_from))
	{
		cout << "Error in 'EDataType DiGraph::erase(Vertex* ptr_vertex_from, Vertex* ptr_vertex_to)'" << endl
			 << "Current Graph dosen't have vertex:ptr_vertex_from" << endl;
		exit(-1);
	}

	for(auto it = ptr_vertex_from->adjacency_list.begin();
		it != ptr_vertex_from->adjacency_list.end(); it++)
	{
		if(it->_ptr_vertex_to == ptr_vertex_to)
		{
			return it->_data;
		}
	}

	cout << "Error in function:" << endl
		 << "'EDataType& DiGraph<VDataType, EDataType>::edge(Vertex<VDataType, EDataType>* ptr_vertex_from," << endl
		 <<	"								   				 Vertex<VDataType, EDataType>* ptr_vertex_to)'" << endl
		 << "Current Graph dosen't have this edge!" << endl;
	exit(-1);
}

template<class VDataType, class EDataType>
EDataType& DiGraph<VDataType, EDataType>::edge(int it_vertex_from, int it_vertex_to)const
{
	Vertex<VDataType, EDataType>* ptr_vertex_to = &vertex_list[it_vertex_to];
	for(auto it = vertex_list[it_vertex_from]->adjacency_list.begin();
		it != vertex_list[it_vertex_from]->adjacency_list.end(); it++)
	{
		if(it->_ptr_vertex_to == ptr_vertex_to)
		{
			return it->_data;
		}
	}

	cout << "Error in function:" << endl
		 << "'EDataType& DiGraph<VDataType, EDataType>::edge(int, int)'" << endl
		 << "Current Graph dosen't have this edge!" << endl;
	exit(-1);
}

template<class VDataType, class EDataType>
void DiGraph<VDataType, EDataType>::show(const string& name, bool show_weight, const string& layout)const
{
	if(empty())
	{
		cout << "The Graph is empty, nothing to show!" << endl;
		return;
	}
	write(name, show_weight, layout);
	system(("start sumatrapdf Figures/" + name).data());
}

template<class VDataType, class EDataType>
void DiGraph<VDataType, EDataType>::write(const string& name, bool show_weight, const string& layout)const
{
	if(empty())
	{
		cout << "The Graph is empty, nothing to write!" << endl;
		return;
	}
	ofstream file(("Figures/" + name + ".dot").data());
	file << "digraph" << endl
		 << "{" << endl;

	typename List< Vertex<VDataType, EDataType> >::iterator it_vertex;
	int i;
	if(!show_weight)
	{
		typename List< Vertex<VDataType, EDataType> >::iterator it_vertex_next;
		int j;
		for(it_vertex = vertex_list.begin(), i = 0; it_vertex != vertex_list.end(); it_vertex++, i++)
		{
			for(it_vertex_next = it_vertex, j = i; it_vertex_next != vertex_list.end(); it_vertex_next++, j++)
			{
				bool flag_out = exist(it_vertex.ptr(), it_vertex_next.ptr());
				bool flag_in  = exist(it_vertex_next.ptr(), it_vertex.ptr());
				if(flag_out && flag_in)
				{
					file << "\t" << i << "->" << j << "[dir=\"both\"];" << endl;
				}
				else if(flag_out)
				{
					file << "\t" << i << "->" << j << ";" << endl;
				}
				else if(flag_in)
				{
					file << "\t" << j << "->" << i << ";" << endl;
				}
			}
		}
	}
	else
	{
		typename List< Edge<VDataType, EDataType> >::iterator it_edge;
		for(it_vertex = vertex_list.begin(), i = 0; it_vertex != vertex_list.end(); it_vertex++, i++)
		{
			for(it_edge = it_vertex->adjacency_list.begin();
				it_edge != it_vertex->adjacency_list.end(); it_edge++)
			{
				file << "\t" << i << "->" << vertex_list.locate(it_edge->_ptr_vertex_to)
					 << "[label=\"" << it_edge->_weight << "\"];" << endl;
			}
		}
	}

	file << endl;
	for(it_vertex = vertex_list.begin(), i = 0; it_vertex != vertex_list.end(); it_vertex++, i++)
	{
		file << "\t" << i << "[shape=\"circle\",label=\"" << it_vertex->_data << "\"];" << endl;
	}
	file << "}";
	file.close();

	system((layout + " -Tpdf Figures/" + name + ".dot -o Figures/" + name).data());
}

template<class VDataType, class EDataType>
void DiGraph<VDataType, EDataType>::reset()
{
	for(auto it_vertex = vertex_list.begin(); it_vertex != vertex_list.end(); it_vertex++)
	{
		it_vertex->status = Vertex<VDataType, EDataType>::UNDISCOVERED;
		it_vertex->discover_time = 0;
		it_vertex->finish_time = 0;
		it_vertex->got = false;

		for(auto it_edge = it_vertex->adjacency_list.begin();
			it_edge != it_vertex->adjacency_list.end(); it_edge++)
		{
			it_edge->type = Edge<VDataType, EDataType>::UNDETERMINED;
		}
	}
}

template<class VDataType, class EDataType>
Tree<VDataType*>& DiGraph<VDataType, EDataType>::bfs(Vertex<VDataType, EDataType>* vertex)
{
	Tree<VDataType*>* ptr_tree = new Tree<VDataType*>;
	auto tree_node = ptr_tree->insert_root(&(vertex->_data));

	Queue< Vertex<VDataType, EDataType>* > queue_vertex;
	Queue< typename Tree<VDataType*>::Node* > queue_node;
	queue_vertex.push(vertex);
	queue_node.push(tree_node);

	while(!queue_vertex.empty())
	{
		vertex = queue_vertex.pop();
		tree_node = queue_node.pop();
		for(auto it_edge = vertex->adjacency_list.begin();
			it_edge != vertex->adjacency_list.end(); it_edge++)
		{
			if(Vertex<VDataType, EDataType>::UNDISCOVERED == it_edge->_ptr_vertex_to->status)
			{
				it_edge->_ptr_vertex_to->status = Vertex<VDataType, EDataType>::DISCOVERED;
				queue_vertex.push(it_edge->_ptr_vertex_to);
				queue_node.push( ptr_tree->append_child(tree_node, &(it_edge->_ptr_vertex_to->_data)) );
				it_edge->type = Edge<VDataType, EDataType>::TREE;
			}
			else
			{
				it_edge->type = Edge<VDataType, EDataType>::CROSS;
			}
		}
		vertex->status = Vertex<VDataType, EDataType>::VISITED;
	}

	return *ptr_tree;
}

template<class VDataType, class EDataType>
Forest<VDataType*>& DiGraph<VDataType, EDataType>::BFS(Vertex<VDataType, EDataType>* vertex)
{
	Forest<VDataType*>* ptr_forest = new Forest<VDataType*>;
	ptr_check(ptr_forest);

	if(empty())
	{
		cout << "Warning in 'Forest<VDataType*>& DiGraph<VDataType, EDataType>::BFS(Vertex<VDataType, EDataType>* vertex)'" << endl
			 << "Current Graph is empty. Return an empty tree." << endl;
		return *ptr_forest;
	}

	if(!exist(vertex))
	{
		cout << "Warning in 'Forest<VDataType*>& DiGraph<VDataType, EDataType>::BFS(Vertex<VDataType, EDataType>* vertex)'" << endl
			 << "Current Graph dosen't has this vertex. Return an empty tree." << endl;
		return *ptr_forest;
	}

	reset();

	typename List< Vertex<VDataType, EDataType> >::iterator it0 = vertex_list.locate(vertex_list.locate(vertex));
	auto it_vertex = it0;

	do
	{
		if(Vertex<VDataType, EDataType>::UNDISCOVERED == it_vertex->status)
		{
			ptr_forest->push_back(bfs(it_vertex.ptr()));
		}

		it_vertex++;
		if(it_vertex == vertex_list.end())
		{
			it_vertex = vertex_list.begin();
		}
	}
	while(it_vertex != it0);

	return *ptr_forest;
}

template<class VDataType, class EDataType>
Forest<VDataType*>& DiGraph<VDataType, EDataType>::BFS()
{
	return BFS(&vertex_list[0]);
}

template<class VDataType, class EDataType>
void DiGraph<VDataType, EDataType>::dfs(Vertex<VDataType, EDataType>* vertex, int& clock)
{
	vertex->status = Vertex<VDataType, EDataType>::DISCOVERED;
	vertex->discover_time = ++clock;
	for(auto it_edge = vertex->adjacency_list.begin();
		it_edge != vertex->adjacency_list.end(); it_edge++)
	{
		switch(it_edge->_ptr_vertex_to->status)
		{
			case Vertex<VDataType, EDataType>::UNDISCOVERED:
			{
				it_edge->_ptr_vertex_to->discover_time = ++clock;
				it_edge->type = Edge<VDataType, EDataType>::TREE;
				dfs(it_edge->_ptr_vertex_to, clock);

				break;
			}

			case Vertex<VDataType, EDataType>::DISCOVERED:
			{
				it_edge->type = Edge<VDataType, EDataType>::BACKWARD;
				break;
			}

			default:
			{
				it_edge->type = vertex->discover_time < it_edge->_ptr_vertex_to->discover_time ? 
								Edge<VDataType, EDataType>::FORWARD : Edge<VDataType, EDataType>::CROSS;
			}
		}
	}
	vertex->status = Vertex<VDataType, EDataType>::VISITED;
	vertex->finish_time = ++clock;
}

template<class VDataType, class EDataType>
Tree<VDataType*>& DiGraph<VDataType, EDataType>::get_tree(Vertex<VDataType, EDataType>* vertex)
{
	Tree<VDataType*>* ptr_tree = new Tree<VDataType*>;
	ptr_check(ptr_tree);

	if(empty())
	{
		cout << "Warning in 'Tree<VDataType*>& DiGraph<VDataType, EDataType>::get_tree(Vertex<VDataType, EDataType>* vertex)'" << endl
			 << "Current Graph is empty. Return an empty tree." << endl;
		return *ptr_tree;
	}

	if(!exist(vertex))
	{
		cout << "Warning in 'Tree<VDataType*>& DiGraph<VDataType, EDataType>::get_tree(Vertex<VDataType, EDataType>* vertex)'" << endl
			 << "Current Graph dosen't has this vertex. Return an empty tree." << endl;
		return *ptr_tree;
	}

	ptr_tree->insert_root(&(vertex->_data));
	Queue< Vertex<VDataType, EDataType>* > queue_vertex;
	Queue< typename Tree<VDataType*>::Node* > queue_node;
	queue_vertex.push(vertex);
	queue_node.push(ptr_tree->root());

	while(!queue_vertex.empty())
	{
		auto ptr_vertex = queue_vertex.pop();
		ptr_vertex->got = true;
		auto ptr_node = queue_node.pop();
		for(auto it_edge = ptr_vertex->adjacency_list.begin();
			it_edge != ptr_vertex->adjacency_list.end(); it_edge++)
		{
			if(Edge<VDataType, EDataType>::TREE == it_edge->type)
			{
				queue_node.push( ptr_tree->append_child(ptr_node, &(it_edge->_ptr_vertex_to->_data)) );
				queue_vertex.push(it_edge->_ptr_vertex_to);
			}
		}
	}

	return *ptr_tree;
}

template<class VDataType, class EDataType>
Tree<VDataType*>& DiGraph<VDataType, EDataType>::get_tree()
{
	return get_tree(&vertex_list[0]);
}

template<class VDataType, class EDataType>
Forest<VDataType*>& DiGraph<VDataType, EDataType>::get_forest(Vertex<VDataType, EDataType>* vertex)
{
	Forest<VDataType*>* ptr_forest = new Forest<VDataType*>;
	ptr_check(ptr_forest);

	if(empty())
	{
		cout << "Warning in 'Forest<VDataType*>& DiGraph<VDataType, EDataType>::get_forest(Vertex<VDataType, EDataType>* vertex)'" << endl
			 << "Current Graph is empty. Return an empty tree." << endl;
		return *ptr_forest;
	}

	if(!exist(vertex))
	{
		cout << "Warning in 'Forest<VDataType*>& DiGraph<VDataType, EDataType>::get_forest(Vertex<VDataType, EDataType>* vertex)'" << endl
			 << "Current Graph dosen't has this vertex. Return an empty tree." << endl;
		return *ptr_forest;
	}

	auto it0 = vertex_list.locate(vertex_list.locate(vertex));
	auto it_vertex = it0;

	do
	{
		Tree<VDataType*> tree;
		if(!(it_vertex->got))
		{
			tree = get_tree(it_vertex.ptr());
			ptr_forest->push_back(tree);
		}

		it_vertex++;
		if(it_vertex == vertex_list.end())
		{
			it_vertex = vertex_list.begin();
		}
	}
	while(it_vertex != it0);

	for(it_vertex = vertex_list.begin(); it_vertex != vertex_list.end(); it_vertex++)
	{
		it_vertex->got = false;
	}

	return *ptr_forest;
}

template<class VDataType, class EDataType>
Forest<VDataType*>& DiGraph<VDataType, EDataType>::get_forest()
{
	return get_forest(&vertex_list[0]);
}

template<class VDataType, class EDataType>
Forest<VDataType*>& DiGraph<VDataType, EDataType>::DFS(Vertex<VDataType, EDataType>* vertex)
{
	Forest<VDataType*>* ptr_forest = new Forest<VDataType*>;
	ptr_check(ptr_forest);

	if(empty())
	{
		cout << "Warning in 'Forest<VDataType*>& DiGraph<VDataType, EDataType>::DFS(Vertex<VDataType, EDataType>* vertex)'" << endl
			 << "Current Graph is empty. Return an empty tree." << endl;
		return *ptr_forest;
	}

	if(!exist(vertex))
	{
		cout << "Warning in 'Forest<VDataType*>& DiGraph<VDataType, EDataType>::DFS(Vertex<VDataType, EDataType>* vertex)'" << endl
			 << "Current Graph dosen't has this vertex. Return an empty tree." << endl;
		return *ptr_forest;
	}

	reset();

	int clock = 0;
	typename List< Vertex<VDataType, EDataType> >::iterator it0 = vertex_list.locate(vertex_list.locate(vertex));
	auto it_vertex = it0;

	do
	{
		if(Vertex<VDataType, EDataType>::UNDISCOVERED == it_vertex->status)
		{
			dfs(it_vertex.ptr(), clock);
			Tree<VDataType*> tree = get_tree(it_vertex.ptr());
			ptr_forest->push_back(tree);
		}
		
		it_vertex++;
		if(it_vertex == vertex_list.end())
		{
			it_vertex = vertex_list.begin();
		}
	}
	while(it_vertex != it0);

	return *ptr_forest;
}

template<class VDataType, class EDataType>
Forest<VDataType*>& DiGraph<VDataType, EDataType>::DFS()
{
	return DFS(&vertex_list[0]);
}

#endif