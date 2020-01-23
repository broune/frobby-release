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
#ifndef SLICE_STRATEGY_GUARD
#define SLICE_STRATEGY_GUARD

#include <string>
#include "TermConsumer.h"

class Slice;
class Term;
class TermTranslator;
class Projection;
class Ideal;
class TermGrader;

class SliceStrategy : public TermConsumer {
 public:
  virtual ~SliceStrategy();

  virtual void initialize(const Slice& slice);

  // *** Methods for handling independence splits
  virtual void doingIndependenceSplit(const Slice& slice,
				      Ideal* mixedProjectionSubtract) = 0;
  virtual void doingIndependentPart(const Projection& projection,
				    bool last) = 0;
  virtual bool doneWithIndependentPart() = 0;
  virtual void doneWithIndependenceSplit() = 0;

  // *** Methods to inform debug strategies when the algorothm starts
  // processing the content of a slice and when it stops.
  virtual void startingContent(const Slice& slice);
  virtual void endingContent();

  // *** Methods for handling pivot and label splits

  enum SplitType {
    LabelSplit = 1,
    PivotSplit = 2
  };
  virtual SplitType getSplitType(const Slice& slice) = 0;

  virtual void getPivot(Term& pivot, const Slice& slice);
  virtual size_t getLabelSplitVariable(const Slice& slice);

  // report a msm to the strategy.
  virtual void consume(const Term& term) = 0;

  // Simplifies the slice prior to a split.
  virtual void simplify(Slice& slice);


  // *** Static methods to create strategies.

  // These report an error and exit the program if the name is unknown.
  static SliceStrategy* newDecomStrategy(const string& name,
										 TermConsumer* consumer);
  static SliceStrategy* newFrobeniusStrategy(const string& name,
											 TermConsumer* consumer,
											 TermGrader& grader);

  static SliceStrategy* addStatistics(SliceStrategy* strategy);
  static SliceStrategy* addDebugOutput(SliceStrategy* strategy);
};

#endif