/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:14 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/15 13:37:43 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
#define STACK_H

#include <deque>

namespace ft
{
	/**
	 * @brief Stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out), where elements are inserted and extracted only from one end of the container. stacks are implemented as container adaptors, which are classes that use an encapsulated object of a specific container class as its underlying container, providing a specific set of member functions to access its elements. Elements are pushed/popped from the "back" of the specific container, which is known as the top of the stack.
	 *
	 * @tparam T Type of the elements.
	 * @tparam Container Type of the internal underlying container object where the elements are stored.
	 */
	template <class T, class Container = std::deque<T> > class stack
	{
	  public:
		typedef T         value_type;
		typedef Container container_type;
		typedef size_t    size_type;

		explicit stack(const container_type &ctnr = container_type())
		    : container(ctnr){};
		~stack(){};
		template <class E, class Cont>
		friend bool operator==(const ft::stack<E, Cont> &lhs, const ft::stack<E, Cont> &rhs);
		template <class E, class Cont>
		friend bool operator!=(const ft::stack<E, Cont> &lhs, const ft::stack<E, Cont> &rhs);
		template <class E, class Cont>
		friend bool operator<(const ft::stack<E, Cont> &lhs, const ft::stack<E, Cont> &rhs);
		template <class E, class Cont>
		friend bool operator<=(const ft::stack<E, Cont> &lhs, const ft::stack<E, Cont> &rhs);
		template <class E, class Cont>
		friend bool operator>(const ft::stack<E, Cont> &lhs, const ft::stack<E, Cont> &rhs);
		template <class E, class Cont>
		friend bool operator>=(const ft::stack<E, Cont> &lhs, const ft::stack<E, Cont> &rhs);

		/**
		 * @brief Test whether container is empty
		 * This member function effectively calls member empty of the underlying container object.
		 *
		 * @return true if the underlying container's size is 0, false otherwise.
		 */
		bool empty() const
		{
			return this->container.empty();
		}

		/**
		 * @brief Returns the number of elements in the stack.
		 * This member function effectively calls member size of the underlying container object.
		 *
		 * @return The number of elements in the underlying container.
		 */
		size_t size() const
		{
			return this->container.size();
		}

		/**
		 * @brief Returns a reference to the top element in the stack.
		 * Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
		 * This member function effectively calls member back of the underlying container object.
		 *
		 * @return A reference to the top element in the stack.
		 */
		value_type &top()
		{
			return this->container.back();
		}

		/**
		 * @brief Returns a constant reference to the top element in the stack.
		 * Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
		 * This member function effectively calls member back of the underlying container object.
		 *
		 * @return A reference to the top element in the stack.
		 */
		const value_type &top() const
		{
			return this->container.back();
		}

		/**
		 * @brief Inserts a new element at the top of the stack, above its current top element. The content of this new element is initialized to a copy of val.
		 * This member function effectively calls the member function push_back of the underlying container object.
		 *
		 * @param val Value to which the inserted element is initialized.
		 * Member type value_type is the type of the elements in the container (defined as an alias of the first class template parameter, T).
		 */
		void push(const value_type &val)
		{
			return this->container.push_back(val);
		}

		/**
		 * @brief Remove top element
		 * Removes the element on top of the stack, effectively reducing its size by one.
		 * The element removed is the latest element inserted into the stack, whose value can be retrieved by calling member stack::top.
		 * This calls the removed element's destructor.
		 * This member function effectively calls the member function pop_back of the underlying container object.
		 */
		void pop()
		{
			return this->container.pop_back();
		}

	  private:
		container_type container;
	};
	// operators
	template <class T, class Container>
	bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.container == rhs.container;
	}
	template <class T, class Container>
	bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.container != rhs.container;
	}
	template <class T, class Container>
	bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.container < rhs.container;
	}
	template <class T, class Container>
	bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.container <= rhs.container;
	}
	template <class T, class Container>
	bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.container > rhs.container;
	}
	template <class T, class Container>
	bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.container >= rhs.container;
	}
} // namespace ft

#endif
