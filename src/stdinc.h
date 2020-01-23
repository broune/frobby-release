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
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

//#define LOG
//#define PROFILE

#ifdef PROFILE
static void _noInline() {cerr << "this should not be printed - inlining prevention has gone awry" << endl;}
int _noInlineVariable = time(0); // so the compiler will not know what the value is
// place enough code into the function so that it will not be inlined.
#define PROFILE_NO_INLINE {if (_noInlineVariable == -1){\
_noInline();_noInline();_noInline();_noInline();_noInline();\
_noInline();_noInline();_noInline();_noInline();_noInline();\
_noInline();_noInline();_noInline();_noInline();_noInline();\
_noInline();_noInline();_noInline();_noInline();_noInline();\
_noInline();_noInline();_noInline();_noInline();_noInline();\
_noInline();_noInline();_noInline();_noInline();_noInline();}}
#else
#define PROFILE_NO_INLINE
#endif

#ifdef DEBUG
#define PRINT
#define IF_DEBUG(X) X
#include <cassert>
#define ASSERT(X) assert(X);
#else
#define IF_DEBUG(X)
#define ASSERT(X)
#endif

typedef unsigned int Exponent;
typedef mpz_class Degree;

namespace constants {
  extern const char* version;
}