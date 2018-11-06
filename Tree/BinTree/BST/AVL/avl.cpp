#ifdef AVL_H

template<class KeyType>
int AVL<KeyType>::balance_factor(typename BinTree<KeyType>::Node* node)
{
	if(!node)
	{
		return 0;
	}
	return this->height(node->lchild) - this->height(node->rchild);
}

template<class KeyType>
bool AVL<KeyType>::balanced(typename BinTree<KeyType>::Node* node)
{
	int factor = balance_factor(node);
	return (factor >= -1 && factor <= 1);
}

template<class KeyType>
typename BinTree<KeyType>::Node* AVL<KeyType>::taller_child(typename BinTree<KeyType>::Node* node)
{
	return (node->lchild->height > node->rchild->height ? node->lchild :
			node->lchild->height < node->rchild->height ? node->rchild :
			this->islchild(node) ? node->lchild : node->rchild);
}

template<class KeyType>
typename BinTree<KeyType>::Node* AVL<KeyType>::insert(const KeyType& key)
{
	auto node_insert = this->BST<KeyType>::insert(key);
	auto v = node_insert;
	if(!(this->isleaf(v)) || !(this->_hot) || !(this->_hot->parent))
	{
		return node_insert;
	}
	auto p = this->_hot;
	auto g = this->_hot->parent;

	while(balanced(g))
	{
		g = g->parent;
		if(!g)
		{
			return node_insert;
		}
		p = p->parent;
		v = v->parent;
	}

	if(g->rchild == p && p->rchild == v)
	{
		this->zag(g);
	}
	else if(g->lchild == p && p->lchild == v)
	{
		this->zig(g);
	}
	else if(g->rchild == p && p->lchild == v)
	{
		this->zig(p);
		this->zag(g);
	}
	else if(g->lchild == p && p->rchild == v)
	{
		this->zag(p);
		this->zig(g);
	}
}

template<class KeyType>
typename BinTree<KeyType>::Node* AVL<KeyType>::remove(const KeyType& key)
{
	auto replace_node = this->BST<KeyType>::remove(key);
	auto g = this->_hot;
	if(!g)
	{
		return replace_node;
	}
	
	while(true)
	{
		while(balanced(g))
		{
			g = g->parent;
			if(!g)
			{
				return replace_node;
			}
		}
		auto p = taller_child(g);
		auto v = taller_child(p);

		if(g->lchild == p && p->lchild == v)
		{
			this->zig(g);
			return replace_node;
		}
		else if(g->rchild == p && p->rchild == v)
		{
			this->zag(g);
			return replace_node;
		}
		else if(g->lchild == p && p->rchild == v)
		{
			this->zag(p);
			this->zig(g);
		}
		else
		{
			this->zig(p);
			this->zag(g);
		}
	}
}

#endif