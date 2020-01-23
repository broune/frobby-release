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
#ifndef IRREDUCIBLE_DECOM_PARAMETERS_GUARD
#define IRREDUCIBLE_DECOM_PARAMETERS_GUARD

#include "ParameterGroup.h"
#include "BoolParameter.h"
#include "StringParameter.h"

class IrreducibleDecomParameters : public ParameterGroup {
 public:
  IrreducibleDecomParameters(bool exposeBoundParam = false);

  void setUseIndependence(bool value);
  void setSplit(const string& split);

  bool getPrintDebug() const;
  bool getPrintStatistics() const;
  bool getUseBound() const;
  bool getUseIndependence() const;
  bool getMinimal() const;
  
  const string& getSplit() const;

 private:
  bool _exposeBoundParam;

  BoolParameter _printDebug;
  BoolParameter _printStatistics;
  BoolParameter _useBound;
  BoolParameter _useIndependence;
  BoolParameter _minimal;

  StringParameter _split;
};

#endif
