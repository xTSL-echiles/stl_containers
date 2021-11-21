#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
    
  template<typename _Pair>
    struct select_1st
    {
      typename _Pair::first_type&
      operator()(_Pair& __x) const
      { return __x.first; }

      const typename _Pair::first_type&
      operator()(const _Pair& __x) const
      { return __x.first; }
    };

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1) 
                return false;
            else if (*first1 < *first2) 
                return true;
            ++first1; ++first2;
        }
        return (first2 != last2);
    }

    template<typename T>
	std::string to_string(const T& value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

    template <class Arg1, class Arg2, class Result>
    struct binary_function 
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

}


#endif