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
#include "stdinc.h"
#include "Term.h"

const unsigned int PoolCount = 50;
const unsigned int ObjectPoolSize = 1000;

struct ObjectPool {
  ObjectPool(): objectsStored(0), objects(0) {}

  bool empty() const {
    return objectsStored == 0;
  }

  bool canStoreMore() const {
    return objectsStored < ObjectPoolSize;
  }

  Exponent* removeObject() {
    ASSERT(!empty());
    --objectsStored;
    return objects[objectsStored];
  }

  void addObject(Exponent* object) {
    ASSERT(canStoreMore());

    if (objects == 0)
      objects = new Exponent*[ObjectPoolSize];
    objects[objectsStored] = object;
    ++objectsStored;
  }
  
  ~ObjectPool() {
    if (objects == 0)
      return;
    for (size_t i = 0; i < objectsStored; ++i)
      delete[] objects[i];
    delete[] objects;
  }

  unsigned int objectsStored;
  Exponent** objects;
} pools[PoolCount];

Exponent* Term::allocate(size_t size) {
  ASSERT(size > 0);

  if (size < PoolCount && !pools[size].empty())
    return pools[size].removeObject();
  else
    return new Exponent[size];  
}

void Term::deallocate(Exponent* p, size_t size) {
  if (p == 0)
    return;

  ASSERT(size > 0);

  if (size < PoolCount && pools[size].canStoreMore())
    pools[size].addObject(p);
  else
    delete[] p;
}
