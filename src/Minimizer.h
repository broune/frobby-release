/* Frobby, software for computations related to monomial ideals.
   Copyright (C) 2007 Bjarke Hammersholt Roune (www.broune.com)

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/ 
#ifndef IDEAL_MINIMIZER_GUARD
#define IDEAL_MINIMIZER_GUARD

#include <vector>

class Minimizer {
 private:
  typedef vector<Exponent*>::iterator iterator;

 public:
  Minimizer(size_t varCount):
	_varCount(varCount) {}

  iterator minimize(iterator begin, iterator end) const;

 private:
  size_t _varCount;
};

#endif
