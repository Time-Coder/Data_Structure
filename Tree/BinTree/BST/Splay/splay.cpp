#ifdef SPLAY_H

template<class KeyType>
void Splay<KeyType>::splay(typename BinTree<KeyType>::Node* v)
{
	if(!v)
	{
		return;
	}
	while(v->parent)
	{
		auto p = v->parent;
		auto g = p->parent;
		if(!g)
		{
			this->islchild(v) ? this->zig(p) : this->zag(p);
		}
		else if(g->lchild == p && p->lchild == v)
		{
			this->zig(g);
			this->zig(p);
		}
		else if(g->rchild == p && p->rchild == v)
		{
			this->zag(g);
			this->zag(p);
		}
		else if(g->lchild == p && p->rchild == v)
		{
			this->zag(p);
			this->zig(g);
		}
		else if(g->rchild == p && p->lchild == v)
		{
			this->zig(p);
			this->zag(g);
		}
	}
}

template<class KeyType>
typename BinTree<KeyType>::Node*& Splay<KeyType>::search(const KeyType& key)
{
	auto v = this->BST<KeyType>::search(key);
	splay(v ? v : this->_hot);
	return v ? this->_root : v;
}

template<class KeyType>
typename BinTree<KeyType>::Node* Splay<KeyType>::insert(const KeyType& key)
{
	auto v = search(key);
	if(v)
	{
		return v;
	}

	auto old_root = this->_root;
	if(!old_root)
	{
		this->_root = this->new_Node(key);
	}
	else if(old_root->data < key)
	{
		this->_root = this->_root->parent = this->new_Node(key, this->_root->height+1, NULL, this->_root, this->_root->rchild);
		if(old_root->rchild)
		{
			old_root->rchild->parent = this->_root;
			old_root->rchild = NULL;
		}
	}
	else
	{
		this->_root = this->_root->parent = this->new_Node(key, this->_root->height+1, NULL, this->_root->lchild, this->_root);
		if(old_root->lchild)
		{
			old_root->lchild->parent = this->_root;
			old_root->lchild = NULL;
		}
	}
	this->_size++;

	return this->_root;
}

template<class KeyType>
typename BinTree<KeyType>::Node* Splay<KeyType>::remove(const KeyType& key)
{
	if(!search(key))
	{
		return this->_root;
	}

	this->_size--;
	auto TL = this->_root->lchild;
	auto TR = this->_root->rchild;
	delete this->_root;
	this->_root = NULL;
	if(TR)
	{
		this->_root = TR;
		this->_root->parent = NULL;
		search(key);
		if(TL)
		{
			this->_root->lchild = TL;
			TL->parent = this->_root;
			this->update_height(this->_root);
		}
	}
	else if(TL)
	{
		this->_root = TL;
		this->_root->parent = NULL;
		search(key);
	}

	return this->_root;
}


#endif