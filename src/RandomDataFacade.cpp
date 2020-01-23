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
#include "RandomDataFacade.h"

#include "randomDataGenerators.h"
#include "GenerateIdealParameters.h"

RandomDataFacade::RandomDataFacade(bool printActions):
  Facade(printActions) {
}

void RandomDataFacade::generateIdeal
(BigIdeal& ideal,
 const GenerateIdealParameters& generateIdealParams) {
  beginAction("Generating random monomial ideal.");

  bool fullSize =
    ::generateRandomIdeal(ideal,
			  generateIdealParams.getExponentRange(),
			  generateIdealParams.getVariableCount(),
			  generateIdealParams.getGeneratorCount());
  endAction();
  
  if (!fullSize)
    fputs("NOTE: Generated ideal has fewer minimal "
	  "generators than requested.\n", stderr);
}

void RandomDataFacade::generateFrobeniusInstance(vector<mpz_class>& instance) {
  beginAction("Generating random Frobenius instance.");

  ::generateRandomFrobeniusInstance(instance);

  endAction();
}
