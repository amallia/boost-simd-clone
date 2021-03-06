//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#include <boost/simd/pack.hpp>
#include <boost/simd/function/next.hpp>
#include <boost/simd/function/bits.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <simd_test.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/eps.hpp>
#include <boost/simd/constant/bitincrement.hpp>
#include <boost/simd/constant/two.hpp>


template <typename T, std::size_t N, typename Env>
void test(Env& $)
{
  namespace bs = boost::simd;
  using p_t = bs::pack<T, N>;

  T a1[N], b[N];
  for(std::size_t i = 0; i < N; ++i)
  {
    a1[i] = (i%2) ? T(i) : T(-i);
    b[i] = bs::next(a1[i]) ;
  }
  p_t aa1(&a1[0], &a1[0]+N);
  p_t bb (&b[0], &b[0]+N);
  STF_IEEE_EQUAL(bs::next(aa1), bb);
}

STF_CASE_TPL("Check next on pack" , STF_NUMERIC_TYPES)
{
  namespace bs = boost::simd;
  using p_t = bs::pack<T>;
  static const std::size_t N = bs::cardinal_of<p_t>::value;
  test<T, N>($);
  test<T, N/2>($);
  test<T, N*2>($);
}


STF_CASE_TPL (" next real",  STF_IEEE_TYPES)
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;
  using bs::next;
  using p_t = bs::pack<T>;
  using r_t = decltype(next(p_t()));

  // return type conformity test
  STF_TYPE_IS(r_t, p_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  STF_EQUAL(next(bs::Inf<p_t>()), bs::Inf<r_t>());
  STF_EQUAL(next(bs::Minf<p_t>()), bs::Valmin<r_t>());
  STF_IEEE_EQUAL(next(bs::Nan<p_t>()), bs::Nan<r_t>());
  STF_EQUAL(next(bs::Valmax<p_t>()), bs::Inf<r_t>());
#endif
  STF_EQUAL(next(bs::Mone<p_t>()), bs::Mone<r_t>()+bs::Eps<r_t>()/2);
  STF_EQUAL(next(bs::One<p_t>()), bs::One<r_t>()+bs::Eps<r_t>());
  STF_EQUAL(next(bs::Zero<p_t>()), bs::Bitincrement<p_t>());
}

STF_CASE_TPL (" next unsigned_int",  STF_UNSIGNED_INTEGRAL_TYPES)
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;
  using bs::next;
  using p_t = bs::pack<T>;
  using r_t = decltype(next(p_t()));

  // return type conformity test
  STF_TYPE_IS(r_t, p_t);

  // specific values tests
  STF_EQUAL(next(bs::One<p_t>()), bs::Two<r_t>());
  STF_EQUAL(next(bs::Valmax<p_t>()), bs::Valmin<r_t>());
  STF_EQUAL(next(bs::Zero<p_t>()), bs::One<r_t>());
}

STF_CASE_TPL (" next signed_int",  STF_SIGNED_INTEGRAL_TYPES)
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;
  using bs::next;
  using p_t = bs::pack<T>;
  using r_t = decltype(next(p_t()));

  // return type conformity test
  STF_TYPE_IS(r_t, p_t);

  // specific values tests
  STF_EQUAL(next(bs::Mone<p_t>()), bs::Zero<r_t>());
  STF_EQUAL(next(bs::One<p_t>()), bs::Two<r_t>());
  STF_EQUAL(next(bs::Zero<p_t>()), bs::One<r_t>());
}
