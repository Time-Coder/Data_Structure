#ifdef BINTREE_H

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::new_Node(const DataType& value,
													 Node* parent,
													 Node* lchild,
													 Node* rchild)
{
	BinTree<DataType>::Node* p_node = new BinTree<DataType>::Node(value, parent, lchild, rchild);
	if(!p_node)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	return p_node;
}

template<class DataType>
int BinTree<DataType>::Node::size()const
{
	if(isleaf())
	{
		return 1;
	}

	int n = 1;
	if(lchild)
	{
		n += lchild->size();
	}
	if(rchild)
	{
		n += rchild->size();
	}

	return n;
}

template<class DataType>
int BinTree<DataType>::Node::height()const
{
	if(isleaf())
	{
		return 0;
	}

	int lheight = -1, rheight = -1;
	if(lchild)
	{
		lheight = lchild->height();
	}
	if(rchild)
	{
		rheight = rchild->height();
	}

	return max(lheight, rheight) + 1;
}

template<class DataType>
int BinTree<DataType>::Node::level()const
{
	if(!parent)
	{
		return 0;
	}

	return parent->level() + 1;
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::Node::insert_lchild(const DataType& value)
{
	if(lchild)
	{
		cout << "Error in 'typename BinTree<DataType>::Node* BinTree<DataType>::Node::insert_lchild(const DataType& value)'" << endl
			 << "Current node already has left child!" << endl;
		exit(-1);
	}
	lchild = new_Node(value, this);

	return lchild;
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::Node::insert_rchild(const DataType& value)
{
	if(rchild)
	{
		cout << "Error in 'typename BinTree<DataType>::Node* BinTree<DataType>::Node::insert_rchild(const DataType& value)'" << endl
			 << "Current node already has right child!" << endl;
		exit(-1);
	}
	rchild = new_Node(value, this);

	return rchild;
}

template<class DataType>
bool BinTree<DataType>::Node::isleaf()const
{
	return !(lchild || rchild);
}

template<class DataType>
bool BinTree<DataType>::Node::isroot()const
{
	return !parent;
}

template<class DataType>
bool BinTree<DataType>::Node::islchild()const
{
	return (parent && parent->lchild == this);
}

template<class DataType>
bool BinTree<DataType>::Node::isrchild()const
{
	return (parent && parent->rchild == this);
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::Node::brother()const
{
	if(!parent)
	{
		return NULL;
	}

	return (parent->rchild == this ? parent->lchild : parent->rchild);
}

template<class DataType>
bool BinTree<DataType>::Node::belong_to(const BinTree<DataType>& tree)const
{
	return tree.has_node(this);
}

template<class DataType>
void BinTree<DataType>::copy(BinTree<DataType>& dest_tree, const BinTree<DataType>& src_tree)
{
	dest_tree.clear();
	dest_tree._size = src_tree._size;

	Node* src_node;
	Node* dest_node = dest_tree._root;
	dest_tree._root = new_Node(src_tree._root->data);

	Stack<Node*> src_stack, dest_stack;
	src_stack.push(src_tree._root);
	dest_stack.push(dest_tree._root);

	while(!src_stack.empty())
	{
		src_node = src_stack.pop();
		dest_node = dest_stack.pop();
		if(src_node->rchild)
		{
			dest_node->rchild = new_Node(src_node->rchild->data, dest_node);
			src_stack.push(src_node->rchild);
			dest_stack.push(dest_node->rchild);
		}
		if(src_node->lchild)
		{
			dest_node->lchild = new_Node(src_node->lchild->data, dest_node);
			src_stack.push(src_node->lchild);
			dest_stack.push(dest_node->lchild);
		}
	}
}

template<class DataType>
BinTree<DataType>::BinTree(const BinTree<DataType>& tree)
{
	copy(*this, tree);
}

template<class DataType>
BinTree<DataType>::BinTree(const Tree<DataType>& tree)
{
	_root = new_Node(tree.root()->data);

	Stack<typename Tree<DataType>::Node*> src_stack;
	Stack<Node*> dest_stack;

	src_stack.push(tree.root());
	dest_stack.push(_root);

	while(!src_stack.empty())
	{
		typename Tree<DataType>::Node* src_node = src_stack.pop();
		Node* dest_node = dest_stack.pop();

		if(src_node->children.empty())
		{
			continue;
		}

		auto it = src_node->children.begin();
		dest_node->lchild = new_Node((*it)->data, dest_node);
		dest_node = dest_node->lchild;

		dest_stack.push(dest_node);
		src_stack.push(*it);

		it++;
		for(; it != src_node->children.end(); it++)
		{
			dest_node->rchild = new_Node((*it)->data, dest_node);
			dest_node = dest_node->rchild;
			dest_stack.push(dest_node);
			src_stack.push(*it);
		}
	}
	_size = tree.size();
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::operator =(const BinTree<DataType>& tree)
{
	copy(*this, tree);

	return *this;
}

template<class DataType>
BinTree<DataType>::~BinTree()
{
	clear();
}

template<class DataType>
void BinTree<DataType>::clear()
{
	if(empty())
	{
		return;
	}

	Stack<Node*> stack;
	stack.push(_root);
	while(!stack.empty())
	{
		Node *p_node = stack.pop();
		if(p_node->rchild)
		{
			stack.push(p_node->rchild);
		}
		if(p_node->lchild)
		{
			stack.push(p_node->lchild);
		}
		delete p_node;
	}

	_root = NULL;
	_size = 0;
	_begin = iterator(NULL);
	_rear = iterator(NULL);
}

template<class DataType>
int BinTree<DataType>::remove(Node* node)
{
	if(!has_node(node))
	{
		cout << "Error in \'int BinTree<DataType>::remove(Node* node)\'" << endl
			 << "node is not in current tree." << endl;
		exit(-1);
	}
	_begin = iterator(NULL);
	_rear = iterator(NULL);
	if(node->isroot())
	{
		_root = NULL;
	}
	else
	{
		if(node->islchild())
		{
			node->parent->lchild = NULL;
		}
		else if(node->isrchild())
		{
			node->parent->rchild = NULL;
		}
	}

	Stack<Node*> stack;
	stack.push(node);
	int n = 0;
	while(!stack.empty())
	{
		node = stack.pop();
		if(node->rchild)
		{
			stack.push(node->rchild);
		}
		if(node->lchild)
		{
			stack.push(node->lchild);
		}
		delete node;
		n++;
	}
	_size -= n;

	return n;
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::secede(Node* p_node)
{
	if(!has_node(p_node))
	{
		cout << "Error in 'BinTree<DataType>& BinTree<DataType>::secede(Node* p_node)'" << endl
			 << "Current node is not in this tree!" << endl;
		exit(-1);
	}

	BinTree<DataType>* p_dest_tree = new BinTree<DataType>;
	p_dest_tree->_root = p_node;
	p_dest_tree->_size = p_node->size();
	_begin = iterator(NULL);
	_rear = iterator(NULL);	
	_size -= p_dest_tree->_size;

	if(p_node == _root)
	{
		_root = NULL;
	}
	else
	{
		if(p_node->islchild())
		{
			p_node->parent->lchild = NULL;
		}
		else if(p_node->isrchild())
		{
			p_node->parent->rchild = NULL;
		}
	}

	return *p_dest_tree;
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::subtree(Node* p_node)
{
	if(!has_node(p_node))
	{
		cout << "Error in 'BinTree<DataType>& BinTree<DataType>::subtree(Node* p_node)'" << endl
			 << "Current node is not in this tree!" << endl;
		exit(-1);
	}

	BinTree<DataType>* ptr_dest_tree = new BinTree<DataType>;
	if(!ptr_dest_tree)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}

	ptr_dest_tree->_root = new_Node(p_node->data);

	Node* src_node;
	Node* dest_node;

	Stack<Node*> src_stack, dest_stack;
	src_stack.push(p_node);
	dest_stack.push(ptr_dest_tree->_root);

	ptr_dest_tree->_size = 1;
	while(!src_stack.empty())
	{
		src_node = src_stack.pop();
		dest_node = dest_stack.pop();
		if(src_node->rchild)
		{
			dest_node->rchild = new_Node(src_node->rchild->data, dest_node);
			ptr_dest_tree->_size++;
			src_stack.push(src_node->rchild);
			dest_stack.push(dest_node->rchild);
		}
		if(src_node->lchild)
		{
			dest_node->lchild = new_Node(src_node->lchild->data, dest_node);
			ptr_dest_tree->_size++;
			src_stack.push(src_node->lchild);
			dest_stack.push(dest_node->lchild);
		}
	}

	return *ptr_dest_tree;
}

template<class DataType>
int BinTree<DataType>::size()const
{
	return _size;
}

template<class DataType>
int BinTree<DataType>::height()const
{
	return _root->height();
}

template<class DataType>
bool BinTree<DataType>::empty()const
{
	return (_root == NULL);
}

template<class DataType>
bool BinTree<DataType>::has_node(Node* p_node)const
{
	while(p_node->parent)
	{
		p_node = p_node->parent;
	}

	return (p_node == _root);
}

template<class DataType>
bool BinTree<DataType>::has_node(const Node& node)const
{
	Node* p_node = &node;
	while(p_node->parent)
	{
		p_node = p_node->parent;
	}

	return (p_node == _root);
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::root()const
{
	return _root;
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::insert_root(const DataType& value)
{
	if(_root)
	{
		cout << "Error in \'BinTree<DataType>::Node* BinTree<DataType>::insert_root(const DataType& value)\'" << endl
			 << "Current tree already has root node." << endl;
		exit(-1);
	}

	_size = 1;
	return (_root = new_Node(value));
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::insert_lchild(BinTree<DataType>::Node* node, const DataType& value)
{
	if(!has_node(node))
	{
		cout << "Error in \'BinTree<DataType>::Node* BinTree<DataType>::insert_lchild(BinTree<DataType>::Node* node, const DataType& value)\'" << endl
			 << "node is not in current tree." << endl;
		exit(-1);
	}

	_size++;
	return node->insert_lchild(value);
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::insert_rchild(BinTree<DataType>::Node* node, const DataType& value)
{
	if(!has_node(node))
	{
		cout << "Error in \'BinTree<DataType>::Node* BinTree<DataType>::insert_rchild(BinTree<DataType>::Node* node, const DataType& value)\'" << endl
			 << "node is not in current tree." << endl;
		exit(-1);
	}

	_size++;
	return node->insert_rchild(value);
}

template<class DataType>
typename BinTree<DataType>::Node*
BinTree<DataType>::attach_lchild(BinTree<DataType>::Node* p_node, const BinTree<DataType>& tree)
{
	if(!has_node(p_node))
	{
		cout << "Error in \'BinTree<DataType>::Node* BinTree<DataType>::attach_lchild(BinTree<DataType>::Node* p_node, const BinTree<DataType>& tree)\'" << endl
			 << "p_node is not in current tree." << endl;
		exit(-1);
	}

	if(p_node->lchild)
	{
		cout << "Error in 'BinTree<DataType>::Node*" << endl
			 << "          BinTree<DataType>::attach_lchild(BinTree<DataType>::Node*," << endl
			 << "                                           const BinTree<DataType>&)'" << endl
			 << "Current node already has left child!" << endl;
		exit(-1);
	}

	BinTree<DataType>* p_tree = new BinTree<DataType>(tree);

	_size += p_tree->_size;
	p_node->lchild = p_tree->_root;
	p_tree->_root->parent = p_node;

	return p_tree->_root;
}

template<class DataType>
typename BinTree<DataType>::Node*
BinTree<DataType>::attach_rchild(BinTree<DataType>::Node* p_node, const BinTree<DataType>& tree)
{
	if(!has_node(p_node))
	{
		cout << "Error in \'BinTree<DataType>::Node* BinTree<DataType>::attach_rchild(BinTree<DataType>::Node* p_node, const BinTree<DataType>& tree)\'" << endl
			 << "p_node is not in current tree." << endl;
		exit(-1);
	}

	if(p_node->rchild)
	{
		cout << "Error in 'BinTree<DataType>::Node*" << endl
			 << "          BinTree<DataType>::attach_rchild(BinTree<DataType>::Node*," << endl
			 << "                                           const BinTree<DataType>&)'" << endl
			 << "Current node already has right child!" << endl;
		exit(-1);
	}

	BinTree<DataType>* p_tree = new BinTree<DataType>(tree);

	_size += p_tree->_size;
	p_node->rchild = p_tree->_root;
	p_tree->_root->parent = p_node;

	return p_tree->_root;
}

template<class DataType>
void BinTree<DataType>::write(const string& filename)const
{
	if(empty())
	{
		cout << "The tree is empty, nothing to write!" << endl;
		return;
	}

	ofstream file("Figures/bintree.dot");
	file << "graph BinTree" << endl
		 <<	"{" << endl
		 << "	graph[ordering=\"out\"];" << endl << endl;
		 
	Node* p_node;
	Stack<Node*> stack, stack_all;
	Stack<int> stack_name;
	stack.push(_root);
	stack_all.push(_root);
	int node_name = 0;
	stack_name.push(node_name);

	while(!stack.empty())
	{
		p_node = stack.pop();
		int current_name = stack_name.pop();
		if(p_node && !(p_node->isleaf()) )
		{
			node_name++;
			if(p_node->lchild)
			{
				file << "\t" << current_name << "--" << node_name << ";" << endl;
			}
			else
			{
				file << "\t" << current_name << "--NULL" << node_name << "[style=\"invis\"];" << endl;
			}
			stack.push(p_node->lchild);
			stack_all.push(p_node->lchild);
			stack_name.push(node_name);

			node_name++;
			if(p_node->rchild)
			{
				file << "\t" << current_name << "--" << node_name << ";" << endl;
			}
			else
			{
				file << "\t" << current_name << "--NULL" << node_name << "[style=\"invis\"];" << endl;
			}
			stack.push(p_node->rchild);
			stack_all.push(p_node->rchild);
			stack_name.push(node_name);
		}
	}

	file << endl;
	while(!stack_all.empty())
	{
		p_node = stack_all.pop();
		if(!p_node)
		{
			file << "	NULL" << node_name-- << "[shape=\"circle\",label=\"A\",style=\"invis\"];" << endl;
		}
		else
		{
			file << "\t" << node_name-- << "[shape=\"circle\",label=\"" << p_node->data << "\"];" << endl;
		}
	}

	file << "}" << endl;
	file.close();
	string cmd = "dot Figures/bintree.dot | gvpr -c -f Figures/binarytree.gvpr | neato -n -Tpdf -o Figures/" + filename;
	system(cmd.data());
}

template<class DataType>
void BinTree<DataType>::show(const string& filename)const
{
	if(empty())
	{
		cout << "The tree is empty, nothing to show!" << endl;
		return;
	}

	write(filename);
	string cmd = "start sumatrapdf Figures/" + filename;
	system(cmd.data());
}

template<class DataType>
typename BinTree<DataType>::iterator& BinTree<DataType>::iterator::operator  =(Node* ptr)
{
	_ptr = ptr;
	return *this;
}

template<class DataType>
typename BinTree<DataType>::iterator& BinTree<DataType>::iterator::operator ++()
{
    _ptr = _ptr->next;
    return *this;
}

template<class DataType>
typename BinTree<DataType>::iterator BinTree<DataType>::iterator::operator ++(int)
{
    iterator temp = *this;
    _ptr = _ptr->next;
    return temp;
}

template<class DataType>
typename BinTree<DataType>::iterator& BinTree<DataType>::iterator::operator --()
{
    _ptr = _ptr->prev;
    return *this;
}

template<class DataType>
typename BinTree<DataType>::iterator BinTree<DataType>::iterator::operator --(int)
{
    iterator temp = *this;
    _ptr = _ptr->prev;
    return temp;
}

template<class DataType>
typename BinTree<DataType>::iterator BinTree<DataType>::begin()const
{
	if(iterator(NULL) == _begin && _root)
	{
		cout << "Warning: not specify traversal method!" << endl
			 << "Plear use 'void BinTree<DataType>::trav_method(TravType method)' to specify a traversal method!" << endl;
	}
	return _begin;
}

template<class DataType>
typename BinTree<DataType>::iterator BinTree<DataType>::end()const
{
	return _end;
}

template<class DataType>
typename BinTree<DataType>::iterator BinTree<DataType>::rear()const
{
	if(iterator(NULL) == _rear && _root)
	{
		cout << "Warning: not specify traversal method!" << endl
			 << "Plear use 'void BinTree<DataType>::trav_method(TravType method)' to specify a traversal method!" << endl;
	}
	return _rear;
}

template<class DataType>
void BinTree<DataType>::trav_method(TravType method)
{
	switch(method)
	{
		case PRE: trav_pre(); break;
		case POST: trav_post(); break;
		case IN: trav_in(); break;
		case LEVEL: trav_level(); break;
		default:
		{
			cout << "Error in \'void BinTree<DataType>::trav_method(TravType method)\'" << endl
				 << "method is not a enum member in BinTree<DataType>::TravType" << endl;
			exit(-1);
		} 
	}
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::trav_left_branch(Node* node, Stack<Node*>& stack)
{
	while( !(node->isleaf()) )
	{
		if(node->lchild)
		{
			if(node->rchild)
			{
				stack.push(node->rchild);
			}
			node->next = node->lchild;
			node->lchild->prev = node;
			node = node->lchild;
		}
		else // if(node->rchild)
		{
			node->next = node->rchild;
			node->rchild->prev = node;
			node = node->rchild;
		}
	}
	return node;
}

template<class DataType>
void BinTree<DataType>::trav_pre()
{
	_begin = iterator(_root);

	Stack<Node*> stack;
	stack.push(_root);
	Node *node;

	while(true)
	{
		node = trav_left_branch(stack.pop(), stack);
		if(stack.empty())
		{
			_rear = iterator(node);
			return;
		}
		node->next = stack.top();
		stack.top()->prev = node;
	}
}

template<class DataType>
void BinTree<DataType>::gotoHLVFL(Stack<Node*>& stack)
{
	if(stack.empty())
	{
		return;
	}

	Node* node = stack.top();
	while( !(node->isleaf()) )
	{
		if(node->rchild)
		{
			stack.push(node->rchild);
		}
		if(node->lchild)
		{
			stack.push(node->lchild);
		}

		node = stack.top();
	}
}

template<class DataType>
void BinTree<DataType>::trav_post()
{
	Stack<Node*> stack;

	stack.push(_root);
	gotoHLVFL(stack);
	Node *last_node = stack.pop(), *node;
	_begin = last_node;

	while(!stack.empty())
	{
		if(stack.top() != last_node->parent)
		{
			gotoHLVFL(stack);
		}
		node = stack.pop();
		last_node->next = node;
		node->prev = last_node;
		last_node = node;
	}
	_rear = iterator(node);
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::goto_most_left(Node* node, Stack<Node*>& stack)
{
	do
	{
		if(node->rchild)
		{
			stack.push(node->rchild);
		}
		stack.push(node);
	}while((node = node->lchild));

	return stack.pop();
}

template<class DataType>
void BinTree<DataType>::trav_in()
{
	Stack<Node*> stack;
	Node *last_node = goto_most_left(_root, stack), *node;
	_begin = last_node;

	while(!stack.empty())
	{
		node = stack.pop();
		if(last_node == node->parent)
		{
			node = goto_most_left(node, stack);
		}
		last_node->next = node;
		node->prev = last_node;
		last_node = node;
	}
	_rear = iterator(node);
}

template<class DataType>
void BinTree<DataType>::trav_level()
{
	_begin = iterator(_root);

	Queue<Node*> queue;
	queue.push(_root);
	while(true)
	{
		Node* node = queue.pop();
		if(node->lchild)
		{
			queue.push(node->lchild);
		}
		if(node->rchild)
		{
			queue.push(node->rchild);
		}
		if(queue.empty())
		{
			_rear = iterator(node);
			return;
		}
		node->next = queue.front();
		queue.front()->prev = node;
	}
}

#endif