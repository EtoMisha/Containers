#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
    template <typename T>
    class Iterator
    {
        public:

            typedef T                   value_type;
            typedef value_type *        pointer;
            typedef value_type const *  const_pointer;
            typedef value_type &        reference;
            typedef value_type const &  const_reference;

        protected:

            pointer _p;

        public:

            Iterator(void): _p(nullptr) {};
            Iterator(pointer point): _p(point) {};
            Iterator(Iterator const & other): _p(other._p) {};
            virtual ~Iterator() {};

            Iterator& operator++ ()
            {
                ++this->_p;
                return (*this);
            };

            Iterator operator++ (int)
            {
                Iterator   tmp(*this);

                ++this->_p;
                return (tmp);
            };

            Iterator& operator-- ()
            {
                --this->_p;
                return (*this);
            };

            Iterator operator-- (int)
            {
                Iterator   tmp(*this);

                --this->_p;
                return (tmp);
            };

            reference operator* ()
            {
                return (*this->_p);
            };

            const_reference operator* () const
            {
                return (*this->_p);
            };

            pointer operator-> ()
            {
                return (*&this->_p);
            };

            const_pointer operator-> () const
            {
                return (*&this->_p);
            };

            reference operator[](int val)
            {
                return (*(this->_p + val));
            }

            const_reference operator[](int val) const
            {
                return (*(this->_p + val));
            }

            Iterator& operator= (const Iterator & other)
            {
                this->_p = other._p;
                return (*this);
            };

            
            Iterator   operator+ (int val)
            {
                Iterator   tmp(*this);

                tmp._p = tmp._p + val;
                return (tmp);
            };

            Iterator   operator- (int val)
            {
                Iterator   tmp(*this);

                tmp._p = tmp._p - val;
                return (tmp);
            };

            Iterator&   operator+= (int val)
            {
                this->_p = this->_p + val;
                return (*this);
            };

            Iterator&   operator-= (int val)
            {
                this->_p = this->_p - val;
                return (*this);
            };

            bool operator== (const Iterator & other) const
            {
                return (this->_p == other._p);
            };

            bool operator!= (const Iterator & other) const
            {
                return (this->_p != other._p);
            };

            bool operator>= (const Iterator & other) const
            {
                return (this->_p >= other._p);
            };

            bool operator<= (const Iterator & other) const
            {
                return (this->_p <= other._p);
            };

            bool operator< (const Iterator & other) const
            {
                return (this->_p < other._p);
            };

            bool operator> (const Iterator & other) const
            {
                return (this->_p > other._p);
            };

    };

}

#endif