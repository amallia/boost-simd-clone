//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS
  @copyright 2015 J.T. Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED

#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/arch/common/detail/generic/invtrig.hpp>
#include <boost/simd/function/scalar/copysign.hpp>
#include <boost/simd/function/scalar/if_else.hpp>
#include <boost/simd/function/scalar/if_else_zero.hpp>
#include <boost/simd/function/scalar/is_gtz.hpp>
#include <boost/simd/function/scalar/is_inf.hpp>
#include <boost/simd/function/scalar/is_ltz.hpp>
#include <boost/simd/function/scalar/is_nan.hpp>
#include <boost/simd/function/scalar/signnz.hpp>
#include <boost/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( atan2_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      #ifndef BOOST_SIMD_NO_NANS
      if (bs::is_nan(a0) || bs::is_nan(a1)) return bs::Nan<A0>();
      #endif

      #ifndef BOOST_SIMD_NO_INFINITIES
      if (bs::is_inf(a0) && bs::is_inf(a1))
      {
        a0 = bs::copysign(bs::One<A0>(), a0);
        a1 = bs::copysign(bs::One<A0>(), a1);
      }
      #endif
      A0 z = detail::invtrig_base<A0,radian_tag, tag::not_simd_type>::kernel_atan(a0/a1);
      z = bs::if_else(bs::is_gtz(a1), z, bs::Pi<A0>()-z)*bs::signnz(a0);
      return bs::if_else(bs::is_eqz(a0), bs::if_else_zero(bs::is_ltz(a1), bs::Pi<A0>()), z);
    }
  };
} } }


#endif