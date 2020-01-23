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
#ifndef DECOM_RECORDER_GUARD
#define DECOM_RECORDER_GUARD

#include "TermConsumer.h"
#include "Term.h"

class Ideal;

class DecomRecorder : public TermConsumer {
public:
  // DecomRecorder does not take over ownership of recordInto.
  DecomRecorder(Ideal* recordInto);
  virtual ~DecomRecorder();

  virtual void consume(const Term& term);

private:
  Ideal* _recordInto;
  Term _tmp;
};

#endif
