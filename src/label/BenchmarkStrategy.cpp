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
#include "BenchmarkStrategy.h"

void BenchmarkStrategy::getName(string& name) const {
  name = "BenchmarkStrategy";
}

bool BenchmarkStrategy::consideringCall(const Term& b,
					bool sameExponentAsNext,
					const TermTree& tree) {
  return true;
}

bool BenchmarkStrategy::startingCall(const Term& b,
				     const TermTree& tree,
				     bool startingPartition) {
  return true;
}

void BenchmarkStrategy::endingCall(const Term& b,
				   const TermTree& tree) {
}

void BenchmarkStrategy::foundSolution(const Term& b,
				      bool startingPartition) {
}  

void BenchmarkStrategy::startingPartitioning(const Term& b,
					     const Partition& partition,
					     const TermTree& tree) {
}

void BenchmarkStrategy::doingPartitionSet(int position,
					  const Term& b,
					  const Term& compressedB,
					  const Partition& partition,
					  vector<Exponent> compressor,
					  const TermTree& tree) {
}

void BenchmarkStrategy::doneDoingPartitionSet(int position,
					      const vector<Exponent>& compressor) {
}

void BenchmarkStrategy::endingPartitioning(int position,
					   const Term& b) {
}
