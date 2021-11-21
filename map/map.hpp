#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include <memory> // allocator
#include <iostream> // std::
#include "../utils/pair.hpp"
#include "../utils/enableif.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils/utils.hpp"
#include "RBtree.hpp"
namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
    class map
    {
    public:
        typedef Key                     key_type;
        typedef T                       mapped_type;
        typedef ft::pair< const Key, T>  value_type;
        typedef Compare                 key_compare; 
        typedef Alloc                   allocator_type;
        typedef value_type*             pointer;
        typedef value_type&             reference;
        typedef const value_type*       const_pointer;
        typedef const value_type&       const_reference;
        typedef  __gnu_cxx::ptrdiff_t   difference_type;
        typedef std::size_t             size_type;
    private:
        typedef ft::RB_tree<Key, value_type, ft::select_1st<value_type>, key_compare, allocator_type> Tree;
        Tree _tree;
    public:
        typedef typename Tree::iterator                 iterator;
        typedef typename Tree::const_iterator           const_iterator;
        typedef typename Tree::reverse_iterator         reverse_iterator;
        typedef typename Tree::const_reverse_iterator   const_reverse_iterator;

        class value_compare : public ft::binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc)
        {
            _tree.insert(first, last);
        }

        map (const map& x) : _tree(x._tree) {}

        map& operator= (const map& x)
        {
            _tree = x._tree;
        }
        ~map(){}
        iterator begin()
        {
            return _tree.begin();
        }
        const_iterator begin() const
        {
            return _tree.begin();
        }
        iterator end()
        {
            return _tree.end();
        }
        const_iterator end() const
        {
            return _tree.end();
        }
        const_reverse_iterator rbegin() const
        {
            return _tree.rbegin();
        }
        reverse_iterator rbegin()
        {
            return _tree.rbegin();
        }
        reverse_iterator rend()
        {
            return _tree.rend();
        }
        const_reverse_iterator rend() const
        {
            return _tree.rend();
        }

        bool empty() const
        {
            return _tree.empty();
        }

        size_type size() const
        {
          return _tree.size();
        }
        size_type max_size() const
        {
            return _tree.max_size();
        }
        mapped_type& operator[] (const key_type& k)
        {
          return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
        }
        ft::pair<iterator,bool> insert (const value_type& val)
        {
          return _tree.insert(val);
        }
        iterator insert (iterator position, const value_type& val)
        {
          return _tree.insert(position, val);
        }
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            return _tree.insert(first, last); 
        }
        void erase (iterator position)
        {
            _tree.erase(position);
        }
        size_type erase (const key_type& k)
        {
            return _tree.erase(k);
        }
        void erase (iterator first, iterator last)
        {
            _tree.erase(first, last);
        }
        void swap (map& x)
        {
            _tree.swap(x._tree);
        }
        void clear()
        {
            _tree.clear();
        }
        iterator lower_bound (const key_type& k)
        {
            return _tree.lower_bound(k);
        }
        const_iterator lower_bound (const key_type& k) const
        {
            return _tree.lower_bound(k);
        }
        iterator upper_bound (const key_type& k)
        {
            return _tree.upper_bound(k);
        }
        const_iterator upper_bound (const key_type& k) const
        {
            return _tree.upper_bound(k);
        }
        pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            return _tree.equal_range(k);
        }
        pair<iterator,iterator>             equal_range (const key_type& k)
        {
            return _tree.equal_range(k);
        }
        allocator_type get_allocator() const
        {
            return _tree.getAllocData();
        }
        key_compare key_comp() const
        {
            return _tree.getCompare();
        }
        value_compare value_comp() const
        {
            return value_compare(_tree.getCompare());
        }
        iterator find (const key_type& k)
        {
            return _tree.find(k);
        }
        const_iterator find (const key_type& k) const
        {
            return _tree.find(k);
        }
        size_type count (const key_type& k) const
        {
            return _tree.count(k);
        }

    };
}
#endif