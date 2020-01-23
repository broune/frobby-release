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
#include "stdinc.h"
#include "randomDataGenerators.h"

#include "BigIdeal.h"
#include "Ideal.h"
#include "Term.h"

bool generateRandomIdeal(BigIdeal& bigIdeal,
			 unsigned int exponentRange,
			 unsigned int variableCount,
			 unsigned int generatorCount) {
  Ideal ideal(variableCount);
  Term term(variableCount);

  unsigned int generatorsToGo = generatorCount;
  unsigned int triesLeft = (unsigned int)4 * 1000 * 1000;
  while (generatorsToGo > 0 && triesLeft > 0) {
    --triesLeft;

    for (unsigned int var = 0; var < variableCount; ++var) {
      term[var] = rand();
      if (exponentRange != numeric_limits<unsigned int>::max())
	term[var] %= exponentRange + 1;
    }

    if (ideal.isIncomparable(term)) {
      ideal.insert(term);
      --generatorsToGo;
    }

    --triesLeft;
  }

  VarNames names(variableCount);
  bigIdeal.clearAndSetNames(names);
  bigIdeal.insert(ideal);

  return generatorsToGo == 0;
}

void generateRandomFrobeniusInstance(vector<Degree>& degrees) {
  int numberCount = 10;//;4 + (rand() % 6);
  int mod = 100000;

  degrees.resize(numberCount);

  Degree totalGcd = 0;
  for (int i = 0; i < numberCount - 1; ++i) {
    Degree number = Degree(2+(rand() % mod));
    if (totalGcd == 0)
      totalGcd = number;
    else {
      mpz_gcd(totalGcd.get_mpz_t(),
	      totalGcd.get_mpz_t(),
	      number.get_mpz_t());
    }
    degrees[i] = number;
  }

  // This ensures that the gcd of all the numbers is 1.
  degrees[numberCount - 1] =
    (totalGcd == 1 ? Degree((rand() % mod) + 2) : totalGcd + 1);

  sort(degrees.begin(), degrees.end());
}
