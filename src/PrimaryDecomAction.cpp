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
#include "PrimaryDecomAction.h"

#include "BigIdeal.h"
#include "IOFacade.h"
#include "PrimaryDecomFacade.h"

const char* PrimaryDecomAction::getName() const {
  return "primdecom";
}

const char* PrimaryDecomAction::getShortDescription() const {
  return "Computes the primary decomposition of monomial ideals.";
}

const char* PrimaryDecomAction::getDescription() const {
  return
    "Computes the primary decomposition of monomial ideals using\n"
    "the Uwe algorithm.\n"
    "\n"
    "Do note that this operation is currently implemented in a slow way.\n";
}

Action* PrimaryDecomAction::createNew() const {
  return new PrimaryDecomAction();
}

void PrimaryDecomAction::obtainParameters(vector<Parameter*>& parameters) {
  Action::obtainParameters(parameters);
}

void PrimaryDecomAction::perform() {
  BigIdeal ideal;
  IOFacade ioFacade(_printActions);
  ioFacade.readIdeal(stdin, ideal);

  PrimaryDecomFacade facade(_printActions);
  facade.computePrimaryDecom(ideal, stdout);
}