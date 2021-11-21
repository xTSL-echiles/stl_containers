#pragma once
#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "../utils/enableif.hpp"

namespace ft
{
    template <class Iter>
    class reverse_iterator
    {
    private:
        Iter _it;
    public:
        typedef Iter                             iterator_type;
        typedef typename Iter::iterator_category iterator_category;
        typedef typename Iter::value_type        value_type;
        typedef typename Iter::difference_type   difference_type;
        typedef typename Iter::pointer           pointer;
        typedef typename Iter::reference         reference;
        reverse_iterator() : _it(){}
        explicit reverse_iterator(iterator_type it) : _it(it) {}
        template <typename U>
        reverse_iterator (const reverse_iterator<U>& rev_it) : _it(rev_it.base()) {}
        template<class T>
			reverse_iterator& operator=(const reverse_iterator<T>& other) {
			_it= other.base();
			return *this;
		}
		iterator_type base() const {
			return _it;
		}
		reference operator*() const {
			Iter tmp = _it;
			return *--tmp;
		}
		pointer operator->() const {
			return &(operator*());
		}
		reference operator[](difference_type n) const {
			return *(*this + n);
		}
		reverse_iterator& operator++() {
			--_it;
			return *this;
		}
		reverse_iterator& operator--() {
			++_it;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			--_it;
			return tmp;
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			++_it;
			return tmp;
		}
		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(_it - n);
		}
		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(_it + n);
		}
		reverse_iterator& operator+=(difference_type n) {
			_it -= n;
			return *this;
		}
		reverse_iterator& operator-=(const difference_type n) {
			_it += n;
			return *this;
		}
    };
    template <class Iter1, class Iter2>
	inline bool operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
		return x.base() == y.base();
	}
	template <class Iter1, class Iter2>
	inline bool operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
		return x.base() != y.base();
	}
	template <class Iter1, class Iter2>
	inline bool operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
		return x.base() < y.base();
	}
	template <class Iter1, class Iter2>
	inline bool operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
		return x.base() <= y.base();
	}
	template <class Iter1, class Iter2>
	inline bool operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
		return x.base() > y.base();
	}
	template <class Iter1, class Iter2>
	inline bool operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
		return x.base() >= y.base();
	}
	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type
	operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
		return y.base() - x.base();
	}
	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
									 const reverse_iterator<Iter>& x) {
		return reverse_iterator<Iter>(x.base() - n);
	}
}
#endif