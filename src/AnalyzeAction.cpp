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
#include "AnalyzeAction.h"

#include "BigIdeal.h"
#include "IOFacade.h"
#include "IdealFacade.h"

AnalyzeAction::AnalyzeAction():
  _printLcm
("printLcm",
 "Print the least common multiple of the generators.",
 false) {
}

const char* AnalyzeAction::getName() const {
  return "analyze";
}

const char* AnalyzeAction::getShortDescription() const {
  return "Display information about the input ideal.";
}

const char* AnalyzeAction::getDescription() const {
  return "Compute and display information about input ideal.";
}

Action* AnalyzeAction::createNew() const {
  return new AnalyzeAction();
}

void AnalyzeAction::obtainParameters(vector<Parameter*>& parameters) {
  Action::obtainParameters(parameters);
  parameters.push_back(&_printLcm);
}

void AnalyzeAction::perform() {
  BigIdeal ideal;

  IOFacade ioFacade(_printActions);
  ioFacade.readIdeal(stdin, ideal);

  IdealFacade idealFacade(_printActions);
  if (_printLcm)
	idealFacade.printLcm(stdout, ideal);
  idealFacade.printAnalysis(stderr, ideal);
}
