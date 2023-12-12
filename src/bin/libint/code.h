/*
 *  Copyright (C) 2004-2021 Edward F. Valeev
 *
 *  This file is part of Libint.
 *
 *  Libint is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Libint is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Libint.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <vector>

#ifndef _libint2_src_bin_libint_code_h_
#define _libint2_src_bin_libint_code_h_

namespace libint2 {

/** Class CodeSymbols specifies a set of symbols used in a code
 */

class CodeSymbols {
 public:
  CodeSymbols();
  ~CodeSymbols();

  void append_symbol(const std::string& s);
  unsigned int n() const;
  const std::string& symbol(unsigned int i) const;

 private:
  std::vector<std::string> symbols_;
};

};  // namespace libint2

#endif
