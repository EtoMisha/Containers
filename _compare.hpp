#ifndef COMPARE_HPP
# define COMPARE_HPP

namespace ft 
{
  template <class T>
  struct less 
  {
    typedef bool  result_type;
    typedef T     first_argument_type;
    typedef T     second_argument_type;

    bool operator() (const T &lhs, const T &rhs) const 
    {
      return lhs < rhs;
    };
  };

  template <class Compare, class T>
  class Comp 
  {
   public:
    Comp(Compare c) : _comp(c) {};

    bool operator()(const T& x, const T& y) const
    {
      return comp_(x.first, y.first);
    };

    Compare _comp;
  };
  
  #endif
