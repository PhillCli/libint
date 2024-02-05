/*
 *  Copyright (C) 2004-2024 Edward F. Valeev
 *
 *  This file is part of Libint compiler.
 *
 *  Libint compiler is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Libint compiler is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Libint compiler.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <global_macros.h>
#include <iter.h>
#include <libint2.h>
#include <libint2/config.h>
#include <libint2/deriv_iter.h>
#include <libint2/util/memory.h>
#include <math.h>
#include <policy_spec.h>
#include <rr.h>
#include <stdlib.h>
#include <sys/time.h>
#include <test_eri/prep_libint2.h>
#include <util.h>

#include <iostream>
#include <sstream>
// generated by test_eri.pl
#include <test_eri_conf.h>

using namespace std;
using namespace libint2;

typedef unsigned int uint;

libint2::FmEval_Chebyshev7<double> fmeval_chebyshev(28);
libint2::FmEval_Taylor<double, 6> fmeval_taylor(28, 1e-15);

namespace {
std::string usage();
std::string am2label(unsigned int);
unsigned int am2nbf(unsigned int);
};  // namespace

int main(int argc, char** argv) {
  typedef unsigned int uint;

  if (argc != 2) {
    cerr << usage() << endl;
    exit(1);
  }

  uint niter = atoi(argv[1]);

  const uint veclen = LIBINT2_MAX_VECLEN;
#if LIBINT_CONTRACTED_INTS
  const uint contrdepth = 3;
#else
  const uint contrdepth = 1;
#endif
  const uint contrdepth4 = contrdepth * contrdepth * contrdepth * contrdepth;
  RandomShellSet<4> rsqset(am, veclen, contrdepth);

  const unsigned int deriv_order = 0;
  CartesianDerivIterator<4> diter(deriv_order);
  const unsigned int nderiv = diter.range_size();

  CGShell sh0(am[0]);
  CGShell sh1(am[1]);
  CGShell sh2(am[2]);
  CGShell sh3(am[3]);

  const double* A = &(rsqset.R[0][0]);
  const double* B = &(rsqset.R[1][0]);
  const double* C = &(rsqset.R[2][0]);
  const double* D = &(rsqset.R[3][0]);

  typedef SubIteratorBase<CGShell> iter;
  std::shared_ptr<iter> sh0_iter(new iter(sh0));
  std::shared_ptr<iter> sh1_iter(new iter(sh1));
  std::shared_ptr<iter> sh2_iter(new iter(sh2));
  std::shared_ptr<iter> sh3_iter(new iter(sh3));

  Libint_eri0_t* erieval = libint2::malloc<Libint_eri0_t>(contrdepth4);
  const int max_am = max(max(am[0], am[1]), max(am[2], am[3]));
  LIBINT2_PREFIXED_NAME(libint2_init_eri0)(&erieval[0], max_am, 0);

  // record start wall time
  struct timeval tod;
  gettimeofday(&tod, 0);
  const double start_wall_time = tod.tv_sec + 0.000001 * tod.tv_usec;

  prep_libint2(erieval, rsqset, 0);
  erieval[0].nflops[0] = 0;

  cout << "Computing (" << am2label(am[0]) << am2label(am[1]) << "|"
       << am2label(am[2]) << am2label(am[3]) << ") " << niter << " times"
       << endl;

#if LIBINT_CONTRACTED_INTS
  erieval[0].contrdepth = contrdepth4;
#endif
  for (int iter = 0; iter < niter; iter++) COMPUTE_XX_ERI_XX(&erieval[0]);

  // record end wall time, compute total wall time spent here
  gettimeofday(&tod, 0);
  const double end_wall_time = tod.tv_sec + 0.000001 * tod.tv_usec;
  const unsigned int nints = am2nbf(am[0]) * am2nbf(am[1]) * am2nbf(am[2]) *
                             am2nbf(am[3]) * LIBINT2_MAX_VECLEN;
  cout << "nflops = " << *(erieval[0].nflops) << " nints = " << nints
       << " wtime = " << (end_wall_time - start_wall_time) << " seconds"
       << endl;

  LIBINT2_PREFIXED_NAME(libint2_cleanup_eri0)(&erieval[0]);
  free(erieval);

  exit(0);
}

namespace {
std::string usage() {
  ostringstream oss;
  oss << "Usage: time_eri <niter>" << endl;
  oss << "       niter -- number of iterations" << endl;
  return oss.str();
}

std::string am2label(unsigned int l) {
  static char labels[] = "spdfghiklmoqrtuvwxyz";
  std::ostringstream oss;
  oss << labels[l];
  return oss.str();
}

unsigned int am2nbf(unsigned int l) { return (l + 1) * (l + 2) / 2; }
};  // namespace
