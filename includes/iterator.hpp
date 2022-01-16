/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 00:04:49 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/16 19:08:34 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>

namespace	ft
{
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
			typedef std::random_access_iterator_tag iterator_category;
	};
	template <class T>
	class iterator_traits<const T* >
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T *pointer;
			typedef T &reference;
			typedef std::random_access_iterator_tag iterator_category;
	};
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
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it): _type(rev_it.base()) {};

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
				return (reverse_iterator(this->_type + n));
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

			template <class Iter>
			friend bool operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
			{
				return (lhs._type == rhs.base());
			}

			template <class Iter>
			friend bool operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
			{
				return (lhs._type != rhs.base());
			}

			template <class Iter>
			friend bool operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
			{
				return (lhs._type < rhs.base());
			}

			template <class Iter>
			friend bool operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
			{
				return (lhs._type <= rhs.base());
			}

			template <class Iter>
			friend bool operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
			{
				return (lhs._type > rhs.base());
			}

			template <class Iter>
			friend bool operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
			{
				return (lhs._type >= rhs.base());
			}

			iterator_type base() const
			{
				return (this->_type);
			}
	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() <= rhs.base();
	}

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
