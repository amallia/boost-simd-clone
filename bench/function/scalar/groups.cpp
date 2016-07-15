// -------------------------------------------------------------------------------------------------
//                              Copyright 2016 - NumScale SAS
//
//                   Distributed under the Boost Software License, Version 1.0.
//                        See accompanying file LICENSE.txt or copy at
//                            http://www.boost.org/LICENSE_1_0.txt
// -------------------------------------------------------------------------------------------------

#include <simd_bench.hpp>
#include <boost/simd/function/simd/group.hpp>
#include <cmath>

namespace nsb = ns::bench;
namespace bs =  boost::simd;

DEFINE_SCALAR_BENCH(scalar_groups, bs::saturated_(bs::group));

int main(int argc, char** argv) {
  nsb::parse_args(argc, argv);
  nsb::for_each<scalar_groups, NS_BENCH_IEEE_TYPES>(-10, 10, -10, 10);
  print_results();
  return 0;
}
