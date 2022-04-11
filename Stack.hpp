#ifndef Stack_HPP
# define Stack_HPP

# include "Vector.hpp"

namespace ft 
{
	template <class T, class Container = ft::Vector<T> >
	class Stack 
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef std::size_t	size_type;

			explicit Stack(const container_type& cont = container_type())
			{
				c = cont;
			};

			Stack(const Stack& other)
			{
				c = other.c;
			}

			Stack& operator = (const Stack& other)
			{
				c = other.c;
				return *this;
			};

			~Stack() {};

			bool empty() const
			{
				return c.empty();
			};
			size_type size() const
			{
				return c.size();
			};
			value_type&	top()
			{
				return c.back();
			};
			const value_type& top() const
			{
				return c.back();
			};
			void push(const value_type& val)
			{
				c.push_back(val);
			};
			void pop()
			{
				c.pop_back();
			};

			template <class U, class Cont>
			friend bool operator== (const Stack<U,Cont>& lhs, const Stack<U,Cont>& rhs)
			{
				return lhs.c == rhs.c;
			}
			template <class U, class Cont>
			friend bool operator< (const Stack<U,Cont>& lhs, const Stack<U,Cont>& rhs)
			{
				return lhs.c < rhs.c;
			};

			template <class U, class Cont>
			friend bool operator!= (const Stack<U,Cont>& lhs, const Stack<U,Cont>& rhs)
			{
				return !(lhs == rhs);
			};

			template <class U, class Cont>
			friend bool operator<= (const Stack<U,Cont>& lhs, const Stack<U,Cont>& rhs)
			{
				return !(rhs < lhs);
			};

			template <class U, class Cont>
			friend bool operator>	(const Stack<U,Cont>& lhs, const Stack<U,Cont>& rhs)
			{
				return rhs < lhs;
			};

			template <class U, class Cont>
			friend bool operator>= (const Stack<U,Cont>& lhs, const Stack<U,Cont>& rhs)
			{
				return !(lhs < rhs);
			};
			
	protected:
		container_type c;
	};

};

#endif