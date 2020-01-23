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
#include "GenerateFrobeniusAction.h"

#include "BigIdeal.h"
#include "RandomDataFacade.h"
#include "IOFacade.h"

const char* GenerateFrobeniusAction::getName() const {
  return "genfrob";
}

const char* GenerateFrobeniusAction::getShortDescription() const {
  return "Generate a random Frobenius problem instance.";
}

const char* GenerateFrobeniusAction::getDescription() const {
  return "Generate a random Frobenius problem instance.";
}

Action* GenerateFrobeniusAction::createNew() const {
  return new GenerateFrobeniusAction();
}

void GenerateFrobeniusAction::
obtainParameters(vector<Parameter*>& parameters) {
  Action::obtainParameters(parameters);
}

void GenerateFrobeniusAction::perform() {
  vector<mpz_class> instance;

  RandomDataFacade randomDataFacade(_printActions);
  randomDataFacade.generateFrobeniusInstance(instance);

  IOFacade ioFacade(_printActions);
  ioFacade.writeFrobeniusInstance(stdout, instance);
}
