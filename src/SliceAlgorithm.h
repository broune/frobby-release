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
#ifndef SLICE_ALGORITHM_GUARD
#define SLICE_ALGORITHM_GUARD

class Ideal;
class Slice;
class SliceStrategy;
class Term;

// Computes the Maximal Standard Monomials (MSMs) of the input ideal.
class SliceAlgorithm {
 public:
  SliceAlgorithm();

  // setStrategy takes over ownership of the strategy.
  void setStrategy(SliceStrategy* strategy);
  void setUseIndependence(bool useIndependence);

  // Runs the algorithm and clears ideal. Then deletes the strategy
  // and consumer.
  void runAndClear(Ideal& ideal);

 private:
  void content(Slice& slice, bool simplifiedAndDependent = false);

  void labelSplit(Slice& slice);
  void labelSplit2(Slice& slice);
  void pivotSplit(Slice& slice);
  bool independenceSplit(Slice& slice);

  bool _useIndependence;
  SliceStrategy* _strategy;
};

// For getting a single MSM. This may fail if slice.getIdeal() is
// not artinian, in which case the return value is false.
bool computeSingleMSM(const Slice& slice, Term& msm);

#endif