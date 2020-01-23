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
#ifndef GENERATE_IDEAL_PARAMETERS_GUARD
#define GENERATE_IDEAL_PARAMETERS_GUARD

#include "ParameterGroup.h"
#include "IntegerParameter.h"

class GenerateIdealParameters : public ParameterGroup {
 public:
  GenerateIdealParameters();

  unsigned int getExponentRange() const;
  unsigned int getVariableCount() const;
  unsigned int getGeneratorCount() const;
  
 private:
  IntegerParameter _exponentRange;
  IntegerParameter _variableCount;
  IntegerParameter _generatorCount;
};

#endif