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
#ifndef ALLOCATOR_GUARD
#define ALLOCATOR_GUARD

// TODO: this class needs an overhaul.
template<class T>
class Allocator {
 public:
  Allocator():
    _buffers(),
    _buffer(0),
    _bufferEnd(0) {
  }

  ~Allocator() {
    clear();
  }

  void clear() throw() {
    for (typename list<T*>::iterator it = _buffers.begin();
	 it != _buffers.end(); ++it)
      doBuffer(*it);
    _buffers.clear();

    _buffer = 0;
    _bufferEnd = 0;
  }

  T* allocate() throw() {
    if (_buffer == _bufferEnd) {
      _buffer = doBuffer(0);
      _bufferEnd = _buffer + BufferSize;
      _buffers.push_back(_buffer);
    }

    return _buffer++;
  }

  static void clearStatic() throw() {
    doBuffer((T*)1);
  }

 private:
  static const int BufferSize = 1000;

  // We declare a single static variable of this type inside
  // doBuffer. This will cause the destructor to be called on program
  // exit, thus clearing the buffers, which we want to do to avoid
  // spurious reports from memory leak detectors. We have to put the
  // buffer object inside ClearBuffers to make sure that the buffers
  // object does not get destructed before ClearBuffers get destructed,
  // which could otherwise happen if we had simply declared buffers as a
  // static local variable inside doBuffer.
  template<class S>
    class ClearBuffers {
    public:
    ~ClearBuffers() {clearStatic();}
    vector<S*> buffers;
  };


  // A hack to get static data working without problems.
  static T* doBuffer(T* buffer) {
    static ClearBuffers<T> clearBuffers;
    vector<T*>& buffers = clearBuffers.buffers;

    if (buffer == (T*)1) {
      // TODO: check if 1 is really invalid as a pointer.
      for (typename vector<T*>::iterator it = buffers.begin();
	   it != buffers.end(); ++it) {
	delete[] *it;
      }
      buffers.clear();
      return 0;
    }
    else if (buffer == 0) {
      if (buffers.empty()) {
	return new T[BufferSize];
      }
      else {
	T* tmp = buffers.back();
	buffers.pop_back();
	return tmp;
      }
    } else {
      buffers.push_back(buffer);
      return 0;
    }
  }

  Allocator(const Allocator&); // not supported
  Allocator& operator=(const Allocator&); // not supported

  list<T*> _buffers;
  T* _buffer;
  T* _bufferEnd;
};

#endif
