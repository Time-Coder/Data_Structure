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
Tree<DataType>::Tree(const BinTree<DataType>& bintree)
{
	if(bintree.empty())
	{
		return;
	}

	if(bintree.root()->rchild)
	{
		cout << "Error when converting Binary Tree to General Tree." << endl
			 << "Current binary tree's root node has right child!" << endl;
		exit(-1);
	}

	_root = new_Node(bintree.root()->data);
	Stack<Node*> dest_stack;
	Stack< typename BinTree<DataType>::Node* > src_stack;

	dest_stack.push(_root);
	src_stack.push(bintree.root());

	while(!src_stack.empty())
	{
		Node* dest_node = dest_stack.pop();
		auto src_node = src_stack.pop();
		if(src_node->lchild)
		{
			src_node = src_node->lchild;
			Node* dest_child_node = new_Node(src_node->data, dest_node);
			dest_node->children.push_back(dest_child_node);
			dest_stack.push(dest_child_node);
			src_stack.push(src_node);
			while(src_node->rchild)
			{
				src_node = src_node->rchild;
				dest_child_node = new_Node(src_node->data, dest_node);
				dest_node->children.push_back(dest_child_node);
				dest_stack.push(dest_child_node);
				src_stack.push(src_node);
			}
		}
	}

	_size = bintree.size();
}

template<class DataType>
Forest<DataType>::Forest(BinTree<DataType> bintree)
{
	typename BinTree<DataType>::Node* node = NULL;

	auto ptr_bintree = &bintree;
	while((node = ptr_bintree->root()->rchild))
	{
		auto ptr_subtree = &(ptr_bintree->secede(node));
		this->push_back(Tree<DataType>(*ptr_bintree));
		delete ptr_bintree;
		ptr_bintree = ptr_subtree;
	}

	this->push_back(Tree<DataType>(*ptr_bintree));
}

template<class DataType>
void ptr_check(DataType*& ptr)
{
	if(!ptr)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
}

template<class DataType>
BinTree<DataType*>& Tree<DataType>::toBinTree()const
{
	BinTree<DataType*>* ptr_bintree = new BinTree<DataType*>;
	if(empty())
	{
		return *ptr_bintree;
	}

	ptr_bintree->_root = new typename BinTree<DataType*>::Node(&(_root->data));
	ptr_check(ptr_bintree->_root);

	Stack<Node*> src_stack;
	Stack<typename BinTree<DataType*>::Node*> dest_stack;

	src_stack.push(_root);
	dest_stack.push(ptr_bintree->_root);

	while(!src_stack.empty())
	{
		Node* src_node = src_stack.pop();
		auto dest_node = dest_stack.pop();

		if(src_node->children.empty())
		{
			continue;
		}

		auto it = src_node->children.begin();
		dest_node->lchild = new typename BinTree<DataType*>::Node(&(_root->data), dest_node);
		ptr_check(dest_node->lchild);
		
		dest_node = dest_node->lchild;

		dest_stack.push(dest_node);
		src_stack.push(*it);

		it++;
		for(; it != src_node->children.end(); it++)
		{
			dest_node->rchild = new typename BinTree<DataType*>::Node(&((*it)->data), dest_node);
			ptr_check(dest_node->rchild);

			dest_node = dest_node->rchild;
			dest_stack.push(dest_node);
			src_stack.push(*it);
		}
	}
	ptr_bintree->_size = _size;

	return *ptr_bintree;
}

template<class DataType>
BinTree<DataType*>& Forest<DataType>::toBinTree()const
{
	BinTree<DataType*>* ptr_main_bintree;
	if(this->empty())
	{
		ptr_main_bintree = new BinTree<DataType*>;
		ptr_check(ptr_main_bintree);
		return *ptr_main_bintree;
	}

	auto it = this->begin();
	BinTree<DataType*>* ptr_bintree = new BinTree<DataType*>(it->toBinTree());
	if(!ptr_bintree)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	ptr_main_bintree = ptr_bintree;
	typename BinTree<DataType*>::Node* node = ptr_main_bintree->root();

	it++;
	for(; it != this->end(); it++)
	{
		ptr_bintree = new BinTree<DataType*>(it->toBinTree());
		if(!ptr_bintree)
		{
			cerr << "Failed to allocate memory!" << endl;
			exit(-1);
		}

		node->rchild = ptr_bintree->_root;
		ptr_bintree->_root->parent = node;
		node = node->rchild;
		ptr_main_bintree->_size += ptr_bintree->_size;
	}

	return *ptr_main_bintree;
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
Tree<DataType>& Tree<DataType>::operator =(const BinTree<DataType>& bintree)
{
	clear();
	Tree<DataType>& ptr_tree = new Tree<DataType>(bintree);
	if(!ptr_tree)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	_root = ptr_tree->_root;
	_size = ptr_tree->_size;

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
void Tree<DataType>::show_content(const string& filename)const
{
	if(!_root)
	{
		cout << "The tree is empty, nothing to show!" << endl;
	}

	write_content(filename);
	system(("dot -Tpdf Figures/" + filename + ".dot -o Figures/" + filename + " && start sumatrapdf Figures/" + filename).data());
}

template<class DataType>
void Tree<DataType>::write_part1(Stack<Node*>& stack_node2,
								 Stack<int>& stack_number2,
								 int n,
								 ofstream& file)const
{
	Stack<Node*> stack_node;
	Stack<int> stack_number;

	stack_node.push(_root);
	stack_number.push(n);

	Node *node;
	int i, j = n + 1;
	while(!stack_node.empty())
	{
		node = stack_node.pop();
		i = stack_number.pop();

		stack_node2.push(node);
		stack_number2.push(i);

		for(typename List<Node*>::iterator it = node->children.begin(); it != node->children.end(); it++, j++)
		{
			file << "\t" << i << "->" << j << ";" << endl;
			stack_node.push(*it);
			stack_number.push(j);
		}
	}
	file << endl;
}

template<class DataType>
void Tree<DataType>::write_part2(Stack<Node*>& stack_node2,
								 Stack<int>& stack_number2,
								 ofstream& file)const
{
	while(!stack_node2.empty())
	{
		auto node = stack_node2.pop();
		int i = stack_number2.pop();
		file << "\t" << i << "[shape=\"circle\",label=\""<< node->data <<"\"];" << endl;
	}
}

template<class DataType>
void Tree<DataType>::write_content_part2(Stack<Node*>& stack_node2,
								 		 Stack<int>& stack_number2,
								 		 ofstream& file)const
{
	while(!stack_node2.empty())
	{
		auto node = stack_node2.pop();
		int i = stack_number2.pop();
		file << "\t" << i << "[shape=\"circle\",label=\""<< *(node->data) <<"\"];" << endl;
	}
}

template<class DataType>
void Tree<DataType>::write(const string& filename)const
{
	ofstream file("Figures/" + filename + ".dot");
	file << "digraph" << endl
		 << "{" << endl;

	Stack<Node*> stack_node2;
	Stack<int> stack_number2;
	
	this->write_part1(stack_node2, stack_number2, 0, file);
	this->write_part2(stack_node2, stack_number2, file);

	file << "}";
	file.close();
}

template<class DataType>
void Tree<DataType>::write_content(const string& filename)const
{
	ofstream file("Figures/" + filename + ".dot");
	file << "graph" << endl
		 << "{" << endl;

	Stack<Node*> stack_node2;
	Stack<int> stack_number2;
	
	this->write_part1(stack_node2, stack_number2, 0, file);
	this->write_content_part2(stack_node2, stack_number2, file);

	file << "}";
	file.close();
}

template<class DataType>
Forest<DataType>& Forest<DataType>::operator =(const BinTree<DataType>& bintree)
{
	this->clear();

	Forest<DataType>* ptr_forest = new Forest<DataType>(bintree);
	if(!ptr_forest)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	this->head = ptr_forest->head;
	this->_rear = ptr_forest->_rear;
	this->length = ptr_forest->length;

	return *this;
}

template<class DataType>
void Forest<DataType>::show(const string& filename)const
{
	if(this->empty())
	{
		cout << "The forest is empty, nothing to show!" << endl;
	}

	write(filename);
	system(("dot -Tpdf Figures/" + filename + ".dot -o Figures/" + filename + " && start sumatrapdf Figures/" + filename).data());
}

template<class DataType>
void Forest<DataType>::show_content(const string& filename)const
{
	if(this->empty())
	{
		cout << "The forest is empty, nothing to show!" << endl;
	}

	write_content(filename);
	system(("dot -Tpdf Figures/" + filename + ".dot -o Figures/" + filename + " && start sumatrapdf Figures/" + filename).data());
}

template<class DataType>
void Forest<DataType>::write(const string& filename)const
{
	if(this->empty())
	{
		cout << "The forest is empty, nothing to write!" << endl;
	}

	ofstream file("Figures/" + filename + ".dot");
	file << "digraph" << endl
		 << "{" << endl;

	Stack<typename Tree<DataType>::Node*> stack_node2;
	Stack<int> stack_number2;
	
	int i = 1;
	for(auto it = this->begin(); it != this->end(); it++)
	{
		if(it->empty())
		{
			continue;
		}
		it->write_part1(stack_node2, stack_number2, i, file);
		i += it->size();
	}
	
	for(auto it = this->begin(); it != this->end(); it++)
	{
		if(it->empty())
		{
			continue;
		}
		it->write_part2(stack_node2, stack_number2, file);
	}

	file << "}";
	file.close();
}

template<class DataType>
void Forest<DataType>::write_content(const string& filename)const
{
	if(this->empty())
	{
		cout << "The forest is empty, nothing to write!" << endl;
	}

	ofstream file("Figures/" + filename + ".dot");
	file << "digraph" << endl
		 << "{" << endl;

	Stack<typename Tree<DataType>::Node*> stack_node2;
	Stack<int> stack_number2;
	
	int i = 1;
	for(auto it = this->begin(); it != this->end(); it++)
	{
		if(it->empty())
		{
			continue;
		}
		it->write_part1(stack_node2, stack_number2, i, file);
		i += it->size();
	}
	
	for(auto it = this->begin(); it != this->end(); it++)
	{
		if(it->empty())
		{
			continue;
		}
		it->write_content_part2(stack_node2, stack_number2, file);
	}

	file << "}";
	file.close();
}

#endif