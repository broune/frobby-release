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
#ifndef PARAMETER_GROUP_GUARD
#define PARAMETER_GROUP_GUARD

#include "Parameter.h"
#include <vector>

class ParameterGroup : public Parameter {
 public:
  ParameterGroup(const char* name, const char* description);
  virtual ~ParameterGroup();

  virtual bool process(const char** params, unsigned int paramCount);
  virtual void processParameters(const char** params, unsigned int paramCount);

  void addParameter(Parameter* parameter);

  void obtainParameters(vector<Parameter*>& parameters);

  virtual void getValue(string& str) const;

 private:
  vector<Parameter*> _parameters;
};

#endif