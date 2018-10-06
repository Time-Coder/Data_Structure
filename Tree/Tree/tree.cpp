#ifdef TREE_H

template<class DataType>
int Tree<DataType>::Node::size()const
{
	if(isleaf())
	{
		return 1;
	}

	int n = 1;
	for(typename List<Node*>::iterator it = children.begin(); it != children.end(); it++)
	{
		n += (*it)->size();
	}
	return n;
}

template<class DataType>
int Tree<DataType>::Node::height()const
{
	if(isleaf())
	{
		return 0;
	}

	typename List<Node*>::iterator it = children.begin();
	int h = (*it)->height();
	it++;

	for(; it != children.end(); it++)
	{
		int h_temp = (*it)->height();
		if(h_temp > h)
		{
			h = h_temp;
		}
	}
	return h + 1;
}

template<class DataType>
int Tree<DataType>::Node::level()const
{
	if(isroot())
	{
		return 0;
	}
	return parent->level() + 1;
}

template<class DataType>
bool Tree<DataType>::Node::isleaf()const
{
	return children.empty();
}

template<class DataType>
bool Tree<DataType>::Node::isroot()const
{
	return !parent;
}

template<class DataType>
bool Tree<DataType>::Node::belong_to(const Tree<DataType>& tree)const
{
	const Node* node = this;
	while(node->parent)
	{
		node = node->parent;
	}

	return (node == tree._root);
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::Node::append_child(const DataType& value)
{
	Node* node = new_Node(value, this);
	children.push_back(node);
	return node;
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::Node::insert_child(int i, const DataType& value)
{
	Node* node = new_Node(value, this);
	children.insert(i, node);
	return node;
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::new_Node(const DataType& value, Node* parent)
{
	Node* node = new Node(value, parent);
	if(!node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return node;
}

template<class DataType>
Tree<DataType>::Tree(const Tree<DataType>& tree)
{
	if(!(tree._root))
	{
		return;
	}

	_root = new_Node(tree._root->data);

	Stack<Node*> src_stack, dest_stack;
	src_stack.push(tree._root);
	dest_stack.push(_root);

	while(!src_stack.empty())
	{
		Node* src_node = src_stack.pop();
		Node* dest_node = dest_stack.pop();
		typename List<Node*>::iterator it;
		for(it = src_node->children.begin(); it != src_node->children.end(); it++)
		{
			Node* node_temp = new_Node((*it)->data, dest_node);
			dest_node->children.push_back(node_temp);
			src_stack.push(*it);
			dest_stack.push(node_temp);
		}
	}
	_size = tree._size;
}

template<class DataType>
Tree<DataType>::~Tree()
{
	clear();
}

template<class DataType>
void Tree<DataType>::clear()
{
	if(!_root)
	{
		return;
	}

	Stack<Node*> stack;
	stack.push(_root);
	while(!stack.empty())
	{
		Node* node = stack.pop();
		while(!(node->children.empty()))
		{
			stack.push(node->children.pop_back());
		}
		delete node;
	}

	_root = NULL;
	_size = 0;
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::insert_root(const DataType& value)
{
	if(_root)
	{
		cout << "Warning in 'Node* Tree<DataType>::insert_root(const DataType& value)'" << endl
			 << "Current tree already has root node." << endl
			 << "Nothing has been done and return NULL" << endl;
		return NULL;
	}

	_root = new_Node(value);
	_size++;

	return _root;
}

template<class DataType>
bool Tree<DataType>::bad_node(Node* node, const string& message, const string& function_name)
{
	if(!node)
	{
		cout << message << " in '" << function_name << "'" << endl
			 << "node is NULL" << endl
			 << "Nothing has been done and return NULL" << endl;
		return true;
	}
	if(!(node->belong_to(*this)))
	{
		cout << message << " in '" << function_name << "'" << endl
			 << "Current Tree dosen't have this node!" << endl
			 << "Nothing has been done and return NULL" << endl;
		return true;
	}

	return false;
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::append_child(Node* node, const DataType& value)
{
	if(bad_node(node, "Warning", "Node* Tree<DataType>::append_child(Node* node, const DataType& value)"))
	{
		return NULL;
	}

	Node* new_node = new_Node(value, node);
	node->children.push_back(new_node);
	_size++;

	return new_node;
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::insert_child(Node* node, int i, const DataType& value)
{
	if(bad_node(node, "Warning", "Node* Tree<DataType>::append_child(Node* node, const DataType& value)"))
	{
		return NULL;
	}

	Node* new_node = new_Node(value, node);
	node->children.insert(i, new_node);
	_size++;

	return new_node;
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::attach(Node* node, const Tree<DataType>& tree)
{
	if(!(tree._root))
	{
		cout << "Warning in 'Node* Tree<DataType>::attach(Node* node, const Tree<DataType>& tree)'" << endl
			 << "The tree is empty." << endl
			 << "Nothing has been done and return NULL" << endl;
		return NULL;
	}

	if(bad_node(node, "Warning", "Node* Tree<DataType>::attach(Node* node, const Tree<DataType>& tree)"))
	{
		return NULL;
	}

	Tree* ptr_temp_tree = new Tree(tree);
	if(!ptr_temp_tree)
	{
		cout << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	ptr_temp_tree->_root->parent = node;
	node->children.push_back(ptr_temp_tree->_root);
	_size += tree._size;

	return ptr_temp_tree->_root;
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::attach(Node* node, int i, const Tree<DataType>& tree)
{
	if(!(tree._root))
	{
		cout << "Warning in 'Node* Tree<DataType>::attach(Node* node, const Tree<DataType>& tree)'" << endl
			 << "The tree is empty." << endl
			 << "Nothing has been done and return NULL" << endl;
		return NULL;
	}

	if(bad_node(node, "Warning", "Node* Tree<DataType>::attach(Node* node, const Tree<DataType>& tree)"))
	{
		return NULL;
	}

	Tree* ptr_temp_tree = new Tree(tree);
	if(!ptr_temp_tree)
	{
		cout << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	ptr_temp_tree->_root->parent = node;
	node->children.insert(i, ptr_temp_tree->_root);
	_size += tree._size;

	return ptr_temp_tree->_root;
}

template<class DataType>
int Tree<DataType>::remove(Node* node)
{
	if(bad_node(node, "Warning", "int Tree<DataType>::remove(Node* node)"))
	{
		return 0;
	}

	Tree<DataType> tree;
	tree._root = new Node(*node);
	if(!(tree._root))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	tree._size = tree._root->size();
	_size -= tree._size;

	node->parent->children.erase(node->parent->children.find(node));
	return tree._size;
}

template<class DataType>
Tree<DataType>& Tree<DataType>::secede(Node* node)
{
	if(bad_node(node, "Error", "Tree<DataType>& Tree<DataType>::secede(Node* node)"))
	{
		exit(-1);
	}

	Tree<DataType> *tree;
	tree->_root = new Node(*node);
	if(!(tree->_root))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	tree->_root->parent = NULL;
	tree->_size = tree->_root->size();
	_size -= tree->_size;

	node->parent->children.erase(node->parent->children.find(node));

	return *tree;
}

template<class DataType>
Tree<DataType> Tree<DataType>::subtree(Node* node)
{
	if(!node)
	{
		cout << "Error in 'Tree<DataType>& Tree<DataType>::subtree(Node* node)'" << endl
			 << "The node is NULL" << endl;
		exit(-1);
	}

	Tree<DataType> *tree;
	tree->_root = new Node(*node);
	if(!(tree->_root))
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
	tree->_root->parent = NULL;
	tree->_size = tree->_root->size();

	return *tree;
}

template<class DataType>
Tree<DataType>& Tree<DataType>::operator =(const Tree<DataType>& tree)
{
	clear();
	Tree<DataType> *ptr_tree = new Tree<DataType>(tree);
	_root = ptr_tree->_root;
	_size = tree._size;

	return *this;
}

template<class DataType>
void Tree<DataType>::show(const string& filename)const
{
	if(!_root)
	{
		cout << "The tree is empty, nothing to show!" << endl;
	}

	write(filename);
	system(("dot -Tpdf Figures/" + filename + ".dot -o Figures/" + filename + " && start sumatrapdf Figures/" + filename).data());
}

template<class DataType>
void Tree<DataType>::write(const string& filename)const
{
	ofstream file("Figures/" + filename + ".dot");
	file << "graph" << endl
		 << "{" << endl;

	Stack<Node*> stack_node, stack_node2;
	Stack<int> stack_number, stack_number2;
	stack_node.push(_root);
	stack_number.push(0);

	Node *node;
	int i, j = 1;
	while(!stack_node.empty())
	{
		node = stack_node.pop();
		i = stack_number.pop();

		stack_node2.push(node);
		stack_number2.push(i);

		for(typename List<Node*>::iterator it = node->children.begin(); it != node->children.end(); it++, j++)
		{
			file << "\t" << i << "--" << j << ";" << endl;
			stack_node.push(*it);
			stack_number.push(j);
		}
	}

	file << endl;

	while(!stack_node2.empty())
	{
		node = stack_node2.pop();
		i = stack_number2.pop();
		file << "\t" << i << "[shape=\"circle\",label=\""<< node->data <<"\"];" << endl;
	}
	file << "}";
	file.close();
}

#endif