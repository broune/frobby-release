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
#ifndef HELP_ACTION_GUARD
#define HELP_ACTION_GUARD

#include "Action.h"

class HelpAction : public Action {
 public:
  HelpAction();

  virtual const char* getName() const;
  virtual const char* getShortDescription() const;
  virtual const char* getDescription() const;

  virtual void obtainParameters(vector<Parameter*>& parameters);

  virtual bool acceptsNonParameter() const;
  virtual bool processNonParameter(const char* str);

  virtual Action* createNew() const;

  virtual void perform();

 private:
  void displayTopic();

  Action* _topic;
};

#endif
