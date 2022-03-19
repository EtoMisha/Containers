#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>

namespace ft {
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits <T*> {
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits <const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};


//-------------------------- ???

	template <bool flag, class const_type, class normal_type>
	struct choose_type;

	template <class const_type, class normal_type>
	struct choose_type<true, const_type, normal_type> 
	{
		typedef const_type type;
	};

	template <class const_type, class normal_type>
	struct choose_type<false, const_type, normal_type>
	{
		typedef normal_type type;
	};
};

#endif