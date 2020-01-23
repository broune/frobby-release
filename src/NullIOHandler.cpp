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
#include "NullIOHandler.h"

#include "BigIdeal.h"

class NullIdealWriter : public IdealWriter {
public:
  NullIdealWriter() {
  }

  virtual ~NullIdealWriter() {
  }

  virtual void consume(const vector<mpz_class>& term) {
  }

  virtual void consume(const Term& term) {
  }
};

IdealWriter* NullIOHandler::
createWriter(FILE* file, const VarNames& names) const {
  return new NullIdealWriter();
}

IdealWriter* NullIOHandler::
createWriter(FILE* file, const TermTranslator* translator) const {
  return new NullIdealWriter();
}

void NullIOHandler::readIdeal(Scanner& scanner, BigIdeal& ideal) {
  VarNames names;
  ideal.clearAndSetNames(names);
}

void NullIOHandler::readIrreducibleDecomposition(Scanner& scanner,
												 BigIdeal& decom) {
}

const char* NullIOHandler::getFormatName() const {
  return "null";
}
