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
#include "SkipRedundantStrategy.h"

#include "TermTree.h"

#include <iterator>
#include "OldPartition.h"


SkipRedundantStrategy::SkipRedundantStrategy(Strategy* strategy,
					     unsigned int dimension):
  _newSkip(dimension),
  _remember(dimension),
  _dimension(dimension),
  _strategy(strategy),
  _toAddNext(dimension),
  _seenHasChanged(dimension) {
  for (unsigned int position = 0; position < _dimension; ++position)
    _skip.push_back(TermTree(dimension, position));
}

SkipRedundantStrategy::~SkipRedundantStrategy() {
  delete _strategy;
}

void SkipRedundantStrategy::getName(string& name) const {
  name = "SkipRedundantStrategy";
}

bool SkipRedundantStrategy::consideringCall(const Term& b,
					    bool sameExponentAsNext,
					    const TermTree& tree) {
  unsigned int position = tree.getPosition();
  
  _remember[position] = sameExponentAsNext;

  if (_skip[position].getDivisor(b) != 0) {
    if (!sameExponentAsNext)
      _newSkip[position + 1].clear();
    return false;
  }

  return _strategy->consideringCall(b, sameExponentAsNext, tree);
}

bool SkipRedundantStrategy::startingCall(const Term& b,
					 const TermTree& tree,
					 bool startingPartition) {
  unsigned int position = tree.getPosition();
  
  if (!startingPartition) {
    _skip[position].clear();
    _skip[position].setThreshold(b);
    if (position > 0)
      _skip[position].insertProjectionOf(_skip[position - 1], 0, b[position - 1]);
    for (unsigned int i = 0; i < _newSkip[position].size(); ++i)
      _skip[position].insert(_newSkip[position][i]);
  }

  _remember[position] = false;
      
  return _strategy->startingCall(b, tree, startingPartition);
}

void SkipRedundantStrategy::endingCall(const Term& b,
				       const TermTree& tree) {
  unsigned int position = tree.getPosition();

  if (position > 0) {
    if (_remember[position - 1])
      _newSkip[position].push_back(b);
    else
      _newSkip[position].clear();
  }

  _strategy->endingCall(b, tree);
}
  
void SkipRedundantStrategy::foundSolution(const Term& b,
					  bool startingPartition) {
  if ((startingPartition && _skip[_dimension - 1].getDivisor(b) == 0) ||
      (!startingPartition && _skip[_dimension - 2].getDivisor(b) == 0))
    _strategy->foundSolution(b, startingPartition);
}

void SkipRedundantStrategy::
startingPartitioning(const Term& b,
		     const OldPartition& partition,
		     const TermTree& tree) {
  unsigned int position = tree.getPosition();
  
  _skip[position].clear();
  _skip[position].setThreshold(b);
  if (position > 0)
    _skip[position].insertProjectionOf(_skip[position - 1], 0, b[position - 1]);
  for (unsigned int i = 0; i < _newSkip[position].size(); ++i)
    _skip[position].insert(_newSkip[position][i]);

  _remember[position] = false; // TODO: is this necessary?

  _strategy->startingPartitioning(b, partition, tree);
}
    
void SkipRedundantStrategy::doingPartitionSet(int position,
					      const Term& b,
					      const Term& compressedB,
					      const OldPartition& partition,
					      vector<Exponent> compressor,
					      const TermTree& tree) {
  int nextPosition = tree.getPosition();
  TermTree::TreeIterator it((TermTree&)_skip[position]);

  _skip[nextPosition].clear();
  _skip[nextPosition].setThreshold(compressedB);

  Term term(_dimension);
  while (!it.atEnd()) {
    it.getTerm(term);

    for (int i = _dimension - 1; i >= position; --i) {
      if (compressor[i] == 0xFFFFFFFF) {
	if (term[i] > b[i])
	  goto skip;
      } else
	term[compressor[i]] = term[i];
    }
    _skip[nextPosition].insert(term);

  skip:
    ++it;
  }

  _strategy->doingPartitionSet(position, b, compressedB, partition, compressor, tree);
}

void SkipRedundantStrategy::
doneDoingPartitionSet(int position,
		      const vector<Exponent>& compressor) {
  _strategy->doneDoingPartitionSet(position, compressor);
}

void SkipRedundantStrategy::endingPartitioning(int position,
					       const Term& b) {
  if (position > 0) {
    if (_remember[position - 1])
      _newSkip[position].push_back(b);
    else
      _newSkip[position].clear();
  }
  
  _strategy->endingPartitioning(position, b);
}
