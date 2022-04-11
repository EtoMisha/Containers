#ifndef Vector_HPP
#define Vector_HPP

# include <iostream>
# include <string>
# include <cstddef>

# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
	template < typename T, class Alloc = std::allocator<T> >
	class Vector
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
			explicit Vector (const allocator_type& alloc = allocator_type())
			{
				this->_container = NULL;
				this->_size = 0;
				this->_capacity = 0;
				this->_alloc = alloc;
			}

			explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			{
				this->_container = NULL;
				this->_size = 0;
				this->_capacity = 0;
				this->_alloc = alloc;
				insert(begin(), n, val);
			}

			template <class InputIterator>
			Vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
			{
				this->_container = NULL;
				this->_size = 0;
				this->_capacity = 0;
				this->_alloc = alloc;
				insert(begin(), first, last);
			}

			Vector(const Vector& x)
			{
				this->_container = NULL;
				this->_alloc = x._alloc;
				this->_size = 0;
				this->_capacity = 0;
				assign(x.begin(), x.end());
			}

			virtual ~Vector()
			{
				clear();
				this->_alloc.deallocate(this->_container, this->_capacity);
			}

			Vector& operator= (const Vector& x)
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
				return (std::numeric_limits<difference_type>::max() / sizeof(value_type));
			}

			void resize( size_type count, T value = T() ) {
				if (count < _size) {
					while (_size != count)
						pop_back();
				} else {
					if (_capacity * 2 < count)
						reserve(count);
					while (_size != count)
						push_back(value);
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
					throw std::length_error("Vector reserve length error");
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

			void assign(size_type count, const_reference value ) {
				if (count < 0)
					throw std::out_of_range("Vector length error");
				this->clear();
				this->reserve(count);
				for (size_t i = 0; i < count; ++i, this->_size++)
					this->_container[i] = value;
			}

			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
			assign(InputIterator first, InputIterator last)
			{
				int range_size = last - first;

				if (range_size < 0)
					throw std::length_error("Vector length error");
				this->clear();
				this->reserve(range_size);
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
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

			iterator insert(iterator pos, const_reference value)
			{
				// std::cout << "1\n";
				int index = pos - begin();
				this->insert(pos, 1, value);
				return (iterator(this->_container + index));
			}

			template <class InputIt>
			typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
			insert( iterator pos, InputIt first, InputIt last)
			{
				// std::cout << "2\n";
				size_t range_size = last - first;
				pointer reserved_buffer = this->_alloc.allocate(range_size);
				bool result = true;
				size_t i = 0;
				while (first != last)
				{
					try
					{
						reserved_buffer[i] = *first;
					}
					catch (...)
					{
						result = false;
						break;
					}
					first++;
					i++;
				}
				this->_alloc.deallocate(reserved_buffer, range_size);
				if (!result)
					throw std::exception();

				size_t new_size = _size + range_size;
				int last_index = (pos - begin()) + range_size - 1;
				if (range_size >= this->_capacity)
				{
					reserve(this->_capacity + range_size);
					this->_size = new_size;
				}
				else
				{
					while (this->_size != new_size)
					{
						if (this->_size == this->_capacity)
							reserve(this->_capacity * 2);
						this->_size++;
					}
				}
				for (int i = this->_size - 1; i >= 0; --i)
				{
					if (i == last_index)
					{
						while (range_size > 0)
						{
							this->_container[i] = *--last;
							range_size--;
							i--;
						}
						return;
					}
					this->_container[i] = this->_container[i - range_size];
				}
			}

			void insert (iterator position, int n, const value_type& val)
			{
				// std::cout << "3\n";
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
		
			void swap (Vector& x)
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
	bool operator== (const Vector<T>& lhs, const Vector<T>& rhs)
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
	bool operator!= (const Vector<T>& lhs, const Vector<T>& rhs) 
	{
		return !(lhs == rhs); 
	};

	template <class T>
	bool operator<	(const Vector<T>& lhs, const Vector<T>& rhs) 
	{
		typename Vector<T>::const_iterator iter1 = lhs.begin();
		typename Vector<T>::const_iterator iter2 = rhs.begin();

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
	bool operator<= (const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(rhs < lhs); 
	};

	template <class T>
	bool operator>	(const Vector<T>& lhs, const Vector<T>& rhs) 
	{
		return (rhs < lhs); 
	};

	template <class T>
	bool operator>= (const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(lhs < rhs); 
	};

	template <class T>
	void swap (Vector<T>& x, Vector<T>& y) 
	{
		x.swap(y); 
	};

};

#endif