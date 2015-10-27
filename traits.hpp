#pragma once
struct true_type {};
struct false_type {};

template <typename T>
struct is_integer
{
    enum { result = 0 };
    typedef false_type type;
};
template <>
struct is_integer<int>
{
    enum { result = 1 };
    typedef true_type type;
};
//and so on
