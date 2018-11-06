#ifdef BINTREE_H

template<class DataType>
template<class ElemType>
void BinTree<DataType>::check_ptr(const ElemType* ptr)
{
	if(!ptr)
	{
		cerr << "Failed to allocate memory!" << endl;
		exit(-1);
	}
}

template<class DataType>
void BinTree<DataType>::check_node(const Node* node, const char* function_name)
{
	if(!has_node(node))
	{
		cout << "Error in '" << function_name << "'" << endl
			 << "The node is not in current tree." << endl;
		exit(-2);
	}
}

template<class DataType>
typename BinTree<DataType>::Node*
BinTree<DataType>::new_Node(const DataType& value,
							int height,
							Node* parent,
							Node* lchild,
							Node* rchild)
{
	BinTree<DataType>::Node* node = new BinTree<DataType>::Node(value, height, parent, lchild, rchild);
	check_ptr(node);

	return node;
}

template<class DataType>
int BinTree<DataType>::size(const Node* node)
{
	if(!node)
	{
		return 0;
	}

	if(isleaf(node))
	{
		return 1;
	}

	return 1 + size(node->lchild) + size(node->rchild);
}

template<class DataType>
int BinTree<DataType>::height(const Node* node)
{
	if(!node)
	{
		return -1;
	}

	return node->height;
}

template<class DataType>
void BinTree<DataType>::update_height(Node* node)
{
	if(!node)
	{
		return;
	}

	node->height = 1 + max(height(node->lchild), height(node->rchild));
}

template<class DataType>
void BinTree<DataType>::update_height_above(Node* node)
{
	while(node)
	{
		update_height(node);
		node = node->parent;
	}
}

template<class DataType>
void BinTree<DataType>::update_height_below(Node* node)
{
	if(!node)
	{
		return;
	}

	update_height_below(node->lchild);
	update_height_below(node->rchild);
	node->height = 1 + max(height(node->lchild), height(node->rchild));
}

template<class DataType>
int BinTree<DataType>::depth(const Node* node)
{
	int n = -1;
	while(node)
	{
		n++;
		node = node->parent;
	}

	return n;
}

template<class DataType>
bool BinTree<DataType>::isleaf(const Node* node)
{
	return node && !(node->lchild || node->rchild);
}

template<class DataType>
bool BinTree<DataType>::isroot(const Node* node)
{
	return node && !(node->parent);
}

template<class DataType>
bool BinTree<DataType>::islchild(const Node* node)
{
	return node && node->parent && node->parent->lchild == node;
}

template<class DataType>
bool BinTree<DataType>::isrchild(const Node* node)
{
	return node && node->parent && node->parent->rchild == node;
}

template<class DataType>
typename BinTree<DataType>::Node*& BinTree<DataType>::branch(Node*& node)
{
	if(!node)
	{
		return node;
	}
	if(!(node->parent))
	{
		return _root;
	}
	
	return (node->parent->lchild == node) ? node->parent->lchild : node->parent->rchild;
}

template<class DataType>
typename BinTree<DataType>::Node*& BinTree<DataType>::brother(Node*& node)
{
	if(!node)
	{
		return node;
	}
	if(!(node->parent))
	{
		return node->parent;
	}

	return (node->parent->rchild == node) ? node->parent->lchild : node->parent->rchild;
}

template<class DataType>
void BinTree<DataType>::copy_from(const BinTree<DataType>& bintree)
{
	_size = bintree._size;

	Node* src_node;
	Node* dest_node = _root;
	_root = new_Node(bintree._root->data, bintree._root->height);

	Queue<Node*> src_queue, dest_queue;
	src_queue.push(bintree._root);
	dest_queue.push(_root);

	while(!src_queue.empty())
	{
		src_node = src_queue.pop();
		dest_node = dest_queue.pop();
		if(src_node->rchild)
		{
			dest_node->rchild = new_Node(src_node->rchild->data, src_node->rchild->height, dest_node);
			src_queue.push(src_node->rchild);
			dest_queue.push(dest_node->rchild);
		}
		if(src_node->lchild)
		{
			dest_node->lchild = new_Node(src_node->lchild->data, src_node->lchild->height, dest_node);
			src_queue.push(src_node->lchild);
			dest_queue.push(dest_node->lchild);
		}
	}
}

template<class DataType>
BinTree<DataType>::BinTree(const BinTree<DataType>& bintree)
{
	copy_from(bintree);
}

template<class DataType>
BinTree<DataType>::BinTree(BinTree<DataType>&& bintree)
{
	*this = move(bintree);
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
		dest_node->lchild = new_Node((*it)->data, 0, dest_node);
		dest_node = dest_node->lchild;

		dest_stack.push(dest_node);
		src_stack.push(*it);

		it++;
		for(; it != src_node->children.end(); it++)
		{
			dest_node->rchild = new_Node((*it)->data, 0, dest_node);
			dest_node = dest_node->rchild;
			dest_stack.push(dest_node);
			src_stack.push(*it);
		}
	}
	_size = tree.size();

	update_height_below(_root);
}

template<class DataType>
template<class ElemType>
BinTree<DataType>::BinTree(const Tree<ElemType>* tree)
{
	if(!type_equal(DataType, ElemType*))
	{
		cout << "Error in 'BinTree<DataType>::BinTree(const Tree<ElemType>* tree)'" << endl
			 << "DataType must equal to ElemType*" << endl;
		exit(-1);
	}

	if(tree->empty())
	{
		return;
	}

	_root = new_Node(&(tree->_root->data));

	Queue<typename Tree<ElemType>::Node*> src_queue;
	Queue<Node*> dest_queue;

	src_queue.push(tree->_root);
	dest_queue.push(_root);

	while(!src_queue.empty())
	{
		auto src_node = src_queue.pop();
		Node* dest_node = dest_queue.pop();

		if(src_node->children.empty())
		{
			continue;
		}

		auto it = src_node->children.begin();
		dest_node->lchild = new_Node(&((*it)->data), 0, dest_node);
		dest_node = dest_node->lchild;

		dest_queue.push(dest_node);
		src_queue.push(*it);

		it++;
		for(; it != src_node->children.end(); it++)
		{
			dest_node->rchild = new_Node(&((*it)->data), 0, dest_node);
			dest_node = dest_node->rchild;
			dest_queue.push(dest_node);
			src_queue.push(*it);
		}
	}
	_size = tree->_size;
	update_height_below(_root);
}

template<class DataType>
BinTree<DataType>::BinTree(const Forest<DataType>& forest)
{
	if(forest.empty())
	{
		return;
	}

	auto it = forest.begin();
	*this = *it;
	Node* node = _root;

	it++;
	for(; it != forest.end(); it++)
	{
		BinTree<DataType>* ptr_bintree = new BinTree<DataType>(*it);
		check_ptr(ptr_bintree);

		node->rchild = ptr_bintree->_root;
		ptr_bintree->_root->parent = node;
		node = node->rchild;
		_size += ptr_bintree->_size;
	}
	update_height_below(_root);
}

template<class DataType>
template<class ElemType>
BinTree<DataType>::BinTree(const Forest<ElemType>* forest)
{
	if(!type_equal(DataType, ElemType*))
	{
		cout << "Error in 'BinTree<DataType>::BinTree(const Forest<ElemType>* forest)'" << endl
			 << "DataType must equal to ElemType*" << endl;
		exit(-1);
	}

	if(forest->empty())
	{
		return;
	}

	auto it = forest->begin();
	*this = it.ptr();
	Node* node = _root;

	it++;
	for(; it != forest->end(); it++)
	{
		BinTree<DataType>* ptr_bintree = new BinTree<DataType>(it.ptr());
		check_ptr(ptr_bintree);

		node->rchild = ptr_bintree->_root;
		ptr_bintree->_root->parent = node;
		node = node->rchild;
		_size += ptr_bintree->_size;
	}
	update_height_below(_root);
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::operator =(const BinTree<DataType>& bintree)
{
	if(this != &bintree)
	{
		clear();
		copy_from(bintree);
	}

	return *this;
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::operator =(BinTree<DataType>&& bintree)
{
	if(this != &bintree)
	{
		clear();
		_root = move(bintree._root);
		_size = move(bintree._size);
		bintree._root = NULL;
		bintree._size = 0;
	}
	
	return *this;
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::operator =(const Tree<DataType>& tree)
{
	clear();
	BinTree<DataType> bintree = tree;
	return *this = move(bintree);
}

template<class DataType>
template<class ElemType>
BinTree<DataType>& BinTree<DataType>::operator =(const Tree<ElemType>* tree)
{
	clear();
	BinTree<DataType> bintree = tree;
	return *this = move(bintree);
}

template<class DataType>
BinTree<DataType>& BinTree<DataType>::operator =(const Forest<DataType>& forest)
{
	clear();
	BinTree<DataType> bintree = forest;
	return *this = move(bintree);
}

template<class DataType>
template<class ElemType>
BinTree<DataType>& BinTree<DataType>::operator =(const Forest<ElemType>* forest)
{
	clear();
	BinTree<DataType> bintree = forest;
	return *this = move(bintree);
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

// 删除以节点 node 为根的子树
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

	Node* node_parent = node->parent;
	if(!node_parent)
	{
		_root = NULL;
	}
	else
	{
		if(islchild(node))
		{
			node_parent->lchild = NULL;
		}
		else if(isrchild(node))
		{
			node_parent->rchild = NULL;
		}
	}

	Queue<Node*> queue;
	queue.push(node);
	int n = 0;
	while(!queue.empty())
	{
		node = queue.pop();
		if(node->rchild)
		{
			queue.push(node->rchild);
		}
		if(node->lchild)
		{
			queue.push(node->lchild);
		}
		delete node;
		n++;
	}
	_size -= n;
	update_height_above(node_parent);

	return n;
}

// 取下以节点 node 为根的子树并返回它
template<class DataType>
BinTree<DataType> BinTree<DataType>::secede(Node* node)
{
	if(!has_node(node))
	{
		cout << "Error in 'BinTree<DataType>& BinTree<DataType>::secede(Node* node)'" << endl
			 << "Current node is not in this tree!" << endl;
		exit(-1);
	}

	BinTree<DataType> dest_tree;
	dest_tree._root = node;
	dest_tree._size = size(node);
	_begin = iterator(NULL);
	_rear = iterator(NULL);	
	_size -= dest_tree._size;

	if(node == _root)
	{
		_root = NULL;
	}
	else
	{
		if(islchild(node))
		{
			node->parent->lchild = NULL;
		}
		else if(isrchild(node))
		{
			node->parent->rchild = NULL;
		}
	}
	dest_tree._root->parent = NULL;

	return dest_tree;
}

// 返回以 node 为根的子树
template<class DataType>
BinTree<DataType> BinTree<DataType>::subtree(Node* node)
{
	check_node(node, "BinTree<DataType> BinTree<DataType>::subtree(Node* node)");

	BinTree<DataType> dest_tree;
	dest_tree._root = new_Node(node->data, node->height);

	Node* src_node;
	Node* dest_node;

	Queue<Node*> src_queue, dest_queue;
	src_queue.push(node);
	dest_queue.push(dest_tree._root);

	dest_tree._size = 1;
	while(!src_queue.empty())
	{
		src_node = src_queue.pop();
		dest_node = dest_queue.pop();
		if(src_node->rchild)
		{
			dest_node->rchild = new_Node(src_node->rchild->data, src_node->rchild->height, dest_node);
			dest_tree._size++;
			src_queue.push(src_node->rchild);
			dest_queue.push(dest_node->rchild);
		}
		if(src_node->lchild)
		{
			dest_node->lchild = new_Node(src_node->lchild->data, src_node->lchild->height, dest_node);
			dest_tree._size++;
			src_queue.push(src_node->lchild);
			dest_queue.push(dest_node->lchild);
		}
	}

	return dest_tree;
}

template<class DataType>
int BinTree<DataType>::size()const
{
	return _size;
}

template<class DataType>
int BinTree<DataType>::height()const
{
	return _root->height;
}

template<class DataType>
bool BinTree<DataType>::empty()const
{
	return (_root == NULL);
}

template<class DataType>
bool BinTree<DataType>::has_node(const Node* node)const
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
		cout << "Error in 'BinTree<DataType>::Node* BinTree<DataType>::insert_root(const DataType& value)'" << endl
			 << "Current tree already has root node." << endl;
		exit(-1);
	}

	_size = 1;
	return (_root = new_Node(value));
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::insert_lchild(BinTree<DataType>::Node* node, const DataType& value)
{
	check_node(node, "BinTree<DataType>::Node* BinTree<DataType>::insert_lchild(BinTree<DataType>::Node* node, const DataType& value)");

	_size++;
	if(node->lchild)
	{
		cout << "Error when insert left child!" << endl
			 << "Current node already has left child!" << endl;
		exit(-1);
	}
	node->lchild = new_Node(value, 0, node);
	update_height_above(node);

	return node->lchild;
}

template<class DataType>
typename BinTree<DataType>::Node* BinTree<DataType>::insert_rchild(BinTree<DataType>::Node* node, const DataType& value)
{
	check_node(node, "BinTree<DataType>::Node* BinTree<DataType>::insert_rchild(BinTree<DataType>::Node* node, const DataType& value)");

	_size++;
	if(node->rchild)
	{
		cout << "Error when insert right child!" << endl
			 << "Current node already has right child!" << endl;
		exit(-1);
	}
	node->rchild = new_Node(value, 0, node);
	update_height_above(node);

	return node->rchild;
}

template<class DataType>
typename BinTree<DataType>::Node*
BinTree<DataType>::attach_lchild(BinTree<DataType>::Node* node, const BinTree<DataType>& bintree)
{
	check_node(node, "BinTree<DataType>::attach_lchild(BinTree<DataType>::Node* node, const BinTree<DataType>& bintree)");

	if(node->lchild)
	{
		cout << "Error in 'BinTree<DataType>::Node*" << endl
			 << "          BinTree<DataType>::attach_lchild(BinTree<DataType>::Node*," << endl
			 << "                                           const BinTree<DataType>&)'" << endl
			 << "Current node already has left child!" << endl;
		exit(-1);
	}

	BinTree<DataType>* ptr_bintree = new BinTree<DataType>(bintree);
	check_ptr(ptr_bintree);

	_size += ptr_bintree->_size;
	node->lchild = ptr_bintree->_root;
	ptr_bintree->_root->parent = node;
	update_height_above(node);

	return ptr_bintree->_root;
}

template<class DataType>
typename BinTree<DataType>::Node*
BinTree<DataType>::attach_rchild(BinTree<DataType>::Node* node, const BinTree<DataType>& bintree)
{
	check_node(node, "BinTree<DataType>::attach_rchild(BinTree<DataType>::Node* node, const BinTree<DataType>& bintree)");

	if(node->rchild)
	{
		cout << "Error in 'BinTree<DataType>::Node*" << endl
			 << "          BinTree<DataType>::attach_rchild(BinTree<DataType>::Node*," << endl
			 << "                                           const BinTree<DataType>&)'" << endl
			 << "Current node already has right child!" << endl;
		exit(-1);
	}

	BinTree<DataType>* ptr_bintree = new BinTree<DataType>(bintree);
	check_ptr(ptr_bintree);

	_size += ptr_bintree->_size;
	node->rchild = ptr_bintree->_root;
	ptr_bintree->_root->parent = node;
	update_height_above(node);

	return ptr_bintree->_root;
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
		case IN1: trav_in1(); break;
		case IN2:
		case IN: trav_in2(); break;
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
	while(!isleaf(node))
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
	_root->prev = NULL;

	Stack<Node*> stack;
	stack.push(_root);
	Node *node;

	while(true)
	{
		node = trav_left_branch(stack.pop(), stack);
		if(stack.empty())
		{
			_rear = iterator(node);
			node->next = NULL;
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
	while(!isleaf(node))
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
	last_node->prev = NULL;

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
	node->next = NULL;
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
void BinTree<DataType>::trav_in1()
{
	Stack<Node*> stack;
	Node *last_node = goto_most_left(_root, stack), *node;
	_begin = last_node;
	last_node->prev = NULL;

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
	node->next = NULL;
}

template<class DataType>
void BinTree<DataType>::trav_in2()
{
	Stack<Node*> stack;
	Node* last_node = NULL;
	Node* node = _root;
	while(true)
	{
		if(node)
		{
			stack.push(node);
			node = node->lchild;
		}
		else if(!stack.empty())
		{
			node = stack.pop();
			if(last_node)
			{
				last_node->next = node;
			}
			else
			{
				_begin = iterator(node);
				node->prev = NULL;
			}
			node->prev = last_node;
			last_node = node;
			node = node->rchild;
		}
		else
		{
			_rear = iterator(last_node);
			last_node->next = NULL;
			return;
		}
	}
}

template<class DataType>
void BinTree<DataType>::trav_level()
{
	_begin = iterator(_root);

	Queue<Node*> queue;
	queue.push(_root);
	_root->prev = NULL;
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
			node->next = NULL;
			return;
		}
		node->next = queue.front();
		queue.front()->prev = node;
	}
}
#include <draw.cpp>
#endif