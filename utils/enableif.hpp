#pragma once
#ifndef ENABLEIF_HPP
#define ENABLEIF_HPP

#include <sstream>
namespace ft
{
    template<bool B, typename T>
    struct enable_if{};

    template<typename T>
    struct enable_if<true, T>{ typedef T type;};

    template<typename _Tp>
    struct remove_const
    { typedef _Tp     type; };

    template<typename _Tp>
    struct remove_const<_Tp const>
    { typedef _Tp     type; };

    template<typename T>
    struct is_integral_helper
    {
        static const bool value = false;
    };

    template<>
    struct is_integral_helper<bool>
    {
        const static bool value = true;
    };
    
    template<>
    struct is_integral_helper<char>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<signed char>
    {
        const static bool value = true;
    };
    

    template<>
    struct is_integral_helper<unsigned char>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<wchar_t>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<short>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<unsigned short>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<int>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<unsigned int>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<long>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<unsigned long>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<long long>
    {
        const static bool value = true;
    };

    template<>
    struct is_integral_helper<unsigned long long>
    {
        const static bool value = true;
    };
    
    template<typename T>
    struct is_integral
    {
        const static bool value = is_integral_helper<typename remove_const<T>::type>::value;
    };
    
    

    // template<typename T>
    // struct is_class
    // {
    // private:
    //     template<typename C>
    //     static int func_check(int C::* ){return 0;}
    //     template<typename C>
    //     static char func_check(C){return 0;}
    // public:
    //     static const bool value = (sizeof(func_check<T>(0)) == sizeof(int));
    // };
}



#endif