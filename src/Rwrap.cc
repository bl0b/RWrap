/* RWrap
 *
 * Copyright (C) 2012 Damien "bl0b" Leroux
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "RWrap.h"
#include <dlfcn.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Rwrap NAMESPACE and glue generator © 2012 Damien Leroux" << std::endl;
        std::cout << "Usage: " << argv[0] << " path/to/SHLIB.so" << std::endl;
        return -1;
    }
    void* handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        std::cerr << "Couldn't open shared object " << argv[1] << std::endl;
        return -1;
    }
    void (*gen)() = (void (*)()) dlsym(handle, "Rwrap_gen");
    if (!gen) {
        std::cerr << "Shared object doesn't seem to be an Rwrap'd SHLIB." << std::endl;
        return -1;
    }
    gen();
    return 0;
}

