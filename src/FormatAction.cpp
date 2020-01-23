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
#include "FormatAction.h"

#include "BigIdeal.h"
#include "IOFacade.h"
#include "IdealFacade.h"

FormatAction::FormatAction():
  _inputFormat
("iformat",
 "The input format. The available formats are monos, m2, 4ti2, null and newmonos.",
 "monos"),
  
  _outputFormat
  ("oformat",
   "The output format. The additional format \"auto\" means use input format.",
   "auto"),
  
  _canonicalize
  ("canon",
   "Sort generators and variables to get canonical representation.",
   false),

  _sort
  ("sort",
   "Sort generators according to the reverse lexicographic order.",
   false),

  _unique
  ("unique",
   "Remove duplicate generators.",
   false),

  _minimize 
  ("minimize",
  "Remove non-minimial generators.",
   false) {
}

const char* FormatAction::getName() const {
  return "format";
}

const char* FormatAction::getShortDescription() const {
  return "Change the representation of the input ideal.";
}

const char* FormatAction::getDescription() const {
  return
    "By default, format simply writes the input ideal to output. A number\n"
    "of parameters allows to change the representation of the ideal\n"
    "in various ways before writing it out.";
}

Action* FormatAction::createNew() const {
  return new FormatAction();
}

void FormatAction::obtainParameters(vector<Parameter*>& parameters) {
  parameters.push_back(&_inputFormat);
  parameters.push_back(&_outputFormat);
  parameters.push_back(&_canonicalize);
  parameters.push_back(&_minimize);
  parameters.push_back(&_sort);
  parameters.push_back(&_unique);
  Action::obtainParameters(parameters);
}

void FormatAction::perform() {
  string iformat = _inputFormat.getValue();
  string oformat = _outputFormat.getValue();

  if (oformat == "auto")
    oformat = iformat;

  IOFacade facade(_printActions);

  if (!facade.isValidMonomialIdealFormat(iformat.c_str())) {
    fprintf(stderr, "ERROR: Unknown input format \"%s\".\n", iformat.c_str());
    exit(1);
  }

  if (!facade.isValidMonomialIdealFormat(oformat.c_str())) {
    fprintf(stderr, "ERROR: Unknown output format \"%s\".\n", oformat.c_str());
    exit(1);
  }

  BigIdeal ideal;
  facade.readIdeal(stdin, ideal, iformat.c_str());

  IdealFacade idealFacade(_printActions);

  if (_minimize)
    idealFacade.sortAllAndMinimize(ideal, stdout, oformat.c_str());
  else {
	if (_canonicalize)
	  idealFacade.sortVariables(ideal);

	if (_unique)
	  idealFacade.sortGeneratorsUnique(ideal);
	else if (_sort || _canonicalize)
	  idealFacade.sortGenerators(ideal);

	facade.writeIdeal(stdout, ideal, oformat.c_str());
  }
}
