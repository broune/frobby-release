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
#include "ParameterGroup.h"

ParameterGroup::ParameterGroup(const char* name, const char* description):
  Parameter(name, description) {
}

ParameterGroup::~ParameterGroup() {
}

void ParameterGroup::getValue(string& str) const {
  str = "...";
}

bool ParameterGroup::process(const char** params, unsigned int paramCount) {
  for (vector<Parameter*>::const_iterator it = _parameters.begin();
       it != _parameters.end(); ++it)
    if ((*it)->process(params, paramCount))
      return true;

  return false;
}

void ParameterGroup::processParameters(const char** params,
				       unsigned int paramCount) {
  fputs("INTERNAL ERROR: Called ParameterGroup::processParameters.\n", stderr);
  ASSERT(false);
  exit(1);
}

void ParameterGroup::addParameter(Parameter* parameter) {
  ASSERT(parameter != 0);

  _parameters.push_back(parameter);
}

void ParameterGroup::obtainParameters(vector<Parameter*>& parameters) {
  parameters.insert(parameters.begin(),
		    _parameters.begin(),
		    _parameters.end());
}
