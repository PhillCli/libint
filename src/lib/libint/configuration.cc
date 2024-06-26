/*
 *  Copyright (C) 2004-2024 Edward F. Valeev
 *
 *  This file is part of Libint library.
 *
 *  Libint library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Libint library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Libint library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <libint2/util/configuration.h>

#include <cstdio>
#include <cstring>

const char *configuration_accessor(void) {
  // return "@Libint2_CONFIG_COMPONENTS@";
  return "(nyi)";
}

void libint_version(int *major, int *minor, int *micro) {
  *major = -1;
  *minor = -1;
  *micro = -1;
  std::sscanf(libint_version_string(false), "%d.%d.%d", major, minor, micro);
}

const char *libint_version_string(bool ext) {
  if (ext)
    return "@LIBINT_SORTABLE_VERSION@";
  else
    return "@LIBINT_VERSION@";
}

const char *libint_commit(void) { return "@LIBINT_GIT_COMMIT@"; }

const char *libint_reference(void) {
  std::string ref = "Libint: @LIBINT_DESCRIPTION@, Version " +
                    std::string(libint_version_string(true)) +
                    " Edward F. Valeev, http://libint.valeyev.net/";

  auto slen = ref.length();
  char *cref = new char[slen + 1];
  std::memcpy(cref, ref.c_str(), slen);
  cref[slen] = '\0';
  return cref;
}

const char *libint_reference_doi(void) { return "@LIBINT_DOI@"; }

const char *libint_bibtex(void) {
  return "@Misc{Libint2,\n  author = {E.~F.~Valeev},\n  title = "
         "{\\textsc{Libint}: @LIBINT_DESCRIPTION@},\n  "
         "howpublished = {http://libint.valeyev.net/},\n  note = {version "
         "@Libint2_VERSION@},\n  year = {@LIBINT_VERSION_YEAR@}\n}\n";
}
