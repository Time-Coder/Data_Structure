#ifdef REDBLACK_H

template<class KeyType>
typename BinTree<KeyType>::Node*
RedBlack<KeyType>::red_child(typename BinTree<KeyType>::Node* node)
{
	if(!node)
	{
		return NULL;
	}
	if(is_red(node->lchild))
	{
		return node->lchild;
	}
	if(is_red(node->rchild))
	{
		return node->rchild;
	}
	return NULL;
}

template<class KeyType>
void RedBlack<KeyType>::update_height(typename BinTree<KeyType>::Node* node)
{
	if(node)
	{
		node->height = this->height(node->lchild) + this->height(node->rchild);
		if(node->color == BLACK)
		{
			node->height++;
		}
	}
}

template<class KeyType>
bool RedBlack<KeyType>::is_black(typename BinTree<KeyType>::Node* node)
{
	return (!node || node->color == BLACK);
}

template<class KeyType>
bool RedBlack<KeyType>::is_red(typename BinTree<KeyType>::Node* node)
{
	return (node && node->color == RED);
}

template<class KeyType>
void RedBlack<KeyType>::solve_red2(typename BinTree<KeyType>::Node* x)
{
	if(!x)
	{
		return;
	}
	if(!(x->parent))
	{
		x->color = BLACK;
		return;
	}

	auto p = x->parent;
	if(is_black(p))
	{
		return;
	}

	// 能到这里说明 p 是红色
	auto g = p->parent; // g 一定存在，因为如果没有 g，说明 p(红色) 是根结点，不合法。
	auto u = this->brother(p);

	if(is_black(u))
	{
		auto b = this->rebalance(x, p, g);
		b->lchild->color = RED;
		b->color = BLACK;
		b->rchild->color = RED;
	}
	else // if(u->color == RED)
	{
		p->color = BLACK;
		u->color = BLACK;
		g->color = RED;
		if(is_red(g->parent) || !(g->parent))
		{
			solve_red2(g);
		}
	}
}

template<class KeyType>
void RedBlack<KeyType>::solve_black2(typename BinTree<KeyType>::Node* r)
{
	auto p = this->_hot;
	if(!p)
	{
		return;
	}

	auto s = (r == p->rchild) ? p->lchild : p->rchild;
	if(is_black(s))
	{
		auto t = red_child(s);
		if(t)
		{
			int p_color = p->color;
			auto b = this->rebalance(t, s, p);
			b->lchild->color = BLACK;
			b->rchild->color = BLACK;
			b->color = p_color;
		}
		else
		{
			if(is_red(p))
			{
				p->color = BLACK;
				s->color = RED;
			}
			else
			{
				s->color = RED;
				this->_hot = p->parent;
				solve_black2(p);
			}
		}
	}
	else
	{
		if(this->islchild(s))
		{
			this->zig(p);
		}
		else
		{
			this->zag(p);
		}
		p->color = RED;
		s->color = BLACK;
		solve_black2(r);
	}
}

template<class KeyType>
typename BinTree<KeyType>::Node* RedBlack<KeyType>::insert(const KeyType& key)
{
	typename BinTree<KeyType>::Node*& x = this->search(key);
	if(x)
	{
		return x;
	}
	x = this->new_Node(key, 0, this->_hot);
	x->color = RED;
	this->_size++;

	solve_red2(x);
	return x;
}

template<class KeyType>
typename BinTree<KeyType>::Node* RedBlack<KeyType>::remove(const KeyType& key)
{
	auto r = this->BST<KeyType>::remove(key);
	if(!(this->_hot))
	{
		if(r)
		{
			r->color = BLACK;
			update_height(r);
		}
		return r;
	}

	if(this->color_removed == RED)
	{
		return r;
	}

	if(is_red(r))
	{
		r->color = BLACK;
		update_height(r);
		return r;
	}

	solve_black2(r);
	return r;
}

#endif