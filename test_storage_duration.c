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

#include "storage_duration.h"

allocated_push_back(int);
automated_push_back(int);

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int   *allocated      = {0}, automated[4096] = {0};
    size_t allocated_size = {0}, automated_size  = {0};

    for (size_t x = 0; x < sizeof automated / sizeof *automated; x++) {
        push_back(int, allocated, allocated_size, rand());
        push_back(int, automated, automated_size, rand()); 
        putchar('.');
    }

    tear_down(int, allocated, allocated_size);
    tear_down(int, automated, automated_size);
}
