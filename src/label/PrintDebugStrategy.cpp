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
#include "../stdinc.h"
#include "PrintDebugStrategy.h"

#include "TermTree.h"

#include <iterator>

PrintDebugStrategy::~PrintDebugStrategy() {
  fputs("The computation is done.\n", stderr);
}

void PrintDebugStrategy::getName(string& name) const {
  name = "PrintDebugStrategy";
}

bool PrintDebugStrategy::consideringCall(const Term& b,
					 bool sameExponentAsNext,
					 const TermTree& tree) {
  return false;
}

bool PrintDebugStrategy::startingCall(const Term& b,
				      const TermTree& tree,
				      bool startingPartition) {
  if (tree.getPosition() == 0) {
    fputs("Debug printing on. Starting the computation.\n", stderr);
  }
  
  for (int i = 0; i < tree.getPosition(); ++i)
    fputc('^', stderr);
  fputs(" Starting b=", stderr);
  b.print(stderr);
  fprintf(stderr, " position=%lu\n", (unsigned long)tree.getPosition());

  return false;
}

void PrintDebugStrategy::endingCall(const Term& b,
				    const TermTree& tree) {
  for (int i = 0; i < tree.getPosition(); ++i)
    fputc('v', stderr);
  fputs(" Ending b=", stderr);
  b.print(stderr);
  fprintf(stderr, " position=%lu\n", (unsigned long)tree.getPosition());
}

void PrintDebugStrategy::foundSolution(const Term& b,
				       bool startingPartition) {
  for (unsigned int i = 0; i < b.getVarCount(); ++i)
    fputc('*', stderr);
  fputs(" Found solution ", stderr);
  b.print(stderr);
  fputc('\n', stderr);
}

void PrintDebugStrategy::startingPartitioning(const Term& b,
					      const Partition& partition,
					      const TermTree& tree) {
  for (int i = 0; i < tree.getPosition(); ++i)
    fputc('-', stderr);
  fputs(" starting partitioning\n", stderr);
}

void PrintDebugStrategy::doingPartitionSet(int position,
					   const Term& b,
					   const Term& compressedB,
					   const Partition& partition,
					   vector<Exponent> compressor,
					   const TermTree& tree) {
  fputs("doing a set of the partition\n", stderr);
}

void PrintDebugStrategy::doneDoingPartitionSet
(int position,
 const vector<Exponent>& compressor) {
  fputs("done doing that set of the partition\n", stderr);
}

void PrintDebugStrategy::endingPartitioning(int position,
					    const Term& b) {
  fputs("ending partitioning\n", stderr);
}
