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
#include "FrobeniusAction.h"

#include "BigIdeal.h"
#include "IOFacade.h"
#include "IrreducibleDecomFacade.h"

FrobeniusAction::FrobeniusAction() {
  _decomParameters.setUseIndependence(false);
  _decomParameters.setSplit("frob");
}

const char* FrobeniusAction::getName() const {
  return "frobgrob";
}

const char* FrobeniusAction::getShortDescription() const {
  return "Compute Frobenius number using a Grobner basis algorithm.";
}

const char* FrobeniusAction::getDescription() const {
  return
"Compute the Frobenius number of the passed-in Frobenius instance. This instance\n"
"must be preceded in the input by a deg-rev-lex lattice ideal Grobner basis as\n"
"produced by the program 4ti2.\n"
"\n"
"The algorithm for this uses irreducible decomposition to compute the Frobenius\n"
"number, which is why this action accepts parameters related to that. See the\n"
"paper \"Solving Thousand Digit Frobenius Problems Using Grobner Bases\"\n"
"at www.broune.com for more details.";
}

Action* FrobeniusAction::createNew() const {
  return new FrobeniusAction();
}

void FrobeniusAction::obtainParameters(vector<Parameter*>& parameters) {
  Action::obtainParameters(parameters);
  _decomParameters.obtainParameters(parameters);
}

void FrobeniusAction::perform() {
  vector<mpz_class> instance;
  BigIdeal ideal;

  IOFacade ioFacade(_printActions);
  ioFacade.readFrobeniusInstanceWithGrobnerBasis(stdin, ideal, instance);

  if (_decomParameters.getUseIndependence()) {
    fputs("NOTE: Due to implementation issues, the Grobner basis\n"
	  "based Frobenius feature using the Label algorithm does\n"
	  "not support independence splits. They have been turned off.\n",
	  stderr);
    _decomParameters.setUseIndependence(false);
  }

  IrreducibleDecomFacade facade(_printActions, _decomParameters);

  mpz_class frobeniusNumber;
  facade.computeFrobeniusNumber(instance, ideal, frobeniusNumber);

  gmp_fprintf(stdout, "%Zd\n", frobeniusNumber.get_mpz_t());
}
