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

			this->_container = alloc_node_.allocate(1);
			this->_container->left_ = this->_container;
			this->_container->right_ = this->_container;
			this->_container->parent_ = NULL;

			this->_alloc.construct(&this->_container->pair_, value_type());
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
		{
			this->_alloc = alloc;
			this->_compare = comp;
			this->_size = 0;

			this->_container = alloc_node_.allocate(1);
			this->_container->left_ = this->_container;
			this->_container->right_ = this->_container;
			this->_container->parent_ = NULL;
			this->_alloc.construct(&this->_container->pair_, value_type());

			insert(first, last);
		};

		map(const map& x)
		{
			this->_compare = x._comp;
			this->_size = 0;
			this->_alloc = x._alloc;

			this->_container = alloc_node_.allocate(1);
			this->_container->left_ = this->_container;
			this->_container->right_ = this->_container;
			this->_container->parent_ = NULL;
			this->_alloc.construct(&this->_container->pair_, value_type());

			insert(x.begin(), x.end());
		};

		~map() 
		{
			clear();
			this->_alloc.destroy(&this->_container->pair_);
			alloc_node_.deallocate(this->_container, 1);
		};

		map& operator= (const map& x) 
		{
			clear();
			insert(x.begin(), x.end());
			return *this;
		};

	//	Iterators

		iterator begin() 
		{
			return iterator(get_left());
		};
		iterator end() 
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
			return alloc_node_.max_size();
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
			tree *current = position.ptr_;
			tree *tmp = NULL;

			if (current->left_)
			{
				tmp = current->left_;
				while (tmp->right_)
					tmp = tmp->right_;
				if (tmp->parent_->right_ == tmp) 
				{
					if (tmp->left_) 
					{
						tmp->parent_->right_ = tmp->left_;
						tmp->left_->parent_ = tmp->parent_;
					}
					else
						tmp->parent_->right_ = NULL;
				}
				tmp->right_ = current->right_;
				if (current->right_)
					current->right_->parent_ = tmp;
				if (current->left_ != tmp)
					tmp->left_ = current->left_;
				if (current->left_)
					current->left_->parent_ = tmp;
				tmp->parent_ = current->parent_;
			}
			else if (current->right_) {
				tmp = current->right_;
				tmp->parent_ = current->parent_;
			}
			if (current->parent_->left_ == current)
				current->parent_->left_ = tmp;
			else
				current->parent_->right_ = tmp;
			if (current == get_root())
				this->_container->parent_ = tmp;
			this->_alloc.destroy(&current->pair_);
			alloc_node_.deallocate(current, 1);
			this->_size--;
			set_left_right();
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
			this->_container = x.container;
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
			found = key_exists_recurse(root->left_, key);
			if (!this->_compare(root->pair_.first, key) && !this->_compare(key, root->pair_.first))
				found = root;
			if (!found)
				found = key_exists_recurse(root->right_, key);
			return found;
		}

		size_type key_count_recurse(tree *root, key_type key) const
		{
			if (!root)
				return 0;
			if (!this->_compare(root->pair_.first, key) && !this->_compare(key, root->pair_.first))
				return 1;
			return key_count_recurse(root->left_, key) + key_count_recurse(root->right_, key);
		}

		void	set_left_right()
		{
			tree *tmp = get_root();

			if (!tmp)
			{
				this->_container->left_ = this->_container;
				this->_container->right_ = this->_container;
				return ;
			}
			while (tmp && tmp->left_)
				tmp = tmp->left_;
			this->_container->left_ = tmp;

			tmp = get_root();
			while (tmp && tmp->right_)
				tmp = tmp->right_;
			this->_container->right_ = tmp;
		}

		tree	*insert_node(tree *node, key_compare comp, value_type pair)
		{
			if (node == this->_container)
			{
				if (!node->parent_)
				{
					node->parent_ = alloc_node_.allocate(1);
					node->parent_->left_ = NULL;
					node->parent_->right_ = NULL;
					node->parent_->parent_ = node;
					this->_alloc.construct(&node->parent_->pair_, pair);

					set_left_right();
					return node->parent_;
				}
				else
					node = node->parent_;
			}
			if (comp(pair.first, node->pair_.first))
			{
				if (!node->left_)
				{
					node->left_ = alloc_node_.allocate(1);
					node->left_->left_ = NULL;
					node->left_->right_ = NULL;
					node->left_->parent_ = node;
					this->_alloc.construct(&node->left_->pair_, pair);

					set_left_right();
					return node->left_;
				}
				else
					node = insert_node(node->left_, comp, pair);
			}
			else
			{
				if (!node->right_) {
					node->right_ = alloc_node_.allocate(1);
					node->right_->left_ = NULL;
					node->right_->right_ = NULL;
					node->right_->parent_ = node;
					this->_alloc.construct(&node->right_->pair_, pair);

					set_left_right();
					return node->right_;
				}
				else
					node = insert_node(node->right_, comp, pair);
			}
			return node;
		}

		tree *get_root() const { return this->_container->parent_; };
		tree *get_left() const { return this->_container->left_; };
		tree *get_right() const { return this->_container->right_; };

		typename allocator_type::template rebind<tree>::other alloc_node_;

		tree						*_container;
		allocator_type	_alloc;
		key_compare		 _compare;
		size_type			 _size;
	};

	//	Operators

	template <class Key, class T>
	bool operator== (const map<Key, T>& lhs, const map<Key, T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename map<Key, T>::const_iterator it1 = lhs.begin();
		typename map<Key, T>::const_iterator it2 = rhs.begin();

		while (it1 != lhs.end() && it2 != rhs.end())
		{
			if (*it1 != *it2)
				return false;
			it1++;
			it2++;
		}
		return (it1 == lhs.end()) && (it2 == rhs.end());
	};

	template <class Key, class T>
	bool operator!= (const map<Key, T>& lhs, const map<Key, T>& rhs) 
	{
		return !(lhs == rhs);
	};

	template <class Key, class T>
	bool operator<	(const map<Key, T>& lhs, const map<Key, T>& rhs)
	{
		typename map<Key, T>::const_iterator it1 = lhs.begin();
		typename map<Key, T>::const_iterator it2 = rhs.begin();

		while (it1 != lhs.end() && it2 != rhs.end())
		{
			if (*it1 < *it2)
				return true;
			if (*it2 < *it1)
				return false;
			it1++;
			it2++;
		}
		return (it1 == lhs.end()) && (it2 != rhs.end());
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
