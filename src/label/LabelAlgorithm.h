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
#ifndef LABEL_ALGORITHM_GUARD
#define LABEL_ALGORITHM_GUARD

class Term;
class Strategy;
class TermTree;
class Ideal;

class LabelAlgorithm {
public:
  LabelAlgorithm();

  void setStrategy(Strategy* strategy);
  void setUsePartition(bool usePartition);

  // Runs the algorithm and clears ideal. Then deletes the strategy.
  void runAndClear(Ideal& ideal);

private:
  bool performPartition(const Term& b, const TermTree& tree);
  void recurse(const Term& b, const TermTree& tree,
	       bool startingPartition);
  void baseCase(const Term& b, const TermTree& tree);

  unsigned int _dimension;
  Strategy* _strategy;
  bool _usePartition;
};

#endif
