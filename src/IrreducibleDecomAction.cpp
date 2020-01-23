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
#include "IrreducibleDecomAction.h"

#include "BigIdeal.h"
#include "IrreducibleDecomFacade.h"
#include "IOFacade.h"

const char* IrreducibleDecomAction::getName() const {
  return "irrdecom";
}

const char* IrreducibleDecomAction::getShortDescription() const {
  return "Compute the irreducible decomposition of the input ideal.";
}

const char* IrreducibleDecomAction::getDescription() const {
  return
"Compute the irredundant irreducible decomposition of the input monomial ideal.\n\n"
"The decomposition is computed using the Slice Algorithm. This algorithm is\n"
"described in the paper `The Slice Algorithm For Irreducible Decomposition of\n"
"Monomial Ideals', which is available at www.broune.com . It is also possible\n""to use the older Label algorithm, though this is not as efficient.";
}

Action* IrreducibleDecomAction::createNew() const {
  return new IrreducibleDecomAction();
}

void IrreducibleDecomAction::obtainParameters(vector<Parameter*>& parameters) {
  Action::obtainParameters(parameters);
  _decomParameters.obtainParameters(parameters);
}

void IrreducibleDecomAction::perform() {
  BigIdeal ideal;

  IOFacade ioFacade(_printActions);
  ioFacade.readIdeal(stdin, ideal);

  IrreducibleDecomFacade facade(_printActions, _decomParameters);
  facade.computeIrreducibleDecom(ideal, stdout);
}