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
#include "LatticeFormatAction.h"

#include "BigIdeal.h"
#include "IOFacade.h"
#include "fplllIO.h"
#include "LatticeFacade.h"

LatticeFormatAction::LatticeFormatAction():
  _inputFormat
("iformat",
 "The input format. The available formats are 4ti2 and fplll.",
 "4ti2"),
  
  _outputFormat
  ("oformat",
   "The output format. The additional format \"auto\" means use input format.",
   "auto"),

  _zero
  ("zero",
   "Adjust lattice basis to increase the number of zero entries.",
   false) {
}

const char* LatticeFormatAction::getName() const {
  return "latformat";
}

const char* LatticeFormatAction::getShortDescription() const {
  return "Change the representation of the input lattice.";
}

const char* LatticeFormatAction::getDescription() const {
  return
    "By default, latformat simply writes the input lattice to output.\n"
    "The main functionality is to change the format.";
}

Action* LatticeFormatAction::createNew() const {
  return new LatticeFormatAction();
}

void LatticeFormatAction::obtainParameters(vector<Parameter*>& parameters) {
  Action::obtainParameters(parameters);
  parameters.push_back(&_inputFormat);
  parameters.push_back(&_outputFormat);
  parameters.push_back(&_zero);
}

void LatticeFormatAction::perform() {
  string iformat = _inputFormat.getValue();
  string oformat = _outputFormat.getValue();

  if (oformat == "auto")
    oformat = iformat;

  IOFacade facade(_printActions);

  if (!facade.isValidLatticeFormat(iformat.c_str())) {
    fprintf(stderr, "ERROR: Unknown input format \"%s\".\n", iformat.c_str());
    exit(1);
  }

  if (!facade.isValidLatticeFormat(oformat.c_str())) {
    fprintf(stderr, "ERROR: Unknown output format \"%s\".\n", oformat.c_str());
    exit(1);
  }

  BigIdeal basis;
  facade.readLattice(stdin, basis, iformat.c_str());

  if (_zero) {
    LatticeFacade latticeFacade(_printActions);
    latticeFacade.makeZeroesInLatticeBasis(basis);
  }

  facade.writeLattice(stdout, basis, oformat.c_str());
}