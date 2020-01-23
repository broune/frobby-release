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
#include "BigIdeal.h"

#include "VarNames.h"
#include "TermTranslator.h"
#include "Ideal.h"

class OffsetTermCompare {
public:
  OffsetTermCompare(const BigIdeal& ideal): _ideal(ideal) {
  }

  bool operator()(size_t aa, size_t bb) const {
	const vector<mpz_class>& a = _ideal.getTerm(aa);
	const vector<mpz_class>& b = _ideal.getTerm(bb);

	ASSERT(a.size() == b.size());
	for (size_t i = 0; i < a.size(); ++i) {
	  if (a[i] > b[i])
		return true;
	  if (a[i] < b[i])
		return false;
	}
	return false;
  }

private:
  const BigIdeal& _ideal;
};

BigIdeal::BigIdeal() {
}

BigIdeal::BigIdeal(const VarNames& names):
  _names(names) {
}

void BigIdeal::insert(const Ideal& ideal) {
  _terms.reserve(_terms.size() + ideal.getGeneratorCount());

  Ideal::const_iterator it = ideal.begin();
  for (; it != ideal.end(); ++it) {
    newLastTerm();

    for (size_t var = 0; var < _names.getVarCount(); ++var)
      getLastTermExponentRef(var) = (*it)[var];
  }
}

void BigIdeal::insert(const Ideal& ideal,
					  const TermTranslator& translator) {
  _terms.reserve(_terms.size() + ideal.getGeneratorCount());

  Ideal::const_iterator it = ideal.begin();
  for (; it != ideal.end(); ++it) {
    newLastTerm();

    for (size_t var = 0; var < _names.getVarCount(); ++var)
      getLastTermExponentRef(var) = translator.getExponent(var, (*it)[var]);
  }
}

void BigIdeal::setNames(const VarNames& names) {
  _names = names;
}

void BigIdeal::newLastTerm() {
  if (_terms.size() == _terms.capacity())
	reserve(getVarCount() * _terms.size());

  _terms.resize(_terms.size() + 1);
  _terms.back().resize(_names.getVarCount());
}

void BigIdeal::reserve(size_t capacity) {
  // std::vector can do reallocations by itself, but the version here
  // is much faster.
  if (capacity <= _terms.capacity())
	return;

  // We grow the capacity at a rate of getVarCount() instead of a
  // doubling because each *used* entry allocates at least
  // getVarCount() memory anyway, so we will still only use at most
  // double the memory than we need.
  //
  // We make tmp have the capacity we need, then we move the data
  // entry by entry to tmp, and then we swap tmp and _terms. This
  // will also swap the excess capacity into _terms. If allowed to
  // reallocate by itself, the implementation of STL (GCC 3.4.4) I'm
  // using will *copy* the data instead of swapping it, which is
  // very bad.
  vector<vector<mpz_class> > tmp;
  size_t newCapacity = getVarCount() * _terms.size();
  if (capacity > newCapacity)
	newCapacity = capacity;

  tmp.reserve(newCapacity);
  tmp.resize(_terms.size());

  size_t size = _terms.size();
  for (size_t i = 0; i < size; ++i)
	tmp[i].swap(_terms[i]);
  tmp.swap(_terms);
}

mpz_class& BigIdeal::getLastTermExponentRef(size_t var) {
  ASSERT(!empty());
  ASSERT(var < _names.getVarCount());
  
  return _terms.back()[var];
}

vector<mpz_class>& BigIdeal::getLastTermRef() {
  ASSERT(!empty());

  return _terms.back();
}

const vector<mpz_class>& BigIdeal::getTerm(size_t term) const {
  ASSERT(term < getGeneratorCount());
  return _terms[term];
}

void BigIdeal::getLcm(vector<mpz_class>& lcm) const {
  lcm.clear();
  lcm.resize(getVarCount());

  for (vector<vector<mpz_class> >::const_iterator it = _terms.begin();
	   it != _terms.end(); ++it)
	for (size_t var = 0; var < getVarCount(); ++var)
	  if (lcm[var] < (*it)[var])
		lcm[var] = (*it)[var];
}

bool BigIdeal::operator==(const BigIdeal& b) const {
  return _terms == b._terms;
}

vector<mpz_class>& BigIdeal::operator[](unsigned int index) {
  ASSERT(index < _terms.size());
  return _terms[index];
}

const vector<mpz_class>& BigIdeal::operator[](unsigned int index) const {
  ASSERT(index < _terms.size());
  return _terms[index];
}

bool BigIdeal::empty() const {
  return _terms.empty();
}

void BigIdeal::clear() {
  _terms.clear();
}

size_t BigIdeal::getGeneratorCount() const {
  return _terms.size();
}

size_t BigIdeal::getVarCount() const {
  return _names.getVarCount();
}

void BigIdeal::clearAndSetNames(const VarNames& names) {
  clear();
  _names = names;
}

const VarNames& BigIdeal::getNames() const {
  return _names;
}

void BigIdeal::sortGeneratorsUnique() {
  sortGenerators();
  vector<vector<mpz_class> >::iterator newEnd =
    unique(_terms.begin(), _terms.end());
  _terms.erase(newEnd, _terms.end());
}

void BigIdeal::sortGenerators() {
  size_t size = _terms.size();
  vector<size_t> sortedOffsets(size);
  for (size_t term = 0; term < size; ++term)
	sortedOffsets[term] = term;

  std::sort(sortedOffsets.begin(), sortedOffsets.end(),
			OffsetTermCompare(*this));

  vector<vector<mpz_class> > sorted;
  sorted.reserve(_terms.capacity());
  sorted.resize(size);
  for (size_t term = 0; term < size; ++term)
	sorted[term].swap(_terms[sortedOffsets[term]]);

  _terms.swap(sorted);
}

struct VarSorter {
  VarSorter(VarNames& names):
    _names(names),
	_tmp(names.getVarCount()) {
	_permutation.reserve(names.getVarCount());
    for (size_t i = 0; i < names.getVarCount(); ++i)
      _permutation.push_back(i);
    sort(_permutation.begin(), _permutation.end(), *this);
  }

  bool operator()(size_t a, size_t b) const {
    return
      _names.getName(_permutation[a]) <
      _names.getName(_permutation[b]);
  }

  void getOrderedNames(VarNames& names) {
    names.clear();
    for (size_t i = 0; i < _permutation.size(); ++i)
      names.addVar(_names.getName(_permutation[i]));
  }

  void permute(vector<mpz_class>& term) {
	ASSERT(term.size() == _tmp.size());
    _tmp.swap(term);
    for (size_t i = 0; i < _permutation.size(); ++i)
	  mpz_swap(term[i].get_mpz_t(), _tmp[_permutation[i]].get_mpz_t());
  }

private:
  vector<size_t> _permutation;
  VarNames _names;
  vector<mpz_class> _tmp;
};

void BigIdeal::sortVariables() {
  VarSorter sorter(_names);
  sorter.getOrderedNames(_names);
  for (size_t i = 0; i < _terms.size(); ++i)
    sorter.permute(_terms[i]);
}

void BigIdeal::print(FILE* file) const {
  fprintf(stderr, "/---- BigIdeal of %lu terms:\n",
	  (unsigned long)_terms.size());
  for (vector<vector<mpz_class> >::const_iterator it = _terms.begin();
       it != _terms.end(); ++it) {
    for (vector<mpz_class>::const_iterator entry = it->begin();
	 entry != it->end(); ++entry)
      gmp_fprintf(file, "%Zd ", entry->get_mpz_t());
    fputc('\n', file);
  }
  fputs("----/ End of list.\n", file);
}

const mpz_class& BigIdeal::getExponent(size_t term, size_t var) const {
  ASSERT(term < _terms.size());
  ASSERT(var < _names.getVarCount());

  return _terms[term][var];
}

mpz_class& BigIdeal::getExponent(size_t term, size_t var) {
  ASSERT(term < _terms.size());
  ASSERT(var < _names.getVarCount());

  return _terms[term][var];
}

void BigIdeal::setExponent(size_t term, size_t var, const mpz_class& exp) {
  ASSERT(term < _terms.size());
  ASSERT(var < _names.getVarCount());

  _terms[term][var] = exp;
}

bool BigIdeal::bigTermCompare(const vector<mpz_class>& a,
			      const vector<mpz_class>& b) {
  ASSERT(a.size() == b.size());
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] > b[i])
      return true;
    if (a[i] < b[i])
      return false;
  }
  return false;
}