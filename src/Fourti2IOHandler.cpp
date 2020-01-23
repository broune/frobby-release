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
#include "Fourti2IOHandler.h"

#include "Scanner.h"
#include "BigIdeal.h"

void Fourti2IOHandler::readIdeal(Scanner& scanner, BigIdeal& ideal) {
  size_t termCount;
  size_t varCount;

  scanner.readInteger(termCount);
  scanner.readInteger(varCount);

  VarNames names(varCount);
  ideal.clearAndSetNames(names);

  ideal.reserve(termCount);
  for (size_t t = 0; t < termCount; ++t) {
	// Read a term
	ideal.newLastTerm();
	vector<mpz_class>& term = ideal.getLastTermRef();
	for (size_t var = 0; var < varCount; ++var)
	  scanner.readIntegerAndNegativeAsZero(term[var]);
  }
}

void Fourti2IOHandler::readIrreducibleDecomposition(Scanner& scanner,
													BigIdeal& decom) {
  fputs("ERROR: The 4ti2 format does not support decompositions.\n", stderr);
  exit(1);
}

void Fourti2IOHandler::readTerm(Scanner& in, const VarNames& names,
								vector<mpz_class>& term) {
  term.resize(names.getVarCount());
  for (size_t var = 0; var < names.getVarCount(); ++var)
	in.readIntegerAndNegativeAsZero(term[var]);
}

void Fourti2IOHandler::writeIdeal(FILE* out, const BigIdeal& ideal) {
  fprintf(out, "%lu %lu\n",
		  (unsigned long)ideal.getGeneratorCount(),
		  (unsigned long)ideal.getVarCount());

  for (size_t term = 0; term < ideal.getGeneratorCount(); ++term) {
	for (size_t var = 0; var < ideal[term].size(); ++var) {
	  if (var != 0)
		fputc(' ', out);
	  gmp_fprintf(out, "%Zd", ideal[term][var].get_mpz_t());
	}
	fputc('\n', out);
  }
}

IdealWriter* Fourti2IOHandler::createWriter
(FILE* file, const VarNames& names) const {
  fputs("ERROR: The 4ti2 format does not support incremental output.", stderr);
  exit(1);
}

IdealWriter* Fourti2IOHandler::createWriter
(FILE* file, const TermTranslator* translator) const {
  fputs("ERROR: The 4ti2 format does not support incremental output.", stderr);
  exit(1);
}

const char* Fourti2IOHandler::getFormatName() const {
  return "4ti2";
}
