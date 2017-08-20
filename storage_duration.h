/* The MIT License (MIT)
 * 
 * Copyright (c) 2017 Sebastian Ramadan
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef INCLUDE_STORAGE_DURATION_H
#define INCLUDE_STORAGE_DURATION_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef void *internal(void *base, size_t nelem, size_t size);
internal allocated_internal;
internal automated_internal;
void *internal_push_back(void **, size_t *, size_t, void const *, size_t, internal *);
int   external_push_back(FILE *,  size_t *, size_t, void const *, size_t);

#ifndef COMPILE_STORAGE_DURATION_C
#define allocated_push_back(T) \
 int allocated_##T##_push_back(T **base, size_t *nelem, size_t max, T value) {\
     void *b = *base;                                                         \
     int   r = internal_push_back(&b, nelem, max, &value                      \
                                                , sizeof (T)                  \
                                                , allocated_internal);        \
     if ((T *) b != *base) { *base = b; }                                     \
     return r;                                                                 }
#define automated_push_back(T) \
 int automated_##T##_push_back(T *base, size_t *nelem, size_t max, T value) {\
     return internal_push_back(&(void *){base}, nelem, max, &value           \
                                              , sizeof (T)                   \
                                              , automated_internal);          }
#define relocated_push_back(T) \
 int relocated_##T##_push_back(FILE *base, size_t *nelem, size_t max, T value) {\
     return external_push_back(base, nelem, max, &value, sizeof (T));           }

#define push_back(T, base, nelem, value) \
 _Generic(&base   , T **:    allocated_##T##_push_back((void *) &base, &nelem    \
                                                                     , SIZE_MAX  \
                                                                     / sizeof (T)\
                                                                     , value)    \
                  , default:                                                     \
 _Generic(&base[0], FILE *:  relocated_##T##_push_back( base, &nelem, SIZE_MAX   \
                                                                    / sizeof (T) \
                                                                    , value)     \
                  , T *:     automated_##T##_push_back( base, &nelem, sizeof base\
                                                                    / sizeof (T) \
                                                                    , value)))

#define tear_down(T, base, nelem)                           \
 free(_Generic(&base   , T **:    base                      \
                       , default:                           \
      _Generic(&base[0], FILE *:  fclose((void *) base) && 0\
                       , T *:     NULL)));                  \
 nelem = 0 
#else
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#endif
#endif

