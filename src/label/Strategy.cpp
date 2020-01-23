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
#include "Strategy.h"

#include "PrintDebugStrategy.h"
#include "StatisticsStrategy.h"
#include "CompositeStrategy.h"
#include "PrintProgressStrategy.h"
#include "SkipRedundantStrategy.h"

Strategy::~Strategy() {
}

void Strategy::startingPartitioning(const Term& b,
				    const OldPartition& partition,
				    const TermTree& tree) {
  ASSERT(false);
}
    
void Strategy::doingPartitionSet(int position,
				 const Term& b,
				 const Term& compressedB,
				 const OldPartition& partition,
				 vector<Exponent> compressor,
				 const TermTree& tree) {
  ASSERT(false);
}

void Strategy::doneDoingPartitionSet(int position,
				     const vector<Exponent>& compressor) {
  string name;
  getName(name);
  fprintf(stderr,
	  "ERROR: doneDoingPartitionSet not implemented in %s.\n",
	  name.c_str());
  ASSERT(false);
}

void Strategy::endingPartitioning(int position,
				  const Term& b) {
  string name;
  getName(name);
  fprintf(stderr, "ERROR: endingPartitioning not implemented in %s.\n",
	  name.c_str());
  ASSERT(false);
}

Strategy* Strategy::addDebugOutput(Strategy* strategy) {
  return new CompositeStrategy(strategy, new PrintDebugStrategy());
}

Strategy* Strategy::addStatistics(Strategy* strategy, size_t varCount) {
  return new CompositeStrategy(strategy, new StatisticsStrategy(varCount));
}

Strategy* Strategy::addPrintProgress(Strategy* strategy) {
  return new CompositeStrategy(strategy, new PrintProgressStrategy());
}

Strategy* Strategy::addSkipRedundant(Strategy* strategy, size_t varCount) {
  return new SkipRedundantStrategy(strategy, varCount);
}
