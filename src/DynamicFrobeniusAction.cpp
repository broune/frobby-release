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
#include "DynamicFrobeniusAction.h"

#include "IOFacade.h"
#include "DynamicFrobeniusFacade.h"

const char* DynamicFrobeniusAction::getName() const {
  return "frobdyn";
}

const char* DynamicFrobeniusAction::getShortDescription() const {
  return "Compute Frobenius number using a dynamic programming algorithm.";
}

const char* DynamicFrobeniusAction::getDescription() const {
  return
"Compute the Frobenius number of the input Frobenius instance using a simple\n"
"and quite slow dynamic programming algorithm. This functionality has mainly\n"
"been implemented to check the answers of the Grobner basis-based Frobenius\n"
"solver.";
}

Action* DynamicFrobeniusAction::createNew() const {
  return new DynamicFrobeniusAction();
}

void DynamicFrobeniusAction::obtainParameters(vector<Parameter*>& parameters) {
  Action::obtainParameters(parameters);
}

void DynamicFrobeniusAction::perform() {
  vector<mpz_class> instance;

  IOFacade ioFacade(_printActions);
  ioFacade.readFrobeniusInstance(stdin, instance);

  mpz_class frobeniusNumber;

  DynamicFrobeniusFacade frobeniusFacade(_printActions);
  frobeniusFacade.computeFrobeniusNumber(instance, frobeniusNumber);

  gmp_fprintf(stdout, "%Zd\n", frobeniusNumber.get_mpz_t());
}