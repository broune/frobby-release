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
#include "GenerateIdealAction.h"

#include "BigIdeal.h"
#include "RandomDataFacade.h"
#include "IOFacade.h"

const char* GenerateIdealAction::getName() const {
  return "genideal";
}

const char* GenerateIdealAction::getShortDescription() const {
  return "Generate a random monomial ideal.";
}

const char* GenerateIdealAction::getDescription() const {
  return
    "Generate a random monomial ideal. In certain rare cases the generated ideal\n"
"may have less than the requested number of minimial generators. This can be\n"
"alleviated by increasing the exponent range or the number of variables.";
}

Action* GenerateIdealAction::createNew() const {
  return new GenerateIdealAction();
}

void GenerateIdealAction::obtainParameters(vector<Parameter*>& parameters) {
  Action::obtainParameters(parameters);
  _parameters.obtainParameters(parameters);
}

void GenerateIdealAction::perform() {
  BigIdeal ideal;
  
  RandomDataFacade randomDataFacade(_printActions);
  randomDataFacade.generateIdeal(ideal, _parameters);

  IOFacade ioFacade(_printActions);
  ioFacade.writeIdeal(stdout, ideal);
}
