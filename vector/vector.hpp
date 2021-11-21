#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include "../iterators/vector_itereator.hpp"
// #include "reverse_vector_iterator.hpp"
#include "../utils/enableif.hpp"
#include "../utils/utils.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
   template <typename T, typename Allocator = std::allocator<T> >
   class vector
   {
   public:
      typedef T                                          value_type;
      typedef Allocator                                  allocator_type;
      typedef typename allocator_type::pointer           pointer;
      typedef typename allocator_type::reference         reference;
      typedef typename allocator_type::const_pointer     const_pointer;
      typedef typename allocator_type::const_reference   const_reference;
      typedef std::ptrdiff_t                             difference_type;
      typedef std::size_t                                size_type;

      typedef ft::VectorIterator<value_type>                 iterator;
      typedef ft::VectorIterator<value_type const>           const_iterator;
      typedef ft::reverse_iterator<iterator>                 reverse_iterator;
      typedef ft::reverse_iterator<const_iterator>           const_reverse_iterator;
      //------------------------------------constructors------------------------------------------
      vector(const allocator_type& alloc = allocator_type() ) :
      _pointer(),
      _capacity(0), 
      _size(0),
      _allocator(alloc)
      {}

      vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
      {
         _allocator = alloc;
         _size = n;
         _capacity = _size;
         _pointer = _allocator.allocate(n);
         for (size_t i = 0; i < _size; i++)
         {
            _allocator.construct(_pointer + i, val); 
         }
      }
      
      vector (const vector &x) : _size(x._size), _capacity(x._capacity), _allocator(x._allocator)
      {
         _pointer = _allocator.allocate(_capacity);
         for (size_type i = 0; i < _size; i++)
         {
            _allocator.construct(&_pointer[i], x._pointer[i]);
         }
      }

      template <class InputIterator>
      vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type()) : _allocator(alloc)
      {
         difference_type len = last - first;
         _pointer = _allocator.allocate(len);
         _size = len;
         _capacity = len;
         for (size_t i = 0; i < _size; i++)
         {
            _allocator.construct(_pointer + i, *(first + i));
         }
      }
      //-------------------------------------operators------------------------------------------
      vector& operator=(const vector &x)
      {
         if(this != &x)
         {
            if(this->_capacity > 0)
               _allocator.deallocate(_pointer, _capacity);
            this->_allocator = x._allocator;
            this->_size = x._size;
            this->_capacity = x._capacity;
            this->_pointer = this->_allocator.allocate(_capacity);
            for (size_t i = 0; i < x._size; i++)
            {
               _allocator.construct(this->_pointer + i, *(x._pointer + i));
            }
         }
         return *this;
      }

      reference operator[](size_type n)
      {
         return *(this->_pointer + n);
      }
      
      const_reference operator[] (size_type n) const
      {
         return *(this->_pointer + n);
      }
      //-------------------------------------destructor------------------------------------------
      ~vector()
      {
         for (size_t i = 0; i < _capacity; i++)
         {
            _allocator.destroy(_pointer + i);
         }
         
         _allocator.deallocate(_pointer, _capacity);
      }
      //-------------------------------------private-field----------------------------------------
      //-------------------------------------methods
      
      iterator begin(void) 
      {
         return iterator(this->_pointer);
      }
      
      const_iterator begin() const
      {
         return const_iterator(this->_pointer);
      }

      reverse_iterator rbegin (void)
      {
         return reverse_iterator(end());
      }
      const_reverse_iterator rbegin() const
      {
         return const_reverse_iterator(end());
      }

      iterator end()
      {
         return iterator(this->_pointer + _size);
      }

      const_iterator end() const
      {
         return const_iterator(this->_pointer + _size);
      }

      reverse_iterator rend()
      {
         return reverse_iterator(begin());
      }
      
      const_reverse_iterator rend() const
      {
         return const_reverse_iterator(begin());
      }

      size_type size() const
      {
         return this->_size;
      }

      size_type max_size() const
      {
         return _allocator.max_size(); // походу переписать
      }

      void resize(size_type n, value_type val = value_type())
      {
         if(n == this->_size)
            return ;
         else if(n > this->_size)
         {
            while(n > _size)
            {
               if(n > _capacity)
               {
                  newCapacity(n);
               }
               _allocator.construct(this->_pointer+ (_size++), val);
            }
         }
         else if( n < this->_size)
         {
            for (size_t i = _size; i > n; i--)
            {
               _allocator.destroy(_pointer+i);
            }
            _size = n;
         }
      }

      size_type capacity() const
      {
         return this->_capacity;
      }

      bool empty() const
      {
         return (this->_size == 0);
      }

      void reserve(size_type n)
      {
         capCheck(n);
         if(n > _capacity)
         {
            pointer tmp;
            tmp = _allocator.allocate(n);
            for (size_t i = 0; i < _size; i++)
            {
               _allocator.construct(tmp + i, *(this->_pointer + i));
            }
            _allocator.deallocate(_pointer, _capacity);
            _capacity = n;
            this->_pointer = tmp;
         }
      }
      reference at(size_type n)
      {
         if(n >= this->_size)
            throw std::out_of_range("vector::at_check: n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) +")");
         return this->_pointer[n];
      }
      const_reference at(size_type n) const
      {
         if(n >= this->_size)
            throw std::out_of_range("vector::at_check: n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) +")");
         return this->_pointer[n];
      }
      reference front()
      {
         return this->_pointer[0];
      }
      const_reference front() const
      {
         return this->_pointer[0];
      }
      reference back(void)
      {
         return this->_pointer[_size - 1];
      }
      const_reference back(void) const
      {
         return this->_pointer[_size - 1];
      }
      void assign(size_type n, const value_type &val)
      {
         clear();
         if(n > this->_capacity)
            newCapacity(n);
         for (size_t i = 0; i < n; i++)
         {
            _allocator.construct(this->_pointer + i, val);
            this->_size++;
         }
      }
      template <class InputIterator>
      void assign (InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
      {
         clear();
         difference_type len = last-first;
         if(static_cast<size_type>(len) > this->_capacity)
            newCapacity((last - first));
         for (difference_type i = 0; i < len; i++)
         {
            _allocator.construct(this->_pointer + i, *(first + i));
            this->_size++;
         }
      }

      void push_back(const value_type& val)
      {
         if(_size + 1 > _capacity)
            newCapacity(((this->_size == 0) ? 1 : this->_size * 2));
         this->_allocator.construct(this->_pointer + (this->_size++), val);
      }

      void pop_back(void)
      {
         this->_allocator.destroy(this->_pointer + (this->_size-- -1));
      }

      void clear()
      {
         for (size_t i = 0; i < _size; i++)
         {
            this->_allocator.destroy(this->_pointer + i);
         }
         this->_size = 0;
      }
      void swap(vector& x)
      {
         vector tmp(x);
         x = *this;
         *this = tmp;
      }
      Allocator get_allocator() const
      {
         return this->_allocator;
      }
      //----------------------------------------------------------------------------

      iterator insert (iterator position, const value_type& val)
      {
         pointer tmp;
         difference_type where_is =  position - begin();
         if(_size + 1 > _capacity)
         {
            capCheck((_size == 0) ? 1 : _size * 2);
            tmp = _allocator.allocate((_size == 0) ? 1 : _size * 2);
            size_type i = 0;
            for (; i < static_cast<size_type>(where_is); i++)
            {
               _allocator.construct(tmp + i, *(_pointer + i));
            }
            _allocator.construct(tmp + i++, val);
            for (; i < _size + 1; i++)
            {
               _allocator.construct(tmp + i, *(_pointer + i - 1));
            }
            _allocator.deallocate(_pointer, _capacity);
            _capacity = (_size == 0) ? 1 : _size * 2;
            _pointer = tmp;
         }
         else
         {
            size_type i;
            for (i = _size; i > static_cast<size_type>(where_is); i--)
            {
               _pointer[i] = _pointer[i - 1];
            }
            _allocator.construct(_pointer + i, val);
         }
         _size++;
         return iterator(_pointer + where_is);
      }

      void insert (iterator position, size_type n, const value_type& val)
      {
         pointer tmp;
         difference_type where_is =  position - begin();
         if(_size + n > _capacity)
         {
            capCheck((_size == 0) ? 1 : ((_size * 2 < _size + n) ? _size + n : _size * 2));
            tmp = _allocator.allocate(((_size == 0) ? 1 : ((_size * 2 < _size + n) ? _size + n : _size * 2)));
            size_type i = 0;
            for (; i < static_cast<size_type>(where_is); i++)
            {
                  _allocator.construct(tmp + i, *(_pointer + i));
            }
            for (size_type j = 0; j < n; j++)
            {
                _allocator.construct(tmp + i + j, val);
            }
            for (; i < _size; i++)
            {
               _allocator.construct(tmp + i + n, *(_pointer + i));
            }
            _allocator.deallocate(_pointer, _capacity);
            _capacity = ((_size == 0) ? 1 : ((_size * 2 < _size + n) ? _size + n : _size * 2));
            _pointer = tmp;
         }
         else
         {
            size_type i;
            for (i = _size; i > where_is + n; i--)
            {
               _pointer[i + n - 1] = _pointer[i - 1];
            }
            for (size_t j = 0; i < n; j++)
            {
               _allocator.construct(_pointer + i--, val);
            }
         }
         _size+=n;
      }

      template <class InputIterator>
      void insert (iterator position, InputIterator first, 
                                      typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
      {
         difference_type where_is = position - begin();
         difference_type len = last - first;
         pointer tmp;
         if(_size + len > _capacity)
         {
            capCheck((_size == 0) ? 1 : ((_size * 2 < _size + len) ? _size + len : _size * 2));
            tmp = _allocator.allocate(((_size == 0) ? 1 : ((_size * 2 < _size + len) ? _size + len : _size * 2)));
            difference_type i = 0;
            for (; i < where_is ; i++)
            {
               _allocator.construct(tmp + i, *(_pointer + i));
            }
            for (difference_type j = 0; j < len; j++)
            {
                _allocator.construct(tmp + i + j, *(first + j));
            } 
            for (; i < _size; i++)
            {
               _allocator.construct(tmp + i + len, *(_pointer + i));
            }
            _allocator.deallocate(_pointer, _capacity);
            _capacity = ((_size == 0) ? 1 : ((_size * 2 < _size + len) ? _size + len : _size * 2));
            _pointer = tmp;
         }
         else
         {
            size_type i = 0;
            for (i = _size; i > static_cast<size_type>(where_is + len); i--)
            {
               _pointer[i + len - 1] = _pointer[i - 1];
            }
            for (size_type j = 0; i < static_cast<size_type>(len); j++)
            {
               _allocator.construct(_pointer + i--, *(first + j));
            }
         }
         _size += len;
      }
//-------------------------------------------------------------------
      // переписать уудаление после нахождения удаляемого
      iterator erase (iterator position)
      {
         size_type where = position - begin();
         _allocator.destroy(&(*position));
         for (size_type i = where; i < _size; i++)
         {
            _pointer[i] = _pointer[i + 1];
         }
         _allocator.destroy(&_pointer[_size]);
         this->_size--;
         return iterator(_pointer);
      }
      iterator erase (iterator first, iterator last)
      {
         difference_type where_is = first - begin();
         difference_type len = last - first;
         pointer tmp;
         if(len == 0)
            return iterator(_pointer);
         size_type i;
         for (i = where_is; i < _size - len; i++)
         {
            _pointer[i] = _pointer[i + len];
         }
         this->_size -= len;
         return (_pointer);
      }

   private:
      void newCapacity(size_type new_cap)
      {
         capCheck(new_cap);
         pointer tmp;
         tmp = _allocator.allocate(new_cap);
         for (size_t i = 0; i < _size; i++)
         {
            _allocator.construct(tmp + i, *(this->_pointer + i));
         }
         _allocator.deallocate(_pointer, _capacity);
         _capacity = new_cap;
         this->_pointer = tmp;
      }

      void capCheck(size_type new_cap)
      {
         if(new_cap < 0 || new_cap > _allocator.max_size())
            throw std::out_of_range("cannot create std::vector larger than max_size()");
      }

      pointer     _pointer;
   	size_type   _capacity;
      size_type   _size;
      Allocator   _allocator;
   };
   
   template <class T, class Alloc>
   bool operator ==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
   {
      if (lhs.size() != rhs.size())
			return false;
		for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return true;
   }

   template <class T, class Alloc>
   bool operator !=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
   {
      return !(lhs == rhs);
   }

   template <class T, class Alloc>
   bool operator <(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
   {
      return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
   }

   template <class T, class Alloc>
   bool operator <=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
   {
      return !(rhs < lhs);
   }

   template <class T, class Alloc>
   bool operator >(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
   {
      return rhs < lhs;
   }

   template <class T, class Alloc>
   bool operator >=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
   {
      return !(lhs < rhs);
   }

   template <class T, class Alloc>
   void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
   {
      vector<T, Alloc> tmp(x);
      x = y;
      y = tmp;
   }
}
#endif