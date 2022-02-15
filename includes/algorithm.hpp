/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:56:09 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/15 13:40:30 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
	/**
	 * @brief Test whether the elements in two ranges are equal
	 * Compares the elements in the range [first1,last1) with those in the range beginning at first2, and returns true if all of the elements in both ranges match.
	 *
	 * @tparam InputIt1 InputIt2 must meet the requirements of LegacyInputIterator.
	 * @tparam InputIt2 ForwardIt2 must meet the requirements of LegacyForwardIterator.
	 * @param first1 Input iterators to the initial and final positions of the first sequence. The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
	 * @param last1 Input iterators to the initial and final positions of the first sequence. The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
	 * @param first2 Input iterator to the initial position of the second sequence. The comparison includes up to as many elements of this sequence as those in the range [first1,last1).
	 * @return true
	 * @return false
	 */
	template <class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief
	 *
	 * @brief Test whether the elements in two ranges are equal
	 * Compares the elements in the range [first1,last1) with those in the range beginning at first2, and returns true if all of the elements in both ranges match.
	 *
	 * @tparam InputIt1 InputIt2 must meet the requirements of LegacyInputIterator.
	 * @tparam InputIt2 ForwardIt2 must meet the requirements of LegacyForwardIterator.
	 * @param first1 Input iterators to the initial and final positions of the first sequence. The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
	 * @param last1 Input iterators to the initial and final positions of the first sequence. The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
	 * @param first2 Input iterator to the initial position of the second sequence. The comparison includes up to as many elements of this sequence as those in the range [first1,last1).
	 * @param p binary predicate which returns ​true if the elements should be treated as equal.
	 * The signature of the predicate function should be equivalent to the following:
	 *  - bool pred(const Type1 &a, const Type2 &b);
	 * While the signature does not need to have const &, the function must not modify the objects passed to it and must be able to accept all values of type (possibly const) Type1 and Type2 regardless of value category (thus, Type1 & is not allowed, nor is Type1 unless for Type1 a move is equivalent to a copy (since C++11)).
	 * The types Type1 and Type2 must be such that objects of types InputIt1 and InputIt2 can be dereferenced and then implicitly converted to Type1 and Type2 respectively.​
	 * @return true
	 * @return false
	 */
	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	 * A lexicographical comparison is the kind of comparison generally used to sort words alphabetically in dictionaries; It involves comparing sequentially the elements that have the same position in both ranges against each other until one element is not equivalent to the other. The result of comparing these first non-matching elements is the result of the lexicographical comparison.
	 * If both sequences compare equal until one of them ends, the shorter sequence is lexicographically less than the longer one.
	 *
	 * @tparam InputIt1
	 * @tparam InputIt2
	 * @param first1 Input iterators to the initial and final positions of the first sequence. The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
	 * @param last1 Input iterators to the initial and final positions of the first sequence. The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
	 * @param first2 Input iterators to the initial and final positions of the second sequence. The range used is [first2,last2).
	 * @param last2 Input iterators to the initial and final positions of the second sequence. The range used is [first2,last2).
	 * @return true
	 * @return false
	 */
	template <class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	/**
	 * @brief Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	 * A lexicographical comparison is the kind of comparison generally used to sort words alphabetically in dictionaries; It involves comparing sequentially the elements that have the same position in both ranges against each other until one element is not equivalent to the other. The result of comparing these first non-matching elements is the result of the lexicographical comparison.
	 * If both sequences compare equal until one of them ends, the shorter sequence is lexicographically less than the longer one.
	 *
	 * @tparam InputIt1
	 * @tparam InputIt2
	 * @param first1 Input iterators to the initial and final positions of the first sequence. The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
	 * @param last1 Input iterators to the initial and final positions of the first sequence. The range used is [first1,last1), which contains all the elements between first1 and last1, including the element pointed by first1 but not the element pointed by last1.
	 * @param first2 Input iterators to the initial and final positions of the second sequence. The range used is [first2,last2).
	 * @param last2 Input iterators to the initial and final positions of the second sequence. The range used is [first2,last2).
	 * @param comp Binary function that accepts two arguments of the types pointed by the iterators, and returns a value convertible to bool. The value returned indicates whether the first argument is considered to go before the second in the specific strict weak ordering it defines.
	 * The function shall not modify any of its arguments.
	 * This can either be a function pointer or a function object.
	 * @return true
	 * @return false
	 */
	template <class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
} // namespace ft

#endif
