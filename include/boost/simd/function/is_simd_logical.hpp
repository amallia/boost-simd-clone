//==================================================================================================
/*!
  @file

  @copyright 2012-2015 NumScale SAS
  @copyright 2015 J.T.Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_SIMD_LOGICAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-reduction

    returns true if all vector elements have all or no bit sets.

    @par Semantic:

    For every parameter of type T0

    @code
    logical<scalar_of_t<T0>> r = is_simd_logical(a0);
    @endcode

    is similar to:

    @code
    T0 r = all(a0 == Allbits || a0 == Zero);
    @endcode


    @return a value of the scalar logical type associated to the parameter

**/
  template<typename T> auto is_simd_logical(T const& x) {}

  namespace functional
  {
    /*!
      @ingroup group-reduction

      Function object tied to simd::is_simd_logical

      @see simd::is_simd_logical
    **/
    const boost::dispatch::functor<tag::is_simd_logical_> is_simd_logical = {};
  }
} }
#endif

#include <boost/simd/function/definition/is_simd_logical.hpp>
#include <boost/simd/arch/common/scalar/function/is_simd_logical.hpp>
//#include <boost/simd/arch/common/function/simd/is_simd_logical.hpp>

#endif