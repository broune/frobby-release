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
#include "GenerateIdealParameters.h"

GenerateIdealParameters::GenerateIdealParameters():
  ParameterGroup("", ""),
  _exponentRange
  ("expRange",
   "Exponents are chosen uniformly in the range [0,INTEGER].", 9),

  _variableCount("varCount", "The number of variables.", 3),
  _generatorCount("genCount", "The number of minimal generators.", 5) {
  addParameter(&_exponentRange);
  addParameter(&_variableCount);
  addParameter(&_generatorCount);
}

unsigned int GenerateIdealParameters::getExponentRange() const {
  return _exponentRange;
}

unsigned int GenerateIdealParameters::getVariableCount() const {
  return _variableCount;
}

unsigned int GenerateIdealParameters::getGeneratorCount() const {
  return _generatorCount;
}
