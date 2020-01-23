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
#ifndef STRATEGY_GUARD
#define STRATEGY_GUARD

#include <vector>

class Term;
class TermTree;
class OldPartition;

class Strategy {
public:
  virtual ~Strategy();

  virtual bool consideringCall(const Term& b,
			       bool sameExponentAsNext,
			       const TermTree& tree) = 0;

  virtual bool startingCall(const Term& b,
			    const TermTree& tree,
			    bool startingPartition) = 0;

  virtual void endingCall(const Term& b,
			  const TermTree& tree) = 0;

  virtual void foundSolution(const Term& b,
			     bool startingPartition) = 0;

  virtual void startingPartitioning(const Term& b,
				    const OldPartition& partition,
				    const TermTree& tree);
    
  virtual void doingPartitionSet(int position,
				 const Term& b,
				 const Term& compressedB,
				 const OldPartition& partition,
				 vector<Exponent> compressor,
				 const TermTree& tree);

  virtual void doneDoingPartitionSet(int position,
				     const vector<Exponent>& compressor);

  virtual void endingPartitioning(int position,
				  const Term& b);

  virtual void getName(string& name) const = 0;

  static Strategy* addDebugOutput(Strategy* strategy);
  static Strategy* addStatistics(Strategy* strategy, size_t varCount);
  static Strategy* addPrintProgress(Strategy* strategy);
  static Strategy* addSkipRedundant(Strategy* strategy, size_t varCount);
};

#endif
