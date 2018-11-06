#ifdef TREE_H

template<class DataType>
int Tree<DataType>::size(const Node* node)
{
	if(!node)
	{
		return 0;
	}

	int n = 1;
	for(typename List<Node*>::iterator it = node->children.begin(); it != node->children.end(); it++)
	{
		n += size(*it);
	}
	return n;
}

template<class DataType>
int Tree<DataType>::height(const Node* node)
{
	if(!node)
	{
		return -1;
	}

	typename List<Node*>::iterator it = node->children.begin();
	int h = height(*it);
	it++;

	for(; it != node->children.end(); it++)
	{
		int h_temp = height(*it);
		if(h_temp > h)
		{
			h = h_temp;
		}
	}
	return h + 1;
}

template<class DataType>
int Tree<DataType>::depth(const Node* node)
{
	int d = -1;
	while(node)
	{
		d++;
		node = node->parent;
	}

	return d;
}

template<class DataType>
bool Tree<DataType>::isleaf(const Node* node)
{
	return node && node->children.empty();
}

template<class DataType>
bool Tree<DataType>::isroot(const Node* node)
{
	return node && !(node->parent);
}

template<class DataType>
typename Tree<DataType>::Node* Tree<DataType>::Node::append_child(const DataType& value)
{
	Node* node = new_Node(value, this);
	children.push_back(node);
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
void Tree<DataType>::copy_from(const Tree<DataType>& tree)
{
	if(!(tree._root))
	{
		return;
	}

	_root = new_Node(tree._root->data);

	Queue<Node*> src_queue, dest_queue;
	src_queue.push(tree._root);
	dest_queue.push(_root);

	while(!src_queue.empty())
	{
		Node* src_node = src_queue.pop();
		Node* dest_node = dest_queue.pop();
		typename List<Node*>::iterator it;
		for(it = src_node->children.begin(); it != src_node->children.end(); it++)
		{
			Node* node_temp = new_Node((*it)->data, dest_node);
			dest_node->children.push_back(node_temp);
			src_queue.push(*it);
			dest_queue.push(node_temp);
		}
	}
	_size = tree._size;
}

template<class DataType>
Tree<DataType>::Tree(const Tree<DataType>& tree)
{
	copy_from(tree);
}

template<class DataType>
Tree<DataType>::Tree(Tree<DataType>&& tree)
{
	*this = move(tree);
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
		exit(-3);
	}

	_root = new_Node(bintree.root()->data);
	Queue<Node*> dest_queue;
	Queue< typename BinTree<DataType>::Node* > src_queue;

	dest_queue.push(_root);
	src_queue.push(bintree.root());

	while(!src_queue.empty())
	{
		Node* dest_node = dest_queue.pop();
		auto src_node = src_queue.pop();
		if(src_node->lchild)
		{
			src_node = src_node->lchild;
			Node* dest_child_node = new_Node(src_node->data, dest_node);
			dest_node->children.push_back(dest_child_node);
			dest_queue.push(dest_child_node);
			src_queue.push(src_node);
			while(src_node->rchild)
			{
				src_node = src_node->rchild;
				dest_child_node = new_Node(src_node->data, dest_node);
				dest_node->children.push_back(dest_child_node);
				dest_queue.push(dest_child_node);
				src_queue.push(src_node);
			}
		}
	}

	_size = bintree.size();
}

template<class DataType>
Forest<DataType>::Forest(const BinTree<DataType>& bintree)
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
bool Tree<DataType>::has_node(const Node& node)const
{
	auto p_node = &node;
	while(p_node->parent)
	{
		p_node = p_node->parent;
	}

	return (p_node == _root);
}

template<class DataType>
bool Tree<DataType>::has_node(Node* node)const
{
	if(!node)
	{
		return false;
	}

	while(node->parent)
	{
		node = node->parent;
	}
	return (node == _root);
}

template<class DataType>
template<class ElemType>
void Tree<DataType>::check_ptr(const ElemType* ptr)
{
	if(!ptr)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
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

	Queue<Node*> queue;
	queue.push(_root);
	while(!queue.empty())
	{
		Node* node = queue.pop();
		while(!(node->children.empty()))
		{
			queue.push(node->children.pop_back());
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
	if(!(this->has_node(node)))
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

	// 定义局部变量 tree，函数返回时，局部变量自动销毁
	Tree<DataType> tree;
	tree._root = node;
	tree._size = size(tree._root);
	_size -= tree._size;

	if(node == _root)
	{
		_root = NULL;
	}
	else
	{
		node->parent->children.erase(node->parent->children.find(node));
		node->parent = NULL;
	}
	
	return tree._size;
}

template<class DataType>
Tree<DataType> Tree<DataType>::secede(Node* node)
{
	if(bad_node(node, "Error", "Tree<DataType> Tree<DataType>::secede(Node* node)"))
	{
		exit(-1);
	}

	// 定义局部变量 tree，函数返回时，若调用处没有变量接受返回值，该局部变量自动销毁；
	// 反之，该局部变量从逻辑上转移到被调用处的空间（内存上位置没有改变，没有调用拷贝构造函数或是移动构造函数），
	// 并在那里函数结束后被销毁。
	Tree<DataType> tree;
	tree._root = node;
	tree._size = size(tree._root);
	_size -= tree->_size;

	if(node == _root)
	{
		_root = NULL;
	}
	else
	{
		node->parent->children.erase(node->parent->children.find(node));
		node->parent = NULL;
	}

	return tree;
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

	Tree<DataType> *tree = new Tree<DataType>;
	tree->_root = node;
	tree->_size = size(tree->_root);

	return *tree;
}

template<class DataType>
Tree<DataType>& Tree<DataType>::operator =(const Tree<DataType>& tree)
{
	if(this != &tree)
	{
		clear();
		copy_from(tree);
	}
	
	return *this;
}

template<class DataType>
Tree<DataType>& Tree<DataType>::operator =(Tree<DataType>&& tree)
{
	if(this != &tree)
	{
		clear();
		_root = move(tree._root);
		_size = move(tree._size);
		tree._root = NULL;
		tree._size = 0;
	}

	return *this;
}

template<class DataType>
Tree<DataType>& Tree<DataType>::operator =(const BinTree<DataType>& bintree)
{
	clear();
	Tree<DataType> tree(bintree);
	return *this = move(tree);
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
	Forest<DataType> forest(bintree);
	return *this = move(forest);
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