//==================================================================================================
/*!
  @file

  @copyright 2012-2015 NumScale SAS
  @copyright 2015 J.T.Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NLTZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NLTZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-predicates

    Returns True if a0 is not less than zero else returns False.

    @par Semantic:

    @code
    logical<T> r = is_nltz(a0);
    @endcode

    is similar to:

    @code
    logical<T> r = !(a0 < 0);
    @endcode


    @par Note:

    Due to existence of nan, this is not equivalent to @c is_gez(a0)
    for floating types


    @return a logical value

**/
  template<typename T> auto is_nltz(T const& x) {}

  namespace functional
  {
    /*!
      @ingroup group-predicates

      Function object tied to simd::is_nlt

z      @see simd::is_nlt
z    **/
    const boost::dispatch::functor<tag::is_nltz_> is_nltz = {};
  }
} }
#endif

#include <boost/simd/function/definition/is_nltz.hpp>
#include <boost/simd/arch/common/scalar/function/is_nltz.hpp>
//#include <boost/simd/arch/common/function/simd/is_nltz.hpp>

#endif