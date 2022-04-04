#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <limits>
# include <cstddef>

# include "map_iterator.hpp"
# include "reverse_iterator.hpp"
# include "pair.hpp"
# include "compare.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
	template <	class Key,
				class T,
				class Compare = less<Key>,
				class Alloc = std::allocator<pair<const Key,T> > 
			>
	class map
	{
	 public:

		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef ft::Comp<Compare, value_type>			value_compare;

		typedef Alloc										allocator_type;;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef ft::map_iterator<key_type, mapped_type>			iterator;
		typedef ft::map_iterator<key_type, mapped_type, true>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t		size_type;

	//	Constructors

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
		{
			this->_alloc = alloc;
			this->_compare = comp;
			this->_size = 0;

			this->_container = alloc_node.allocate(1);
			this->_container->left = this->_container;
			this->_container->right = this->_container;
			this->_container->parent = NULL;

			this->_alloc.construct(&this->_container->pair, value_type());
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
		{
			this->_alloc = alloc;
			this->_compare = comp;
			this->_size = 0;

			this->_container = alloc_node.allocate(1);
			this->_container->left = this->_container;
			this->_container->right = this->_container;
			this->_container->parent = NULL;
			this->_alloc.construct(&this->_container->pair, value_type());

			insert(first, last);
		};

		map(const map& x)
		{
			this->_compare = x._compare;
			this->_size = 0;
			this->_alloc = x._alloc;

			this->_container = alloc_node.allocate(1);
			this->_container->left = this->_container;
			this->_container->right = this->_container;
			this->_container->parent = NULL;
			this->_alloc.construct(&this->_container->pair, value_type());

			insert(x.begin(), x.end());
		};

		~map() 
		{
			clear();
			this->_alloc.destroy(&this->_container->pair);
			alloc_node.deallocate(this->_container, 1);
		};

		map& operator= (const map& x) 
		{
			clear();
			insert(x.begin(), x.end());
			return *this;
		};

	//	Iterators

		iterator begin() const
		{
			return iterator(get_left());
		};
		iterator end() const
		{
			return iterator(this->_container);
		};

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		};
		reverse_iterator rend() 
		{
			return reverse_iterator(begin());
		};

	//	Capacity

		bool empty() const
		{
			return this->_size == 0;
		};
		size_type size() const
		{
			return this->_size;
		};
		size_type max_size() const	
		{
			return alloc_node.max_size();
		};

	//	Element access

		mapped_type& operator[] (const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		};
	
	//	Modifiers

		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			tree *exist = key_exists_recurse(get_root(), val.first);

			if (exist)
				return iterator(exist);
			this->_size++;
			return iterator(insert_node(this->_container, this->_compare, val));
		};

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			while (first != last) {
				insert(*first);
				first++;
			}
		};

		void erase(iterator position)
		{
			tree *current = position._ptr;
			tree *tmp = NULL;

			if (current->left)
			{
				tmp = current->left;
				while (tmp->right)
					tmp = tmp->right;
				if (tmp->parent->right == tmp) 
				{
					if (tmp->left) 
					{
						tmp->parent->right = tmp->left;
						tmp->left->parent = tmp->parent;
					}
					else
						tmp->parent->right = NULL;
				}
				tmp->right = current->right;
				if (current->right)
					current->right->parent = tmp;
				if (current->left != tmp)
					tmp->left = current->left;
				if (current->left)
					current->left->parent = tmp;
				tmp->parent = current->parent;
			}
			else if (current->right)
			{
				tmp = current->right;
				tmp->parent = current->parent;
			}
			if (current->parent->left == current)
				current->parent->left = tmp;
			else
				current->parent->right = tmp;
			if (current == get_root())
				this->_container->parent = tmp;
			this->_alloc.destroy(&current->pair);
			alloc_node.deallocate(current, 1);
			this->_size--;
			set_leftright();
		};

		size_type erase(const key_type& k)
		{
			iterator it = begin();
			iterator tmp;
			size_type count = 0;

			while (it != end())
			{
				if (!this->_compare(it->first, k) && !this->_compare(k, it->first))
				{
					erase(it);
					count++;
					return count;
				}
				else
					it++;
			}
			return count;
		};

		void erase(iterator first, iterator last)
		{
			iterator tmp;

			while (first != last)
			{
				tmp = first++;
				erase(tmp);
			}
		};

		void swap (map& x)
		{
			tree *tmp;
			size_type size_tmp;

			size_tmp = this->_size;
			this->_size = x._size;
			x._size = size_tmp;

			tmp = this->_container;
			this->_container = x._container;
			x._container = tmp;
		};

		void clear()
		{
			erase(begin(), end());
		};

	//	Observers

		key_compare key_comp() const 
		{
			return key_compare();
		};
		value_compare value_comp() const
		{
			return value_compare(key_compare());
		};

	//	Operations

		iterator find (const key_type& k) 
		{
			tree *found = key_exists_recurse(get_root(), k);

			if (found)
				return iterator(found);
			return (end());
		};

		const_iterator find (const key_type& k) const
		{
			tree *found = key_exists_recurse(get_root(), k);

			if (found)
				return const_iterator(found);
			return (end());
		};

		size_type count (const key_type& k) const
		{
			return key_count_recurse(get_root(), k);
		};

		iterator lower_bound (const key_type& k)
		{
			iterator it = begin();

			while (it != end()) {
				if (!this->_compare(it->first, k))
					return it;
				it++;
			}
			return it;
		};
		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator it = begin();

			while (it != end()) {
				if (!this->_compare(it->first, k))
					return it;
				it++;
			}
			return it;
		};

		iterator upper_bound (const key_type& k)
		{
			iterator it = begin();

			while (it != end()) {
				if (this->_compare(k, it->first))
					return it;
				it++;
			}
			return it;
		};
		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator it = begin();

			while (it != end()) {
				if (this->_compare(k, it->first))
					return it;
				it++;
			}
			return it;
		};

		ft::pair<iterator, iterator> equal_range (const key_type& k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		};

		ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		};


		pair<iterator, bool> insert (const value_type& val)
		{
			tree *exist = key_exists_recurse(get_root(), val.first);

			if (exist)
				return ft::make_pair(iterator(exist), false);
			this->_size++;
			return ft::make_pair(iterator(insert_node(this->_container, this->_compare, val)), true);
		};

	private:
		typedef Tree<value_type>	tree;

		tree *key_exists_recurse(tree *root, key_type key) const
		{
			tree *found = get_root();

			if (!root)
				return NULL;
			found = key_exists_recurse(root->left, key);
			if (!this->_compare(root->pair.first, key) && !this->_compare(key, root->pair.first))
				found = root;
			if (!found)
				found = key_exists_recurse(root->right, key);
			return found;
		}

		size_type key_count_recurse(tree *root, key_type key) const
		{
			if (!root)
				return 0;
			if (!this->_compare(root->pair.first, key) && !this->_compare(key, root->pair.first))
				return 1;
			return key_count_recurse(root->left, key) + key_count_recurse(root->right, key);
		}

		void	set_leftright()
		{
			tree *tmp = get_root();

			if (!tmp)
			{
				this->_container->left = this->_container;
				this->_container->right = this->_container;
				return ;
			}
			while (tmp && tmp->left)
				tmp = tmp->left;
			this->_container->left = tmp;

			tmp = get_root();
			while (tmp && tmp->right)
				tmp = tmp->right;
			this->_container->right = tmp;
		}

		tree	*insert_node(tree *node, key_compare comp, value_type pair)
		{
			if (node == this->_container)
			{
				if (!node->parent)
				{
					node->parent = alloc_node.allocate(1);
					node->parent->left = NULL;
					node->parent->right = NULL;
					node->parent->parent = node;
					this->_alloc.construct(&node->parent->pair, pair);

					set_leftright();
					return node->parent;
				}
				else
					node = node->parent;
			}
			if (comp(pair.first, node->pair.first))
			{
				if (!node->left)
				{
					node->left = alloc_node.allocate(1);
					node->left->left = NULL;
					node->left->right = NULL;
					node->left->parent = node;
					this->_alloc.construct(&node->left->pair, pair);

					set_leftright();
					return node->left;
				}
				else
					node = insert_node(node->left, comp, pair);
			}
			else
			{
				if (!node->right) {
					node->right = alloc_node.allocate(1);
					node->right->left = NULL;
					node->right->right = NULL;
					node->right->parent = node;
					this->_alloc.construct(&node->right->pair, pair);

					set_leftright();
					return node->right;
				}
				else
					node = insert_node(node->right, comp, pair);
			}
			return node;
		}

		tree *get_root() const { return this->_container->parent; };
		tree *get_left() const { return this->_container->left; };
		tree *get_right() const { return this->_container->right; };

		typename allocator_type::template rebind<tree>::other alloc_node;

		tree*			_container;
		allocator_type	_alloc;
		key_compare		_compare;
		size_type		_size;
	};

	//	Operators

	template <class Key, class T>
	bool operator== (const map<Key, T>& lhs, const map<Key, T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename map<Key, T>::const_iterator iter1 = lhs.begin();
		typename map<Key, T>::const_iterator iter2 = rhs.begin();

		while (iter1 != lhs.end() && iter2 != rhs.end())
		{
			if (*iter1 != *iter2)
				return false;
			iter1++;
			iter2++;
		}
		return (iter1 == lhs.end()) && (iter2 == rhs.end());
	};

	template <class Key, class T>
	bool operator!= (const map<Key, T>& lhs, const map<Key, T>& rhs) 
	{
		return !(lhs == rhs);
	};

	template <class Key, class T>
	bool operator<	(const map<Key, T>& lhs, const map<Key, T>& rhs)
	{
		typename map<Key, T>::const_iterator iter1 = lhs.begin();
		typename map<Key, T>::const_iterator iter2 = rhs.begin();

		while (iter1 != lhs.end() && iter2 != rhs.end())
		{
			if (*iter1 < *iter2)
				return true;
			if (*iter2 < *iter1)
				return false;
			iter1++;
			iter2++;
		}
		return (iter1 == lhs.end()) && (iter2 != rhs.end());
	};

	template <class Key, class T>
	bool operator<= (const map<Key, T>& lhs, const map<Key, T>& rhs)
	{
		return !(rhs < lhs);
	};

	template <class Key, class T>
	bool operator>	(const map<Key, T>& lhs, const map<Key, T>& rhs)
	{
		return rhs < lhs;
	};

	template <class Key, class T>
	bool operator>= (const map<Key, T>& lhs, const map<Key, T>& rhs)
	{
		return !(lhs < rhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	};
};

#endif
