#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "utils_iterator.hpp"

namespace ft 
{
  template <class T, bool isconst = false>
  struct iterator 
  {
    typedef iterator<T, isconst>      type;

    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef typename choose_type<isconst, const T&, T&>::type  reference;
    typedef typename choose_type<isconst, const T*, T*>::type  pointer;

    iterator() : _ptr(NULL) {};
    iterator(value_type *ptr) : _ptr(ptr) {};
    iterator(const iterator<T, false> &copy) : _ptr(copy._ptr) {};

    virtual ~iterator() {};

    type   &operator = (const type &rhs)
    {
      _ptr = rhs._ptr;
      return *this;
    };

    type     &operator ++ ()
    {
      _ptr++;
      return *this;
    };
    
    type     operator ++ (int) 
    {
      type tmp = *this;
      ++(*this);
      return tmp;
    };
    
    type     &operator -- () 
    {
      _ptr--;
      return *this;
    };
    
    type     operator -- (int) 
    {
        type tmp = *this;
        --(*this);
        return tmp;
    };
    
    type     operator += (int n) 
    {
        _ptr += n;
        return *this;
    };
    
    type     operator -= (int n) 
    {
        _ptr -= n;
        return *this;
    };
    
    type     operator + (int n) const 
    {
        type  tmp(*this);
        return tmp += n;
    };
    
    type     operator - (int n) const 
    {
        type  tmp(*this);
        return tmp -= n;
    };
    
    difference_type     operator - (iterator<T, true> it) const 
    {
        return _ptr - it._ptr;
    };
    
    reference operator[] (size_t n) const 
    {
        return _ptr[n];
    };

    bool      operator < (const iterator<T, true> &rhs) const   
    {
        return _ptr < rhs._ptr;
    };
    bool      operator > (const iterator<T, true> &rhs) const
    {
        return _ptr > rhs._ptr;
    };
    bool      operator <= (const iterator<T, true> &rhs) const
    {
        return _ptr <= rhs._ptr;
    };
    bool      operator >= (const iterator<T, true> &rhs) const  
    {
        return _ptr >= rhs._ptr;
    };
    bool      operator == (const iterator<T, true> &rhs) const 
    {
        return _ptr == rhs._ptr;
    };
    bool      operator != (const iterator<T, true> &rhs) const  
    {
        return _ptr != rhs._ptr;
    };
    reference operator *  () const                 
    {
        return *_ptr;
    };
    pointer   operator -> () const                 
    {
        return _ptr;
    };

    friend self operator + (int n, self it) 
    {
        return it += n;
    };
    friend self operator - (int n, self it) 
    {
        return it -= n;
    };

    pointer _ptr;
  };
}

#endif
