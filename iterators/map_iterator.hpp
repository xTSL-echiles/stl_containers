#pragma once
#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <unistd.h>
#include "enableif.hpp"
#include "iterator_traits.hpp"
namespace ft
{   
    template<typename Val>
    struct Node
    {
        bool                    color;
        Val                     data;
        Node*                   parent;
        Node*                   left;
        Node*                   right;
    };

    template<typename val>
    class map_iterator
    {
    private:
        typedef typename ft::remove_const<val>::type value;
        typedef ft::Node<value>   Node;
        Node*   _last_elem;
        Node*   _first_elem;
    public:
        Node*   _root;
        typedef val                             value_type;
        typedef val*                            pointer;
        typedef val&                            reference;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::size_t                     size_type;
        typedef ft::bidirectional_iterator_tag  iterator_category;
        operator map_iterator<const val>()
        {
            return map_iterator<val const>(_root, _last_elem, _first_elem);
        }
        map_iterator() : _root(NULL), _last_elem(NULL), _first_elem(NULL) {}
        map_iterator(Node* node, Node* last_elem,  Node* first_elem) : _root(node)
        {
            _last_elem = last_elem;
            _first_elem = first_elem;
        }
        map_iterator(const map_iterator& it)
        {
            *this = it;
        }
        const map_iterator& operator =(const map_iterator& copy) 
        {
            if(this != &copy)
            {
                this->_root = copy._root;
                this->_last_elem = copy._last_elem;
                this->_first_elem = copy._first_elem;
            }
            return *this;
        }
        bool operator == (const map_iterator& it)
        {
            return (it._root == this->_root);
        }

        bool operator != (const map_iterator& it)
        {
            return !(it._root == this->_root);
        }
        
        map_iterator& operator++(void)
		{
            if (this->_node == _last_elem->parent)
                this->_node = _last_elem;
            if (this->_node->right != _last_elem && this->_node->right != NULL)
			{
				this->_node = this->_node->right;
				while (this->_node->left != _last_elem && this->_node->left != NULL)
				    this->_node = this->_node->left;
			}
			else if (this->_node == this->_node->parent->left && this->_node != _last_elem)
				this->_node = this->_node->parent;
			else if (this->_node == this->_node->parent->right && this->_node != _last_elem)
			{
				while (this->_node != this->_node->parent->left)
                    this->_node = this->_node->parent;
                this->_node = this->_node->parent;
			}
			return *this;
        }

        map_iterator operator++(int)
        {
            map_iterator tmp = *this;
            ++*this;
            return (tmp);
        }

        map_iterator& operator--(void)
        {
            if(this->_root == _first_elem)
            {
                this->_root = _first_elem->left;
                return *this;
            }
			if (this->_root->left != _last_elem && this->_root->left != NULL)
			{
				this->_root = this->_root->left;
				while (this->_root->right != _last_elem)
					this->_root = this->_root->right;
			}
			else if (this->_root == this->_root->parent->right)
				this->_root = this->_root->parent;
			else if (this->_root == this->_root->parent->left)
			{
				while (this->_root != this->_root->parent->right)
					this->_root = this->_root->parent;
				this->_root = this->_root->parent;
			}
            return *this;
        }
        
        map_iterator operator--(int)
        {
            map_iterator tmp = *this;
            --*this;
            return(tmp);
        }

        reference operator*() const
        {
            return (_root->data);
        }
        
        pointer operator ->() const
        {
            return (&_root->data);
        }
        
    };
} 

#endif