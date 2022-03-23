#ifndef ALLOCATOR_HPP
# define ALLOCATOR_HPP

namespace ft
{
  template <class T>
  class allocator 
  {
   public:
    typedef T        value_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    template <class T>
    struct rebind { typedef ft::allocator<T> other; };

    pointer address (reference value) const { return &value; }
    const_pointer address (const_reference value) const { return &value; }

    allocator() throw() {}
    allocator(const allocator&) throw() {}

    template <class T>
    allocator (const allocator<T>&) throw() {}

    ~allocator() throw() {}

    size_type max_size () const throw()
    {
      return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    pointer allocate (size_type num, const void* = 0)
    {
      return reinterpret_cast<pointer>(::operator new(num * sizeof (T)));
    }

    void construct (pointer p, const T& value) 
    {
      new(p) T(value);
    }

    void destroy (pointer p) 
    {
      p->~T();
    }

    void deallocate (pointer p, size_type) 
    {
      ::operator delete(p);
    }
    bool operator== (const allocator&) throw() 
    {
      return true;
    }
    bool operator!= (const allocator &a) throw() 
    {
      return !operator==(a);
    }
  };
}
