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
#ifndef RANDOM_DATA_FACADE_GUARD
#define RANDOM_DATA_FACADE_GUARD

#include "Facade.h"
#include <vector>

class BigIdeal;
class GenerateIdealParameters;

class RandomDataFacade : private Facade {
 public:
  RandomDataFacade(bool printActions);

  void generateIdeal(BigIdeal& ideal,
		     const GenerateIdealParameters& generateIdealParams);
  void generateFrobeniusInstance(vector<mpz_class>& instance);
};

#endif
