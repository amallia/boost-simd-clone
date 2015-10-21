//==================================================================================================
/*!
  @file

  @copyright 2012-2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MAXLEFTSHIFT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MAXLEFTSHIFT_HPP_INCLUDED

#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/dispatch/function/make_callable.hpp>
#include <boost/dispatch/hierarchy/functions.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/as.hpp>
//TODO
namespace boost { namespace simd
{
  namespace tag
  {
    struct maxleftshift_ : boost::dispatch::constant_value_<maxleftshift_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxleftshift_,boost::dispatch::constant_value_<maxleftshift_>);
      struct value_map
      {
        template<typename X>
        static std::integral_constant<typename boost::dispatch::as_integer_t<X>,sizeof(X)*CHAR_BIT-1> value(boost::dispatch::arithmetic_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,maxleftshift_);
  }

  namespace functional
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxleftshift_,maxleftshift);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxleftshift() BOOST_NOEXCEPT
  -> decltype(functional::maxleftshift( boost::dispatch::as_<T>{}))
  {
    return functional::maxleftshift( boost::dispatch::as_<T>{} );
  }
} }

#endif
