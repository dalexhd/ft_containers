/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 00:04:49 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/07 14:50:56 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace	ft
{
	struct input_iterator_tag {};

	struct forward_iterator_tag : input_iterator_tag {};

	struct bidirectional_iterator_tag : forward_iterator_tag {};

	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::iterator_category iterator_category;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
	};
	template <class T>
	class iterator_traits<T *>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T *pointer;
			typedef T &reference;
			typedef ft::random_access_iterator_tag iterator_category;
	};
	template <class T>
	class iterator_traits<const T* >
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T *pointer;
			typedef T &reference;
			typedef ft::random_access_iterator_tag iterator_category;
	};

	/**
	 * @brief The iterator is an object that can be used to access the elements of a container.
	 *
	 * @tparam Iterator  The type of the iterator.
	 */
	template <class Iterator>
	class iterator
	{
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type value_type;
			typedef typename iterator_traits<iterator_type>::difference_type difference_type;
			typedef typename iterator_traits<iterator_type>::pointer pointer;
			typedef typename iterator_traits<iterator_type>::reference reference;
		private:
			iterator_type _type;
		public:
			iterator() : _type() {};
			iterator(const iterator::pointer u) : _type(u) {};
			template <class Iterator1>
			iterator(const iterator<Iterator1>& u) : _type(u.base()) {};

			reference operator*() const {
				return (*_type);
			};
			reference operator[] (difference_type n) const {
				return (_type[n]);
			};
			pointer operator->() const {
				return (std::addressof(operator*()));
			};
			iterator& operator++() {
				++_type;
				return (*this);
			};
			iterator  operator++(int) {
				iterator tmp(*this);
				++(*this);
				return (tmp);
			}
			iterator& operator--() {
				--_type;
				return (*this);
			};
			iterator  operator--(int) {
				iterator tmp(*this);
				--(*this);
				return (tmp);
			}
			iterator operator+ (difference_type n) {
				iterator tmp(*this);
				tmp += n;
				return tmp;
			};
			iterator& operator+= (difference_type n) {
				_type += n;
				return (*this);
			};
			iterator operator- (difference_type n) const {
				iterator tmp(*this);
				tmp -= n;
				return tmp;
			};
			difference_type operator- (const iterator& u) const {
				return (_type - u._type);
			};
			iterator& operator-= (difference_type n) {
				*this += -n;
				return (*this);
			};

			template <class Iterator1, class Iterator2>
			friend bool operator==(const iterator<Iterator1>&, const iterator<Iterator2>&);

			template <class Iterator1, class Iterator2>
			friend bool operator<(const iterator<Iterator1>&, const iterator<Iterator2>&);

			template <class Iterator1, class Iterator2>
			friend bool operator!=(const iterator<Iterator1>&, const iterator<Iterator2>&);

			template <class Iterator1, class Iterator2>
			friend bool operator>(const iterator<Iterator1>&, const iterator<Iterator2>&);

			template <class Iterator1, class Iterator2>
			friend bool operator>=(const iterator<Iterator1>&, const iterator<Iterator2>&);

			template <class Iterator1, class Iterator2>
			friend bool operator<=(const iterator<Iterator1>&, const iterator<Iterator2>&);

			template <class Iterator1, class Iterator2>
			friend typename iterator<Iterator1>::difference_type operator-(const iterator<Iterator1>&, const iterator<Iterator2>&);

			template <class Iterator1>
			friend iterator<Iterator1>operator+(typename iterator<Iterator1>::difference_type, iterator<Iterator1>);

			iterator_type base() const
			{
				return (this->_type);
			}
	};
	template <class Iterator1, class Iterator2>
	bool operator==(const iterator<Iterator1>& x, const iterator<Iterator2>& y)
	{
		return x.base() == y.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator<(const iterator<Iterator1>& x, const iterator<Iterator2>& y)
	{
		return x.base() < y.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator!=(const iterator<Iterator1>& x, const iterator<Iterator2>& y)
	{
		return !(x == y);
	};

	template <class Iterator1, class Iterator2>
	bool operator>(const iterator<Iterator1>& x, const iterator<Iterator2>& y)
	{
		return y < x;
	};

	template <class Iterator1, class Iterator2>
	bool operator>=(const iterator<Iterator1>& x, const iterator<Iterator2>& y)
	{
		return !(x < y);
	};

	template <class Iterator1, class Iterator2>
	bool operator<=(const iterator<Iterator1>& x, const iterator<Iterator2>& y)
	{
		return !(y < x);
	};

	template <class Iterator1>
	bool operator!=(const iterator<Iterator1>& x, const iterator<Iterator1>& y)
	{
		return !(x == y);
	};

	template <class Iterator1>
	bool operator>(const iterator<Iterator1>& x, const iterator<Iterator1>& y)
	{
		return y < x;
	};

	template <class Iterator1>
	bool operator>=(const iterator<Iterator1>& x, const iterator<Iterator1>& y)
	{
		return !(x < y);
	};

	template <class Iterator1>
	bool operator<=(const iterator<Iterator1>& x, const iterator<Iterator1>& y)
	{
		return !(y < x);
	};

	template <class Iterator1, class Iterator2>
	typename iterator<Iterator1>::difference_type operator-(const iterator<Iterator1>& x, const iterator<Iterator2>& y)
	{
		return x.base() - y.base();
	};

	template <class Iterator1>
	iterator<Iterator1> operator+(const typename iterator<Iterator1>::difference_type& n, const iterator<Iterator1>& x)
	{
		x += n;
		return	x;
	};

	/**
	 * @brief A class that represents a range of elements.
	 *
	 * @tparam Iterator The type of the iterator used to iterate through the range.
	 */
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;
		private:
			iterator_type _type;
		public:
			reverse_iterator() {};
			explicit reverse_iterator (iterator_type it): _type(it) {};
			template <class Itera>
			reverse_iterator (const reverse_iterator<Itera>& rev_it): _type(rev_it.base()) {};

			reference operator*() const
			{
				iterator_type tmp = this->_type;
				return (*--tmp);
			}

			reference operator[]( difference_type n ) const
			{
				return (this->_type[-n - 1]);
			}

			pointer operator->() const
			{
				return (std::addressof(operator*()));
			}

			reverse_iterator& operator++()
			{
				--this->_type;
				return (*this);
			}

			reverse_iterator& operator--()
			{
				++this->_type;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator temp = *this;
				++(*this);
				return temp;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator temp = *this;
				--(*this);
				return temp;
			}

			reverse_iterator operator+( difference_type n ) const
			{
				return (reverse_iterator(this->_type - n));
			}

			reverse_iterator operator-( difference_type n ) const
			{
				reverse_iterator tmp(*this);
				tmp -= n;
				return tmp;
			}

			reverse_iterator& operator+=( difference_type n )
			{
				this->_type -= n;
				return (*this);
			}

			reverse_iterator& operator-=( difference_type n )
			{
				this->_type += n;
				return (*this);
			}

			friend bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
			{
				return (lhs._type == rhs.base());
			}

			friend bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
			{
				return (lhs._type != rhs.base());
			}

			friend bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
			{
				return (lhs._type > rhs.base());
			}

			friend bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
			{
				return (lhs._type >= rhs.base());
			}

			friend bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
			{
				return (lhs._type < rhs.base());
			}

			friend bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
			{
				return (lhs._type <= rhs.base());
			}

			iterator_type base() const
			{
				return (this->_type);
			}
	};

	template< class Iterator >
	reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it )
	{
		return (it + n);
	}

	template< class Iterator >
	reverse_iterator<Iterator> operator-( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it )
	{
		return (it.base() - n.base());
	}
}

#endif
