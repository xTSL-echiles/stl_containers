#pragma once
#ifndef RBTREE_HPP
#define RBTREE_HPP


#include "../utils/iterator_traits.hpp"
#include "../utils/utils.hpp"
#include "../iterators/reverse_iterator.hpp"
namespace ft
{
    enum node_color{red = true, black = false};

    template<typename Val>
    struct RB_node
    {
        node_color  color;
        RB_node*    parent;
        RB_node*    right;
        RB_node*    left;
        Val         value;
    };

        template<typename T>
    class RB_iterator
    {
    private:
		    typedef typename ft::remove_const<T>::type value;
    public:
        RB_node<value>* _node;
    private:
        RB_node<value>* _last_elem;
        RB_node<value>* _first_elem;

    public:
        typedef T                               value_type;
        typedef T&                              reference;
        typedef T*                              pointer;
        typedef ft::bidirectional_iterator_tag  iterator_category;
        typedef std::ptrdiff_t                  difference_type;

		    operator RB_iterator<const T>()
        {
            return RB_iterator<const T>(this->_node, this->_last_elem, this->_first_elem);
        }

        RB_iterator() : _node(), _last_elem(), _first_elem() {}

        explicit RB_iterator(RB_node<value>* node, RB_node<value>* last_elem, RB_node<value>* first_elem) : _node(node), _last_elem(last_elem), _first_elem(first_elem) {}

        RB_iterator(const RB_iterator& iter) : _node(iter._node), _last_elem(iter._last_elem), _first_elem(iter._first_elem) {}

        RB_iterator& operator= (const RB_iterator& x)
        {
          if(this != &x)
          {
            this->_last_elem = x._last_elem;
            this->_first_elem = x._first_elem;
            this->_node = x._node;
          }
          return *this;
        }
        
        reference operator*() const 
        {
          return _node->value;
		    }
		    pointer operator->() const
        {
		    	return &_node->value;
		    }
        RB_iterator& operator++()
			  {	
          if(this->_node == _last_elem)
          {
            _node = _last_elem->parent;
            return *this;
          }
          else if (this->_node == NULL || this->_last_elem->parent == _node)
          {
            _node = _last_elem;
            return *this;
          }
				  if (this->_node->right == this->_last_elem && this->_node->parent != NULL)
				  {
				  	while (this->_node->parent != NULL && this->_node->parent->right == this->_node)
				  		this->_node = this->_node->parent;
				  	this->_node = this->_node->parent;
				  	return *this;
				  }
				  else if (this->_node->right != this->_last_elem && this->_node->right != NULL)
				  	this->_node = this->_node->right;
				  while (this->_node->left != this->_last_elem && this->_node->left != NULL)
				  	this->_node = this->_node->left;
				  return *this;
			  }
		    RB_iterator operator++(int) 
        {
			    RB_iterator tmp = *this;
			    ++*this;
			    return tmp;
        }

        RB_iterator& operator--()
        {
          if (this->_node == _last_elem)
					{
            _node = _last_elem->parent;
            return *this;
          }
          else if(this->_node == _first_elem)
          {
            _node = _last_elem;
            return *this;
          }
				  if (this->_node->left == this->_last_elem && this->_node->parent != NULL)
				  {
					  while (this->_node->parent != NULL && this->_node->parent->left == this->_node)
					  	this->_node = this->_node->parent;
					  if (this->_node->parent != NULL)
					  	this->_node = this->_node->parent;
					  return *this;
				  }
				  else if (this->_node->left != this->_last_elem && this->_node->left != NULL)
				  	this->_node = this->_node->left;
				  while (this->_node->right != this->_last_elem && this->_node->right != NULL)
				  	this->_node = this->_node->right;
				  return *this;
        }
        RB_iterator operator--(int)
        {
          RB_iterator tmp = *this;
          --*this;
          return (tmp);
        }
		    bool operator==(const RB_iterator& x) const 
        {
		    	return (_node == x._node);
		    }
		    bool operator!=(const RB_iterator& x) const 
        {
		    	return (_node != x._node);
		    }
    };
    template<typename Key, typename Val, typename KOV, typename Compare = std::less<Key>, typename Alloc = std::allocator<Val> >
    class RB_tree
    {
    public:
        typedef Val										                value_type;
		    typedef Compare								                key_compare;
		    typedef Alloc									                allocator_type;
		    typedef Key										                key_type;
		    typedef value_type*						                pointer;
		    typedef const value_type*			                const_pointer;
		    typedef value_type&						                reference;
		    typedef const value_type&			                const_reference;
		    typedef RB_node<Val>*					                node;
		    typedef std::size_t						                size_type;
		    typedef std::ptrdiff_t				                difference_type;
		    typedef RB_iterator<value_type>					      iterator;
		    typedef RB_iterator<const value_type>		      const_iterator;
        typedef ft::reverse_iterator<iterator>        reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;
    private:
        node                            _root;
        node                            _last_node;
        node                            _first_node;
		    size_type			                  _size;
        allocator_type 		              _alloc_data;
		    std::allocator<RB_node<Val> >    _alloc_node;
		    Compare				                  _comp;                  
    public:
        RB_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc_data(alloc), _alloc_node(), _comp(comp) 
        {
            //перед первой
            _first_node = _alloc_node.allocate(1);
            _first_node->right = 0;
            _first_node->left = 0;
            _first_node->parent = _root;
            //последняя
            _last_node =  _alloc_node.allocate(1);
            _last_node->right = 0;
            _last_node->left = 0;
            _last_node->parent = 0;
			      _root = _last_node;
            _size = 0;

        }
        RB_tree(const RB_tree& x) 
        {
            //перед первой
            _first_node = _alloc_node.allocate(1);
            _first_node->right = 0;
            _first_node->left = 0;
            _first_node->parent = _root;
            //последняя
            _last_node =  _alloc_node.allocate(1);
            _last_node->right = 0;
            _last_node->left = 0;
            _last_node->parent = 0;
			      _root = _last_node;
            _size = 0;
            *this = x;
        }
        RB_tree& operator= (const RB_tree& x)
        {
          if(this != &x)
          {
            insert(x.begin(), x.end());
          }
          return *this;
        }
        ~RB_tree()
        {
          clear();
          _alloc_node.deallocate(_last_node, 1);
          _alloc_node.deallocate(_first_node, 1);
          this->_size = 0;
        }
        allocator_type getAllocData() const
        {
          return _alloc_data;
        }
		    std::allocator<RB_node<Val> >    getAllocNode() const
        {
          return _alloc_node;
        }
		    Compare getCompare() const
        {
          return _comp;
        }
      private:
        void deleteFix(node x) 
        {
          node s;
          while (x != _root && x->color == black) 
          {
            if ( x == x->parent->left) 
            {
              s = x->parent->right;
              if (s->color == red) 
              {
                s->color = black;
                x->parent->color = red;
                leftRotate(x->parent);
                s = x->parent->right;
              }        
              if (s->left->color == black && s->right->color == black)
              {
                s->color = red;
                x = x->parent;
              }
              else
              {
                if (s->right->color == black)
                {
                  s->left->color = black;
                  s->color = red;
                  rightRotate(s);
                  s = x->parent->right;
                }
                s->color = x->parent->color;
                x->parent->color = black;
                s->right->color = black;
                leftRotate(x->parent);
                x = _root;
              }
            }
            else
            {
              s = x->parent->left;
              if (s->color == red)
              {
                s->color = black;
                x->parent->color = red;
                rightRotate(x->parent);
                s = x->parent->left;
              }
              if (s->right->color == black && s->right->color == black)
              {
                s->color = red;
                x = x->parent;
              }
              else
              {
                if (s->left->color == black)
                {
                  s->right->color = black;
                  s->color = red;
                  leftRotate(s);
                  s = x->parent->left;
                }
              s->color = x->parent->color;
              x->parent->color = black;
              s->left->color = black;
              rightRotate(x->parent);
              x = _root;
              }
            }
          }
          x->color = black;
        }

        void rbTransplant(node u, node v)
        {
          if (u->parent == NULL)
          {
            this->_root = v;
          }
          else if (u == u->parent->left)
          {
            u->parent->left = v;
          }
          else
          {
            u->parent->right = v;
          }
          v->parent = u->parent;
        }

        void deleteNodeHelper(node node_ftt, Key key)
        {
          node node_ft = node_ftt;
          node z = _last_node;
          node x, y;
          while (node_ft != _last_node)
          {
            if((_comp(KOV()(node_ft->value), key)))
              node_ft = node_ft->right;
            else if((_comp(key, KOV()(node_ft->value))))
              node_ft = node_ft->left;
            else
            {
              z = node_ft;
              break;
            }
          }
          if (z == _last_node) {
            return;
          }
          this->_size--;
          y = z;
          node_color y_original_color = y->color;
          if (z->left == _last_node) {
            x = z->right;
            rbTransplant(z, z->right);
          } else if (z->right == _last_node) {
            x = z->left;
            rbTransplant(z, z->left);
          } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
              x->parent = y;
            } else {
              rbTransplant(y, y->right);
              y->right = z->right;
              y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
          }

          _alloc_data.destroy(&z->value);
          _alloc_node.deallocate(z, 1);

          if (y_original_color == black) {
            deleteFix(x);
          }
            _last_node->parent = maximum(_root);
            _first_node->parent = minimum(_root);
        }     
        void leftRotate(node x)
        {
          node y = x->right;
          x->right = y->left;
          if (y->left != _last_node)
            y->left->parent = x;
          y->parent = x->parent;
          if (x->parent == NULL)
            this->_root = y;
          else if (x == x->parent->left)
            x->parent->left = y;
          else
            x->parent->right = y;
          y->left = x;
          x->parent = y;
        }

        void rightRotate(node x) 
        {
          node y = x->left;
          x->left = y->right;
          if (y->right != _last_node) 
            y->right->parent = x;
          y->parent = x->parent;
          if (x->parent == NULL) 
            this->_root = y;
          else if (x == x->parent->right)
            x->parent->right = y;
          else
            x->parent->left = y;
          y->right = x;
          x->parent = y;
        }

        void insertFix(node h) 
        {
          node u;
          while(h->parent->color == red)
          {
            if(h->parent == h->parent->parent->right)
            {
              u = h->parent->parent->left;
              if(u->color == red)
              {
                  u->color = black;
                  h->parent->color = black;
                  h->parent->parent->color = red;
                  h = h->parent->parent;
              }
              else
              {
                if(h == h->parent->left)
                {
                    h = h->parent;
                    rightRotate(h);
                }
                h->parent->color = black;
                h->parent->parent->color = red;
                leftRotate(h->parent->parent);
              }
            }
            else
            {
              u = h->parent->parent->right;
              if(u->color == red)
              {
                  u->color = black;
                  h->parent->color = black;
                  h->parent->parent->color = red;
                  h = h->parent->parent;
              }
              else
              {
                  if( h == h->parent->right)
                  {
                      h = h->parent;
                      leftRotate(h);
                  }
                  h->parent->color = black;
                  h->parent->parent->color = red;
                  rightRotate(h->parent->parent);
              }
            }
            if(h == _root)
              break;
          }
              _root->color = black;
          }

          node minimum(node h)
          {
            node tmp = h;
            while(tmp->left != _last_node && tmp->left != NULL)
              tmp = tmp->left;
            return tmp;
          }
          node maximum(node h)
          {
            node  tmp = h;
            while(tmp->right != _last_node && tmp->right != 0)
              tmp = tmp->right;
            return tmp;
          }
          node insert_private(const value_type& value) 
          {
            node x = this->_root;
            node y = NULL;
            node z = NULL;

            while (x != _last_node) 
            {
                y = x;
                if (_comp(value.first, KOV()(x->value)))
                    x = x->left;
                else if(_comp(KOV()(x->value), value.first))
                    x = x->right;
                else
                    return x;
            }
            this->_size++;
            if(y == NULL)
            {
                this->_root = NULL;
                this->_root = _alloc_node.allocate(1);
                _alloc_data.construct(&_root->value, value);
                this->_root->color = red;
                this->_root->left = _last_node;
                this->_root->right = _last_node;
                this->_root->parent = NULL;
                z = this->_root;
                _last_node->parent = _root;
                _first_node->parent = _root;
            }
            else if (_comp(value.first, KOV()(y->value)))
            {
                y->left = NULL;
                y->left = _alloc_node.allocate(1);
                _alloc_data.construct(&y->left->value, value);
                y->left->parent = y;
                y->left->right = _last_node;
                y->left->right = _last_node;
                y->left->color = red;
                z = y->left;
                if(_comp(KOV()(_last_node->parent->value), KOV()(y->left->value)))
                  _last_node->parent = z;
                if(_comp(KOV()(y->left->value), KOV()(_first_node->parent->value)))
                  _first_node->parent = z;
            } 
            else 
            {
                y->right = NULL;
                y->right = _alloc_node.allocate(1);
                _alloc_data.construct(&y->right->value, value);
                y->right->parent = y;
                y->right->left = _last_node;
                y->right->right = _last_node;
                y->right->color = red;
                z = y->right;
                if(_comp(KOV()(_last_node->parent->value), KOV()(y->right->value)))
                  _last_node->parent = z;
                if(_comp(KOV()(y->right->value), KOV()(_first_node->parent->value)))
                  _first_node->parent = z;
            }
            if (z->parent == NULL) 
            {
              z->color = black;
              return z;
            }
            if (z->parent->parent == NULL) 
            {
              return z;
            }
            insertFix(z);
            return z;
          }

          template<typename U>
          void swap(U& x, U& y)
          {
              U tmp = y;
              y = x;
              x = tmp;
          }
        public:
          iterator begin()
          {
            return iterator(_first_node->parent, _last_node, _first_node->parent);
          }
          const_iterator begin() const
          {
            return const_iterator(_first_node->parent, _last_node, _first_node->parent);
          }

          iterator end()
          {
            return iterator(_last_node, _last_node, _first_node->parent);
          }
          const_iterator end() const
          {
            return const_iterator(_last_node, _last_node, _first_node->parent);
          }

          reverse_iterator rend()
          {
            return reverse_iterator(begin());
          }
          const_reverse_iterator rend() const
          {
            return const_reverse_iterator(begin());
          }
          reverse_iterator rbegin()
          {
            return reverse_iterator(end());
          }
          const_reverse_iterator rbegin() const
          {
            return const_reverse_iterator(end());
          }
          bool empty() const
          {
              return (this->_size) ? false : true;
          }
          size_type size() const
          {
            return this->_size;
          }
          size_type max_size() const
          {
              return _alloc_node.max_size();
          }
          ft::pair<iterator,bool> insert (const value_type& val)
          {
            size_type temp_prev_size = this->_size;
            node h = insert_private(val);
            return (ft::pair<iterator, bool>(iterator(h, _last_node, _first_node->parent), (this->_size == temp_prev_size) ? false : true));
          }
          iterator insert (iterator position, const value_type& val)
          {
            (void)position;
            return iterator(insert_private(val));
          }
          template <class InputIterator>
          void insert (InputIterator first, InputIterator last)
          {
            for (; first != last; first++)
            {
              insert_private(*first);
            }
          }
          void erase (iterator position)
          {
            if(position._node == _last_node)
              return;
            deleteNodeHelper(_root, position->first);
          }
          size_type erase (const key_type& k)
          {
            size_type prev = this->_size;
            deleteNodeHelper(this->_root, k);
            return !(prev == this->_size);
          }
          void erase (iterator first, iterator last)
          {
            while(first != last)
              erase(first++);
          }
          iterator find (const key_type& k)
          {
            node x = this->_root;
            while (x != _last_node) 
            {
                if (_comp(k, KOV()(x->value)))
                    x = x->left;
                else if(_comp(KOV()(x->value), k))
                    x = x->right;
                else
                    break;
            }
            return iterator(x, _last_node, _first_node->parent);
          }

          const_iterator find (const key_type& k) const
          {
            node x = this->_root;
            while (x != _last_node) 
            {
                if (_comp(k, KOV()(x->value)))
                    x = x->left;
                else if(_comp(KOV()(x->value), k))
                    x = x->right;
                else
                    break;
            }
            return const_iterator(x, _last_node);
          }
          void swap (RB_tree& x)
          {
              swap(x._root, this->_root);
              swap(x._last_node, this->_last_node);
              swap(x._comp, this->_comp);
              swap(x._size, this->_size);
              swap(x._first_node, this->_first_node);
          }
        public:
          void clear()
          {
            clear(this->_root);
            this->_root = _last_node;
            _last_node->parent = _root;
            _first_node->parent = _root;
            this->_size = 0;
          }
        private:
          void clear(node tmp)
          {
              if(tmp == _last_node)
                  return;
              if(tmp->left != _last_node && tmp->left != NULL)
                clear(tmp->left);
              if(tmp->right != _last_node && tmp->right != NULL)
                clear(tmp->right);
              _alloc_node.deallocate(tmp, 1);
              tmp = _last_node;
          }
        public:
        size_type count (const key_type& k) const
        {
          node x = this->_root;
          while (x != _last_node) 
          {
              if (_comp(k, KOV()(x->value)))
                  x = x->left;
              else if(_comp(KOV()(x->value), k))
                  x = x->right;
              else
                  return 1;
          }
          return 0;
        }

        iterator lower_bound (const key_type& k)
        {
			    node x = this->_root;
			    node y = _last_node;
			    while (x != _last_node) {
			    	if (!_comp(KOV()(x->value), k))
			    		y = x, x = x->left;
			    	else
			    		x = x->right;
			    }
			    return iterator(y, _last_node, _first_node->parent);
        }

        const_iterator lower_bound (const key_type& k) const
        {
			    node x = this->_root;
			    node y = _last_node;
			    while (x != _last_node) {
			    	if (!_comp(KOV()(x->value), k))
			    		y = x, x = x->left;
			    	else
			    		x = x->right;
			    }
			    return const_iterator(y, _last_node, _first_node->parent);
        }

        iterator upper_bound (const key_type& k)
        {
          node x = this->_root;
			    node y = _last_node;
			    while (x != _last_node) {
			    	if (_comp(k, KOV()(x->value))) {
			    		y = x;
			    		x = x->left;
			    	}
			    	else
			    		x = x->right;
			    }
			    return iterator(y, _last_node, _first_node->parent);
        }
        const_iterator upper_bound (const key_type& k) const
        {
          node x = this->_root;
			    node y = _last_node;
			    while (x != _last_node) {
			    	if (_comp(k, KOV()(x->value))) {
			    		y = x;
			    		x = x->left;
			    	}
			    	else
			    		x = x->right;
			    }
			    return const_iterator(y, _last_node, _first_node->parent);    
        }
        pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
          return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }
        pair<iterator,iterator>             equal_range (const key_type& k)
        {
          return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }

    };

}

#endif