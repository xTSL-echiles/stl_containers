#pragma once
#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"
namespace ft
{
   template <class T>
   class VectorIterator
   {
   private:
      T* current;
   public:
      typedef T value_type;
      typedef T* pointer;
      typedef const T* const_pointer;
      typedef T& reference;
      typedef const T& const_reference;
      typedef __gnu_cxx::ptrdiff_t difference_type;
      typedef ft::random_access_iterator_tag iterator_category;
      VectorIterator() : current(NULL) {}
      VectorIterator(const VectorIterator &a) : current(a.current) {}
      VectorIterator(pointer a) : current(a) {}
      ~VectorIterator(){}
      operator VectorIterator<const value_type>()
      {
         return VectorIterator<value_type const>(current);
      }
      VectorIterator& operator=(const VectorIterator &a)
      {
         if(&a != this)
         {
            this->current = a.current;
         }
         return *this;
      }
      pointer base() const
      {
         return this->current;
      }
      VectorIterator operator++(void)
      {
         ++this->current;
         return *this;
      }
      
      VectorIterator operator++(int)
      {
         VectorIterator temp(*this);
         ++this->current;
         return temp;
      }
      
      VectorIterator operator--(void)
      {
         --this->current;
         return *this;
      }
      
      VectorIterator operator--(int)
      {
         VectorIterator temp(*this);
         --this->current;
         return temp;
      }

      bool operator==(const VectorIterator &a) const
      {
         return this->current == a.base();
      }
      
      bool operator!=(const VectorIterator &a) const
      {
         return this->current != a.base();
      }

      reference operator*()
      {
         return *(this->current);
      }
      const_reference operator*() const
      {
         return *(this->current);
      }
      pointer operator->()
      {
         return this->current;
      }
      const_pointer operator->() const
      {
         return this->current;
      }
      difference_type operator-(const VectorIterator &a) const 
      {
		   return (this->current - a.base());
      }
      VectorIterator operator-(difference_type n) const
      {
         return (this->current - n);
      }
      VectorIterator operator-(difference_type n)
      {
         return (this->current - n);
      }
      reference operator[](difference_type i)
      {
         return *(this->current + i);
      }
      const_reference operator[](difference_type i) const
      {
         return *(this->current + i);
      }
      VectorIterator operator+(difference_type i) const
      {
         return this->current + i;
      }
      VectorIterator operator+(difference_type i)
      {
         return this->current + i;
      }

      VectorIterator operator+=(difference_type value)
      {
         current += value;
         return *this;
      }
      
      VectorIterator operator-=(difference_type value)
      {
         current -= value;
         return *this;
      }

      bool operator>( const VectorIterator &a) const
      {
         return (this->current > a.base());
      }

      bool operator<(const VectorIterator &a) const
      {
         return (this->current < a.base());
      }

      bool operator>=(const VectorIterator &a) const
      {
         return (this->current >= a.base());
      }

      bool operator<=(const VectorIterator &a) const
      {
         return (this->current <= a.base());
      }
   };

   template <class T>
   VectorIterator<T> operator+(typename VectorIterator<T>::difference_type i, VectorIterator<T> &tmp)
   {
      return tmp + i;
   }

   template <class T>
   VectorIterator<T> operator+(VectorIterator<T> &tmp, typename VectorIterator<T>::difference_type i)
   {
      return tmp + i;
   }
}
#endif