#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft 
{
	template <typename Iterator>
	class reverse_iterator 
	{
	 public:
		typedef reverse_iterator	type;
		typedef Iterator			iterator_type;

		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;

		reverse_iterator() : _iter() {};
		reverse_iterator(const iterator_type copy) : _iter(copy) {};

		template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter> &copy) : _iter(copy.base()) {};

		virtual ~reverse_iterator() {};

		template <class Iter> 
		reverse_iterator &operator=(const reverse_iterator<Iter>& other) 
		{
			this->_iter = other.base();
			return *this;
		}

		type base() const
		{
			return _iter;
		}

		type &operator++()
		{
			--_iter;
			return *this;
		};
		type operator++(int)
		{
			type tmp = *this;
			--_iter;
			return tmp;
		};
		type &operator--()
		{
			++_iter;
			return *this;
		};
		type operator--(int) 
		{
			type tmp = *this;
			++_iter;
			return tmp;
		};
		type operator+(difference_type n)const
		{
			reverse_iterator tmp(*this);
			tmp._iter -= n;
			return tmp;
		};
		type operator += (difference_type n) 
		{
			_iter = _iter - n;
			return *this;
		};
		type operator-(difference_type n) const
		{
			reverse_iterator tmp(*this);
			tmp._iter += n;
			return tmp;
		};
		type operator-=(difference_type n)
		{
			_iter = _iter + n;
			return *this;
		};
		reference operator[](difference_type n) const 
		{
			return *(*this + n);
		};

		reference operator*() const
		{
			iterator_type tmp = _iter;
			return *--tmp;
		};
		pointer	 operator->() const
		{
			iterator_type tmp = _iter;
			return &*--tmp;
		};

		template <class Iter>
		difference_type operator-(const reverse_iterator<Iter> &x)
		{
			return x.base().operator-(_iter);;
		};

		friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs) 
		{
			return rhs + n;
		};

		template <class Iter>
		bool operator==(const reverse_iterator<Iter> &rhs) const
		{
			return _iter == rhs.base();
		};

		template <class Iter>
		bool operator!=(const reverse_iterator<Iter> &rhs) const
		{
			return _iter != rhs.base(); 
		};

		template <class Iter>
		bool operator<(const reverse_iterator<Iter> &rhs) const 
		{
			return _iter > rhs.base();
		};

		template <class Iter>
		bool operator>(const reverse_iterator<Iter> &rhs) const
		{
			return _iter < rhs.base();
		};

		template <class Iter>
		bool operator<=(const reverse_iterator<Iter> &rhs) const 
		{
			return _iter >= rhs.base();
		};

		template <class Iter>
		bool operator>=(const reverse_iterator<Iter> &rhs) const
		{
			return _iter <= rhs.base();
		};

		private:
			iterator_type _iter;
		};
}
#endif
