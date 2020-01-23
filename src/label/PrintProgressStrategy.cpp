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
#include "PrintProgressStrategy.h"

#include "TermTree.h"

#include <iomanip>

PrintProgressStrategy::PrintProgressStrategy():
  _workTotal(0),
  _workDone(0) {}

void PrintProgressStrategy::getName(string& name) const {
  name = "PrintProgressStrategy";
}

bool PrintProgressStrategy::consideringCall(const Term& b,
					    bool sameExponentAsNext,
					    const TermTree& tree) {
  ASSERT(_workTotal != 0);
  ASSERT(_workDone <= _workTotal);
  
  if (tree.getPosition() == 0) {
    if (_timeSinceLastReport.getSeconds() >= 5) {
      _timeSinceLastReport.reset();

      double doneRatio = ((double)_workDone)/_workTotal;
      fprintf(stderr, "%lu/%lu=%.3f%% done in ",
	      (unsigned long)_workDone,
	      (unsigned long)_workTotal,
	      doneRatio * 100.0);
      _totalTime.print(stderr);
      fputs(".\n", stderr);
    }

    ++_workDone;
  }

  return false;
}

bool PrintProgressStrategy::startingCall(const Term& b,
					 const TermTree& tree,
					 bool startingPartition) {
  if (tree.getPosition() == 0) {
    _workTotal = 0;
    TermTree::TreeIterator treeIt(tree);
    while (!treeIt.atEnd()) {
      if (treeIt.getExponent(0) != 0)
	++_workTotal;
      ++treeIt;
    }
  }

  return false;
}

void PrintProgressStrategy::endingCall(const Term& b,
				       const TermTree& tree) {
}

void PrintProgressStrategy::foundSolution(const Term& b,
					  bool startingPartition) {
}

void PrintProgressStrategy::startingPartitioning(const Term& b,
						 const Partition& partition,
						 const TermTree& tree) {
}

void PrintProgressStrategy::doingPartitionSet(int position,
					      const Term& b,
					      const Term& compressedB,
					      const Partition& partition,
					      vector<Exponent> compressor,
					      const TermTree& tree) {
}

void PrintProgressStrategy::
doneDoingPartitionSet(int position,
		      const vector<Exponent>& compressor) {
}

void PrintProgressStrategy::endingPartitioning(int position,
					       const Term& b) {
}
