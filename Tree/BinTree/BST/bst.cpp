#ifdef BST_H

template<class KeyType>
typename BinTree<KeyType>::Node*& BST<KeyType>::search(const KeyType& key)
{
	_hot = NULL;
	typename BinTree<KeyType>::Node** node = &(this->_root);
	while(true)
	{
		if(!(*node) || key == (*node)->data)
		{
			return *node;
		}
		_hot = *node;
		node = &(key < (*node)->data ? (*node)->lchild : (*node)->rchild);
	}
}

template<class KeyType>
typename BinTree<KeyType>::Node* BST<KeyType>::insert(const KeyType& key)
{
	typename BinTree<KeyType>::Node*& node = search(key);
	if(node)
	{
		return node;
	}

	node = this->new_Node(key, 0, _hot);
	this->_size++;
	this->update_height_above(_hot);

	return node;
}

template<class KeyType>
typename BinTree<KeyType>::Node* BST<KeyType>::remove(const KeyType& key)
{
	typename BinTree<KeyType>::Node*& node = search(key);
	typename BinTree<KeyType>::Node* replace_node = node;
	if(!replace_node)
	{
		return replace_node;
	}

	auto out_node = node;
	if(node->lchild && node->rchild) // 有两个孩子
	{
		out_node = node->rchild;
		while(out_node->lchild)
		{
			out_node = out_node->lchild;
		}
		node->data = out_node->data;
		replace_node = out_node->rchild;
		if(replace_node)
		{
			replace_node->parent = out_node->parent;
		}
		this->branch(out_node) = replace_node;
	}
	else if(!(node->lchild) && !(node->rchild)) // 没有孩子
	{
		replace_node = node = NULL;
	}
	else // 只有一个孩子
	{
		replace_node = node = (node->lchild ? node->lchild : node->rchild);
		node->parent = _hot;
	}
	_hot = out_node->parent;
	color_removed = out_node->color;
	delete out_node;
	this->_size--;
	this->update_height_above(_hot);

	return replace_node;
}

template<class KeyType>
void BST<KeyType>::zig(typename BinTree<KeyType>::Node* node)
{
	if(!node || !(node->lchild))
	{
		return;
	}

	auto node_lchild = node->lchild;
	auto node_lchild_rchild = node_lchild->rchild;

	this->branch(node) = node_lchild;
	node_lchild->parent = node->parent;
	node_lchild->rchild = node;
	node->parent = node_lchild;
	node->lchild = node_lchild_rchild;
	if(node_lchild_rchild)
	{
		node_lchild_rchild->parent = node;
	}
	this->update_height_above(node);
}

template<class KeyType>
void BST<KeyType>::zag(typename BinTree<KeyType>::Node* node)
{
	if(!node || !(node->rchild))
	{
		return;
	}

	auto node_rchild = node->rchild;
	auto node_rchild_lchild = node_rchild->lchild;

	this->branch(node) = node_rchild;
	node_rchild->parent = node->parent;
	node_rchild->lchild = node;
	node->parent = node_rchild;
	node->rchild = node_rchild_lchild;
	if(node_rchild_lchild)
	{
		node_rchild_lchild->parent = node;
	}

	this->update_height_above(node);
}

template<class KeyType>
typename BinTree<KeyType>::Node*
BST<KeyType>::connect34(typename BinTree<KeyType>::Node* a,
		  typename BinTree<KeyType>::Node* b,
		  typename BinTree<KeyType>::Node* c,
		  typename BinTree<KeyType>::Node* T0,
		  typename BinTree<KeyType>::Node* T1,
		  typename BinTree<KeyType>::Node* T2,
		  typename BinTree<KeyType>::Node* T3,
		  typename BinTree<KeyType>::Node* hole_parent,
		  typename BinTree<KeyType>::Node*& child_branch)
{
	a->lchild = T0;
	a->rchild = T1;
	if(T0) T0->parent = a;
	if(T1) T1->parent = a;
	this->update_height(a);

	c->lchild = T2;
	c->rchild = T3;
	if(T2) T2->parent = c;
	if(T3) T3->parent = c;
	this->update_height(c);

	b->lchild = a;
	a->parent = b;
	b->rchild = c;
	c->parent = b;
	this->update_height(b);

	child_branch = b;
	b->parent = hole_parent;
	this->update_height(hole_parent);

	return b;
}

template<class KeyType>
typename BinTree<KeyType>::Node*
BST<KeyType>::rebalance(typename BinTree<KeyType>::Node* v,
							typename BinTree<KeyType>::Node* p,
							typename BinTree<KeyType>::Node* g)
{
	if(g->lchild == p && p->lchild == v)
	{
		return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild, g->parent, this->branch(g));
	}
	else if(g->rchild == p && p->rchild == v)
	{
		return connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild, g->parent, this->branch(g));
	}
	else if(g->rchild == p && p->lchild == v)
	{
		return connect34(g, v, p, g->lchild, v->lchild, v->rchild, p->rchild, g->parent, this->branch(g));
	}
	else // if(g->lchild == p && p->rchild == v)
	{
		return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild, g->parent, this->branch(g));
	}
}

#endif