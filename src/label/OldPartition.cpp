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
#include "OldPartition.h"

#include "../Term.h"

OldPartition::OldPartition(int size):
  _partitions(new int[size]),
  _size(size) {
  fill_n(_partitions, _size, -1);
}

OldPartition::~OldPartition() {
  delete[] _partitions;
}

void OldPartition::join(int i, int j) {
  int rootI = getRoot(i);
  int rootJ = getRoot(j);
  
  if (rootI == rootJ)
    return;
  
  _partitions[rootI] += _partitions[rootJ];
  _partitions[rootJ] = rootI;
}

int OldPartition::getSetCount(int minSize, int position) const {
  int partitionCount = 0;
  for (int i = position; i < _size; ++i)
    if (i == getRoot(i) &&
	-_partitions[i] >= minSize)
      ++partitionCount;
  return partitionCount;
}

int OldPartition::getSetSize(int set, int position) const {
  for (int i = position; i < _size; ++i) {
    if (i == getRoot(i)) {
      if (set == 0)
	return -_partitions[i];
      --set;
    }
  }
  ASSERT(false);
  return 0;
}

int OldPartition::getRoot(int i) const {
  ASSERT(i < _size);
  if (_partitions[i] >= 0) {
    _partitions[i] = getRoot(_partitions[i]);
    return _partitions[i];
  } else
    return i;
}

void OldPartition::getSetTranslators(int number,
				  vector<Exponent>& compressor,
				  int position) const {
  
  int root = -1;
  for (int i = position; i < _size; ++i) {
    if (i == getRoot(i)) {
      if (number == 0) {
	root = i;
	break;
      }
      --number;
    }
  }
  ASSERT(number == 0 && root != -1);

  compressor.resize(_size);
    
  // Compressing t is done by setting t[compressor[i]] = t[i].

  int decompressorOffset = _size - 1;
  int compressorOffset = _size - 1;
  for (; compressorOffset >= 0; --compressorOffset) {
    if (getRoot(compressorOffset) != root) {
      compressor[compressorOffset] = 0xFFFFFFFF;
      continue;
    }

    compressor[compressorOffset] = decompressorOffset;
    --decompressorOffset;
  }
}

bool OldPartition::compress(Term& term,
			 const vector<Exponent>& compressor) const {
  bool insideSet = false;
  bool outsideSet = false;

  for (int i = _size - 1; i >= 0; --i) {
    if (compressor[i] == 0xFFFFFFFF) {
      if (term[i] != 0)
	outsideSet = true;
      continue;
    }
    if (term[i] != 0)
      insideSet = true;
    term[compressor[i]] = term[i];
  }

  return insideSet && !outsideSet;
}
