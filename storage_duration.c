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

#define COMPILE_STORAGE_DURATION_C
#include "storage_duration.h"

void *allocated_internal(void *base, size_t nelem, size_t size) {
    return (nelem & -~nelem) ? base
                             : realloc(base, (nelem + -~nelem) * size);
}

void *automated_internal(void *base, size_t nelem, size_t size) {
    return base;
}

void *internal_push_back(void **base, size_t *nelem, size_t max_nelem, void const *value, size_t size, internal *func) {
    if (*nelem == max_nelem) {
        return NULL;
    }

    typedef unsigned char array[size];
    array *b = func(*base, *nelem, size);
    if (!b) {
        return NULL;
    }

    *base = b;
    b += (*nelem)++;
    return value
         ? memmove(*b, value, sizeof *b)
         : *b;
}

int external_push_back(FILE *base, size_t *nelem, size_t max_nelem, void const *value, size_t size) {
    return *nelem == max_nelem
        || fseek(base, *nelem * size, SEEK_SET)
        || fwrite(value, size, 1, base)
        || !++*nelem;
}

