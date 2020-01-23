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
#ifndef SKIP_REDUNDANT_STRATEGY_GUARD
#define SKIP_REDUNDANT_STRATEGY_GUARD

#include "Strategy.h"

class TermTree;
class TermTranslator;
class OldPartition;

class SkipRedundantStrategy : public Strategy {
public:
  SkipRedundantStrategy(Strategy* strategy,
			unsigned int dimension);
  ~SkipRedundantStrategy();

  virtual void getName(string& name) const;

  virtual bool consideringCall(const Term& b,
			       bool sameExponentAsNext,
			       const TermTree& tree);

  virtual bool startingCall(const Term& b,
			    const TermTree& tree,
			    bool startingPartition);

  virtual void endingCall(const Term& b,
			  const TermTree& tree);
  
  virtual void foundSolution(const Term& b,
			     bool startingPartition);

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

private:
  vector<TermTree> _skip;
  vector<vector<Term> > _newSkip;
  vector<bool> _remember;
  unsigned int _dimension;
  Strategy* _strategy;

  vector<Exponent> _toAddNext;
  vector<TermTree> _seen;
  vector<TermTree> _projectedSeen;
  vector<bool> _seenHasChanged;
};

#endif
