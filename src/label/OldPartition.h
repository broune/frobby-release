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
#ifndef OLD_PARTITION_GUARD
#define OLD_PARTITION_GUARD

#include <vector>
class Term;

class OldPartition {
 public:
  OldPartition(int size);
  ~OldPartition();

  void join(int i, int j);

  int getSetCount(int minSize = 1, int position = 0) const;

  int getSetSize(int set, int position = 0) const;

  int getRoot(int i) const;

  void getSetTranslators(int number,
			 vector<Exponent>& compressor,
			 int position = 0) const;

  bool compress(Term& term,
		const vector<Exponent>& compressor) const;

 private:
  int* _partitions;
  int _size;
};

#endif
