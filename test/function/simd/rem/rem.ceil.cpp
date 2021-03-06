//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#include <boost/simd/pack.hpp>
#include <boost/simd/function/rem.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/function/is_negative.hpp>
#include <boost/simd/function/is_positive.hpp>
#include <boost/simd/function/all.hpp>
#include <simd_test.hpp>

template <typename T, std::size_t N, typename Env>
void test(Env& $)
{
  namespace bs = boost::simd;
  using p_t = bs::pack<T, N>;

  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  T a1[N], a2[N], b[N];
  for(std::size_t i = 0; i < N; ++i)
  {
     a1[i] =  T(i) ;
     a2[i] = T(i+N) ;
     b[i] = bs::rem(bs::ceil, a1[i], a2[i]);
   }
  p_t aa1(&a1[0], &a1[0]+N);
  p_t aa2(&a2[0], &a2[0]+N);
  p_t bb(&b[0], &b[0]+N);
  STF_IEEE_EQUAL(bs::rem(bs::ceil, aa1, aa2), bb);
}

STF_CASE_TPL("Check rem on pack" , STF_SIGNED_NUMERIC_TYPES)
{
  namespace bs = boost::simd;
  using p_t = bs::pack<T>;
  static const std::size_t N = bs::cardinal_of<p_t>::value;
  test<T, N>($);
  test<T, N/2>($);
  test<T, N*2>($);
}

template <typename T, std::size_t N, typename Env>
void testceilfast(Env& $)
{
  namespace bs = boost::simd;
  using p_t = bs::pack<T, N>;

  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  T a1[N], a2[N], b[N];
  for(std::size_t i = 0; i < N; ++i)
  {
     a1[i] =T(i);
     a2[i] =T(i+N);
     b[i] = bs::fast_(bs::rem)(bs::ceil, a1[i], a2[i]);
   }
  p_t aa1(&a1[0], &a1[0]+N);
  p_t aa2(&a2[0], &a2[0]+N);
  p_t bb(&b[0], &b[0]+N);
  STF_IEEE_EQUAL(bs::fast_(bs::rem)(bs::ceil, aa1, aa2), bb);
}

STF_CASE_TPL("Check fast_(rem) on pack option ceil" , STF_IEEE_TYPES)
{
  namespace bs = boost::simd;
  using p_t = bs::pack<T>;
  static const std::size_t N = bs::cardinal_of<p_t>::value;
  testceilfast<T, N>($);
  testceilfast<T, N/2>($);
  testceilfast<T, N*2>($);
}


STF_CASE_TPL("Check rem ceil on pack limiting cases" , STF_IEEE_TYPES)
{
  namespace bs = boost::simd;
  using p_t = bs::pack<T>;
  STF_EXPECT(bs::all(bs::is_negative(bs::rem(bs::floor, bs::Mzero<p_t>(), bs::One<p_t>()))));
  STF_EXPECT(bs::all(bs::is_positive(bs::rem(bs::floor, bs::Zero<p_t>(), bs::One<p_t>()))));
  STF_IEEE_EQUAL(bs::rem(bs::floor, bs::Mzero<p_t>(), bs::One<p_t>()), bs::Zero<p_t>());
  STF_IEEE_EQUAL(bs::rem(bs::floor, bs::Zero<p_t>(), bs::One<p_t>()), bs::Zero<p_t>());
 #ifndef BOOST_SIMD_NO_INVALIDS
  STF_IEEE_EQUAL(bs::rem(bs::ceil, bs::Inf<p_t>(), bs::Inf<p_t>()), bs::Nan<p_t>());
  STF_IEEE_EQUAL(bs::rem(bs::ceil, bs::Minf<p_t>(), bs::Minf<p_t>()), bs::Nan<p_t>());
  STF_IEEE_EQUAL(bs::rem(bs::ceil, bs::Nan<p_t>(), bs::Nan<p_t>()), bs::Nan<p_t>());
  STF_IEEE_EQUAL(bs::rem(bs::ceil, bs::Inf<p_t>(), bs::One<p_t>()), bs::Nan<p_t>());
  STF_IEEE_EQUAL(bs::rem(bs::ceil, bs::One<p_t>(), bs::Zero<p_t>()), bs::Nan<p_t>());
  STF_IEEE_EQUAL(bs::rem(bs::ceil, bs::Zero<p_t>(), bs::Zero<p_t>()), bs::Nan<p_t>());
#endif

}
