/***************************************************************************
 *  algo/test_sort_all_parameters.h
 *
 *  Part of the STXXL. See http://stxxl.sourceforge.net
 *
 *  Copyright (C) 2002 Roman Dementiev <dementiev@mpi-sb.mpg.de>
 *  Copyright (C) 2008 Andreas Beckmann <beckmann@cs.uni-frankfurt.de>
 *
 *  Distributed under the Boost Software License, Version 1.0.
 *  (See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 **************************************************************************/

#include <limits>
#include <stxxl/types>


template <typename KEY, unsigned SIZE>
struct my_type
{
    typedef KEY key_type;

    key_type _key;
    char _data[SIZE - sizeof(key_type)];

    my_type() { }
    my_type(key_type __key) : _key(__key) { }

#ifdef KEY_COMPARE
    key_type key() const
    {
        return _key;
    }

    static my_type<KEY, SIZE> min_value()
    {
        return my_type<KEY, SIZE>(0);
    }
    static my_type<KEY, SIZE> max_value()
    {
        return my_type<KEY, SIZE>(0xffffffff);
    }
#endif
};

template <typename KEY, unsigned SIZE>
std::ostream & operator << (std::ostream & o, const my_type<KEY, SIZE> obj)
{
#ifndef KEY_COMPARE
    o << obj._key;
#else
    o << obj.key();
#endif
    return o;
}

#ifndef KEY_COMPARE

template <typename KEY, unsigned SIZE>
bool operator < (const my_type<KEY, SIZE> & a, const my_type<KEY, SIZE> & b)
{
    return a._key < b._key;
}

template <typename KEY, unsigned SIZE>
bool operator == (const my_type<KEY, SIZE> & a, const my_type<KEY, SIZE> & b)
{
    return a._key == b._key;
}

template <typename KEY, unsigned SIZE>
bool operator != (const my_type<KEY, SIZE> & a, const my_type<KEY, SIZE> & b)
{
    return a._key != b._key;
}

template <typename T>
struct Cmp : public std::less<T>
{
    bool operator () (const T & a, const T & b) const
    {
        return a._key < b._key;
    }

    static T min_value()
    {
        return T(0);
    }
    static T max_value()
    {
        return T(0xffffffff);
    }
};

#else

template <typename KEY, unsigned SIZE>
bool operator < (const my_type<KEY, SIZE> & a, const my_type<KEY, SIZE> & b)
{
    return a.key() < b.key();
}

#endif

struct zero
{
    unsigned operator () ()
    {
        return 0;
    }
};
