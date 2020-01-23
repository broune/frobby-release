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
#ifndef LATTICE_FORMAT_ACTION_GUARD
#define LATTICE_FORMAT_ACTION_GUARD

#include "Action.h"
#include "StringParameter.h"
#include "BoolParameter.h"

class LatticeFormatAction : public Action {
 public:
  LatticeFormatAction();

  virtual const char* getName() const;
  virtual const char* getShortDescription() const ;
  virtual const char* getDescription() const;
  virtual Action* createNew() const;

  virtual void obtainParameters(vector<Parameter*>& parameters);

  virtual void perform();

 private:
  StringParameter _inputFormat;
  StringParameter _outputFormat;
  BoolParameter _zero;
};

#endif
