#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <iostream>
# include <string>
# include <cstddef>

# include "iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template < typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T 										value_type;
			typedef T& 										reference;
			typedef const T& 								const_reference;
			typedef T* 										pointer;
			typedef const T*								const_pointer;
			typedef ft::iterator<T>							iterator;
			typedef ft::iterator<T, true>					const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef std::ptrdiff_t							difference_type;
			typedef std::size_t								size_type;
			typedef Alloc									allocator_type;

		/*		Constructors + destructor	*/
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				this->_container = NULL;
				this->_size = 0;
				this->_capacity = 0;
				this->_alloc = alloc;
			}

			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			{
				this->_container = NULL;
				this->_size = 0;
				this->_capacity = 0;
				this->_alloc = alloc;
				insert(begin(), n, val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
			{
				this->_container = NULL;
				this->_size = 0;
				this->_capacity = 0;
				this->_alloc = alloc;
				insert(begin(), first, last);
			}

			vector(const vector& x)
			{
				this->_container = NULL;
				this->_alloc = x._alloc;
				this->_size = 0;
				this->_capacity = 0;
				assign(x.begin(), x.end());
			}

			virtual ~vector()
			{
				clear();
				this->_alloc.deallocate(this->_container, this->_capacity);
			}

			vector& operator= (const vector& x)
			{
				if (&x == this)
					return *this;
				assign(x.begin(), x.end());
				return *this;
			}

		/*		Iterators		*/

			iterator begin(void) const
			{
				return(iterator(this->_container));
			}
			iterator end(void) const
			{
				return(iterator(&(this->_container[this->_size])));
			}
			reverse_iterator rbegin(void)
			{
				return (reverse_iterator(this->end()));
			}
			reverse_iterator rend(void)
			{
				return (reverse_iterator(this->begin()));
			}
			
		/*		Capacity		*/

			size_type size(void) const 
			{
				return(this->_size);
			}
			size_type max_size(void) const 
			{
				return (std::numeric_limits<difference_type>::max() / sizeof(value_type) * 2);
			}
			void resize(size_type n, value_type val = value_type()) 
			{
				if (this->_capacity < n)
				{
					if (this->_capacity == 0)
						reserve(n);
					else
					{
						if (n < this->_size * 2)
							reserve(this->_size * 2);
						else 
							reserve(n);
					}
				}
				while (this->_size < n)
				{
					push_back(val);
				}
				while (this->_size > n)
				{
					pop_back();
				}
			}
			size_type capacity() const 
			{
				return(this->_capacity);
			}
			bool empty() const
			{
				return(this->_size == 0);
			}
			void reserve(size_type n) 
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n < this->_capacity)
					return;
				pointer new_container = _alloc.allocate(n);
				size_type i = 0;
				while (i < this->_size)
				{
					this->_alloc.construct(&new_container[i], this->_container[i]);
					this->_alloc.destroy(&(this->_container[i]));
					i++;
				}
				this->_alloc.deallocate(this->_container, this->_capacity);
				this->_capacity = n;
				this->_container = new_container;
			}

		/*		Element access	*/

			reference operator[] (size_type n) 
			{
				return (this->_container[n]);
			}
			const_reference operator[] (size_type n) const
			{
				return (this->_container[n]); 
			}
			reference at (size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("Vector index out of range");
				return (this->_container[n]);
			}
			const_reference at (size_type n) const 
			{
				if (n < this->_size)
					throw std::out_of_range("Vector index out of range");
				return (this->_container[n]);
			}
			reference front() 
			{
				return (this->_container[0]);
			}
			const_reference front() const 
			{
				return (this->_container[0]);
			}
			reference back() 
			{
				return (this->_container[this->_size - 1]);
			}
			const_reference back() const 
			{
				return (this->_container[this->_size - 1]);
			}

		/*		Modifiers		*/

			template <class InputIterator>		
			void assign (InputIterator first, InputIterator last)
			{
				clear();
				InputIterator temp = first;
				difference_type n = 0;
				while (temp != last) 
				{
					n++;
					temp++;
				}
				reserve(n);
				insert(begin(), first, last);
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				reserve(n);
				insert(begin(), n, val);
			}

			void push_back (const value_type& val)
			{
				if (this->_size + 1 > this->_capacity) 
				{
					if (this->_capacity == 0)
						reserve(1);
					else
						reserve(this->_capacity * 2);
				}
				this->_alloc.construct(&this->_container[this->_size], val);
				this->_size++;
			}

			void pop_back(void)
			{
				if (this->_size)
				{
					this->_alloc.destroy(&this->_container[this->_size - 1]);
					this->_size--;
				}
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type index = position - begin();
				if (this->_size + 1 > this->_capacity)
				{
					if (this->_capacity == 0)
						reserve(1);
					else
						reserve(this->_capacity * 2);
				}
				this->_size++;
				if (index < this->_size) 
				{
					size_type i = this->_size - 1;
					while (i > index)
					{
						this->_alloc.construct(&this->_container[i], this->_container[i - 1]);
						this->_alloc.destroy(&this->_container[i - 1]);
						i--;
					}
				}
				this->_alloc.construct(&this->_container[index], val);
				return iterator(&this->_container[index]);
			}

			void insert (iterator position, int n, const value_type& val)
			{
				size_type index = position - begin();

				if (this->_size + n > this->_capacity) 
				{
					if (this->_capacity == 0)
						reserve(n);
					else
					{
						if (this->_size * 2 >= this->_size + n)
							reserve(this->_size * 2);
						else
							reserve(this->_size + n);
					}
				}
				size_type i = n + this->_size - 1;
				while ( i > index + n - 1)
				{
					this->_alloc.construct(&this->_container[i], this->_container[i - n]);
					this->_alloc.destroy(&this->_container[i - n]);
					i--;
				}
				i = index;
				while (i < index + n)
				{
					this->_alloc.construct(&this->_container[i], val);
					this->_size++;
					i++;
				}
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				size_type offset = position - begin();
				InputIterator tmp = first;
				difference_type n = 0;
				while (tmp != last)
				{
					n++;
					tmp++;
				}
				if (this->_size + n > this->_capacity) 
				{
					if (this->_capacity == 0)
						reserve(n);
					else 
					{
						if (this->_size * 2 >= this->_size + n)
							reserve(this->_size * 2);
						else
							reserve(this->_size + n);
					}
				}
				size_type i = n + this->_size - 1;
				while (i > offset + n - 1)
				{
					this->_alloc.construct(&this->_container[i], this->_container[i - n]);
					this->_alloc.destroy(&this->_container[i - n]);
					i--;
				}
				i = offset;
				while (i < offset + n)
				{
					this->_alloc.construct(&this->_container[i], *first);
					first++;
					this->_size++;
					i++;
				}
			}			

			iterator erase (iterator position)
			{
				size_type index = position - begin();
				this->_alloc.destroy(&this->_container[index]);
				this->_size--;
				if (index < this->_size)
				{
					size_type i = index;
					while (i < this->_size)
					{
						this->_alloc.construct(&this->_container[i], this->_container[i + 1]);
						this->_alloc.destroy(&this->_container[i + 1]);
						i++;
					}
				}
				return (iterator(&this->_container[index]));
			}

			iterator erase (iterator first, iterator last)
			{
				size_type start = first - begin();
				difference_type offset = last - first;
	
				if (first == last)
					return iterator(first);
				iterator iter = first;
				while (iter < last)
				{
					this->_alloc.destroy(&(*iter));
					iter++;
				}
				this->_size -= offset;
				if (start < this->_size) 
				{
					size_type i = start;
					while (i < this->_size)
					{
						this->_alloc.construct(&this->_container[i], this->_container[i + offset]);
						this->_alloc.destroy(&this->_container[i + offset]);
						i++;
					}
				}
				return iterator(&this->_container[start]);
			}

			void swap (vector& x)
			{
				pointer tmp = x._container;
				size_type tmp_size = x._size;
				size_type tmp_capacity = x._capacity;
	
				x._container = this->_container;
				x._size = this->_size;
				x._capacity = this->_capacity;

				this->_container = tmp;
				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
			}

			void clear(void)
			{
				erase(begin(), end());
			}

		private:
			pointer			_container;
			size_type		_capacity;
			size_type		_size;
			allocator_type	_alloc;
	};

	/*		Non members		*/

	template <class T>
	bool operator== (const vector<T>& lhs, const vector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		size_t i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] != rhs[i])
				return false;
			i++;
		}
		return true;
	};

	template <class T>
	bool operator!= (const vector<T>& lhs, const vector<T>& rhs) 
	{
		return !(lhs == rhs); 
	};

	template <class T>
	bool operator<	(const vector<T>& lhs, const vector<T>& rhs) 
	{
		typename vector<T>::const_iterator iter1 = lhs.begin();
		typename vector<T>::const_iterator iter2 = rhs.begin();

		while (iter1 != lhs.end() && iter2 != rhs.end()) {
			if (*iter1 < *iter2)
				return true;
			else if (*iter1 > *iter2)
				return false;
			iter1++;
			iter2++;
		}
		return (iter2 != rhs.end());
	};

	template <class T>
	bool operator<= (const vector<T>& lhs, const vector<T>& rhs)
	{
		return !(rhs < lhs); 
	};

	template <class T>
	bool operator>	(const vector<T>& lhs, const vector<T>& rhs) 
	{
		return (rhs < lhs); 
	};

	template <class T>
	bool operator>= (const vector<T>& lhs, const vector<T>& rhs)
	{
		return !(lhs < rhs); 
	};

	template <class T>
	void swap (vector<T>& x, vector<T>& y) 
	{
		x.swap(y); 
	};

};

#endif