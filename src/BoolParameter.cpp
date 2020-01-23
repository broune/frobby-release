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
#include "BoolParameter.h"

BoolParameter::BoolParameter(const char* name,
			     const char* description,
			     bool defaultValue):
  Parameter(name, description),
  _value(defaultValue) {
}

const char* BoolParameter::getParameterName() const {
  return "[BOOL]";
}

void BoolParameter::getValue(string& str) const {
  if (_value)
    str = "on";
  else
    str = "off";
}

BoolParameter::operator bool() const {
  return _value;
}

BoolParameter& BoolParameter::operator=(bool value) {
  _value = value;
  return *this;
}

void BoolParameter::
processParameters(const char** params, unsigned int paramCount) {
  checkCorrectParameterCount(0, 1, params, paramCount);
  
  if (paramCount == 0) {
    _value = true;
    return;
  }
  ASSERT(paramCount == 1);

  string param(params[0]);
  if (param == "off")
    _value = false;
  else if (param == "on")
    _value = true;
  else {
    fprintf(stderr, "ERROR: Option -%s was given the parameter \"%s\".\n"
	    "The only valid parameters are \"on\" and \"off\".\n",
	    getName(), param.c_str());
    exit(1);
  }
}