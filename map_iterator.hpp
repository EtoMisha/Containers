#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "pair.hpp"

namespace ft
{
	template <typename T>
	struct Tree {
		Tree *left;
		Tree *right;
		Tree *parent;
		T pair;
	};
	
	template <class Key, class T, bool isconst = false>
	struct map_iterator 
	{
		typedef map_iterator<Key, T, isconst>	 self;

		typedef std::ptrdiff_t									difference_type;
		typedef std::bidirectional_iterator_tag					iterator_category;
		typedef ft::pair<const Key, T>							value_type;
		typedef typename choose_type<isconst, 
			const value_type&, value_type&>::type				reference;
		typedef typename choose_type<isconst, 
			const value_type*, value_type*>::type				pointer;
		typedef typename choose_type<isconst, 
			const Tree<value_type>*, Tree<value_type>*>::type	nodeptr;

		map_iterator() : _ptr(NULL) {};
		map_iterator(nodeptr ptr) : _ptr(ptr) {};
		map_iterator(const map_iterator<Key, T, false> &copy) : _ptr(copy._ptr) {};
		map_iterator(const map_iterator<Key, T, true> &copy) : _ptr(copy._ptr) {};

		virtual ~map_iterator() {};

		self &operator= (const self &rhs)
		{
			_ptr = rhs._ptr;
			return *this;
		};

		self &operator++ ()
		{
			if ((_ptr->right && _ptr->right->parent != _ptr)
				|| (_ptr->left && _ptr->left->parent != _ptr))
				_ptr = _ptr->left;
			else if (_ptr->right)
			{
				_ptr = _ptr->right;
				while (_ptr->left)
					_ptr = _ptr->left;
			}
			else
			{
				nodeptr tmp = _ptr->parent;
				while (_ptr == tmp->right)
				{
					_ptr = tmp;
					tmp = tmp->parent;
				}
				if (_ptr->right != tmp)
					_ptr = tmp;
			}
			return *this;
		};

		self operator++ (int)
		{
			self tmp = *this;
			++(*this);
			return tmp;
		};

		self &operator -- ()
		{
			if ((_ptr->right && _ptr->right->parent != _ptr)
				|| (_ptr->left && _ptr->left->parent != _ptr))
				_ptr = _ptr->right;
			else if (_ptr->left)
			{
				_ptr = _ptr->left;
				while (_ptr->right)
					_ptr = _ptr->right;
			}
			else 
			{
				nodeptr tmp = _ptr->parent;
				while (_ptr == tmp->left)
				{
					_ptr = tmp;
					tmp = tmp->parent;
				}
				_ptr = tmp;
			}
			return *this;
		};

		self operator-- (int)
		{
			self tmp = *this;
			--(*this);
			return tmp;
		};
		bool operator== (const self &rhs) const
		{
			return _ptr == rhs._ptr;
		};
		bool operator!= (const self &rhs) const
		{
			return _ptr != rhs._ptr;
		};
		reference operator* () const
		{
			return _ptr->pair;
		};
		pointer	 operator-> () const
		{
			return &_ptr->pair;
		};

		nodeptr _ptr;
	};
}

#endif